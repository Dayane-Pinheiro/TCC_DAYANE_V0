/*
 * LIS.h
 *
 *  Created on: Jul 15, 2025
 *      Author: Dayane
 */

#ifndef SENSOR_LIS_H_
#define SENSOR_LIS_H_

/* Exported Includes */
#include "main.h"


/* Exported Variables */
extern volatile FlagStatus acc_data_ready;


/* Exported Function Prototypes */
uint8_t MEMS_GetRain(void);


#endif /* SENSOR_LIS_H_ */
