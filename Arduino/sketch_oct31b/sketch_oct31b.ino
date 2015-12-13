int val;
int LED = 13;
bool a;

void setup()

{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}
void loop()
{
  if (Serial.available())
  {
    val = Serial.read();
    Serial.println(val);
       if (val == 48)
    {
      digitalWrite(LED, HIGH);
      
    }

    // При символе "0" выключаем светодиод
    if ( val == 49)
    {
      digitalWrite(LED, LOW);
    }
    
    
    
/*    if(val != NULL) 
    {
      if (a) 
      {
        digitalWrite(LED, HIGH); 
        a= not a;
      }
      else
      {
        digitalWrite(LED, LOW)}; 
        a= not a;
      };
    val = NULL;*/
  }
}
    /* При символе "1" включаем светодиод
    if (val == '1')
    {
      digitalWrite(LED, HIGH);
    }

    // При символе "0" выключаем светодиод
    if ( val == '0')
    {
      digitalWrite(LED, LOW);
    }*/

 


