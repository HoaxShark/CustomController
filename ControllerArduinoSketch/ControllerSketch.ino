
int redSensorPin = 0; 
int greenSensorPin = 1;     // the cell and 10K pulldown are connected to a0
int blueSensorPin = 2;
int yellowSensorPin = 3;

int redReading;
int greenReading;     // analog reading from the sensor for green
int blueReading;
int yellowReading;

int redLED = 10;            // Red LED to pin 10
int greenLED = 11;          // Green LED to pin 11
int blueLED = 12;           // Blue LED to pin 12
int yellowLED = 13;         // Yellow LED to pin 13

byte incomingByte;      // a variable to read incoming serial data into

void setup(void) {
  // debugging information via the Serial monitor
  Serial.begin(115200);   
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
}
 
void loop(void) {
  redReading = analogRead(redSensorPin);  
  greenReading = analogRead(greenSensorPin); 
  blueReading = analogRead(blueSensorPin); 
  yellowReading = analogRead(yellowSensorPin); 
 
  //Serial.print("Red = ");
  //Serial.print(redReading);     // the raw analog reading
  //Serial.print("- Green = ");
  //Serial.print(greenReading);     // the raw analog reading
  //Serial.print("- Blue = ");
  //Serial.print(blueReading);     // the raw analog reading
  //Serial.print("- Yellow = ");
  //Serial.println(yellowReading);     // the raw analog reading
 
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  digitalWrite(yellowLED, HIGH);

   // see if there's incoming serial data:
 if (Serial.available() > 0) {
   // read the oldest byte in the serial buffer:
   incomingByte = Serial.read();
   // if it's a capital H:
   if (incomingByte == 'H') {
     padPrint(redReading,4);
     padPrint(greenReading,4);
     padPrint(blueReading,4);
     padPrint(yellowReading,4);
     Serial.println();
   } 
 }
}

// padPrint pattern found on arduino forums "http://forum.arduino.cc/index.php?topic=42155.0"
void padPrint( int value, int width)
{
// pads values with leading zeros to make the given width
char valueStr[6]; // large enough to hold an int
  itoa (value, valueStr, 10);
  int len = strlen(valueStr);
  if(len < width){
    len = width-len;
    while(len--){
     Serial.print('0');
  }
 Serial.print(valueStr);   
}
}
