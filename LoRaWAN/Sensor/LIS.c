/*
 * LIS.c
 *
 *  Created on: Jul 15, 2025
 *      Author: Dayane
 */
/* Private Includes */
#include "LIS.h"
#include "lis2dw12.h"
#include "sw_i2c.h"
#include "NanoEdgeAI.h"
#include "knowledge.h"


/* Private Defines */
#define ACC_NBR_OF_SAMPLES					16
#define ACC_NBR_OF_AXES						1
#define ACC_READ_TIMEOUT					32000


/* Local Variables */
volatile FlagStatus acc_data_ready = RESET;
LIS2DW12_Object_t MotionSensor;
FlagStatus is_sensor_initialized = RESET;


/* Private Function Prototypes */
void MEMS_Init(void);


/* Private Functions */
void MEMS_Init(void)
{
	/* Local Variables */
	LIS2DW12_IO_t io_ctx;
	LIS2DW12_AxesRaw_t axes;
	uint8_t id = 0;

	/* Link I2C functions to the LIS2DW12 driver */
	io_ctx.Address     = LIS2DW12_I2C_ADD_H;
	io_ctx.Init        = SW_I2C_Init;
	io_ctx.DeInit      = SW_I2C_DeInit;
	io_ctx.ReadReg     = SW_I2C_ReadReg;
	io_ctx.WriteReg    = SW_I2C_WriteReg;
	io_ctx.GetTick     = SW_I2C_GetTick;

	LIS2DW12_RegisterBusIO(&MotionSensor, &io_ctx);

	/* Read the LIS2DW12 WHO_AM_I register */
	for(uint8_t i = 0; i < 5; i++)
	{
		LIS2DW12_ReadID(&MotionSensor, &id);
		if (id == LIS2DW12_ID)
		{
			is_sensor_initialized = SET;
			break;
		}

		io_ctx.Address = LIS2DW12_I2C_ADD_L;

		LIS2DW12_ReadID(&MotionSensor, &id);
		if (id == LIS2DW12_ID)
		{
			is_sensor_initialized = SET;
			break;
		}

		io_ctx.Address = LIS2DW12_I2C_ADD_H;
	}

	/* Initialize the LIS2DW12 sensor */
	LIS2DW12_Init(&MotionSensor);

	/* Configure the LIS2DW12 accelerometer (ODR, scale and interrupt) */
	LIS2DW12_ACC_SetOutputDataRate(&MotionSensor, 26.0f); /* 26 Hz */
	LIS2DW12_ACC_SetFullScale(&MotionSensor, 2);     /* [-2000mg; +2000mg] */
	LIS2DW12_ACC_Enable_DRDY_Interrupt(&MotionSensor);   /* Enable DRDY INT1*/
	LIS2DW12_ACC_GetAxesRaw(&MotionSensor, &axes);   /* Clear DRDY */

	neai_classification_init(knowledge);
}


/* Exported Functions */
uint8_t MEMS_GetRain(void)
{
	/* Local Variables */
	uint32_t timeout_tick = 0;
	int16_t sensor_raw_data[3];
	float sensor_normalized_data[ACC_NBR_OF_SAMPLES * ACC_NBR_OF_AXES];
	float output_buffer[3];
	uint16_t result, result_average=0;

	/* Verify if the sensor is initialized */
	if(is_sensor_initialized == RESET)
	{
		/* Try to reinitialize the sensor */
		MEMS_Init();

		/* Not able to initialize the sensor, return 0 to avoid code to be blocked */
		if(is_sensor_initialized == RESET)
			return 3;
	}

	/* Start the LIS2DW12 accelerometer */
	LIS2DW12_ACC_Enable(&MotionSensor);

	/* Read the accelerometer data */
	for(uint8_t i = 0; i < ACC_NBR_OF_SAMPLES; i++)
	{
		/* Reset the timeout counter */
		timeout_tick = 0;

		/* Wait for the data to be ready */
		while(acc_data_ready == RESET)
		{
			/* Check if the time ended-up */
			if(timeout_tick++ >= ACC_READ_TIMEOUT)
			{
				/* Return error */
				return 3;
			}
		}

		/* Read the sensor data */
		lis2dw12_acceleration_raw_get(&MotionSensor.Ctx, sensor_raw_data);

		/* Convert the read data to mg */
		sensor_normalized_data[(i)] = lis2dw12_from_fs2_to_mg(sensor_raw_data[2]);
		//			sensor_normalized_data[(i * 3) + 1] = lis2dw12_from_fs2_to_mg(sensor_raw_data[1]);
		//			sensor_normalized_data[(i * 3) + 2] = lis2dw12_from_fs2_to_mg(sensor_raw_data[2]);
	}

	/* Stop the accelerometer */
	LIS2DW12_ACC_Disable(&MotionSensor);

	/* NanoEdge Part */
	neai_classification(sensor_normalized_data, output_buffer, &result);


	return (uint8_t)(result - 1);
}
