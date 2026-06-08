#include "BNO055.h"
// #########################################################  INIT ######################################################### //
/* Sets BNO055 in NDOF MODE */
HAL_StatusTypeDef BNO055_Init(I2C_HandleTypeDef *hi2c)
{
	//
	BNO055_I2C_Reset(hi2c);

	HAL_StatusTypeDef Status1, Status2, Status3;
	/* RESET */
	 uint8_t rst = 0x20;
	 Status1 = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, SYS_TRIGGER_ADDR, I2C_MEMADD_SIZE_8BIT, &rst, 1, 100);
	 HAL_Delay(700);

	 /* SET TO CONFIG MODE */
	 uint8_t cfg = 0x00;
	 Status2 = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, OPR_MODE_ADDR, I2C_MEMADD_SIZE_8BIT, &cfg, 1, 100);
	 HAL_Delay(25);

	 /* SET NDOF (ACC + GYRO + MAG)*/
	 uint8_t ndof = 0x0C;
	 Status3 = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, OPR_MODE_ADDR, I2C_MEMADD_SIZE_8BIT, &ndof, 1, 100);
	 HAL_Delay(25);

	 if(Status1 == HAL_OK && Status2 == HAL_OK && Status3 == HAL_OK) { return HAL_OK;}
	 else{return HAL_ERROR;}
}

// #########################################################  STORES RAW DATA + FLOAT ATT# ######################################################### //
/* Reads Euler, Acc and Gyro, and stores them: IMU for Telemetry, Att for Control */
HAL_StatusTypeDef BNO055_ReadIMU(I2C_HandleTypeDef *hi2c, float* Att, uint8_t* IMU_Data)
{
	// Variables
	uint8_t Buff[IMU_BUFFER_LEN];				// Buffer to store the data
	int16_t temp;

	// Reads Acc, Gyro and Euler angles
	HAL_StatusTypeDef ReadStatus = HAL_I2C_Mem_Read(hi2c, BNO055_ADDR, ACCX_LSB_ADDR, I2C_MEMADD_SIZE_8BIT, Buff, IMU_BUFFER_LEN, MAX_TIMEOUT_MS);
	if(ReadStatus != HAL_OK) return ReadStatus;

	/* ======================================= READS ATTITUDE DATA ====================================== */
	// Row
    temp = ( (int16_t)Buff[21] << 8 ) | Buff[20];    				// Unites LSB and MSB
    Att[0] = (float)temp*INT_TO_EULER;                    			// 16bit int to float

    // Pitch
    temp = ( (int16_t)Buff[23] << 8 ) | Buff[22];    				// Unites LSB and MSB
    Att[1] = (float)temp*INT_TO_EULER;                    			// 16bit int to float

    // Yaw
    temp = ( (int16_t)Buff[19] << 8 ) | Buff[18];    				// Unites LSB and MSB
    Att[2] = (float)temp*INT_TO_EULER;                    			// 16bit int to float

	/* ======================================= STORES THE ACC & GYRO ================================== */
	int j=0;
	for(int i=0; i  <  6; i++) { IMU_Data[j++] = Buff[i];}			// [0 - 5]   = Acc, [6 - 11] Mag (Not Logged)
	for(int i=12; i < 18; i++) { IMU_Data[j++] = Buff[i]; }			// [12 - 17] =Gyro, [18 - 23] Heading

	/* ======================================= STORES EULER ANGLES ================================== */
	// Heading (Places it in Row, Pitch and Yaw Order to match telemetry)
	// Row
	IMU_Data[j++] = Buff[20];
	IMU_Data[j++] = Buff[21];

	// Pitch
	IMU_Data[j++] = Buff[22];
	IMU_Data[j++] = Buff[23];

	// Yaw
	IMU_Data[j++] = Buff[18];
	IMU_Data[j]   = Buff[19];

	return HAL_OK;
}

/* Trigger DMA Read of Euler, Acc and Gyro */
HAL_StatusTypeDef BNO055_StartRead_DMA(I2C_HandleTypeDef *hi2c, uint8_t* IMU_Buffer)
{
	// Reads Acc, Gyro and Euler angles
	return HAL_I2C_Mem_Read_DMA(hi2c, BNO055_ADDR, ACCX_LSB_ADDR, I2C_MEMADD_SIZE_8BIT, IMU_Buffer, IMU_BUFFER_LEN);
}

/* Stores Euler, Acc and Gyro when DMA is done: Att for Control, IMU for Telemetry */
HAL_StatusTypeDef BNO055_FinishRead_DMA(I2C_HandleTypeDef *hi2c, uint8_t* IMU_Buffer, float* Att, uint8_t* IMU_Data)
{
	// Variables
	int16_t temp;

	/* ======================================= READS ATTITUDE DATA ====================================== */
	// Row
    temp = ( (int16_t)IMU_Buffer[21] << 8 ) | IMU_Buffer[20];    			// Unites LSB and MSB
    Att[0] = (float)temp*INT_TO_EULER;                    					// 16bit int to float

    // Pitch
    temp = ( (int16_t)IMU_Buffer[23] << 8 ) | IMU_Buffer[22];    			// Unites LSB and MSB
    Att[1] = (float)temp*INT_TO_EULER;                    					// 16bit int to float

    // Yaw
    temp = ( (int16_t)IMU_Buffer[19] << 8 ) | IMU_Buffer[18];  				// Unites LSB and MSB
    Att[2] = (float)temp*INT_TO_EULER;                    					// 16bit int to float

	/* ======================================= STORES THE ACC & GYRO ================================== */
	int j=0;
	for(int i=0; i  <  6; i++) { IMU_Data[j++] = IMU_Buffer[i];}			// [0 - 5]   = Acc, [6 - 11] Mag (Not Logged)
	for(int i=12; i < 18; i++) { IMU_Data[j++] = IMU_Buffer[i]; }			// [12 - 17] =Gyro, [18 - 23] Heading

	/* ======================================= STORES EULER ANGLES ================================== */
	// Heading (Places it in Row, Pitch and Yaw Order to match telemetry)
	// Row
	IMU_Data[j++] = IMU_Buffer[20];
	IMU_Data[j++] = IMU_Buffer[21];

	// Pitch
	IMU_Data[j++] = IMU_Buffer[22];
	IMU_Data[j++] = IMU_Buffer[23];

	// Yaw
	IMU_Data[j++] = IMU_Buffer[18];
	IMU_Data[j]   = IMU_Buffer[19];

	return HAL_OK;
}





// ###########################################################  STORES RAW DATA ######################################################### //
/* Reads Euler, Acc and Gyro, and stores them [JUST FOR LOGGING DATA] */
void BNO055_ReadIMU_Raw(I2C_HandleTypeDef *hi2c, uint8_t* IMU_Data)
{
	// Variables
	uint8_t Buff[IMU_BUFFER_LEN];				// Buffer to store the data

	// Reads
	HAL_I2C_Mem_Read(hi2c, BNO055_ADDR, ACCX_LSB_ADDR, I2C_MEMADD_SIZE_8BIT, Buff, IMU_BUFFER_LEN, 10);

	/* =========================== Stores the Buffer data =========================== */
	int j=0;
	for(int i=0; i  <  6; i++) { IMU_Data[j++] = Buff[i];}			// [0 - 5]   = Acc, [6 - 11] Mag (Not Logged)
	for(int i=12; i < 18; i++) { IMU_Data[j++] = Buff[i]; }			// [12 - 17] =Gyro, [18 - 23] Heading

	// Heading (Places it in Row, Pitch and Yaw Order to match telemetry)
	// Row
	IMU_Data[j++] = Buff[20];
	IMU_Data[j++] = Buff[21];

	// Pitch
	IMU_Data[j++] = Buff[22];
	IMU_Data[j++] = Buff[23];

	// Yaw
	IMU_Data[j++] = Buff[18];
	IMU_Data[j]   = Buff[19];

}

// ###########################################################  STORES EULER ANGLES ######################################################### //
/* Reads Euler angles */
void BNO055_ReadEuler(I2C_HandleTypeDef *hi2c, float* Att)
{
	// Variables
	uint8_t Buff[EULER_TOTAL_BYTES];				// Buffer to store the data
	int16_t temp;

	// Read Data from Sensor
	HAL_I2C_Mem_Read(hi2c, BNO055_ADDR, EULER_LSB_ADDR, I2C_MEMADD_SIZE_8BIT, Buff, EULER_TOTAL_BYTES, 2);

	/* ======================================= READS ATTITUDE DATA ====================================== */
	// Row
    temp = ( (int16_t)Buff[3] << 8 ) | Buff[2];    			// Unites LSB and MSB
    Att[0] = (float)temp*INT_TO_EULER;                    	// 16bit int to float

    // Pitch
    temp = ( (int16_t)Buff[5] << 8 ) | Buff[4];    			// Unites LSB and MSB
    Att[1] = (float)temp*INT_TO_EULER;                    	// 16bit int to float

    // Yaw
    temp = ( (int16_t)Buff[1] << 8 ) | Buff[0];    			// Unites LSB and MSB
    Att[2] = (float)temp*INT_TO_EULER;                    	// 16bit int to float
}

// ##############################################################  DEBUG ############################################################ //
/* Checks values from the IMU PACKET*/
void BNO055_ReadIMU_DEBUG(I2C_HandleTypeDef *hi2c, float* Acc, float* Gyro, float* AttEuler)
{
	uint8_t IMU_Data[IMU_BUFFER_LEN];
	int16_t temp;
	BNO055_ReadIMU_Raw(hi2c, IMU_Data);

	/* ATTITUDE ---------------------------------------------------------------------------*/
	temp = (int16_t)( IMU_Data[12] | ((int16_t)IMU_Data[13] << 8) );             // Unites LSB and MSB
	AttEuler[0] = (float)temp*INT_TO_EULER;                                      // 16bit int to float

	temp = (int16_t)( IMU_Data[14] | ((int16_t)IMU_Data[15] << 8) );             // Unites LSB and MSB
	AttEuler[1] = (float)temp*INT_TO_EULER;                                      // 16bit int to float

	temp = (int16_t)( IMU_Data[16] | ((int16_t)IMU_Data[17] << 8) );             // Unites LSB and MSB
	AttEuler[2] = (float)temp*INT_TO_EULER;                                      // 16bit int to float

	/* ACCELERATION  ---------------------------------------------------------------------*/
	temp = (int16_t)( IMU_Data[0] | ((int16_t)IMU_Data[1] << 8) );            	 // Unites LSB and MSB
	Acc[0] = (float)temp*INT_TO_MPS2;

	temp = (int16_t)( IMU_Data[2] | ((int16_t)IMU_Data[3] << 8) );            	// Unites LSB and MSB
	Acc[1] = (float)temp*INT_TO_MPS2;                                         	//

	temp = (int16_t)( IMU_Data[4] | ((int16_t)IMU_Data[5] << 8) );           	// Unites LSB and MSB
	Acc[2] = (float)temp*INT_TO_MPS2;                                          	//

	/* GYROSCOPE  ------------------------------------------------------------------------*/
	temp = (int16_t)( IMU_Data[6] | ((int16_t)IMU_Data[7] << 8) );           	// Unites LSB and MSB
	Gyro[0] = (float)temp*INT_TO_DPS;                                          	//

	temp = (int16_t)( IMU_Data[8] | ((int16_t)IMU_Data[9] << 8) );           	// Unites LSB and MSB
	Gyro[1] = (float)temp*INT_TO_DPS;                                          	//

	temp = (int16_t)( IMU_Data[10] | ((int16_t)IMU_Data[11] << 8) );           // Unites LSB and MSB
	Gyro[2] = (float)temp*INT_TO_DPS;                                          //

}

/**/
void BNO055_I2C_Reset(I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_DeInit(hi2c);
    HAL_Delay(10);
    HAL_I2C_Init(hi2c);
    HAL_Delay(10);
}
