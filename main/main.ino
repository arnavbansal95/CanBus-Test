#include "SPI.h"
#include "src/CAN_BUS_Shield-master/mcp_can.h"

const int spiCSPin = 10;
bool CAN_Init = false;
MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial Comm Initialised");
    for(int i=1;i<=18;i++)
    {
        if((CAN_OK == CAN.begin(i)) && (CAN_Init == false))
        {
            Serial.print("CAN Initialised at: ");
            Serial.println(i);
            CAN_Init = true;
        }
        delay(100);
    }
    if(!CAN_Init)
    {
        Serial.println("CAN Initialised Failed!");
    }
}

void loop()
{
    if(CAN_Init)
    {
        unsigned char len = 0;
        unsigned char buf[8];
        if (CAN_MSGAVAIL == CAN.checkReceive())     // check if data coming
        {         
            CAN.readMsgBuf(&len, buf);              // read data,  len: data length, buf: data buf

            unsigned long canId = CAN.getCanId();

            Serial.println("-----------------------------");
            Serial.print("Get data from ID: 0x");
            Serial.println(canId, HEX);

            for (int i = 0; i < len; i++)           // print the data 
            { 
                Serial.print(buf[i], HEX);
                Serial.print("\t");
            }
            Serial.println();
        }
    }
}