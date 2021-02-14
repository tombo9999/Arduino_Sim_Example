//*****************************************************************************************************************************************************************************************
//***************************************************************************  Arduino Simulator Drag & Draw  *****************************************************************************
//*******************************************************************  Copyright by Marc Van Den Berge and Louis D'Hont  ******************************************************************
//*****************************************************************************************************************************************************************************************

#include <SimulatorProgram.h>
#include <LiquidCrystalSim.h>

// #include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float cm;
float inches;

int sensorPin = A0;
int OUTPUT_PIN = 8;
int readValue;
int potValue;

float frequency;        // Frequency in Herz

void setup()
{
	Serial.begin(9600);
  inString.reserve(25);
  RealIO_Connect();
	lcd.begin(16, 2);  
	pinMode(OUTPUT_PIN, OUTPUT);
	pinMode(sensorPin, INPUT);	

	frequency = 40;
}

void loop() {

	readValue = analogRead(sensorPin);
	potValue = map(readValue, 0, 1023, 117, 23229);

	// Calculate the period and the amount of time the output is on for (HIGH) and 
	// off for (LOW).
	double period = 1000000 / frequency;
	double onFor = potValue;
	double offFor = 25000 - potValue;

	if( period > 16383 ) {
		// If the period is greater than 16383 then use the millisecond timer delay,
		// otherwise use the microsecond timer delay. Currently, the largest value that
		// will produce an accurate delay for the microsecond timer is 16383.

		digitalWrite(OUTPUT_PIN, HIGH);
		delay((long)onFor/1000);

		digitalWrite(OUTPUT_PIN, LOW);
		delay((long)offFor/1000);
	} else {
		digitalWrite(OUTPUT_PIN, HIGH);
		delayMicroseconds((long)onFor);

		digitalWrite(OUTPUT_PIN, LOW);
		delayMicroseconds((long)offFor);
	}
	cm = 0.01722 * onFor;
	inches = (cm / 2.54);
  Serial.print(inches, 1);
  Serial.print("\t");
  Serial.println(cm, 1);
  lcd.setCursor(0,0);
  lcd.print("Inches       ");
  lcd.print("cm");
  lcd.setCursor(1,1);
  String stringInch = String(inches);
  lcd.print(stringInch.substring(0, (stringInch.length() - 1)));
  lcd.print("  -  ");
  String stringCm = String(cm);
  lcd.print(stringCm.substring(0, (stringCm.length() - 1)));
  delay(3000);
}
