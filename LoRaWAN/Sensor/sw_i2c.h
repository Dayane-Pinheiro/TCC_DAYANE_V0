/*
 * sw_i2c.h
 *
 *  Created on: Jul 14, 2025
 *      Author: botelhod
 */

#ifndef SW_I2C_H_
#define SW_I2C_H_

/* Exported Includes */
#include "main.h"


/* Exported Defines */
#define SW_I2C_OK				0
#define SW_I2C_ERROR			1


/* Exported Functions Prototypes */
int32_t SW_I2C_Init(void);
int32_t SW_I2C_DeInit(void);
int32_t SW_I2C_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t SW_I2C_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t SW_I2C_GetTick(void);

#endif /* SW_I2C_H_ */
