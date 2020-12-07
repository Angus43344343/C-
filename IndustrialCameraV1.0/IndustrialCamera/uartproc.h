#ifndef _UARTPROC_H__
#define _UARTPROC_H__

#include "proc.h"

class CUartProc : public CProc
{
private:
	virtual void AlgRecUARTPrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void AlgRecResultPrm(PCHAR pcParam, ULONG ulParamLen);
public:
	CUartProc();
	virtual ~CUartProc();
};

#endif /*_UARTPROC_H__*/