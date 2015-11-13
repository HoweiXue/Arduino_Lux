 #include <LiquidCrystal.h>
// WIFI 7-7
#include <ESP8266.h>

#include "dht.h"

//#define DEBUG(s) //Serial.println(s)
#define LED_STATUS	12
#define LED_ERROR	13
//#define LED_IR	11
//#define IR_RECV 10
//#define IR_SEND 3

#define PIN_DHT11 A6	// 湿度传感器
#define PIN_MQ2 A7		// 烟雾传感器
//#define SWITCH_1 5		// 四个开关
//#define SWITCH_2 6
//#define SWITCH_3 7
//#define SWITCH_4 8             
#define WIFI_RST 4		//WIFI模块复位脚

#define UDP_PORT 8266
#define TCP_PORT 8266



unsigned int delayTime = 1000;       // 数据推送间隔

bool isConnected = 0;
byte id, length;
//byte switch_group[4] = { SWITCH_1, SWITCH_2, SWITCH_3, SWITCH_4 };
//bool switch_status[4] = { false, false, false, false };
String rcvData = "";
String sendData = "";



byte IP_SERVER[4] = { 0, 0, 0, 0 };     // 本地IP地址
String ipServer;

unsigned long time=0;
unsigned int dataLux = 0;
unsigned int dataTemperature = 0;
unsigned int dataHumidity = 0;
unsigned int dataGas = 0;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);//7-5

ESP8266 e;
dht dht11;



void setup()
{
	//Serial.begin(115200);
         lcd.begin(16, 2);

//	pinMode(SWITCH_1, OUTPUT);
//	pinMode(SWITCH_2, OUTPUT);
//	pinMode(SWITCH_3, OUTPUT);
//	pinMode(SWITCH_4, OUTPUT);
	pinMode(PIN_MQ2, INPUT);
	pinMode(LED_ERROR, OUTPUT);
	pinMode(LED_STATUS, OUTPUT);


	digitalWrite(WIFI_RST, LOW);
//	digitalWrite(SWITCH_1, LOW);
//	digitalWrite(SWITCH_2, LOW);
//	digitalWrite(SWITCH_3, LOW);
//	digitalWrite(SWITCH_4, LOW);


	digitalWrite(LED_ERROR, HIGH);      //异常灯亮起，表示服务器未开启

	pinMode(WIFI_RST, OUTPUT);

	SensorInit();		// 初始化传感器（光线传感器）

	//irRecv.enableIRIn(); // Start the receiver

	delay(1000);
	digitalWrite(WIFI_RST, HIGH);

	while (!ServerInit());      // 初始化服务器,如果返回false则一直循环

	digitalWrite(LED_ERROR, LOW);      //配置完毕，错误灯关闭
     
 
       
}
void loop()
{   
     time=time+1;

   if (time%3==1)
   {
        Lcd_1602(); 
       
   } 
   else if (time%3==2)
   {
       Get_Sensor_Data();
       Lcd_1602(); 
   } 
    else if (time%3==0)
   {    
       control(); 
     
   } 

   
      
	if (e.Test())
	{
		digitalWrite(LED_ERROR, LOW);
                   
	}
	else
	{
		digitalWrite(LED_ERROR, HIGH);
		digitalWrite(WIFI_RST, LOW);
		delay(1000);
		digitalWrite(WIFI_RST, HIGH);
		while (!ServerInit());		// 自恢复
	}

   
     
}

void parseIPAddress(String addr)
{
	byte flag = 0;
	flag = addr.indexOf("\"");
	IP_SERVER[0] = addr.substring(flag + 1, flag = addr.indexOf(".", flag + 1)).toInt();
	IP_SERVER[1] = addr.substring(flag + 1, flag = addr.indexOf(".", flag + 1)).toInt();
	IP_SERVER[2] = addr.substring(flag + 1, flag = addr.indexOf(".", flag + 1)).toInt();
	IP_SERVER[3] = addr.substring(flag + 1, flag = addr.lastIndexOf("\"")).toInt();

}

unsigned char switchPort;
unsigned char switchMode;
void control()
{      
      
        rcvData = e.GetIPData(&length);
	if (rcvData != "")
	{       
                
		digitalWrite(LED_STATUS, HIGH);	// 点亮状态灯表示正在处理数据
		// 设备发现指令
		if (rcvData.equalsIgnoreCase("[HI]"))
		{
			//e.SendIPData(ipServer);	// 2015/3/18废除
			e.SendIPData("[HERE]");
		}
		// 请求数据指令
		else if (rcvData.equalsIgnoreCase("[GET]"))
		{
			//Get_Sensor_Data(); 7-9
			String str = "[L:";
			str += String(dataLux);
			str += ",T:";
			str += String(dataTemperature);
			str += ",H:";
			str += String(dataHumidity);
			str += ",G:";
			str += String(dataGas);
			str += ']';

			e.SendIPData(str);
                     
                      
		}
		// 控制开关指令(格式)[SWa:b] a:1-4号开关 b:1开 0关 ?查询状态
//		else if (rcvData.indexOf("SW") > 0)
//		{
//			switchPort = rcvData.charAt(3);	//a
//			switchMode = rcvData.charAt(5);	//b
//			if (switchMode == '?')	// 如果是查询指令
//			{
//				// 替换原接受字符串的?， 改为状态值：1开0关，再发回去……
//				switch_status[switchPort - '1'] ? rcvData.setCharAt(5, '1') : rcvData.setCharAt(5, '0');
//				e.SendIPData(rcvData);
//                                 delay(3000);
//			}
//			else	// 如果是控制指令
//			{
//				if (Switch_Control(switchPort, switchMode))
//                         
//					e.SendIPData("[OK]");
//				else
//					e.SendIPData("[ERR]");
//			}
//		}
//		else if (rcvData.indexOf("C:") > 0)		// Smart Config	[C:"",""]
//		{
//			//Serial.println("Smart Config Mode");
//			String ssid = rcvData.substring(4, rcvData.indexOf("\","));
//			String password = rcvData.substring(rcvData.indexOf(",\"") + 2, rcvData.lastIndexOf("\"]"));
//			//Serial.println(ssid);
//			//Serial.println(password);
//
//			e.SetJoinAP(ssid, password);
//
//			unsigned long time = millis();
//			while (millis() - time < 10000)
//			{
//				if (Serial.find("OK"))
//				{
//					e.SendIPData("[CONNECTED]");
//					break;
//				}
//				else if (millis() - time > 10000)
//				{
//					e.SendIPData("[FAILED]");
//				}
//			}
//		}


	}
	else
		digitalWrite(LED_STATUS, LOW);
}

// 8266初始化配置
bool ServerInit()
{

	if (e.Test())
		if (e.SetIP_UDP(UDP_PORT))
			return true;
		else
			return false;
}
// 传感器初始化设置
void SensorInit()
{
	Sensor_Lux_Init();
        Lcd_1602();
}

void getStatus()
{
	rcvData = e.GetIPData(&id, &length);
	e.GetIPStatus();

      
}

// 读取传感器数据
void Get_Sensor_Data()
{
  unsigned int tmp = 0;
  unsigned int tmp_1 = 0;
  unsigned int data_t = 0;
  unsigned int data_h = 0;
  for(int i = 0; i<20;i++)
      {
	dataLux = Sensor_Lux_Read();		// 光线
	//dht11.Read(PIN_DHT11);
	dht11.read11(PIN_DHT11);
	tmp = (int)dht11.temperature;
       	// 温度
	tmp_1 = (int)dht11.humidity;		// 湿度
        
        dataGas = analogRead(PIN_MQ2);  
        
          data_t = data_t + tmp;
          data_h = data_h + tmp_1;
    
          delay(60);
       
        }
      
          dataTemperature = data_t/20;
          dataHumidity = data_h/20;
      
	
}

//bool Switch_Control(char port, char mode)
//{
//	byte port_num = port - '1';
//	digitalWrite(switch_group[port_num], LOW);
//
//
//	if (mode == '1')
//	{
//		digitalWrite(switch_group[port_num], HIGH);
//		switch_status[port_num] = true;
//	}
//	else if (mode == '0')
//	{
//		digitalWrite(switch_group[port_num], HIGH);
//		switch_status[port_num] = false;
//	}
//	else
//		return false;
//	delay(300);
//	digitalWrite(switch_group[port_num], LOW);
//
//	return true;
//}
 void Lcd_1602()
  {  

  lcd.setCursor(0, 0);
  lcd.print("Tep:");
  lcd.print(dataTemperature, 1);
  //lcd.print((int)dht11.temperature, 1);
  
  lcd.print("C ");

  lcd.print("Lux:");
  lcd.print(dataLux, 1);
   lcd.print("u");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("Hum:");
  lcd.print(dataHumidity, 1);
  
  lcd.print("% ");
  
  lcd.print("Gas:");
  lcd.print(dataGas, 1);
  
  lcd.print("%");
  
     

  }
