char buf[128];

void setup() {
  Serial.begin(115200);
  
  FILE *hostname;
  hostname = fopen("/etc/hostname", "r");
  fgets(buf, 128, hostname);
  fclose(hostname);
  Serial.print("HOST: ");
  Serial.println(buf);
}

void loop() {  
 
  /* --- дата-время --- */
  system("date > /tmp/my.txt");  //получим текущую дату/время
                                   //и сохраним полученные данные в файл my.txt расположенном в /tmp
  FILE *fp;
  fp = fopen("/tmp/my.txt", "r");
  fgets(buf, 128, fp);
  fclose(fp);

  Serial.print("Now: ");
  Serial.print(buf);
  
  /* --- IP-адрес --- */
  system("ifconfig | grep inet | grep -v inet6 | grep -v 127.0.0.1 | cut -d: -f2 | awk '{printf $1""\n""}' > /tmp/my.txt");  

  fp = fopen("/tmp/my.txt", "r");
  fgets(buf, 128, fp);
  fclose(fp);

  Serial.print("Current IP: ");
  Serial.println(buf);
  
  /* --- температура SoC --- */
  int temp;
  temp = getQuarkTemp();
  Serial.print("The temperature of the Quark SoC is ");
  Serial.print(temp);
  Serial.println(" degrees celcius.");
  
  /* --- uptime --- */
  system("uptime > /tmp/my.txt");  

  fp = fopen("/tmp/my.txt", "r");
  fgets(buf, 128, fp);
  fclose(fp);

  //Serial.print("Current IP: ");
  Serial.println(buf);
  
  Serial.println();
  delay(3000);
}

int getQuarkTemp(){
  char temp_raw[6];
  FILE *fp;
  fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r"); 
  fgets(temp_raw, 5, fp);
  fclose(fp);
  int temp = atoi(temp_raw);
  temp /= 100;
  return temp;  
}
