#define __AVR_ATmega1280__
#define __cplusplus
#define __builtin_va_list int
#define __attribute__(x)
#define __inline__
#define __asm__(x)
#define ARDUINO 100
extern "C" void __cxa_pure_virtual() {}
void setup();
void ConfigTimer();
void loop();
void GetSerialData();
void ChangeEffect();
void SelectEffect();
void UpdateCube();
void DisplayLayer(int Layer);
void SetupIO();
String ReadData(int count);
int StringToInt(String temp);
void CheckButtons();

#include "E:\Program Files\arduino-1.0\hardware\arduino\variants\mega\pins_arduino.h" 
#include "E:\Program Files\arduino-1.0\hardware\arduino\cores\arduino\Arduino.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller V2\LED_Cube_Controller.ino" 
