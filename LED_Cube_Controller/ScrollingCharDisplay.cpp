#include "ScrollingCharDisplay.h"


ScrollingCharDisplay::ScrollingCharDisplay(Cube8x8x8 *CubeRef, long UpdateDelay, String display)
{
	Cube = CubeRef;
	Delay = UpdateDelay;

	Display = display;
	StringSize = Display.length();
	StringPos = 0;

	NextPos = 0;

	// clear NextChar array
	for(int r = 0; r < 8; r ++)
	{
		for( int c = 0; c < 8; c++)
		{
			NextChar[r][c] = false;
		}
	}
}


ScrollingCharDisplay::~ScrollingCharDisplay(void)
{
	Cube->CreateCubeOff();
}

void ScrollingCharDisplay::Update()
{	
	if(millis() > StartTime + Delay)
	{
		StartTime = millis();

		// rotate cube to display new character
				
		//remove wraparound
		for(int z = 0; z < 8; z++)
		{
			Cube->SetVoxel(7,7,z,0);
		}

		Cube->RotateShell();

		// determin if need to display new character
		if(NextPos >= 8)
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

			NextPos = 0;
			if(Display[StringPos] == ' ') NextPos = 4;

			StringPos = StringPos++;
			if(StringPos > StringSize + 1) StringPos = 0;
		}

		// put next col of character on the display
		// Load character into display
		for(int z = 0; z < 8; z ++)
		{
			Cube->SetVoxel(7,0,z, NextChar[z][NextPos]);
		}

		NextPos ++;
	}
	
}

void ScrollingCharDisplay::Begin()
{
	Cube->CreateCubeOff();
	StartTime = millis();
}

void ScrollingCharDisplay::End()
{
}

// same algorithym as in Char_Display
void ScrollingCharDisplay::UnpackDisplay()
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