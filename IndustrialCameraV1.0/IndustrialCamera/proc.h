#ifndef _PROC_H__
#define _PROC_H__

#include "log.h"
#include "sock.h"
#include "uart.h"
#include "checkSum.h"

class CProc
{
private:
	HANDLE m_hEvent;
	BOOL m_bThreadExit;
	CWinThread *m_threadHnd;
	CRITICAL_SECTION m_stCS;
private:
	CLog *m_pobjLog;
protected:
	HWND m_stHwnd;
	CDriver *m_pobjDrv;
	CCheckSum m_objCheckSum;
protected:
	virtual void SetFrameHeaderTail(PCHAR pcParam, ULONG ulParamLen, EN_FRAME_TYPE enFrameType);
private:
	virtual void HandshakePrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void ReadCMOSPrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void SetCMOSPrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void SoftwarePrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void HardwarePrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void BatchModePrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void NormalModePrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void AlgRecUARTPrm(PCHAR pcParam, ULONG ulParamLen);
	virtual void AlgRecResultPrm(PCHAR pcParam, ULONG ulParamLen);
private:
	virtual PCHAR SetParam(EN_FRAME_TYPE enFrameType);
	virtual void RspProcCtrl(PCHAR pcRecvBuf, ULONG ulBufSize);

	static void ThreadRun(void *pvArg);
	void DoThreadRun();
public:
	void Init();
	void Uninit();

	void CreateDrvObj(EN_DRV_TYPE enDrvType);
	void DestroyDrvObj();

	bool OpenDrvApi();
	void SetDlgHwnd(HWND stHwnd);
	void CmdProcCtrl(EN_FRAME_TYPE enFrameType);
public:
	CProc();
	virtual ~CProc();
};

#endif /*_PROC_H__*/