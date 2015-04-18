#include <Arduino.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "core.h"
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


// shutter speeds * 10
const uint16_t shutter_speeds[] = {
               10, 13, 16, 20, 25, 30, 40, 50, 60, 80, 100, 130, 150, 200,
               250, 300, 400, 500, 600, 800, 1000, 1250, 1600, 2000, 2500, 
               3200, 4000, 5000, 6400, 8000, 10000, 12500, 16000, 20000, 
               25000, 32000, 40000};

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
  radioItem mode_hdr(str_mode_hdr, &config.mode, MODE_HDR);
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
  subMenu menu_settings_hdr(str_hdr);
    enterShutterSpeed shutter_speed_shortest(str_shutter_speed_shortest, str_shutter_speed, &config.shutter_speed_shortest_index, shutter_speeds, sizeof(shutter_speeds)/sizeof(shutter_speeds[0]));
    enterShutterSpeed shutter_speed_longest(str_shutter_speed_longest, str_shutter_speed, &config.shutter_speed_longest_index, shutter_speeds, sizeof(shutter_speeds)/sizeof(shutter_speeds[0]));
    enterNumberItem hdr_shoots(str_hdr_shoots, str_hdr_shoots, &config.hdr_shoots);
  enterNumberItem start_delay(str_start_delay, str_start_delay2, &config.start_delay);
  enterNumberItem calibration_duration(str_calibration_duration, str_calibration_duration2, &config.calibration_duration, 0, 100);
  enterNumberItem lcd_backlight(str_lcd_backlight, str_lcd_backlight, &config.backlight, set_backlight);
  yesNoItem speaker_enable(str_speaker_enable, str_speaker_enable2, &config.speaker_enabled);
  enterNumberItem timelapse_interval(str_timelapse_interval, str_timelapse_interval2, &config.timelapse_interval);
  enterNumberItem sensor_tolerance(str_sensor_tolerance, str_sensor_tolerance2, &config.sensor_tolerance);
  yesNoItem camera_bulb(str_camera_bulb, str_camera_bulb2, &config.camera_bulb);
  menuRun save_configuration(str_save_configuration, write_config);
  menuRun reset_defaults(str_reset_defaults, initialize_eeprom);

subMenu menu_tools(str_tools);
  menuRun tools_measure_sound(str_measure_sound, measure_sound);
  menuRun tools_measure_light(str_measure_light, measure_light);
  menuRun tools_measure_pressure(str_measure_pressure, measure_pressure);
  menuRun tools_measure_ir(str_measure_ir, measure_ir);
  menuDialog tools_open_valves(str_open_valves, str_open_valves2, open_valves, close_valves);


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
        case MODE_HDR:
            run_hdr();
            break;
        case MODE_DROP:
            run_drop();
            break;
        case MODE_TESTING_SHOT:
            run_testing_shot();
            break;
        default:
            break;
    }
}

void fire_flashes(int flash_delay) {

    if(flash_delay) {
        delay(flash_delay);
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
            fire_flashes(config.flash_delay);
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
            button_pressed = wait_or_button(config.timelapse_interval * 1000);
            cameras_stop();
        } else {
            cameras_stop();
            button_pressed = wait_or_button(config.timelapse_interval * 1000);
        }
        
        if(button_pressed) {
            repeat = 0;
        }
    }
}

void run_hdr() {

    // in seconds
    double shortest = shutter_index_to_seconds(config.shutter_speed_shortest_index, shutter_speeds);
    double longest = shutter_index_to_seconds(config.shutter_speed_longest_index, shutter_speeds);
    double delay_time;

    uint8_t button_pressed;

    // take at least two pictures
    if(config.hdr_shoots < 2) {
        return;
    }

    for(uint8_t cycle=0; cycle<config.hdr_shoots; cycle++){

        delay_time = pow(2, (log2(shortest) + ((cycle * (log2(longest) - log2(shortest))) / (config.hdr_shoots - 1))));

        lcd.clear();
        strcpy_P(buffer, str_picture);
        lcd.print(buffer);
        lcd.print(cycle + 1);
        lcd.setCursor(0, 1);
        strcpy_P(buffer, str_exposure);
        lcd.print(buffer);
        lcd.print(round(delay_time * 1000));
        lcd.print(F(" ms"));

        cameras_start();
        button_pressed = wait_or_button(delay_time * 1000);
        cameras_stop();

        // delay between shoots
        button_pressed += wait_or_button(500);

        if(button_pressed) {
            break;
        }
    }
}

void check_and_open_valve(uint8_t enabled, int count_ms, int drop_delay, int drop_port) {
    if(enabled && count_ms == drop_delay) {
        switch(drop_port) {
            case 1:
                output_1_12v.on();
                break;
            case 2:
                output_2_12v.on();
                break;
            case 3:
                output_3_12v.on();
                break;
        }
    }
}

void check_and_close_valve(uint8_t enabled, int count_ms, int drop_delay, int drop_duration, int drop_port) {
    if(enabled && count_ms == drop_delay + drop_duration) {
        switch(drop_port) {
            case 1:
                output_1_12v.off();
                break;
            case 2:
                output_2_12v.off();
                break;
            case 3:
                output_3_12v.off();
                break;
        }
    }
}

void open_valves() {
    output_1_12v.on();
    output_2_12v.on();
    output_3_12v.on();
}

void close_valves() {
    output_1_12v.off();
    output_2_12v.off();
    output_3_12v.off();
}

void run_drop() {

    int count_ms;

    // turn off light
    socket.on();
    delay(1000);

    // turn off display
    lcd.set_backlight_off();

    cameras_start();

    for(count_ms = 0; count_ms < config.flash_delay; count_ms++) {
        check_and_open_valve(config.drop_1_enabled, count_ms, config.drop_1_delay, config.drop_1_port);
        check_and_open_valve(config.drop_2_enabled, count_ms, config.drop_2_delay, config.drop_2_port);
        check_and_open_valve(config.drop_3_enabled, count_ms, config.drop_3_delay, config.drop_3_port);
        check_and_open_valve(config.drop_4_enabled, count_ms, config.drop_4_delay, config.drop_4_port);

        check_and_close_valve(config.drop_1_enabled, count_ms, config.drop_1_delay, config.drop_1_duration, config.drop_1_port);
        check_and_close_valve(config.drop_2_enabled, count_ms, config.drop_2_delay, config.drop_2_duration, config.drop_2_port);
        check_and_close_valve(config.drop_3_enabled, count_ms, config.drop_3_delay, config.drop_3_duration, config.drop_3_port);
        check_and_close_valve(config.drop_4_enabled, count_ms, config.drop_4_delay, config.drop_4_duration, config.drop_4_port);

        delay(1);
    }

    // close all valves, just for sure
    output_1_12v.off();
    output_2_12v.off();
    output_3_12v.off();

    fire_flashes();
    cameras_stop();

    delay(500);
    lcd.set_backlight_on();

    //turn on light
    socket.off();
}

void run_testing_shot() {
    
    // turn off light
    socket.on();
    delay(1000);

    // turn off display
    lcd.set_backlight_off();
    
    cameras_start();

    wait_or_button(400);

    fire_flashes(config.flash_delay);

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
        menu_mode.append(mode_hdr);
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
        menu_settings.append(menu_settings_hdr);
            menu_settings_hdr.append(shutter_speed_shortest);
            menu_settings_hdr.append(shutter_speed_longest);
            menu_settings_hdr.append(hdr_shoots);
        menu_settings.append(start_delay);
        menu_settings.append(calibration_duration);
        menu_settings.append(lcd_backlight);
        menu_settings.append(speaker_enable);
        menu_settings.append(sensor_tolerance);
        menu_settings.append(timelapse_interval);
        menu_settings.append(save_configuration);
        menu_settings.append(reset_defaults);
    menu.append(menu_tools);
        menu_tools.append(tools_measure_sound);
        menu_tools.append(tools_measure_light);
        menu_tools.append(tools_measure_pressure);
        menu_tools.append(tools_measure_ir);
        menu_tools.append(tools_open_valves);
    
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

