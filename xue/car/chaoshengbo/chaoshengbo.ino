#include <Servo.h>   
int pinLB=9;     // 定义8脚位 左后  0
int pinLF=6;     // 定义9脚位 左前  
  
int pinRB=5;    // 定义10脚位 右后  0
int pinRF=3;    // 定义11脚位 右前  1
  
int inputPin = A0;  // 定义超音波信号接收脚位  
int outputPin =A1;  // 定义超音波信号发射脚位  
  
int Fspeedd = 0;      // 前速  
int Rspeedd = 0;      // 右速  
int Lspeedd = 0;      // 左速  
int directionn = 0;   // 前=8 后=2 左=4 右=6   
Servo myservo;        // 设 myservo  
int delay_time = 250; // 伺服马达转向后的稳定时间  
  
int Fgo = 8;         // 前进  
int Rgo = 6;         // 右转  
int Lgo = 4;         // 左转  
int Bgo = 2;         // 倒车  
  
void setup()  
 {  
// Serial.begin(9600);     // 定义马达输出脚位   
  pinMode(pinLB,OUTPUT); // 脚位 8 (PWM)  
  pinMode(pinLF,OUTPUT); // 脚位 9 (PWM)  
  pinMode(pinRB,OUTPUT); // 脚位 10 (PWM)   
  pinMode(pinRF,OUTPUT); // 脚位 11 (PWM)  
    
  pinMode(inputPin, INPUT);    // 定义超音波输入脚位  
  pinMode(outputPin, OUTPUT);  // 定义超音波输出脚位     
  
  myservo.attach(11);    // 定义伺服马达输出第5脚位(PWM)  
 }  
void advance(int a)     // 前进  
    {  
//     digitalWrite(pinRB,LOW);  // 使马达（右后）动作  
//     digitalWrite(pinRF,HIGH);  
//     digitalWrite(pinLB,LOW);  // 使马达（左后）动作  
//     digitalWrite(pinLF,HIGH);  
     analogWrite(pinRB,0);  
     analogWrite(pinRF,200);  
     analogWrite(pinLB,0);  
     analogWrite(pinLF,200);  
     delay(a * 50);       
    }  
  
void right(int b)        //右转(单轮)  
    {  
//     digitalWrite(pinRB,LOW);   //使马达（右后）动作  
//     digitalWrite(pinRF,HIGH);  
//     digitalWrite(pinLB,HIGH);  
//     digitalWrite(pinLF,HIGH); 
        analogWrite(pinRB,0);  
     analogWrite(pinRF,200);  
     analogWrite(pinLB,200);  
     analogWrite(pinLF,200);   
     delay(b * 20);  
    }  
void left(int c)         //左转(单轮)  
    {  
//     digitalWrite(pinRB,HIGH);  
//     digitalWrite(pinRF,HIGH);  
//     digitalWrite(pinLB,LOW);   //使马达（左后）动作  
//     digitalWrite(pinLF,HIGH); 
     analogWrite(pinRB,200);  
     analogWrite(pinRF,200);  
     analogWrite(pinLB,0);  
     analogWrite(pinLF,200);   
     delay(c * 20);  
    }  
void turnR(int d)        //右转(双轮)  
    {  
//     digitalWrite(pinRB,LOW);  //使马达（右后）动作  
//     digitalWrite(pinRF,HIGH);  
//     digitalWrite(pinLB,HIGH);  
//     digitalWrite(pinLF,LOW); 
     analogWrite(pinRB,0);  
     analogWrite(pinRF,200);  
     analogWrite(pinLB,200);  
     analogWrite(pinLF,0);   //使马达（左前）动作  
     delay(d * 15);  
    }  
void turnL(int e)        //左转(双轮)  
    {  
//     digitalWrite(pinRB,HIGH);  
//     digitalWrite(pinRF,LOW);   //使马达（右前）动作  
//     digitalWrite(pinLB,LOW);   //使马达（左后）动作  
//     digitalWrite(pinLF,HIGH);  
     analogWrite(pinRB,200);  
     analogWrite(pinRF,0);  
     analogWrite(pinLB,0);  
     analogWrite(pinLF,200);  
     delay(e * 15);  
    }      
void stopp(int f)         //停止  
    {  
     analogWrite(pinRB,0);  
     analogWrite(pinRF,0);  
     analogWrite(pinLB,0);  
     analogWrite(pinLF,0);  
     delay(f * 50);  
    }  
void back(int g)          //后退  
    {  
  
//     digitalWrite(pinRB,HIGH);  //使马达（右后）动作  
//     digitalWrite(pinRF,LOW);  
//     digitalWrite(pinLB,HIGH);  //使马达（左后）动作  
//     digitalWrite(pinLF,LOW); 
     analogWrite(pinRB,200);  
     analogWrite(pinRF,0);  
     analogWrite(pinLB,200);  
     analogWrite(pinLF,0);   
     delay(g * 50);       
    }  
      
void detection()        //测量3个角度(0.90.179)  
    {        
      int delay_time = 250;   // 伺服马达转向后的稳定时间  
      ask_pin_F();            // 读取前方距离  
//        
//     if(Fspeedd < 15)         // 假如前方距离小于10公分  
//      {  
//      stopp(1);               // 清除输出数据   
//      back(2);                // 后退 0.2秒  
//      }  
             
      if(Fspeedd < 20)         // 假如前方距离小于25公分  
      {  
        stopp(1);               // 清除输出数据   
        ask_pin_L();            // 读取左方距离  
        delay(delay_time);      // 等待伺服马达稳定  
        ask_pin_R();     23       // 读取右方距离    
        delay(delay_time);      // 等待伺服马达稳定    
          
        if(Lspeedd >= Rspeedd || Lspeedd >= 20  )   //假如 左边距离大于右边距离  
        {  
         directionn = Lgo;      //向右走  
        }  
          
        if(Lspeedd <= Rspeedd || Rspeedd >= 20)   //假如 左边距离小于或等于右边距离  
        {  
         directionn = Rgo;      //向左走  
        }   
          
        if (Lspeedd < 5 && Rspeedd < 5)   //假如 左边距离和右边距离皆小于10公分  
        {  
         directionn = Bgo;      //向后走          
        }            
      }  
      else                      //加如前方不小于(大于)25公分       
      {  
        directionn = Fgo;        //向前走       
      }  
       
  
    }      
void ask_pin_F()   // 量出前方距离   
    {  
      myservo.write(90);  
      digitalWrite(outputPin, LOW);   // 让超声波发射低电压2μs  
      delayMicroseconds(2);  
      digitalWrite(outputPin, HIGH);  // 让超声波发射高电压10μs，这里至少是10μs  
      delayMicroseconds(10);  
      digitalWrite(outputPin, LOW);    // 维持超声波发射低电压  
      float Fdistance = pulseIn(inputPin, HIGH);  // 读差相差时间  
      Fdistance= Fdistance/5.8/10;       // 将时间转为距离距离（单位：公分）  
  //    Serial.print("F distance:");      //输出距离（单位：公分）  
     // Serial.println(Fdistance);         //显示距离  
      Fspeedd = Fdistance;              // 将距离 读入Fspeedd(前速)  
    }    
 void ask_pin_L()   // 量出左边距离   
    {  
      myservo.write(5);  
      delay(delay_time);  
      digitalWrite(outputPin, LOW);   // 让超声波发射低电压2μs  
      delayMicroseconds(2);  
      digitalWrite(outputPin, HIGH);  // 让超声波发射高电压10μs，这里至少是10μs  
      delayMicroseconds(10);  
      digitalWrite(outputPin, LOW);    // 维持超声波发射低电压  
      float Ldistance = pulseIn(inputPin, HIGH);  // 读差相差时间  
      Ldistance= Ldistance/5.8/10;       // 将时间转为距离距离（单位：公分）  
  //    Serial.print("L distance:");       //输出距离（单位：公分）  
    //  Serial.println(Ldistance);         //显示距离  
      Lspeedd = Ldistance;              // 将距离 读入Lspeedd(左速)  
    }    
void ask_pin_R()   // 量出右边距离   
    {  
      myservo.write(175);  
      delay(delay_time);  
      digitalWrite(outputPin, LOW);   // 让超声波发射低电压2μs  
      delayMicroseconds(2);  
      digitalWrite(outputPin, HIGH);  // 让超声波发射高电压10μs，这里至少是10μs  
      delayMicroseconds(10);  
      digitalWrite(outputPin, LOW);    // 维持超声波发射低电压  
      float Rdistance = pulseIn(inputPin, HIGH);  // 读差相差时间  
      Rdistance= Rdistance/5.8/10;       // 将时间转为距离距离（单位：公分）  
 //     Serial.print("R distance:");       //输出距离（单位：公分）  
  //    Serial.println(Rdistance);         //显示距离  
      Rspeedd = Rdistance;              // 将距离 读入Rspeedd(右速)  
    }    
      
void loop()  
 {  
    myservo.write(90);  //让伺服马达回归 预备位置 准备下一次的测量  
    detection();      //测量角度 并且判断要往哪一方向移动  
   
        
       if(directionn == 2)  //假如directionn(方向) = 2(倒车)               
  {  
      back(2);                    //  倒退(车)  
     turnL(2);                   //些微向左方移动(防止卡在死巷里)  
   //  Serial.print(" Reverse ");   //显示方向(倒退)  
   }  
   if(directionn == 6)           //假如directionn(方向) = 6(右转)      
   {  
     back(4);   
     turnR(12);                   // 右转  
  //   Serial.print(" Right ");    //显示方向(左转)  
   }  
   if(directionn == 4)          //假如directionn(方向) = 4(左转)      
   {    
     back(4);        
     turnL(12);                  // 左转  
  //   Serial.print(" Left ");     //显示方向(右转)     
   }    
   if(directionn == 8)          //假如directionn(方向) = 8(前进)        
   {   
    advance(1);                 // 正常前进    
 //   Serial.print(" Advance ");   //显示方向(前进)  
  //  Serial.print("   ");      
   }  
 }  
