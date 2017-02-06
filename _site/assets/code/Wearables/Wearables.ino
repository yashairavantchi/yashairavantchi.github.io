// which analog pin to connect
#define HRMPIN A0
#define THERMISTORPIN A1
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer
// but is more 'smooth', this only works for TEMP
#define NUMSAMPLES 1
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000
// the sampling rate
#define SAMPLINGRATE 10000
// the analog read resolution
#define RESOLUTION 10
// Which values to display, set 0 for HRM, 1 for TEMP, 2 for BOTH
#define DISPLAY 2


// Include relevant libraries
#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

// Some code to make the SAMD boards happy
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(10000);

int samples[NUMSAMPLES];
int bits = pow(2,RESOLUTION)-1;
const int chipSelect = 9;

void setup(void) {


  Serial.begin(9600);

  /* SD CARD SETUP */
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("NO SD");
    // don't do anything more:
   // return;
  }
  Serial.println("SD Init");

  /* ACC SETUP */
  //Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  //if (!accel.begin())
  //{
    /* There was a problem detecting the ADXL345 ... check your connections */
    //Serial.println("NO ACC");
    //while (1);
  //}
  //Serial.println("ACC Init");
  //analogReference(EXTERNAL);
  //Fix Pins
  pinMode(HRMPIN, INPUT_PULLUP);
  pinMode(THERMISTORPIN, INPUT_PULLUP);

}

void loop(void) {

  analogReadResolution(RESOLUTION);

  //HRM Section

  float hrm = float(analogRead(HRMPIN)) / bits * 3.3;
  

  //ACC Section
  //sensors_event_t event;
  //accel.getEvent(&event);
  //float mag = (sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) + sq(event.acceleration.z))) / 9.8;

  // Temperature Reading Section
  uint8_t i;
  float average;

  // take N samples in a row, with a slight delay
  for (i = 0; i < NUMSAMPLES; i++) {
    samples[i] = analogRead(THERMISTORPIN);
  }

  // average all the samples out
  average = 0;
  for (i = 0; i < NUMSAMPLES; i++) {
    average += samples[i];
  }
  average /= NUMSAMPLES;

  // convert the value to resistance
  average =  bits / average - 1;
  average = SERIESRESISTOR / average;

  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C

  // Print section  
  if (DISPLAY == 0){
    Serial.println(hrm);
  }

  if (DISPLAY == 1){
    Serial.println(steinhart);
  }

  if (DISPLAY == 2){
    Serial.print(hrm);
    Serial.print(" ");
    Serial.println(steinhart);    
  }

  float period = 1000 / SAMPLINGRATE;
  delay(period);
}

