#include <Arduino.h>
#include <stdio.h>
#include <LiquidCrystal.h>
#include "button.h"

const int LCD_LED_PIN    = 2;
const int LCD_RS_PIN     = 23;
const int LCD_ENABLE_PIN = 25;
const int LCD_DB4_PIN    = 27;
const int LCD_DB5_PIN    = 29;
const int LCD_DB6_PIN    = 31;
const int LCD_DB7_PIN    = 33;

const int NOISE_SENSOR_PIN    = A4;
const int LIGHT_SENSOR_PIN    = A5;
const int PREASURE_SENSOR_PIN = A6;
const int IR_SENSOR_PIN       = A7;

const int BUZZER_PIN = 3;

const int FLASH_1_PIN = 30;

const int CAMERA_1_FOCUS_PIN = 26;
const int CAMERA_1_SHUTTER_PIN = 28;

LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DB4_PIN, LCD_DB5_PIN, LCD_DB6_PIN, LCD_DB7_PIN);

button *up = new button(20);

void setup() {
    pinMode(LCD_LED_PIN, OUTPUT);
    analogWrite(LCD_LED_PIN, 255);
    lcd.begin(20, 4);
    lcd.print("hello, world!");

    pinMode(NOISE_SENSOR_PIN, INPUT);
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    pinMode(PREASURE_SENSOR_PIN, INPUT);
    pinMode(IR_SENSOR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(FLASH_1_PIN, OUTPUT);
    pinMode(CAMERA_1_FOCUS_PIN, OUTPUT);
    pinMode(CAMERA_1_SHUTTER_PIN, OUTPUT);

    //analogWrite(BUZZER_PIN, 128);
}

void loop() {
    int light;

    up->get_state();

    //light = analogRead(LIGHT_SENSOR_PIN);
    //light = analogRead(NOISE_SENSOR_PIN);
    //light = analogRead(PREASURE_SENSOR_PIN);
    //light = analogRead(IR_SENSOR_PIN);
    //lcd.clear();
    //lcd.print(light);
    delay(2000);
    lcd.clear();
    digitalWrite(CAMERA_1_FOCUS_PIN, HIGH);
    lcd.print("FOCUS");
    delay(1000);
    digitalWrite(CAMERA_1_SHUTTER_PIN, HIGH);
    lcd.print(" SHUTTER");
    delay(100);
    digitalWrite(CAMERA_1_FOCUS_PIN, LOW);
    digitalWrite(CAMERA_1_SHUTTER_PIN, LOW);

}

int main(void) {

    init();

#if defined(USBCON)
    USB.attach();
#endif

    setup();

    for (;;) {
        loop();
        if (serialEventRun) serialEventRun();
    }

    return 0;
}

