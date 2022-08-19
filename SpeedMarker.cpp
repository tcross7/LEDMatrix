#include "Arduino.h"
#include "SpeedMarker.h"

// side = -1: left
// side = 1: right
// inputOffset: a number to shift the markers vertically so we can have multiple sets
SpeedMarker::SpeedMarker(int side, int inputOffset)
{
    randomSeed(analogRead(A0));
    offset = inputOffset;

    // create the structure that holds the color information
    union COLOR
    {
        unsigned long RGB;
        byte bytes[3];
    };

    union COLOR assembledColor;
    

    // randomize the markers to start, until reset
    randomizeMarker();

    // refers to the base (lowest) position of the marker
    // markers are 1 pixel wide and 3 (for now) pixels tall
    // start location is dependent on which side of the straight they're on

    // start just beyond the track limits
    if (side == -1)
    {
        left = true;
        x = 8+offset;
        y = 0-offset; 
        start_pos = x;
    }
    else if (side == 1)
    {
        right = true;
        x = 23-offset;
        y = 0-offset; 
        start_pos = x;
    }    
}

// reset the marker to it's initial position
void SpeedMarker::reset() 
{
    x = start_pos;
    y = 0-offset;

    randomizeMarker();
}


// can move at different speeds? 
// for now let's stick to one speed, but in the future we could make them move more slowly as we approach a corner (on the opposite side)

// move the marker to the side and down by 1 unit per frame
void SpeedMarker::move(void)
{
    if (left)
    {
        x--;
    }
    else if (right)
    {
        x++;
    }

    y++;

    // reset the marker to the top of the screen after it leaves
    // spaced from 0-9 so we can show the markers evenly
    if (y > 9)
    { 
        reset();
    }  
}

// get which side of the track the marker is on
// returns -1: left
// returnes 1: right
int SpeedMarker::getSide()
{
    if (left)
    {
        return -1;
    }
    else if (right)
    {
        return 1;
    }
}



int SpeedMarker::getColor(void)
{
    return assembledColor.RGB;
}

// get the x location of the current marker
int SpeedMarker::getX(void)
{
    return x;
}

// get the y location of the current marker
int SpeedMarker::getY(void)
{
    return y;
}


// TO-DO: randomize the color (and shape?) so we can get a variety of options - trees, poles, bush?
// NOTE: it might be easier to do this up a level (for drawing purposes - unless I can return arrays here)
void SpeedMarker::randomizeMarker(void)
{
    assembledColor.bytes[2] = random(255); // R
    assembledColor.bytes[1] = random(100); // G - keep this value lower so the objects show up on the green grass background
    assembledColor.bytes[0] = random(255); // B 
}