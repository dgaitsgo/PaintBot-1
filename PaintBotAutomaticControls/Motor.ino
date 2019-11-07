#include "Motor.h"

void Motor::setup(const int pin_1, const int pin_2) {

  float zero = 0.0;
  float one = 0.5;

  _pin_1 = pin_1;
  _pin_2 = pin_2;

  _PIDController.setup(&_currentSpeed, &_pidOutput, &_targetSpeed, _Kp, _Ki, _Kd, &one, DIRECT);
        
  initializePID();
}

void  Motor::setSpeed(const float speed) {
  //PID will read from this speed
  _targetSpeed = speed;

}

float Motor::computeSpeed(Encoder encoder) {
    /*
    
    Returns the motors speed in RPM since the last time this function was called
    should only be called by the PID process otherwise we are calculating the
    distance moved over a varying amount of time.
    */
    
    float currentPosition = encoder.read();
    float currentMicros = micros();
    
    float distMoved   =  currentPosition - _lastPosition;
    if (distMoved > 3 || distMoved < -3) {
        // This dampens some of the effects of quantization without having 
        // a big effect on other changes
        float saveDistMoved = distMoved;
        if (distMoved - _lastDistMoved <= -1)
          distMoved += .5;
        else if (distMoved - _lastDistMoved >= 1)
          distMoved -= .5;
        _lastDistMoved = saveDistMoved;
        
        unsigned long timeElapsed =  currentMicros - _lastTimeStamp;
        //Compute the speed in RPM
        _RPM = (_encoderStepsToRPMScaleFactor*distMoved) / float(timeElapsed);
    
    } else {
        float elapsedTime = encoder.elapsedTime();
        float lastTime = micros() - encoder.lastStepTime();  // no direction associated with this
        if (lastTime > abs(elapsedTime)) {
            // This allows the RPM to approach 0
            if (elapsedTime < 0){
                elapsedTime = -lastTime;
            } else {
                elapsedTime = lastTime;
            }
        };

        _RPM = 0 ;
        if (elapsedTime != 0){
          _RPM = _encoderStepsToRPMScaleFactor / elapsedTime;
        }
    }
    _RPM = _RPM * -1.0;
    
    //Store values for next time
    _lastTimeStamp = currentMicros;
    _lastPosition  = currentPosition;
    
    return _RPM;
}

void Motor::write(float speed) {

  speed = constrain(speed, -255, 254);
  _lastSpeed = speed;
  bool forward = speed > 0;
  speed = fabs(speed);

  if (speed == 0) {
    analogWrite(_pin_1, 0);
    analogWrite(_pin_2, 0);
  } else if (forward) {    
    analogWrite(_pin_1, speed);
    analogWrite(_pin_2, 0);
  } else {
    analogWrite(_pin_1, 0);
    analogWrite(_pin_2, speed);
  }
  
}

void  Motor::initializePID() {
  //setup positive PID controller
  _PIDController.SetMode(AUTOMATIC);
  _PIDController.SetOutputLimits(-255, 255);
  _PIDController.SetSampleTime(LOOP_INTERVAL / 1000);
}

void Motor::computePID(Encoder encoder) {
  /*Recompute the speed control PID loop and command the motor to move.*/
  _currentSpeed = computeSpeed(encoder);
  _PIDController.Compute();
  additiveWrite(_pidOutput);
}

void  Motor::setPIDTuningValues(float* KpV, float* KiV, float* KdV, float* propWeightV) {
  _Kp = KpV;
  _Ki = KiV;
  _Kd = KdV;

  _PIDController.SetTunings(_Kp, _Ki, _Kd, propWeightV);
}

void Motor::additiveWrite(int speed) {
  /*
    Increases/decreases the motor speed by the passed speed amount
  */
  write(_lastSpeed + speed);
}

void Motor::stop() const {

  setSpeed(0);
  analogWrite(_pin_1, 0);
  analogWrite(_pin_2, 0);
}

float Motor::cachedSpeed() {
  /*
    Returns the last result of computeSpeed
  */

  return _RPM;
}

double  Motor::getCurrentSpeed() const {
  return (_currentSpeed);
}

void    Motor::debug() const {
  Serial.print("output pid output ");
  Serial.println(_pidOutput);
  Serial.print("output target speed ");
  Serial.println(_targetSpeed);
  Serial.print("output current speed ");
  Serial.println(_currentSpeed);
  Serial.print("output last position ");
  Serial.println(_lastPosition);
  Serial.print("output timestamp ");
  Serial.println(_lastTimeStamp);
  Serial.print("output last dist ");
  Serial.println(_lastDistMoved);
  Serial.print("output rpm ");
  Serial.println(_RPM);
  Serial.print("output kp ");
  Serial.println(*_Kp);
  Serial.print("output ki ");
  Serial.println(*_Ki);
  Serial.print("output kd ");
  Serial.println(*_Kd);
  Serial.print("output last speed ");
  Serial.println(_lastSpeed);
  Serial.print("Pid State");
  Serial.println(_PIDController.pidState());
}
