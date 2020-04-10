#ifndef __COMMON_PACKETS_H__
#define __COMMON_PACKETS_H__

#define PROTOCOL_REVISION  100

// UART HEADER
#define UART_LI_F 0x55
#define UART_LI_L 0xAA

// PACKET IDENTIFIERS
#define PID_ERROR			 0
#define PID_SENSOR		 1
#define PID_LOG				 2

#if PRAGMA_PACK_AVAILABLE
#define __PACKED
#pragma pack(push, 1)
#else
#define __PACKED __attribute__((packed))
#endif

typedef struct {
	uint8_t  firstLeadIn;
	uint8_t  lastLeadIn;
	uint8_t  packetLength;
	uint8_t  packetID;
	uint8_t  headerCRC;
} __PACKED UARTHEADER;

typedef struct {
	float ozonePPM;
	float temperature;
	float humidity;
	float ratio;
} __PACKED SENSORPACK;

typedef struct {
	union {
		struct {
			bool generator :1;
			bool blower :1;
			bool decomposer :1;
			bool humidifier :1;
			bool lock :1;
			bool deb_0 :1;
			bool deb_1 :1;
			bool deb_2 :1;
		} bit;
		uint8_t	value;
	} state;
} __PACKED GPIOS;

typedef struct {
	SENSORPACK sensor;
	uint8_t 	 status;
} __PACKED LOG;

#if PRAGMA_PACK_AVAILABLE
#pragma pack(pop)
#endif

#endif
