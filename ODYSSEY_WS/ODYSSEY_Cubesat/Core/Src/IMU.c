//#include "IMU.h"
//// Registers:

/////*============================================== MAG =============================================*/
///* Init Magnetometer */
//void HMC5883L_Init(I2C_HandleTypeDef *hi2c)
//{
//    uint8_t data;
//
//    // Config A: 8-average, 15 Hz, normal measurement
//    data = 0x70;  // 0111 0000
//    HAL_I2C_Mem_Write(hi2c, HMC5883L_ADDR, 0x00, 1, &data, 1, HAL_MAX_DELAY);
//
//    // Config B: Gain = ±1.3 Ga
//    data = 0x20;  // 0010 0000
//    HAL_I2C_Mem_Write(hi2c, HMC5883L_ADDR, 0x01, 1, &data, 1, HAL_MAX_DELAY);
//
//    // Mode: Continuous measurement
//    data = 0x00;
//    HAL_I2C_Mem_Write(hi2c, HMC5883L_ADDR, 0x02, 1, &data, 1, HAL_MAX_DELAY);
//
//}
//
///**/
////void HMC5883L_Read(I2C_HandleTypeDef *hi2c, IMU_int16* Mag_raw)
////{
////    uint8_t buf[6];
////
////    //
////    HAL_I2C_Mem_Read(hi2c,
////                     HMC5883L_ADDR,
////                     0x03,
////                     1,
////                     buf,
////                     6,
////                     HAL_MAX_DELAY);
////
////    //
////    Mag_raw->x = (int16_t)(buf[0] << 8 | buf[1]);
////    Mag_raw->y = (int16_t)(buf[2] << 8 | buf[3]);
////    Mag_raw->z = (int16_t)(buf[4] << 8 | buf[5]);
////
////    //
////    Mag_g->x = Mag_raw->x / 10.90f;
////    Mag_g->y = Mag_raw->y / 10.9f;
////    Mag_g->z = Mag_raw->z / 10.90f;
////}
////
////
////void HMC5883L_Calibrate(I2C_HandleTypeDef *hi2c, IMU_int16 *offset)
////{
////    IMU_int16 mag;
////
////    int16_t min_x = 32767, max_x = -32768;
////    int16_t min_y = 32767, max_y = -32768;
////    int16_t min_z = 32767, max_z = -32768;
////
////    // ================================== HARD IRON CALIBRATION ================================== //
////    // Update Max / Min values
////    for(int i = 0; i < 2000; i++)
////    {
////        HMC5883L_Read(hi2c, &mag);
////
////        if(mag.x < min_x) {min_x = mag.x;}
////        if(mag.x > max_x) {max_x = mag.x;}
////
////        if(mag.y < min_y) {min_y = mag.y;}
////        if(mag.y > max_y) {max_y = mag.y;}
////
////        if(mag.z < min_z) {min_z = mag.z;}
////        if(mag.z > max_z) {max_z = mag.z;}
////
////        HAL_Delay(5);
////    }
////
////    // Offset is the distance from the 0,
////    offset->x = (max_x + min_x) / 2;
////    offset->y = (max_y + min_y) / 2;
////    offset->z = (max_z + min_z) / 2;
////
////    // ================================== SOFT IRON CALIBRATION ================================== //
////    float scale_x = (max_x - min_x) / 2.0f;
////    float scale_y = (max_y - min_y) / 2.0f;
////    float scale_z = (max_z - min_z) / 2.0f;
////
////    float avg = (scale_x + scale_y + scale_z) / 3.0f;
////
////    float correction_x = avg / scale_x;
////    float correction_y = avg / scale_y;
////    float correction_z = avg / scale_z;
////
////}
////
////void HMC5883L_Read(I2C_HandleTypeDef *hi2c, IMU_int16* Mag_raw, IMU_int16* Mag_g)
////{
////    uint8_t buf[6];
////
////    //
////    HAL_I2C_Mem_Read(hi2c,
////                     HMC5883L_ADDR,
////                     0x03,
////                     1,
////                     buf,
////                     6,
////                     HAL_MAX_DELAY);
////
////    //
////    Mag_raw->x = (int16_t)(buf[0] << 8 | buf[1]);
////    Mag_raw->y = (int16_t)(buf[2] << 8 | buf[3]);
////    Mag_raw->z = (int16_t)(buf[4] << 8 | buf[5]);
////
////    //
////    Mag_g->x = Mag_raw->x / 10.90f;
////    Mag_g->y = Mag_raw->y / 10.9f;
////    Mag_g->z = Mag_raw->z / 10.90f;
////}
//
//
//
//
///* Turn from Quaternion to an Euler angle */
////void Quat_to_Euler(float* Att_Quat, float* Att_Euler)
////{
////
////	Euler[0] = 1 ;
////	Euler[1] = 1 ;
////	Euler[2] = 1 ;
////}
//
//
//
/////*============================================== IMU =============================================*/
//// IMU
///* Initializes the MPU6050 and GY-271 */
////void IMU_Init(I2C_HandleTypeDef *hi2c)
////{
////	MPU6050_Init(hi2c);
////	HMC5883L_Init(hi2c);
////
////}
////
////void IMU_Calibrate(I2C_HandleTypeDef *hi2c)
////{
////	MPU6050_Gyro_Calibrate(hi2c);
////	HMC5883L_Calibrate(hi2c);
////}
//
//
/////* Reads 3 Axys Orientation*/
////void IMU_Quat(I2C_HandleTypeDef *hi2c, MPU_Data* MPUData)
////{
////
////	// Acc
////
////	// Gyro
////	MPU6050_Read_Gyro(hi2c, gyro , offset);
////
////	// Fusion
////
////	// Att
////}
////
/////* Reads 3 Axys Orientation*/
////void IMU_Euler(I2C_HandleTypeDef *hi2c, MPU_Data* MPUData)
////{
////
////	// Acc
////
////	// Gyro
////	MPU6050_Read_Gyro(hi2c, gyro , offset);
////
////	// Fusion
////
////	// Att
////}
//
//
