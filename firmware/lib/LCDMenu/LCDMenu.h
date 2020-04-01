#ifndef LCDMenu_h
#define LCDMenu_h
#include <LiquidCrystal.h>
#include "LCDMenuItem.h"

class LCDMenu{
  protected:
    String Name;
	LCDMenuItem* menuFirst;
	LCDMenuItem* menuLast;
    void setName (String);
	LiquidCrystal* LCD;
	LCDMenu* parent;
  public: 
    LCDMenu(String newName, LiquidCrystal* newLCD, LCDMenu* parentMenu = NULL);
	LCDMenuItem* next();
	LCDMenuItem* prev();
	void addMenuItem (LCDMenuItem *);
	LCDMenuItem* menuCurrent;
	void setLCD(LiquidCrystal*);
	LiquidCrystal* getLCD();
	void selectOption();
	void display();
	bool hasParentMenu();
	LCDMenu* getParentMenu();
}; 

#endif