#include "Arduino.h"
#include "Leaves.h"

Leaves::Leaves(int shiftTimeIn, int x1in, int y1in, int x2in, int y2in, int x3in, int y3in)
{
    randomSeed(analogRead(A0));
    startTime = millis();
    shiftTime = shiftTimeIn;
    colorStage = 1;
    leafSlower = 0;

    // LEAF 1
    x1 = x1in;
    x1_start = x1in;
    x1_swing = random(2, 5); // the horizontal path a leaf takes while moving downward (this is half of the total horizontal travel)
    x1_dir = random(2); // initial left or right movement from tree
    x1_limit_R = x1 + x1_swing;
    x1_limit_L = x1 - x1_swing;
    
    y1 = y1in;
    y1_start = y1in;
    y1_limit = random(14,16); // where the leaf will stop on the ground
    leaf1Delay = random(100, 60000); // how much time after turning orange the leaf will fall
    
    // LEAF 2
    x2 = x2in;
    x2_start = x2in;
    x2_swing = random(2, 5);
    x2_dir = random(2);
    x2_limit_R = x2 + x2_swing;
    x2_limit_L = x2 - x2_swing;
    
    y2 = y2in;
    y2_start = y2in;
    y2_limit = random(14,16);
    //leaf2Delay = random(70000, 120000);

    // LEAF 3
    x3 = x3in;
    x3_start = x3in;
    x3_swing = random(2, 5);
    x3_dir = random(2);
    x3_limit_R = x3 + x3_swing;
    x3_limit_L = x3 - x3_swing;
    
    y3 = y3in;
    y3_start = y3in;
    y3_limit = random(14,16);
    //leaf3Delay = random(120000, 180000);

}

// reset the leaves to their original position and color
void Leaves::reset(void)
{

    colorStage = 0;
    leafSlower = 0;

    // leaf 1
    x1 = x1_start;
    y1 = y1_start;

    x1_swing = random(2, 5); // the horizontal path a leaf takes while moving downward (this is half of the total horizontal travel)
    x1_dir = random(2); // initial left or right movement from tree
    x1_limit_R = x1 + x1_swing;
    x1_limit_L = x1 - x1_swing;

    y1_limit = random(14,16); // where the leaf will stop on the ground
    leaf1Delay = random(100, 60000); // how much time after turning orange the leaf will fall

    // leaf2 
    x2 = x2_start;
    y2 = y2_start;

    x2_swing = random(2, 5);
    x2_dir = random(2);
    x2_limit_R = x2 + x2_swing;
    x2_limit_L = x2 - x2_swing;
    
    y2_limit = random(14,16);

    // leaf3
    x3 = x3_start;
    y3 = y3_start;

    x3_swing = random(2, 5);
    x3_dir = random(2);
    x3_limit_R = x3 + x3_swing;
    x3_limit_L = x3 - x3_swing;
    
    y3_limit = random(14,16);

    colorTick();

}

void Leaves::colorTick(void)
{
    
    if ((millis() - startTime) > shiftTime)
    {
        // if we're still green or yellow, just move to the next color stage and reset 'startTime'
        if (colorStage < 3)
        {
            colorStage += 1;
            startTime = millis();
            leafDelayStartTime = millis();
        }
        // if we're orange and have waited the right amount of time, then drop the leaves
        else if ((colorStage == 3) && (colorIndex > 5))
        {
            moveLeaves();
        }
        
    }
    
    // only change color if leaves have not yet reached the ground
    // 10 times a second: (millis() % 100) == 0) && 
    if (((y1<y1_limit) && (y2<y2_limit) && (y3<y3_limit)))
    {
        // randomly pick a leaf color based on the stage we're in
        if (colorStage == 1)
        {
            colorIndex = random(0,3); // green range
        }
        else if (colorStage == 2)
        {
            colorIndex = random(3,5); // yellow range
        }
        else if (colorStage == 3)
        {
            colorIndex = random(5, 8); // orange range
        }

        // yet to be incorporated
        else if (colorStage == 4)
        {
            colorIndex = random(8,10); // red range
        }
    }
    
}

void Leaves::moveLeaves(void)
{
    if (leafSlower % 3 == 0)
    {
        if ((millis() - leafDelayStartTime) > leaf1Delay)
        {
            moveLeaf1();
        }
        
        if ((millis() - leafDelayStartTime) > leaf1Delay*2)
        {
            moveLeaf2();
        }
        
        if ((millis() - leafDelayStartTime) > leaf1Delay*3)
        {
            moveLeaf3();
        }    
        
    }
    leafSlower += 1;
}

void Leaves::moveLeaf1(void)
{
    // move LEAF 1
    if (y1 < y1_limit)
    {
        // currently moving to the right
        if (x1_dir == 1)
        {
            if (x1 < x1_limit_R)
            {
                x1 += 1;
            }
            // if we're at the Right limit, flip directions to the left and move down
            else if (x1 == x1_limit_R)
            {
                x1_dir = 0;
                y1 += 1;
            }
        }
        // currently moving to the left
        else if (x1_dir == 0)
        {
            if (x1 > x1_limit_L)
            {
                x1 -= 1;
            }
            // if we're at the Left limit, flip directions to the left and move down
            else if (x1 == x1_limit_L)
            {
                x1_dir = 1;
                y1 += 1;
            }
        }
    }
}

void Leaves::moveLeaf2(void)
{
    // Move LEAF 2
    if (y2 < y2_limit)
    {
        // currently moving to the right
        if (x2_dir == 1)
        {
            if (x2 < x2_limit_R)
            {
                x2 += 1;
            }
            // if we're at the Right limit, flip directions to the left and move down
            else if (x2 == x2_limit_R)
            {
                x2_dir = 0;
                y2 += 1;
            }
        }
        // currently moving to the left
        else if (x2_dir == 0)
        {
            if (x2 > x2_limit_L)
            {
                x2 -= 1;
            }
            // if we're at the Left limit, flip directions to the left and move down
            else if (x2 == x2_limit_L)
            {
                x2_dir = 1;
                y2 += 1;
            }
        }
    }

}

void Leaves::moveLeaf3(void)
{
    // Move LEAF 3
    if (y3 < y3_limit)
    {
        // currently moving to the right
        if (x3_dir == 1)
        {
            if (x3 < x3_limit_R)
            {
                x3 += 1;
            }
            // if we're at the Right limit, flip directions to the left and move down
            else if (x3 == x3_limit_R)
            {
                x3_dir = 0;
                y3 += 1;
            }
        }
        // currently moving to the left
        else if (x3_dir == 0)
        {
            if (x3 > x3_limit_L)
            {
                x3 -= 1;
            }
            // if we're at the Left limit, flip directions to the left and move down
            else if (x3 == x3_limit_L)
            {
                x3_dir = 1;
                y3 += 1;
            }
        }
    }
}

// return the index of the leaf color array that we want
int Leaves::getColorIndex(void)
{
    return colorIndex;
}

// return int that indicates what stage the color is at
// 1: still green
// 2: yellow range
// 3: orange range
// 4: red range (rare)
int Leaves::getStage(void)
{
    return colorStage;
}


// draw a black cat walking across the screen to the right
// step range: 0 to 35 (31+length)
/*void drawLumiR(void)
{
    int lumi_x[7] = [step, step-1, step-1, step-2, step-3, step-3, step-4];
    int lumi_y[7] = [13,14,15,14,14,15,14];


}

// draw a black cat walking across the screen to the left
// step range: 31 to -4 (0-length)
void drawLumiL()
{
    int lumi_x[7] = [step, step+1, step+1, step+2, step+3, step+3, step+4];
    int lumi_y[7] = [13,14,15,14,14,15,14];
}*/

