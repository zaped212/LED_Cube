#include "Char_Display.h"


Char_Display::Char_Display(Cube8x8x8 *CubeRef, long UpdateDelay, int Thickness, String display)
{	
	Cube = CubeRef;
	Delay = UpdateDelay;

	thickness = Thickness;
	thickness_count = 0;

	Axis = X_Axis;
	Dirrection = -1;

	Display = display;
	StringSize = Display.length();
	StringPos = 0;

	for(int r = 0; r < 8; r ++)
	{
		for( int c = 0; c < 8; c++)
		{
			NextChar[r][c] = false;
		}
	}

}

Char_Display::~Char_Display(void)
{
	Cube->CreateCubeOff();
}

void Char_Display::Update()
{	
	if(millis() > StartTime + Delay)
	{
		StartTime = millis();
		
		// shift cube to display new layer
		Cube->Shift(Axis,Dirrection);

		// determin if need to display new character
		if(thickness_count >= 8)
		{
			// if still displaying characters output next avaliable 
			if(StringPos < StringSize)
			{
				UnpackDisplay();
			}
			// else display blank character
			else
			{
				for(int r = 0; r < 8; r ++)
				{
					for(int c = 0; c < 8; c ++)
					{
						NextChar[r][c] = false;
					}
				}
			}

			
			thickness_count = 0;
			if(Display[StringPos] == ' ') thickness_count = 4;

			StringPos = StringPos++;
			if(StringPos > StringSize + 1) StringPos = 0;
		}

		// determin is more layers need to be displayed
		if(thickness_count < thickness)
		{
			// Load character into display
			for(int r = 0; r < 8; r ++)
			{
				for(int c = 0; c < 8; c ++)
				{
					Cube->SetVoxel(7,7-c,r, NextChar[r][c]);
				}
			}
		}

		thickness_count ++;
	}
	
}

void Char_Display::Begin()
{
	Cube->CreateCubeOff();
	StartTime = millis();
}

void Char_Display::End()
{
}


void Char_Display::UnpackDisplay()
{
	// Algorithym to unpack character matrix information
	int pos = (Display[StringPos] - 32)*2;

	uint32_t matrix = toncfontTiles[pos];
	uint32_t temp;
	uint32_t one = 0x00000001;
	uint32_t offset;

	// load in upper 4 layers
	offset = 0;
	for(int r = 7; r > 3; r --)
	{
		for(int c = 0; c < 8; c ++)
		{
			// parse out the bits
			temp = (one<<(offset));
			temp = temp & matrix;
			temp = temp >> (offset);

			offset ++;			

			NextChar[r][c] = (bool)temp;
		}
	}

	pos++;
	matrix = toncfontTiles[pos];

	offset = 0;
	// load in lower 4 layers
	for(int r = 3; r >= 0; r --)
	{
		for(int c = 0; c < 8; c ++)
		{
			// parse out the bits
			temp = (one<<(offset));
			temp = temp & matrix;
			temp = temp >> (offset);

			offset ++;			

			NextChar[r][c] = (bool)temp;
		}
	}
	
	Serial.println();
}
