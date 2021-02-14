#include <Native_LiquidCrystal.h>

Native_LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

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
	lcd.begin(16, 2);         //16 , 2 corrisponde al numero di colonne e righe del display
	// lcd.setCursor(4,0);
	lcd.print("--> Distance <--");   //scrivo sul display i caratteri " metro digitale "
	delay(3000);
	lcd.clear();              //dopo 1500ms la scritta si cancella
}

void loop()
{
	cm = 0.01722 * readUltrasonicDistance(2, 3);
	inches = (cm / 2.54);
	Serial.print(inches, 1);
	Serial.print("\t");
	Serial.println(cm, 1);
	//lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Inches");
	lcd.setCursor(4,0);
	lcd.setCursor(12,0);
	lcd.print("cm");
	lcd.setCursor(1,1);                            //setto il cursore alla colonna 8 riga 0
	lcd.print(inches, 1);
	lcd.setCursor(11,1);                            //setto il cursore alla colonna 8 riga 0
	lcd.print(cm, 1);                           //scrivo il valore della  variabile distanza
	lcd.setCursor(14,1);                           //setto il cursore alla colonna 12 riga 0
	delay(3000);
	lcd.clear();//elimino ogni scritta sul display fino ad una nuova misurazione 
}
