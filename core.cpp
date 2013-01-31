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
#include "eeprom_config.h"

void run();
void write_config();
void read_config();

const uint8_t LCD_LED_PIN    =  2;
const uint8_t LCD_RS_PIN     = 23;
const uint8_t LCD_ENABLE_PIN = 25;
const uint8_t LCD_DB4_PIN    = 27;
const uint8_t LCD_DB5_PIN    = 29;
const uint8_t LCD_DB6_PIN    = 31;
const uint8_t LCD_DB7_PIN    = 33;

const uint8_t SOUND_SENSOR_PIN    = A4;
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

const uint8_t SOCKET_PIN       = 38;
const uint8_t OUTPUT_1_12V_PIN = 40;
const uint8_t OUTPUT_2_12V_PIN = 42;
const uint8_t OUTPUT_3_12V_PIN = 44;
const uint8_t OUTPUT_1_5V_PIN  = 46;
const uint8_t OUTPUT_2_5V_PIN  = 48;
const uint8_t OUTPUT_3_5V_PIN  = 50;


const uint8_t MODE_SOUND    = 1;
const uint8_t MODE_LIGHT    = 2;
const uint8_t MODE_PRESSURE = 3;
const uint8_t MODE_IR       = 4;

// strings in program memory
PROGMEM const prog_char str_start[] = "Start";
PROGMEM const prog_char str_mode[] = "Mode...";
PROGMEM const prog_char str_settings[] = "Settings...";
PROGMEM const prog_char str_save_defaults[] = "Save as default";

// mode
PROGMEM const prog_char str_mode_sound[]    = "Sound (microphone)";
PROGMEM const prog_char str_mode_light[]    = "Light";
PROGMEM const prog_char str_mode_pressure[] = "Pressure (piezo)";
PROGMEM const prog_char str_mode_ir[]       = "IR (Infrared)";

// settings
PROGMEM const prog_char str_flash_delay[]  = "Flash delay";
PROGMEM const prog_char str_flash_delay2[] = "Flash delay [ms]";
PROGMEM const prog_char str_start_delay[]  = "Start delay";
PROGMEM const prog_char str_start_delay2[] = "Start delay [s]";
PROGMEM const prog_char str_lcd_backlight[]  = "LCD backlight";

PROGMEM const prog_char str_ok[] = "OK";
PROGMEM const prog_char str_waiting[] = "Waiting... ";
PROGMEM const prog_char str_calibrating_sensor[] = "Calibrating sensor...";


display lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DB4_PIN, LCD_DB5_PIN, LCD_DB6_PIN, LCD_DB7_PIN);

button button_up(BUTTON_UP_PIN, UP);
button button_down(BUTTON_DOWN_PIN, DOWN);
button button_left(BUTTON_LEFT_PIN, LEFT);
button button_right(BUTTON_RIGHT_PIN, RIGHT);
button button_ok(BUTTON_OK_PIN, OK);
button button_rc1(BUTTON_RC1_PIN, RC1);
button button_rc2(BUTTON_RC2_PIN, RC2);
rotaryEncoder rotary_button(ROT_CH_A_PIN, ROT_CH_B_PIN, UP, DOWN);

buttonsReader buttons_reader;

camera camera_1(CAMERA_1_FOCUS_PIN, CAMERA_1_SHUTTER_PIN);
camera camera_2(CAMERA_2_FOCUS_PIN, CAMERA_2_SHUTTER_PIN);

flash flash_1(FLASH_1_PIN);
flash flash_2(FLASH_2_PIN);
flash flash_3(FLASH_3_PIN);
flash flash_4(FLASH_4_PIN);

analogSensor sound_sensor(SOUND_SENSOR_PIN);
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


// for PROGMEM strings
char buffer[30];

// menu
menuCore menu;
menuRun menu_start(str_start, run);
subMenu menu_mode(str_mode);
  radioItem mode_sound(str_mode_sound, &config.mode, MODE_SOUND);
  radioItem mode_light(str_mode_light, &config.mode, MODE_LIGHT);
  radioItem mode_pressure(str_mode_pressure, &config.mode, MODE_PRESSURE);
  radioItem mode_ir(str_mode_ir, &config.mode, MODE_IR);

subMenu menu_settings(str_settings);
  enterNumberItem flash_delay(str_flash_delay, str_flash_delay2, &config.flash_delay);
  enterNumberItem start_delay(str_start_delay, str_start_delay2, &config.start_delay);
  enterNumberItem lcd_backlight(str_lcd_backlight, str_lcd_backlight, &config.backlight);

menuRun save_defaults(str_save_defaults, write_config);

// wait for an event and fire a flash
void run() {
    
    int sensor_max;
    int sensor_min;
    int sensor_value;

    analogSensor *sensor;
    
    switch(config.mode) {
        case MODE_SOUND:
            sensor = &sound_sensor;
            break;
        case MODE_LIGHT:
            sensor = &light_sensor;
            break;
        case MODE_PRESSURE:
            sensor = &pressure_sensor;
            break;
        case MODE_IR:
            sensor = &ir_sensor;
            break;
        default:
            return;
    }
    
    for(int i = 0; i < config.start_delay; i++) {
        lcd.clear();
        strcpy_P(buffer, str_waiting);
        lcd.print(buffer);
        lcd.print(config.start_delay - i);
        delay(1000);
    }

    lcd.clear();
    strcpy_P(buffer, str_calibrating_sensor);
    lcd.print(buffer);
    
    sensor->calibrate(1000);
    sensor_min = sensor->get_minimal();
    sensor_max = sensor->get_maximal();
    
    strcpy_P(buffer, str_ok);
    lcd.print(buffer);
    
    // turn off light
    socket.on();
    delay(1000);

    // turn off display
    lcd.set_backlight(0);
    
    camera_1.start();

    while(1) {
        sensor_value = sensor->get_value();
        if(sensor_value < sensor_min || sensor_value > sensor_max) {
            if(config.flash_delay) {
                delay(config.flash_delay);
            }
            flash_1.fire();
            break;
        }
        
        // action canceled by user
        if(button_rc1.read()) {
            break;
        }
    }

    camera_1.stop();

    delay(500);

    lcd.set_backlight(config.backlight);
    // turn on light
    socket.off();
}

void setup() {

    read_config();

    lcd.begin(20, 4);
    lcd.begin_backlight(LCD_LED_PIN, config.backlight);

    buttons_reader.add_button(button_up);
    buttons_reader.add_button(button_down);
    buttons_reader.add_button(button_left);
    buttons_reader.add_button(button_right);
    buttons_reader.add_button(button_ok);
    buttons_reader.add_button(button_rc1);
    buttons_reader.add_button(button_rc2);
    buttons_reader.add_button(rotary_button);

    menu.attach_display(lcd);

    menu.append(menu_start);
    menu.append(menu_mode);
    menu.append(menu_settings);
    menu.append(save_defaults);
    
    menu_mode.append(mode_sound);
    menu_mode.append(mode_light);
    menu_mode.append(mode_pressure);
    menu_mode.append(mode_ir);

    menu_settings.append(flash_delay);
    menu_settings.append(start_delay);
    menu_settings.append(lcd_backlight);
    
    menu.print();

}

void loop() {
    uint8_t button_pressed;

    button_pressed = buttons_reader.read();
    
    if(button_pressed == RC1) {
        run();
    }
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

