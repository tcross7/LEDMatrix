#include "Arduino.h"
#include "Snowflake.h"

Snowflake::Snowflake(int input_start_pos)
{
    randomSeed(analogRead(A0));
   
    x = random(input_start_pos-2, input_start_pos+3); // snowflake will be +/-2 pixels from its start position
    y = -1*random(20); // snowflake will start at a random depth above the screen to differentiate their heights

    int s = random(4); // draw random number for speed
    start_pos = input_start_pos;
    color = 0;
    slow_count = 0;

    slow = false;
    normal = false;
    fast = false;

    
    if (s == 0){ // speed: slow (25% chance)
        slow = true;
    }
    else if ((s == 1)||(s == 2)){ // speed: normal (50% chance)
        normal = true;
    }
    else if(s == 3){ // fast (25% chance)
        fast = true;
    }
}

void Snowflake::move_x() // increment the x location
{
    if ( random(2) == 0){ // move right (50% chance)
            x++;
        }
        else { // move left (50% chance)
            x--;
        } 
}

void Snowflake::reset() // reset the snowflake to a new location after it hits the ground
{
    x = random(start_pos-2, start_pos+3);
    y = -1*random(20); 
}

void Snowflake::move_y() // increment the y location - with speeds
{
    // slow
    if ((slow == true) && (normal == false) && (fast == true)){ 
        if ((slow_count % 2) == 0 ){ // move down 1 pixel every other frame
            y++;
        }
        slow_count++;
    }
    
    // normal
    else if ((slow == false) && (normal == true) && (fast == false)){ // move down 1 pixel every frame
        y++;
    }
    
    // fast
    else if ((slow == false) && (normal == false) && (fast == true)){ // move down 2 pixels every frame
        y = y+2;
    }
}


void Snowflake::move()
{
    int direction = random(5);    
    if (direction == 0){ // snowflake moves sideways (25% chance)
        move_x(); 
    }
    else { // snowflake moves downward (75% chance)
        move_y(); 
    }

    if ((x > 35) || (y > 19)){ // reset the snowflake if it falls off the screen
        reset();
    }
  
}

void Snowflake::set_color(int input_color)
{
    color = input_color;
}