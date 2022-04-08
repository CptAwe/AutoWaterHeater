#include <Arduino.h>
#include "RTClib.h"
#include <avr/sleep.h>

#include <relay.h>
#include <button.h>
#include <led.h>
#include <Switch.h>
#include <errors.h>
#include <alarms.h>

#define RELAY_PIN 5
#define SWITCH_PIN 3
#define BUTT_PIN 2

relay WaterHeater(RELAY_PIN);
button butt(BUTT_PIN);
led status_led;
Switch swt(SWITCH_PIN);
RTC_DS3231 clock;
errors err(LED_BUILTIN);
alarms alrms;

void showTime(DateTime time_input = clock.now());
void toggleButtonStatus();
void turnWaterHeaterON();
void turnWaterHeaterOFF();
// void wake_up();/* NOT USED YET */
// void sleep();/* NOT USED YET */

void setup() {
    Serial.begin(9600);
    
    //________CLOCK________
    if (!clock.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        err.error(0);
    }
    if (clock.lostPower()) {
        clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    //________CLOCK________

    //________INTERRUPTS________
    attachInterrupt(
        digitalPinToInterrupt(BUTT_PIN),
        toggleButtonStatus,
        RISING
    );
    //________INTERRUPTS________

    //________INITIALISATION________
    status_led.off();
    //________INITIALISATION________

    Serial.println("I am powered on");
}

bool was_button_pressed = false;
// CHSV colour_fade = CHSV(0, 255, status_led.MAX_BRIGHTNESS);// what colour to show while incrementing
DateTime turn_off_at = DateTime();

// Used by the status LED
byte increment = 1;
byte brightness_temp = 0;

void loop() {
    // Serial.println("I haven't crashed yet");
    
    if (was_button_pressed) {
        
        if (WaterHeater.status){
            // The waterheater is already on
            // Power it off?
        } else {
            // Power on the waterheater
            turnWaterHeaterON();
            was_button_pressed = false;
        }
    }

    if (WaterHeater.status) {

        if (was_button_pressed) {// Was the button pressed again?
            // If it stays pressed then turn it off
            Serial.println("The button was pressed while the waterheater is on");
            unsigned long time_start = millis();
            while (butt.status()) {
                // It is still being pressed
                if ((int)(millis() - time_start) > alrms.CANCEL_TIMEOUT){// Wait for the timeout
                    // Turn off the waterheater
                    Serial.println("Manually turned off the waterheater.");
                    turnWaterHeaterOFF();
                    while (butt.status());// Wait for the button to get released
                    break;
                }
            }
            was_button_pressed = false;
        }

        // Check if the waterheater should be powered off
        if (clock.now() >= turn_off_at) {
            turnWaterHeaterOFF();
        }
    }

}

void toggleButtonStatus() {
    was_button_pressed = true;
}

void showTime(DateTime time_input) {
    Serial.print(time_input.year(), DEC);
    Serial.print('/');
    Serial.print(time_input.month(), DEC);
    Serial.print('/');
    Serial.print(time_input.day(), DEC);
    Serial.print(" (");
    Serial.print(alrms.daysOfTheWeek[time_input.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(time_input.hour(), DEC);
    Serial.print(':');
    Serial.print(time_input.minute(), DEC);
    Serial.print(':');
    Serial.print(time_input.second(), DEC);
}

void turnWaterHeaterON() {
    DateTime turned_on_at = clock.now();
    turn_off_at = turned_on_at + TimeSpan(0, 0, 0, alrms.Waterheater_on_duration);

    showTime();
    Serial.print(" -- Turning on waterheater for ");
    Serial.print(alrms.Waterheater_on_duration);
    Serial.println(" seconds");

    WaterHeater.on(turned_on_at);
    status_led.colour(status_led.RED);
    status_led.show();

    Serial.print("|- Should be turned off at ");
    showTime(turn_off_at);
    Serial.println();
}

void turnWaterHeaterOFF() {
    showTime();
    Serial.println(" -- Turning off the waterheater...");
    WaterHeater.off();
    status_led.off();
}

//-----------------------------------------------

// void sleep() {/* NOT USED YET */
//     /* Puts the arduino in sleep mode */
//     Serial.println("I will sleep now...");
//     sleep_enable();
//     set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//     sleep_cpu();
// }

// void wake_up() {/* NOT USED YET */
//     /* Wakes up the arduino */
//     sleep_disable();
//     Serial.println("Just woke up!");
//     showTime();
// }