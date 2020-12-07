#include "stdafx.h"
#include "uart.h"
#include "setprminfo.h"

#define WRITE_BUF_SIZE	(4096)
#define READ_BUF_SIZE	(4096)
#define WRITE_TIMEOUT	(2000)/*ms*/
#define READ_TIMEOUT	(1000)/*ms*/
#define READ_TIMESPACE	(500) /*ms*/


CUart::CUart()
{
	m_hHnd = nullptr;
}

CUart::~CUart()
{
}

bool CUart::OpenUart()
{
	CString strUartName;
	READ_INI_FILE(EN_MOD_UART, IDC_COMBO_DRVNAME, strUartName);
	printf("打开UART名称: %s \n", strUartName);

	m_hHnd = CreateFile(strUartName,					/*端口号*/
						GENERIC_READ | GENERIC_WRITE,	/*操作方式*/
						0,								/*独占*/ 
						NULL,							//
						OPEN_EXISTING,					/*只打开已存在*/ 
						0,								/*同步*/
						NULL);

	return (INVALID_HANDLE_VALUE == m_hHnd) ? false : true;
}

void CUart::SetCommBufSize(DWORD dwWriteBufSize, DWORD dwReadBufSize)
{
	SetupComm(m_hHnd, dwReadBufSize, dwWriteBufSize);
}

void CUart::SetCommTimeout(DWORD dwWriteTimeout, DWORD dwReadTimeout, DWORD dwReadSpace)
{
	COMMTIMEOUTS cTimeout;
	/*set read timeout*/
	cTimeout.ReadIntervalTimeout = dwReadSpace;			/*读间隔超时，两个字符间*/
	cTimeout.ReadTotalTimeoutMultiplier = 0;			/*读时间系数*/
	cTimeout.ReadTotalTimeoutConstant = dwReadTimeout;	/*读时间常量*/
	/*set write timeout*/
	cTimeout.WriteTotalTimeoutMultiplier = 0;			/*写时间系数*/
	cTimeout.WriteTotalTimeoutConstant = dwWriteTimeout;/*写时间常量*/
	SetCommTimeouts(m_hHnd, &cTimeout);
}

BOOL CUart::SetCommAttr()
{
	DCB stDcb;
	CString strBaud;
	CString strByte;
	CString strParity;
	CString strStopBits;
	
	GetCommState(m_hHnd, &stDcb);/*Get attibute*/
	READ_INI_FILE(EN_MOD_UART, IDC_COMBO_BAUD, strBaud);
	stDcb.BaudRate = _ttoi(strBaud);
	printf("波特率: %d\n", _ttoi(strBaud));
	READ_INI_FILE(EN_MOD_UART, IDC_EDIT_BYTE, strByte);
	stDcb.ByteSize = _ttoi(strByte);
	printf("数据位: %d\n", _ttoi(strBaud));
	READ_INI_FILE(EN_MOD_UART, IDC_RADIO_NO, strParity);
	if (_T("true") == strParity)
	{
		stDcb.Parity = NOPARITY;
	}
	else
	{
		strParity.Empty();
		READ_INI_FILE(EN_MOD_UART, IDC_RADIO_ODD, strParity);
		stDcb.Parity = (_T("true") == strParity) ? ODDPARITY : EVENPARITY;
	}
	READ_INI_FILE(EN_MOD_UART, IDC_RADIO_ONEBIT, strStopBits);
	if (_T("true") == strStopBits)
	{
		stDcb.StopBits = ONESTOPBIT;
	}
	else
	{
		strStopBits.Empty();
		READ_INI_FILE(EN_MOD_UART, IDC_RADIO_ONE5BITS, strStopBits);
		stDcb.StopBits = (_T("true") == strStopBits) ? ONE5STOPBITS : TWOSTOPBITS;
	}

	return SetCommState(m_hHnd, &stDcb);/*set attribute*/
}

BOOL CUart::SetCommAttr(DCB *pstDcb)
{
	return SetCommState(m_hHnd, pstDcb);
}

bool CUart::Open()
{
	printf("设备UART开启流程：=======================================================\n");
	if (OpenUart())//获取驱动句柄
	{
		printf("打开UART成功\n");
		SetCommBufSize(WRITE_BUF_SIZE, READ_BUF_SIZE);/*设置通信buffer*/
		SetCommTimeout(WRITE_TIMEOUT, READ_TIMEOUT, READ_TIMESPACE);/*设置通信超时*/
		if (TRUE == SetCommAttr())/*设置串口基本属性*/
		{
			printf("设置参数成功\n");
			PurgeComm(m_hHnd, PURGE_TXCLEAR | PURGE_RXCLEAR);/*清除读写buffer*/
			return true;
		}
		else
		{
			printf("设置参数失败-----------------------\n");
		}
		CloseHandle(m_hHnd);
	}
	else
	{
		printf("打开UART失败-----------------------\n");
	}
	return false;
}

int CUart::Write(const PCHAR pcSendData, UINT uiDataLen)/*根据协议定制，cmd---rsp，有求必应*/
{
	DWORD dwWriteLen = 0;
	DWORD dwErrorFlags = 0;
	COMSTAT stComStat = { 0 };

	/*刷新并清空缓冲区*/
	ClearCommError(m_hHnd, &dwErrorFlags, &stComStat);/*根据需求获取错误信息*/
	PurgeComm(m_hHnd, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	if (TRUE == WriteFile(m_hHnd, pcSendData, uiDataLen, &dwWriteLen, NULL))
	{
		return (int)dwWriteLen;
	}

	return SEND_RECV_ERROR;
}

int CUart::Read(PCHAR pcRecvBuf, UINT uiBufSize)
{
	DWORD dwReadLen = 0;
	if (TRUE == ReadFile(m_hHnd, pcRecvBuf, uiBufSize, &dwReadLen, NULL))
	{
		return (int)dwReadLen;
	}

	return SEND_RECV_ERROR;
}

void CUart::Close()
{
	if (nullptr != m_hHnd)
	{
		CloseHandle(m_hHnd);
	}
}

	