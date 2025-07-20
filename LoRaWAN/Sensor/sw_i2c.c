/*
 * sw_i2c.c
 *
 *  Created on: Jul 14, 2025
 *      Author: botelhod
 */
/* Private Includes */
#include "sw_i2c.h"
#include <stdio.h>

/* Private Macros */
#define DELAY_TIM_HANLDE			htim17
#define	I2C_SDA_Port				SW_I2C_SDA_GPIO_Port
#define	I2C_SDA_Pin					SW_I2C_SDA_Pin
#define	I2C_SCL_Port				SW_I2C_SCL_GPIO_Port
#define	I2C_SCL_Pin					SW_I2C_SCL_Pin

#define I2C_SET_SDA					SW_I2C_SDA_GPIO_Port->BSRR |= SW_I2C_SDA_Pin;
#define I2C_RESET_SDA				SW_I2C_SDA_GPIO_Port->BRR |= SW_I2C_SDA_Pin;
#define I2C_SET_SCL					SW_I2C_SCL_GPIO_Port->BSRR |= SW_I2C_SCL_Pin;
#define I2C_RESET_SCL				SW_I2C_SCL_GPIO_Port->BRR |= SW_I2C_SCL_Pin;

#define I2C_READ_SDA				((SW_I2C_SDA_GPIO_Port->IDR & SW_I2C_SDA_Pin) ? 1 : 0);

#define I2C_DELAY					i2c_delay(1);

#define I2C_START_CONDITION_YES		1
#define I2C_START_CONDITION_NO		0
#define I2C_STOP_CONDITION_YES		1
#define I2C_STOP_CONDITION_NO		0
#define I2C_SEND_ACK_TO_RECEIVE		1
#define I2C_SEND_NACK_TO_RECEIVE	0

#define I2C_ACK						0
#define I2C_NACK					1


/* Private Variables */
extern TIM_HandleTypeDef DELAY_TIM_HANLDE;


/* Private Function Prototypes */
static void i2c_delay(uint16_t delay);
static void i2c_start_condition(void);
static void i2c_stop_condition(void);
static void i2c_write_bit(uint8_t bit);
static uint8_t i2c_read_bit(void);
static uint8_t i2c_write_byte(uint8_t byte, uint8_t start, uint8_t stop);
static uint8_t i2c_read_byte(uint8_t ack, uint8_t stop);


/* Private Functions */
static void i2c_delay(uint16_t delay)
{
	for(uint32_t i = 0; i < delay*50; i++)
	{
		asm("NOP");
	}
}

static void i2c_start_condition(void)
{
	I2C_SET_SCL
	I2C_SET_SDA
	I2C_DELAY
	I2C_RESET_SDA
	I2C_DELAY
	I2C_RESET_SCL
	I2C_DELAY
}

static void i2c_stop_condition(void)
{
	I2C_RESET_SDA
	I2C_DELAY
	I2C_SET_SCL
	I2C_DELAY
	I2C_SET_SDA
	I2C_DELAY
}

static void i2c_write_bit(uint8_t bit)
{
	if (bit > 0)
		I2C_SET_SDA
	else
		I2C_RESET_SDA

	I2C_DELAY
	I2C_SET_SCL
	I2C_DELAY
	I2C_RESET_SCL
}

static uint8_t i2c_read_bit(void)
{
	uint8_t b;

	I2C_SET_SDA
	I2C_DELAY
	I2C_SET_SCL
	I2C_DELAY

	b = I2C_READ_SDA

	I2C_RESET_SCL

	return b;
}

static uint8_t i2c_write_byte(uint8_t byte, uint8_t start, uint8_t stop)
{
	uint8_t ack = 0;

	if (start)
		i2c_start_condition();

	for (uint8_t i = 0; i < 8; i++)
	{
		i2c_write_bit(byte & 0x80); // write the most-significant bit
		byte <<= 1;
	}

	ack = i2c_read_bit();

	if (stop)
		i2c_stop_condition();

	return ack; //0-ack, 1-nack
}

static uint8_t i2c_read_byte(uint8_t ack, uint8_t stop)
{
	uint8_t B = 0;

	for (uint8_t i = 0; i < 8; i++)
	{
		B <<= 1;
		B |= i2c_read_bit();
	}

	if (ack)
		i2c_write_bit(0);
	else
		i2c_write_bit(1);

	if (stop)
		i2c_stop_condition();

	return B;
}


/* Exported Functions */
int32_t SW_I2C_Init(void)
{
	HAL_TIM_Base_Start(&DELAY_TIM_HANLDE);

	return 0;
}

int32_t SW_I2C_DeInit(void)
{
	HAL_TIM_Base_Stop(&DELAY_TIM_HANLDE);

	return 0;
}

int32_t SW_I2C_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
	uint8_t *p_aux = pData;

	/* Force a STOP condition before start */
	i2c_stop_condition();

	/* Send the Device Address - Need start condition only */
	if (i2c_write_byte(DevAddr & (~0x01), I2C_START_CONDITION_YES, I2C_STOP_CONDITION_NO) != I2C_ACK)
	{
		i2c_stop_condition();
		return I2C_NACK;
	}

	/* Send the Reg Address to be read */
	if (i2c_write_byte(Reg, I2C_START_CONDITION_NO, I2C_STOP_CONDITION_NO) != I2C_ACK)
	{
		i2c_stop_condition();
		return I2C_NACK;
	}

	if (i2c_write_byte(DevAddr | 0x01, I2C_START_CONDITION_YES, I2C_STOP_CONDITION_NO) != I2C_ACK) // start again, send address, read
	{
		i2c_stop_condition();
		return I2C_NACK;
	}

	for(uint8_t i = 0; i < Length; i++)
	{
		if(i != (Length - 1))
		{
			*p_aux = i2c_read_byte(I2C_SEND_ACK_TO_RECEIVE, I2C_STOP_CONDITION_NO); // read data
			p_aux++;
		}
		else
		{
			*p_aux = i2c_read_byte(I2C_SEND_NACK_TO_RECEIVE, I2C_STOP_CONDITION_YES); // read data
		}
	}

	return I2C_ACK;
}

int32_t SW_I2C_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{

	uint8_t *p_aux = pData;

	/* Force a STOP condition before start */
	i2c_stop_condition();

	/* Send the Device Address - Need start condition only */
	if (i2c_write_byte(DevAddr & (~0x01), I2C_START_CONDITION_YES, I2C_STOP_CONDITION_NO) != I2C_ACK)
	{
		i2c_stop_condition();
		return I2C_NACK;
	}

	/* Send the Reg Address to be read */
	if (i2c_write_byte(Reg, I2C_START_CONDITION_NO, I2C_STOP_CONDITION_NO) != I2C_ACK)
	{
		i2c_stop_condition();
		return I2C_NACK;
	}

	for(uint8_t i = 0; i < Length; i++)
	{
		if(i != (Length - 1))
		{
			i2c_write_byte(*p_aux, I2C_START_CONDITION_NO, I2C_STOP_CONDITION_NO); // read data
			p_aux++;
		}
		else
		{
			i2c_write_byte(*p_aux, I2C_START_CONDITION_NO, I2C_STOP_CONDITION_YES); // read data
		}
	}

	return I2C_ACK;
}

int32_t SW_I2C_GetTick(void)
{
	return HAL_GetTick();
}
