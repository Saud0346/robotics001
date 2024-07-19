#include <Ps3Controller.h>

// Motor pins
const int pin1 = 2;
const int pin2 = 4;
const int pin3 = 12;
const int pin4 = 13;

// Motor speeds
int f_speed = 0, b_speed = 0;
int l_speed = 0, r_speed = 0;

int yAxisValue; // Left stick - y axis - forward/backward car movement
int xAxisValue; // Right stick - x axis - left/right car movement

void notify()
{
    yAxisValue = Ps3.data.analog.stick.ly;
    xAxisValue = Ps3.data.analog.stick.rx;

    // Map the values of sticks
    f_speed = map(yAxisValue, 0, -127, 0, 252);
    b_speed = map(yAxisValue, 0,  128, 0, 255);
    r_speed = map(xAxisValue, 0,  127, 0, 255);
    l_speed = map(xAxisValue, 0, -128, 0, 255);

    move(f_speed,b_speed,l_speed,r_speed);
    // Serial.print(f_speed);
    // Serial.print("  ");
    // Serial.print(b_speed);
    // Serial.print("  ");
    // Serial.print(l_speed);
    // Serial.print("  ");
    // Serial.print(r_speed);
    // Serial.print("  ");
    // Serial.println("");
}


void move(int &f_speed, int &b_speed, int &l_speed, int &r_speed)
{
    int val1=0,val2=0,val3=0,val4=0;

    if (f_speed > 0 && l_speed <= 0 && r_speed <= 0)
    val1 = val4 = f_speed;                                 // Forward
    else if (b_speed > 0 && l_speed <= 0 && r_speed <= 0)
    val2 = val3 = b_speed;                                 // Backward
    else if (l_speed > 0 && f_speed <= 0 && b_speed <= 0)
    val1 = val3 = l_speed;                                 // Left
    else if (r_speed > 0 && f_speed <= 0 && b_speed <= 0)
    val2 = val4 = r_speed;                                 // Right
    else if (f_speed > 0 && r_speed > 0)
    {
      // Forward-right
      val1 = r_speed/4;
      val4 = f_speed;
    }
    else if (f_speed > 0 && l_speed > 0)
    {

        // Forward-left
        val1 = f_speed;
        val4 = l_speed/4;

    }
    else if (b_speed > 0 && r_speed > 0)
    {
        // Backward-right
        val2 = r_speed/4;
        val3 = b_speed;

    }
    else if (b_speed > 0 && l_speed > 0)
    {
        // Backward-left
        val2 = b_speed;
        val3 = l_speed/4;
    }
    else
    val1=val2=val3=val4=0;


    analogWrite(pin1, val1);
    analogWrite(pin2, val2);
    analogWrite(pin3, val3);
    analogWrite(pin4, val4);
}

void onConnect()
{
    Serial.println("Connected!");
}

void onDisconnect()
{
    f_speed = 0;
    l_speed = 0;
    b_speed = 0;
    r_speed = 0;
}

void setUpPinModes()
{
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
}

void setup()
{
    setUpPinModes();
    Serial.begin(115200);
    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.attachOnDisconnect(onDisconnect);
    Ps3.begin();
    Serial.println("Ready.");
    
}
void loop()
{
    // The loop can be left empty if no continuous task is needed
}
