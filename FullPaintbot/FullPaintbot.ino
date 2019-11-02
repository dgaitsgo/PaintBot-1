#define SRPAY_MAX_VOLTAGE 255

const int VRx = A0; // Joystick x axis
const int VRy = A1; // Joystick y axis
const int SW = 7; //
//bool swState = false;
int readX = 500;
int readY = 500;

const int encoderRightA = 2; // Green - pin 4 - Digital
const int encoderRightB = 4; // White - pin 5 - Digital
const int encoderLeftA = 3; // Green - pin 2 - Digital
const int encoderLeftB = 5; // White - pin 3 - Digital
const int RPWMOutputRight = 10; // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
const int LPWMOutputRight = 11; // Arduino PWM output pin 10; connect to IBT-2 pin 2 (LPWM)
const int RPWMOutputLeft = 6; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
const int LPWMOutputLeft = 9; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)
const int ZMOTOR_A_Output = 12; // Arduino PWM output pin 7; connect to IBT-2 pin 1 (RPWM)
const int ZMOTOR_B_Output = 13; // Arduino PWM output pin 8; connect to IBT-2 pin 2 (LPWM)

int spraySwitchDistance = 600;

long encoderLeft = 0;
long encoderRight = 0;
bool done = false;
long encL = 8000L * 6;
long encR = 6000L * 8;
long encLprev = 0L;
long encRprev = 0L;


///////////////////////////////////////////////////////////////// SPRAY ///////////////////////////////////////////////////////
void spray() {

//    EEPROM.write(sprayStatusCacheAddr, 1);  
    analogWrite(ZMOTOR_A_Output, 0);
    analogWrite(ZMOTOR_B_Output, SRPAY_MAX_VOLTAGE);
    
    delay(spraySwitchDistance);
    
    analogWrite(ZMOTOR_A_Output, 0);
    analogWrite(ZMOTOR_B_Output, 0);
}

int stopSpraying() {

//    EEPROM.write(sprayStatusCacheAddr, 0);  
    analogWrite(ZMOTOR_A_Output, SRPAY_MAX_VOLTAGE);
    analogWrite(ZMOTOR_B_Output, 0);

    delay(spraySwitchDistance * 0.8);

    analogWrite(ZMOTOR_A_Output, 0);
    analogWrite(ZMOTOR_B_Output, 0);

    return (1);
}

///////////////////////////////////////////////////////////////// MOVEMENTS ///////////////////////////////////////////////////////

void goUp(int vol)
{
  if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, vol);
    
    analogWrite(RPWMOutputRight, vol);
    analogWrite(LPWMOutputRight, 0);
}

void goUp_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, volL);
    
    analogWrite(RPWMOutputRight, volR);
    analogWrite(LPWMOutputRight, 0);
}

void goDown(int vol)
{
  if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, vol);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, vol);
}

void goDown_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, volL);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, volR);
}

void goRight(int vol)
{
  if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, vol);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, vol);
    analogWrite(LPWMOutputRight, 0);
}

void goRight_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, volL);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, volR);
    analogWrite(LPWMOutputRight, 0);
}

void goLeft(int vol)
{
  if (vol >= 255)
    vol = 255;    
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, vol);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, vol);
}

void goLeft_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, volL);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, volR);
}

void goUpRight(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputRight, vol);
    analogWrite(LPWMOutputRight, 0);
}

void goDownLeft(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, vol);
}

void goUpLeft(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, vol);
}

void goDownRight(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, vol);
    analogWrite(LPWMOutputLeft, 0);
}

void doStop()
{
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, 0);
}

///////////////////////////////////////////////////////////////// SQUARE ///////////////////////////////////////////////////////

void square() {

  
  goLeft_v2(230, 200);   // first 
  delay(5750);
  goDown_v2(160, 150);
  delay(1000);
  goRight_v2(180, 240);    // first
  delay(5500);

  goDown_v2(160, 150);
  delay(1000);
  goLeft_v2(195, 200);   // second 
  delay(5750);
  goDown_v2(160, 150);
  delay(1000);
  goRight_v2(180, 240);    // second
  delay(5000);

  goDown_v2(160, 150);
  delay(1000);
  goLeft_v2(195, 200);   // third 
  delay(5750);
  goDown_v2(160, 150);
  delay(1000);
  goRight_v2(180, 225);    // third
  delay(5000);

  doStop();
}

void square_v2()
{
    Serial.print("Encoder Left = ");
    Serial.println(encoderLeft);
    Serial.print("Encoder Right = ");
    Serial.println(encoderRight);
    Serial.println("start left");

    spray();
    while (1)
    {
      goLeft_v2(195, 125);   //155, 100
      if ((encoderLeft > (encLprev + encL * 2.5)) && (encoderRight > (encRprev + encR * 2.5)))
      {
        doStop();
        encoderLeft = 0;
        encoderRight = 0;
        encLprev = encoderLeft;
        encRprev = encoderRight;
        break ;
      }
    } 
    while (1) {
      if (stopSpraying()) {
        break ;
      }
    }
    Serial.print("Encoder Left = ");
    Serial.println(encoderLeft);
    Serial.print("Encoder Right = ");
    Serial.println(encoderRight);
    Serial.println("start down");
    while (1)
    {
      goDown_v2(90, 140);
      if ((encoderLeft < (encLprev - encL * 0.5)) && (encoderRight > (encLprev + encR * 0.5)))
      {
        doStop();
        encoderLeft = 0;
        encoderRight = 0;
        encLprev = encoderLeft;
        encRprev = encoderRight;
        break ;
      }
    }
    Serial.print("Encoder Left = ");
    Serial.println(encoderLeft);
    Serial.print("Encoder Right = ");
    Serial.println(encoderRight);
    Serial.println("start right");
    spray();
    while (1)
    {
      goRight_v2(120, 150); //100 : 150
      if ((encoderLeft < (encLprev - encL * 2.1)) && (encoderRight < (encRprev - encR * 2.1)))
      {
        doStop();
        encoderLeft = 0;
        encoderRight = 0;
        encLprev = encoderLeft;
        encRprev = encoderRight;
        break ;
      }
    }
     
    while (1) {
      if (stopSpraying()) {
        break ;
      }
    }
    Serial.print("Encoder Left = ");
    Serial.println(encoderLeft);
    Serial.print("Encoder Right = ");
    Serial.println(encoderRight);
    Serial.println("start down");
    while (1)
    {
      goDown_v2(100, 140);
      if ((encoderLeft < (encLprev - encL * 0.5)) && (encoderRight > (encLprev + encR * 0.5)))
      {
        doStop();
        encoderLeft = 0;
        encoderRight = 0;
        encLprev = encoderLeft;
        encRprev = encoderRight;
        break ;
      }
    }
    Serial.print("Encoder Left = ");
    Serial.println(encoderLeft);
    Serial.print("Encoder Right = ");
    Serial.println(encoderRight);
    Serial.println("start left");
    spray();
    while (1)
    {
      goLeft_v2(125, 165); // 15 left : 19 right
      if ((encoderLeft > (encLprev + encL * 1.9)) && (encoderRight > (encRprev + encR * 1.9)))
      {
        doStop();
        encoderLeft = 0;
        encoderRight = 0;
        encLprev = encoderLeft;
        encRprev = encoderRight;
        break ; 
      }
    }
    while (1) {
      if (stopSpraying()) {
        break ;
      }
    }
    Serial.print("Encoder Left = ");
    Serial.println(encoderLeft);
    Serial.print("Encoder Right = ");
    Serial.println(encoderRight);
    Serial.println("end");
}

bool joystick(const int VRx, const int VRy, int encoderLeft, int encoderRight)
{
    readX = analogRead(VRx);
    readY = analogRead(VRy);
//    Serial.print("X-axis: ");
//    Serial.println(readX);
//    Serial.print("Y-axis: ");
//    Serial.println(readY);
//    Serial.print(encoderLeft);
//    Serial.print(" - ");
//    Serial.println(encoderRight);
//    Serial.print("\n\n");

    while (readX < 300 && readY > 600)
    {
      goDownRight(140);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY > 600 && readX < 300)
    {
      goUpRight(140);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY < 300 && readX < 300)
    {
      goDownRight(140);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY > 600 && readX > 600)
    {
      goUpLeft(140);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readX < 300)
    {
      goRight_v2(140, 200);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readX > 700)
    {
      goLeft_v2(150, 165);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY < 300)
    {
      goDown_v2(145, 200);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY > 700)
    {
      goUp_v2(145, 200);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
}

//void callibrate(     callibrate(100, "FORWARD");

///////////////////////////////////////////////////////////////// SETUP ///////////////////////////////////////////////////////
void setup() {
  
  Serial.begin(9600);

  //MOVEMENT MOTORS//
  pinMode(encoderLeftA, INPUT_PULLUP);
  pinMode(encoderLeftB, INPUT_PULLUP);
  pinMode(encoderRightA, INPUT_PULLUP);
  pinMode(encoderRightB, INPUT_PULLUP);
  pinMode(RPWMOutputLeft, OUTPUT);
  pinMode(LPWMOutputLeft, OUTPUT);
  pinMode(RPWMOutputRight, OUTPUT);
  pinMode(LPWMOutputRight, OUTPUT);

  //JOYSTICK//
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);

  //MOVEMENT ENCODERS//
  attachInterrupt(digitalPinToInterrupt(encoderLeftA), encoderLeftPinChangeA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderLeftB), encoderLeftPinChangeB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderRightA), encoderRightPinChangeA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderRightB), encoderRightPinChangeB, CHANGE);

  //SPRAY//
//  pinMode(encoderZA, INPUT_PULLUP);
//  pinMode(encoderZB, INPUT_PULLUP);
  //Check if Spray nozzle is engaged and set it off
//  spraying = EEPROM.read(sprayStatusCacheAddr);
//  if (spraying) {
//    stopSpraying();
//  }
}

void loop() {
  int turn = digitalRead(SW);
  if (turn)
    joystick(VRx, VRy, encoderLeft, encoderRight);
  else
  {
    while (!done)
    {
      encoderLeft = 0;
      encoderRight = 0;
      delay(100);
      encoderLeft = 0;
      encoderRight = 0;
//      square_v2();
      spray();
      delay(400);
      stopSpraying();
      break ;
    }
  }
}

// Reading the encoder inputs
//  Left encoder
void encoderLeftPinChangeA() {
  encoderLeft += digitalRead(encoderLeftA) == digitalRead(encoderLeftB) ? -1 : 1;
}

void encoderLeftPinChangeB() {
  encoderLeft += digitalRead(encoderLeftA) != digitalRead(encoderLeftB) ? -1 : 1;
}

//  Right encoder
void encoderRightPinChangeA() {
  encoderRight += digitalRead(encoderRightA) == digitalRead(encoderRightB) ? -1 : 1;
}

void encoderRightPinChangeB() {
  encoderRight += digitalRead(encoderRightA) != digitalRead(encoderRightB) ? -1 : 1;
}
