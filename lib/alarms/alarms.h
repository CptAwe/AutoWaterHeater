#ifndef alarms_h
#define alarms_h

#include "Arduino.h"

class alarms {
    public:
        //________MISC________
        int CANCEL_TIMEOUT = 2000;// How many milliseconds the button has to be pressed to cancel.
        char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        //________MISC________

        //________WATERHEATER________
        byte waterheater[2][2][2] = {// 24h format
            {// morning
                {7, 0},// start
                {8, 0}// stop
            },
            {// midday
                {16, 00},//start
                {17, 00}// stop
            }
        };
        int Waterheater_on_duration = 1800;// How many seconds the waterheater will be on for
        //________WATERHEATER________
};


#endif
