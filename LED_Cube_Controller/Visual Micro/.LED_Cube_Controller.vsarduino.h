//Board = Arduino Mega (ATmega1280)
#define ARDUINO 104
#define __AVR_ATmega1280__
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
#define __attribute__(x)
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__
#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define prog_void
#define PGM_VOID_P int
#define NOINLINE __attribute__((noinline))

typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {}

//already defined in arduno.h
void ConfigTimer();
//already defined in arduno.h
void GetSerialData();
void ChangeEffect();
void SelectEffect();
void UpdateCube();
void DisplayLayer(int Layer);
void SetupIO();
String ReadSerialData(int count);
int StringToInt(String temp);
void CheckButtons();

#include "E:\Program Files\Arduino\arduino-1.0.4\hardware\arduino\variants\mega\pins_arduino.h" 
#include "E:\Program Files\Arduino\arduino-1.0.4\hardware\arduino\cores\arduino\arduino.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\LED_Cube_Controller.ino"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\CharMatrix.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Char_Display.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Char_Display.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Cube8x8x8.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Cube8x8x8.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\EffectClass.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\EffectClass.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\FireWork.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\FireWork.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Maize.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Maize.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Pin_Defines.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Rain.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Rain.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\RandomFill.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\RandomFill.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\ScrollingCharDisplay.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\ScrollingCharDisplay.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Snake.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Snake.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\ToggleRandom.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\ToggleRandom.h"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Voxel.cpp"
#include "D:\Users\Nathan\Projects\LED Cube\LED_Cube_Controller\Voxel.h"
