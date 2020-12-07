#include "stdafx.h"
#include "sock.h"
#include "setprminfo.h"

CSock::CSock()
{
	m_sockAddr = {0};
	m_sockHnd = INVALID_SOCKET;
}

CSock::~CSock()
{
}

bool CSock::InitWSA()
{
	WSADATA stWsaData = { 0 };

	WORD dSockVersion = MAKEWORD(2, 2);
	
	return (0 == WSAStartup(dSockVersion, &stWsaData)) ? true : false;
}

void CSock::UninitWSA()
{
	WSACleanup();
}

SOCKET CSock::GetSoket()
{
	return m_sockHnd;
}

sockaddr_in CSock::GetSockAddr()
{
	return m_sockAddr;
}

ULONG CSock::GetHostIPaddr()
{
	in_addr stIPaddr = {0};
	CHAR acHostName[256] = { 0 };
	hostent* pstHostAddr = nullptr;
	
	if (SOCKET_ERROR != gethostname(acHostName, sizeof (acHostName)))
	{
		pstHostAddr = gethostbyname(acHostName);
		if (nullptr != pstHostAddr)
		{
			for (int iNum = 0; nullptr != pstHostAddr->h_addr_list[iNum]; iNum++)
			{
				memcpy(&stIPaddr.S_un.S_addr, pstHostAddr->h_addr_list[iNum], pstHostAddr->h_length);
			}
			printf("本机IP地址：%s \n", inet_ntoa(stIPaddr));
			return stIPaddr.S_un.S_addr;
		}
	}

	return 0;
}

void CSock::SetPortMode(ULONG ulPortMode)
{
	ioctlsocket(m_sockHnd, FIONBIO, (unsigned long*)&ulPortMode); 
	printf("通信模式: %d \n", ulPortMode);
}

#if (_WIN32_WINNT < 0x0600)
void CSock::SetSockAddr(short sFamilyAddr, USHORT usPort, ULONG ulIPaddr)
{
	memset(&m_stSockAddr, 0, sizeof (m_stSockAddr));
	m_stSockAddr.sin_family = sFamilyAddr;
	m_stSockAddr.sin_port = htons(usPort);
	m_stSockAddr.sin_addr.S_un.S_addr = ulIPaddr;
}
#else
void CSock::SetSockAddr(USHORT usFamilyAddr, USHORT usPort, ULONG ulIPaddr)
{
	memset(&m_sockAddr, 0, sizeof (m_sockAddr));
	m_sockAddr.sin_family = usFamilyAddr;
	m_sockAddr.sin_port = htons(usPort);
	m_sockAddr.sin_addr.S_un.S_addr = ulIPaddr;
}
#endif

SOCKET CSock::CreateSock(int iInternetType, int iCommunicateType, int iPotocol)
{
	SOCKET sockHnd = socket(iInternetType, iCommunicateType, iPotocol);
	if (INVALID_SOCKET != sockHnd)
	{
		m_sockHnd = sockHnd;
		return sockHnd;
	}

	return INVALID_SOCKET;
}

bool CSock::ConnectServer(SOCKET sockHnd, sockaddr_in stSockAddr)
{
	return (SOCKET_ERROR == connect(sockHnd, (sockaddr *)&stSockAddr, sizeof (stSockAddr))) ? false : true;
}

int CSock::RecvData(SOCKET sockHnd, PCHAR pcRecvBuf, UINT uiBufSize)
{
	int iRecvLen = recv(sockHnd, pcRecvBuf, uiBufSize, 0);
	return  (0 < iRecvLen) ? iRecvLen : -1;
}

int CSock::SendData(SOCKET sockHnd, const PCHAR pcSendData, UINT uiDataLen)
{
	int iSendLen = send(sockHnd, pcSendData, uiDataLen, 0);
	return (0 < iSendLen) ? iSendLen : -1;
}

void CSock::DestroySock(SOCKET sockHnd)
{
	if (INVALID_SOCKET != sockHnd)
	{
		closesocket(sockHnd);
	}
}

bool CSock::Open()
{
	SOCKET sockHnd = 0;
	ULONG ulHostIPaddr = 0;
	sockaddr_in stSockAddr = { 0 };
	UCHAR aucIPaddrBuf[255] = { 0 };
	printf("设备SOCK开启流程：=======================================================\n");
	if (InitWSA())
	{
		printf("WSA初始化成功\n");
		sockHnd = CreateSock(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET != sockHnd)
		{
			printf("创建SOCK成功\n");
			ulHostIPaddr = GetHostIPaddr();//获取本机IP地址
			if (0 != ulHostIPaddr)
			{
				CString strParam;
				READ_INI_FILE(EN_MOD_SOCK, IDC_RADIO_BLOCK, strParam);
				SetPortMode((_T("true") == strParam) ? EN_MODE_BLOCK : EN_MODE_NOBLOCK);/*模式：同步或异步*/

				strParam.Empty();
				READ_INI_FILE(EN_MOD_SOCK, IDC_EDIT_PORT, strParam);
				SetSockAddr(AF_INET, _ttoi(strParam), inet_addr("192.168.12.122"));/*sock attr*/

				if (ConnectServer(sockHnd, GetSockAddr()))
				{
					printf("成功连接服务器\n");
					return true;
				}
				else
				{
					printf("连接失败-----------------------\n");
				}
			}
			Close();//关闭句柄
		}
		else
		{
			printf("创建SOCK失败-----------------------\n");
		}
	}
	else
	{
		printf("WSA初始化失败-----------------------\n");
	}

	return false;
}

int CSock::Write(const PCHAR pcSendData, UINT uiDataLen)
{
	SOCKET sockHnd = GetSoket();
	if (INVALID_SOCKET != sockHnd)
	{
		return SendData(sockHnd, pcSendData, uiDataLen);
	}

	return SEND_RECV_ERROR;
}

int CSock::Read(PCHAR pcRecvBuff, UINT uiBuffLength)
{
	SOCKET sockHnd = GetSoket();
	if (INVALID_SOCKET != sockHnd)
	{
		return RecvData(sockHnd, pcRecvBuff, uiBuffLength);
	}

	return SEND_RECV_ERROR;
}

void CSock::Close()
{
	DestroySock(GetSoket());
	UninitWSA();
}

