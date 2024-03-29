#ifndef SpeedMarkers_h
#define SpeedMarkers_h

#include "Arduino.h"

class SpeedMarker
{
    public:
        SpeedMarker(int side, int inputOffset);

        int x;
        int y;
        int start_pos;
        int offset;
        bool left;
        bool right;

        union COLOR
        {
            unsigned long RGB;
            byte bytes[3];
        };

        union COLOR assembledColor;


        void reset();
        void move();
        int getSide();
        int getX();
        int getY();
        void randomizeMarker();
        int getColor();
};
#endif