// TO-DO:
// flip left commands so they work for right hand turns as well
// integrate corner sequence with straight sequence - needs some thinking
// add red/green button to indicate acceleration/braking
// have the driver's hands draw all of the pixels so no clear screen is needed
// add more objects to be markers - maybe just randomize shapes and colors?
// add brake markers close to corners?
//
// LONGER TERM: add lively 'performance' like lockups
//              Randomize driver helmet color/pattern



#include <RGBmatrixPanel.h>
#include <SpeedMarker.h>

#define CLK  11   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2


// randomize the offset?
SpeedMarker markerL(-1,0);
SpeedMarker markerR(1,0);

SpeedMarker markerL1(-1,2);
SpeedMarker markerR1(1,3);

SpeedMarker markerL2(-1,8);
SpeedMarker markerR2(1,7);



RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() 
{
   Serial.begin(9600);
   matrixInit();
}

void loop() 
{
   
   drawStraight();
   //delay(5000);

   //drawLeftTurnSequence();
}

/*
 * Functions
 */

// draw the base image:
void drawStraight(void)
{
   markerL.move();
   markerR.move();
   markerL1.move();
   markerR1.move();
   markerL2.move();
   markerR2.move();

   drawGrass(0);

   drawMarker(markerL);
   drawMarker(markerR);
   drawMarker(markerL1);
   drawMarker(markerR1);
   drawMarker(markerL2);
   drawMarker(markerR2);

   drawRoad(0);
   drawTrackLimits(0);
   
   drawCar();
   drawDriver(0);
   drawTires(0);

   drawPoint(0,0,matrix.Color888(34,139,34));

}

// draw the car approaching a left turn:
void drawLeftTurnSequence(void)
{
   // stage 1:
   drawGrass(0);

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-1);
   
   drawCar();
   drawDriver(0);
   
   //
   delay(100);

   // stage 2:
   drawGrass(0);

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-2);
   
   drawCar();
   drawDriver(0);
   
   //
   delay(150);

   // stage 3:
   drawGrass(0);

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-3);
   
   drawCar();
   drawDriver(0);
   
   //
   delay(200);

   // stage 4: 
   drawGrass(0);

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-4);
   
   drawCar();
   drawDriver(0);
   
   //
   delay(250);

   // stage 5 START CAR + DRIVER TURN: 
   drawGrass(0);

   drawRoad(-1);
   drawTires(-1);
   drawTrackLimits(-5);
   
   drawCar();
   drawDriver(-1);

   //
   delay(450);

   // stage 6 (mid-corner/exit): 
   drawRoad(-1);
   drawTires(-1);
   drawTrackLimits(-6);
   drawGrass(-6);
   
   drawCar();
   drawDriver(-1);

   //
   delay(600);
}

// draw the car turning left on the road:
void drawCarAndRoadTurnLeft(void)
{    
      drawGrass(0);

      drawRoad(-1);
      drawTrackLimits(-5);

      drawCar();
      drawDriver(-1);
      drawTires(-1);
}

// draw the moving speed markers on the side of the road
void drawMarker(SpeedMarker inputMarker)
{
   int x = inputMarker.getX();
   int y = inputMarker.getY();

   int shifter = inputMarker.getSide();

   int x_array[8] = {x, x,   x,   x,   x+shifter, x+shifter, x+shifter, x+shifter};
   int y_array[8] = {y, y-1, y-2, y-3, y,         y-1,       y-2,       y-3,};

   int markerColor = matrix.Color333(2,1,0); // brown

   drawArray(x_array, sizeof(x_array), y_array, sizeof(y_array), markerColor, 0);
}

// draw the road straigh with no gaps for tires
// dir = 0: straight

// dir = -1: first left
// dir = -2: second left
// dir = -3: third left
// dir = -4: fourth left
// dir = -5: fifth left
// dir = -6: mid-corner/exit (experimental)
void drawRoad(int dir)
{
   int color_gray = matrix.Color333(2,2,4);

   // part of the left turn, negative space will come in later to draw the wheels:
   if (dir == -1)
   {
      int x_gray[280] =                     {   12,13,14,15,16,17,18,19,
                                          11,12,13,14,15,16,17,18,19,20,
                                       10,11,12,13,14,15,16,17,18,19,20,21,
                                       9,10,11,12,13,14,15,16,17,18,19,20,21,22,
                                    8, 9,10,11,12,13,14,      17,18,19,20,21,22,23,
                                 7, 8, 9,                                    22,23,24,
                              6, 7, 8, 9,10,11,12,13,14,      17,18,19,20,21,22,23,24,25,
                           5, 6, 7, 8, 9,10,11,12,13,            18,19,20,21,22,23,24,25,26,
                        4, 5, 6, 7, 8, 9,10,11,12,13,            18,19,20,21,22,23,24,25,26,27,
                     3, 4, 5, 6, 7, 8,9,10,11,12,13,             18,19,20,21,22,23,24,25,26,27,28,
                  2, 3, 4, 5, 6, 7, 8, 9,10,11,12,                  19,20,21,22,23,24,25,26,27,28,29,
               1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,                        20,21,22,23,24,25,26,27,28,29,30,31,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,                              21,22,23,24,25,26,27,28,29,30,31};

            
      int y_gray[280] =            {         0, 0, 0, 0, 0, 0, 0, 0, 
                                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                                 4, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4, 4,
                              5, 5, 5,                                     5, 5, 5,
                           6, 6, 6, 6, 6, 6, 6, 6, 6,       6, 6, 6, 6, 6, 6, 6, 6, 6,
                        7, 7, 7, 7, 7, 7, 7, 7, 7,              7, 7, 7, 7, 7, 7, 7, 7, 7,
                     8, 8, 8, 8, 8, 8, 8, 8, 8, 8,              8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,              9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
               10,10,10,10,10,10,10,10,10,10,10,                10,10,10,10,10,10,10,10,10,10,10,
            11,11,11,11,11,11,11,11,11,11,11,                      11,11,11,11,11,11,11,11,11,11,11,
         12,12,12,12,12,12,12,12,12,12,12,12,                      12,12,12,12,12,12,12,12,12,12,12,12,
         13,13,13,13,13,13,13,13,13,13,13,13,                      13,13,13,13,13,13,13,13,13,13,13,13,
         14,14,14,14,14,14,14,14,14,14,14,14,                      14,14,14,14,14,14,14,14,14,14,14,14,
         15,15,15,15,15,15,15,15,15,15,15,                            15,15,15,15,15,15,15,15,15,15,15};

      drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
   }
   
   // fully straight, draw the wheels in to avoid flashing:
   if (dir == 0)
   {
      int x_gray[248] =                     {   12,13,14,15,16,17,18,19,
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

            
      int y_gray[248] =            {         0, 0, 0, 0, 0, 0, 0, 0, 
                                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                                 4, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4, 4,
                              5, 5, 5,                                     5, 5, 5,
                           6, 6, 6, 6, 6, 6, 6, 6, 6,       6, 6, 6, 6, 6, 6, 6, 6, 6,
                        7, 7, 7, 7, 7, 7,                                7, 7, 7, 7, 7, 7,
                     8, 8, 8, 8,                                                  8, 8, 8, 8,
                  9, 9, 9, 9, 9, 9, 9,                                     9, 9, 9, 9, 9, 9, 9,
               10,10,10,10,10,10,10,10,                                    10,10,10,10,10,10,10,10,
            11,11,11,11,11,11,11,11,11,11,11,                      11,11,11,11,11,11,11,11,11,11,11,
         12,12,12,12,12,12,12,12,12,12,12,12,                      12,12,12,12,12,12,12,12,12,12,12,12,
         13,13,13,13,13,13,13,13,13,13,13,13,                      13,13,13,13,13,13,13,13,13,13,13,13,
         14,14,14,14,14,14,14,14,14,14,14,14,                      14,14,14,14,14,14,14,14,14,14,14,14,
         15,15,15,15,15,15,15,15,15,15,15,                            15,15,15,15,15,15,15,15,15,15,15};

      drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
   }
   // second left turn
   else if (dir == -2)
   {

   }

   
}

// draw the blank tires and axle based on which direction we're going. Note tires are drawn in negative space
// left: -1
// straight: 0
// right: 1
void drawTires(int dir)
{
      int color_gray = matrix.Color333(2,2,4);

      // left:
      if (dir == -1)
      {
            int x_blank[29] = {8, 8, 9, 9, 9, 9,10,10,10,10,11,11,12,13,23,23,22,22,22,22,21,21,21,21,20,20,18,19};
            int y_blank[29] = {7, 8, 6, 7, 8, 9, 7, 8, 9,10, 8, 9, 8, 8, 8, 9, 7, 8, 9,10, 6, 7, 8, 9, 7, 8, 8, 8};
            drawArray(x_blank, sizeof(x_blank), y_blank, sizeof(y_blank), 0 ,0);
      }
      
      // straight:
      else if (dir == 0)
      {
         int x_blank[32] = {8, 8, 8, 8, 9, 9, 9, 9,10,10,10,10,11,12,13,11,21,21,21,21,22,22,22,22,23,23,23,23,18,19,20,20};
         int y_blank[32] = {7, 8, 9,10, 7, 8, 9,10, 7, 8, 9,10, 8, 8, 8, 9, 7, 8, 9,10, 7, 8, 9,10, 7, 8, 9,10, 8, 8, 8, 9};
         drawArray(x_blank, sizeof(x_blank), y_blank, sizeof(y_blank), 0 ,0);
      }

      // right:
      else if (dir == 1)
      {
            /*int x_gray[] = {

            };

            int y_gray[] = {

            };*/
      }
}

// draw the white track limits
// dir = 0: straight

// dir = -11: left curve
// dir = -1: first left
// dir = -2: second left
// dir = -3: third left
// dir = -4: fourth left
// dir = -5: fifth left
// dir = -6: mid-corner/exit (experimental)
void drawTrackLimits(int dir)
{
  int color_white = matrix.Color888(255,255,255);
  int color_gray = matrix.Color333(2,2,4);
  
  // left curve
  if (dir == -11) 
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

  // left 1
  else if (dir == -1)
  {
      int x_white[75] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                          0,1,2,3,4,5,6,7,8,9,21,22,
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
                         
      int y_white[75] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         1,1,1,1,1,1,1,1,1,1,1,1,
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
       
       // account for the extra spot of road that we've uncovered:
       drawPoint(10,1,color_gray);
  }

  // left 2
  else if (dir == -2)
  {
      int x_white[71] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                          21,22,
                          0,1,2,3,4,5,6,7,22,23,
                          7, 8,23,24,
                          6, 7,24,25,
                          5, 6,25,26,
                          4, 5,26,27,
                          3, 4,27,28,
                          2, 3,28,29,
                          1, 2,29,30,
                          0,1, 30,31,
                          31};
                         
      int y_white[71] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         1,1,
                         2,2,2,2,2,2,2,2,2,2,
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

       // adding the new space to the road:
       int x_gray[13] = {0,1,2,3,4,5,6,7,8,9,10,8,9};
       int y_gray[13] = {1,1,1,1,1,1,1,1,1,1,1, 2,2};
       drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
  }

   // left 3
  else if (dir == -3)
  {
      int x_white[70] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                          21,22,
                          22,23,
                          0,1,2,3,4,5,6,7, 23,24,
                          6, 7,24,25,
                          5, 6,25,26,
                          4, 5,26,27,
                          3, 4,27,28,
                          2, 3,28,29,
                          1, 2,29,30,
                          0,1, 30,31,
                          31};
                         
      int y_white[70] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         1,1,
                         2,2,
                         3,3,3,3,3,3,3,3,3,3,
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

       // adding the new space to the road:
       int x_gray[22] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 8};
       int y_gray[22] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3};
       drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
  }

  // left 4
  else if (dir == -4)
  {
      int x_white[68] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                          21,22,
                          22,23,
                          23,24,
                          0,1,2,3,4,5,6,7, 24,25,
                          5, 6,25,26,
                          4, 5,26,27,
                          3, 4,27,28,
                          2, 3,28,29,
                          1, 2,29,30,
                          0,1, 30,31,
                          31};
                         
      int y_white[68] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         1,1,
                         2,2,
                         3,3,
                         4,4,4,4,4,4,4,4,4,4,
                         5,5,5,5,
                         6,6,6,6,
                         7,7,7,7,
                         8,8,8,8,
                         9,9,9,9,
                         10,10,10,10,
                         11,11,11,11,
                         12};
       drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

       // adding the new space to the road:
       int x_gray[31] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8, 7};
       int y_gray[31] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 4};
       drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
  }

  // left 5
  else if (dir == -5)
  {
      int x_white[63] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                          21,22,
                          22,23,
                          23,24,
                          24,25,
                          25,26,
                          0,1,2,3,4, 5,26,27,
                          3, 4,27,28,
                          2, 3,28,29,
                          1, 2,29,30,
                          0,1, 30,31,
                          31};
                         
      int y_white[63] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         1,1,
                         2,2,
                         3,3,
                         4,4,
                         5,5,
                         6,6,6,6,6,6,6,6,
                         7,7,7,7,
                         8,8,8,8,
                         9,9,9,9,
                         10,10,10,10,
                         11,11,11,11,
                         12};
       drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

       // adding the new space to the road:
       int x_gray[48] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8, 0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7, 5};
       int y_gray[48] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4, 5,5,5,5,5,5,5,5, 6};
       drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
  }

  // mid-corner/exit
  else if (dir == -6) 
  {
      int x_white[59] = { 20,21,
                          21,22,
                          0,22,23,
                          0, 1,23,24,
                             1, 2,24,25,
                                2, 3,25,26,
                                   3, 4,26,27,
                                      4, 5,27,28,
                                         5, 6,28,29,
                                         5, 6,28,29,
                                         5, 6,28,29,
                                      4, 5,27,28,
                                      4, 5,26,27,
                                   3, 4,26,27,
                                   3, 4,26,27,
                                2, 3,25,26};
                         
      int y_white[59] = {0, 0,
                         1, 1,
                         2, 2, 2,
                         3, 3, 3, 3,
                         4, 4, 4, 4,
                         5, 5, 5, 5,
                         6, 6, 6, 6,
                         7, 7, 7, 7,
                         8, 8, 8, 8,
                         9, 9, 9, 9,
                         10,10,10,10,
                         11,11,11,11,
                         12,12,12,12,
                         13,13,13,13,
                         14,14,14,14,
                         15,15,15,15};

      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

      // adding the new space to the road:
      int x_gray[48] = {0,1,2,3,4,5,6,7,8,9,10,11, 0,1,2,3,4,5,6,7,8,9,10,  1,2,3,4,5,6,7,8,9, 2,3,4,5,6,7,8, 3,4,5,6,7, 4,5,6, 5};
      int y_gray[48] = {0,0,0,0,0,0,0,0,0,0, 0, 0, 1,1,1,1,1,1,1,1,1,1, 1,  2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3, 4,4,4,4,4, 5,5,5, 6};
      drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
  }
  
  // straight
  else if (dir == 0) 
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
// left curve: dir = -11
// left (mid-corner/exit): dir = -1
// straight: dir = 0
// right: dir = 1
void drawGrass(int dir)
{
    int color_green = matrix.Color888(34,139,34);
   
   // left curve
    if (dir == -11) 
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

    // straight
    else if(dir == 0) 
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
    
    // left (mid-corner/exit)
    else if(dir == -6) 
    {
        int x_green[119] = {                     22,23,24,25,26,27,28,29,30,31,
                                                    23,24,25,26,27,28,29,30,31,
                                                       24,25,26,27,28,29,30,31,
                                                          25,26,27,28,29,30,31,
                            0,                               26,27,28,29,30,31,
                            0,1,                                27,28,29,30,31,
                            0,1,2,                                 28,29,30,31,
                            0,1,2,3,                                  29,30,31,
                            0,1,2,3,4,                                   30,31,
                            0,1,2,3,4,                                   30,31,
                            0,1,2,3,4,                                   30,31,
                            0,1,2,3,                                  29,30,31,
                            0,1,2,3,                               28,29,30,31,
                            0,1,2,                                 28,29,30,31,
                            0,1,2,                                 28,29,30,31,
                            0,1,                                27,28,29,30,31};

        int y_green[119] = {0,0,0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1,1,
                           2,2,2,2,2,2,2,2,
                           3,3,3,3,3,3,3,
                           4,4,4,4,4,4,4,
                           5,5,5,5,5,5,5,
                           6,6,6,6,6,6,6,
                           7,7,7,7,7,7,7,
                           8,8,8,8,8,8,8,
                           9,9,9,9,9,9,9,
                           10,10,10,10,10,10,10,
                           11,11,11,11,11,11,11,
                           12,12,12,12,12,12,12,12,
                           13,13,13,13,13,13,13,
                           14,14,14,14,14,14,14,
                           15,15,15,15,15,15,15};
        drawArray(x_green, sizeof(x_green), y_green, sizeof(y_green), color_green ,0);
    }
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

      int x_black[4] = {15,16,15,16};
      int y_black[4] = {11,11,12,12};

      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white, 0);
      drawArray(x_black, sizeof(x_black), y_black, sizeof(y_black), 0, 0);
  }

  // turning left
  else if (turn == -1)
  {
      int x_white[8] = {16,17,14,15, 15,16,15,16};
      int y_white[8] = {11,11,12,12, 14,14,15,15};

      int x_black[4] = {14,15,16,17};
      int y_black[4] = {11,11,12,12};

      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white, 0);
      drawArray(x_black, sizeof(x_black), y_black, sizeof(y_black), 0, 0);
  }
  
  // turning right
  else if (turn == 1)
  {
      int x_white[8] = {14,15,16,17, 15,16,15,16};
      int y_white[8] = {11,11,12,12, 14,14,15,15};

      int x_black[4] = {14,15,16,17};
      int y_black[4] = {12,12,11,11};

      drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white, 0);
      drawArray(x_black, sizeof(x_black), y_black, sizeof(y_black), 0, 0);
  }
}

// EXPERIMENTAL
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

// EXPERIMENTAL:
// draw the gray-blue road surface for a left curve 
// left: -1
// straight: 0
// right: 1
void drawLeftCurve(int road, int tire)
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
