#include "mraa.h"

#include <stdio.h>
#include <unistd.h>

#include "Master_i2c.h"

#define startbyte 0x0F
#define I2Caddress 0x07

int main()
{

	int sv[6]={1500,1500,1500,1500,0,0};                 // servo positions: 0 = Not Used
	//int sd[6]={5,10,-5,-15,20,-20};                      // servo sweep speed/direction
	int lmspeed,rmspeed;                                 // left and right motor speed from -255 to +255 (negative value = reverse)
	//int ldir=5;                                          // how much to change left  motor speed each loop (use for motor testing)
	//int rdir=5;                                          // how much to change right motor speed each loop (use for motor testing)
	char lmbrake,rmbrake;                                // left and right motor brake (non zero value = brake)
	char devibrate=50;                                   // time delay after impact to prevent false re-triggering due to chassis vibration
	int sensitivity=50;                                  // threshold of acceleration / deceleration required to register as an impact
	int lowbat=550;                                      // adjust to suit your battery: 550 = 5.50V
	char i2caddr=7;                                      // default I2C address of T'REX is 7. If this is changed, the T'REX will automatically store new address in EEPROM
	char i2cfreq=0;                                      // I2C clock frequency. Default is 0=100kHz. Set to 1 for 400kHz

	char* m;

	mraa_init();

	mraa_uart_context uart;
	uart = mraa_uart_init(0);
    if (uart == NULL) {
        fprintf(stderr, "UART failed to setup\n");
        return EXIT_FAILURE;
    }
    mraa_uart_set_baudrate(uart,9600);
    mraa_uart_set_mode(uart, 8, MRAA_UART_PARITY_NONE , 1);

    char buffer[] = "Hello Mraa!";
    mraa_uart_write(uart, buffer, sizeof(buffer));
    m=malloc(sizeof(unsigned char));
    m[0]='0';
    //

    i2c = mraa_i2c_init(0);
    mraa_i2c_frequency(i2c,MRAA_I2C_STD);
    mraa_i2c_address(i2c, I2Caddress);		// transmit data to 7
    lmspeed=100;
    rmspeed=100;
    rmbrake=0;
    lmbrake=0;
    while (1)
    {
    	if (mraa_uart_data_available(uart,100))
    	{
    		mraa_uart_read(uart,m,1);
    		 //--отладочная часть--//
    		//m[0]=m[0]+1;
    		mraa_uart_write(uart,m,1);

    	    if (m[0] == '1')
    	    {
    	      lmspeed = -120;    // поворот
    	      rmspeed = 120;
    	                                         // send data packet to T'REX controller
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	      usleep(100000);
    	      lmspeed = -100;    // поворот
    	      rmspeed = 100;
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	    }
    	    if (m[0] == '2')
    	    {
    	      lmspeed = 120;    // поворот
    	      rmspeed = 120;
    	                                         // send data packet to T'REX controller
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	      usleep(100000);
    	      lmspeed = 35;    // поворот
    	      rmspeed = 35;
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	    }
    	    if (m[0] == '3')
    	    {
    	      lmspeed = -120;    // поворот
    	      rmspeed = -120;
    	                                         // send data packet to T'REX controller
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	      usleep(100000);
    	      lmspeed = -35;    // поворот
    	      rmspeed = -35;
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	    }
    	    if (m[0] == '4')
    	    {
    	      lmspeed = 120;    // поворот
    	      rmspeed = -120;
    	                                         // send data packet to T'REX controller
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	      usleep(100000);
    	      lmspeed = 100;    // поворот
    	      rmspeed = -100;
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	    }
    	    if (m[0] == '0')
    	    {
    	      lmspeed = 0;
    	      rmspeed = 0;
    	      MasterSend(startbyte,6,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);

    	    }
    	}

    	//MasterSend(startbyte,2,lmspeed,lmbrake,rmspeed,rmbrake,sv[0],sv[1],sv[2],sv[3],sv[4],sv[5],devibrate,sensitivity,lowbat,i2caddr,i2cfreq);
    	//usleep(500000);
    	//MasterReceive();
    	//usleep(200000);
    	//sleep(2);
    }

    mraa_uart_stop(uart);
    mraa_deinit();

    return 0;
}
