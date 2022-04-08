#ifndef errors_h
#define errors_h

#include "Arduino.h"

class errors {
    private:
        byte _PIN;

        void error_blink(int on_time, int off_time) {
            while (1) {
                digitalWrite(_PIN, HIGH);
                delay(on_time);
                digitalWrite(_PIN, LOW);
                delay(off_time);
            }
        }
    public:
    
        errors(byte pin) {
            _PIN = pin;
            pinMode(_PIN, OUTPUT);
        }

        void error(int error_code) {
            switch (error_code) {
                case 0:// No RTC found
                    error_blink(500, 100);
                    break;
                
                default:// No specific error
                    error_blink(1000, 1000);
                    break;
            }
        }
};


#endif
