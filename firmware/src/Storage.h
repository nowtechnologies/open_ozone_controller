#ifndef __STORAGE_H__
#define __STORAGE_H__

#define STORAGE_REVISION				1
	/*

	Use only the first 512 bytes for compatibility with smaller AVRs.

	*/

	#include "Arduino.h"
	#include "EEPROM.h"

	  //////////////////////////////////////////////////////////////////////////////////////
	 //					  			EEPROM ADDRESS TABLE								 //
	//////////////////////////////////////////////////////////////////////////////////////

	#define ROM_BRIGHT		32

	// lib 
	#define ROM_REV1 			62
	#define ROM_REV2 			63
	#define ROM_INIT 			64

	class Storage {

	public:

		void initialize();
		void reset();

		// save
		void storeBrightness(uint8_t thisValue);

		// load
		uint8_t brightness();

	private:

		void storeDefaults();
		bool compareBytes(uint8_t thisbyte, uint16_t onaddress);
		bool compareInts(int thisInt, uint16_t onaddress);
		void writeInt(int thisInt, uint16_t startAddress);
		int  readInt(uint16_t startAddress);
		void writeByte(uint8_t thisByte, uint16_t startAddress);
		uint8_t readByte(uint16_t onAddress);

	};

#endif
