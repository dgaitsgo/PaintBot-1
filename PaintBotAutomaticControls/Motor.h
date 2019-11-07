#include "PID.h"
#include "Encoder.h"

#define LOOP_INTERVAL 1000
#define RESOLUTION USHRT_MAX

#ifndef Motor_h_
#define Motor_h_

class Motor {

  public:
    Motor() { ; }
    void                setup(int pin_1, int pin_2);
    float               cachedSpeed();
    void                write(const float speed);
    void                computePID(Encoder encoder);
    void                initializePID();
    float               computeSpeed(Encoder encoder);
    void                setSpeed(const float speed);
    void                additiveWrite(int speed);
    void                setPIDTuningValues(float* KpV, float* KiV, float* KdV, float* propWeightV);
    double              getCurrentSpeed() const;
    void                debug() const;
    void                stop() const;

  private:
    PID                 _PIDController;
    double              _pidOutput;
    double              _targetSpeed;
    double              _currentSpeed;
    volatile double     _lastPosition;
    volatile double     _lastTimeStamp;
    float               _lastDistMoved;
    float               _RPM;
    float               *_Kp;
    float               *_Ki;
    float               *_Kd;
    float               _encoderStepsToRPMScaleFactor = 3125; //6*10^7 us per minute divided by encoders 19,200 steps per big sprocket revolution
    int                 _lastSpeed = 0;
    int                 _pin_1;
    int                 _pin_2;
};
#endif
