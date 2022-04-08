#ifndef relay_h
#define relay_h

#include "Arduino.h"

class relay {
    private:
        byte _PIN;
        bool _on_value;// what value (true/false) turns the relay on

        void _update_status() {
            digitalWrite(_PIN, status);
        }

    public:
        bool status;
        DateTime time_since_last_power_on;
    
        relay(byte pin, bool on_val = true) {
            /* The relay starts in the off state */
            _PIN = pin;
            pinMode(_PIN, OUTPUT);
            _on_value = on_val;
            status = !_on_value;
            _update_status();
        }

        void on(DateTime time_it_was_powered_on) {
            status = _on_value;
            _update_status();
            time_since_last_power_on = time_it_was_powered_on;
        }

        void off() {
            status = !_on_value;
            _update_status();
            time_since_last_power_on = DateTime();
        }
};


#endif
