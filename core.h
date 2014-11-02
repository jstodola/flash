#ifndef CORE_H
#define CORE_H

#include "analogSensor.h"

void run();
void run_sensor();
void run_timelapse();
void run_hdr();
void run_drop();
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
void fire_flashes(int flash_delay = 0);
void cameras_start();
void cameras_stop();
void check_and_open_valve(uint8_t enabled, int count_ms, int drop_delay, int drop_port);
void check_and_close_valve(uint8_t enabled, int count_ms, int drop_delay, int drop_duration, int drop_port);

//PINs
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

// strings in program memory
PROGMEM const prog_char str_start[] = "Start";
PROGMEM const prog_char str_mode[] = "Mode";
PROGMEM const prog_char str_settings[] = "Settings";
PROGMEM const prog_char str_tools[] = "Tools";

// mode
PROGMEM const prog_char str_mode_sound[]     = "Sound (microphone)";
PROGMEM const prog_char str_mode_light[]     = "Light";
PROGMEM const prog_char str_mode_pressure[]  = "Pressure (piezo)";
PROGMEM const prog_char str_mode_ir[]        = "IR (Infrared)";
PROGMEM const prog_char str_mode_timelapse[] = "Time-lapse";
PROGMEM const prog_char str_mode_hdr[]       = "HDR";
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
PROGMEM const prog_char str_timelapse_interval[]  = "Time-lapse interval";
PROGMEM const prog_char str_timelapse_interval2[] = "Set interval [s]";
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
PROGMEM const prog_char str_hdr[] = "HDR";
PROGMEM const prog_char str_shutter_speed_shortest[] = "Shutter sp. short.";
PROGMEM const prog_char str_shutter_speed_longest[]  = "Shutter sp. long.";
PROGMEM const prog_char str_shutter_speed[]   = "Shutter speed [s]";
PROGMEM const prog_char str_hdr_shoots[]   = "Number of shoots";
PROGMEM const prog_char str_save_configuration[] = "Save configuration";
PROGMEM const prog_char str_reset_defaults[] = "Reset to defaults";

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
PROGMEM const prog_char str_exposure[] = "Exposure: ";


#endif
