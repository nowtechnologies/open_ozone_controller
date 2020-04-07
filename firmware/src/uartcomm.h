#define UART_LI_F 0x55
#define UART_LI_L 0xAA
#define UART_BUFFER_SIZE 128

#include "ringbuffer.h"
#include "packets.h"

RingBuffer serialBuffer(UART_BUFFER_SIZE);
UARTHEADER packetHeader;
SENSORPACK sensorPacket;

void process(const UARTHEADER &header, RingBuffer &buffer) {

  if(header.packetID == PID_SENSOR) {
    if(buffer.capacity() >= sizeof(SENSORPACK)) {
      buffer.get(0, (uint8_t*)&sensorPacket, sizeof(SENSORPACK));
    }
  }
}

void append(uint8_t b) {
	uint16_t datacrc;
	uint16_t checksum;

	if(serialBuffer.push(b)) {
		size_t required = sizeof(UARTHEADER) + packetHeader.packetLength;

		while (serialBuffer.capacity() >= required) {
			// header bytes available
			serialBuffer.get(0, (uint8_t*)&packetHeader, sizeof(UARTHEADER));

			if(packetHeader.firstLeadIn == UART_LI_F && packetHeader.lastLeadIn == UART_LI_L) {
				uint8_t crc = crc8(&packetHeader, 0, sizeof(UARTHEADER) - 1);
				if(packetHeader.headerCRC == crc) {
					if(serialBuffer.capacity() >= sizeof(UARTHEADER) + packetHeader.packetLength) {
							// data bytes available
							serialBuffer.pop(sizeof(UARTHEADER));

							serialBuffer.get(packetHeader.packetLength - 2, (uint8_t*)&datacrc, sizeof(uint16_t));
							checksum = serialBuffer.crc16(0, packetHeader.packetLength - 2);
							if(datacrc == checksum) {
								process(packetHeader, serialBuffer); // [1716 byte]
							} else {
								// data crc error - read next packet
								// ErrorDetails e;
								// e.words[1] = checksum;
								// e.words[0] = datacrc;
							}

							serialBuffer.pop(packetHeader.packetLength);
							packetHeader.packetLength = 0;
					} else {
						// not enough bytes available (continue read)
						break;
					} // if enough bytes
				} else {
					// error - invalid crc
					packetHeader.packetLength = 0;
					serialBuffer.pop();
				} // if crc
			} else {
				// invalid lead in (continue read)
				packetHeader.packetLength = 0;
				serialBuffer.pop();
			} // if lead in
		} // while
	} else {
		// error - buffer overflow
		serialBuffer.clear();
	} // push
}
