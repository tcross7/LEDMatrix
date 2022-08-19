// TO-DO:
// randomize color shapes - needs some figuring out
// Add start lights
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

// VARIABLES
int x_green_mc3[115] = {0,1,2,3,4,5,6,7,8,9, 20,21,22,23,24,25,26,27,28,29,30,31,
                     0,1,2,3,4,5,6,7,8,      21,22,23,24,25,26,27,28,29,30,31,
                     0,1,2,3,4,5,6,7,              23,24,25,26,27,28,29,30,31,
                     0,1,2,3,4,5,6,                      25,26,27,28,29,30,31,
                     0,1,2,3,4,5,                           26,27,28,29,30,31,
                     0,1,2,3,4,                                27,28,29,30,31,
                     0,1,2,3,                                     28,29,30,31,
                     0,1,2,                                          29,30,31,
                     0,1,                                               30,31,
                     0,                                                    31};
int y_green_mc3[115] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                     1,1,1,1,1,1,1,1,1,    1,1,1,1,1,1,1,1,1,1,1,
                     2,2,2,2,2,2,2,2,          2,2,2,2,2,2,2,2,2,
                     3,3,3,3,3,3,3,                3,3,3,3,3,3,3,
                     4,4,4,4,4,4,                    4,4,4,4,4,4,
                     5,5,5,5,5,                        5,5,5,5,5,
                     6,6,6,6,                            6,6,6,6,
                     7,7,7,                                7,7,7,
                     8,8,                                    8,8,
                     9,                                        9};

int x_green_mc2[66] ={0,1,               21,22,23,24,25,26,27,28,29,30,31,
                  0,1,                     23,24,25,26,27,28,29,30,31,
                  0,1,2,                         25,26,27,28,29,30,31,
                  0,1,2,                               27,28,29,30,31,
                  0,1,2,                               27,28,29,30,31,
                  0,1,2,                                     29,30,31,
                  0,1,                                             31,
                  0,1,                                             31,
                  0,1,
                  0,
                  0};

int y_green_mc2[66] = {0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,1,1,1,1,1,1,1,1,1,1,
               2,2,2,2,2,2,2,2,2,2,
               3,3,3,3,3,3,3,3,
               4,4,4,4,4,4,4,4,
               5,5,5,5,5,5,
               6,6,6,
               7,7,7,
               8,8,
               9};

int x_green_mc1[54] = {            19,20,21,22,23,24,25,26,27,28,29,30,31,
                                          23,24,25,26,27,28,29,30,31,
                                                25,26,27,28,29,30,31,
                                                      27,28,29,30,31,
                                                               30,31,
                     0,
                     0,1,
                     0,1,2,
                     0,1,2,
                     0,1,2,
                     0,1,
                     0,1,
                     0,
                     0};

int y_green_mc1[54] = {0,0,0,0,0,0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1,1,
                  2,2,2,2,2,2,2,
                  3,3,3,3,3,
                  4,4,
                  5,
                  6,6,
                  7,7,7,
                  8,8,8,
                  9,9,9,
                  10,10,
                  11,11,
                  12,
                  13};




// randomize the offset?
SpeedMarker markerL(-1,0);
SpeedMarker markerL1(-1,4);
//SpeedMarker markerL2(-1,8);

SpeedMarker markerR(1,2);
SpeedMarker markerR1(1,6);
//SpeedMarker markerR2(1,8);



RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() 
{
   matrixInit();
}

void loop() 
{
   drawCircuit();
}

// draw a pre-determined pattern that represents a single circuit
// Possibly randomize this in the future?
void drawCircuit()
{
   int initial_time = millis();
   int count = millis() - initial_time; // current_time - initial_time

   while (count < 30000) // 30 second lap
   {
      count = millis() - initial_time;
      
      // 8 second straight
      if (count < 8000)
      {
         drawStraight();
      }
      
      // turn left
      else if ((count >= 8000) && (count < 10100))
      {
         drawLeftTurnSequence();
      }

      // ~12 second straight
      else if ((count >= 10100) && (count < 22000))
      {
         drawStraight();
      }

      // turn right
      else if ((count >= 22000) && (count < 24100))
      {
         drawRightTurnSequence();
      }

      // ~2 second straight
      else if ((count >= 24100) && (count < 26000))
      {
         drawStraight();
      }
      
      // turn left
      else if ((count >= 26000) && (count < 28100))
      {
         drawLeftTurnSequence();
      }

      // straight until the end of the timer
      else if (count >= 28100)
      {
         drawStraight();
      } 
   }
}

/*
 * Functions
 */

// draw the base image:
void drawStraight(void)
{
   
   moveLeftMarkers();
   moveRightMarkers();   

   drawGrass(1, 0);

   drawLeftMarkers();
   drawRightMarkers();   

   drawRoad(0);
   drawTrackLimits(0,0);
   
   drawCar();
   drawDriver(0,1);
   drawTires(0);

   drawPoint(0,0,matrix.Color888(34,139,34));

}

// draw the car approaching a left turn
// currently 2100 milliseconds total
void drawLeftTurnSequence(void)
{
  drawLeftStage1(100);
   drawLeftStage2(150);
   drawLeftStage3(200);
   drawLeftStage4(250);
   drawLeftStage5(400);

   drawLeftStage6(400);
   drawLeftStage7(350);
   drawLeftStage8(250);
}

// draw the car approaching a right turn
// currently 2100 milliseconds total
void drawRightTurnSequence(void)
{

   drawRightStage1(100);
   drawRightStage2(150);
   drawRightStage3(200);
   drawRightStage4(250);
   drawRightStage5(400);

   drawRightStage6(400);
   drawRightStage7(350);
   drawRightStage8(250);
}

void moveRightMarkers()
{
   markerR.move();
   markerR1.move();
   //markerR2.move();
}

void drawRightMarkers()
{
   drawMarker(markerR);
   drawMarker(markerR1);
   //drawMarker(markerR2);
}

void moveLeftMarkers()
{
   markerL.move();
   markerL1.move();
   //markerL2.move();
}

void drawLeftMarkers()
{
   drawMarker(markerL);
   drawMarker(markerL1);
   //drawMarker(markerL2);
}

// Left stage 1 - approach
void drawLeftStage1(int pause_length)
{   
   moveRightMarkers();
   drawGrass(-1, 0);

   drawRightMarkers();
   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-1,1);
   
   drawCar();
   drawDriver(0,0);

   drawPoint(0,0,matrix.Color888(255,255,255));   
   
   delay(pause_length);
}

// Left stage 2 - approach
void drawLeftStage2(int pause_length)
{
   moveRightMarkers();
   drawGrass(-1, 0);

   drawRightMarkers();

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-1,2);
   
   drawCar();
   drawDriver(0,0);
   
   drawPoint(0,0,matrix.Color888(255,255,255));  
   //
   delay(pause_length);

}
// Left stage 3 - approach
void drawLeftStage3(int pause_length)
{
   moveRightMarkers();
   drawGrass(-1, 0);

   drawRightMarkers();

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-1,3);
   
   drawCar();
   drawDriver(0,0);
   
   drawPoint(0,0,matrix.Color888(255,255,255));  
   
   delay(pause_length);
}

// Left stage 4 - approach
void drawLeftStage4(int pause_length)
{
   moveRightMarkers();
   drawGrass(-1, 0);

   drawRightMarkers();

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(-1,4);
   
   drawCar();
   drawDriver(0,0);
   
   drawPoint(0,0,matrix.Color888(255,255,255));  
   //
   delay(pause_length);
}

// Left stage 5 - approach
void drawLeftStage5(int pause_length)
{
   // START CAR + DRIVER TURN: 

   moveRightMarkers();
   drawGrass(-1, 0);

   drawRightMarkers();

   drawRoad(-1);
   drawTires(-1);
   drawTrackLimits(-1,5);
   
   drawCar();
   drawDriver(-1,0);

   drawPoint(0,0,matrix.Color888(255,255,255));  
   
   delay(pause_length);
}

// Left stage 6 - mid-corner 1
void drawLeftStage6(int pause_length)
{
   // mid-corner/exit: 
   drawRoad(-1);
   drawTires(-1);
   drawTrackLimits(-1, 6);
   drawGrass(-1, 6);
   
   drawCar();
   drawDriver(-1,0);

   drawPoint(0,0,matrix.Color333(2,2,4));
   
   delay(pause_length);
}

// Left stage 7 - mid-corner 2
void drawLeftStage7(int pause_length)
{
   // mid-corner
   drawRoad(-1);
   drawTires(-1);
   drawTrackLimits(-1, 7);
   drawGrass(-1, 7);
   
   drawCar();
   drawDriver(-1,0);

   drawPoint(0,0,matrix.Color888(34,139,34));  //top left and top right pixels neec to be green here
   drawPoint(31,0,matrix.Color888(34,139,34));
   
   delay(pause_length);
}

// Left stage 8 - mid-corner 3 / exit
void drawLeftStage8(int pause_length)
{
   drawRoad(-1);
   drawTires(-1);
   drawGrass(-1, 8);
   drawTrackLimits(-1, 8);
   
   drawCar();
   drawDriver(-1,0);

   drawPoint(0,0,matrix.Color888(34,139,34));  
   
   delay(pause_length);
}

// Right stage 1 - approach
void drawRightStage1(int pause_length)
{
   moveLeftMarkers();
   drawGrass(1, 0);

   drawLeftMarkers();

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(1,1);
   
   drawCar();
   drawDriver(0,0);

   drawPoint(0,0,matrix.Color888(34,139,34)); // draw 0,0 pixel green
   
   delay(pause_length);
}

// Right stage 2 - approach
void drawRightStage2(int pause_length)
{
   moveLeftMarkers();
   drawGrass(1, 0);

   drawLeftMarkers();

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(1,2);
   
   drawCar();
   drawDriver(0,0);
   
   drawPoint(0,0,matrix.Color888(34,139,34));   
   
   delay(pause_length);
}

// Right stage 3 - approach
void drawRightStage3(int pause_length)
{
   moveLeftMarkers();
   drawGrass(1, 0);

   drawLeftMarkers();

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(1,3);
   
   drawCar();
   drawDriver(0,0);
   
   drawPoint(0,0,matrix.Color888(34,139,34));   
   
   delay(pause_length);
}

// Right stage 4 - approach
void drawRightStage4(int pause_length)
{
   moveLeftMarkers();
   drawGrass(1, 0);

   drawLeftMarkers();

   drawRoad(0);
   drawTires(0);
   drawTrackLimits(1,4);
   
   drawCar();
   drawDriver(0,0);
   
   drawPoint(0,0,matrix.Color888(34,139,34));    
   
   delay(pause_length);
}

// Right stage 5 - approach
void drawRightStage5(int pause_length)
{
   // START CAR + DRIVER TURN: 
   moveLeftMarkers();
   drawGrass(1, 0);

   drawLeftMarkers();

   drawRoad(1);
   drawTires(1);
   drawTrackLimits(1,5);
   
   drawCar();
   drawDriver(1,0);

   drawPoint(0,0,matrix.Color888(34,139,34));  
   
   delay(pause_length);
}

// Right stage 6 - mid-corner 1
void drawRightStage6(int pause_length)
{
   // mid-corner/exit: 
   drawRoad(1);
   drawTires(1);
   drawTrackLimits(1,6);
   drawGrass(1, 6);
   
   drawCar();
   drawDriver(1,0);

   drawPoint(0,0,matrix.Color888(34,139,34));  
   
   delay(pause_length);
}

// Right stage 7 - mid-corner 2
void drawRightStage7(int pause_length)
{
   // mid-corner/exit: 
   drawRoad(1);
   drawTires(1);
   drawTrackLimits(1,7);
   drawGrass(1, 7);
   
   drawCar();
   drawDriver(1,0);

   drawPoint(0,0,matrix.Color888(34,139,34));  
   
   delay(pause_length);
}

// Right stage 8 - mid-corner 3 / exit
void drawRightStage8(int pause_length)
{
   // mid-corner/exit: 
   drawRoad(1);
   drawTires(1);
   drawTrackLimits(1,8);
   drawGrass(1, 8);
   
   drawCar();
   drawDriver(1,0);

   drawPoint(0,0,matrix.Color888(34,139,34));  
   
   delay(pause_length);
}

////

// draw the moving speed markers on the side of the road
void drawMarker(SpeedMarker inputMarker)
{
   int x = inputMarker.getX();
   int y = inputMarker.getY();

   int shifter = inputMarker.getSide();

   int x_array[8] = {x, x,   x,   x,   x+shifter, x+shifter, x+shifter, x+shifter};
   int y_array[8] = {y, y-1, y-2, y-3, y,         y-1,       y-2,       y-3,};

   int markerColor = inputMarker.getColor();

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

   // part of the left/right turn, negative space will come in later to draw the wheels:
   if (dir == -1 || dir == 1)
   {
      int x_gray[280] =                     {12,13,14,15,16,17,18,19,
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
         int x_blank[29] = {8, 8, 9, 9, 9, 9,10,10,10,10,11,11,12,13,23,23,22,22,22,22,21,21,21,21,20,20,18,19};
         int y_blank[29] = {7, 8, 6, 7, 8, 9, 7, 8, 9,10, 8, 9, 8, 8, 8, 9, 7, 8, 9,10, 6, 7, 8, 9, 7, 8, 8, 8};
         drawArrayHFlip(x_blank, sizeof(x_blank), y_blank, sizeof(y_blank), 0 ,0);
      }
}

// draw the white track limits
// dir = -1: left
// dir = 0: straight
// dir = 1: right

// stage = 0: straight
// stage = 1: approaching turn first
// stage = 2: approaching turn second
// stage = 3: approaching turn third
// stage = 4: approaching turn fourth
// stage = 5: approaching turn fifth
// stage = 6: mid-corner first
// stage = 7: mid-corner second
// stage = 8: mid-corner third/exit
void drawTrackLimits(int dir, int stage)
{
  int color_white = matrix.Color888(255,255,255);
  int color_gray = matrix.Color333(2,2,4);
  
  // 1
  if (stage == 1)
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

      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // account for the extra spot of road that we've uncovered:
         drawPoint(10,1,color_gray);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // account for the extra spot of road that we've uncovered:
         drawPoint(21,1,color_gray);
      }
  }

  // 2
  else if (stage == 2)
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


      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // adding the new space to the road:
         int x_gray[13] = {0,1,2,3,4,5,6,7,8,9,10,8,9};
         int y_gray[13] = {1,1,1,1,1,1,1,1,1,1,1, 2,2};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // adding the new space to the road:
         int x_gray[13] = {0,1,2,3,4,5,6,7,8,9,10,8,9};
         int y_gray[13] = {1,1,1,1,1,1,1,1,1,1,1, 2,2};
         drawArrayHFlip(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }
  }

   // 3
  else if (stage == 3)
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

      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // adding the new space to the road:
         int x_gray[22] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 8};
         int y_gray[22] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // adding the new space to the road:
         int x_gray[22] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 8};
         int y_gray[22] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3};
         drawArrayHFlip(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

  }

  // 4
  else if (stage == 4)
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

      
      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // adding the new space to the road:
         int x_gray[31] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8, 7};
         int y_gray[31] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 4};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // adding the new space to the road:
         int x_gray[31] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8, 7};
         int y_gray[31] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 4};
         drawArrayHFlip(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }
  }

  // 5
  else if (stage == 5)
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

      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // adding the new space to the road:
         int x_gray[48] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8, 0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7, 5};
         int y_gray[48] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4, 5,5,5,5,5,5,5,5, 6};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // adding the new space to the road:
         int x_gray[48] = {0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8, 0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7, 5};
         int y_gray[48] = {1,1,1,1,1,1,1,1,1,1,1,  2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4, 5,5,5,5,5,5,5,5, 6};
         drawArrayHFlip(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }
  }

  // mid-corner 1
  else if (stage == 6) 
  {
      int x_white[39] = {13,14,15,16,17,18,
                        19,20,21,22,
                        22,23,24,
                        24,25,26,
                        0,1,26,27,28,29,
                        1,2,29,30,31,
                        2,3,31,
                        3,
                        3,
                        3,
                        2,
                        2,
                        1,
                        1,
                        0,
                        0};
                         
      int y_white[39] = {0,0,0,0,0,0,
                        1,1,1,1,
                        2,2,2,
                        3,3,3,
                        4,4,4,4,4,4,
                        5,5,5,5,5,
                        6,6,6,
                        7,8,9,10,11,12,13,14,15};
                        
      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // adding the new space to the road:
         int x_gray[83] = {0,1,2,3,4,5,6,7,8,9,10,11, 0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8,23, 2,3,4,5,6,7,24,25, 3,4,5,6,7,25,26,27,28, 4,5,26,27,28,29,30, 4,27,28,29,30,31, 28,29,30,31, 29,30,31, 30,31, 31};
         int y_gray[83] = {0,0,0,0,0,0,0,0,0,0, 0, 0, 1,1,1,1,1,1,1,1,1,1, 1, 2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 3, 4,4,4,4,4,4, 4, 4, 5,5,5,5,5, 5, 5, 5, 5, 6,6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7,  8, 8, 8, 8,  9, 9, 9, 10,10, 11};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // adding the new space to the road:
         int x_gray[83] = {0,1,2,3,4,5,6,7,8,9,10,11, 0,1,2,3,4,5,6,7,8,9,10, 0,1,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8,23, 2,3,4,5,6,7,24,25, 3,4,5,6,7,25,26,27,28, 4,5,26,27,28,29,30, 4,27,28,29,30,31, 28,29,30,31, 29,30,31, 30,31, 31};
         int y_gray[83] = {0,0,0,0,0,0,0,0,0,0, 0, 0, 1,1,1,1,1,1,1,1,1,1, 1, 2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,3, 3, 4,4,4,4,4,4, 4, 4, 5,5,5,5,5, 5, 5, 5, 5, 6,6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7,  8, 8, 8, 8,  9, 9, 9, 10,10, 11};
         drawArrayHFlip(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }
  }
  
  // mid-corner 2
  else if (stage == 7) 
  {
      int x_white[35] = {2,18,19,20,
                        2,20,21,22,
                        3,22,23,24,
                        3,24,25,26,
                        3,26,27,28,
                        2,28,29,30,
                        2,30,
                        2,30,31,
                        1,31,
                        1,31,
                        0,
                        0
                        };
                         
      int y_white[35] = {0,0,0,0,
                        1,1,1,1,
                        2,2,2,2,
                        3,3,3,3,
                        4,4,4,4,
                        5,5,5,5,
                        6,6,
                        7,7,7,
                        8,8,
                        9,9,
                        10,
                        11};
                        
      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // adding the new space to the road:
         int x_gray[67] = {  3,4,5,6,7,8,9,10,11,
                             3,4,5,6,7,8,9,10,
                               4,5,6,7,8,9,
                               4,5,6,7,8,             23,
                               4,5,6,7,                  24,25,
                             3,4,5,6,7,                     25,26,27,
                             3,4,5,                            26,27,28,29,
                             3,4,                                 27,28,29,
                           2,3,                                      28,29,30,
                           2,                                           29,30,
                           1,                                              30,31,
                                                                              31};
         int y_gray[67] = {0,0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1,
                           2,2,2,2,2,2,
                           3,3,3,3,3,3,
                           4,4,4,4,4,4,
                           5,5,5,5,5,5,5,5,
                           6,6,6,6,6,6,6,
                           7,7,7,7,7,
                           8,8,8,8,8,
                           9,9,9,
                           10,10,10,
                           11};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // adding the new space to the road:
         int x_gray[67] = {  3,4,5,6,7,8,9,10,11,
                             3,4,5,6,7,8,9,10,
                               4,5,6,7,8,9,
                               4,5,6,7,8,             23,
                               4,5,6,7,                  24,25,
                             3,4,5,6,7,                     25,26,27,
                             3,4,5,                            26,27,28,29,
                             3,4,                                 27,28,29,
                           2,3,                                      28,29,30,
                           2,                                           29,30,
                           1,                                              30,31,
                                                                              31};
         int y_gray[67] = {0,0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1,
                           2,2,2,2,2,2,
                           3,3,3,3,3,3,
                           4,4,4,4,4,4,
                           5,5,5,5,5,5,5,5,
                           6,6,6,6,6,6,6,
                           7,7,7,7,7,
                           8,8,8,8,8,
                           9,9,9,
                           10,10,10,
                           11};
         drawArrayHFlip(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }
  }

  // mid-corner 3 / exit
  else if (stage == 8) 
  {
      int x_white[26] = {5, 18,19,
                         4, 19,20,
                         4, 21,22,
                         3, 23,24,
                         3, 25,
                         2, 26,
                         2, 27,28,
                         1, 29,30,
                         1, 31,
                         0,
                         0};
                         
      int y_white[26] = {0,0,0,
                        1,1,1,
                        2,2,2,
                        3,3,3,
                        4,4,
                        5,5,
                        6,6,6,
                        7,7,7,
                        8,8,
                        9,
                        10};
                        
      // left
      if (dir == -1)
      {
         drawArray(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);
         
         // adding the new space to the road:
         int x_gray[57] = {6,7,8,9,10,11,
                           5,6,7,8,9,10,
                           5,6,7,8,9,
                           4,5,6,7,8,
                           4,5,6,7, 24,
                           3,4,5,6, 25,
                           3,4,5, 26,
                           2,3,4, 27,28,
                           2,3, 28,29,30,
                           1,2,3, 29,30,31,
                           1, 30,31,
                           0, 31};
         int y_gray[57] = {0,0,0,0,0,0,
                           1,1,1,1,1,1,
                           2,2,2,2,2,
                           3,3,3,3,3,
                           4,4,4,4,4,
                           5,5,5,5,5,
                           6,6,6,6,
                           7,7,7,7,7,
                           8,8,8,8,8,
                           9,9,9,9,9,9,
                           10,10,10,
                           11,11};
         drawArray(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }

      // right
      else if (dir == 1)
      {
         drawArrayHFlip(x_white, sizeof(x_white), y_white, sizeof(y_white), color_white ,0);

         // adding the new space to the road:
         int x_gray[57] = {6,7,8,9,10,11,
                           5,6,7,8,9,10,
                           5,6,7,8,9,
                           4,5,6,7,8,
                           4,5,6,7, 24,
                           3,4,5,6, 25,
                           3,4,5, 26,
                           2,3,4, 27,28,
                           2,3, 28,29,30,
                           1,2,3, 29,30,31,
                           1, 30,31,
                           0, 31};
         int y_gray[57] = {0,0,0,0,0,0,
                           1,1,1,1,1,1,
                           2,2,2,2,2,
                           3,3,3,3,3,
                           4,4,4,4,4,
                           5,5,5,5,5,
                           6,6,6,6,
                           7,7,7,7,7,
                           8,8,8,8,8,
                           9,9,9,9,9,9,
                           10,10,10,
                           11,11};
            drawArrayHFlip(x_gray, sizeof(x_gray), y_gray, sizeof(y_gray), color_gray ,0);
      }
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
}

// draw the green grass
// left: dir = -1
// right: dir = 1
//
// mid-corner 1: stage = 6
// mid-corner 2: stage = 7
// mid-corner 3 / exit: stage = 8
// straight: stage = 0
void drawGrass(int dir, int stage)
{
    int color_green = matrix.Color888(34,139,34);

    // straight, all approaching turns, and mid-corner 3 / exit
    if(stage == 0) 
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
    
    // mid-corner 1
    else if(stage == 6) 
    {
        // left                           
        if (dir == -1)
        {
            drawArray(x_green_mc1, sizeof(x_green_mc1), y_green_mc1, sizeof(y_green_mc1), color_green ,0);
        }
        // right
        else if (dir == 1)
        {
            drawArrayHFlip(x_green_mc1, sizeof(x_green_mc1), y_green_mc1, sizeof(y_green_mc1), color_green ,0);
        }
    }

    // mid-corner 2
    else if(stage == 7) 
    {     
      // left                           
        if (dir == -1)
        {

            drawArray(x_green_mc2, sizeof(x_green_mc2), y_green_mc2, sizeof(y_green_mc2), color_green ,0);
        }
        // right
        else if (dir == 1)
        {
            drawArrayHFlip(x_green_mc2, sizeof(x_green_mc2), y_green_mc2, sizeof(y_green_mc2), color_green ,0);
        }
    }
   
   // mid-corner 3 / exit
    else if(stage == 8) 
    {     
      // left                           
        if (dir == -1)
        {
            drawArray(x_green_mc3, sizeof(x_green_mc3), y_green_mc3, sizeof(y_green_mc3), color_green ,0);
        }
        // right
        else if (dir == 1)
        {
            drawArrayHFlip(x_green_mc3, sizeof(x_green_mc3), y_green_mc3, sizeof(y_green_mc3), color_green ,0);
        }
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
// turn = -1: left
// turn = 0: straight | accel = 1: green light, accel = 0: red light
// turn = 1: right
void drawDriver(int turn, int accel)
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
      if (accel == 1)
      {
         drawPoint(15,12, matrix.Color888(0,255,0));
         drawPoint(16,12, matrix.Color888(0,255,0));
      }
      else if (accel == 0)
      {
         drawPoint(15,12, matrix.Color888(255,0,0));
         drawPoint(16,12, matrix.Color888(255,0,0));
      }
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

/*void draw_logo(void)
{
   int x_dig[18] = {0,1,2,2,2,2,3,4,5,5,5,5,6,7,8,8,8,8};
   int y_dig[18] = {8,8,8,7,6,5,5,5,5,6,7,8,8,8,8,7,6,5};

   int x_t[9] = {9,10,11,12,13,11,11,11,11};
   int y_t[9] = {5,5,5,5,5,4,6,7,8};

   int x_x[8] = {14,15,16,17,17,16,15,14};
   int y_x[8] = {5,6,7,8,5,6,7,8};

   int x_ana[14] = {18,19,20,21,22,23,24,25,26,27,28,29,30,31};
   int y_ana[14] = {4,4,5,7,8,8,7,5,4,5,7,8,8,7};


   drawArray(x_dig, sizeof(x_dig), y_dig, sizeof(y_dig), matrix.Color888(255,255,255), 100);
   drawArray(x_t, sizeof(x_t), y_t, sizeof(y_t), matrix.Color888(33,150,243), 100);
   drawArray(x_x, sizeof(x_x), y_x, sizeof(y_x), matrix.Color888(255,255,0), 100);
   drawArray(x_ana, sizeof(x_ana), y_ana, sizeof(y_ana), matrix.Color888(255,255,255), 100); 
   
   delay(3000);
   matrixClearScreen();
}*/

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

// draw a series of points with a given color, flipped across the y axis (horizontally)
int drawArrayHFlip(int xarray[], int size_x, int yarray[], int size_y, int color, int pause)
{
    int x_length = size_x/sizeof(xarray[0]);
    int y_length = size_y/sizeof(yarray[0]);
    
    if (x_length != y_length)
    {
        return 0;
    }

    for (int i = 0 ; i < x_length ; i++)
    {
      int drawX = (-1*xarray[i]) + 31;
      matrix.drawPixel(drawX, yarray[i], color);
      delay(pause);
    }
    return 1;
}

// draw a single point with a given color
void drawPoint(int x, int y, int color)
{
    matrix.drawPixel(x, y, color);
}
