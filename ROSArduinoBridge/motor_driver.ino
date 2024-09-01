/***************************************************************
   Motor driver code
***************************************************************/

#ifdef USE_BASE

#ifdef A100_MOTOR_DRIVER

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float voltage = 0.0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 10000.0;
float R2 = 10000.0; 
 
// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;

void initMotorController() {
  // Initialize the motor pins as outputs
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);

  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);

  // Optionally, you can set the motors to be initially stopped
  analogWrite(RIGHT_PWM, 0);
  analogWrite(LEFT_PWM, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
}

void setMotorSpeed(int i, int spd) {
  unsigned char reverse = 0;

  // Check if the speed is negative, which means reverse direction
  if (spd < 0) {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255) { // Limit speed to 255
    spd = 255;
  }

  // Set motor speed and direction based on the motor index (i)
  if (i == LEFT) {
    if (reverse == 0) {
      digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    } else {
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
    }
    // IF higher freq pwmWrite() is needed
    analogWrite(LEFT_PWM, spd);
  }
  else if (i == RIGHT) {
    if (reverse == 0) {
      digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    } else {
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
    }
    // IF higher freq pwmWrite() is needed
    analogWrite(RIGHT_PWM, spd);
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  targetLeftSpeed = constrain(leftSpeed, -255, 255);
  targetRightSpeed = constrain(rightSpeed, -255, 255);
  rampStartTime = millis();
  isRamping = true;
}


float readVoltage() {
  // Read the Analog Input
  adc_value = analogRead(VOLTAGE_PIN);
  
  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
  
  // Calculate voltage at divider input
  voltage = adc_voltage*(R1+R2)/R2;

  return voltage;
}

float readCurrent() {
  const int numReadings = 10;
  long sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(CURRENT_PIN);
    delay(100); // Short delay between readings
  }
  float average = sum / numReadings;
  return ((average * 5.0) / 1023.0);
}

void monitorMotorParameters() {
  float current = readCurrent();
  float voltage = readVoltage();

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.print(" A, Voltage: ");
  Serial.print(voltage, 2);
  Serial.println(" V");
  delay(500);
}

#endif // End of 100A_MOTOR_DRIVER check

#else
#error A motor driver must be selected!

#endif // End of USE_BASE check
