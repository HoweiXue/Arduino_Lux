#define R 11
#define G 10
#define B 9      

void setup()
{
pinMode(R,OUTPUT);
pinMode(G,OUTPUT);
pinMode(B,OUTPUT);    
}

void loop()
{
  int value=analogRead(A0);   
  int value1=analogRead(A1);
  int value2=analogRead(A2);
  
  if (value>=0 && value<256)     
  {
   analogWrite(R,value);      
   analogWrite(G,0);
   analogWrite(B,0);      
  }
  
  else if(value>=256 && value<512)
  {
   analogWrite(G,value1-256);  
   analogWrite(R,0);
   analogWrite(B,0);
  }
  else if(value>=512 && value<768)
  {
   analogWrite(B,value-512);  
   analogWrite(R,0);
   analogWrite(G,0);
  }
//  else
//   {
//    analogWrite(R,value-768);
//    analogWrite(G,value-768);
//    analogWrite(B,value-768);  
//   }
}
