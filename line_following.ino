// Motor control pins
const int motor1Pin1 = 5;  // Motor 1 control pin 1
const int motor1Pin2 = 6;  // Motor 1 control pin 2
const int motor2Pin1 = 9;  // Motor 2 control pin 1
const int motor2Pin2 = 10; // Motor 2 control pin 2

// IR sensor pins
const int leftIRPin = A0;
const int centerIRPin = A1;
const int rightIRPin = A2;

// Threshold for IR sensor
const int threshold = 500;

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
  int leftValue = analogRead(leftIRPin);
  int centerValue = analogRead(centerIRPin);
  int rightValue = analogRead(rightIRPin);

  // Print sensor values for debugging
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" Center: ");
  Serial.print(centerValue);
  Serial.print(" Right: ");
  Serial.println(rightValue);

  // Line following logic
  if (centerValue < threshold) {
    // Move forward
    moveForward();
  } else if (leftValue < threshold) {
    // Turn left
    turnLeft();
  } else if (rightValue < threshold) {
    // Turn right
    turnRight();
  } else {
    // Stop
    stopMotors();
  }

  delay(10); // Short delay to stabilize readings
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
