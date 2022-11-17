#ifndef Leaves_h
#define Leaves_h

#include "Arduino.h"

class Leaves
{
    public:
        Leaves(int shiftTimeIn, int x1in, int y1in, int x2in, int y2in, int x3in, int y3in);
        
        unsigned long startTime;
        unsigned long shiftTime;
        unsigned long leafDelayStartTime;

        int colorStage;
        int colorIndex;
        int leafSlower;
        
        int x1;
        int x1_start;
        int x1_swing;
        int x1_dir;
        int x1_limit_R;
        int x1_limit_L;

        int y1;
        int y1_start;
        int y1_limit; 
        unsigned long leaf1Delay;
        

        int x2;
        int x2_start;
        int x2_swing;
        int x2_dir;
        int x2_limit_R;
        int x2_limit_L;
        
        int y2;
        int y2_start;
        int y2_limit;
        //unsigned long leaf2Delay;

        int x3;
        int x3_start;
        int x3_swing;
        int x3_dir;
        int x3_limit_R;
        int x3_limit_L;
        
        int y3;
        int y3_start;
        int y3_limit;
        //unsigned long leaf3Delay;

        void reset();
        void moveLeaves();
        void moveLeaf1();
        void moveLeaf2();
        void moveLeaf3();

        void colorTick();
        void colorShift();
        int getColorIndex();
        int getStage();
};
#endif