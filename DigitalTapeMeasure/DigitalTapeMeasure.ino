#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

float cm;
float inches;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
	pinMode(triggerPin, OUTPUT);  // Clear the trigger
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	// Sets the trigger pin to HIGH state for 10 microseconds
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
	// Reads the echo pin, and returns the sound wave travel time in microseconds
	return pulseIn(echoPin, HIGH);
}

void setup()
{
	Serial.begin(9600);
	lcd.begin(16, 2);
	lcd.print("--> Distance <--");
	delay(3000);
	lcd.clear();
}

void loop()
{
	cm = 0.01722 * readUltrasonicDistance(2, 3);
	inches = (cm / 2.54);
	Serial.print(inches, 1);
	Serial.print("\t");
	Serial.println(cm, 1);
	lcd.setCursor(0,0);
	lcd.print("Inches");
	lcd.setCursor(4,0);
	lcd.setCursor(12,0);
	lcd.print("cm");
	lcd.setCursor(1,1);
	lcd.print(inches, 1);
	lcd.setCursor(11,1);
	lcd.print(cm, 1);
	lcd.setCursor(14,1);
	delay(3000);
	lcd.clear();
}
