#ifndef __STORAGE_H__
#define __STORAGE_H__

#define STORAGE_REVISION 4
	/*

	Use only the first 512 bytes for compatibility with smaller AVRs.

	*/

	#include "Arduino.h"
	#include "EEPROM.h"

	  //////////////////////////////////////////////////////////////////////////////////////
	 //					  			EEPROM ADDRESS TABLE								 //
	//////////////////////////////////////////////////////////////////////////////////////

	#define ROM_BRIGHT		32
	#define ROM_OZONE			33
	#define ROM_TIME			34
	#define ROM_LOCK			35
	#define ROM_THRESH		36

	// lib
	#define ROM_REV1 			62
	#define ROM_REV2 			63
	#define ROM_INIT 			64

	class Storage {

	public:

		void begin();
		void reset();

		// save
		void storeBrightness(uint8_t thisValue);
		void storeKillLevel(uint8_t thisValue);
		void storeDeconTime (uint8_t thisValue);
		void storeControlThreshold(uint8_t thisValue);
		void storeLockInstalled(bool thisBool);

		// load
		uint8_t brightness();
		uint8_t killLevel();
		uint8_t deconTime();
		uint8_t	controlThreshold();
		bool		lockInstalled();

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
