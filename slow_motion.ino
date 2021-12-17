// slow dance
// Andrea Esuli (andrea@esuli.it) 2018

// derived from:
// TimeFrame V3.0 - simple version
// Copyright (C) 2016 Cubc-Print

// esuli's code: http://github.com/aesuli/slowdance
// Cubc-Print source code: http://www.github.com/cubic-print/timeframe

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    GNU General Public License terms: <http://www.gnu.org/licenses/>.

#define MAX_MAG_FREQ 120.0
#define MIN_MAG_FREQ 30.0
#define MIN_MAG_DUTY 10.0
#define MAX_MAG_DUTY 60.0
#define MIN_PHASE_SHIFT 0.1
#define MAX_PHASE_SHIFT 5.0
#define MIN_LED_DUTY 1.0 
#define MAX_LED_DUTY 100.0 
#define ALWAYS_OFF_THRESHOLD 100
  
float phase_shift = 0.5; 
float freq_mag = 80;

bool is_mag_on = false;
bool is_led_on = false;

//Timer 2 for Magnet
//Prescaler = 1024 = CS111 = 64us/tick
//PIN 3
float duty_mag = 50;
long time_mag = round(16000000/1024/freq_mag); 

//Timer 1 for LED
//Prescaler = 8 = CS010 = 0.5 us/tick
//PIN 10
float duty_led = 20;
float freq_led = freq_mag+phase_shift;
long time_led = round(16000000/8/freq_led);
  
void setup() {
  pinMode(A0, INPUT); // magnet frequency
  pinMode(A1, INPUT); // magnet duty

  pinMode(A2, INPUT); // led shift
  pinMode(A3, INPUT); // led duty

  pinMode(3, OUTPUT); //MAG: Timer 2B cycle output
  pinMode(10, OUTPUT); //LED: Timer 1B cycle output 
  
  mag_on();
  OCR2A = round(time_mag); //output compare register
  OCR2B = round(duty_mag*time_mag/100L); // output compare registers
  
  led_on();
  OCR1A = round(time_led); //output compare registers
  OCR1B = round(duty_led*time_led/100L); // output compare registers
}

void loop() {
  float freq_mag_read = analogRead(A0);
  float duty_mag_read = analogRead(A1);
  float phase_shit_read = analogRead(A2);
  float duty_led_read = analogRead(A3);

  freq_mag = MAX_MAG_FREQ-(MAX_MAG_FREQ-MIN_MAG_FREQ)/1023L*freq_mag_read;
  delay(3);

  if(duty_mag_read<ALWAYS_OFF_THRESHOLD) {
    mag_off();
  }
  else {
    mag_on();
    long duty_mag_range = 1023L-ALWAYS_OFF_THRESHOLD;
    duty_mag = MAX_MAG_DUTY-(MAX_MAG_DUTY-MIN_MAG_DUTY)/duty_mag_range*(duty_mag_read-ALWAYS_OFF_THRESHOLD); 
  }
  delay(3);
  
  phase_shift = MAX_PHASE_SHIFT-(MAX_PHASE_SHIFT-MIN_PHASE_SHIFT)/1023L*phase_shit_read;
  delay(3);

  if(duty_led_read<ALWAYS_OFF_THRESHOLD) {
    led_off();
  }
  else {
    led_on();
    duty_led = MAX_LED_DUTY-(MAX_LED_DUTY-MIN_LED_DUTY)/1023L*(duty_led_read-ALWAYS_OFF_THRESHOLD);
  }
  delay(3);

  freq_led = freq_mag+phase_shift;

  time_mag = round(16000000L/1024L/freq_mag); 
  time_led = round(16000000L/8L/freq_led);

  OCR2A = round(time_mag);
  OCR2B = round(duty_mag*time_mag/100L); 
  OCR1A = round(time_led); 
  OCR1B = round(duty_led*time_led/100L);
}

void mag_on() {
  if(!is_mag_on) {
    is_mag_on = true;
    TCCR2A = 0;
    TCCR2B = 0;
    TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(WGM22) | _BV(CS22)| _BV(CS21)| _BV(CS20);
  }
}

void mag_off() {
  if(is_mag_on) {
    is_mag_on = false;
    TCCR2A = 0;
    TCCR2B = 0;
    TCCR2A = _BV(COM2A0) | _BV(COM2B1);
    TCCR2B = _BV(CS22)| _BV(CS21)| _BV(CS20); 
  }
}

void led_on() {
  if(!is_led_on) {
    is_led_on = true;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1A = _BV(COM1A0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10); 
    TCCR1B =  _BV(WGM13) | _BV(WGM12)  |  _BV(CS11);
  }
}

void led_off() {
  if(is_led_on) {
    is_led_on = false;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1A = _BV(COM1A0) | _BV(COM1B1); 
    TCCR1B =  _BV(CS11); 
  }
}  
