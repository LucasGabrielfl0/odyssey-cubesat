#ifndef MPU6050_H_
#define MPU6050_H_

#include "stm32f4xx_hal.h"

/* ----------------------------------------------*/
// MPU6050
#define MPU6050_ADDR  		(0x68 << 1)			// WHO_AM_I
#define PWR_MGMT_1			0x6B				// Wake up

// Gyro
#define GYRO_CONFIG			0x1B				// Gyro full-scale
#define GYRO_XOUT_H			0x43				// First Gyro data register
#define GYRO_CAL_SAMPLES 	500

// Acc
#define ACCEL_CONFIG		0x1C				// Accel full-scale
#define ACCEL_XOUT_H		0x3B				// First accel data register

// GY-271
#define HMC5883L_ADDR 		(0x1E << 1)			// WHO_AM_I

//
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} IMU_int16;
typedef struct {
    float x;
    float y;
    float z;
} IMU_float;

///*---------------------------------------------------------------------------------------------*/
// MPU6050
void MPU6050_Init(I2C_HandleTypeDef *hi2c);													// Start the sensor

//
void MPU6050_Read_Gyro_Raw(I2C_HandleTypeDef *hi2c, IMU_int16 *gyro_raw);						// Read raw int16_t value
void MPU6050_Read_Gyro(I2C_HandleTypeDef *hi2c, IMU_int16 offset, IMU_float *gyro_dps);			// Read gyro, returns float dps value
void MPU6050_Gyro_Calibrate(I2C_HandleTypeDef *hi2c, IMU_int16 *offset);						// Read gyro, returns offset int16_t

void MPU6050_Read_Accel(I2C_HandleTypeDef *hi2c, IMU_float *Acc);								//
//

#endif
