void debugEncoders() {
      Serial.print("Encoder right :");
      Serial.println(rightEncoder.read());
      Serial.print("Encoder left  :");
      Serial.println(leftEncoder.read());
}

void debugJoystick() {
      Serial.print("Joystick X :");
      Serial.println(analogRead(VRx));
      Serial.print("Joystick Y  :");
      Serial.println(analogRead(VRy));
      Serial.println("_____________________________________");
}

void debugSpeed() {
  Serial.print(leftMotor.computeSpeed(leftEncoder));
  Serial.print(",");
  Serial.println(rightMotor.computeSpeed(rightEncoder));
}
