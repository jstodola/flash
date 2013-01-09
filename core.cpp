#include <Arduino.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "common.h"
#include "display.h"
#include "button.h"
#include "camera.h"
#include "flash.h"
#include "analogSensor.h"
#include "buzzer.h"
#include "digitalOutput.h"
#include "menu.h"

const uint8_t LCD_LED_PIN    =  2;
const uint8_t LCD_RS_PIN     = 23;
const uint8_t LCD_ENABLE_PIN = 25;
const uint8_t LCD_DB4_PIN    = 27;
const uint8_t LCD_DB5_PIN    = 29;
const uint8_t LCD_DB6_PIN    = 31;
const uint8_t LCD_DB7_PIN    = 33;

const uint8_t NOISE_SENSOR_PIN    = A4;
const uint8_t LIGHT_SENSOR_PIN    = A5;
const uint8_t PRESSURE_SENSOR_PIN = A6;
const uint8_t IR_SENSOR_PIN       = A7;

const uint8_t BUZZER_PIN = 3;

const uint8_t FLASH_1_PIN = 30;
const uint8_t FLASH_2_PIN = 32;
const uint8_t FLASH_3_PIN = 34;
const uint8_t FLASH_4_PIN = 36;

const uint8_t CAMERA_1_FOCUS_PIN   = 26;
const uint8_t CAMERA_1_SHUTTER_PIN = 28;
const uint8_t CAMERA_2_FOCUS_PIN   = 22;
const uint8_t CAMERA_2_SHUTTER_PIN = 24;

const uint8_t ROT_CH_A_PIN     = 37;
const uint8_t ROT_CH_B_PIN     = 35;
const uint8_t BUTTON_OK_PIN    = 39;
const uint8_t BUTTON_UP_PIN    = 49;
const uint8_t BUTTON_DOWN_PIN  = 47;
const uint8_t BUTTON_LEFT_PIN  = 51;
const uint8_t BUTTON_RIGHT_PIN = 45;
const uint8_t BUTTON_RC1_PIN   = 53;
const uint8_t BUTTON_RC2_PIN   = 52;
const uint8_t BUTTONS_COUNT    = 7;     // all buttons except rotary encoder

const uint8_t SOCKET_PIN       = 38;
const uint8_t OUTPUT_1_12V_PIN = 40;
const uint8_t OUTPUT_2_12V_PIN = 42;
const uint8_t OUTPUT_3_12V_PIN = 44;
const uint8_t OUTPUT_1_5V_PIN  = 46;
const uint8_t OUTPUT_2_5V_PIN  = 48;
const uint8_t OUTPUT_3_5V_PIN  = 50;


display lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DB4_PIN, LCD_DB5_PIN, LCD_DB6_PIN, LCD_DB7_PIN);

button button_up(BUTTON_UP_PIN, UP);
button button_down(BUTTON_DOWN_PIN, DOWN);
button button_left(BUTTON_LEFT_PIN, LEFT);
button button_right(BUTTON_RIGHT_PIN, RIGHT);
button button_ok(BUTTON_OK_PIN, OK);
button button_rc1(BUTTON_RC1_PIN, RC1);
button button_rc2(BUTTON_RC2_PIN, RC2);
rotaryEncoder rotary_button(ROT_CH_A_PIN, ROT_CH_B_PIN, UP, DOWN);

button *button_array[BUTTONS_COUNT] = {&button_up, &button_down,
                         &button_left, &button_right,
                         &button_ok, &button_rc1, &button_rc2};

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


PROGMEM const prog_char str_mode[] = "Mode...";
PROGMEM const prog_char str_settings[] = "Settings...";
PROGMEM const prog_char str_save_defaults[] = "Save as default";

PROGMEM const prog_char str_mode_1[] = "mode 1";
PROGMEM const prog_char str_mode_2[] = "mode 2";
PROGMEM const prog_char str_mode_3[] = "mode 3";

PROGMEM const prog_char str_settings_1[] = "settings 1";
PROGMEM const prog_char str_settings_2[] = "settings 2";
PROGMEM const prog_char str_settings_3[] = "settings 3";
PROGMEM const prog_char str_settings_4[] = "settings 4";
PROGMEM const prog_char str_settings_5[] = "settings 5";

menuCore menu;
subMenu menu_mode(str_mode);
subMenu menu_settings(str_settings);
menuLeaf save_defaults(str_save_defaults);

menuLeaf mode_1(str_mode_1);
menuLeaf mode_2(str_mode_2);
menuLeaf mode_3(str_mode_3);

menuLeaf settings_1(str_settings_1);
menuLeaf settings_2(str_settings_2);
menuLeaf settings_3(str_settings_3);
menuLeaf settings_4(str_settings_4);
menuLeaf settings_5(str_settings_5);

// returns pressed key
uint8_t read_buttons(button **button_array, rotaryEncoder &rotary_button) {
    uint8_t button_state;

    for(uint8_t i = 0; i < BUTTONS_COUNT; i++) {
        button_state = button_array[i]->read();
        if(button_state) {
            return button_state;
        }
    }

    button_state = rotary_button.read();
    return button_state;
}

void setup() {
    lcd.begin(20, 4);
    lcd.begin_backlight(LCD_LED_PIN, 63);

    menu.attach_display(lcd);
    menu.append(menu_mode);
    menu.append(menu_settings);
    menu.append(save_defaults);
    
    menu_mode.append(mode_1);
    menu_mode.append(mode_2);
    menu_mode.append(mode_3);

    menu_settings.append(settings_1);
    menu_settings.append(settings_2);
    menu_settings.append(settings_3);
    menu_settings.append(settings_4);
    menu_settings.append(settings_5);
    
    menu.print();

}

void loop() {
    uint8_t button_pressed;

    button_pressed = read_buttons(button_array, rotary_button);
    if(button_pressed) {
        menu.action(button_pressed);
    }

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

