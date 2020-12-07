#include "stdafx.h"
#include "checkSum.h"

CCheckSum::CCheckSum()
{
}

CCheckSum::~CCheckSum()
{
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*函  数：GetChkSum
*-*-*-*功  能：获取校验和
*-*-*-*参  数：pucData      *-*-*-*   要进行计算的数据
*-*-*-*       ulDataSize   *-*-*-*   数据长度 
*-*-*-*返回值：返回校验和
*-*-*-*备  注：对数据进行单字节累加，再将累加和 & 0x7f
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
unsigned char CCheckSum::GetChkSum(unsigned char *pucData, unsigned long ulDataSize)
{
    unsigned char ucChkSum = 0;
    for (unsigned int uiCount = 0; uiCount < ulDataSize; uiCount++)
    {
        ucChkSum += pucData[uiCount];
    }
    
    ucChkSum &= CAL_CHKSUM;//calculate base on rule

    return ucChkSum;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*函  数：CompChkSum
*-*-*-*功  能：比较校验和
*-*-*-*参  数：pucData      *-*-*-*   要进行计算的数据
*-*-*-*       ulDataSize   *-*-*-*   数据长度 
*-*-*-*       ucChkSum     *-*-*-*   要比较的校验和  
*-*-*-*返回值: true   *-*-*-*   两个校验和值相同
*-*-*-*		  false  *-*-*-*   两个校验和值不同
*-*-*-*备  注：比较计算后的校验和和数据帧的校验和，从而判断传输的数据是否正常
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
bool CCheckSum::CompChkSum(unsigned char *pucData, unsigned long ulDataSize, unsigned char ucChkSum)
{
    return (ucChkSum == GetChkSum(pucData, ulDataSize));
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*函  数：GetChkCRC
*-*-*-*功  能：获取CRC
*-*-*-*参  数：pucData      *-*-*-*   要进行计算的数据
*-*-*-*       ulDataSize   *-*-*-*   数据长度 
*-*-*-*返回值：返回CRC
*-*-*-*备  注：进行CRC16运算
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
unsigned short CCheckSum::GetChkCRC(unsigned char *pucData, unsigned long ulDataSize)
{
    unsigned char  ucTemp = 0;
    unsigned short usCrc = DEF_CRC_INIT_VALUE;

    for (unsigned int uiCount = 0; uiCount < ulDataSize; uiCount++)
    {
        ucTemp = *pucData++;
        usCrc = CalCRC(usCrc,(unsigned short)ucTemp);
    }

    return usCrc;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*函  数：CompChkCRC
*-*-*-*功  能：比较CRC
*-*-*-*参  数：pucData      *-*-*-*   要进行计算的数据
*-*-*-*       ulDataSize   *-*-*-*   数据长度
*-*-*-*       usChkCRC     *-*-*-*   要比较的CRC值
*-*-*-*返回值：true  *-*-*-*  两个CRC值相同
*-*-*-*       false *-*-*-*  两个CRC值不同
*-*-*-*备  注：比较计算后的CRC和数据帧的CRC，从而判断传输的数据是否正常
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
bool CCheckSum::CompChkCRC(unsigned char *pucData, unsigned long ulDataSize, unsigned short usChkCRC)
{
    return (usChkCRC == GetChkCRC(pucData, ulDataSize));
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*函  数：CalCRC
*-*-*-*功  能：计算CRC
*-*-*-*参  数：usDstCrc   *-*-*-*   要获取的CRC
*-*-*-*       usCalCrc   *-*-*-*   要计算的CRC 
*-*-*-*返回值：返回CRC
*-*-*-*备  注：无
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
unsigned short CCheckSum::CalCRC(unsigned short usDstCrc, unsigned short usCalCrc)
{
    usCalCrc <<= 8;

    for (int iCount = 8; iCount > 0; iCount--)
    {
        if ((usCalCrc ^ usDstCrc ) & 0x8000)
        {
            usDstCrc = (usDstCrc << 1) ^ DEF_CRC_POLINOMIAL;	   
        }
        else
        {
            usDstCrc <<= 1;
        }

        usCalCrc <<= 1;
    }

    return usDstCrc;
}
