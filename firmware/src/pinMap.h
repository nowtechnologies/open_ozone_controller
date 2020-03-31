#ifndef _CONTROLLER_PINMAP_HEADER_
#define _CONTROLLER_PINMAP_HEADER_

// pinmap
#define fanEnablePin  0
#define safeSignPin   1 // also lock disable
#define chipSelect1   2
#define chipSelect2   3
#define lcdData4Pin   4
#define lcdData5Pin   5
#define lcdData6Pin   6
#define lcdData7Pin   7
#define lcdResetPin   8
#define lcdEnablePin  9
#define lcdBrightPin  10
//SPI: 11 - 12 - 13
#define buttonsPin    A0
#define analogInput1  A1
#define analogInput2  A2
#define generatorPin  A3
#define decomposerPin A4
#define humidifierPin A5

#endif
