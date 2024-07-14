#include <Ps3Controller.h>

//Motors pins 
int pin1=2,pin2=4,pin3=12,pin4=13;

//Motors speed
int f_speed=0,b_speed=0;
int l_speed=0,r_speed=0;


int yAxisValue;//Left stick  - y axis - forward/backward car movement
int xAxisValue;//Right stick - x axis - left/right car movement

void notify()
{
  yAxisValue =(Ps3.data.analog.stick.ly);
  xAxisValue =(Ps3.data.analog.stick.rx);
  
  //This is to map the values of sticks 
  f_speed = map(yAxisValue, 0, -128,   0, 255);
  b_speed = map(yAxisValue, 0,   128,  0, 255);
  r_speed = map(xAxisValue, 0,   128,  0, 255);
  l_speed = map(xAxisValue, 0, -128,   0, 256);


  if(f_speed>0 && l_speed ==0 && r_speed ==0)
  {
    //F
    analogWrite(pin1,f_speed);
    analogWrite(pin2,LOW);
    analogWrite(pin3,LOW);
    analogWrite(pin4,f_speed);
  
  }

  else if(b_speed>0 && l_speed ==0 && r_speed ==0)
  {
    //B
    analogWrite(pin1,LOW);
    analogWrite(pin2,b_speed);
    analogWrite(pin3,b_speed);
    analogWrite(pin4,LOW);
    
  }

  else if(l_speed>0 && f_speed <=0 && b_speed <=0)
  {
    //R
    analogWrite(pin1,LOW);
    analogWrite(pin2,l_speed);
    analogWrite(pin3,LOW);
    analogWrite(pin4,l_speed);
    
  }
  else if(r_speed>0 && f_speed<=0 && b_speed<=0)
  {

    analogWrite(pin1,r_speed);
    analogWrite(pin2,LOW);
    analogWrite(pin3,r_speed);
    analogWrite(pin4,LOW);
    //L
  

  }


  else if(f_speed >0 && r_speed >0)
  {
    //F: R
    analogWrite(pin1,r_speed);
    analogWrite(pin2,LOW);
    analogWrite(pin3,LOW);
    analogWrite(pin4,f_speed/4);

  }

  else if(f_speed >0 && l_speed >0)
  {
    //F: L
    analogWrite(pin1,f_speed/4);
    analogWrite(pin2,LOW);
    analogWrite(pin3,LOW);
    analogWrite(pin4,l_speed);

  }

  else if(b_speed >0 && r_speed >0)
  {
    //B: R
    analogWrite(pin1,LOW);
    analogWrite(pin2,r_speed/4);
    analogWrite(pin3,b_speed);
    analogWrite(pin4,LOW);
    
  }

  else if(b_speed >0 && l_speed >0 )
  {
    //B: L 
    analogWrite(pin1,LOW);
    analogWrite(pin2,b_speed);
    analogWrite(pin3,l_speed/4);
    analogWrite(pin4,LOW);
    
  }
  
  else
  {
    analogWrite(pin1,LOW);
    analogWrite(pin2,LOW);
    analogWrite(pin3,LOW);
    analogWrite(pin4,LOW);
  }
  Serial.println(f_speed);

}

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  f_speed =0, l_speed =0, b_speed =0, r_speed = 0;
}


void setUpPinModes()
{

  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);

}


void setup()
{
  setUpPinModes();
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisConnect);
  Ps3.begin();
  Serial.println("Ready.");
}

void loop()
{

}