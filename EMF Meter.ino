#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int numReadings = 5;
int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;            // the average
int inputPin = A0;
LiquidCrystal_I2C lcd(0x27, 16, 3);
void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  lcd.init();
  lcd.backlight();
}
void loop() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println("____________________");
  Serial.print("ADC ");
  Serial.println(average);
  delay(500);
  int voltageval = map(average, 300, 900, 0, 80);
  Serial.print("Voltage ");
  Serial.println(voltageval);
  double hfval = mapf(average, 900, 0, 0.20, 5.25);
  if (hfval < 0) {
    hfval = 0;
  }
  Serial.print("hfval ");
  Serial.println(hfval);
  int efval = map(average, 900, 250, 0, 170);
  if (efval < 0) {
    efval = 0;
  }
  Serial.print("efval ");
  Serial.println(efval);
  lcd.clear();
  String v = String(voltageval);
  v.trim();
  Serial.println(v.length());
  String mf = String(hfval);
  mf.trim();
  String emf = String(efval);
  emf.trim();
  lcd.print("**LTLC DETECTOR**");
  lcd.setCursor(0, 2);
  lcd.print("HMF(uT):" + mf);
  lcd.setCursor(0, 3);
  lcd.print("EMF(V/m):" + emf);
  lcd.setCursor(1, 4);
  Serial.println("____________________");
  if((emf.toInt()) > 50){
    tone(11, emf.toInt(), 500); //pin, frequency, duration
  }
  else{
    tone(11, 0, 0); //pin, frequency, duration
  }
}
double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
