#include "Encoder.h"
#include "Motor.h"
#include "PID_Constants.h"

#define LEFT_ANCHOR_OFFSET_X -5
#define LEFT_ANCHOR_OFFSET_Y 5
#define RIGHT_ANCHOR_OFFSET_X 5
#define RIGHT_ANCHOR_OFFSET_Y 5
#define ROTATION_DISTANCE 2.65
#define MAX_VOLTAGE 180

enum Directions {
  Left,
  Right,
  Up,
  Down,
  UpLeft,
  DownLeft,
  UpRight,
  DownRight
};

struct vector {
  float x;
  float y;
};

struct vectorNode {
  struct vector point;
  bool spray;
  struct vectorNode *next;
};

struct vectorQueue {
  struct vectorNode *first;
  struct vectorNode *last;
};

// Dimensions of the structure
const float width = 85;
const float height = 67;

/////////////////////////////////////////////////////////////////////////////////////// PINS //////////////////////////////////////////////////////////////////////////////
const int VRx = A1; // Joystick x axis
const int VRy = A0; // Joystick y axis
const int JOYSTICK_SW = 13; // Joystick click

// Logic pins for encoders - Must use interrupt pins
const uint8_t encoderRightA = 20; // Green - Digital
const uint8_t encoderRightB = 21; // White - Digital
const uint8_t encoderLeftA = 18; // Green - Digital
const uint8_t encoderLeftB = 19; // White - Digital
long  encValL = 0;          
long  encValR = 0;

// Logic pins for motors - Must use PWM pins
const int RPWMOutputRight = 10;
const int LPWMOutputRight = 11;
const int RPWMOutputLeft = 8;
const int LPWMOutputLeft = 9;

/////////////////////////////////////////////////////////////////////////////////////// Globals //////////////////////////////////////////////////////////////////////////////
Encoder leftEncoder;
Encoder rightEncoder;

PID_Constants pidc = PID_Constants(
  0.5,  //kp - proportional
  0.2,  //ki - integral
  0.2,  //kd - derivative
  0.1   //weight
);

long encoderCurrentLeft = 0;
long encoderCurrentRight = 0;

Motor leftMotor;
Motor rightMotor;

struct vector origin = (struct vector){ width / 2, height / 2 };
struct vector topRight = (struct vector){ width, height };
struct vector topLeft = (struct vector){ 0, height };
struct vector start;
struct vector goTo;
struct vectorQueue *points = NULL;
bool done = false;

/////////////////////////////////////////////////////////////////////////////////////// Init functions //////////////////////////////////////////////////////////////////////////////////////

void initMotors() {

  pinMode(RPWMOutputLeft, OUTPUT);
  pinMode(LPWMOutputLeft, OUTPUT);
  pinMode(RPWMOutputRight, OUTPUT);
  pinMode(LPWMOutputRight, OUTPUT);

  leftMotor.setup(RPWMOutputLeft, LPWMOutputLeft);
  rightMotor.setup(RPWMOutputRight, LPWMOutputRight);
  
  leftMotor.setPIDTuningValues(&pidc._kp, &pidc._ki, &pidc._kd, &pidc._weight);
  rightMotor.setPIDTuningValues(&pidc._kp, &pidc._ki, &pidc._kd, &pidc._weight);
}

void  initEncoders() {
  leftEncoder.setup(encoderLeftA, encoderLeftB);
  rightEncoder.setup(encoderRightA, encoderRightB);
  leftEncoder.write(0);
  rightEncoder.write(0);
}

void  initJoystick() {
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(JOYSTICK_SW, INPUT);
  digitalWrite(JOYSTICK_SW, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////// Main Arduino functions //////////////////////////////////////////////////////////////////////////////////////
void setup() {

  Serial.begin(9600);

  initMotors();
  initEncoders();
  initJoystick();

  leftMotor.debug();
  rightMotor.debug();

//
//  points = loadPoints();
//  start = origin;
//  goTo = vectorQueueDequeue(points);
 
}

void loop() {

  int turn = digitalRead(JOYSTICK_SW);
  if (turn)
    joystick(VRx, VRy);    
  else {
//    algorithm();
      
  }
  
}
