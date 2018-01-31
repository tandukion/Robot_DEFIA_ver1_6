// by DEFIA
// Dwindra Sulistyoutomo
// Edwin Raissa Varian Wahyudi
// Febryanto Chang
// Robosoccer Small Size League 2014

//update ver 1.2
// reset lasterror, lastsig, lasterror2 when set point change (ref!=lastref)
// see at serial.ino

//update ver 1.3
// PI calculation changed a bit

//update ver 1.4
// Kb changed from 1 to 12 

#define id  2 //id of robot

//motor 1->right motor 2->left

#define EN1A 2
#define EN2A 3
#define EN1B 4
#define EN2B 5

//define motor >> yujin pcb baru
#define AIN1 13
#define AIN2 8
#define BIN1 12
#define BIN2 11
#define STBY 7
#define PWMA 9
#define PWMB 10

// for control
#define Kn 1380  //speed constant based on datasheet (rpm/V)
#define Ke 0.725 //Back EMF constant (mV/rpm)
#define Ts 0.001 //sampling time

#define maxwrad 533

//pi
#define pi 3.14159

//for serial
  static FILE uartout = {0};
  byte head = 253;
  byte tail = 254;
  char dataIn[12];
  int vr,vl;

//variable for encoder and speed
  long EN1Pos = 0;
  long EN2Pos = 0;
  double wradR=0;
  double wradL=0;
  int TimerReady=0;
//int time;

//variable for control
  int    moveR=0,       moveL=0;
  double wradRefR=0,    wradRefL=0;
  double LastRefR=0,    LastRefL=0;
  double wradErrorR=0,  wradErrorL=0;
  double LastErrorR=0,  LastErrorL=0;
  double LastError2R=0, LastError2L=0;
  double controlsigR=0, controlsigL=0; 
  double lastsigR=0,    lastsigL=0;
  double saturationR=0, saturationL=0;
  double antiwindupR=0, antiwindupL=0;
  double KpR=0.57,       KpL=0.57; 
  double KiR=52.19,     KiL=52.19;  
  double KdR=0,         KdL=0;  
  double Kb=12; //konstanta back-calculation

void setup(){ 
  Serial.begin (9600);
  //for serial data
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout ;
    TCCR1B = TCCR1B & 0b11111000 | 0x01;
  
  digitalWrite(PWMA, OUTPUT);
  digitalWrite(PWMB, OUTPUT);
  initEncoder();
  initTimer2();
  initDriverMotor();
}

int i;
int j=20;

void loop(){
  if((Serial.available() > 0)&&(Serial.read()==head))
  {
    Serial.readBytesUntil(tail, dataIn, 12);
    parsingData(dataIn);
    //memset(dataIn,  0, sizeof(dataIn));
  }
}
