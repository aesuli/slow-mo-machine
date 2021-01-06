// slow-mo machine
// Andrea Esuli  (andrea@esuli.it) 2018

// derived from:
// TimeFrame V3.0 - simple version
// Copyright (C) 2016 Cubc-Print

// esuli's code: https://github.com/aesuli/slow-mo-machine
// Cubc-Print source core here: https://www.github.com/cubic-print/timeframe

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

#define MAX_MAG_FREQ 150.0
#define MIN_MAG_FREQ 50.0
#define MIN_MAG_DUTY 0.0
#define MAX_MAG_DUTY 50.0
#define MIN_PHASE_SHIFT -4.0
#define MAX_PHASE_SHIFT 4.0
#define MIN_LED_DUTY 0.0 
#define MAX_LED_DUTY 40.0 
  
float phase_shift = 0.5; 
float frequency_mag = 80;


//Timer 2 for Magnet
//Prescaler = 1024 = CS111 = 64us/tick
//PIN 3
float duty_mag = 50;
long time_mag = round(16000000/1024/frequency_mag); 

//Timer 1 for LED
//Prescaler = 8 = CS010 = 0.5 us/tick
//PIN 10
float duty_led = 20;
float frequency_led = frequency_mag+phase_shift;
long time_led = round(16000000/8/frequency_led);
  
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

long freq_read = 100;

void loop() {
  frequency_mag = -(MAX_MAG_FREQ-MIN_MAG_FREQ)/1023L*analogRead(A0)+MAX_MAG_FREQ;
  delay(3);
  duty_mag = -(MAX_MAG_DUTY-MIN_MAG_DUTY)/1023L*analogRead(A1)+MAX_MAG_DUTY;
  delay(3);
  phase_shift = -(MAX_PHASE_SHIFT-MIN_PHASE_SHIFT)/1023L*analogRead(A2)+MAX_PHASE_SHIFT;
  delay(3);
  duty_led = -(MAX_LED_DUTY-MIN_LED_DUTY)/1023L*analogRead(A3)+MAX_LED_DUTY;
  delay(3);

  frequency_led = frequency_mag+phase_shift;

  time_mag = round(16000000L/1024L/frequency_mag); 
  time_led = round(16000000L/8L/frequency_led);

  OCR2A = round(time_mag);
  OCR2B = round(duty_mag*time_mag/100L); 
  OCR1A = round(time_led); 
  OCR1B = round(duty_led*time_led/100L);
}

void mag_on() {
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS22)| _BV(CS21)| _BV(CS20);
}

void led_on() {
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A = _BV(COM1A0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10); 
  TCCR1B =  _BV(WGM13) | _BV(WGM12)  |  _BV(CS11);
}
