static int uart_putchar (char c, FILE *stream) {
   Serial.write(c);
   return 0 ;
}

void parsingData(char dt[]){
    vr = (unsigned char)dt[(id*2)-1];
    vl = (unsigned char)dt[(id*2)-2];
    
    wradRefR= abs(double(vr-127)) *maxwrad/127;
    wradRefL= abs(double(vl-127)) *maxwrad/127;
    
    if (wradRefR!=LastRefR){
      lastsigR=0;
      LastErrorR=0;
      LastError2R=0;
      LastRefR=wradRefR;
    }
    
    if (wradRefL!=LastRefL){
      lastsigL=0;
      LastErrorL=0;
      LastError2L=0;
      LastRefL=wradRefL;
    }
} 
