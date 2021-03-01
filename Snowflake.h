#ifndef Snowflake_h
#define Snowflake_h

#include "Arduino.h"

class Snowflake
{
    public:
        Snowflake(int input_start_pos);

        int x;
        int y;
        int color;
        int start_pos;
        bool slow;
        int slow_count;
        bool normal;
        bool fast;

        void move_x();
        void move_y();
        void reset();
        void move();
        void set_color(int input_color);
};
#endif