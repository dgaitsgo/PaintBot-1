
void algorithm()
{
    while (!done) {
    rightEncoder.write(0);
    bool rightMotorFinished = false;
    float rightChainCurrentLength = distanceBetweenVectors(topRight, start, RIGHT_ANCHOR_OFFSET_X, RIGHT_ANCHOR_OFFSET_Y);
    float rightChainNewLength = distanceBetweenVectors(topRight, goTo, RIGHT_ANCHOR_OFFSET_X, RIGHT_ANCHOR_OFFSET_Y);
    float rightMotorDistanceToTravel = fabs(rightChainCurrentLength - rightChainNewLength);
    bool rightMotorRotateClockwise = (rightChainNewLength < rightChainCurrentLength);

    leftEncoder.write(0);
    bool leftMotorFinished = false;
    float leftChainCurrentLength = distanceBetweenVectors(topLeft, start, LEFT_ANCHOR_OFFSET_X, LEFT_ANCHOR_OFFSET_Y);
    float leftChainNewLength = distanceBetweenVectors(topLeft, goTo, LEFT_ANCHOR_OFFSET_X, LEFT_ANCHOR_OFFSET_Y);
    float leftMotorDistanceToTravel = fabs(leftChainCurrentLength - leftChainNewLength);
    bool leftMotorRotateClockwise = (leftChainNewLength > leftChainCurrentLength);

    while (!rightMotorFinished || !leftMotorFinished) {
      encoderCurrentLeft = leftEncoder.read();
      encoderCurrentRight = rightEncoder.read();
      float rightMotorDistanceTraveled = distTravel(encoderCurrentRight); // ERROROROORORR
      float leftMotorDistanceTraveled = distTravel(encoderCurrentLeft); // Added divided by 8.0 because 8 rotations of the encoders is one rotation of the chain sprocket
      float *percent = new float[2];
      voltagePercent(percent, leftMotorDistanceToTravel, rightMotorDistanceToTravel, leftMotorDistanceTraveled, rightMotorDistanceTraveled);
      
        int leftMotorVoltage = percent[0] * MAX_VOLTAGE;
        int rightMotorVoltage = percent[1] * MAX_VOLTAGE;

        Serial.print("Right motor distance traveled: ");
        Serial.print(rightMotorDistanceTraveled);
        Serial.print(" Left motor distance traveled: ");
        Serial.println(leftMotorDistanceTraveled);
        Serial.print("Right encoder rotations: ");
        Serial.print(encoderCurrentRight / (2400.0 * 8.0) * ROTATION_DISTANCE);
        Serial.print(" Left encoder rotations: ");
        Serial.println(encoderCurrentLeft / (2400.0 * 8.0) * ROTATION_DISTANCE);

      if (!rightMotorFinished)
      {
        if (rightMotorDistanceTraveled < rightMotorDistanceToTravel)
        {
          if (rightMotorRotateClockwise)
            moveTo(UpRight, rightMotorVoltage);
          else
            moveTo(DownLeft, rightMotorVoltage);
        }
        else
        {
          Serial.println("Right motor finished");
          rightMotorFinished = true;
          rightMotor.stop();
        }
      }
      // Left motor
      if (!leftMotorFinished)
      {
        if (leftMotorDistanceTraveled < leftMotorDistanceToTravel)
        {
          if (leftMotorRotateClockwise)
            moveTo(DownRight, leftMotorVoltage);
          else
            moveTo(UpLeft, leftMotorVoltage);
        }
        else if (leftMotorFinished == false)
        {
          Serial.println("Left motor finished");
          leftMotorFinished = true;
          leftMotor.stop();
        }
      }
      delete[] percent;
    }
    if (isVectorQueueEmpty(points) == true)
      done = true;
    else
    {
      start = goTo;
      goTo = vectorQueueDequeue(points);
    }
  }
}

/*
 *  Calculate the distance travled by encoder info.
 *  Input
 *    encoder value
 *  Output: distance.
*/
float distTravel (long encoder)
{
  float dist = 0;
  dist = (fabs(encoder / (2400.0 * 8.0))) * ROTATION_DISTANCE; // ERROROROORORR
  return (dist);
}

/*
 *  Calculate the voltage percent to control the motor speed.
 *  Input
 *    percent       : Storage for return value
 *    toTravelLeft  : Goal position to travel left side.
 *    toTravelRight : Goal position to travel right side.
 *    distLeft      : Distance traveled on left motor.
 *    distRight     : Distance traveled on right motor.    
*/
void voltagePercent(float *percent,  float toTravelLeft,float toTravelRight, float distLeft, float distRight)
{
  float maxDist = max(toTravelLeft - distLeft, toTravelRight - distRight);
  percent[0] = (toTravelLeft - distLeft) / maxDist;     // voltage percent for Left
  percent[1] = (toTravelRight - distRight) / maxDist;   // voltage percent for Right
  return (percent);
}
