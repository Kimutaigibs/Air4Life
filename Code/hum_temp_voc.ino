// Monitoring temperature, rel. humidity, and volatile organic compounds (VOC).
// Sensors: DHT22 and SPG40

#include "DHT.h" // load DHT library
#include "SparkFun_SGP40_Arduino_Library.h" // VOC sensor library; Click here to get the library: http://librarymanager/All#SparkFun_SGP40
#include <Wire.h>

#define DHTPIN 7 // connect sensor to GPIO 7    

#define DHTTYPE DHT22    // define that we're using DHT22

DHT dht(DHTPIN, DHTTYPE); // call sensor with "dht"

SGP40 mySensor; //create an object of the SGP40 class

float RH, T; // in VOC sensor library, relative humidity (RH) and temperature (T) are defined; we're over-writing them here

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // start serial connection
  Serial.println(F("Air Monitoring"));

  dht.begin(); // start DHT11 sensor
  Wire.begin();

  //Initialize sensor
  if (mySensor.begin() == false)
  {
    Serial.println(F("SGP40 not detected. Check connections. Freezing..."));
    while (1)
      ; // Do nothing more
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  RH = dht.readHumidity(); // read humidity
  T = dht.readTemperature(); // read temperature

  Serial.print("rel. Humidity: "); //Im seriellen Monitor den Text und 
  Serial.print(RH); //die Dazugehörigen Werte anzeigen
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println("°C");
  Serial.print(F("VOC Index is: "));
  Serial.println(mySensor.getVOCindex()); //Get the VOC Index using the default RH (50%) and T (25C)

  delay(1000); //Wait 1 second - the Sensirion VOC algorithm expects a sample rate of 1Hz
}
