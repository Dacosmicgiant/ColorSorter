//use servo library
#include <Servo.h>

// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

//initialize variable to manipulate bottom servo
int pos=0;
int i;

//initialze servo variables
Servo topServo;
Servo bottomServo;
Servo gateServo;

int color=0;

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 67; // Red minimum value
int redMax = 250; // Red maximum value
int greenMin = 90; // Green minimum value
int greenMax = 287; // Green maximum value
int blueMin = 76; // Blue minimum value
int blueMax = 245; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int R;
int G;
int B;

void setup() {
	// Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

	// Set Frequency scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

   // Set servo locations
  topServo.attach(9);
  bottomServo.attach(10);
  gateServo.attach(11);


	// Setup Serial Monitor
	Serial.begin(9600);
}

void loop()
{
    //direct top servo to receive ball
    for(int i=80;i<142;i++)
  { 
    topServo.write(i);
    delay(10);
  }

  bottomServo.write(0);
  delay(100);

    for(int i=0;i<90;i++)
  { 
    gateServo.write(i);
    delay(10);
  }
  delay(100);

  //direct top servo towards sensor
  for(int i = 142; i > 80; i--) 
  {
    topServo.write(i);
    delay(10);
  }
  delay(500);

  label:color = Data();
  delay(500);

  switch (color) 
  {
    case 1:
    Orange();
    break;

    case 2:
    Green();
    break;

    case 3:
    Pink();
    break;
    
    case 0:
    goto label;
    
  }
  delay(300);
  
  //direct ball towards hole
  for(int i = 80; i > 29; i--) 
  {
    topServo.write(i);
    delay(10);
  } 
  delay(1000);

  Back0(pos);
  
  //close gate for swindle

  for(int i=90;i>0;i--)
  {
    gateServo.write(i);
    delay(10);
  }
  delay(10000);
  
  //wait till ball reaches top

  //direct top servo back to pipe
  for(int i = 29; i < 142; i++) 
  {
    topServo.write(i);
    delay(10);
  }
  color=0;
}

int Data()
{
	// Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	 R= map(redPW, redMin,redMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	G = map(greenPW, greenMin,greenMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Blue value
	bluePW = getBluePW();
	// Map to value from 0-255
	B = map(bluePW, blueMin,blueMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Print output to Serial Monitor
	Serial.print("Red = ");
	Serial.print(R);
	Serial.print(" - Green = ");
	Serial.print(G);
	Serial.print(" - Blue = ");
	Serial.println(B);

  if(R>190 & G>50 & G<80 & B>40 & B<80){

    color = 1; // Red

    Serial.print("Detected Color is = ");

    Serial.println("ORANGE");

  }

  else if (R>160 & R<=190 & G>=210 & B>105 & B<=140){

    color = 2; // Blue

     Serial.print("Detected Color is = ");

    Serial.println("GREEN");

  }

  else if(R>140 & R<180 & G>=30 & G<=570 & B>90 & B<125){

    color = 3; // Green

      Serial.print("Detected Color is = ");

    Serial.println("PINK");

  }

  else{
    color=0;
  }


  return color;  

}


// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

void Orange()
{
  for (pos = 0; pos <=6; pos+=1)
  {
    bottomServo.write(pos);
    delay(10);
  }
  delay(500);
}


void Green()
{
  for (pos = 0; pos <=55; pos+=1)
  {
    bottomServo.write(pos);
    delay(10);
  }
  delay(500);
}


void Pink()
{
  for (pos = 0; pos <=102; pos+=1)
  {
    bottomServo.write(pos);
    delay(10);
  }
  delay(500);
}

void Back0(int)
{
  for(pos=pos;pos>=0;pos--)
  {
    bottomServo.write(pos);
    delay(10);
  }
}