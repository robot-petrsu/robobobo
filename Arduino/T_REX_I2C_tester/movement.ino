/*float magnetometr()
{
     mag.getHeading(&mx, &my, &mz);

    // display tab-separated gyro x/y/z values
    Serial.print("mag:\t");
    Serial.print(mx); Serial.print("\t");
    Serial.print(my); Serial.print("\t");
    Serial.print(mz); Serial.print("\t");
    
// To calculate heading in degrees. 0 degree indicates North
    float heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    Serial.print("heading:\t");
    Serial.println(heading * 180/M_PI);
    return heading * 180/M_PI;
    // blink LED to indicate activity
    //blinkState = !blinkState;
    //digitalWrite(LED_PIN, blinkState);
}



void forward(int spd)
{
  lmspeed = 120;    
  rmspeed = 120;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
  delay(100);
  lmspeed = spd;    
  rmspeed = spd;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    
}

void backward(int spd)
{
  lmspeed = -120;    
  rmspeed = -120;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
  delay(100);
  lmspeed = spd;    
  rmspeed = spd;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
}

void left(int spd, int deg)
{
  float mdirP, mdirC; //magnitometr dir past/current
  
  mdirC = magnetometr();
  Serial.println("begore: ");
  Serial.print(mdirC);
  lmspeed = -120;    
  rmspeed = 120;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
  delay(100);
  
  while (!(20>abs(mdirC-deg)))
  {
    lmspeed = -spd;    
    rmspeed = spd;
    MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    mdirC = magnetometr();  
  }
  
  Serial.println("after: ");
  Serial.print(mdirC);
  lmspeed = 0;    
  rmspeed = 0;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
}

void right(int spd, int deg)
{
  float mdirP, mdirC; //magnitometr dir past/current
  
  mdirC = magnetometr();
  lmspeed = 120;    
  rmspeed = -120;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
  delay(100);
  mdirP = magnetometr();
  Serial.println(mdirC);
  Serial.println(mdirP);
  Serial.println(abs(mdirC-mdirP));
  while (((deg>abs(mdirC-mdirP)) ))//|| (deg+5<abs(mdirC-mdirP))))
  {
    lmspeed = spd;    
    rmspeed = -spd;
    MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    mdirP = magnetometr();
    Serial.println(abs(mdirP-mdirC));
  }
  Serial.println("EXIT");
  lmspeed = 0;    
  rmspeed = 0;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
}

void stop()
{
  lmspeed = 0;
  rmspeed = 0;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
}*/
