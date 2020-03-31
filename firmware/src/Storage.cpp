	#include "Storage.h"

	///////////////////////////////////////
	//					  	  PRIVATE						 //
	///////////////////////////////////////

	bool Storage::compareBytes(uint8_t thisbyte, uint16_t onaddress){
		bool answer = false;
		uint8_t storedValue = EEPROM.read(onaddress);
		if (thisbyte == storedValue) answer = true;
		return answer;
	};

	bool Storage::compareInts(int thisInt, uint16_t onaddress){
		bool answer = false;
		uint8_t high = EEPROM.read(onaddress);
		uint8_t low  = EEPROM.read(onaddress + 1);
		int storedValue = word(high, low);
		if (thisInt == storedValue) answer = true;
		return answer;
	};

	void Storage::writeInt(int thisInt, uint16_t startAddress){
		if ( !Storage::compareInts(thisInt, startAddress) ) {
			EEPROM.write(startAddress, highByte(thisInt));
			EEPROM.write(startAddress + 1, lowByte(thisInt));
		}
	};

	int Storage::readInt(uint16_t startAddress){
		uint8_t high = EEPROM.read(startAddress);
		uint8_t low  = EEPROM.read(startAddress + 1);
		int storedValue = word(high, low);
		return storedValue;
	};

	void Storage::writeByte(uint8_t thisByte, uint16_t startAddress){
		if ( !Storage::compareBytes(thisByte, startAddress) ) EEPROM.write(startAddress, thisByte);
	};

	uint8_t Storage::readByte(uint16_t onAddress){
		uint8_t storedValue = EEPROM.read(onAddress);
		return storedValue;
	};

	///////////////////////////////////////
	//					  	  PUBLIC						 //
	///////////////////////////////////////

	/// SAVE

	void Storage::storeBrightness(uint8_t thisByte){
		Storage::writeByte(thisByte, ROM_BRIGHT);
	};

	/// LOAD

	uint8_t Storage::brightness(){
		uint8_t value = Storage::readByte(ROM_BRIGHT);
		return value;
	};

	//////////////////////////////////////////
	//					  	 INITIALIZE						 //
	////////////////////////////////////////

	void Storage::storeDefaults(){
		Storage::storeBrightness(255);
	};

	void Storage::initialize(){
		uint8_t valid = STORAGE_REVISION * 2;
		uint8_t check = Storage::readByte(ROM_REV1) + Storage::readByte(ROM_REV2);
		if ( valid != check ) {
			Storage::storeDefaults();
		}
	};

	void Storage::reset(){
		Storage::storeDefaults();
	};
