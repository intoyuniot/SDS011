/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 时间:  03-30-16
************************************************************************
功能描述：
颗粒物浓度检测仪：检测2.5um和1.0um颗粒物浓度

所需器件:
1. Atom
2. SDS011 PM2.5PM10模块

连接说明：
SDS011                       Atom
1.VCC                        +5.0V
2.GND                        GND
3.RX                         A3(TX)
4.TX                         A2(RX)
测量范围：0-999ug/m3
*/

#include <SDS011.h>

//PM2.5PM10
SDS011 sds011_0;

void setup()
{
    //初始化
    Serial.begin(115200);
    sds011_0.begin();
    delay(1000);
}

void loop()
{
    Serial.print("PM2.5:"); // 串口输出PM2.5浓度数据
    Serial.print(sds011_0.getPM25()); // 串口输出PM2.5浓度数据
    Serial.print("PM1.0:"); // 串口输出PM2.5浓度数据
    Serial.print(sds011_0.getPM10()); // 串口输出PM2.5浓度数据
    delay(2000);
}
