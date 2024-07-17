// Motor speed control for forward-backward and left-right.
int FB_speed = 100, LR_speed = 150;

// Pins to control the direction for motors rotation
int pin1 = 3, pin2 = 5, pin3 = 6, pin4 = 9;

// Ultrasonic sensors pins
int trig1 = 2, echo1 = 4, trig2 = 7, echo2 = 8, trig3 = 10, echo3 = 11;

float duration;
float distance1, distance2, distance3;
const float set_distance1 = 35, set_distance2 = 35, set_distance3 = 35;

void setup() {
    Serial.begin(9600);

    // Set motor control pins as outputs
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    // Set ultrasonic sensor pins
    pinMode(trig1, OUTPUT);
    pinMode(trig2, OUTPUT);
    pinMode(trig3, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(echo2, INPUT);
    pinMode(echo3, INPUT);
}

void loop() {
    self_driving();
}

void self_driving() {
    // Measure distances from ultrasonic sensors
    distance1 = dist_measure(trig1, echo1);
    distance2 = dist_measure(trig2, echo2);
    distance3 = dist_measure(trig3, echo3);

    if (distance2 > set_distance2) {
        // Forward
        move_forward();
    } else if (distance1 > set_distance1 && distance1 > distance3) {
        // Right turn
        turn_right();
    } else if (distance3 > set_distance3) {
        // Left turn
        turn_left();
    } else if (distance1 < set_distance1 && distance2 < set_distance2 && distance3 < set_distance3) {
        // No clear path, move backward until there is space
        move_backward_until_clear();
    }
}

void move_forward() {

         analogWrite(pin1, LOW);
        analogWrite(pin2, FB_speed);
        analogWrite(pin3, LOW);
        analogWrite(pin4, FB_speed);
    
    Serial.println("Forward");
}

void turn_right() {
    analogWrite(pin1, LR_speed);
    analogWrite(pin2, LOW);
    analogWrite(pin3, LOW);
    analogWrite(pin4, LR_speed);
    Serial.println("Right");
}

void turn_left() {
    analogWrite(pin1, LOW);
    analogWrite(pin2, LR_speed);
    analogWrite(pin3, LR_speed);
    analogWrite(pin4, LOW);
    Serial.println("Left");
}

void move_backward_until_clear() {
    while (true) {
        // Measure distances again
        distance1 = dist_measure(trig1, echo1);
        distance3 = dist_measure(trig3, echo3);

        if (distance1 > set_distance1 && distance3 > set_distance3) {
            // Clear path found
            break;
        }

        // Move backward
        analogWrite(pin1, FB_speed);
        analogWrite(pin2, LOW);
        analogWrite(pin3, FB_speed);
        analogWrite(pin4, LOW);
        Serial.println("Reverse");
    }

    // Decide which way to turn
    if (distance1 > set_distance1 && distance1 > distance3) {
        turn_right();
    } else if (distance3 > set_distance3) {
        turn_left();
    }
}

float dist_measure(int trig, int echo) {
    duration = 0;

    // Send a pulse to the trigger pin
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Measure the duration of the pulse on the echo pin
    duration = pulseIn(echo, HIGH);

    // Calculate the distance based on the duration of the pulse
    return ((duration * 0.034) / 2);
}
