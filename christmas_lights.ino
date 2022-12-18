#include <Snowflake.h>
#include <Arduino.h>
#include <RGBmatrixPanel.h>

#define CLK  11   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2


Snowflake flake1(5);
Snowflake flake2(7);
Snowflake flake3(9);
Snowflake flake4(11);
Snowflake flake5(13);
Snowflake flake6(15);
Snowflake flake7(17);
Snowflake flake8(19);
Snowflake flake9(21);
Snowflake flake10(23);
Snowflake flake11(25);
Snowflake flake12(27);

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);


#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

int deer_countdown = 0;
int fire_shifter = 0;

bool scrolling = false;
bool cooldown = false;

// colors:

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

const char str[] PROGMEM = "Merry";
const char str2[] PROGMEM = "      Christmas";
int16_t    textX         = matrix.width(), // adjust for tree 
           textMin       = sizeof(str2)*-6; // increase the multiplier to increase the amount of time between scrolls

void setup() {
    matrix.begin();
    matrix.setTextWrap(false); // Allow text to run off right edge
    matrix.setTextSize(1); // size 1 == 8 pixels high
    randomSeed(analogRead(A0));

    // create flakes
    flake1.set_color(matrix.Color333(3,3,3));
    flake2.set_color(matrix.Color333(3,3,3));
    flake3.set_color(matrix.Color333(3,3,3));
    flake4.set_color(matrix.Color333(3,3,3));
    flake5.set_color(matrix.Color333(3,3,3));
    flake6.set_color(matrix.Color333(3,3,3));
    flake7.set_color(matrix.Color333(3,3,3));
    flake8.set_color(matrix.Color333(3,3,3));
    flake9.set_color(matrix.Color333(3,3,3));
    flake10.set_color(matrix.Color333(3,3,3));
    flake11.set_color(matrix.Color333(3,3,3));
    flake12.set_color(matrix.Color333(3,3,3));
}

void loop() {
    // adjust speed here:
    delay(50);
    
    // move the flakes
    flake1.move();
    flake2.move();
    flake3.move();
    flake4.move();
    flake5.move();
    flake6.move();
    flake7.move();
    flake8.move();
    flake9.move();
    flake10.move();
    flake11.move();
    flake12.move();

    // clear the screen
    matrix.fillScreen(0);
    
    // redraw environment
    draw_ground();
    draw_tree();
    draw_reindeer();

    if (millis() % 10 == 0)
    {
        fire_shifter = random(2);
    }
    draw_fire(fire_shifter);
    
    draw_lights();
       
    draw_dot_snowflake(flake1);
    draw_dot_snowflake(flake2);
    draw_dot_snowflake(flake3);
    draw_dot_snowflake(flake4);
    draw_dot_snowflake(flake5);
    draw_dot_snowflake(flake6);
    draw_dot_snowflake(flake7);
    draw_dot_snowflake(flake8);
    draw_dot_snowflake(flake9);
    draw_dot_snowflake(flake10);
    draw_dot_snowflake(flake11);
    draw_dot_snowflake(flake12);
    

    scroll_christmas();
    if (millis() % 1000 == 0){
        cooldown = false;
    }
    
    if ((random(10) == 0) && (cooldown == false)){ // 10% chance - play with this
        scrolling = true;
        cooldown = true;
    }

    // HOW TO PRINT CHARACTERS
    //    matrix.setCursor(1, 9);  // set the cursor
    //    matrix.setTextColor(matrix.Color333(0,7,0)); // set the color
    //    matrix.print('*'); // print the line
    
    matrix.swapBuffers(false); // updates the display, allegedly
}


// Active functions
void draw_lights(void)
{
    int blue_x[4] = {24, 22, 26, 19};
    int blue_y[4] = {2, 5, 8, 11};
    int blue_color = matrix.Color888(75,100,255); // 'light sky blue'

    int yellow_light_x[3] = {24, 23, 27};
    int yellow_light_y[3] = {5, 8, 10};
    int yellow_light_color = matrix.Color888(255,150,0); // 'lightyellow2'

    int red_light_x[3] = {26, 21, 29};
    int red_light_y[3] = {5, 10, 11};
    int red_light_color = matrix.Color888(139,0,0); //'darkred'

    int purple_x[3] = {20, 25, 22};
    int purple_y[3] = {7, 11, 12};
    int purple_color = matrix.Color888(218,30,214); // 'orchid'
    

    if (scrolling == false)
    {
        drawArray(blue_x, sizeof(blue_x), blue_y, sizeof(blue_y), blue_color, 0);
        drawArray(yellow_light_x, sizeof(yellow_light_x), yellow_light_y, sizeof(yellow_light_y), yellow_light_color, 0);
        drawArray(red_light_x, sizeof(red_light_x), red_light_y, sizeof(red_light_y), red_light_color, 0);
        drawArray(purple_x, sizeof(purple_x), purple_y, sizeof(purple_y), purple_color, 0);
    }
}
void draw_fire(int shifter)
{
    int NUMBRN = 8;
    int NUMRED = 2;
    int NUMORG = 2;
    int NUMYEL = 1;
    
    // fire base
    int xlist_wood[NUMBRN] = {11,12,13,14,
                              11,12,13,14};
    int ylist_wood[NUMBRN] = {13,13,13,13,
                              14,14,14,14};

    // red fire
    int xlist_red[NUMRED] = {12,13};
    int ylist_red[NUMRED] = {12,12};
    
    // orange fire
    int xlist_orange[NUMORG] = {12,13};
    int ylist_orange[NUMORG] = {11,11};

    // yellow fire
    int xlist_yellow[NUMYEL+1] = {12, 13};
    int ylist_yellow[NUMYEL] = {10};

    if (scrolling == false){
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
}

void draw_reindeer()
{
    if(deer_countdown == 0)
    {
        draw_reindeer_up();
        if (random(1000) <= 2)
        {
            deer_countdown = random(30,60);
        }
    }
    else
    {
        draw_reindeer_down();
        deer_countdown -= 1;
    }
}

void draw_reindeer_up()
{
    int NUMBRN = 12;
    int NUMLGH = 3;
    int NUMRED = 1;

    int bodycolor = matrix.Color888(139,69,19);
    int antcolor = matrix.Color888(244,164,96);
    int redcolor = matrix.Color888(255,0,0);

    int xlist_body[NUMBRN] =       {5,6,
                              2,3,4,5,6,
                                3,4,5,
                                3,  5};

    int ylist_body[NUMBRN] =          {11,11,
                              12,12,12,12,12,
                                 13,13,13,
                                 14,   14};

    int xlist_ant[NUMLGH] = {5,
                             5,6};

    int ylist_ant[NUMLGH] = {9,
                            10,10};

    int xlist_nose[NUMRED] = {7};
    int ylist_nose[NUMRED] = {11};

    if (scrolling == false)
    {
        for (int i = 0 ; i < NUMBRN ; i++ ){
              matrix.drawPixel(xlist_body[i], ylist_body[i], bodycolor);
              if (i < NUMLGH)
              {
                  matrix.drawPixel(xlist_ant[i], ylist_ant[i], antcolor);
              }
              if (i < NUMRED)
              {
                  matrix.drawPixel(xlist_nose[i], ylist_nose[i], redcolor);
              }
          }
    }
}

void draw_reindeer_down()
{
    int NUMBRN = 13;
    int NUMLGH = 3;
    int NUMRED = 1;

    int bodycolor = matrix.Color888(139,69,19);
    int antcolor = matrix.Color888(244,164,96);
    int redcolor = matrix.Color888(255,0,0);

    int xlist_body[NUMBRN] = {2,3,4,5,6,7,
                                3,4,5,6,7,
                                3,  5};

    int ylist_body[NUMBRN] =  {12,12,12,12,12,12,
                                  13,13,13,13,13,
                                  14,   14};

    int xlist_ant[NUMLGH] = {8,9,
                             8};

    int ylist_ant[NUMLGH] = {12,12,
                             13};

    int xlist_nose[NUMRED] = {7};
    int ylist_nose[NUMRED] = {14};

    if (scrolling == false)
    {
        for (int i = 0 ; i < NUMBRN ; i++ ){
              matrix.drawPixel(xlist_body[i], ylist_body[i], bodycolor);
              if (i < NUMLGH)
              {
                  matrix.drawPixel(xlist_ant[i], ylist_ant[i], antcolor);
              }
              if (i < NUMRED)
              {
                  matrix.drawPixel(xlist_nose[i], ylist_nose[i], redcolor);
              }
          }
    }
}

// draw a dot snowflake, under any circumstance
void draw_dot_snowflake(Snowflake input_flake) 
{
    int x = input_flake.x;
    int y = input_flake.y;
    int color = input_flake.color;

    matrix.drawPixel(x   , y   , color); 
}

// draw the tree, only under steady state
void draw_tree()
{
    int NUMGRN = 86;
    int NUMBRN = 4;
    
    int tree_brown = matrix.Color333(2,1,0);
    int tree_green = matrix.Color888(34, 139, 34); // 'forest green'

    int x_list_green[NUMGRN] =         {23,24,
                                    22,23,24,25,
                                21,22,23,24,25,26,
                                20,21,22,23,24,25,26,27,
                                21,22,23,24,25,26,
                                20,21,22,23,24,25,26,27,
                            19,20,21,22,23,24,25,26,27,28,
                                20,21,22,23,24,25,26,27,
                            19,20,21,22,23,24,25,26,27,28,
                        18,19,20,21,22,23,24,25,26,27,28,29,
                        18,19,20,21,22,23,24,25,26,27,28,29}; 
                            
    int y_list_green[NUMGRN] =         {2,2,
                                    3,3,3,3,
                                4,4,4,4,4,4,
                                5,5,5,5,5,5,5,5,
                                6,6,6,6,6,6,
                                7,7,7,7,7,7,7,7,
                            8,8,8,8,8,8,8,8,8,8,
                                9,9,9,9,9,9,9,9,
                            10,10,10,10,10,10,10,10,10,10,
                        11,11,11,11,11,11,11,11,11,11,11,11,
                        12,12,12,12,12,12,12,12,12,12,12,12};
    
    int x_list_brown[NUMBRN] = {23,24,23,24};
    int y_list_brown[NUMBRN] = {13,13,14,14};


    if (scrolling == false) {
        for (int i = 0 ; i < NUMGRN ; i++ ){
            matrix.drawPixel(x_list_green[i], y_list_green[i], tree_green);
            if (i < NUMBRN){
                matrix.drawPixel(x_list_brown[i], y_list_brown[i], tree_brown);
            }
        }
    }
}

// draw the ground, only under steady state
void draw_ground()
  { 
      if (scrolling == false){
          for (int i = 0 ; i < 32 ; i++){
              matrix.drawPixel(i,15,matrix.Color333(3,3,3));
          }
      }
  }

void scroll_christmas()
  {
      if (scrolling == true){
        // red
        matrix.setTextColor(matrix.Color333(3,0,0)); 
        matrix.setCursor(textX, 1);
        matrix.print(F2(str)); // "Merry"

        // green
        matrix.setTextColor(matrix.Color333(0,3,0)); 
        matrix.setCursor(textX, 9);
        matrix.print(F2(str2)); // "Christmas"
      
        if((--textX) < textMin){
          scrolling = false; // exit scrolling
          textX = matrix.width(); // Move text left (w/wrap)
        }
      }
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

// Inactive functions
void draw_fire_old(int shifter)
{
    int NUMBRN = 4;
    int NUMRED = 4;
    int NUMYEL = 1;

    int woodcolor = matrix.Color333(2,1,0);
    
    int fire1 = matrix.Color888(196,10,0); // R
    int fire2 = matrix.Color888(204,10,0); // R
    int fire3 = matrix.Color888(255,51,51); // R
    int fire4 = matrix.Color888(255,69,0); // O
    int fire5 = matrix.Color888(255,140,0); // O
    int fires[5] = {fire1,fire2,fire3,fire4,fire5};
    
    int white = matrix.Color888(255,255,255);
    int blank = matrix.Color888(0,0,0);
    
    int yellowcolor1 = matrix.Color888(255,255,51);
    int yellowcolor2 = matrix.Color888(255,255,0);
    int yellows[2] = {yellowcolor1, yellowcolor2};


    int xlist_wood[NUMBRN] = {12,13,14,15};
    int ylist_wood[NUMBRN] = {14,14,14,14};

    int xlist_red[NUMRED] = {13,14,
                             13,14};
    int ylist_red[NUMRED] = {12, 12,
                             13, 13};
    
    int xlist_yellow[NUMYEL+1] = {13, 14};
    int ylist_yellow[NUMYEL] = {11};

    if (scrolling == false)
    {
        for (int i = 0 ; i < NUMBRN ; i++ ){
              matrix.drawPixel(xlist_wood[i], ylist_wood[i], woodcolor);
              if (i < NUMRED)
              {
                  matrix.drawPixel(xlist_red[i], ylist_red[i], fires[random(5)]);
              }
              if (i < NUMYEL)
              {
                  matrix.drawPixel(xlist_yellow[i+shifter], ylist_yellow[i], fires[random(5)]);
              }
          }
    }
    
}

void draw_star()
{
    int x = 6;
    int y = 3;
    int color = matrix.Color888(255,255,0);
    
    
    matrix.drawPixel(x   , y   , color); // center
    matrix.drawPixel(x+1 , y+1 , color);
    matrix.drawPixel(x+1 , y-1 , color);
    matrix.drawPixel(x-1 , y+1 , color);
    matrix.drawPixel(x-1 , y-1 , color);

    matrix.drawPixel(x   , y-2 , color);
    matrix.drawPixel(x   , y+2 , color);
    //matrix.drawPixel(x+4 , y   , color);
    //matrix.drawPixel(x-4 , y   , color);
}
// drawing the thin tree:
void draw_tree_thin()
  {
      int tree_brown = matrix.Color333(2,1,0);
      int tree_green = matrix.Color333(0,3,1);
      int x_list_green[13] = {27,25,27,29,23,25,29,31,23,31,25,29,27}; 
      int y_list_green[13] = {7,9,9,9,11,11,11,11,13,13,13,13,11};
  
      int x_list_brown[2] = {27,27};
      int y_list_brown[2] = {13,15};
  
  
      if (scrolling == false) {
          for (int i = 0 ; i < 13 ; i++ ){
              matrix.drawPixel(x_list_green[i]-2,y_list_green[i]-2, tree_green);
              if (i < 3){
                  matrix.drawPixel(x_list_brown[i]-2,y_list_brown[i]-2, tree_brown);
              }
          }
      }
  }
  
void draw_big_diamond(Snowflake input_flake) // draw the diamond snowflake
{
    int x = input_flake.x;
    int y = input_flake.y;
    int color = input_flake.color;
    
    
    matrix.drawPixel(x   , y   , color); // center
    matrix.drawPixel(x+2 , y+2 , color);
    matrix.drawPixel(x+2 , y-2 , color);
    matrix.drawPixel(x-2 , y+2 , color);
    matrix.drawPixel(x-2 , y-2 , color);

    matrix.drawPixel(x   , y-4 , color);
    matrix.drawPixel(x   , y+4 , color);
    matrix.drawPixel(x+4 , y   , color);
    matrix.drawPixel(x-4 , y   , color);
}

void draw_big_square(Snowflake input_flake) // draw the big square snowflake
{
    int x = input_flake.x;
    int y = input_flake.y;
    int color = input_flake.color;
    
    matrix.drawPixel(x   , y   , color); // bottom left of inner square
    matrix.drawPixel(x+2 , y   , color);
    matrix.drawPixel(x   , y-2 , color);
    matrix.drawPixel(x+2 , y-2 , color);

    matrix.drawPixel(x-2 , y+2 , color);
    matrix.drawPixel(x+4 , y+2 , color);
    matrix.drawPixel(x-2 , y-4 , color);
    matrix.drawPixel(x+4 , y-4 , color);
}
