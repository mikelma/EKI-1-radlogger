#include <SD.h>

#include <DS3231.h>
#include <Wire.h>

/* Connect the SD card reader like follows:
  MOSI - pin 11
  MISO - pin 12
  PIN_CLOCK - pin 13
  CS - pin 10
*/

#define PIN_SDCS 10 // SD Chip Select

DS3231 Clock;
File loggerFile;

const int interruptPin = 2;
const int cycle = 10000;
int count = 0;
bool century = false;
bool h12;
bool PM;
String fileName = "";

void setup() {
  // Define pins
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), notify, FALLING);

  // Start the I2C interface
  Wire.begin();

  // Complete file name
  fileName += Clock.getDate();
  fileName += Clock.getHour(h12, PM);
  fileName += Clock.getMinute();
  fileName += Clock.getSecond();
  fileName += ".txt";

  // Init serial
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Serial initialized.");

  // Init SD Card
  Serial.println("Initializing SD card...");
  if (!SD.begin(PIN_SDCS)) {
    Serial.println(" Initialization failed!");
    return;
  }
  Serial.println("SD Card initialized.");
}

void loop() {
  if (millis() % cycle == 0) {
    // Generate data string
    String data_str = "date: ";
    data_str += getDateStr();
    data_str += " counter: ";
    data_str += count;

    File file = SD.open(fileName, FILE_WRITE);
    file.println(data_str);
    file.close();

    Serial.println("Cycle end! " + data_str);
    count = 0;
  }
}

void notify() {
  // Serial.print("Detected! counter:");
  count ++;
  // Serial.println(count);
}

String getDateStr() {
  String data_str = "";
  data_str += Clock.getYear();
  data_str += "/";
  data_str += Clock.getMonth(century);
  data_str += "/";
  data_str += Clock.getDate();
  data_str += " ";
  data_str += Clock.getHour(h12, PM);
  data_str += ":";
  data_str += Clock.getMinute();
  data_str += ":";
  data_str += Clock.getSecond();
  return (data_str);

}
