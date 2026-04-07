#ifndef _BNO055_H_
#define _BNO055_H_
#include "stm32f4xx_hal.h"

/* =============================================== DEFINES =============================================== */
//#define
#define BNO055_ADDR 		(0x29 << 1)
#define SYS_TRIGGER_ADDR 	0x3F
#define OPR_MODE_ADDR 		0x3D

#define ACCX_LSB_ADDR		0x08
#define GYROX_LSB_ADDR    	0x14
#define EULER_LSB_ADDR    	0x1A

#define INT_TO_EULER		(1/16.0f)
#define INT_TO_DPS			(1/16.0f)
#define INT_TO_MPS2			0.00981f

#define IMU_BUFFER_LEN		24				// Euler + Acc + Mag+ Gyro = 3x2 * 4 = 24
#define IMU_PACKED_LEN		18				// Acc (6), Gyro (6), Euler (6)
#define EULER_TOTAL_BYTES	6 //

/* =============================================== PROTOTYPES =============================================== */
HAL_StatusTypeDef BNO055_Init(I2C_HandleTypeDef *hi2c);
//void BNO055_ReadIMU(I2C_HandleTypeDef *hi2c, uint8_t* IMU_Data);
void BNO055_ReadIMU(I2C_HandleTypeDef *hi2c, uint8_t* IMU_Data);
void BNO055_ReadEuler(I2C_HandleTypeDef *hi2c, float* Att);

// DEBUG
void BNO055_ReadIMU_DEBUG(I2C_HandleTypeDef *hi2c, float* Acc, float* Gyro, float* AttEuler);

#endif
