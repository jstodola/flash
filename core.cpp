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
#include "timer.h"

void run();
void run_sensor();
void run_timelapse();
void run_testing_shot();
void write_config();
void read_config();
uint8_t wait_or_button(int delay);
void measure_sensor(analogSensor &sensor);
void measure_sound();
void measure_light();
void measure_pressure();
void measure_ir();
void set_backlight(int value);
void fire_flashes();
void cameras_start();
void cameras_stop();
 
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


const uint8_t MODE_SOUND     = 1;
const uint8_t MODE_LIGHT     = 2;
const uint8_t MODE_PRESSURE  = 3;
const uint8_t MODE_IR        = 4;
const uint8_t MODE_TIMELAPSE = 5;
const uint8_t MODE_TESTING_SHOT = 6;
const uint8_t MODE_DROP = 7;

// strings in program memory
PROGMEM const prog_char str_start[] = "Start";
PROGMEM const prog_char str_mode[] = "Mode";
PROGMEM const prog_char str_settings[] = "Settings";
PROGMEM const prog_char str_tools[] = "Tools";
PROGMEM const prog_char str_save_defaults[] = "Save as default";

// mode
PROGMEM const prog_char str_mode_sound[]     = "Sound (microphone)";
PROGMEM const prog_char str_mode_light[]     = "Light";
PROGMEM const prog_char str_mode_pressure[]  = "Pressure (piezo)";
PROGMEM const prog_char str_mode_ir[]        = "IR (Infrared)";
PROGMEM const prog_char str_mode_timelapse[] = "Time-lapse";
PROGMEM const prog_char str_mode_drop[]      = "Drops";

// settings
PROGMEM const prog_char str_flash[]  = "Flash";
PROGMEM const prog_char str_flash_delay[]  = "Flash delay";
PROGMEM const prog_char str_flash_delay2[] = "Flash delay [ms]";
PROGMEM const prog_char str_flash_1_enable[] = "Enable flash 1";
PROGMEM const prog_char str_flash_1_enable2[] = "Enable flash 1?";
PROGMEM const prog_char str_flash_2_enable[] = "Enable flash 2";
PROGMEM const prog_char str_flash_2_enable2[] = "Enable flash 2?";
PROGMEM const prog_char str_flash_3_enable[] = "Enable flash 3";
PROGMEM const prog_char str_flash_3_enable2[] = "Enable flash 3?";
PROGMEM const prog_char str_flash_4_enable[] = "Enable flash 4";
PROGMEM const prog_char str_flash_4_enable2[] = "Enable flash 4?";
PROGMEM const prog_char str_camera[] = "Camera";
PROGMEM const prog_char str_autofocus_time[] = "Autofocus time";
PROGMEM const prog_char str_autofocus_time2[] = "Autofocus time [ms]";
PROGMEM const prog_char str_shutter_lag[] = "Shutter lag";
PROGMEM const prog_char str_shutter_lag2[] = "Shutter lag [ms]";
PROGMEM const prog_char str_camera_bulb[]  = "Bulb";
PROGMEM const prog_char str_camera_bulb2[] = "Is time set to bulb?";
PROGMEM const prog_char str_camera_1_enable[] = "Enable camera 1";
PROGMEM const prog_char str_camera_1_enable2[] = "Enable camera 1?";
PROGMEM const prog_char str_camera_2_enable[] = "Enable camera 2";
PROGMEM const prog_char str_camera_2_enable2[] = "Enable camera 2?";
PROGMEM const prog_char str_start_delay[]  = "Start delay";
PROGMEM const prog_char str_start_delay2[] = "Start delay [s]";
PROGMEM const prog_char str_lcd_backlight[] = "LCD backlight";
PROGMEM const prog_char str_speaker_enable[] = "Enable speaker";
PROGMEM const prog_char str_speaker_enable2[] = "Enable speaker?";
PROGMEM const prog_char str_timelapse_delay[]  = "Time-lapse interval";
PROGMEM const prog_char str_timelapse_delay2[] = "Set interval [s]";
PROGMEM const prog_char str_sensor_tolerance[] = "Sensor tolerance";
PROGMEM const prog_char str_sensor_tolerance2[] = "Sensor tolerance [%]";
PROGMEM const prog_char str_calibration_duration[] = "Calibr. duration";
PROGMEM const prog_char str_calibration_duration2[] = "Calibr.duration [ms]";
PROGMEM const prog_char str_drop[] = "Drops";
PROGMEM const prog_char str_drop_1[] = "Drop 1";
PROGMEM const prog_char str_drop_2[] = "Drop 2";
PROGMEM const prog_char str_drop_3[] = "Drop 3";
PROGMEM const prog_char str_drop_4[] = "Drop 4";
PROGMEM const prog_char str_drop_1_enable[] = "Enable drop 1";
PROGMEM const prog_char str_drop_1_enable2[] = "Enable Drop 1?";
PROGMEM const prog_char str_drop_2_enable[] = "Enable drop 2";
PROGMEM const prog_char str_drop_2_enable2[] = "Enable Drop 2?";
PROGMEM const prog_char str_drop_3_enable[] = "Enable drop 3";
PROGMEM const prog_char str_drop_3_enable2[] = "Enable Drop 3?";
PROGMEM const prog_char str_drop_4_enable[] = "Enable drop 4";
PROGMEM const prog_char str_drop_4_enable2[] = "Enable Drop 4?";
PROGMEM const prog_char str_drop_delay[] = "Delay";
PROGMEM const prog_char str_drop_delay2[] = "Delay [ms]";
PROGMEM const prog_char str_drop_duration[] = "Duration";
PROGMEM const prog_char str_drop_duration2[] = "Duration [ms]";
PROGMEM const prog_char str_drop_port[] = "Port number";

// tools
PROGMEM const prog_char str_measure_sound[] = "Measure sound";
PROGMEM const prog_char str_measure_light[] = "Measure light";
PROGMEM const prog_char str_measure_pressure[] = "Measure pressure";
PROGMEM const prog_char str_measure_ir[] = "Measure IR";
PROGMEM const prog_char str_testing_shot[] = "Testing shot";


PROGMEM const prog_char str_ok[] = "OK";
PROGMEM const prog_char str_waiting[] = "Waiting... ";
PROGMEM const prog_char str_calibrating_sensor[] = "Calibrating...";
PROGMEM const prog_char str_picture[] = "Picture: ";
PROGMEM const prog_char str_minimal[] = "Minimal: ";
PROGMEM const prog_char str_maximal[] = "Maximal: ";
PROGMEM const prog_char str_current[] = "Current: ";


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

analogSensor sound_sensor(SOUND_SENSOR_PIN, DETECTS_SOUND);
analogSensor light_sensor(LIGHT_SENSOR_PIN, DETECTS_LIGHT);
analogSensor pressure_sensor(PRESSURE_SENSOR_PIN, DETECTS_SOUND);
analogSensor ir_sensor(IR_SENSOR_PIN, DETECTS_LIGHT);

buzzer speaker(BUZZER_PIN);

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
  radioItem mode_timelapse(str_mode_timelapse, &config.mode, MODE_TIMELAPSE);
  radioItem mode_drop(str_mode_drop, &config.mode, MODE_DROP);
  radioItem mode_testing_shot(str_testing_shot, &config.mode, MODE_TESTING_SHOT);

subMenu menu_settings(str_settings);
  subMenu menu_settings_flash(str_flash);
    enterNumberItem flash_delay(str_flash_delay, str_flash_delay2, &config.flash_delay);
    yesNoItem flash_1_enable(str_flash_1_enable, str_flash_1_enable2, &config.flash_1_enabled);
    yesNoItem flash_2_enable(str_flash_2_enable, str_flash_2_enable2, &config.flash_2_enabled);
    yesNoItem flash_3_enable(str_flash_3_enable, str_flash_3_enable2, &config.flash_3_enabled);
    yesNoItem flash_4_enable(str_flash_4_enable, str_flash_4_enable2, &config.flash_4_enabled);
  subMenu menu_settings_camera(str_camera);
    enterNumberItem autofocus_time(str_autofocus_time, str_autofocus_time2, &config.autofocus_time, 0, 100);
    enterNumberItem shutter_lag(str_shutter_lag, str_shutter_lag2, &config.shutter_lag, 0, 10);
    yesNoItem camera_1_enable(str_camera_1_enable, str_camera_1_enable2, &config.camera_1_enabled);
    yesNoItem camera_2_enable(str_camera_2_enable, str_camera_2_enable2, &config.camera_2_enabled);
  subMenu menu_settings_drop(str_drop);
    subMenu menu_settings_drop_1(str_drop_1);
      yesNoItem drop_1_enable(str_drop_1_enable, str_drop_1_enable2, &config.drop_1_enabled);
      enterNumberItem drop_1_delay(str_drop_delay, str_drop_delay2, &config.drop_1_delay);
      enterNumberItem drop_1_duration(str_drop_duration, str_drop_duration2, &config.drop_1_duration);
      enterNumberItem drop_1_port(str_drop_port, str_drop_port, &config.drop_1_port);
    subMenu menu_settings_drop_2(str_drop_2);
      yesNoItem drop_2_enable(str_drop_2_enable, str_drop_2_enable2, &config.drop_2_enabled);
      enterNumberItem drop_2_delay(str_drop_delay, str_drop_delay2, &config.drop_2_delay);
      enterNumberItem drop_2_duration(str_drop_duration, str_drop_duration2, &config.drop_2_duration);
      enterNumberItem drop_2_port(str_drop_port, str_drop_port, &config.drop_2_port);
    subMenu menu_settings_drop_3(str_drop_3);
      yesNoItem drop_3_enable(str_drop_3_enable, str_drop_3_enable2, &config.drop_3_enabled);
      enterNumberItem drop_3_delay(str_drop_delay, str_drop_delay2, &config.drop_3_delay);
      enterNumberItem drop_3_duration(str_drop_duration, str_drop_duration2, &config.drop_3_duration);
      enterNumberItem drop_3_port(str_drop_port, str_drop_port, &config.drop_3_port);
    subMenu menu_settings_drop_4(str_drop_4);
      yesNoItem drop_4_enable(str_drop_4_enable, str_drop_4_enable2, &config.drop_4_enabled);
      enterNumberItem drop_4_delay(str_drop_delay, str_drop_delay2, &config.drop_4_delay);
      enterNumberItem drop_4_duration(str_drop_duration, str_drop_duration2, &config.drop_4_duration);
      enterNumberItem drop_4_port(str_drop_port, str_drop_port, &config.drop_4_port);
  enterNumberItem start_delay(str_start_delay, str_start_delay2, &config.start_delay);
  enterNumberItem calibration_duration(str_calibration_duration, str_calibration_duration2, &config.calibration_duration, 0, 100);
  enterNumberItem lcd_backlight(str_lcd_backlight, str_lcd_backlight, &config.backlight, set_backlight);
  yesNoItem speaker_enable(str_speaker_enable, str_speaker_enable2, &config.speaker_enabled);
  enterNumberItem timelapse_delay(str_timelapse_delay, str_timelapse_delay2, &config.timelapse_delay);
  enterNumberItem sensor_tolerance(str_sensor_tolerance, str_sensor_tolerance2, &config.sensor_tolerance);
  yesNoItem camera_bulb(str_camera_bulb, str_camera_bulb2, &config.camera_bulb);

subMenu menu_tools(str_tools);
  menuRun tools_measure_sound(str_measure_sound, measure_sound);
  menuRun tools_measure_light(str_measure_light, measure_light);
  menuRun tools_measure_pressure(str_measure_pressure, measure_pressure);
  menuRun tools_measure_ir(str_measure_ir, measure_ir);

menuRun save_defaults(str_save_defaults, write_config);

void run() {
    switch(config.mode){
        case MODE_SOUND:
        case MODE_LIGHT:
        case MODE_PRESSURE:
        case MODE_IR:
            run_sensor();
            break;
        case MODE_TIMELAPSE:
            run_timelapse();
            break;
        case MODE_TESTING_SHOT:
            run_testing_shot();
            break;
        default:
            break;
    }
}

void fire_flashes() {

    if(config.flash_delay) {
        delay(config.flash_delay);
    }
    if(config.flash_1_enabled) {
        flash_1.fire_start();
    }
    if(config.flash_2_enabled) {
        flash_2.fire_start();
    }
    if(config.flash_3_enabled) {
        flash_3.fire_start();
    }
    if(config.flash_4_enabled) {
        flash_4.fire_start();
    }

    delay(50);

    flash_1.fire_finish();
    flash_2.fire_finish();
    flash_3.fire_finish();
    flash_4.fire_finish();

}

void cameras_start() {

    // focus
    if(config.camera_1_enabled) {
        camera_1.focus_start();
    }
    if(config.camera_2_enabled) {
        camera_2.focus_start();
    }
    delay(config.autofocus_time);
 
    // shutter
    if(config.camera_1_enabled) {
        camera_1.shutter_start();
    }
    if(config.camera_2_enabled) {
        camera_2.shutter_start();
    }
    delay(config.shutter_lag);
}

void cameras_stop() {
    camera_1.stop();
    camera_2.stop();
}

// wait for an event and fire a flash
void run_sensor() {
    
    int sensor_max;
    int sensor_min;
    int sensor_value;

    analogSensor *sensor;
    timer timer;
    
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

    lcd.clear();
    if(wait_or_button(config.start_delay * 1000)) {
        return;
    }

    if(sensor->is_light_sensor()) {

        // turn off light
        socket.on();
        delay(1000);

        // turn off display
        lcd.set_backlight_off();

        sensor->calibrate(config.calibration_duration, config.sensor_tolerance);
        sensor_min = sensor->get_minimal();
        sensor_max = sensor->get_maximal();

    } else{ 

        lcd.clear();
        strcpy_P(buffer, str_calibrating_sensor);
        lcd.print(buffer);
        
        sensor->calibrate(config.calibration_duration, config.sensor_tolerance);
        sensor_min = sensor->get_minimal();
        sensor_max = sensor->get_maximal();
        
        strcpy_P(buffer, str_ok);
        lcd.print(buffer);
        
        // turn off light
        socket.on();
        delay(1000);

        // turn off display
        lcd.set_backlight_off();
    }

    cameras_start();

    while(1) {
        sensor_value = sensor->get_value();
        if(sensor_value < sensor_min || sensor_value > sensor_max) {
            fire_flashes();
            break;
        }
        
        // action canceled by user
        if(button_rc1.read() || button_ok.read()) {
            break;
        }
    }

    cameras_stop();;

    delay(500);

    lcd.set_backlight_on();
    // turn on light
    socket.off();
}

// wait until time is reached or any
// button is pressed
uint8_t wait_or_button(int delay) {
 
    uint8_t button_pressed;
    timer timer;
    int current_remaining;
    int last_remaining = 0;

    timer.set(delay);
    timer.start();
    button_pressed = buttons_reader.read();
    if(button_pressed != IDLE) {
        return button_pressed;
    }
    while(timer.is_running()) {
        button_pressed = buttons_reader.read();
        if(button_pressed != IDLE) {
            return button_pressed;
        }
        current_remaining = timer.remain_seconds();
        if(current_remaining != last_remaining) {
            lcd.setCursor(0, lcd.get_rows() - 1);
            for(uint8_t i = 0; i < lcd.get_columns(); i++) {
                lcd.print(" ");
            }
            lcd.setCursor(0, lcd.get_rows() - 1);
            strcpy_P(buffer, str_waiting);
            lcd.print(buffer);
            lcd.print(current_remaining);
            last_remaining = current_remaining;
        }
    }
    return 0;
}

void run_timelapse() {

    uint8_t button_pressed;
    uint16_t image_number = 0;
    uint8_t repeat = 1;
    timer timer;

    while(repeat) {
        lcd.clear();
        strcpy_P(buffer, str_picture);
        lcd.print(buffer);
        lcd.print(++image_number);

        if(wait_or_button(200)) {
            repeat = 0;
        } 

        cameras_start();
        
        wait_or_button(50);
        
        if(config.camera_bulb) {
            button_pressed = wait_or_button(config.timelapse_delay * 1000);
            cameras_stop();
        } else {
            cameras_stop();
            button_pressed = wait_or_button(config.timelapse_delay * 1000);
        }
        
        if(button_pressed) {
            repeat = 0;
        }
    }
}

void run_testing_shot() {
    
    // turn off light
    socket.on();
    delay(1000);

    // turn off display
    lcd.set_backlight_off();
    
    cameras_start();

    wait_or_button(400);

    fire_flashes();

    cameras_stop();

    delay(500);

    lcd.set_backlight_on();
    // turn on light
    socket.off();
}


void set_backlight(int value) {
    lcd.set_backlight(value);
}

void measure_sensor(analogSensor &sensor) {

    int minimal, maximal, current, buzzer_frequency;
    unsigned long last_displayed = 0;
    unsigned long last_beep = 0;

    current = sensor.get_value();
    minimal = current;
    maximal = current;

    while(1) {
        current = sensor.get_value();
        if(current < minimal) {
            minimal = current;
        }
        if(current > maximal) {
            maximal = current;
        }
        
        // beep according to intensity of input signal
        if(config.speaker_enabled && sensor.is_light_sensor()) {
            // low value - beep 1/s
            // high value - beep 100/s
            buzzer_frequency = map(current, 0, 1023, 1, 100);
            if(millis() - last_beep >= (1000 / buzzer_frequency)) {
                speaker.beep();
                last_beep = millis();
            }
        }
        
        if(millis() - last_displayed >= 100) { // refresh every 100 ms
            lcd.clear();
            
            lcd.setCursor(0, 1);
            strcpy_P(buffer, str_current);
            lcd.print(buffer);
            lcd.print(current);

            lcd.setCursor(0, 2);
            strcpy_P(buffer, str_minimal);
            lcd.print(buffer);
            lcd.print(minimal);

            lcd.setCursor(0, 3);
            strcpy_P(buffer, str_maximal);
            lcd.print(buffer);
            lcd.print(maximal);

            last_displayed = millis();
        } 
        if(buttons_reader.read() != IDLE) {
            return;
        }
    }
}

void measure_sound() {
    measure_sensor(sound_sensor);
}

void measure_light() {
    measure_sensor(light_sensor);
}

void measure_pressure() {
    measure_sensor(pressure_sensor);
}

void measure_ir() {
    measure_sensor(ir_sensor);
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
        menu_mode.append(mode_sound);
        menu_mode.append(mode_light);
        menu_mode.append(mode_pressure);
        menu_mode.append(mode_ir);
        menu_mode.append(mode_timelapse);
        menu_mode.append(mode_drop);
        menu_mode.append(mode_testing_shot);
    menu.append(menu_settings);
        menu_settings.append(menu_settings_flash);
            menu_settings_flash.append(flash_delay);
            menu_settings_flash.append(flash_1_enable);
            menu_settings_flash.append(flash_2_enable);
            menu_settings_flash.append(flash_3_enable);
            menu_settings_flash.append(flash_4_enable);
        menu_settings.append(menu_settings_camera);
            menu_settings_camera.append(autofocus_time);
            menu_settings_camera.append(shutter_lag);
            menu_settings_camera.append(camera_bulb);
            menu_settings_camera.append(camera_1_enable);
            menu_settings_camera.append(camera_2_enable);
        menu_settings.append(menu_settings_drop);
            menu_settings_drop.append(menu_settings_drop_1);
                menu_settings_drop_1.append(drop_1_enable);
                menu_settings_drop_1.append(drop_1_delay);
                menu_settings_drop_1.append(drop_1_duration);
                menu_settings_drop_1.append(drop_1_port);
            menu_settings_drop.append(menu_settings_drop_2);
                menu_settings_drop_2.append(drop_2_enable);
                menu_settings_drop_2.append(drop_2_delay);
                menu_settings_drop_2.append(drop_2_duration);
                menu_settings_drop_2.append(drop_2_port);
            menu_settings_drop.append(menu_settings_drop_3);
                menu_settings_drop_3.append(drop_3_enable);
                menu_settings_drop_3.append(drop_3_delay);
                menu_settings_drop_3.append(drop_3_duration);
                menu_settings_drop_3.append(drop_3_port);
            menu_settings_drop.append(menu_settings_drop_4);
                menu_settings_drop_4.append(drop_4_enable);
                menu_settings_drop_4.append(drop_4_delay);
                menu_settings_drop_4.append(drop_4_duration);
                menu_settings_drop_4.append(drop_4_port);
        menu_settings.append(start_delay);
        menu_settings.append(calibration_duration);
        menu_settings.append(lcd_backlight);
        menu_settings.append(speaker_enable);
        menu_settings.append(sensor_tolerance);
        menu_settings.append(timelapse_delay);
    menu.append(menu_tools);
        menu_tools.append(tools_measure_sound);
        menu_tools.append(tools_measure_light);
        menu_tools.append(tools_measure_pressure);
        menu_tools.append(tools_measure_ir);
    menu.append(save_defaults);
    
    menu.print();
}

void loop() {
    uint8_t button_pressed;

    button_pressed = buttons_reader.read();
    
    if(button_pressed == RC1) {
        run();
        menu.print();   // redraw menu
    } else if(button_pressed) {
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

