#include <SoftwareSerial.h>

// Define Bluetooth module pins
const int bluetoothTx = 0; // Bluetooth TX to Arduino RX (pin 2)
const int bluetoothRx = 1; // Bluetooth RX to Arduino TX (pin 3)

// Create a SoftwareSerial object for Bluetooth communication
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

// Motor control pins
const int motor1Pin1 = 5; // Motor 1 control pin 1
const int motor1Pin2 = 6; // Motor 1 control pin 2
const int motor2Pin1 = 9; // Motor 2 control pin 1
const int motor2Pin2 = 10; // Motor 2 control pin 2

void setup() {
  // Set motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Start serial communication with Bluetooth module
  Serial.begin(9600);
  bluetooth.begin(9600); // baud rate for Bluetooth communication
}

void loop() {
  // Check if data is available to read from Bluetooth module
  if (bluetooth.available()) {
    char command = bluetooth.read(); // Read the incoming command

    // Process the received command
    switch (command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopMotors();
        break;
      default:
        break;
    }
  }
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
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
