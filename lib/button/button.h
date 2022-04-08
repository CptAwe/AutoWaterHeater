#ifndef button_h
#define button_h

#include "Arduino.h"


class button {
    private:
        byte _PIN;
        byte how_many_tries = 10;
    public:
    
        button(byte pin) {
            _PIN = pin;
            pinMode(_PIN, INPUT);
        }

        bool status() {
            byte how_many_true = 0;
            for (byte i=0; i<=how_many_tries; i++){
                if (digitalRead(_PIN)) {
                    how_many_true++;
                }
                delay(10);
            }
            if (how_many_true >= how_many_tries/2) {
                return true;
            }
            return false;
        }
};


#endif
