# Vector_character_generator
Vector based character generator based on 1980s Calcomp code

I've uploaded C/C++ code to generate ASCII characters for vector drawing devices, translated from 1980 Fortran77 code for Calcomp pen plotters.

The advantage of a vector-based character generator is that unlike bitmap character generators, the output is infinitely scaleable and can be rotated and plotted in arbitrary orientations or with arbitrary distortions. Useful to drive engravers (laser or wood), etc.

Examples of pen-plotted Calcomp characters are shown in the images below:

![c_qa1](https://user-images.githubusercontent.com/5509037/175750542-a4abc832-2eb5-47d3-bb6a-b44a1b694785.gif)

![c_qa2 1](https://user-images.githubusercontent.com/5509037/175750544-fa52a787-6f7e-40b6-b993-a0fce5393dcf.gif)

I included the original Fortran77 code (plotsub.f), which is in the public domain, and three C/C++ translations for Arduino.

1. calcomp4.ino is an Arduino translation of the character generator SYMBOL found in plotsub.f, with extensions to plot lower case ASCII characters.

2. calcomp5.ino is a refactored Arduino translation of the same code, featuring graphic display of single characters on an Adafruit SSD1306 128x64 bitmapped display.

3. calcomp6.ino is the above refactored code, but with general purpose text output (moveto/drawto commands) for the graphics, to be used as input to other devices.

