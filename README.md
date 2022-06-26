# Vector_character_generator
Vector based character generator based on 1980s Calcomp pen plotter Fortran code

I've uploaded C/C++ code to generate ASCII characters for vector drawing devices, translated from the Fortran77 code for Calcomp pen plotters.

The main advantage of a vector-based character generator is that, unlike with bitmap character generators, the output is infinitely scaleable and can be drawn in arbitrary orientations and/or distortions with **no aliasing**. This is very useful to drive plotters, engravers (laser or wood), laser light shows, etc.

Characters are defined on an 8x8 (X, Y) matrix as lines (strokes) between endpoints, and were originally optimized for efficiency and plotting speed, for production of hard copy using simple move/draw pen plotters. 

**NOTE:** due to the program design, vector endpoints with **X = 0** have special significance (a "skip" command) and cannot be used to form part of the character, so that column should be considered as part of character to character spacing.  It is trivial to do away with that restriction, if desired (e.g. X=0 could be coded as X=8, as done for Y>7, pen up move).

Some user guides to the Calcomp vector drawing routines can be found here: http://www.urbanjost.altervista.org/LIBRARY/libcalcomp/index.html

Examples of pen-plotted Calcomp characters and symbols are shown in the images below (from above link).

![c_qa1](https://user-images.githubusercontent.com/5509037/175750542-a4abc832-2eb5-47d3-bb6a-b44a1b694785.gif)

![c_qa2 1](https://user-images.githubusercontent.com/5509037/175750544-fa52a787-6f7e-40b6-b993-a0fce5393dcf.gif)

![c_qa3 4](https://user-images.githubusercontent.com/5509037/175794572-fbf3b9f0-d44c-469c-90e0-383c351d5102.gif)


I included the original Fortran77 code (plotsub.f), which is in the public domain, and three C/C++ translations for Arduino.

1. calcomp4.ino is a C/C++ translation of the character generator SYMB1 found in plotsub.f, which features lower case letters (not available in the original Calcomp routines).

2. calcomp5.ino is a refactored Arduino translation of the same code, featuring graphic display of single characters on an Adafruit SSD1306 128x64 bitmapped display. Some minor symbol and data table errors in the plotsub.f code were corrected in the process.

3. calcomp6.ino is the above refactored code, but with general purpose text output (moveto/drawto commands) for the graphics, to be used as input to other devices.  

The coordinate output from this code consists of the individual moves required for form the character on an 8x8 matrix. It is "proof of principle" and to be useful for plotting text or engraving, the output has to be scaled and origin shifted, and possibly rotated to fit individual requirements. Some study of the Calcomp documentation and the Fortran code in plotsub.f (particularly the subroutines NUMBER and SYMBOL) should make it clear how to proceed. In many cases, rotation/scaling/shifting transformation code can be directly lifted from the Fortran and with very minor changes, incorporated into a C/C++ package.


The file Calcomp_ID_IT.txt is a complete list of all the characters and symbols encoded by calcomp5.ino and calcomp6.ino, including the individual move/draw vector outputs representing each character.
