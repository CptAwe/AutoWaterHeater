#ifndef Switch_h
#define Switch_h

#include "Arduino.h"


class Switch {
    private:
        byte _PIN;
    public:
    
        Switch(byte pin) {
            _PIN = pin;
            pinMode(_PIN, INPUT);
        }

        bool status() {
            return digitalRead(_PIN);
        }
};


#endif
