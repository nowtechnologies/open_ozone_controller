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

	void Storage::storeKillLevel(uint8_t thisByte){
		Storage::writeByte(thisByte, ROM_OZONE);
	};

	void Storage::storeDeconTime(uint8_t thisByte){
		Storage::writeByte(thisByte, ROM_TIME);
	};

	void Storage::storeControlThreshold(uint8_t thisByte){
		Storage::writeByte(thisByte, ROM_THRESH);
	};

	void Storage::storeRestTime(uint8_t thisByte){
		Storage::writeByte(thisByte, ROM_REST);
	};

	void Storage::storeLockInstalled(bool state){
		Storage::writeByte(state?1:0, ROM_LOCK);
	};

	void Storage::storeLogState(bool state){
		Storage::writeByte(state?1:0, ROM_ECHO);
	};

	void Storage::storeChamberVolume(int thisValue){
		Storage::writeInt(thisValue, ROM_CHAMVOL);
	};

	void Storage::storeGeneratorCapacity(int thisValue){
		Storage::writeInt(thisValue, ROM_GENCAP);
	};

	/// LOAD

	uint8_t Storage::brightness(){
		uint8_t value = Storage::readByte(ROM_BRIGHT);
		return value;
	};

	uint8_t Storage::killLevel(){
		uint8_t value = Storage::readByte(ROM_OZONE);
		return value;
	};

	uint8_t Storage::deconTime(){
		uint8_t value = Storage::readByte(ROM_TIME);
		return value;
	};

	uint8_t Storage::controlThreshold(){
		uint8_t value = Storage::readByte(ROM_THRESH);
		return value;
	};

	uint8_t Storage::restTime(){
		uint8_t value = Storage::readByte(ROM_REST);
		return value;
	};

	bool Storage::lockInstalled(){
		uint8_t value = Storage::readByte(ROM_LOCK);
		return bool(value);
	};

	bool Storage::serialLogEnabled(){
		uint8_t value = Storage::readByte(ROM_ECHO);
		return bool(value);
	};

	int Storage::chamberVolume(){
		uint16_t value = Storage::readInt(ROM_CHAMVOL);
		return value;
	};

	int Storage::generatorCapacity(){
		uint16_t value = Storage::readInt(ROM_GENCAP);
		return value;
	};

	//////////////////////////////////////////
	//					  	 INITIALIZE						 //
	////////////////////////////////////////

	void Storage::storeDefaults(){
		Storage::storeBrightness(255); // pwm
		Storage::storeDeconTime(15); // min
		Storage::storeKillLevel(25); // ppm
		Storage::storeControlThreshold(5); // ppm
		Storage::storeRestTime(15); // sec
		Storage::storeLogState(true);
		Storage::storeLockInstalled(false);
		Storage::storeChamberVolume(100); // liter
		Storage::storeGeneratorCapacity(5000); // mg/h
		Storage::writeByte(STORAGE_REVISION, ROM_REV1);
		Storage::writeByte(STORAGE_REVISION, ROM_REV2);
	};

	void Storage::begin(){
		uint8_t valid = STORAGE_REVISION * 2;
		uint8_t check = Storage::readByte(ROM_REV1) + Storage::readByte(ROM_REV2);
		if ( valid != check ) {
			Storage::storeDefaults();
		}
	};

	void Storage::reset(){
		Storage::storeDefaults();
	};
