#ifndef _SOCK_H__
#define _SOCK_H__

#include "driver.h"
#include <winsock2.h>  

#pragma comment(lib,"ws2_32.lib")  

typedef enum
{
	EN_MODE_BLOCK = 0,	/*同步*/
	EN_MODE_NOBLOCK,	/*异步*/
}EN_MODE;

class CSock : public CDriver//客户端
{
private:
	bool InitWSA();
	void UninitWSA();

	SOCKET GetSoket();
	ULONG GetHostIPaddr();
	sockaddr_in GetSockAddr();

	void SetPortMode(ULONG ulPortMode);
#if (_WIN32_WINNT < 0x0600)
	void SetSockAddr(short sFamilyAddr, USHORT usPort, ULONG ulIPaddr); 
#else
	void SetSockAddr(USHORT usFamilyAddr, USHORT usPort, ULONG ulIPaddr);
#endif
private:
	SOCKET CreateSock(int iInternetType, int iCommunicateType, int iPotocol);
	bool ConnectServer(SOCKET sockHnd, sockaddr_in stSockAddr);
	int RecvData(SOCKET sockHnd, PCHAR pcRecvBuf, UINT uiBufSize);
	int SendData(SOCKET sockHnd, const PCHAR pcSendData, UINT uiDataLen);
	void DestroySock(SOCKET sockHnd);
public:
	virtual bool Open();
	virtual int Write(const PCHAR pcSendData, UINT uiDataLen);
	virtual int Read(PCHAR pcRecvBuf, UINT uiBufSize);
	virtual void Close();
public:
	CSock();
	virtual ~CSock();
private:
	SOCKET m_sockHnd;
	sockaddr_in m_sockAddr;
};

#endif /*_SOCK_H__*/