# Vector_character_generator
Vector based character generator based on 1980s Calcomp pen plotter Fortran code

I've uploaded C/C++ code to generate ASCII characters for vector drawing devices, translated from the Fortran77 code for Calcomp pen plotters.

The main advantage of a vector-based character generator is that, unlike with bitmap character generators, the output is infinitely scaleable and can be rotated and plotted in arbitrary orientations or with arbitrary distortions with **no aliasing**. Useful to drive engravers (laser or wood), etc.

Characters are defined on an 8x8 (X, Y) matrix as lines (strokes) between endpoints, and were originally optimized for efficiency and plotting speed, for production of hard copy using simple move/draw pen plotters. **NOTE:** due to program design, character coordinate **X = 0** has special significance and cannot be used to form part of the character, so that column could be considered as part of character to character spacing.

Some guides for Calcomp vector routines can be found here: http://www.urbanjost.altervista.org/LIBRARY/libcalcomp/index.html

Examples of pen-plotted Calcomp characters and symbols are shown in the images below:

![c_qa1](https://user-images.githubusercontent.com/5509037/175750542-a4abc832-2eb5-47d3-bb6a-b44a1b694785.gif)

![c_qa2 1](https://user-images.githubusercontent.com/5509037/175750544-fa52a787-6f7e-40b6-b993-a0fce5393dcf.gif)

I included the original Fortran77 code (plotsub.f), which is in the public domain, and three C/C++ translations for Arduino.

1. calcomp4.ino is a C/C++ translation of the character generator SYMB1 found in plotsub.f, which features lower case letters extensions not found in the original Calcomp routines.

2. calcomp5.ino is a refactored Arduino translation of the same code, featuring graphic display of single characters on an Adafruit SSD1306 128x64 bitmapped display. Some minor symbol and data table errors in the plotsub.f code were corrected in the process.

3. calcomp6.ino is the above refactored code, but with general purpose text output (moveto/drawto commands) for the graphics, to be used as input to other devices.

The file Calcomp_ID_IT.txt is a complete list of all the characters and symbols encoded by calcomp5.ino and calcomp6.ino, including the individual move/draw vector outputs representing each character.
