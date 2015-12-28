/*
 * MasterSend.c
 *
 *  Created on: 06 дек. 2015 г.
 *      Author: Антон
 */

#include "mraa.h"

#include <stdio.h>
#include <unistd.h>


#include "Master_i2c.h"

int MasterSend(char sbyte, char pfreq, int lspeed, char lbrake, int rspeed, char rbrake, int sv0, int sv1, int sv2, int sv3, int sv4, int sv5, char dev,int sens,int lowbat, char i2caddr,char i2cfreq)
{
	uint8_t* tx_buf;
	int i;
	  tx_buf=malloc(24*sizeof(char));
	  for (i=0;i<24;i++)
	  {
		  tx_buf[i]=0;
	  }

	tx_buf[0]=sbyte;					// start byte
	tx_buf[1]=pfreq;					// pwm frequency
	tx_buf[2]=(lspeed&0xFF00)>>8;		// MSB left  motor speed
	tx_buf[3]=(char)(lspeed);			// LSB left  motor speed
	tx_buf[4]=lbrake;					// left  motor brake
	tx_buf[5]=(rspeed&0xFF00)>>8;		// MSB right motor speed
	tx_buf[6]=(char)(rspeed);			// LSB right  motor speed
	tx_buf[7]=rbrake;					// right  motor brake
	tx_buf[8]=(char)((sv0&0xFF00)>>8);	// MSB servo 0
	tx_buf[9]=(char)(sv0);				// LSB servo 0
	tx_buf[10]=(char)((sv1&0xFF00)>>8);	// MSB servo 1
	tx_buf[11]=(char)(sv1);				// LSB servo 1
	tx_buf[12]=(char)((sv2&0xFF00)>>8);	// MSB servo 2
	tx_buf[13]=(char)(sv2);				// LSB servo 2
	tx_buf[14]=(char)((sv3&0xFF00)>>8);	// MSB servo 3
	tx_buf[15]=(char)(sv3);				// LSB servo 3
	tx_buf[16]=(char)((sv4&0xFF00)>>8); // MSB servo 4
	tx_buf[17]=(char)(sv4);				// LSB servo 4
	tx_buf[18]=(char)((sv5&0xFF00)>>8); // MSB servo 5
	tx_buf[19]=(char)(sv5);				// LSB servo 5
	tx_buf[20]=dev;						// devibrate
	tx_buf[21]=(char)((sens&0xFF00)>>8);// MSB impact sensitivity
	tx_buf[22]=(char)(sens);			// LSB impact sensitivity
	tx_buf[23]=(char)((lowbat&0xFF00)>>8);// MSB low battery voltage  550 to 30000 = 5.5V to 30V
	tx_buf[24]=(char)(lowbat);			// LSB low battery voltage
	tx_buf[25]=i2caddr;					// I2C slave address for T'REX controller
	tx_buf[26]=i2cfreq;					// I2C clock frequency:   0=100kHz   1=400kHz

	mraa_i2c_write(i2c,tx_buf,27);		// transmit bufer to TRex

	printf("Master Command Data Packet Sent\n");

	return 0;
}

int MasterReceive()
{//================================================================= Error Checking ==========================================================
  char d;
  int i=0;
  uint8_t* buf;
  buf=malloc(24*sizeof(char));
  for (i=0;i<24;i++)
  {
	  buf[i]=0;
  }
  mraa_i2c_read(i2c,buf,24);
  //sleep(1);
  //Wire.requestFrom(I2Caddress,24);                                // request 24 bytes from device 007
/*
  while(Wire.available()<24)                                      // wait for entire data packet to be received
  {
    if(i==0) printf("Waiting for slave to send data.");     // Only print message once (i==0)
    if(i>0) printf(".");                                    // print a dot for every loop where buffer<24 bytes
    i++;                                                          // increment i so that message only prints once.
    if(i>79)
    {
      printf("\n");
      i=1;
    }
  }
  */
  //d=Wire.read();                                                  // read start byte from buffer
  //d=mraa_i2c_read_byte(i2c);
  d=buf[0];
  printf("Start byte:%X\n",buf[0]);
  if(d!=startbyte)                                                // if start byte not equal to 0x0F
  {
    printf("%u\n",d);
    //while(Wire.available()>0)                                     // empty buffer of bad data
    //{
    	//d=mraa_i2c_read_byte(i2c);
    //}
    printf("  Wrong Start Byte\n");                         // error message
    return -1;                                                       // quit
  }

  //================================================================ Read Data ==============================================================
  printf("Slave Error Message:\n");                           // slave error report
  printf("%X\n",buf[1]);

  i=buf[2]*256+buf[3];
  printf("Battery Voltage:\t%d.%dV\n",(int)(i/10),i-((int)(i/10)*10));

  i=buf[4]*256+buf[5];
  printf("Left  Motor Current:\t%d mA\n",i);	// T'REX left  motor current in mA

  i=buf[6]*256+buf[7];
  printf("Left  Motor Encoder:\t%d\n",i);	// T'REX left  motor encoder count

  i=buf[8]*256+buf[9];
  printf("Right Motor Current:\t%d mA\n",i);		// T'REX right motor current in mA

  i=buf[10]*256+buf[11];
  printf("Right Motor Encoder:\t%d\n",i);		// T'REX right motor encoder count

  i=buf[12]*256+buf[13];
  printf("X-axis:\t\t%d\n",i);				// T'REX X-axis

  i=buf[14]*256+buf[15];
  printf("Y-axis:\t\t%d\n",i); 				// T'REX Y-axis

  i=buf[16]*256+buf[17];
  printf("Z-axis:\t\t%d\n",i);				// T'REX Z-axis

  i=buf[18]*256+buf[19];
  printf("X-delta:\t\t%d\n",i); 			// T'REX X-delta

  i=buf[20]*256+buf[21];
  printf("Y-delta:\t\t%d\n",i);				// T'REX Y-delta

  i=buf[22]*256+buf[23];
  printf("Z-delta:\t\t%d\n",i);				// T'REX Z-delta
  printf("\r\n\n");

  return 0;
}
