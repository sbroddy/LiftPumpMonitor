// include the library code:
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
 
 
// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal_I2C lcd(0x27,20,4);

int brightness = 150;                     // you can change the overall brightness by range 0 -> 255
const int pressureInput = A0;             //select the analog input pin for the pressure transducer
const int pressureZero = 85.0;            //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6;            //analog reading of pressure transducer at 30psi
const int pressureAlarm = 10.0;           //pressure to turn on warning LED
const int pressuretransducermaxPSI = 30;  //psi value of transducer being used
const int baudRate = 9600;                //constant integer to set the baud rate for serial monitor
const int sensorreadDelay = 250;          //constant integer to set the sensor read delay in milliseconds
float pressureValue = 0;                  //variable to store the value coming from the pressure transducer
float voltage = 0;                        //variable to store A0 voltage reading

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);           //Set pin 13 mode to LED
  //lcd.begin(16, 2);                       // set up the LCD's number of rows and columns:
  //lcd.print("                ");          // Print a message to the LCD.
  //lcd.setCursor(0,1);
  //lcd.print("Lift Pump PSI");
  lcd.init(); 
  lcd.init();
  lcd.backlight();
  Serial.begin(baudRate);                 //initializes serial communication at set baud rate bits per second
}
 
 
void loop() //loop routine runs over and over again forever
{
  //reads value from input pin and assigns to variable
  pressureValue = analogRead(pressureInput); 
  voltage = pressureValue * (5.0 / 1023.0);

  lcd.setCursor(1,0);
  Serial.print(pressureValue);
  Serial.print("    ");
  Serial.print(voltage);
  Serial.print("V       ");
  //conversion equation to convert analog reading to psi
  pressureValue = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); 
  Serial.print(pressureValue, 1); //prints value from previous line to serial
  Serial.println("psi"); //prints label to serial

  lcd.setCursor(0,0); //sets cursor to column 0, row 0
  //lcd.print("Pressure:"); //prints label
  lcd.print(pressureValue, 2); //prints pressure value to lcd screen
  lcd.setCursor(0,1);
  lcd.print("Lift Pump PSI");
  
  // Turn on LED if pressure value is below alarm threshold
  if (pressureValue < pressureAlarm)
  { 
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  delay(sensorreadDelay); //delay in milliseconds between read values
}
 
 
 
