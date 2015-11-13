#include <LiquidCrystal.h>

//nano A4 is SDA A5 is SCL

 float dataAvg=0; 
 float dataLux = 0;
 double num = 0.097656;
 LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
void setup()  
{     
      lcd.begin(16, 2);
      Serial.begin(9600); 
      SensorInit(); 	
      delay(1000);
      
     lcd.setCursor(0, 0);
     lcd.print("   Welcome ! ");
     lcd.setCursor(0, 1);
     lcd.print("Press the switch");
 
     
}  
  
void loop()  
{  
  unsigned int i,sum;
  unsigned int datatmp=0;
  
//  
//  for(i=0;i<10;i++)
//  {
//    j = Sensor_Lux_Read();
//    delay(200);
//    Serial.print("j:");
//    Serial.println(dataLux);
//    datatmp = j +  datatmp;
//  }
//    
//      datatmp = datatmp/10;
  dataAvg = 0;datatmp=0;
  sum=0;
  int key=0 ;
  key = analogRead(2);
  delay(100);
  if( key >= 1020 )
  {
     for(i=0;i<=30;i++)
     {
         datatmp = Sensor_Lux_Read();
          delay(100);
          
          dataLux = datatmp*num;
          sum = sum +  dataLux;
          Lcd1602();
       }  
       dataAvg= sum / 30.0;
       key=0 ;
       lcd.clear();
       delay(600);
       Lcd1602_Avg();
       delay(600);
       lcd.clear();
       delay(600);
       Lcd1602_Avg();
       delay(600);
       lcd.clear();
       delay(600);
       Lcd1602_Avg();
       delay(5000);
       lcd.clear();
       
  }
 else
 {
 
     lcd.setCursor(0, 0);
     lcd.print("   Welcome ! ");
     lcd.setCursor(0, 1);
     lcd.print("Press the switch");

  }
  
  
}

void SensorInit()
{
	Sensor_Lux_Init();
      //  Lcd_1602();
}

void Lcd1602()
{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Density:");
      lcd.print(dataLux, 1);
      lcd.print(" N");    
}
void Lcd1602_Avg()
{
    
      lcd.setCursor(0, 0);
      lcd.print(" Density:");
      lcd.print(dataAvg, 1);
      lcd.print(" N"); 
      lcd.setCursor(0, 1);
      lcd.print(" Content:");
      lcd.print(dataAvg, 1);
      lcd.print(" mg"); 
      
}
