/*
 * Master_i2c.h
 *
 *  Created on: 06 дек. 2015 г.
 *      Author: Антон
 */

#ifndef MASTER_I2C_H_
#define MASTER_I2C_H_

#define startbyte 0x0F
#define I2Caddress 0x07


mraa_i2c_context i2c;

int MasterSend(char sbyte, char pfreq, int lspeed, char lbrake, int rspeed, char rbrake, int sv0, int sv1, int sv2, int sv3, int sv4, int sv5, char dev,int sens,int lowbat, char i2caddr,char i2cfreq);
int MasterReceive();
#endif /* MASTER_I2C_H_ */
