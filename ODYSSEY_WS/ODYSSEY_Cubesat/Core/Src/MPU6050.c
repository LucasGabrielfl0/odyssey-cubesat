#include "MPU6050.h"

///*========================================================================================================================*/
/* Initialize the MPU6050 sensor (Both the Accelerometer and the Gyroscope)*/
void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    // Wake up MPU6050
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x6B, 1, &data, 1, HAL_MAX_DELAY);

    // Set accelerometer full scale to ±2g (default, but be explicit)
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x1C, 1, &data, 1, HAL_MAX_DELAY);

    // Gyro full scale ±250 dps
    data = 0x00;   // FS_SEL = 0
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x1B, 1, &data, 1, HAL_MAX_DELAY);

    data = 0x03;   // DLPF = 3 (~44 Hz gyro bandwidth)
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x1A, 1, &data, 1, HAL_MAX_DELAY);
}

//
/*==================== Read  Gyroscope =================== */
void MPU6050_Read_Gyro_Raw(I2C_HandleTypeDef *hi2c, IMU_int16 *gyro_raw)
{
    uint8_t buf[6];

    HAL_I2C_Mem_Read(hi2c,
                     MPU6050_ADDR,
                     GYRO_XOUT_H,
                     1,
                     buf,
                     6,
                     HAL_MAX_DELAY);

    gyro_raw->x = (int16_t)(buf[0] << 8 | buf[1]);
    gyro_raw->y = (int16_t)(buf[2] << 8 | buf[3]);
    gyro_raw->z = (int16_t)(buf[4] << 8 | buf[5]);
}

/* Calibrates the Gyro during start-up (Sensor must be still) */
void MPU6050_Gyro_Calibrate(I2C_HandleTypeDef *hi2c, IMU_int16 *offset)
{
    int32_t sum_x = 0;
    int32_t sum_y = 0;
    int32_t sum_z = 0;

    IMU_int16 gyro_raw;

    for (int i = 0; i < GYRO_CAL_SAMPLES; i++)
    {
    	MPU6050_Read_Gyro_Raw(hi2c, &gyro_raw);

        sum_x += gyro_raw.x;
        sum_y += gyro_raw.y;
        sum_z += gyro_raw.z;

        HAL_Delay(2);
    }

    offset->x = sum_x / GYRO_CAL_SAMPLES;
    offset->y = sum_y / GYRO_CAL_SAMPLES;
    offset->z = sum_z / GYRO_CAL_SAMPLES;
}

void MPU6050_Read_Gyro(I2C_HandleTypeDef *hi2c, IMU_int16 offset, IMU_float *gyro_dps)
{
    uint8_t buf[6];
    IMU_int16 gyro_raw;
    HAL_I2C_Mem_Read(hi2c,
                     MPU6050_ADDR,
                     GYRO_XOUT_H,
                     1,
                     buf,
                     6,
                     HAL_MAX_DELAY);

    // Read raw
    gyro_raw.x = (int16_t)(buf[0] << 8 | buf[1]);
    gyro_raw.y = (int16_t)(buf[2] << 8 | buf[3]);
    gyro_raw.z = (int16_t)(buf[4] << 8 | buf[5]);

    // Remove bias
    gyro_raw.x -= offset.x;
    gyro_raw.y -= offset.y;
    gyro_raw.z -= offset.z;

    // Convert to float (±250 dps)
    gyro_dps->x = gyro_raw.x / 131.0f;
    gyro_dps->y = gyro_raw.y / 131.0f;
    gyro_dps->z = gyro_raw.z / 131.0f;
}

/* Read 3 axys Acceleration */
void MPU6050_Read_Accel(I2C_HandleTypeDef *hi2c, IMU_float *Acc)
{
    uint8_t buf[6];
    IMU_int16 Acc_raw;

    // Reads the acc. data in the MPU6050 register
    HAL_I2C_Mem_Read(hi2c,
                     MPU6050_ADDR,
                     0x3B,
                     1,
                     buf,
                     6,
                     HAL_MAX_DELAY);

    // Saves the raw data
    Acc_raw.x = (int16_t)(buf[0] << 8 | buf[1]);
    Acc_raw.y = (int16_t)(buf[2] << 8 | buf[3]);
    Acc_raw.z = (int16_t)(buf[4] << 8 | buf[5]);

    //
	Acc->x 	= (float)Acc_raw.x / 16384.0f;
	Acc->y	= (float)Acc_raw.y / 16384.0f;
    Acc->z 	= (float)Acc_raw.z / 16384.0f;
}
