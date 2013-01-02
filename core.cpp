#include <Arduino.h>
#include <stdio.h>
#include "LiquidCrystal.h"
#include "button.h"
#include "camera.h"
#include "flash.h"
#include "analogSensor.h"
#include "buzzer.h"
#include "digitalOutput.h"

const int LCD_LED_PIN    =  2;
const int LCD_RS_PIN     = 23;
const int LCD_ENABLE_PIN = 25;
const int LCD_DB4_PIN    = 27;
const int LCD_DB5_PIN    = 29;
const int LCD_DB6_PIN    = 31;
const int LCD_DB7_PIN    = 33;

const int NOISE_SENSOR_PIN    = A4;
const int LIGHT_SENSOR_PIN    = A5;
const int PRESSURE_SENSOR_PIN = A6;
const int IR_SENSOR_PIN       = A7;

const int BUZZER_PIN = 3;

const int FLASH_1_PIN = 30;
const int FLASH_2_PIN = 32;
const int FLASH_3_PIN = 34;
const int FLASH_4_PIN = 36;

const int CAMERA_1_FOCUS_PIN   = 26;
const int CAMERA_1_SHUTTER_PIN = 28;
const int CAMERA_2_FOCUS_PIN   = 22;
const int CAMERA_2_SHUTTER_PIN = 24;

const int ROT_CH_A_PIN     = 37;
const int ROT_CH_B_PIN     = 35;
const int BUTTON_OK_PIN    = 39;
const int BUTTON_UP_PIN    = 49;
const int BUTTON_DOWN_PIN  = 47;
const int BUTTON_LEFT_PIN  = 51;
const int BUTTON_RIGHT_PIN = 45;
const int BUTTON_RC1_PIN   = 53;
const int BUTTON_RC2_PIN   = 52;

const int SOCKET_PIN       = 38;
const int OUTPUT_1_12V_PIN = 40;
const int OUTPUT_2_12V_PIN = 42;
const int OUTPUT_3_12V_PIN = 44;
const int OUTPUT_1_5V_PIN  = 46;
const int OUTPUT_2_5V_PIN  = 48;
const int OUTPUT_3_5V_PIN  = 50;


LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DB4_PIN, LCD_DB5_PIN, LCD_DB6_PIN, LCD_DB7_PIN);

button button_up(BUTTON_UP_PIN);
button button_down(BUTTON_DOWN_PIN);
button button_left(BUTTON_LEFT_PIN);
button button_right(BUTTON_RIGHT_PIN);
button button_ok(BUTTON_OK_PIN);
button button_rc1(BUTTON_RC1_PIN);
button button_rc2(BUTTON_RC2_PIN);
button button_ch_a(ROT_CH_A_PIN);
button button_ch_b(ROT_CH_B_PIN);

camera camera_1(CAMERA_1_FOCUS_PIN, CAMERA_1_SHUTTER_PIN);
camera camera_2(CAMERA_2_FOCUS_PIN, CAMERA_2_SHUTTER_PIN);

flash flash_1(FLASH_1_PIN);
flash flash_2(FLASH_2_PIN);
flash flash_3(FLASH_3_PIN);
flash flash_4(FLASH_4_PIN);

analogSensor noise_sensor(NOISE_SENSOR_PIN);
analogSensor light_sensor(LIGHT_SENSOR_PIN);
analogSensor pressure_sensor(PRESSURE_SENSOR_PIN);
analogSensor ir_sensor(IR_SENSOR_PIN);

buzzer bzzz(BUZZER_PIN);

digitalOutput socket(SOCKET_PIN);
digitalOutput output_1_12v(OUTPUT_1_12V_PIN);
digitalOutput output_2_12v(OUTPUT_2_12V_PIN);
digitalOutput output_3_12v(OUTPUT_3_12V_PIN);
digitalOutput output_1_5v(OUTPUT_1_5V_PIN);
digitalOutput output_2_5v(OUTPUT_2_5V_PIN);
digitalOutput output_3_5v(OUTPUT_3_5V_PIN);

void setup() {
    lcd.begin(20, 4);
    lcd.begin_backlight(LCD_LED_PIN, 63);
    lcd.print("hello, world!");
}

void loop() {

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

