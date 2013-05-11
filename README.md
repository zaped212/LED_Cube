LED_Cube
========
This code was created in visual studio with the Visual Micro Plugin.

You can still use the standard Arduino IDE to program your LED Cube.

This code assumes:
  8x8x8 LED cube is multiplexed by layers via ground.
  Each coloum is independantly controlled via 8 serial shift registers in parrallel to shift out all 64 coloums in 8 steps.

  The display is updated every 1ms on a interrupt. Layer is updated every interrput causing the entire display to be refreshed once every 8ms.

