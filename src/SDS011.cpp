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

#include "SDS011.h"

SDS011::SDS011()
{
    Pm25_ = 0;
    Pm10_ = 0;
}

void SDS011::begin()
{
    serial_ = &Serial;
    serial_->begin(9600);
}

//With Parameter
void SDS011::begin(USARTSerial* serial_pt)
{
    serial_ = serial_pt;
    serial_->begin(9600);
}

//return the value of pm2.5
int SDS011::getPM25()
{
    getSerialData();
    return Pm25_;
}

//return the value of pm1.0
int SDS011::getPM10()
{
    getSerialData();
    return Pm10_;
}

//// Packet format: AA C0 PM25_Low PM25_High PM10_Low PM10_High 0 0 CRC AB
void SDS011::getSerialData()
{
    uint8_t mData = 0;
    uint8_t i = 0;
    uint8_t mPkt[10] = {0};
    uint8_t mCheck = 0;
    while (serial_->available() > 0)
    {
        mData = serial_->read();
        delay(2);//wait until packet is received
        if(mData == 0xAA)//head1 ok
        {
            mPkt[0] =  mData;
            mData = serial_->read();
            if(mData == 0xc0)//head2 ok
            {
                mPkt[1] =  mData;
                mCheck = 0;
                for(i=0;i < 6;i++)//data recv and crc calc
                {
                    mPkt[i+2] = serial_->read();
                    delay(2);
                    mCheck += mPkt[i+2];
                }
                mPkt[8] = serial_->read();
                delay(1);
                mPkt[9] = serial_->read();
                if(mCheck == mPkt[8])//crc ok
                {
                    serial_->flush();

                    Pm25_ = (uint16_t)mPkt[2] | (uint16_t)(mPkt[3]<<8);
                    Pm10_ = (uint16_t)mPkt[4] | (uint16_t)(mPkt[5]<<8);
                    Pm25_ /=10;
                    Pm10_ /=10;
                    if(Pm25_ > 999)
                        Pm25_ = 999;
                    if(Pm10_ > 999)
                        Pm10_ = 999;
                    return;
                }
            }
        }
    }
}
