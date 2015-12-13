#include <Wire.h>



#define startbyte 0x0F
#define I2Caddress 0x07

/*---Для IMU---*/
float angles[3]; // yaw pitch roll
float heading;
char m;
//BMP085 dps = BMP085();
long Temperature = 0, Pressure = 0, Altitude = 0;
float mdir;
// Set the FreeSixIMU object
//FreeSixIMU sixDOF = FreeSixIMU();

//HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

char buf[128];

int sv[6]={1500,1500,1500,1500,0,0};                 // servo positions: 0 = Not Used
int sd[6]={5,10,-5,-15,20,-20};                      // servo sweep speed/direction
int lmspeed,rmspeed;                                 // left and right motor speed from -255 to +255 (negative value = reverse)
int ldir=5;                                          // how much to change left  motor speed each loop (use for motor testing)
int rdir=5;                                          // how much to change right motor speed each loop (use for motor testing)
byte lmbrake,rmbrake;                                // left and right motor brake (non zero value = brake)
byte devibrate=50;                                   // time delay after impact to prevent false re-triggering due to chassis vibration
int sensitivity=50;                                  // threshold of acceleration / deceleration required to register as an impact
int lowbat=550;                                      // adjust to suit your battery: 550 = 5.50V
byte i2caddr=7;                                      // default I2C address of T'REX is 7. If this is changed, the T'REX will automatically store new address in EEPROM
byte i2cfreq=0;                                      // I2C clock frequency. Default is 0=100kHz. Set to 1 for 400kHz

//HMC5883L mag;

int16_t mx, my, mz;

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
*/

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  Wire.begin();                                      // no address - join the bus as master
    delay(1000);
   // pinMode(5, OUTPUT);
//  dps.init();
//  dps.dumpCalData();
 // delay(5000);
  
 // delay(5);
  
 // sixDOF.init(); //init the Acc and Gyro
 // delay(5);
//  compass = HMC5883L(); // init HMC5883
  
//  error = compass.SetScale(1.3); // Set the scale of the compass.
//  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous  
//  if(error != 0) // If there is an error, print it out.
//    Serial.println(compass.GetErrorText(error));
    //mag.initialize();

    // verify connection
    //Serial.println("Testing device connections...");
    //Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
    //right(100,90);
}


void loop()
{
  //Serial.println("Linux command");  
  /* --- дата-время --- */
 // system("date > /tmp/my.txt");  //получим текущую дату/время
                                   //и сохраним полученные данные в файл my.txt расположенном в /tmp
//  FILE *fp;
//  fp = fopen("/tmp/my.txt", "r");
//  fgets(buf, 128, fp);
//  fclose(fp);
//stop();
  //Serial.print("Now: ");
 // Serial.print(buf);
  
  
  //lmspeed = 120;    // поступательное движение
  //rmspeed = 120;  
   //digitalWrite(5, HIGH);
  if (Serial1.available()) {
    m = Serial1.read();
    if (m == '1')
    {
      lmspeed = -120;    // поворот
      rmspeed = 120;
                                         // send data packet to T'REX controller 
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
      delay(100);
      lmspeed = -100;    // поворот
      rmspeed = 100;
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    }
    if (m == '2')
    {
      lmspeed = 120;    // поворот
      rmspeed = 120;
                                         // send data packet to T'REX controller 
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
      delay(100);
      lmspeed = 35;    // поворот
      rmspeed = 35;
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    }
    if (m == '3')
    {
      lmspeed = -120;    // поворот
      rmspeed = -120;
                                         // send data packet to T'REX controller 
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
      delay(100);
      lmspeed = -35;    // поворот
      rmspeed = -35;
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    }
    if (m == '4')
    {
      lmspeed = 120;    // поворот
      rmspeed = -120;
                                         // send data packet to T'REX controller 
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
      delay(100);
      lmspeed = 100;    // поворот
      rmspeed = -100;
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    }
    if (m == '0')
    {
      lmspeed = 0;
      rmspeed = 0;
      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq); 
      
    }
  }
  /*lmspeed = -120;    // поворот
  rmspeed = 120;
                                                     // send data packet to T'REX controller 
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
  delay(100);
  lmspeed = -80;    // поступательное движение
  rmspeed = 80;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);*/
  //right(80,90);
  //forward(27);
  //=================================================== Code to test motors and sweep servos =============================================  
  
  //lmspeed = 0;
  //rmspeed = 0;
  /*
  lmspeed+=ldir;
  if(lmspeed>60 or lmspeed<-60) ldir=-ldir;        // increase / decrease left motor speed and direction (negative values = reverse direction)
  
  rmspeed+=rdir;
  if(rmspeed>60 or rmspeed<-60) rdir=-rdir;        // increase / decrease left motor speed and direction (negative values = reverse direction)
  
  lmbrake=(abs(lmspeed)>55);                        // test left  motor brake 
  rmbrake=(abs(rmspeed)>55);                        // test right motor brake 
  
  for(byte i=0;i<6;i++)                              // sweep servos
  {
    if(sv[i]!=0)                                     // a value of 0 indicates no servo attached
    {
      sv[i]+=sd[i];                                  // update servo position to create sweeping motion
      if(sv[i]>2000 || sv[i]<1000) sd[i]=-sd[i];     // reverse direction of servo if limit reached
    }
  }
 
  
  //lmspeed=50;
  //rmspeed=0;
  //ldir=-ldir;
  */
  //delay(3000);
  //stop();
  //delay(3000);
  /*
  lmspeed = 0;
  rmspeed = 0;
  MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq); 
  delay(3000);*/
}




