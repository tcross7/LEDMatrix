#include <RGBmatrixPanel.h>

#define CLK  11   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int xs[] = {12,13,14,15,19};
int ys[] = {15,14,10,8,10};

void setup() {
    Serial.begin(9600);
    matrixInit();
}

void loop() 
{

    shift_lights();
    delay(100);
    draw_logo(random(5));
    delay(100);

}

void draw_logo(int random_select)
{
    int x_dig[18] = {0,1,2,2,2,2,3,4,5,5,5,5,6,7,8,8,8,8};
    int y_dig[18] = {8,8,8,7,6,5,5,5,5,6,7,8,8,8,8,7,6,5};

    int x_t[9] = {9,10,11,12,13,11,11,11,11};
    int y_t[9] = {5,5,5,5,5,4,6,7,8};

    int x_x[8] = {14,15,16,17,17,16,15,14};
    int y_x[8] = {5,6,7,8,5,6,7,8};

    int x_ana[14] = {18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    int y_ana[14] = {4,4,5,7,8,8,7,5,4,5,7,8,8,7};

    if (random_select == 0)
    {
        drawArray(x_dig, sizeof(x_dig), y_dig, sizeof(y_dig), matrix.Color888(random(255),random(255),random(255)), 100);
        drawArray(x_t, sizeof(x_t), y_t, sizeof(y_t), matrix.Color888(random(255),random(255),random(255)), 100);
        drawArray(x_x, sizeof(x_x), y_x, sizeof(y_x), matrix.Color888(random(255),random(255),random(255)), 100);
        drawArray(x_ana, sizeof(x_ana), y_ana, sizeof(y_ana), matrix.Color888(random(255),random(255),random(255)), 100);
    }
    else
    {
        drawArray(x_dig, sizeof(x_dig), y_dig, sizeof(y_dig), matrix.Color888(255,255,255), 100);
        drawArray(x_t, sizeof(x_t), y_t, sizeof(y_t), matrix.Color888(33,150,243), 100);
        drawArray(x_x, sizeof(x_x), y_x, sizeof(y_x), matrix.Color888(255,255,0), 100);
        drawArray(x_ana, sizeof(x_ana), y_ana, sizeof(y_ana), matrix.Color888(255,255,255), 100); 
    }

    delay(3000);
    matrixClearScreen();
}

void shift_lights(void)
{
        
    matrix.setTextColor(matrix.Color888(255,255,255)); // set the color
    for (int i = 1; i < 9 ; i++ )
    {
        int line_x = 7;
        int line_y = 3;
        
        matrix.setCursor(13, 8);  // set the cursor
        matrix.print(i); // print the line

        if (i == 8)
        {
            delay(600);
            
            drawPoint(line_x, line_y, matrix.Color888(0,255,0));
            line_x++;
            delay(50);
            
            drawPoint(line_x, line_y, matrix.Color888(0,255,0));
            line_x++;
            delay(100);
            
            for (int n = 0 ; n < random(5,15); n++)
            {
                drawPoint(line_x, line_y, matrix.Color888(0,255,0));
                delay(300 - random(80));
                drawPoint(line_x, line_y, matrix.Color888(0,0,0));
                delay(300 - random(80));
            }
            matrixClearScreen();
            return;
        }
        else
        {
            for (int j = 0 ; j < 5 ; j++)
            {
                line_x++;
                drawPoint(line_x, line_y, matrix.Color888(0,255,0));
                //delay(50 - 15*(2/i));
                delay(random((7*i - 2), (7*i + 30)));
            }
            for (int k = 0 ; k < 5 ; k++)
            {
                line_x++;
                drawPoint(line_x, line_y, matrix.Color888(255,0,0));
                //delay(50 - 15*(3/i));
                delay(random((7*i - 2), (7*i + 30)));
            }
            
            int x_8[5] = {line_x+1,line_x+2,line_x+3,line_x+4,line_x+5};
            int y_8[5] = {line_y, line_y, line_y, line_y, line_y};
            
            drawArray(x_8, sizeof(x_8), y_8, sizeof(y_8), matrix.Color888(255,0,255),0);
            delay(20);
            drawArray(x_8, sizeof(x_8), y_8, sizeof(y_8), matrix.Color888(0,0,0),0);
            delay(20);
            drawArray(x_8, sizeof(x_8), y_8, sizeof(y_8), matrix.Color888(255,0,255),0);
            delay(100);
            matrixClearScreen();
         }
        
    }

}


/*
 * Functions
 */

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
