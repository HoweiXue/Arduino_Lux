#include <Arduino.h>
#include <Wire.h>

#define ADDRESS_L 0x23 // Device address (ADDR=LOW)
#define ADDRESS_H 0x5C // Device address (ADDR=HIGH)
#define POWER_DOWN 0x00
#define POWER_ON 0x01
#define RESET 0x07
#define CONTINUOUSLY_H_RESOLUTION_MODE 0x10
#define CONTINUOUSLY_H_RESOLUTION_MODE2 0x11
#define CONTINUOUSKY_L_RESOLUTION_MODE 0x13
#define ONETIME_H_RESOLUTION_MODE 0x20
#define ONETIME_H_RESOLUTION_MODE2 0x21
#define ONETIME_L_RESOLUTION_MODE 0x23

// 传感器初始化
void Sensor_Lux_Init()
{
	Wire.begin();   //Join as a master
	Wire.beginTransmission(ADDRESS_L);
	Wire.write(POWER_ON);
	Wire.endTransmission();
	Wire.beginTransmission(ADDRESS_L);
	Wire.write(CONTINUOUSLY_H_RESOLUTION_MODE);
	Wire.endTransmission();
}
// 读传感器数据
unsigned int Sensor_Lux_Read()
{
	unsigned int luxData = 0;
	//Wire.beginTransmission(ADDRESS_L);
	Wire.requestFrom(ADDRESS_L, 2);
	while (Wire.available())
	{
		luxData = Wire.read();
		luxData <<= 8;
		luxData |= Wire.read();
	}
	luxData /= 1.2;
	return luxData;
}

