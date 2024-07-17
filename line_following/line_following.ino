// Motor control pins
const int motor1Pin1 = 5;  // Motor 1 control pin 1
const int motor1Pin2 = 6;  // Motor 1 control pin 2
const int motor2Pin1 = 9;  // Motor 2 control pin 1
const int motor2Pin2 = 10; // Motor 2 control pin 2

// IR sensor pins
const int leftIRPin = 2;
const int centerIRPin = 3;
const int rightIRPin = 4;

// Threshold for IR sensor
const int car_speed = 150;

void setup() {
  // Set motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Set IR sensor pins as inputs
  pinMode(leftIRPin, INPUT);
  pinMode(centerIRPin, INPUT);
  pinMode(rightIRPin, INPUT);

  Serial.begin(9600); // Start serial communication for debugging
}

void loop() {
  // Read IR sensor values
  int leftValue   =   digitalRead(leftIRPin);
  int centerValue =   digitalRead(centerIRPin);
  int rightValue  =   digitalRead(rightIRPin);

  // Print sensor values for debugging
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" Center: ");
  Serial.print(centerValue);
  Serial.print(" Right: ");
  Serial.println(rightValue);

  // Line following logic
  if (leftValue ==0 &&centerValue ==1 && rightValue==0) {
    // Move forward
    moveForward();
  } else if (leftValue ==1 && centerValue ==1&& rightValue==0) {
    // Turn left
    turnLeft();
  } else if (rightValue ==1&&centerValue ==1 && leftValue==0) {
    // Turn right
    turnRight();
  } else {
    // Stop
    stopMotors();
  }

  delay(10); // Short delay to stabilize readings
}

void moveForward() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, car_speed);

}

void turnLeft() {

  analogWrite(motor1Pin1, car_speed);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, car_speed);
}

void turnRight() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
