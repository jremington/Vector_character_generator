// Translation of CalComp Fortran vector character generator
// file plotsub.f in TNT package

// original indexing, output on SSD1306 display
// some errors in character table not corrected.

//          EACH ELEMENT OF THE ARRAY "ID" CORRESPONDS TO ONE OF
//      THE PRINTING ASCII CHARACTERS.  THE LEFT
//      BYTE  CONTAINS  THE  NUMBER  OF STROKES USED TO FORM THE
//      CHARACTER AND THE RIGHT BYTE CONTAINS THE INDEX IN ARRAY
//      "IT"  OF  THE FIRST STROKE TO BE USED.  ID = STR * 256 +
//      BEG WHERE STR IS THE NUMBER OF STROKES AND  BEG  IS  THE
//      INDEX  TO  THE  FIRST  WORD  IN "IT".  THE "ID" ARRAY IS
//      EQUIVALENT TO THE FOLLOWING TABLE:
//
//      NO OCT CHR STR BEG NO OCT CHR STR BEG NO OCT CHR STR BEG
//      == === === === === == === === === === == === === === ===
//       1  41  !    4   1 22  66  6   11  65 43 113  K    6 143
//       2  42  "    4   3 23  67  7    5  80 44 114  L    3 145
//       3  43  #   11   5 24  70  8   16  83 45 115  M    5 147
//       4  44  $   12  11 25  71  9   12  91 46 116  N    4 150
//       5  45  %   11  17 26  72  :    4  97 47 117  O    9  49
//       6  46  &   10  24 27  73  ;    7  38 48 120  P    7 119
//       7  47  '    2  29 28  74  <    3  99 49 121  Q   11  48
//       8  50  (    4  30 29  75  =    4 101 50 122  R    8 119
//       9  51  )    4  32 30  76  >    3 103 51 123  S   12  84
//      10  52  *    8  34 31  77  ?    7 105 52 124  T    4 152
//      11  53  +    4  36 32 100  @    8 109 53 125  U    6 140
//      12  54  ,    4  38 33 101  A    8 113 54 126  V    3 154
//      13  55  -    2 174 34 102  B   11 117 55 127  W    5 156
//      14  56  .    5  45 35 103  //   8 123 56 130  X    4  22
//      15  57  /    2  22 36 104  D    7 129 57 131  Y    5 159
//      16  60  0   10  49 37 105  E    7 133 58 132  Z    4 162
//      17  61  1    5  55 38 106  F    6 133 59 133  [    4 164
//      18  62  2    8  58 39 107  G   11 123 60 134  \    2 166
//      19  63  3   13  62 40 110  H    6 142 61 135  ]    4 167
//      20  64  4    7  71 41 111  I    6 137 62 136  ^    5 169
//      21  65  5    9  75 43 112  J    5 140 63 137  <-   5 172
//
//      64 140       1 174  (back tic, empty)
//      65 141  a    9 175 74 152  j    6 216 83 163  s    10 255
//      66 142  b    9 180 75 153  k    7 219 84 164  t     7 260
//      67 143  //   8 185 76 154  l    5 223 85 165  u     7 264
//      68 144  d   10 189 77 155  m   10 226 86 166  v     3 268
//      69 145  e   10 194 78 156  n    8 231 87 167  w     9 270
//      70 146  f    7 199 79 157  o    9 235 88 170  x     4 275
//      71 147  g   12 203 80 160  p   12 240 89 171  y     9 277
//      72 150  h    8 209 81 161  q   12 246 90 172  z     4 282
//      73 151  i    6 213 82 162  r    6 252
//
//      NOTE: char #64 empty. Stroke table indexing was changed at some point 
//      to allow more that 255 entries, breaking at char #83, SJR 6/23/2022.
//
const uint16_t ID[] PROGMEM = {
  1025, 1027, 2821, 3083, 2833, 2584,  541, 1054, 1056,
  2082, 1060, 1062,  686, 1325,  534, 2609, 1335, 2106,
  3390, 1863, 2379, 2881, 1360, 4179, 3163, 1121, 1830,
  867, 1125,  871, 1897, 2157, 2161, 2933, 2171, 1921,
  1925, 1669, 2939, 1578, 1673, 1420, 1679,  913, 1427,
  1174, 2353, 1911, 2864, 2167, 3156, 1176, 1676,  922,
  1436, 1046, 1439, 1186, 1188,  678, 1191, 1149, 1452,
  430, 2479, 2484, 2233, 2749, 2754, 1991, 3275, 2257,
  1749, 1752, 2011, 1503, 2786, 2279, 2539, 3312, 3318,
  1788, 2815, 2052, 2056, 1036, 2574, 1299, 2581, 1306
};
//
//          THE  ARRAY "IT" CONTAINS THE ACTUAL COORDINATES USED
//      IN FORMING THE CHARACTERS.  ONE 8 BIT BYTE IS  USED  FOR
//      EACH  COORDINATE  PAIR  RESULTING IN 2 STROKE-COORDINATE
//      PAIRS PER WORD.  THE FIRST NIBBLE IN  THE  BYTE  SPECIFIES
//      THE  X COORDINATE (0<X<7) AND THE SECOND SPECIFIES THE Y
//      COORDINATE (0<=Y<8).  SETTING X=0 CAUSES THE BYTE TO  BE
//      SKIPPED  AND  ADDING  8 TO Y CAUSES THE PEN TO BE RAISED
//      BEFORE MOVING.  IT IS PUT DOWN AFTER MOVING.
//
const uint16_t IT[] PROGMEM = {
  14130, 14640, 10021, 20293,  4690, 16961, 17732, 21524,
  9253,  8448, 12343, 13910,  9749,  9284, 21330, 16657,
  12368, 21042, 12351, 13589,  5888, 22288,  8016, 21040,
  8209,  4934, 14119,  9297, 14133, 18230, 12608, 10038,
  12576,  4437, 22805,  6995, 15665,  8258, 12849, 15172,
  13312,  4119,  5204, 22352,  8241, 12321,  8192, 16976,
  10304, 20822, 18215,  5649,  8263, 12800,  9783, 12320,
  16384,  5671, 18262, 21521,  4176,  5671, 18262, 21828,
  9284, 21329, 16416,  4374, 10055, 22016,  5906, 21071,
  16432, 20480,  4384, 16465, 21316,  5143, 22272,  5655,
  22358,  8192,  9235,  4384, 16465, 21316,  9237,  5671,
  18262, 21828,  4384, 16465, 22087, 10006,  5155, 17236,
  13620, 14897, 17699, 16640,  5461,  6738,  9539,  8448,
  5943, 17956,  8745,  8192, 17444,  8770, 17685,  4417,
  4118, 10055, 22096, 21267, 17491, 20800,  4119, 18262,
  21828,  5200, 22087, 10006,  4384, 16465, 21347, 17152,
  4119, 18262, 20800,  4096, 22295,  5188,  5136, 20480,
  8256, 12343, 10055, 22353, 16416,  4375, 18196, 20500,
  5904, 20480,  4119, 13143, 20480,  4119, 20567, 12343,
  5975,  5936, 22272,  5904, 13392, 22272, 12341,  5941,
  22272,  5975,  4176, 18215,  8256,  5968, 10055, 16416,
  5174, 21558, 12544, 12563, 13568,  4947,  4900, 17491,
  20512,  4386, 20992,  5905,  8256, 20819, 17444,  4864,
  21316,  9235,  4384, 16465, 22352, 22848,  8209,  4900,
  17491, 20800,  8209,  4900, 17491, 21010, 22087, 14118,
  8268,  5120, 21314,  8723,  5157, 17748, 20800,  8209,
  5927,  8235, 13380, 21328, 13612, 13360, 10304, 17724,
  17473, 12321,  5927,  8234, 17450, 20480, 10039, 12328,
  16384,  5136, 15152, 22611, 17459,  9235,  5155,  8235,
  13380, 21328,  4371,  9284, 21329, 16416,  4352,  5413,
  8208, 11317, 17748, 21314, 12835, 21829, 16464, 19509,
  9492,  4898, 12867,  5412,  8236, 21587, 21316,  9235,
  4690, 20800,  8209,  9761, 12352, 20764, 17408,  5137,  8256,
  20828, 20480,  5168, 21504,  5137,  8241, 13369, 16465, 21524,
  5200, 23568,  5396,  9027, 19777, 12320,  4352,  5188,  4160
};


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void qxdraw(int ix, int iy, char penup) {
  static char up = 1, oldx = 0, oldy = 0;
  if (iy > 7 or penup == 1) {
 //   Serial.println(" pen up");

    if (iy > 7) iy = iy - 8;
    up = 1;
    oldx = 5+5 * ix;  //vector start
    oldy = 60 - 5 * iy; 
  }
  ix = 5+5 * ix; //vector end
  iy = 60 - 5 * iy;
//  Serial.print("moveto "); Serial.print(ix); Serial.print(","); Serial.println(iy);
  if (up == 0) display.drawLine(oldx, oldy, ix, iy, SSD1306_WHITE);  // pen down draw
  else {
    display.drawLine(oldx, oldy, ix, iy, SSD1306_BLACK); //pen up move
//    Serial.println(" pen down");  //revert pen
    up = 0;
  }
  oldx = ix; // next vector start
  oldy = iy;
  display.display();
}

void setup() {

  int IX, IY, IDIV, J, K, L1;  //variables in original Fortran code
  char penup = 1; //pen status
  
  Serial.begin(115200);
  while (!Serial);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 begin failed"));
    for (;;);
  }

  // Clear the buffer
  display.clearDisplay();
  display.display();

  for (int i = 62; i < 65; i++) {
    byte char_number = i;  //string[i] - 32; //character number in ASCII table
    byte table_offset = 0;
    if (char_number > 83) table_offset = 1;  //"fudge factor" in Fortran code (gap in table indexing)
    K = pgm_read_word_near(ID + (char_number - 1)); //C array indexing
    Serial.println();
    Serial.print("No ");
    Serial.print(char_number);
    Serial.print(" ID ");
    Serial.println(K);
    //unpack ID table entry  "table_offset" is a kludge to deal with the 255 boundary on L1
    J = (K >> 8) - table_offset;
    L1 = K - (J << 8); //stroke table index

    // draw char using stroke table
    penup = 1;
//    Serial.println(" pen up");

    Serial.print("IT ");
    Serial.print(L1);
    Serial.print(" strokes ");
    Serial.println(J);

    int JJ = (J + 1) / 2;  //round up and calculate number of table words
    for (int w = 0; w < JJ; w++) {

      K = pgm_read_word_near(IT + (L1 - 1)); //get instructions, C array indexing
      IDIV = 4096;

      // decode table and draw each stroke

      for (int b = 0; b < 2; b++) { //bytes
        IX = K / IDIV;  //Fortran code, replace by shifts
        K = K - IDIV * IX;
        IDIV = IDIV / 16;
        IY = K / IDIV;
        K = K - IDIV * IY;
        IDIV = IDIV / 16;

        if (IX > 0 and J > 0) { //IX = 0 -> skip this byte
          qxdraw(IX, IY, penup);
          if (penup = 1) penup = 0;
          J = J - 1; //count down strokes
        } //5650
      } //end for bytes 5650
      L1++;  //next word
    } //end for words 5660
    delay(2000);
    display.clearDisplay();
  } //end for i (char number)
}
void loop() {
}
