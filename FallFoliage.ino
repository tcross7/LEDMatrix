#include <Leaves.h>
#include <Arduino.h>
#include <RGBmatrixPanel.h>

#define CLK  11   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

int timeScaler = 200000; // change this to stretch out or shorten the sequence
//With this at 200,000 the shortest possible time is 3:20, and the longest 116 minutes
// figure out timeframe desired to do this - a couple hours? A day? A week?

// create 30 leaf triads here:
Leaves leaf1(timeScaler*random(1,4), 5,5, 22,2, 0,7);
Leaves leaf2(timeScaler*random(2,5), 0,3, 23,2, 0,8);
Leaves leaf3(timeScaler*random(3,6), 2,4, 18,3, 19,6);
Leaves leaf4(timeScaler*random(4,7), 1,6, 22,7, 20,8);
Leaves leaf5(timeScaler*random(5,8), 4,7, 2,3, 20,1);
Leaves leaf6(timeScaler*random(6,9), 20,6, 4,2, 4,8);
Leaves leaf7(timeScaler*random(7,10), 3,5, 20,4, 1,7);
Leaves leaf8(timeScaler*random(8,11), 3,6, 2,2, 23,6);
Leaves leaf9(timeScaler*random(9,12), 5,3, 19,8, 22,3);
Leaves leaf10(timeScaler*random(10,13), 19,2, 2,7, 3,3);
Leaves leaf11(timeScaler*random(11,14), 4,3, 20,2, 18,6);
Leaves leaf12(timeScaler*random(12,15), 6,6, 21,3, 23,8);
Leaves leaf13(timeScaler*random(13,16), 0,4, 21,1, 0,5);
Leaves leaf14(timeScaler*random(14,17), 20,0, 6,5, 23,4);
Leaves leaf15(timeScaler*random(15,18), 1,4, 5,4, 21, 6);
Leaves leaf16(timeScaler*random(16,19), 22,5, 0,6, 5,6);
Leaves leaf17(timeScaler*random(17,20), 2,8, 18,8, 1,3);
Leaves leaf18(timeScaler*random(18,21), 3,2, 22,1, 22,8);
Leaves leaf19(timeScaler*random(19,22), 22,6, 19,1, 21,8);
Leaves leaf20(timeScaler*random(20,23), 1,8, 19,4, 21,4);
Leaves leaf21(timeScaler*random(21,24), 1,2, 2,6, 21,2);
Leaves leaf22(timeScaler*random(22,25), 4,4, 19,3, 21,6);
Leaves leaf23(timeScaler*random(23,26), 4,6, 3,7, 20,3);
Leaves leaf24(timeScaler*random(24,27), 5,7, 21,0, 4,9);
Leaves leaf25(timeScaler*random(25,28), 2,1, 3,4, 22,4);
Leaves leaf26(timeScaler*random(26,29), 6,4, 1,9, 23,8);
Leaves leaf27(timeScaler*random(27,30), 21,5, 3,8, 2,5);
Leaves leaf28(timeScaler*random(28,31), 1,5, 3,1, 19,7);
Leaves leaf29(timeScaler*random(29,32), 4,5, 21,7, 20,5);
Leaves leaf30(timeScaler*random(30,33), 2,9, 19,5, 20,7);
Leaves leaf31(timeScaler*random(31,35), 19,7, 5,8, 3,9);

Leaves leafList[31] = {leaf1,leaf2,leaf3,leaf4,leaf5,leaf6,leaf7,leaf8,leaf9,leaf10,leaf11,leaf12,leaf13,leaf14,leaf15,leaf16,leaf17,leaf18,leaf19,leaf20,leaf21,leaf22,leaf23,leaf24,leaf25,leaf26,leaf27,leaf28,leaf29,leaf30,leaf31};

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int deer_countdown = 0;
int fire_shifter = 0;

// colors:

// for the tree:
int tree_brown = matrix.Color333(2,1,0);

// for the fire:
int woodcolor = matrix.Color333(2,1,0);
int fire1 = matrix.Color888(196,10,0); // R
int fire2 = matrix.Color888(204,10,0); // R
int fire3 = matrix.Color888(255,51,51); // R
int fire4 = matrix.Color888(255,69,0); // O
int fire5 = matrix.Color888(255,140,0); // O
int fire6 = matrix.Color888(255,192,0); // Y
int fire7 = matrix.Color888(244,196,48); // Y
int fires[7] = {fire1,fire2,fire3,fire4,fire5,fire6,fire7};

// for the pumpkin:
int pumpkin_orange = matrix.Color888(204,85,0);
int pumpkin_stem = matrix.Color888(79,141,66);

int white = matrix.Color888(255,255,255);
int blank = matrix.Color888(0,0,0);

// for the leaves:
int leaf_green1 = matrix.Color888(33, 104, 59); // 'hunter green'
int leaf_green2 = matrix.Color888(79, 141, 66); // 'fern green'
int leaf_green3 = matrix.Color888(34, 139, 34); // 'forest green'

int leaf_yellow1 = matrix.Color888(228,208,10); // 'citrine'
int leaf_yellow2 = matrix.Color888(218,165,32); // 'goldenrod'

int leaf_orange1 = matrix.Color888(200,57,35);
int leaf_orange2 = matrix.Color333(6,3,0);
int leaf_orange3 = matrix.Color333(6,2,1); 

int leaf_red1 = matrix.Color888(136,8,8); // 'blood red'
int leaf_red2 = matrix.Color888(119,7,10);

// old colors:
//int leaf_green4 = matrix.Color888(0, 158, 96); // 'shamrock green'
//int leaf_green5 = matrix.Color888(95, 133, 117); // 'eucalyptus'
//int leaf_yellow3 = matrix.Color888(201,204,63); // 'pear'
//int leaf_yellow4 = matrix.Color888(160,82,45); // 'sienna'
//int leaf_orange4 = matrix.Color333(7,4,3);
//int leaf_orange5 = matrix.Color333(7,4,3);


// 0-2: green
// 3-4: yellow
// 5-7: orange
// 8-9: red
int leaf_colors[10] = {leaf_green1, leaf_green2, leaf_green3, leaf_yellow1, leaf_yellow2, leaf_orange1, leaf_orange2, leaf_orange3, leaf_red1, leaf_red2}; 




void setup() 
{
    matrixInit();
    Serial.begin(9600);

}


void loop() 
{

  // adjust speed here:
  delay(10);
  
  leavesColorTick();

  // clear the screen
  matrixClearScreen();

  // draw elements
  drawGround();
  drawTrees();
  drawPumpkin();
  drawLeaves();
  
  // every so often maybe change the position of the flame tip
  if (millis() % 10 == 0)
    {
        fire_shifter = random(2);
    }

  drawFire(fire_shifter);

}

// draw the orange and brown pumpkin
void drawPumpkin(void)
{
  int pumpkin_x[15] = {27,29,26,27,28,29,30,26,27,28,29,30,27,28,29};
  int pumpkin_y[15] = {10,10,11,11,11,11,11,12,12,12,12,12,13,13,13};
  drawArray(pumpkin_x, sizeof(pumpkin_x), pumpkin_y, sizeof(pumpkin_y), pumpkin_orange, 0);

  int pumpkin_stem_x[2] = {28,28};
  int pumpkin_stem_y[2] = {9,10};
  drawArray(pumpkin_stem_x, sizeof(pumpkin_stem_x), pumpkin_stem_y, sizeof(pumpkin_stem_y), pumpkin_stem, 0);
}

// draw the trunk and branches of the tree
void drawTrees(void)
{
    int tree_left_x[30] = {1,4, 2,3, 0,2,3,6, 1,2,3,5, 0,2,3,4, 2,3, 5,1,2,  3, 2,  3, 2,  3, 2, 3,  2, 3};
    int tree_left_y[30] = {3,3, 4,4, 5,5,5,5, 6,6,6,6, 7,7,7,7, 8,8,8, 9,9,9, 10,10, 11,11, 12,12, 13,13};

    int tree_right_x[34] = {20,19,22,23,18,20,21,20,21,22,23,19,20,21,18,20,21,22,20,21,19,20,21,22,20,21,20,21,20,21,20,21,20,21};
    int tree_right_y[34] = {1,2,2,2,3,3,3,4,4,4,4,5,5,5,6,6,6,6,7,7,8,8,8,8, 9, 9,10,10,11,11,12,12,13,13};

  drawArray(tree_left_x, sizeof(tree_left_x), tree_left_y, sizeof(tree_left_y), tree_brown, 0);
  drawArray(tree_right_x, sizeof(tree_right_x), tree_right_y, sizeof(tree_right_y), tree_brown, 0);



}

// draw the green ground
void drawGround()
  { 
      int grasscolor = matrix.Color333(0,1,0);
      for (int i = 0 ; i < 32 ; i++){
          matrix.drawPixel(i,15,grasscolor);
          matrix.drawPixel(i,14,grasscolor);
      }
  }

void drawFire(int shifter)
{
    int NUMBRN = 8;
    int NUMRED = 2;
    int NUMORG = 2;
    int NUMYEL = 1;
    
    // fire base
    int xlist_wood[NUMBRN] = {11,12,13,14,
                              11,12,13,14};
    int ylist_wood[NUMBRN] = {12,12,12,12,
                              13,13,13,13};

    // red fire
    int xlist_red[NUMRED] = {12,13};
    int ylist_red[NUMRED] = {11,11};
    
    // orange fire
    int xlist_orange[NUMORG] = {12,13};
    int ylist_orange[NUMORG] = {10,10};

    // yellow fire
    int xlist_yellow[NUMYEL+1] = {12, 13};
    int ylist_yellow[NUMYEL] = {9};

    for (int i = 0 ; i < NUMBRN ; i++ ){
          matrix.drawPixel(xlist_wood[i], ylist_wood[i], woodcolor);
          if (i < NUMRED)
          {
              matrix.drawPixel(xlist_red[i], ylist_red[i], fires[random(7)]);
          }
          if (i < NUMORG)
          {
              matrix.drawPixel(xlist_orange[i], ylist_orange[i], fires[random(7)]);
          }
          if (i < NUMYEL)
          {
              matrix.drawPixel(xlist_yellow[i+shifter], ylist_yellow[i], fires[random(7)]);
          }
      }
    
}

// tick along the color timeline for all the leaves in the list
void leavesColorTick(void)
{
    for (int i = 0 ; i < 31 ; i++)
    {
        leafList[i].colorTick();
    }
}

// draw the whole leaf list
void drawLeaves(void)
{
    for (int i = 0 ; i < 31 ; i++)
    {
        drawLeaf(leafList[i]);
    }
}

// draw a triad of leaves from one input leaf
void drawLeaf(Leaves input_leaf)
{
    int x1 = input_leaf.x1;
    int y1 = input_leaf.y1;
    int x2 = input_leaf.x2;
    int y2 = input_leaf.y2;
    int x3 = input_leaf.x3;
    int y3 = input_leaf.y3;

    int color = leaf_colors[input_leaf.getColorIndex()];

    drawPoint(x1, y1, color); 
    drawPoint(x2, y2, color); 
    drawPoint(x3, y3, color); 
}

// draw a single point with a given color
void drawPoint(int x, int y, int color)
{
    matrix.drawPixel(x, y, color);
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