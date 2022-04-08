#ifndef led_h
#define led_h

#include "Arduino.h"
#include <FastLED.h>

#define LED_PIN 4

class led {
    private:
        CRGB _led[1];
        CHSV _current_colour;

    public:

        static const byte MAX_BRIGHTNESS = 50;

        CHSV GREEN = CHSV(100, 255, 100);
        CHSV BLUE = CHSV(160, 255, 100);
        CHSV RED = CHSV(0, 255, 100);

        led() {
            FastLED.addLeds<NEOPIXEL, LED_PIN>(_led, 1);
        }

        void colour(CHSV colour, byte brightness = MAX_BRIGHTNESS) {
            if (brightness > MAX_BRIGHTNESS) {
                brightness = MAX_BRIGHTNESS;
            }

            _current_colour.setHSV(
                colour.hue,
                colour.sat,
                colour.val
            );

            _led[0].setHSV(
                _current_colour.hue,
                _current_colour.sat,
                brightness
            );
        }

        void show() {
            FastLED.show();
        }

        void fade(byte increment) {
            colour(_current_colour, _current_colour.val + increment);
        }

        void off() {
            FastLED.clear(true);
        }
};

#endif
