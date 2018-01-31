void initDriverMotor() { 
   //A is right, B is left
   pinMode(AIN1, OUTPUT);
   pinMode(AIN2, OUTPUT);
   pinMode(PWMA, OUTPUT); 
   
   pinMode(BIN1, OUTPUT);
   pinMode(BIN2, OUTPUT);
   pinMode(PWMB, OUTPUT);
   
   pinMode(STBY, OUTPUT); 
}

void RunMotor(int pwmR, int pwmL, int dirR, int dirL){
  if (dirR==1){ 
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW); 
  }
  else if (dirR==-1){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH); 
  }
  else{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW); 
  }
  
  if (dirL==1){ 
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH); 
  }
  else if (dirL==-1){
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW); 
  }
  else{
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW); 
  }
  if (dirR!=0)
    analogWrite(PWMA,pwmR);
  else
    analogWrite(PWMA,200);  // for stopping
  if (dirL!=0)
    analogWrite(PWMB,pwmL);
  else
    analogWrite(PWMB,200);  // for stopping
  digitalWrite(STBY, HIGH);
}
