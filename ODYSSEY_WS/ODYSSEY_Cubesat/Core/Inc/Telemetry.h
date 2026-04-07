 #ifndef TELEMETRY_H_
 #define TELEMETRY_H_
/* #################################### CUBESAT TELEMETRY  ######################################### */

// Includes
#include "stdint.h"
#include "CRC.h"

// * ========================================== DEFINES ======================================== //
// Sync Bytes
#define START_BYTE1						0xAA				// SYNC Byte 1
#define START_BYTE2						0x55				// SYNC Byte 2

// ID [If more Cubesats are used]
#define ODYSSEY_ID          			0x1					// Cubesat ID 1
#define CUBESAT_ID						0x2					// Cubesat ID 2

// Headers [Indicate Type of message]
#define HEADER_TELEMETRY_PACKET         0x1					//
#define HEADER_HOUSE_KEEPING_PACKET     0x2					//
#define HEADER_COMMAND_PACKET           0x3					//

// Size of each Message in Bytes
#define TELEMETRY_PACKET_SIZE			25					// Telmetery Packet Size [+CRC, Start Byte, ...]
#define HOUSEKEEPING_PACKET_SIZE		22					// Control Packet Size [+CRC, Start Byte, ...]
#define COMMAND_PACKET_SIZE				13					// Control Packet Size [+CRC, Start Byte, ...]


// Cubesat mode
#define MODE_NORMAL            			0x0          		// System runs as normal
#define MODE_START_M1                 	0x1           		// Turn on RW 1
#define MODE_START_M2                	0x2           		// Turn on RW 2
#define MODE_START_M3                  	0x3           		// Turn on RW 3
#define MODE_MANUAL             		0x4           		// Disables the control ISR, uses the Setpoint as DutyC
#define MODE_DISABLE_MOTORS            	0x5          		// Turn off all Motors

// Convert from float to INT
#define ACC_TO_INT						1000.0				//
#define GYRO_TO_INT						10.0				//
#define ATT_TO_INT						16					//
#define INT_TO_ATT						(1/16.0f)			//
#define BATTERY_TO_INT   				(255.0/4095.0)		//
#define INT_TO_ATT2						0.01

#define LAT_TO_INT						1
#define LON_TO_INT						1
#define ALT_TO_INT						1

// * ========================================== FUNC. PROTOTYPES ======================================== //

// SEND MESSAGES
void Encode_TelemetryPacket(uint8_t* TelemetryPacket, uint8_t* IMU_Buffer, uint8_t MsgCounter);							// Encode
void Encode_HouseKeepingPacket(uint8_t* HouseKeepingPacket, float* AttSetpoint, float* GPS, float* HouseKeeping);		// Encode values into a radio MSG

// RECEIVE MESSAGES
void Decode_ControlPacket(uint8_t* ControlPacket, float* AttSetpoints);        								// Get Setpoints from msg

// DEBUG
void EncodeFakePacket(int16_t ADCData, uint8_t* DataPacket);												// [DEBUG]

#endif
