/*
 ******************************************************************************

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, see <http://www.gnu.org/licenses/>.

 This library is SDS011 Particulate Matter sensor module

Author: CHY @ IntoRobot Team @ May 6 2016

 ******************************************************************************
 */

#ifndef SDS011_H
#define SDS011_H

#include "Arduino.h"

class SDS011
{
    public:
        SDS011();
        // 初始化串口
        void begin();
        void begin(USARTSerial* serial_pt);

        void getSerialData();  //从串口读取并处理数据
        int getPM25();         // 获取2.5um粉尘的数据, 单位为ug/m3
        int getPM10();         // 获取1.0um粉尘的数据, 单位为ug/m3

    private:
        int Pm25_;
        int Pm10_;
        USARTSerial* serial_;    //connect to IntoRobot-Atom Serial or Serial1
};

#endif
