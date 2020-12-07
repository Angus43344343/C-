#ifndef _DRIVER_H__
#define _DRIVER_H__

#include "common.h"

class CDriver
{
public:
	virtual bool Open() = 0;
	virtual int Write(const PCHAR pcSendData, UINT uiDataLen) = 0;
	virtual int Read(PCHAR pcRecvBuf, UINT uiBufSize) = 0;
	virtual void Close() = 0;
public:
	CDriver() {};
	virtual ~CDriver() {};
};

#endif /*_DRIVER_H__*/