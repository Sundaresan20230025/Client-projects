#include <SoftwareSerial.h>
SoftwareSerial SIM900(13, 15); //rx tx
char incomingChar;
int flag = 0;
int flag1 = 0;
int a = 1;
const int numReadings = 100;
int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;            // the average
String SP_name = "";
//FOR VOLTAGE SENSOR
float vout = 0.0;
float vin = 0.0;
float R1 = 30000;
float R2 = 7500;
float value = 0;
String SMS;
float vi, avg;
int sensor = A0; // VOLTAGE SENSOR
int lm = 14;      // LIMITSWITCH// D5 to ground
int lmrf = 0;
int led = 2;    // D4 to led
int POWLED = 12;
String _buffer;
int _timeout;
String number1 = "+919344702578";
String number2 = "+919052214221";
String number3 = "+917799193256";
String number4 = "+919444530360";
String number5 = "+917010897188";

void setup() {
  Serial.begin(9600);
  SIM900.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(POWLED, OUTPUT);
  pinMode(lm, INPUT_PULLUP);
  delay(5000);
  Serial.print("SIM900 ready...");
  delay(1000);
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  SIM900.println("AT\r\n");
  delay(100);
  SIM900.println("AT+CLIP=1\r\n");//enable caller id
  delay(100);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
boolean SMSRequest() {
  if (SIM900.available() > 0) {
    while (SIM900.available())
    {
      read_voltage();
      read_lm();
      char character = SIM900.read();
      String line = SIM900.readStringUntil('\n');
      int index_line = line.indexOf("+91");//find the position of phn_initial
      index_line += 3;
      line = line.substring(index_line, index_line + 10); //seperate phone number from main String
      int line_len = line.length() + 1;
      char phn[line_len];
      line.toCharArray(phn, line_len);
      if (line_len >= 10)
      {
        Serial.print("Phn:");
        Serial.println(phn);
        if (String(phn) == "9344702578") {
          SIM900.println("AT+CHUP");
          Serial.print("...Request Received \n");
          return true;
        }
        if (String(phn) == "9052214221") {
          SIM900.println("AT+CHUP");
          Serial.print("...Request Received \n");
          return true;
        }
        if (String(phn) == "7799193256") {
          SIM900.println("AT+CHUP");
          Serial.print("...Request Received \n");
          return true;
        }
        if (String(phn) == "9444530360") {
          SIM900.println("AT+CHUP");
          Serial.print("...Request Received \n");
          return true;
        }
        if (String(phn) == "7010897188") {
          SIM900.println("AT+CHUP");
          Serial.print("...Request Received \n");
          return true;
        }
        else {
          SIM900.println("AT+CHUP");
          return false;
        }
      }
    }
  }
   return false;
}

void loop() {
  read_voltage();
  read_lm();
  if (SMSRequest()) {
    read_voltage();
    digitalWrite(led, HIGH);
    Serial.println ("Sending Message1");
    SIM900.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
    delay(1000);
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number1 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Mid point PSP between  RCP 10 and Madurai station  is = -" + String(vin) + "volt @ CH 505.870Km";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message2");
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number2 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Mid point PSP between  RCP 10 and Madurai station  is = -" + String(vin) + "volt @ CH 505.870Km";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message3");
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number3 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Mid point PSP between  RCP 10 and Madurai station  is = -" + String(vin) + "volt @ CH 505.870Km";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message4");
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number4 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Mid point PSP between  RCP 10 and Madurai station  is = -" + String(vin) + "volt @ CH 505.870Km";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message5");
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number5 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Mid point PSP between  RCP 10 and Madurai station  is = -" + String(vin) + "volt @ CH 505.870Km";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    digitalWrite(led, LOW);
    _buffer = _readSerial();
  }
}
void read_lm() {
  Serial.println("********************" + String(digitalRead(lm)));
  if ( (digitalRead(lm) == LOW) && (flag == 0) ) {
    digitalWrite(led, HIGH);
    Serial.println("Limit Switch Activated");
    Serial.println ("Sending Message1");
    SIM900.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
    delay(1000);
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number1 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Warning !!!!!! CTMPL mainline- Vaigai river crossing  downstream HOV's CH-505.870km fencing gate is opened. Kindly contact the LSM";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message2");
    SIM900.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
    delay(1000);
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number2 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Warning !!!!!! CTMPL mainline- Vaigai river crossing  downstream HOV's CH-505.870km fencing gate is opened. Kindly contact the LSM";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message3");
    SIM900.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
    delay(1000);
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number3 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Warning !!!!!! CTMPL mainline- Vaigai river crossing  downstream HOV's CH-505.870km fencing gate is opened. Kindly contact the LSM";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message4");
    SIM900.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
    delay(1000);
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number4 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Warning !!!!!! CTMPL mainline- Vaigai river crossing  downstream HOV's CH-505.870km fencing gate is opened. Kindly contact the LSM";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    Serial.println ("Sending Message5");
    //Serial.println ("Set SMS Number");
    SIM900.println("AT+CMGS=\"" + number5 + "\"\r"); //Mobile phone number to send message
    delay(1000);
    SMS = "Warning !!!!!! CTMPL mainline- Vaigai river crossing  downstream HOV's CH-505.870km fencing gate is opened. Kindly contact the LSM";
    SIM900.println(SMS);
    delay(100);
    SIM900.println((char)26);// ASCII code of CTRL+Z
    delay(5000);

    _buffer = _readSerial();
    flag = 1;

    digitalWrite(led, LOW);
  }
  if ( (digitalRead(lm) == HIGH) && (flag == 1) )
  {
    flag = 0;
    delay(20);
    Serial.println("Limit Switch Deactivated");
  }
}
void read_voltage() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(sensor);
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
  Serial.println(average);
  vin = (average * 0.00322581)-0.12;
  Serial.println("----------------------" + String(vin));
}
String _readSerial() {
  _timeout = 0;
  while (!SIM900.available() && _timeout < 10 )
  {
    delay(13);
    _timeout++;
  }
  if (SIM900.available()) {
    return SIM900.readString();
    
  }
   return "";  
}
