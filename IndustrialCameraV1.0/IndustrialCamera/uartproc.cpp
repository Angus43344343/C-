#include "stdafx.h"
#include "uartproc.h"

CUartProc::CUartProc()
{
}

CUartProc::~CUartProc()
{
}

void CUartProc::AlgRecUARTPrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_ALG_RECUART pstCmd = (PST_CMD_ALG_RECUART)pcParam;
	/*1.��������λ*/

	/*2.����֡ͷ֡β*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_ALG_RECUART);
}

void CUartProc::AlgRecResultPrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_ALG_RECRESULT pstCmd = (PST_CMD_ALG_RECRESULT)pcParam;
	/*1.��������λ*/

	/*2.����֡ͷ֡β*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_ALG_RECRESULT);
}