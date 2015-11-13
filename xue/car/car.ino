#include <Servo.h>

    Servo myservo;  
 
   
const int you1 =  3;   //1  
const int you2 =  5;   //0
const int zuo1 =  6; 
const int zuo2 =  9; 
//
//const int d0 =  6; 
//const int d1 =  7; 
//const int d2 =  8; 
//const int d3 =  9; 

int state = 0;
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int pos = 0;    // 定义舵机转动位置
void qian()
{
      analogWrite(3, 230); 
      analogWrite(5, 0); 
      analogWrite(6, 230); 
      analogWrite(9, 0); 
     
     
}

void hou()//后退子函数
{
      analogWrite(3, 0); 
      analogWrite(5, 200); 
      analogWrite(6, 0); 
      analogWrite(9, 200); 

}
void zuo()//左转子函数
{
       analogWrite(3, 230); 
       analogWrite(5, 0); 
       analogWrite(6, 150); 
       analogWrite(9, 0); 

}
void you()//右转子函数
{
        analogWrite(3, 150); 
        analogWrite(5, 0); 
        analogWrite(6, 230); 
        analogWrite(9, 0); 

}
void down() //左右轮都停止转动
{
     analogWrite(3, 0); 
     analogWrite(5, 0); 
     analogWrite(6, 0); 
     analogWrite(9, 0); 

}
void duoji()
{
 for(pos = 0; pos < 180; pos += 10)  
     {  
        myservo.write(pos);  
        delay(15); 
      }
      // 180到0旋转舵机，每次延时15毫秒 
      for(pos = 180; pos>=90; pos-=10)
      {                               
        myservo.write(pos);
        delay(15);
      }
}

void setup() {
  
   myservo.attach(11);  // 设置舵机控制针脚
  
  pinMode(3, OUTPUT);      
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(9, OUTPUT); 
  

   pinMode(2, INPUT);   
   pinMode(4, INPUT);  
   pinMode(7, INPUT);  
   pinMode(8, INPUT);  
 
}


void loop(){
  
  
           down();
       //state = pulseIn(2,HIGH);  
       state = digitalRead(2);
      state1 = digitalRead(4);
      state2 = digitalRead(7);
      state3 = digitalRead(8);
  
         
     
  
      if (state == HIGH)     
        {  
              
                qian();
               
                duoji();
        }
  
  
    if(state1 == HIGH ) {    
     
               hou();
               duoji();
           
    }
  
    if (state2 == HIGH)   {  
   
            you();
            duoji();
    }
    if (state3 == HIGH)  {   
          
           zuo();
           duoji();
     }   
 
  
  }
  
  
  

