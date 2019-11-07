#ifndef __PID_Constants_h
# define __PID_Constants_h

class PID_Constants {
  public:
    PID_Constants(float kp, float ki, float kd, float weight) {
      _kp = kp;
      _ki = ki;
      _kd = kd;
      _weight = weight;
    }
    float _kp;
    float _ki;
    float _kd;
    float _weight;
};


#endif
