
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name


void setup() {
  // put your setup code here, to run once:

pinMode(3, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);


}

void cc(int a,int b)
{
 for( int i=1;i<=5;i++)
{  
 
  digitalWrite(b, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(a);    
  digitalWrite(b, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(10-a);
 
}        // wait for a second
}
void loop() {

          analogWrite(3, 30); 
          analogWrite(5, 60); 
          analogWrite(6, 90); 
          analogWrite(9, 130); 
        
          analogWrite(10, 160); 
          analogWrite(11, 200); 
          digitalWrite(12, HIGH); 
          
          
           
    }
         
   



