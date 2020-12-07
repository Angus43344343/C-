#ifndef _UART_H__
#define _UART_H__

#include "driver.h"

class CUart : public CDriver
{
private:
	HANDLE m_hHnd;
private:
	bool OpenUart();
	void SetCommBufSize(DWORD dwWriteBufSize, DWORD dwReadBufSize);
	void SetCommTimeout(DWORD dwWriteTimeout, DWORD dwReadTimeout, DWORD dwReadSpace);
	BOOL SetCommAttr();
	BOOL SetCommAttr(DCB *pstDcb);
public:
	virtual bool Open();
	virtual int Write(const PCHAR pcSendData, UINT uiDataLen);
	virtual int Read(PCHAR pcRecvBuf, UINT uiBufSize);
	virtual void Close();
public:
	CUart();
	virtual ~CUart();
};

#endif /*_UART_H__*/