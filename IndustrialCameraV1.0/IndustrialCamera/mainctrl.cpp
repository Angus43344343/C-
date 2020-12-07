#include "stdafx.h"
#include "mainctrl.h"

CMainCtrl::CMainCtrl()
{
	Init();
}

CMainCtrl::~CMainCtrl()
{
	Uninit();
}

void CMainCtrl::InitProc(EN_DRV_TYPE enDrvType)
{
	if (EN_DRV_UART == enDrvType)
	{
		m_apobjProc[enDrvType] = new CUartProc();
	}
	else if (EN_DRV_SOCK == enDrvType)
	{
		m_apobjProc[enDrvType] = new CSockProc();
	}

	if (nullptr != m_apobjProc[enDrvType])
	{
		m_apobjProc[enDrvType]->CreateDrvObj(enDrvType);
		m_apobjProc[enDrvType]->Init();
	}
}

void CMainCtrl::UninitProc(EN_DRV_TYPE enDrvType)
{
	if (nullptr != m_apobjProc[enDrvType])
	{
		m_apobjProc[enDrvType]->Uninit();
		m_apobjProc[enDrvType]->DestroyDrvObj();

		FREE_MALLOC(m_apobjProc[enDrvType]);
	}	
}

void CMainCtrl::Init()
{
	InitProc(EN_DRV_UART);
	InitProc(EN_DRV_SOCK);
}

void CMainCtrl::Uninit()
{
	UninitProc(EN_DRV_UART);
	UninitProc(EN_DRV_SOCK);
}

void CMainCtrl::SetDlgHwnd(EN_DRV_TYPE enDrvType, HWND stHwnd)
{
	if (nullptr != m_apobjProc[enDrvType])
	{
		m_apobjProc[enDrvType]->SetDlgHwnd(stHwnd);
	}
}

bool CMainCtrl::OpenDrvCtrl(EN_DRV_TYPE enDrvType)
{
	if (nullptr != m_apobjProc[enDrvType])
	{
		return m_apobjProc[enDrvType]->OpenDrvApi();
	}

	return false;
}
	
void CMainCtrl::SendDrvCtrl(EN_DRV_TYPE enDrvType, EN_FRAME_TYPE enFrameType)
{
	if (nullptr != m_apobjProc[enDrvType])
	{
		m_apobjProc[enDrvType]->CmdProcCtrl(enFrameType);
	}
}