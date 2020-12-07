#include "stdafx.h"
#include "checkSum.h"

CCheckSum::CCheckSum()
{
}

CCheckSum::~CCheckSum()
{
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*��  ����GetChkSum
*-*-*-*��  �ܣ���ȡУ���
*-*-*-*��  ����pucData      *-*-*-*   Ҫ���м��������
*-*-*-*       ulDataSize   *-*-*-*   ���ݳ��� 
*-*-*-*����ֵ������У���
*-*-*-*��  ע�������ݽ��е��ֽ��ۼӣ��ٽ��ۼӺ� & 0x7f
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
*-*-*-*��  ����CompChkSum
*-*-*-*��  �ܣ��Ƚ�У���
*-*-*-*��  ����pucData      *-*-*-*   Ҫ���м��������
*-*-*-*       ulDataSize   *-*-*-*   ���ݳ��� 
*-*-*-*       ucChkSum     *-*-*-*   Ҫ�Ƚϵ�У���  
*-*-*-*����ֵ: true   *-*-*-*   ����У���ֵ��ͬ
*-*-*-*		  false  *-*-*-*   ����У���ֵ��ͬ
*-*-*-*��  ע���Ƚϼ�����У��ͺ�����֡��У��ͣ��Ӷ��жϴ���������Ƿ�����
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
bool CCheckSum::CompChkSum(unsigned char *pucData, unsigned long ulDataSize, unsigned char ucChkSum)
{
    return (ucChkSum == GetChkSum(pucData, ulDataSize));
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*��  ����GetChkCRC
*-*-*-*��  �ܣ���ȡCRC
*-*-*-*��  ����pucData      *-*-*-*   Ҫ���м��������
*-*-*-*       ulDataSize   *-*-*-*   ���ݳ��� 
*-*-*-*����ֵ������CRC
*-*-*-*��  ע������CRC16����
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
*-*-*-*��  ����CompChkCRC
*-*-*-*��  �ܣ��Ƚ�CRC
*-*-*-*��  ����pucData      *-*-*-*   Ҫ���м��������
*-*-*-*       ulDataSize   *-*-*-*   ���ݳ���
*-*-*-*       usChkCRC     *-*-*-*   Ҫ�Ƚϵ�CRCֵ
*-*-*-*����ֵ��true  *-*-*-*  ����CRCֵ��ͬ
*-*-*-*       false *-*-*-*  ����CRCֵ��ͬ
*-*-*-*��  ע���Ƚϼ�����CRC������֡��CRC���Ӷ��жϴ���������Ƿ�����
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
bool CCheckSum::CompChkCRC(unsigned char *pucData, unsigned long ulDataSize, unsigned short usChkCRC)
{
    return (usChkCRC == GetChkCRC(pucData, ulDataSize));
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*-*-*-*��  ����CalCRC
*-*-*-*��  �ܣ�����CRC
*-*-*-*��  ����usDstCrc   *-*-*-*   Ҫ��ȡ��CRC
*-*-*-*       usCalCrc   *-*-*-*   Ҫ�����CRC 
*-*-*-*����ֵ������CRC
*-*-*-*��  ע����
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
