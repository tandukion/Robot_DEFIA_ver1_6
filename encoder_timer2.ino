 void initEncoder(){
    pinMode(EN1A, INPUT);
    digitalWrite(EN1A, HIGH);       // turn on pullup resistor
    pinMode(EN2A, INPUT);
    digitalWrite(EN2A, HIGH);       // turn on pullup resistor
    pinMode(EN1B,INPUT);
    digitalWrite(EN1B, HIGH);       // turn on pullup resistor
    pinMode(EN2B,INPUT);
    digitalWrite(EN2B, HIGH);       // turn on pullup resistor  
    attachInterrupt(0,doEncoderKa,RISING);  
    attachInterrupt(1,doEncoderKi,RISING);  
}
  
void doEncoderKa(){
  //case: only 1 channel A 
  EN1Pos++;
}

void doEncoderKi(){
  //case: only 1 channel A 
    EN2Pos++;
}

// Timer 2 for counting motor speed
void initTimer2(){   //Timer2 Register Assignment
  //normal mode
  TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
  //timer 1ms
  TCCR2B=(0<<WGM22) | (1<<CS22) | (0<<CS21) | (0<<CS20);   
  
  TCNT2=0x06;  //start from 6, so totalcount=250
  OCR2A=0x00;
  OCR2B=0x00;
  TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (1<<TOIE2); //Overflow Interrupt Enable
  ASSR=(0<<EXCLK) | (0<<AS2); 
}
  
ISR(TIMER2_OVF_vect) {
  TCNT2=0x06;  //start from 6, so totalcount=250
  TIFR2=0x00;  
  TimerReady=1; 
  
  //timer 1ms
  //speed in rad/s
  wradR=abs(EN1Pos)*1000*2*pi/512;
  wradL=abs(EN2Pos)*1000*2*pi/512;    
  
  EN1Pos=0;
  EN2Pos=0;
  
  
  BigLoop1(KpR,KiR,KdR,vr,wradRefR,wradR,&wradErrorR,&LastErrorR,&LastError2R,&controlsigR,&lastsigR,&saturationR,&moveR);
  BigLoop1(KpL,KiL,KdL,vl,wradRefL,wradL,&wradErrorL,&LastErrorL,&LastError2L,&controlsigL,&lastsigL,&saturationL,&moveL);
  RunMotor(abs(saturationR),abs(saturationL),moveR,moveL);
}
