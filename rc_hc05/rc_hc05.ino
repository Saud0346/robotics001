// Motor control pins
const int motor1Pin1 = 5; // Motor 1 control pin 1
const int motor1Pin2 = 6; // Motor 1 control pin 2
const int motor2Pin1 = 9; // Motor 2 control pin 1
const int motor2Pin2 = 10; // Motor 2 control pin 2


int car_speed=0;

void setup() {
  // Set motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Start serial communication with Bluetooth module
  Serial.begin(9600);

}

void loop() {
  // Check if data is available to read from Bluetooth module
  if (Serial.available()>0) {
    char command = Serial.read(); // Read the incoming command
    speed_controle(command);
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
      case 'G':
        moveForward_L();
        break;
      case 'I':
        moveForward_R();
        break;
      case 'H':
        moveBackward_R();
        break;
      case 'J':
        moveBackward_L();
        break;
      default:
        break;
    }
  }
}
void speed_controle(char &command)
{
  switch(command)
  {
    case '0':
    car_speed = 0;
    break;
    case '1':
    car_speed = 25;
    break;
    case '2':
    car_speed = 50;
    break;
    case '3':
    car_speed = 75;
    break;
    case '4':
    car_speed = 100;
    break;
    case '5':
    car_speed = 125;
    break;
    case '6':
    car_speed = 150;
    break;
    case '7':
    car_speed = 175;
    break;
    case '8':
    car_speed = 200;
    break;
    case '9':
    car_speed = 255;
    break;
  }

}
void moveForward() {
  analogWrite(motor1Pin1, car_speed);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}

void moveBackward() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}

void  turnRight(){
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, car_speed);
}

void moveForward(){
  analogWrite(motor1Pin1, car_speed);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}

void moveBackward_L() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, car_speed/4);
  analogWrite(motor2Pin2, LOW);
}

void moveBackward_R() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed/4);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}


void moveForward_R(){
  analogWrite(motor1Pin1, car_speed/4);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}

void moveForward_L(){
  analogWrite(motor1Pin1, car_speed);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, car_speed/4);
  analogWrite(motor2Pin2, LOW);
}

void stopMotors() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, LOW);
}
