// Translation from CalComp vector character plotter Fortran
// plotsub.f in TNT package
// refactored ID table to eliminate indexing kludge (sjr)
// fixed more characters, IT table in HEX, to see coordinates
// no display output, text move/draw output

//          EACH ELEMENT OF THE ARRAY "ID" CORRESPONDS TO ONE OF
//      THE PRINTING ASCII CHARACTERS.  High 6 bits of the WORD
//      CONTAINS  THE  NUMBER  OF STROKES USED TO FORM THE
//      CHARACTER AND THE lower 10 CONTAIN THE INDEX IN ARRAY
//      "IT"  OF  THE FIRST STROKE TO BE USED. ID = STR * 1024 +
//      BEG WHERE STR IS THE NUMBER OF STROKES AND  BEG  IS  THE
//      INDEX  TO  THE  FIRST  WORD  IN "IT".  THE "ID" ARRAY IS
//      (roughly) EQUIVALENT TO THE FOLLOWING TABLE:
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
//      64 140  `    2 284  (back tic)
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
//  ID array reindexed 6/24/2022, fixed char #62 and #64

const uint16_t ID[] PROGMEM = {
  4097, 4099, 11269, 12299, 11281, 10264, 2077, 4126,
  4128, 8226, 4132, 4134, 2222, 5165, 2070, 10289,
  5175, 8250, 13374, 7239, 9291, 11329, 5200, 16467,
  12379, 4193, 7206, 3171, 4197, 3175, 7273, 8301,
  8305, 11381, 8315, 7297, 7301, 6277, 11387, 6186,
  6281, 5260, 6287, 3217, 5267, 4246, 9265, 7287,
  11312, 8311, 12372, 4248, 6284, 3226, 5276, 4118,
  5279, 4258, 4260, 2214, 4263, 4265, 5292, 2332,   //1198 -> 2332 (IT 284) back tic
  9391, 9396, 8377, 10429, 10434, 7367, 12491, 8401,
  6357, 6360, 7387, 5343, 10466, 8423, 9451, 12528,
  12534, 6396, 10495, 7428, 7432, 3340, 9486, 4371,
  9493, 4378
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
const uint16_t IT[] PROGMEM = {  //284 entries, counting from 1
  0x3732, 0x3930, 0x2725, 0x4F45, 0x1252, 0x4241, 0x4544, 0x5414,
  0x2425, 0x2100, 0x3037, 0x3656, 0x2615, 0x2444, 0x5352, 0x4111,
  0x3050, 0x5232, 0x303F, 0x3515, 0x1700, 0x5710, 0x1F50, 0x5230,
  0x2011, 0x1346, 0x3727, 0x2451, 0x3735, 0x4736, 0x3140, 0x2736,
  0x3120, 0x1155, 0x5915, 0x1B53, 0x3D31, 0x2042, 0x3231, 0x3B44,
  0x3400, 0x1017, 0x1454, 0x5750, 0x2031, 0x3021, 0x2000, 0x4250,
  0x2840, 0x5156, 0x4727, 0x1611, 0x2047, 0x3200, 0x2637, 0x3020,
  0x4000, 0x1627, 0x4756, 0x5411, 0x1050, 0x1627, 0x4756, 0x5544,
  0x2444, 0x5351, 0x4020, 0x1116, 0x2747, 0x5600, 0x1712, 0x524F,
  0x4030, 0x5000, 0x1120, 0x4051, 0x5344, 0x1417, 0x5700, 0x1617,
  0x5756, 0x2000, 0x2413, 0x1120, 0x4051, 0x5344, 0x2415, 0x1627,
  0x4756, 0x5544, 0x1120, 0x4051, 0x5647, 0x2716, 0x1423, 0x4354,
  0x3534, 0x3A31, 0x4523, 0x4100, 0x1555, 0x1A52, 0x2543, 0x2100,
  0x1737, 0x4624, 0x2229, 0x2000, 0x4424, 0x2242, 0x4515, 0x1141,
  0x1016, 0x2747, 0x5650, 0x5313, 0x4453, 0x5140, 0x1017, 0x4756,
  0x5544, 0x1450, 0x5647, 0x2716, 0x1120, 0x4051, 0x5363, 0x4300,
  0x1017, 0x4756, 0x5140, 0x1000, 0x5717, 0x1444, 0x1410, 0x5000,
  0x2040, 0x3037, 0x2747, 0x5751, 0x4020, 0x1117, 0x4714, 0x5014,
  0x1710, 0x5000, 0x1017, 0x3357, 0x5000, 0x1017, 0x5057, 0x3037,
  0x1757, 0x1730, 0x5700, 0x1710, 0x3450, 0x5700, 0x3035, 0x1735,
  0x5700, 0x1757, 0x1050, 0x4727, 0x2040, 0x1750, 0x2747, 0x4020,
  0x1436, 0x5436, 0x3100, 0x3113, 0x3500, 0x1353, 0x1324, 0x4453,
  0x5020, 0x1122, 0x5200, 0x1711, 0x2040, 0x5153, 0x4424, 0x1300,
  0x5344, 0x2413, 0x1120, 0x4051, 0x5750, 0x5940, 0x2011, 0x1324,
  0x4453, 0x5140, 0x2011, 0x1324, 0x4453, 0x5212, 0x5647, 0x3726,
  0x204C, 0x1400, 0x5342, 0x2213, 0x1425, 0x4554, 0x5140, 0x2011,
  0x1727, 0x202B, 0x3444, 0x5350, 0x352C, 0x3430, 0x2840, 0x453C,
  0x4441, 0x3021, 0x1727, 0x202A, 0x442A, 0x5000, 0x2737, 0x3028,
  0x4000, 0x1410, 0x3B30, 0x5853, 0x4433, 0x2413, 0x1423, 0x202B,
  0x3444, 0x5350, 0x1113, 0x2444, 0x5351, 0x4020, 0x1100, 0x1525,
  0x2010, 0x2C35, 0x4554, 0x5342, 0x3223, 0x5545, 0x4050, 0x4C35,
  0x2514, 0x1322, 0x3243, 0x1524, 0x202C, 0x5453, 0x5344, 0x2413,
  0x1252, 0x5140, 0x2011, 0x2621, 0x3040, 0x511C, 0x4400, 0x1411,
  0x2040, 0x515C, 0x5000, 0x1430, 0x5400, 0x1411, 0x2031, 0x3439,
  0x4051, 0x5414, 0x1450, 0x5C10, 0x1514, 0x2343, 0x4D41, 0x3020,
  0x1100, 0x1444, 0x1040, 0x2735
};  //added back tic at last loc (IT[284], Fortran indexing)


// qxdraw dumps the move/draw commands for a character, on the defined 8x8 grid

void qxdraw(int ix, int iy, char penup) {
  static char up=0;
  if (iy > 7 or penup == 1) {
    if (iy > 7) iy = iy - 8;
    up = 1;
  }

  if (up == 1) Serial.print("moveto ");
  else Serial.print("drawto ");
  Serial.print(ix); Serial.print(","); Serial.println(iy);
  up = 0;
}

void setup() {

  int IX, IY, IDIV, J, K, L1;  //variables in original Fortran code
  char penup = 1; //pen status

  Serial.begin(115200);
  while (!Serial);

//  Serial.println("IT array size "); Serial.println(sizeof(IT) / sizeof(IT[0]));

// run through all 90 characters
  for (int i = 1; i < 91; i++) {
    byte char_number = i;  //string[i] - 32; //character number in ASCII table
    K = pgm_read_word_near(ID + (char_number - 1)); //C array indexing
    Serial.println();
    Serial.print(char_number);  //ASCII - 32
    Serial.write(' ');
    Serial.write(char_number+32); //ASCII character to be drawn
    Serial.print(" ID ");  //pointer to character data
    Serial.print(K);
    //unpack ID table entry
    J = (K >> 10);
    L1 = K - (J << 10); //stroke table index

    // draw char using stroke table, start with move (pen up)
    penup = 1;

    Serial.print(" IT ");  
    Serial.print(L1); //table index
    Serial.print(" strokes ");
    Serial.println(J);
    
   // unpack move/draw commands. Always start char with move!

    int JJ = (J + 1) / 2;  //round up and calculate number of stroke table words
    for (int w = 0; w < JJ; w++) {

      K = pgm_read_word_near(IT + (L1 - 1)); //get instructions, C array indexing
      IDIV = 4096;

      // decode table and draw each stroke

      for (int b = 0; b < 2; b++) { //bytes
        
        IX = K / IDIV;  //original Fortran code, could replace by shifts
        K = K - IDIV * IX;
        IDIV = IDIV / 16;
        IY = K / IDIV;
        K = K - IDIV * IY;
        IDIV = IDIV / 16;

        if (IX > 0 and J > 0) { //IX = 0 -> skip this byte (used!)
          qxdraw(IX, IY, penup);  //send to device
          if (penup == 1) penup = 0;
          J = J - 1; //count down strokes
        } //5650
      } //end for bytes 5650
      L1++;  //next word
    } //end for words 5660
  } //end for i (char number)
}
void loop() {
}
