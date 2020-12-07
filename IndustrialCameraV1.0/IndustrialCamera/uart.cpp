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
	printf("��UART����: %s \n", strUartName);

	m_hHnd = CreateFile(strUartName,					/*�˿ں�*/
						GENERIC_READ | GENERIC_WRITE,	/*������ʽ*/
						0,								/*��ռ*/ 
						NULL,							//
						OPEN_EXISTING,					/*ֻ���Ѵ���*/ 
						0,								/*ͬ��*/
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
	cTimeout.ReadIntervalTimeout = dwReadSpace;			/*�������ʱ�������ַ���*/
	cTimeout.ReadTotalTimeoutMultiplier = 0;			/*��ʱ��ϵ��*/
	cTimeout.ReadTotalTimeoutConstant = dwReadTimeout;	/*��ʱ�䳣��*/
	/*set write timeout*/
	cTimeout.WriteTotalTimeoutMultiplier = 0;			/*дʱ��ϵ��*/
	cTimeout.WriteTotalTimeoutConstant = dwWriteTimeout;/*дʱ�䳣��*/
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
	printf("������: %d\n", _ttoi(strBaud));
	READ_INI_FILE(EN_MOD_UART, IDC_EDIT_BYTE, strByte);
	stDcb.ByteSize = _ttoi(strByte);
	printf("����λ: %d\n", _ttoi(strBaud));
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
	printf("�豸UART�������̣�=======================================================\n");
	if (OpenUart())//��ȡ�������
	{
		printf("��UART�ɹ�\n");
		SetCommBufSize(WRITE_BUF_SIZE, READ_BUF_SIZE);/*����ͨ��buffer*/
		SetCommTimeout(WRITE_TIMEOUT, READ_TIMEOUT, READ_TIMESPACE);/*����ͨ�ų�ʱ*/
		if (TRUE == SetCommAttr())/*���ô��ڻ�������*/
		{
			printf("���ò����ɹ�\n");
			PurgeComm(m_hHnd, PURGE_TXCLEAR | PURGE_RXCLEAR);/*�����дbuffer*/
			return true;
		}
		else
		{
			printf("���ò���ʧ��-----------------------\n");
		}
		CloseHandle(m_hHnd);
	}
	else
	{
		printf("��UARTʧ��-----------------------\n");
	}
	return false;
}

int CUart::Write(const PCHAR pcSendData, UINT uiDataLen)/*����Э�鶨�ƣ�cmd---rsp�������Ӧ*/
{
	DWORD dwWriteLen = 0;
	DWORD dwErrorFlags = 0;
	COMSTAT stComStat = { 0 };

	/*ˢ�²���ջ�����*/
	ClearCommError(m_hHnd, &dwErrorFlags, &stComStat);/*���������ȡ������Ϣ*/
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

	