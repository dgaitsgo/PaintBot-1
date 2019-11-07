void timedMove(int len, int dir, int speed) {
    double current = 0;
    double startTime = millis();
    while (startTime + len > current) {
      debugSpeed();
      moveTo(dir, speed);
      current = millis();
    }
    stopMotors();
}

void moveTo(const int dir, const int speed) {
  int rSign = (dir == Left || dir == Down) ? -1 : (dir == UpLeft || dir == DownRight) ? 0 : 1;
  int lSign = (dir == Left || dir == Up) ? -1 : (dir == UpRight || dir == DownLeft) ? 0 : 1;
  int rSpeed = speed * rSign;
  int lSpeed = speed * lSign;

  leftMotor.write(lSpeed);
  rightMotor.write(rSpeed);
}

void stopMotors() {
  leftMotor.stop();
  rightMotor.stop();
}
