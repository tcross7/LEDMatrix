#include <Snowflake.h>
#include <Arduino.h>
#include <RGBmatrixPanel.h>

// Matrix definitions
#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

// Create snowflakes within their lanes
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


#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr // Matrix scrolling

// Set parameters for message scrolling
bool scrolling = false;
bool cooldown = false;

const char str[] PROGMEM = "Merry";
const char str2[] PROGMEM = "      Christmas";
int16_t    textX         = matrix.width(), // adjust for tree 
           textMin       = sizeof(str2)*-6;// * -36; // increase the multiplier to increase the amount of time between scrolls

void setup() {
    matrix.begin();
    
    matrix.setTextWrap(false); // Allow text to run off right edge
    matrix.setTextSize(1); // size 1 == 8 pixels high
    
    randomSeed(analogRead(A0));

    // Color snowflakes
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
    
    delay(30);
    
    // move the snowflakes
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
    draw_tree_2();
    
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
    

    //scroll_christmas(); // UNCOMMENT TO TURN MESSAGE ON
    if (millis() % 500 == 0){ // wait at least half a second to allow scrolling again
        cooldown = false;
    }

    // draw random number to see if a message will be displayed:
    if ((random(10) == 0) && (cooldown == false)){ // 10% chance of getting the message when not in cooldown
        scrolling = true;
        cooldown = true;
    }

    // On non-AVR boards, delay slightly so screen updates aren't too quick.
    #if !defined(__AVR__)
        delay(20);
    #endif
    matrix.swapBuffers(false); // update the display
}


// Active functions

void draw_dot_snowflake(Snowflake input_flake) // draw a dot snowflake, under any circumstance
{
    int x = input_flake.x;
    int y = input_flake.y;
    int color = input_flake.color;

    matrix.drawPixel(x   , y   , color); 
}

void draw_tree(){ // draw the right tree, only when no message is scrolling 
  
    int tree_brown = matrix.Color333(2,1,0);
    int tree_green = matrix.Color333(0,3,1);

    // store the pixel locations for each color
    int x_list_green[13] = {27,25,27,29,23,25,29,31,23,31,25,29,27}; 
    int y_list_green[13] = {7,9,9,9,11,11,11,11,13,13,13,13,11};
    int x_list_brown[2] = {27,27};
    int y_list_brown[2] = {13,15};

    // draw each pixel
    if (scrolling == false) {
        for (int i = 0 ; i < 13 ; i++ ){
            matrix.drawPixel(x_list_green[i]-2,y_list_green[i]-2, tree_green);
            if (i < 3){
                matrix.drawPixel(x_list_brown[i]-2,y_list_brown[i]-2, tree_brown);
            }
        }
    }
}


void draw_tree_2(){ // draw the left tree, only when no message is scrolling 
  
    int tree_brown = matrix.Color333(2,1,0);
    int tree_green = matrix.Color333(0,3,1);
    
    // store the pixel locations for each color
    int x_list_green[13] = {27,25,27,29,23,25,29,31,23,31,25,29,27}; 
    int y_list_green[13] = {7,9,9,9,11,11,11,11,13,13,13,13,11};
    int x_list_brown[2] = {27,27};
    int y_list_brown[2] = {13,15};

    // draw each pixel
    if (scrolling == false) {
        for (int i = 0 ; i < 13 ; i++ ){
            matrix.drawPixel(x_list_green[i]-22,y_list_green[i]-2, tree_green);
            if (i < 3){
                matrix.drawPixel(x_list_brown[i]-22,y_list_brown[i]-2, tree_brown);
            }
        }
    }
}

void draw_ground(){ // draw the ground, only when no message is scrolling 
    if (scrolling == false){
        for (int i = 0 ; i < 32 ; i++){
            matrix.drawPixel(i,15,matrix.Color333(1,1,1));
        }
    }
}

void scroll_christmas(){ // display special message that scrolls across the screen
    if (scrolling == true){
      matrix.setTextColor(matrix.Color333(3,0,3)); // purple
      matrix.setCursor(textX, 1);
      matrix.print(F2(str)); // merry
      
      matrix.setTextColor(matrix.Color333(3,3,0)); // yellow
      matrix.setCursor(textX, 9);
      matrix.print(F2(str2)); // christmas

      // scrolling action:
      if((--textX) < textMin){
        scrolling = false; // exit scrolling
        textX = matrix.width(); // Move text left (w/wrap)
      }
      //
    }   
}
