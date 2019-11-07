int readX = 500;
int readY = 500;

int neutral = 500;
int jsDeadZone = 30;

int joystickPower = 200;

void updateJoystick() {
   readX = analogRead(VRx);
   readY = analogRead(VRy);
}

bool joystickIsActive() {
  return (
    readX <= neutral - jsDeadZone ||
    readX >= neutral + jsDeadZone ||
    readY <= neutral - jsDeadZone ||
    readY >= neutral + jsDeadZone
   );
}

bool joystick(const int VRx, const int VRy) {
    updateJoystick();
    while (joystickIsActive()) {        
      if (readX < 300) {  
        moveTo(Right, joystickPower);
      } else if (readX > 700) {
        moveTo(Left, joystickPower);
      } else if (readY < 300) {
        moveTo(Up, joystickPower);
      } else if (readY > 700) {
        moveTo(Down, joystickPower);
      }
      updateJoystick();
    }
    stopMotors();
}
