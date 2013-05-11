/// LED CUBE
#include <Arduino.h>
#include <avr/interrupt.h>

#include "Pin_Defines.h"
#include "Cube8x8x8.h"
#include "EffectClass.h"

// Included Effects
#include "Snake.h"
#include "Maize.h"
#include "ToggleRandom.h"
#include "RandomFill.h"
#include "Rain.h"
#include "Char_Display.h"
#include "ScrollingCharDisplay.h"
#include "FireWork.h"


Cube8x8x8 *Cube;

EffectClass *effect;
int NextEffect;
int NumberEffects = 11;

int CurLayer = 0;
int CurCollum = 0;

String SerialCommand;
int SerialValue;

//timer value;
long tcnt2;

// Button variables
long Debounce = 500;
int PinValue;

int Prev_NEB = Button_Off;
long Time_NEB = 0;

int Prev_S = Button_Off;
long Time_S = 0;

long ShuffleDelay = 30000;
long ShuffleStart = 0;
int EnableShuffle = 0;


void setup()
{
  Serial.begin(19200);
  SetupIO();
  randomSeed(analogRead(0));
  delay(random()%10);
  Cube = new Cube8x8x8();
  
  // start interrupt timer for cube update
  ConfigTimer();
  Cube->CreateCubeOff();


  NextEffect = random()%100;
  NextEffect = NextEffect%NumberEffects;
  SelectEffect();
}


void ConfigTimer()
{
	// configure timer for 1ms update interval;
	/* First disable the timer overflow interrupt while we're configuring */  
	TIMSK2 &= ~(1<<TOIE2);  
 // 
	/* Configure timer2 in normal mode (pure counting, no PWM etc.) */  
	TCCR2A &= ~((1<<WGM21) | (1<<WGM20));  
	TCCR2B &= ~(1<<WGM22);  
 // /* Select clock source: internal I/O clock */  
	ASSR &= ~(1<<AS2);  
 // 
	/* Disable Compare Match A interrupt enable (only want overflow) */  
	TIMSK2 &= ~(1<<OCIE2A);  
  
	/* Now configure the prescaler to CPU clock divided by 128 */  
	TCCR2B |= (1<<CS22)  | (1<<CS20); // Set bits  
	TCCR2B &= ~(1<<CS21);             // Clear bit  
  
	/* We need to calculate a proper value to load the timer counter. 
	* The following loads the value 131 into the Timer 2 counter register 
	* The math behind this is: 
	* (CPU frequency) / (prescaler value) = 125000 Hz = 8us. 
	* (desired period) / 8us = 125. 
	* MAX(uint8) + 1 - 125 = 131; 
	*/  
	/* Save value globally for later reload in ISR */
	tcnt2 = 131;
  
	/* Finally load end enable the timer */  
	TCNT2 = tcnt2 + 200;  
	TIMSK2 |= (1<<TOIE2);  

	delay(1000);
}


ISR(TIMER2_OVF_vect) {  
  /* Reload the timer */
  TCNT2 = tcnt2;  
  UpdateCube();
}

void loop()
{
	GetSerialData();
	CheckButtons();
	
	
	if(EnableShuffle == 1)
	{
		if(millis() > ShuffleStart + ShuffleDelay)
		{			
			ChangeEffect();
			ShuffleStart = millis();
		}
	}
	

	effect->Update();
}


void GetSerialData()
{
  // get serial Data
  if(Serial.available() >= 4) // read in "x y z s" where s is state;
  {
	  SerialCommand = ReadSerialData(4);
	  SerialCommand.toLowerCase();
	  if(SerialCommand == "next") ChangeEffect();
	  else if(SerialCommand == "rand")
	  {
		  NextEffect = random()%100;
		  NextEffect = NextEffect%7;
		  ChangeEffect();
	  }
	  else if(SerialCommand == "selc")
	  {
		  NextEffect = StringToInt(ReadSerialData(2));
		  ChangeEffect();
	  }
  }
}

void ChangeEffect()
{
	if(EnableShuffle == 1)
	{		
		NextEffect = random()%100;
		NextEffect = NextEffect%NumberEffects;
	}

	effect->End();
	delete effect;
	SelectEffect();
}

void SelectEffect()
{
		
		if(NextEffect == 0)	effect = new Rain(Cube,100, Z_Axis, -1);
		else if(NextEffect == 1)	effect = new RandomFill(Cube,50,On);
		else if(NextEffect == 2)	effect = new RandomFill(Cube,50,Off);
		else if(NextEffect == 3)	effect = new Maize(Cube,50);
		else if(NextEffect == 4)	effect = new ToggleRandom(Cube, 10);
		else if(NextEffect == 5)	effect = new Snake(Cube, 50, 40);
		else if(NextEffect == 6)    effect = new Char_Display(Cube, 75, 2, "ECE Department");
		else if(NextEffect == 7)	effect = new ScrollingCharDisplay(Cube, 100, "KSU EClub 2013");
		else if(NextEffect == 8)	effect = new ScrollingCharDisplay(Cube, 100, "Best Display Ever!!!");
		else if(NextEffect == 9)	effect = new FireWork(Cube, 150);
		else
		{
				effect = new Rain(Cube,100, Z_Axis, 1);
				NextEffect = -1;
		}
		
		delay(1000); // delay 1 second before starting effects
		effect->Begin();
		NextEffect ++;
}




void UpdateCube()
{
	DisplayLayer(CurLayer);
	CurLayer++; // increment the layer Circuraly
	if(CurLayer == 8) CurLayer = 0;
}

void DisplayLayer(int Layer)
{
  // Disable Layers
  switch(Layer)
  {
	case 0:
	  digitalWrite(Layer7,LOW);
	  break;
	case 1:
	  digitalWrite(Layer0,LOW);
	  break;
	case 2:
	  digitalWrite(Layer1,LOW);      
	  break;
	case 3:
	  digitalWrite(Layer2,LOW);      
	  break;
	case 4:
	  digitalWrite(Layer3,LOW);      
	  break;
	case 5:
	  digitalWrite(Layer4,LOW);      
	  break;
	case 6:
	  digitalWrite(Layer5,LOW);      
	  break;
	case 7:
	  digitalWrite(Layer6,LOW);      
	  break;
  }
  //shift values over
  for(CurCollum = 7; CurCollum >= 0; CurCollum --)
  {
	digitalWrite(ClockCycle,LOW);
	//                    x  y  z
	digitalWrite(Row0,Cube->GetVoxel(0,CurCollum,Layer));
	digitalWrite(Row1,Cube->GetVoxel(1,CurCollum,Layer));
	digitalWrite(Row2,Cube->GetVoxel(2,CurCollum,Layer));
	digitalWrite(Row3,Cube->GetVoxel(3,CurCollum,Layer));
	digitalWrite(Row4,Cube->GetVoxel(4,CurCollum,Layer));
	digitalWrite(Row5,Cube->GetVoxel(5,CurCollum,Layer));
	digitalWrite(Row6,Cube->GetVoxel(6,CurCollum,Layer));
	digitalWrite(Row7,Cube->GetVoxel(7,CurCollum,Layer));
	
	digitalWrite(ClockCycle,HIGH);
  }
  
  // Reenable Layers
  switch(Layer)
  {
	case 0:
	  digitalWrite(Layer0,HIGH);
	  break;
	case 1:
	  digitalWrite(Layer1,HIGH);
	  break;
	case 2:
	  digitalWrite(Layer2,HIGH);      
	  break;
	case 3:
	  digitalWrite(Layer3,HIGH);      
	  break;
	case 4:
	  digitalWrite(Layer4,HIGH);      
	  break;
	case 5:
	  digitalWrite(Layer5,HIGH);      
	  break;
	case 6:
	  digitalWrite(Layer6,HIGH);      
	  break;
	case 7:
	  digitalWrite(Layer7,HIGH);      
	  break;
  }
}

void SetupIO()
{
  pinMode(Layer0,OUTPUT);
  digitalWrite(Layer0,LOW);

  pinMode(Layer1,OUTPUT);
  digitalWrite(Layer1,LOW);
  pinMode(Layer2,OUTPUT);
  digitalWrite(Layer2,LOW);
  pinMode(Layer3,OUTPUT);
  digitalWrite(Layer3,LOW);
  pinMode(Layer4,OUTPUT);
  digitalWrite(Layer4,LOW);
  pinMode(Layer5,OUTPUT);
  digitalWrite(Layer5,LOW);
  pinMode(Layer6,OUTPUT);
  digitalWrite(Layer6,LOW);
  pinMode(Layer7,OUTPUT);
  digitalWrite(Layer7,LOW);
  
  pinMode(Row0,OUTPUT);
  digitalWrite(Row0,LOW);
  pinMode(Row1,OUTPUT);
  digitalWrite(Row1,LOW);
  pinMode(Row2,OUTPUT);
  digitalWrite(Row2,LOW);
  pinMode(Row3,OUTPUT);
  digitalWrite(Row3,LOW);
  pinMode(Row4,OUTPUT);
  digitalWrite(Row4,LOW);
  pinMode(Row5,OUTPUT);
  digitalWrite(Row5,LOW);
  pinMode(Row6,OUTPUT);
  digitalWrite(Row6,LOW);
  pinMode(Row7,OUTPUT);
  digitalWrite(Row7,LOW);
  
  pinMode(ClockCycle,OUTPUT);
  digitalWrite(ClockCycle,LOW);
  
  // enables pull up resister
  pinMode(NextEffectButton,INPUT);
  digitalWrite(NextEffectButton,HIGH); 
  // enables shuffle
  pinMode(ShuffleButton,INPUT);
  digitalWrite(ShuffleButton,HIGH); 
  // shuffle LEF
  pinMode(ShuffleLED,OUTPUT);
  digitalWrite(ShuffleLED,LOW); 
}


String ReadSerialData(int count)
{
  
	String Data;
	char temp;
	while(Serial.available() < count){}
	for(int i = 0; i < count; i++)
	{
	  temp = Serial.read();
	  Data = Data + temp;
	}
	Data.trim();
	return Data;
}

int StringToInt(String temp)
{
   int value = atoi(&temp[0]);
   return value;
}

void CheckButtons()
{
  // Change Effect Button
  PinValue = digitalRead(NextEffectButton);
  if(PinValue == Button_On && Prev_NEB == Button_Off && millis() - Time_NEB > Debounce)
  {
	  if(EnableShuffle == 1)
	  {
		  EnableShuffle = 0;
		  digitalWrite(ShuffleLED,0);
	  }
	  else	ChangeEffect();

	  Time_NEB = millis();
  }
  Prev_NEB = PinValue;

  
  // Enable Shuffle Button
  PinValue = digitalRead(ShuffleButton);
  if(PinValue == Button_On && Prev_S == Button_Off && millis() - Time_S > Debounce)
  {
	  EnableShuffle = 1;
	  digitalWrite(ShuffleLED,1);

	  ChangeEffect();
	  
	  ShuffleDelay = 30000;
	  ShuffleStart = millis();
	  Time_S = millis();
  }
  Prev_S = PinValue;
  
}