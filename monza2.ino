// TO-DO:
// flip left commands so they work for right hand turns as well
// add trees and brake marker signs to the side of the road, animate them so it looks like we're moving
// Smooth transition between straight and turn - change road before car?
// idea: have a random selection of objects to 'whizz' past on the side of the track. Start with a stick or brake signs.
// try animating curbs
// fix top left red pixel
// LONGER TERM: add lively 'performance' like lockups
//              Randomize driver helmet color/pattern



#include <RGBmatrixPanel.h>

#define CLK  11   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2


RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() 
{
    Serial.begin(9600);
    matrixInit();
    
}

void loop() 
{
    matrixClearScreen();  
    drawStraight();
    
    delay(5000);
    
    matrixClearScreen();
    drawRoadTurnLeft();
    
    delay(400);
    
    matrixClearScreen();  
    drawCarAndRoadTurnLeft();

    delay(2000);
}

/*
 * Functions
 */

// draw the base image:
void drawStraight(void)
{
      drawRoadAndTires(0,0);
      drawTrackLimits(0);
      drawGrass(0);
      drawCar();
      drawDriver(0);
}

// draw the road turning left:
void drawRoadTurnLeft(void)
{
      drawRoadAndTires(-1,0);
      drawGrass(-1);
      drawTrackLimits(-1);
      drawCar();
      drawDriver(0);
}

// draw the car turning left on the road:
void drawCarAndRoadTurnLeft(void)
{
      drawRoadAndTires(-1,-1);
      drawGrass(-1);
      drawTrackLimits(-1);
      drawCar();
      drawDriver(-1);
}

// draw the gray-blue road surface
// left: -1
// straight: 0
// right: 1
void drawRoadAndTires(int road, int tire)
{
    int color_gray = matrix.Color333(2,2,4);
    
    if ((tire == -1) && (road == -1)) // left tire and left road 
    {
        int x_gray[237] ={3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
                             4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,
                                5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,
                                   6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,
                                   6, 7, 8, 9,10,11,12,13,14,      17,18,19,20,21,22,
                                      7, 8, 9,                                    22,23,24,
                                      7, 8,   10,11,12,13,14,      17,18,19,20,   22,23,24,25,
                                   6, 7,         11,12,13,            18,19,         23,24,25,26,
                                   6, 7,                                                24,25,26,27,28,29,
                                   6, 7, 8,         12,13,            18,19,20,         24,25,26,27,28,
                                5, 6, 7, 8, 9,   11,12,                  19,20,21,   23,24,25,26,27,28,29,
                                5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,
                             4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,
                          3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,
                          3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
                       2, 3, 4, 5, 6, 7, 8, 9,10,                              21,22,23,24,25,26,27,28,29,30,31};
    
                  
        int y_gray[237] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                   3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                                   4, 4, 4, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4,
                                      5, 5, 5,                                    5, 5, 5,
                                      6, 6,    6, 6, 6, 6, 6,       6, 6, 6, 6,   6, 6, 6, 6,
                                   7, 7,          7, 7, 7,             7, 7,         7, 7, 7, 7,
                                   8, 8,                                                 8, 8, 8, 8, 8, 8,
                                   9, 9, 9,          9, 9,             9, 9, 9,          9, 9, 9, 9, 9,
                               10,10,10,10,10,   10,10,                  10,10,10,   10,10,10,10,10,10,10,
                               11,11,11,11,11,11,11,                        11,11,11,11,11,11,11,11,11,11,
                             12,12,12,12,12,12,12,12,                        12,12,12,12,12,12,12,12,12,12,
                          13,13,13,13,13,13,13,13,13,                        13,13,13,13,13,13,13,13,13,13,13,
                          14,14,14,14,14,14,14,14,14,                        14,14,14,14,14,14,14,14,14,14,14,14,
                       15,15,15,15,15,15,15,15,15,                              15,15,15,15,15,15,15,15,15,15,15};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
    }
    
    else if ((tire == 0) && (road == -1)) // tire straight and road left 
    {
        int x_gray[237] ={3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
                           4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,
                              5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,
                                 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,
                                 6, 7, 8, 9,10,11,12,13,14,      17,18,19,20,21,22,
                                    7, 8, 9,                                    22,23,24,
                                    7, 8, 9,10,11,12,13,14,      17,18,19,20,21,22,23,24,25,
                                 6, 7,         11,12,13,            18,19,20,          24,25,26,
                                 6, 7,                                                24,25,26,27,28,29,
                                 6, 7,            12,13,            18,19,            24,25,26,27,28,
                              5, 6, 7,         11,12,                  19,20,         24,25,26,27,28,29,
                              5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,
                           4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,
                        3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,
                        3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
                     2, 3, 4, 5, 6, 7, 8, 9,10,                              21,22,23,24,25,26,27,28,29,30,31};
  
                
      int y_gray[237] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                              2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                                 4, 4, 4, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4,
                                    5, 5, 5,                                    5, 5, 5,
                                    6, 6, 6, 6, 6, 6, 6, 6,       6, 6, 6, 6, 6, 6, 6, 6, 6,
                                 7, 7,          7, 7, 7,             7, 7, 7,         7,7,7,
                                 8, 8,                                                 8, 8, 8, 8, 8, 8,
                                 9, 9,             9, 9,             9, 9,             9, 9, 9, 9, 9,
                             10,10,10,         10,10,                  10,10,         10,10,10,10,10,10,
                             11,11,11,11,11,11,11,                        11,11,11,11,11,11,11,11,11,11,
                           12,12,12,12,12,12,12,12,                        12,12,12,12,12,12,12,12,12,12,
                        13,13,13,13,13,13,13,13,13,                        13,13,13,13,13,13,13,13,13,13,13,
                        14,14,14,14,14,14,14,14,14,                        14,14,14,14,14,14,14,14,14,14,14,14,
                     15,15,15,15,15,15,15,15,15,                              15,15,15,15,15,15,15,15,15,15,15};
       
       drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
    }
    
    else if ((tire == 0) && (road == 0)) // tire straight and road straight
    {
         int x_gray[248] =                     {12,13,14,15,16,17,18,19,
                                             11,12,13,14,15,16,17,18,19,20,
                                          10,11,12,13,14,15,16,17,18,19,20,21,
                                        9,10,11,12,13,14,15,16,17,18,19,20,21,22,
                                     8, 9,10,11,12,13,14,      17,18,19,20,21,22,23,
                                  7, 8, 9,                                    22,23,24,
                               6, 7, 8, 9,10,11,12,13,14,      17,18,19,20,21,22,23,24,25,
                            5, 6, 7,         11,12,13,            18,19,20,         24,25,26,
                         4, 5, 6, 7,                                                24,25,26,27,
                      3, 4, 5, 6, 7,            12,13,            18,19,            24,25,26,27,28,
                   2, 3, 4, 5, 6, 7,         11,12,                  19,20,         24,25,26,27,28,29,
                1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,
             0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
             0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
             0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
             0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,                              21,22,23,24,25,26,27,28,29,30,31};

              
        int y_gray[248] =            {       0, 0, 0, 0, 0, 0, 0, 0, 
                                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                                 4, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4, 4,
                              5, 5, 5,                                     5, 5, 5,
                           6, 6, 6, 6, 6, 6, 6, 6, 6,          6, 6, 6, 6, 6, 6, 6, 6, 6,
                           7, 7, 7,       7, 7, 7,              7, 7, 7,         7, 7, 7,
                        8, 8, 8, 8,                                              8, 8, 8, 8,
                     9, 9, 9, 9, 9,             9, 9,           9, 9,            9, 9, 9, 9, 9,
                 10,10,10,10,10,10,         10,10,                10,10,          10,10,10,10,10,10,
              11,11,11,11,11,11,11,11,11,11,11,                      11,11,11,11,11,11,11,11,11,11,11,
           12,12,12,12,12,12,12,12,12,12,12,12,                      12,12,12,12,12,12,12,12,12,12,12,12,
           13,13,13,13,13,13,13,13,13,13,13,13,                      13,13,13,13,13,13,13,13,13,13,13,13,
           14,14,14,14,14,14,14,14,14,14,14,14,                      14,14,14,14,14,14,14,14,14,14,14,14,
           15,15,15,15,15,15,15,15,15,15,15,                            15,15,15,15,15,15,15,15,15,15,15};

       drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
    }
}

// draw the white track limits
// left: dir = -1
// straight: dir = 0
// right: dir = 1
void drawTrackLimits(int dir)
{
  int color_white = matrix.Color888(255,255,255);
  
  if (dir == -1) // left
  {
      int x_white[65] = { 1,2,16,
                          2,3,17,18,19,
                          3,4,19,20,21,
                          4,5,21,22,23,
                          4,5,23,24,25,
                          5,6,25,26,
                          5,6,26,27,28,
                          4,5,27,28,29,
                          4,5,29,30,
                          4,5,29,30,
                          3,4,30,31,
                          3,4,30,31,
                          2,3,30,31,
                          1,2,31,
                          2,2,
                          0,1};
                         
      int y_white[65] = {0,0,0,
                         1,1,1,1,1,
                         2,2,2,2,2,
                         3,3,3,3,3,
                         4,4,4,4,4,
                         5,5,5,5,
                         6,6,6,6,6,
                         7,7,7,7,7,
                         8,8,8,8,
                         9,9,9,9,
                         10,10,10,10,
                         11,11,11,11,
                         12,12,12,12,
                         13,13,13,
                         14,14,
                         15,15};
       drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
  }
  
  else if (dir == 0) // straight
  {
      int x_white[49] = {10,11,20,21,
                          9,10,21,22,
                          8, 9,22,23,
                          7, 8,23,24,
                          6, 7,24,25,
                          5, 6,25,26,
                          4, 5,26,27,
                          3, 4,27,28,
                          2, 3,28,29,
                          1, 2,29,30,
                          0,1, 30,31,
                          31};
                         
      int y_white[49] = {0,0,0,0,
                         1,1,1,1,
                         2,2,2,2,
                         3,3,3,3,
                         4,4,4,4,
                         5,5,5,5,
                         6,6,6,6,
                         7,7,7,7,
                         8,8,8,8,
                         9,9,9,9,
                         10,10,10,10,
                         11,11,11,11,
                         12};
      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
  }
  else if (dir == 1) // right
  {
      // tbd
  }        
}

// draw the green grass
// left: dir = -1
// straight: dir = 0
// right: dir = 1
void drawGrass(int dir)
{
    int color_green = matrix.Color888(34,139,34);
     
    if (dir == -1) // left
    {
        int x_green[137] = {0, 1,                16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
                            0, 1, 2,                      19,20,21,22,23,24,25,26,27,28,29,30,31,
                            0, 1, 2, 3,                         21,22,23,24,25,26,27,28,29,30,31,
                            0, 1, 2, 3, 4,                            23,24,25,26,27,28,29,30,31,
                            0, 1, 2, 3, 4,                                  25,26,27,28,29,30,31,                        
                            0, 1, 2, 3, 4, 5,                                  26,27,28,29,30,31,
                            0, 1, 2, 3, 4, 5,                                        28,29,30,31,
                            0, 1, 2, 3, 4,                                              29,30,31,
                            0, 1, 2, 3, 4,                                                 30,31,
                            0, 1, 2, 3, 4,                                                 30,31,
                            0, 1, 2, 3,                                                       31,
                            0, 1, 2, 3,                                                       31,
                            0, 1, 2,
                            0, 1,
                            0, 1,
                            0};
        
        int y_green[137] = { 0, 0,                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             1, 1, 1,                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                             2, 2, 2, 2,                          2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                             3, 3, 3, 3, 3,                             3, 3, 3, 3, 3, 3, 3, 3, 3,
                             4, 4, 4, 4, 4,                                   4, 4, 4, 4, 4, 4, 4,
                             5, 5, 5, 5, 5, 5,                                   5, 5, 5, 5, 5, 5,
                             6, 6, 6, 6, 6, 6,                                         6, 6, 6, 6,
                             7, 7, 7, 7, 7,                                               7, 7, 7,
                             8, 8, 8, 8, 8,                                                 8, 8,
                             9, 9, 9, 9, 9,                                                 9, 9,
                            10,10,10,10,                                                      10,
                            11,11,11,11,                                                      11,
                            12,12,12,                                                         
                            13,13,
                            14,14,
                            15};
        drawArray(x_green, sizeof(x_green), y_green, sizeof(y_green), color_green ,0);
    }
    else if(dir == 0) // straight
    {
        int x_green[110] = {0,1,2,3,4,5,6,7,8,9, 22,23,24,25,26,27,28,29,30,31,
                            0,1,2,3,4,5,6,7,8,      23,24,25,26,27,28,29,30,31,
                            0,1,2,3,4,5,6,7,            24,25,26,27,28,29,30,31,
                            0,1,2,3,4,5,6,                25,26,27,28,29,30,31,
                            0,1,2,3,4,5,                     26,27,28,29,30,31,
                            0,1,2,3,4,                          27,28,29,30,31,
                            0,1,2,3,                               28,29,30,31,
                            0,1,2,                                    29,30,31,
                            0,1,                                         30,31,
                            0,                                              31};
        int y_green[110] = {0,0,0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,0,0,
                            1,1,1,1,1,1,1,1,1,        1,1,1,1,1,1,1,1,1,
                            2,2,2,2,2,2,2,2,            2,2,2,2,2,2,2,2,
                            3,3,3,3,3,3,3,                3,3,3,3,3,3,3,
                            4,4,4,4,4,4,                    4,4,4,4,4,4,
                            5,5,5,5,5,                        5,5,5,5,5,
                            6,6,6,6,                            6,6,6,6,
                            7,7,7,                                7,7,7,
                            8,8,                                    8,8,
                            9,                                        9};
        drawArray(x_green, sizeof(x_green), y_green, sizeof(y_green), color_green ,0);
    }
}


// draw the brown gravel
void drawGravel(void)
{
    int x_brown[56] = {0,1,2,3,4,5,6,                  25,26,27,28,29,30,31,
                        0,1,2,3,4,5,                       26,27,28,29,30,31,
                        0,1,2,3,4,                            27,28,29,30,31,
                        0,1,2,3,                                 28,29,30,31,
                        0,1,2,                                      29,30,31,
                        0,1,                                           30,31,
                        0,                                                31};
                       
    int y_brown[56] = {0,0,0,0,0,0,0,                0,0,0,0,0,0,0,
                        1,1,1,1,1,1,                    1,1,1,1,1,1,
                        2,2,2,2,2,                        2,2,2,2,2,
                        3,3,3,3,                            3,3,3,3,
                        4,4,4,                                4,4,4,
                        5,5,                                    5,5,
                        6,                                        6,};

    int color_brown = matrix.Color333(2,1,0);
    drawArray(x_brown, sizeof(x_brown), y_brown, sizeof(y_brown), color_brown, 0);
}

// draw the red car
void drawCar(void)
{
  int x_red[58] = {               15,16,
                   10,11,12,13,14,15,16,17,18,19,20,21,
                                  15,16,
                               14,15,16,17,
                               14,15,16,17,
                               14,15,16,17,
                            13,14,15,16,17,18,
                         12,13,            18,19,
                         12,13,            18,19,
                         12,13,            18,19,
                         12,13,            18,19,
                      11,12,13,            18,19,20};
             
  int y_red[58] = {             4,4,
             5,5,5,5,5,5,5,5,5,5,5,5,
                            6,6,
                         7,7,7,7,
                         8,8,8,8,
                         9,9,9,9,
                      10,10,10,10,10,10,
                   11,11,            11,11,
                   12,12,            12,12,
                   13,13,            13,13,
                   14,14,            14,14,
                15,15,15,            15,15,15};

    int color_red = matrix.Color888(255,0,0);
    
    drawArray(x_red, sizeof(x_red), y_red, sizeof(y_red), color_red, 0);  


}

// draw the driver's helmet and hands, white

void drawDriver(int turn)
{
  int color_white = matrix.Color888(255,255,255);
  
  // going straight
  if (turn == 0)
  {
      int x_white[8] = {14,17,14,17, 15,16,15,16};
      int y_white[8] = {11,11,12,12, 14,14,15,15};

      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white, 0);
  }

  // turning left
  else if (turn == -1)
  {
      int x_white[8] = {16,17,14,15, 15,16,15,16};
      int y_white[8] = {11,11,12,12, 14,14,15,15};

      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white, 0);
  }
  
  // turning right
  else if (turn == 1)
  {
      int x_white[8] = {14,15,16,17, 15,16,15,16};
      int y_white[8] = {11,11,12,12, 14,14,15,15};

      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white, 0);
  }
}

// start the matrix:
void matrixInit(void)
{
    matrix.begin();
    matrix.setTextWrap(false); // Allow text to run off right edge
    matrix.setTextSize(1); // size 1 == 8 pixels high

    randomSeed(analogRead(A0));
}

// clear the screen:
void matrixClearScreen(void)
{
    matrix.fillScreen(0);
}

// update the display, allegedly:
void matrixUpdate(void)
{
    matrix.swapBuffers(false);
}

// draw a series of points with a given color
int drawArray(int xarray[], int size_x, int yarray[], int size_y, int color, int pause)
{
    int x_length = size_x/sizeof(xarray[0]);
    int y_length = size_y/sizeof(yarray[0]);
    
    if (x_length != y_length)
    {
        return 0;
    }

    for (int i = 0 ; i < x_length ; i++)
    {
        matrix.drawPixel(xarray[i], yarray[i], color);
        delay(pause);
    }
    return 1;
}

// draw a single point with a given color
void drawPoint(int x, int y, int color)
{
    matrix.drawPixel(x, y, color);
}
