/*
 * SR04.c
 *
 *  Created on: Jul 15, 2025
 *      Author: Dayane
 */
/* Private Includes */
#include "SR04.h"


/* Private Defines */
#define DELAY_BETWEEN_SAMPLES 		50


/* Extern variables */
extern TIM_HandleTypeDef htim17;


/* Private Variables */
uint8_t index_sr04 = 0;


/* Exported Functions */
void SR04_GetDistance (uint8_t *pData)
{
	/* Local Variables */
	float distance = 0;
	uint8_t *p_aux = pData;
	uint16_t time_elapsed_us = 0;
	uint8_t measurements_counter = 0;

	/* Get 10 samples of the distance sensor */
	for (uint8_t i=0; i<10; i++)
	{
		/* Reset the timer counter */
		__HAL_TIM_SET_COUNTER(&htim17, 0);

		/* Send the >10us pulse */
		HAL_GPIO_WritePin(SR04_TRIGGER_GPIO_Port, SR04_TRIGGER_Pin, GPIO_PIN_SET);

		/* Random delay >10us .-. */
		for(uint32_t i = 0; i < 500; i++)
			__NOP();

		/* Resetting the pin to finish the pulse */
		HAL_GPIO_WritePin(SR04_TRIGGER_GPIO_Port, SR04_TRIGGER_Pin, GPIO_PIN_RESET);

		__HAL_TIM_ENABLE(&htim17);

		/* Wait for the Echo pin to be low or until timeout */
		while(HAL_GPIO_ReadPin(SR04_ECHO_GPIO_Port, SR04_ECHO_Pin) == GPIO_PIN_RESET)
			if(__HAL_TIM_GET_COUNTER(&htim17) >= 10000)
				break;

		__HAL_TIM_DISABLE(&htim17);

		if(__HAL_TIM_GET_COUNTER(&htim17) >= 10000)
		{
			continue;
		}

		__HAL_TIM_SET_COUNTER(&htim17, 0);

		/* Echo pin got low, prepare for the SHOW! */
		__HAL_TIM_ENABLE(&htim17);

		/* Wait for the Echo pin to be high, or until the sensor die */
		while(HAL_GPIO_ReadPin(SR04_ECHO_GPIO_Port, SR04_ECHO_Pin) == GPIO_PIN_SET)
			if(__HAL_TIM_GET_COUNTER(&htim17) >= 38000) // Dumb sensor
				break;

		/* Disable the timer and think you are happy */
		__HAL_TIM_DISABLE(&htim17);

		time_elapsed_us = __HAL_TIM_GET_COUNTER(&htim17);

		/* Check if the sensor data is useful */
		if(time_elapsed_us < 30000)
		{
			/* Good sensor data, sum the data to extract the average after */
			distance += ((float)time_elapsed_us) / 58.0;	// Get distance in centimeters, NOTE cm >>>> in (bullshit, inches sucks)
			measurements_counter++;
		}

		/* Minor delay between reads */
		HAL_Delay(DELAY_BETWEEN_SAMPLES);
	}



	/* Check if the sensor is not a complete useless */
	if(measurements_counter > 0)
	{
		/* Calculate the average */
		distance = distance/((float)measurements_counter);

		/* Check if we are in the last position of the buffer */
		if (index_sr04 == 6)
		{
			/* Move all samples to the left */
			p_aux[0]=p_aux[1];
			p_aux[1]=p_aux[2];
			p_aux[2]=p_aux[3];
			p_aux[3]=p_aux[4];
			p_aux[4]=p_aux[5];

			index_sr04 = 5;
		}

		/* Store the measured distance in the buffer */
		p_aux[index_sr04] = (uint8_t)((distance/800.0) * 255);

		index_sr04++;
	}
}
