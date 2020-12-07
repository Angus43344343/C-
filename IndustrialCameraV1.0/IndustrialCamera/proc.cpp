#include "stdafx.h"
#include "proc.h"
#include "setprminfo.h"

CLog::CReleaseInstance CLog::ms_RealseInstance;
CLog *CLog::ms_pInstanceLog = new CLog; 
CProc::CProc()
{
	m_stCS = { 0 };
	m_hEvent = nullptr;
	m_pobjLog = nullptr;
	m_pobjDrv = nullptr;
	m_bThreadExit = FALSE;
	m_threadHnd = nullptr;
}

CProc:: ~CProc()
{
}

void CProc::SetFrameHeaderTail(PCHAR pcParam, ULONG ulParamLen, EN_FRAME_TYPE enFrameType)
{
	PST_FRAME_HEADER pstHeader = (PST_FRAME_HEADER)pcParam;
	PST_FRAME_TAIL pstTail = (PST_FRAME_TAIL)(pcParam + ulParamLen - sizeof (ST_FRAME_TAIL));

	pstHeader->ucFrameHeader = EN_FRAME_HEADER;
	pstHeader->usFrameType = enFrameType;

	pstTail->ucCheckSum = m_objCheckSum.GetChkSum((PUCHAR)(pcParam + 1), ulParamLen - sizeof (ST_FRAME_TAIL)- 1);/*帧类型+数据位*/
	pstTail->ucFrameTail = EN_FRAME_TAIL;
}

void CProc::HandshakePrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_HANDSHAKE pstCmd = (PST_CMD_HANDSHAKE)pcParam;
	/*1.设置数据位*/

	/*2.设置帧头帧尾*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_HANDSHAKE);
}

void CProc::ReadCMOSPrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_READCMOS pstCmd = (PST_CMD_READCMOS)pcParam;
	/*1.设置数据位*/

	/*2.设置帧头帧尾*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_READCMOS);
}

void CProc::SetCMOSPrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_SETCMOS pstCmd = (PST_CMD_SETCMOS)pcParam;
	/*1.设置数据位*/

	/*2.设置帧头帧尾*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_SETCMOS);
}

void CProc::SoftwarePrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_GETDATA_SOFTWARE pstCmd = (PST_CMD_GETDATA_SOFTWARE)pcParam;
	/*1.设置数据位*/
	CString strCmd;
	READ_INI_FILE(EN_MOD_COLLECT, IDC_EDIT_COLLECT_NUM, strCmd);
	pstCmd->uiNumber = _ttoi(strCmd);

	strCmd.Empty();
	READ_INI_FILE(EN_MOD_COLLECT, IDC_EDIT_COLLECT_SPACE, strCmd);
	pstCmd->uiSpace = _ttoi(strCmd);
	/*2.设置帧头帧尾*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_GETDATA_SOFTWARE);
}

void CProc::HardwarePrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_GETDATA_HARDWARE pstCmd = (PST_CMD_GETDATA_HARDWARE)pcParam;
	/*1.设置数据位*/

	/*2.设置帧头帧尾*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_GETDATA_HARDWARE);
}

void CProc::BatchModePrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_MODE_BATCH pstCmd = (PST_CMD_MODE_BATCH)pcParam;
	/*1.设置数据位*/

	/*2.设置帧头帧尾*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_MODE_BATCH);
}

void CProc::NormalModePrm(PCHAR pcParam, ULONG ulParamLen)
{
	PST_CMD_MODE_NORMAL pstCmd = (PST_CMD_MODE_NORMAL)pcParam;
	/*1.设置数据位*/

	/*2.设置帧头帧尾*/
	SetFrameHeaderTail(pcParam, ulParamLen, EN_TYPE_MODE_NORMAL);
}

void CProc::AlgRecUARTPrm(PCHAR pcParam, ULONG ulParamLen)
{
}

void CProc::AlgRecResultPrm(PCHAR pcParam, ULONG ulParamLen)
{
}

PCHAR CProc::SetParam(EN_FRAME_TYPE enFrameType)
{
	PCHAR pcParam = new CHAR[FRAME_TOTAL_LEN];
	memset(pcParam, 0, FRAME_TOTAL_LEN);

	switch (enFrameType)
	{
	case EN_TYPE_HANDSHAKE: HandshakePrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_READCMOS: ReadCMOSPrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_SETCMOS: SetCMOSPrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_GETDATA_SOFTWARE: SoftwarePrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_GETDATA_HARDWARE: HardwarePrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_MODE_BATCH: BatchModePrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_MODE_NORMAL: NormalModePrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_ALG_RECUART: AlgRecUARTPrm(pcParam, FRAME_TOTAL_LEN); break;
	case EN_TYPE_ALG_RECRESULT: AlgRecResultPrm(pcParam, FRAME_TOTAL_LEN); break;
	default: break;
	}

	return pcParam;
}

void CProc::RspProcCtrl(PCHAR pcRecvBuf, ULONG ulBufSize)
{
	::SendMessage(m_stHwnd, WM_RECV_DATA, ulBufSize, (LPARAM)pcRecvBuf);
}

void CProc::ThreadRun(void *pvArg)
{
	CProc *pobjProcess = (CProc*)pvArg;
	pobjProcess->DoThreadRun();
}

void CProc::DoThreadRun()
{
	int iRecvLen = SEND_RECV_ERROR;
	CHAR ucRecvBuf[RECV_BUF_SIZE] = { 0 };

	while (1)
	{
		if (TRUE == m_bThreadExit)
		{
			SetEvent(m_hEvent);
			break;
		}

		EnterCriticalSection(&m_stCS);

		iRecvLen = m_pobjDrv->Read(ucRecvBuf, sizeof (ucRecvBuf));
		if (0 < iRecvLen)
		{
			m_pobjLog->SaveLog(ucRecvBuf, iRecvLen);
			RspProcCtrl(ucRecvBuf, iRecvLen);
		}

		LeaveCriticalSection(&m_stCS);
		
		Sleep(1);
	}
}

void CProc::Init()
{
	m_pobjLog = CLog::GetInstance();
	InitializeCriticalSection(&m_stCS);//线程锁
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_threadHnd = AfxBeginThread((AFX_THREADPROC)ThreadRun, this);
}

void CProc::Uninit()
{
	m_pobjDrv->Close();
	m_bThreadExit = TRUE;
	WaitForSingleObject(m_hEvent, INFINITE);
	DeleteCriticalSection(&m_stCS);
}

void CProc::CreateDrvObj(EN_DRV_TYPE enDrvType)
{
	if (EN_DRV_UART == enDrvType)
	{
		m_pobjDrv = new CUart();
	}
	else if (EN_DRV_SOCK == enDrvType)
	{
		m_pobjDrv = new CSock();
	}
}

void CProc::DestroyDrvObj()
{
	FREE_MALLOC(m_pobjDrv);
}

bool CProc::OpenDrvApi()
{
	return m_pobjDrv->Open();
}

void CProc::SetDlgHwnd(HWND stHwnd)
{
	m_stHwnd = stHwnd;
}

void CProc::CmdProcCtrl(EN_FRAME_TYPE enFrameType)
{
	PCHAR pcSendData = SetParam(enFrameType);
	PST_FRAME_HEADER pstHeader = (PST_FRAME_HEADER)pcSendData;
	PST_FRAME_TAIL pstTail = (PST_FRAME_TAIL)(pcSendData + FRAME_TOTAL_LEN - sizeof (ST_FRAME_TAIL));

	if ((nullptr != pcSendData) && (EN_FRAME_HEADER == pstHeader->ucFrameHeader) && 
		(EN_FRAME_TAIL == pstTail->ucFrameTail))/*这里简单地进行参数检测*/
	{
		m_pobjLog->SaveLog(pcSendData, FRAME_TOTAL_LEN);
		if (0 < m_pobjDrv->Write(pcSendData, FRAME_TOTAL_LEN))
		{
			::SendMessage(m_stHwnd, WM_SEND_DATA, FRAME_TOTAL_LEN, (LPARAM)pcSendData);
		}
		else
		{
			::SendMessage(m_stHwnd, WM_SEND_DATA, 0, NULL);
		}
	}

	FREE_MALLOC(pcSendData);
}

