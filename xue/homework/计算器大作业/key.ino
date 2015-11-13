  #include <Keypad.h>
  #define ulong unsigned long
  #define uchar unsigned char
  #define uint unsigned int
  
   int key;
   uchar ge=0,shi=0,bai=0,qian=0,wan=0,shiwan=0,baiwan=0,qianwan=0; 
      ulong dat;       //数据
      ulong datA;      //过度数据
      uchar addflag;   //加法标志位
      uchar subflag;   //减法标志位
      uchar mulflag;   //乘法标志位
      uchar divflag;   //除法标志位
       uchar overflow;  //溢出标志位
      uchar clrflag;   //数据处理标志位
      uchar illegal;   //除法的非法标志位
      uchar keynum;    //按键键值
      uchar keycode;   //按键IO口状态值   
      uchar scanok;    //IO口扫描结束
      uchar checkok;   //键值获取结束
  
  //设置阴极接口
    int a = 13;
    int b = 2;
    int h = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    int g = 7;
    int p = 8;
    //设置阳极接口
    int d4 = 9;
    int d3 = 10;
        int d2 = 11;
    int d1 = 12;
    //设置变量
    long n = 0;
    int x = 100;
    int del = 55;  //此处数值对时钟进行微调
  
   char c = '1';
    //mathematic operations
    float Stack; //Total 
    float Input; //new number entered by user
    
    String Stacks;// to manipulate the stack
    String Inputs; // to manipulate new input
    
    int Size; //control if user has entered a new number
    
    char lastOper;// last number in the stack
    float lastNum;
  
  
  const byte ROWS = 4; //four rows
  const byte COLS = 4; //four columns
  //define the cymbols on the buttons of the keypads
  char hexaKeys[ROWS][COLS] = {
    {'1','4','7','0'},
    {'2','5','8','+'},
    {'3','6','9','-'},
    {'*','/','C','='}
  };
  byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {A4, A5, A6, A7}; //connect to the column pinouts of the keypad
   
  //initialize an instance of class NewKeypad
  Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
   
   
   
   
   
  void setup(){
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    
    pinMode(a,OUTPUT);
    pinMode(b,OUTPUT);
    pinMode(h,OUTPUT);
    pinMode(d,OUTPUT);
    pinMode(e,OUTPUT);
    pinMode(f,OUTPUT);
    pinMode(g,OUTPUT);
    pinMode(p,OUTPUT);
    pinMode(d4,OUTPUT);
    pinMode(d3,OUTPUT);
    pinMode(d2,OUTPUT);
    pinMode(d1,OUTPUT);
    
  }
     
  void loop(){
    
    
     


  //   Serial.println(c);
 
      checkkeycode();
      delay(2);
       calculate_handle();  
       display1();
 
  }
  
  void checkkeycode(void)       
  {
    
     char c = customKeypad.getKey();
   if(c)
     {
       Serial.println(c);
    switch(c)                       //用开关语句查找键值对应的逻辑功能...
    {
     case '0': keynum=0 ; break;  //数字键
     case '1': keynum=1  ;break;
     case '2': keynum=2  ;break;
     case '3': keynum=3  ;break;
     case '4': keynum=4  ;break;
     case '5': keynum=5  ;break;
     case '6': keynum=6  ;break;
     case '7': keynum=7  ;break;
     case '8': keynum=8  ;break;
     case '9': keynum=9  ;break;
     case '+': keynum=10 ;break;   // +
     case '-': keynum=11 ;break;   // -
     case '*': keynum=12 ;break;   // *
     case '/': keynum=13 ;break;   // /
     case '=': keynum=14 ;break;   // =
     case 'C': keynum=15 ;break;   //清零
    }
        checkok=1;  
             //查完后,checkok置1.
   //Serial.println(checkok);
  }
 }
  void add(void)
  {
     addflag++;                          //加法标志置1。。。
     subflag=mulflag=divflag=0;          //将其它运算标志清零。。（一次只能作一种运算）
     clrflag=1;                          //清零标标置1,（当按下加号后，再按第二个加数时，这时应该显示第二加数。。所以要清掉第一个加数。）
     if(addflag>1)                       //此处用于边加。。
     {                                   //当连续加的时候。。加号应有等于的功能。。
         dat=dat+datA;                   //算出和
      datA=dat;                       //和保存，用于下一次连加。。
     }                                   //说明:比如进行"1+2+3"时，当按第二个加时，应该要显示1+2的和。。
     else datA=dat;                      //如果不是连加，将输入的第一个加数暂存。。(因为显示程序只显示dat变量的值。)
   
  }
  
  void sub(void)
  {
     subflag++;
     addflag=mulflag=divflag=0;
     clrflag=1;
     if(subflag>1)                //连减。。
     {
         dat=datA-dat;
      datA=dat;
     }
     else datA=dat;
  }
  
  void mul(void)
  {
     mulflag++;
     addflag=subflag=divflag=0;
     clrflag=1;
     if(mulflag>1)                //连乘
     {
    dat=datA*dat;
    datA=dat;
     }
     else datA=dat;
  }
  
  void div(void)
  {
     divflag++;
     addflag=subflag=mulflag=0;
     clrflag=1;
     if(divflag>1)
     {
       dat=datA/dat;
    datA=dat;
     }
     else datA=dat;
  }

  void equ(void)
  {
   
     if(addflag)                           //如果些时做加法运算。。
     {
     dat=dat+datA;                     //计算各存入dat(显示程序会将dat显示的。。)
     }
     if(subflag)
     {
     dat=datA-dat;
     }
     if(mulflag)
     {
        dat=datA*dat;
     }
     if(divflag)
     {
        dat=datA/dat;
     }
     addflag=subflag=mulflag=divflag=0;    //运算一次完成后将所有运标志清零。为下次运算作准备。。
  }
  
  
  void datpros(void)                     //数据处理函数。。
  {
     if(keynum==15)                      //如果是15  则认为是清零的  进行清零
     {
       dat=0;
     }
    else                                //否则则认为是数字键 进行显示 存贮 并运算
     {
    if(clrflag)                    //清除标志为1,则执行以下。
    {        
     dat=0;
     clrflag = 0;                 //为下次使用准备。
    }
    
    dat=dat*10+(ulong)keynum;     //将每次按的数字合成一个整体。。比如按下"1","2","3"后就会把它合成"123"
    if(dat>1000000000) overflow=1; //如果输入值大于65535(所用的为int型数据，最大为65535)的话则溢出标志置1，可供显示程序查询并显示"EEEEEEE"
    if(divflag&&!dat) illegal=1;   //如果做除法时除了零，则非法标志置1，供显示程序查询
    }
  }
  
  void calculate_handle(void)//计算大函数。。
{
    if(checkok)//如果检测键值完。。则执行以下。。
   {
    checkok=0;//检测完标志清零..
  switch (keynum)//如果是+,-,*,/,=则进入相应的函数。。
  {
   case 10 : add(); break;    //如果是按了"+"，则进入加法函数。
   case 11 : sub(); break;    //如果是按了"-"，则进入加法函数。
   case 12 : mul(); break;    //如果是按了"*"，则进入加法函数。
   case 13 : div(); break;    //如果是按了"/"，则进入加法函数。
   case 14 : equ(); break;    //如果是按了"="，则进入加法函数。
   default : datpros();       //如果不是，计算符（即为数字），则进入数据处理函数。
  }
 }
 
}
    
    void display1(void)
    {
    
     if(!overflow && !illegal)
     { 
      ge=dat%10;                        //将数据分开然后分别显示
      shi=dat%100/10;
      bai=dat/100;
      qian=dat/1000;
//      wan=dat/10000;
//      shiwan=dat00000/100000;
//      baiwan=dat000000/1000000;
//      qianwan=dat0000000/10000000;
//         
   //  Serial.println(ge);
     // P0=table1[ge];   
        pickDigit(4); 
        pickNumber(ge);    //个位显示
        delay(2);
  
         pickDigit(3); 
         pickNumber(shi);                //十位显示
         delay(2);
        //  Serial.println(shi);
         
        pickDigit(2); 
        pickNumber(bai);                 //百位显示
        delay(2);    
    //    Serial.println(bai);
  
        pickDigit(1); 
        pickNumber(qian);                 //百位显示
        delay(2);     

//      P0=table4[qian];                //千位位显示
//      delay(2);   
//      
//      P0=table5[wan];                //wan位显示
//      delay(2);
//      
//      P0=table6[shiwan];               //个位显示
//      delay(2);
//      P0=table7[baiwan];               //个位显示
//      delay(2);
//      P0=table8[qianwan];              //个位显示
//      delay(2);
//     
//      P0=0xff;
}
     else
     {
     pickDigit(0);
     pickNumber(ge);                 //百位显示
     delay(2);
     }
    }
  
  
  
  void pickDigit(int x)  //定义pickDigit(x),其作用是开启dx端口
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
   
    switch(x)
    {
    case 1: 
      digitalWrite(d1, LOW); 
      break;
    case 2: 
      digitalWrite(d2, LOW); 
      break;
    case 3: 
      digitalWrite(d3, LOW); 
      break;
    default: 
      digitalWrite(d4, LOW); 
      break;
    }
  }
   
  void pickNumber(int x)   //定义pickNumber(x),其作用是显示数字x
  {
    switch(x)
    {
    default: 
      zero(); 
      break;
    case 1: 
      one(); 
      break;
    case 2: 
      two(); 
      break;
    case 3: 
      three(); 
      break;
    case 4: 
      four(); 
      break;
    case 5: 
      five(); 
      break;
    case 6: 
      six(); 
      break;
    case 7: 
      seven(); 
      break;
    case 8: 
      eight(); 
      break;
    case 9: 
      nine(); 
      break;
    }
  }
   
  void dispDec(int x)  //设定开启小数点
  {
    digitalWrite(p,HIGH);
  }
   
  void clearLEDs()  //清屏
  {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(h, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(p,LOW);
  }
   
  void zero()  //定义数字0时阴极那些管脚开关
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(h, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
  }
   
  void one()  //定义数字1时阴极那些管脚开关
  {
    digitalWrite(a, LOW);
    digitalWrite(b,HIGH);
    digitalWrite(h,HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  }
   
  void two()  //定义数字2时阴极那些管脚开关
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(h, LOW);
    digitalWrite(d,HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
   
  void three()  //定义数字3时阴极那些管脚开关
  {
    digitalWrite(a, HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(h,HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g,HIGH);
  }
   
  void four()  //定义数字4时阴极那些管脚开关
  {
    digitalWrite(a, LOW);
    digitalWrite(b,HIGH);
    digitalWrite(h, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e,LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g,HIGH);
  }
   
  void five()  //定义数字5时阴极那些管脚开关
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(h, HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g,HIGH);
  }
   
  void six()  //定义数字6时阴极那些管脚开关
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    digitalWrite(h,HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
   
  void seven()  //定义数字7时阴极那些管脚开关
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(h,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f, LOW);
    digitalWrite(g,LOW);
  }
   
  void eight()  //定义数字8时阴极那些管脚开关
  {
    digitalWrite(a,HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(h, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g, HIGH);
  }
   
  void nine()  //定义数字9时阴极那些管脚开关
  {
    digitalWrite(a, HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(h, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }

