
void negSUM(double reference, double actual, double *error){
  *error=reference-actual;
}

void PID_AntiWindup(double Kp, double Ki, double Kd, double error, double LastError, double LastError2, double saturation, double lastsignal, double *controlsignal){
  double antiwindup;
  negSUM(saturation,*controlsignal,&antiwindup);
  //absolute antiwindup
  *controlsignal= Kp*(error-LastError) + (Ki*error+Kb*antiwindup)*Ts + Kd*(error-2*LastError+LastError2)/Ts +lastsignal;
}

void PWMSaturation (double input, int v, int *dir, double *output){
  //direction change for stopping (w=0)
  if (input==0)
    *dir=0;
  else {
    if (v>127)
      *dir=1;
    else if (v<127)
      *dir=-1;
  }
  //saturation limit
  if (input>255)
    *output=255;
  else if (input<0)
    *output=0;
  else
    *output=input;
}

//skema 1
void BigLoop1 (double Kp, double Ki, double Kd, int v, double Ref, double Act, double *Error, double *LastError, double *LastError2, double *Sig, double *LastSig, double *Sat, int *dir){
  negSUM(Ref,Act,&(*Error));
  PID_AntiWindup(Kp,Ki,Kd,*Error,*LastError,*LastError2,*Sat,*LastSig,&(*Sig));
  *LastSig=*Sig;
  *LastError2=*LastError;
  *LastError=*Error;
  PWMSaturation(*Sig,v,&(*dir),&(*Sat));
}

