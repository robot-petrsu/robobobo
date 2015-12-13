
#include <Wire.h>

#define SRF_ADDRESS         0x70                                   // Address of the SRF08  //// was 0x70
#define SRF_ADDRESS1        0x71                                   // Address of the SRF08  //// was 0x70
#define CMD                 (byte)0x00                             // Command byte, values of 0 being sent with write have to be masked as a byte to stop them being misinterpreted as NULL this is a bug with arduino 1.0
#define LIGHTBYTE           (byte)0x01                                   // Byte to read light sensor
#define RANGEBYTE           (byte)0x02                                   // Byte for start of ranging data

byte highByte = 0x00;                             // Stores high byte from ranging
byte lowByte = 0x00;                              // Stored low byte from ranging
byte highByte1 = 0x00;                             // Stores high byte from ranging
byte lowByte1 = 0x00;                              // Stored low byte from ranging

byte num=0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Wire.begin();                               
  delay(5000);                                     // Waits to make sure everything is powered up before sending or receiving data

  int softRev = getSoft();                        // Calls function to get software revision
  Serial.println(softRev, DEC);                     // Print softRev to LCD03

}

void loop() {
  // put your main code here, to run repeatedly:

  int rangeData = getRange();                     // Calls a function to get range
  Serial.print("Range ");
  Serial.print(num);
  Serial.print(" = ");
  Serial.println(rangeData);                   // Print rangeData to LCD03
  Serial.println("   ");                            // Print some spaces to slear spaces after data
  
 delay(250);                                      // Wait before looping

}


int getRange(){                                   // This function gets a ranging from the SRF08
  
  int range = 0; 

  
  Wire.beginTransmission(SRF_ADDRESS);             // Start communticating with SRF08
  Wire.write(byte(CMD));                                 // Send Command Byte
  Wire.write(byte(0x51));                                // Send 0x51 to start a ranging
  Wire.endTransmission();
  

  Wire.beginTransmission(SRF_ADDRESS);             // Start communticating with SRF08
  Wire.write(byte(CMD));  
  Wire.write(byte(RANGEBYTE));                                 // Send Command Byte
  //Wire.endTransmission();

  //delay(105);                                      // Wait for ranging to be complete
  
  delay(1);
  
  Wire.requestFrom(SRF_ADDRESS, 2);                // Request 2 bytes from SRF module
  while(Wire.available() < 2);                     // Wait for data to arrive
    highByte = Wire.read();                          // Get high byte
    lowByte = Wire.read();                           // Get low byte
    range = (highByte << 8) + lowByte;               // Put them together
    Serial.println("Read");
  //  range = highByte;
  
return(range);                                   // Returns Range
}


int getSoft(){                                     // Function to get software revision
  
  Wire.beginTransmission(SRF_ADDRESS);             // Begin communication with the SRF module
  Wire.write(CMD);                                 // Sends the command bit, when this bit is read it returns the software revision
  Wire.endTransmission();
  
  Wire.requestFrom(SRF_ADDRESS, 1);                // Request 1 byte
  while(Wire.available() < 0);                     // While byte available
  int software = Wire.read();                      // Get byte
    
  return(software);                               
  
}

