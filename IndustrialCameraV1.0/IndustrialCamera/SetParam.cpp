// SetParam.cpp : 实现文件
#include "stdafx.h"
#include "IndustrialCamera.h"
#include "SetParam.h"
#include "afxdialogex.h"
#include "io.h"
/*==================UI控件信息============================*/
#define UART_MAX_STOPBIT	(8)
const CString g_astrBaud[] = { _T("2400"), _T("4800"), _T("9600"), _T("19200"), _T("38400"), _T("57600"), _T("115200") };
const CString g_astrDrvName[] = { _T("COM1"), _T("COM2"), _T("COM3"), _T("COM4"), _T("COM5"), _T("COM6"), _T("COM7"), _T("COM8") };
/*==================UI控件信息============================*/
// CSetParam 对话框
IMPLEMENT_DYNAMIC(CSetParam, CDialogEx)
CSetParam::CSetParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetParam::IDD, pParent)
{
	m_uiPreParity = IDC_RADIO_NO;
	m_uiPreStopBit = IDC_RADIO_ONEBIT;
	m_uiPreSockMode = IDC_RADIO_BLOCK;
}

CSetParam::~CSetParam()
{
	Uninit();
}

BOOL CSetParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init();

	return TRUE;
}

void CSetParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetParam, CDialogEx)
	//uart=============================================================
	ON_CBN_SELCHANGE(IDC_COMBO_DRVNAME, &CSetParam::OnComboUartName)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, &CSetParam::OnComboBaud)
	ON_EN_CHANGE(IDC_EDIT_BYTE, &CSetParam::OnEditByte)
	ON_BN_CLICKED(IDC_RADIO_ONEBIT, &CSetParam::OnRadioOneBit)
	ON_BN_CLICKED(IDC_RADIO_ONE5BITS, &CSetParam::OnRadioOne5Bits)
	ON_BN_CLICKED(IDC_RADIO_TWOBITS, &CSetParam::OnRadioTwoBits)
	ON_BN_CLICKED(IDC_RADIO_NO, &CSetParam::OnRadioNoParity)
	ON_BN_CLICKED(IDC_RADIO_ODD, &CSetParam::OnRadioODD)
	ON_BN_CLICKED(IDC_RADIO_EVEN, &CSetParam::OnRadioEven)
	//sock=============================================================
	ON_EN_CHANGE(IDC_EDIT_PORT, &CSetParam::OnEditPort)
	ON_BN_CLICKED(IDC_RADIO_BLOCK, &CSetParam::OnRadioBlock)
	ON_BN_CLICKED(IDC_RADIO_NOBLOCK, &CSetParam::OnRadioNoblock)
	//collect==========================================================
	ON_EN_CHANGE(IDC_EDIT_COLLECT_NUM, &CSetParam::OnEditNumber)
	ON_EN_CHANGE(IDC_EDIT_COLLECT_SPACE, &CSetParam::OnEditSpace)
	//log==============================================================
	ON_EN_CHANGE(IDC_EDIT_LOG, &CSetParam::OnEditLogPath)
	ON_EN_CHANGE(IDC_EDIT_IMG, &CSetParam::OnEditImgPath)
	ON_BN_CLICKED(IDC_BTN_SELECT_LOG, &CSetParam::OnClickedLogPath)
	ON_BN_CLICKED(IDC_BTN_SELECT_IMG, &CSetParam::OnClickedImgPath)
	//cmos=============================================================
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetParam::OnClickedSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSetParam::OnClickedCancel)
END_MESSAGE_MAP()

// CSetParam 消息处理程序
//uart=============================================================
void CSetParam::OnComboUartName()
{
	SetUItoMap(EN_MOD_UART, IDC_COMBO_DRVNAME);
}

void CSetParam::OnComboBaud()
{
	SetUItoMap(EN_MOD_UART, IDC_COMBO_BAUD);
}

void CSetParam::OnEditByte()
{
	SetUItoMap(EN_MOD_UART, IDC_EDIT_BYTE);
}

void CSetParam::OnRadioOneBit()
{
	SetUItoMap(EN_MOD_UART, IDC_RADIO_ONEBIT);
	m_uiPreStopBit = IDC_RADIO_ONEBIT;//
}

void CSetParam::OnRadioOne5Bits()
{
	SetUItoMap(EN_MOD_UART, IDC_RADIO_ONE5BITS);
	m_uiPreStopBit = IDC_RADIO_ONE5BITS;
}

void CSetParam::OnRadioTwoBits()
{
	SetUItoMap(EN_MOD_UART, IDC_RADIO_TWOBITS);
	m_uiPreStopBit = IDC_RADIO_TWOBITS;
}

void CSetParam::OnRadioNoParity()
{
	SetUItoMap(EN_MOD_UART, IDC_RADIO_NO);
	m_uiPreParity = IDC_RADIO_NO;
}

void CSetParam::OnRadioODD()
{
	SetUItoMap(EN_MOD_UART, IDC_RADIO_ODD);
	m_uiPreParity = IDC_RADIO_ODD;
}

void CSetParam::OnRadioEven()
{
	SetUItoMap(EN_MOD_UART, IDC_RADIO_EVEN);
	m_uiPreParity = IDC_RADIO_EVEN;
}
//sock===================================
void CSetParam::OnEditPort()
{
	SetUItoMap(EN_MOD_SOCK, IDC_EDIT_PORT);
}

void CSetParam::OnRadioBlock()
{
	SetUItoMap(EN_MOD_SOCK, IDC_RADIO_BLOCK);
	m_uiPreSockMode = IDC_RADIO_BLOCK;
}

void CSetParam::OnRadioNoblock()
{
	SetUItoMap(EN_MOD_SOCK, IDC_RADIO_NOBLOCK);
	m_uiPreSockMode = IDC_RADIO_NOBLOCK;
}
//collect================================
void CSetParam::OnEditNumber()
{
	SetUItoMap(EN_MOD_COLLECT, IDC_EDIT_COLLECT_NUM);
}

void CSetParam::OnEditSpace()
{
	SetUItoMap(EN_MOD_COLLECT, IDC_EDIT_COLLECT_SPACE);
}
//log====================================
void CSetParam::OnEditLogPath()
{
	SetUItoMap(EN_MOD_LOG, IDC_EDIT_LOG);
}

void CSetParam::OnEditImgPath()
{
	SetUItoMap(EN_MOD_LOG, IDC_EDIT_IMG);
}

void CSetParam::OnClickedLogPath()
{
	SetUItoMap(EN_MOD_LOG, IDC_BTN_SELECT_LOG);
}

void CSetParam::OnClickedImgPath()
{
	SetUItoMap(EN_MOD_LOG, IDC_BTN_SELECT_IMG);
}
//cmos===================================

void CSetParam::OnClickedSave()
{
	MAPWIDGET::iterator iter;

	for (int iModID = EN_MOD_UART; iModID < MOD_NUMBER; iModID++)
	{
		for (iter = m_amapWidget[iModID].begin(); iter != m_amapWidget[iModID].end(); iter++)
		{
			WRITE_INI_FILE(iModID, iter->first, iter->second);
		}
	}

	EraseMap();
}

void CSetParam::OnClickedCancel()
{
	EraseMap();

	GetIniFileToUI();
}

void CSetParam::ButtonToEdit(MAPWIDGET &mapWidget, UINT uiWidgetID, CString &strDirPath)
{
	MAPWIDGET::iterator iter;

	iter = mapWidget.find(uiWidgetID);
	if (mapWidget.end() == iter)
	{
		mapWidget.insert(MAPWIDGET::value_type(uiWidgetID, strDirPath));
	}
	else
	{
		iter->second = strDirPath;
	}

	((CEdit *)GetDlgItem(uiWidgetID))->SetWindowTextW(strDirPath);
}

void CSetParam::ManageEdit(MAPWIDGET &mapWidget, UINT uiWidgetID)
{
	CString strRecvData;
	MAPWIDGET::iterator iter;
	((CEdit *)GetDlgItem(uiWidgetID))->GetWindowTextW(strRecvData);

	iter = mapWidget.find(uiWidgetID);
	if (mapWidget.end() == iter)
	{
		mapWidget.insert(MAPWIDGET::value_type(uiWidgetID, strRecvData));
	}
	else
	{
		iter->second = strRecvData;
	}
}

void CSetParam::ManageCombo(MAPWIDGET &mapWidget, UINT uiWidgetID)
{
	CString strRecvData;
	MAPWIDGET::iterator iter;
	CComboBox *pobjComBox = (CComboBox *)GetDlgItem(uiWidgetID);
	if (nullptr != pobjComBox)
	{
		pobjComBox->GetLBText(pobjComBox->GetCurSel(), strRecvData);

		iter = mapWidget.find(uiWidgetID);
		if (mapWidget.end() == iter)
		{
			mapWidget.insert(MAPWIDGET::value_type(uiWidgetID, strRecvData));
		}
		else
		{
			iter->second = strRecvData;
		}
	}
}

void CSetParam::ManageButton(MAPWIDGET &mapWidget, UINT uiWidgetID)
{
	CString strDirPath;
	BROWSEINFO stDirInfo;
	::ZeroMemory(&stDirInfo, sizeof(stDirInfo));

	stDirInfo.pidlRoot = 0;
	stDirInfo.lpszTitle = _T("选择文件存储路径：");
	stDirInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	stDirInfo.lpfn = nullptr;

	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&stDirInfo);
	if (nullptr != lpidlBrowse)
	{
		if (::SHGetPathFromIDList(lpidlBrowse, strDirPath.GetBuffer(MAX_PATH)))
		{
			if (IDC_BTN_SELECT_LOG == uiWidgetID)
			{
				ButtonToEdit(mapWidget, IDC_EDIT_LOG, strDirPath);
			}
			else if (IDC_BTN_SELECT_IMG == uiWidgetID)
			{
				ButtonToEdit(mapWidget, IDC_EDIT_IMG, strDirPath);
			}
		}

		::CoTaskMemFree(lpidlBrowse);
	}
}

void CSetParam::ManageRadio(MAPWIDGET &mapWidget, UINT uiPreWidgetID, UINT uiCurWidgetID)
{
	MAPWIDGET::iterator iter;

	iter = mapWidget.find(uiCurWidgetID);
	if (mapWidget.end() == iter)
	{
		iter = mapWidget.find(uiPreWidgetID);
		if (mapWidget.end() == iter)
		{
			mapWidget.insert(MAPWIDGET::value_type(uiPreWidgetID, _T("false")));
		}
		else
		{
			iter->second = _T("false");
		}

		mapWidget.insert(MAPWIDGET::value_type(uiCurWidgetID, _T("true")));
	}
	//radio不能被重复选中
}

void CSetParam::SetUItoMap(EN_MOD_ID enModID, UINT uiWidgetID)
{
	MAPMODULE::iterator iter;

	if ((IDC_RADIO_ONEBIT == uiWidgetID) || (IDC_RADIO_ONE5BITS == uiWidgetID) ||
		(IDC_RADIO_TWOBITS == uiWidgetID))
	{
		ManageRadio(m_amapWidget[enModID], m_uiPreStopBit, uiWidgetID);
	}
	else if ((IDC_RADIO_NO == uiWidgetID) || (IDC_RADIO_ODD == uiWidgetID) ||
			 (IDC_RADIO_EVEN == uiWidgetID))
	{
		ManageRadio(m_amapWidget[enModID], m_uiPreParity, uiWidgetID);
	}
	else if ((IDC_RADIO_BLOCK == uiWidgetID) || (IDC_RADIO_NOBLOCK == uiWidgetID))
	{
		ManageRadio(m_amapWidget[enModID], m_uiPreSockMode, uiWidgetID);
	}
	else if ((IDC_COMBO_DRVNAME == uiWidgetID) || (IDC_COMBO_BAUD == uiWidgetID))
	{
		ManageCombo(m_amapWidget[enModID], uiWidgetID);
	}
	else if ((IDC_EDIT_BYTE == uiWidgetID) || (IDC_EDIT_PORT == uiWidgetID) ||
			 (IDC_EDIT_COLLECT_NUM == uiWidgetID) || (IDC_EDIT_COLLECT_SPACE == uiWidgetID) ||
			 (IDC_EDIT_LOG == uiWidgetID) || (IDC_EDIT_IMG == uiWidgetID))
	{
		ManageEdit(m_amapWidget[enModID], uiWidgetID);
	}
	else if ((IDC_BTN_SELECT_LOG == uiWidgetID) || (IDC_BTN_SELECT_IMG == uiWidgetID))
	{
		ManageButton(m_amapWidget[enModID], uiWidgetID);
	}

	iter = m_mapModule.find(enModID);
	if (m_mapModule.end() == iter)
	{
		m_mapModule.insert(MAPMODULE::value_type(enModID, m_amapWidget[enModID]));
	}
}

void CSetParam::SetPreRadio(UINT uiWidgetID)
{
	if ((IDC_RADIO_ONEBIT == uiWidgetID) || (IDC_RADIO_ONE5BITS == uiWidgetID) ||
		(IDC_RADIO_TWOBITS == uiWidgetID))
	{
		m_uiPreStopBit = uiWidgetID;
	}
	else if ((IDC_RADIO_NO == uiWidgetID) || (IDC_RADIO_ODD == uiWidgetID) ||
			(IDC_RADIO_EVEN == uiWidgetID))
	{
		m_uiPreParity = uiWidgetID;
	}
	else if ((IDC_RADIO_BLOCK == uiWidgetID) || (IDC_RADIO_NOBLOCK == uiWidgetID))
	{
		m_uiPreSockMode = uiWidgetID;
	}
}

void CSetParam::SetPrmUI(const ST_INI_NODE* pstIniNode)
{
	if ((IDC_COMBO_DRVNAME == pstIniNode->uiWidgetID) || (IDC_COMBO_BAUD == pstIniNode->uiWidgetID))
	{
		((CComboBox*)GetDlgItem(pstIniNode->uiWidgetID))->SelectString(0, pstIniNode->strPrmIni); 
	}
	else if ((IDC_RADIO_ONEBIT == pstIniNode->uiWidgetID) || (IDC_RADIO_NO == pstIniNode->uiWidgetID) ||
			 (IDC_RADIO_BLOCK == pstIniNode->uiWidgetID))
	{
		((CButton *)GetDlgItem(pstIniNode->uiWidgetID))->SetCheck(TRUE);
	}
	else if ((IDC_EDIT_BYTE == pstIniNode->uiWidgetID) || (IDC_EDIT_PORT == pstIniNode->uiWidgetID) ||
			 (IDC_EDIT_COLLECT_NUM == pstIniNode->uiWidgetID) || (IDC_EDIT_COLLECT_SPACE == pstIniNode->uiWidgetID))
	{
		((CEdit*)GetDlgItem(pstIniNode->uiWidgetID))->SetWindowTextW(pstIniNode->strPrmIni);
	}
	else if ((IDC_EDIT_LOG == pstIniNode->uiWidgetID) || (IDC_EDIT_IMG == pstIniNode->uiWidgetID))
	{
		CString strSavePath;
		::GetCurrentDirectory(MAX_PATH, strSavePath.GetBuffer(MAX_PATH));
		((CEdit*)GetDlgItem(pstIniNode->uiWidgetID))->SetWindowTextW(strSavePath);
	}
}

void CSetParam::SetPrmUI(UINT uiWidgetID, CString strUIData)
{
	if ((IDC_COMBO_DRVNAME == uiWidgetID) || (IDC_COMBO_BAUD == uiWidgetID))
	{
		((CComboBox*)GetDlgItem(uiWidgetID))->SelectString(0, strUIData);
	}
	else if ((IDC_EDIT_BYTE == uiWidgetID) || (IDC_EDIT_PORT == uiWidgetID) ||
		(IDC_EDIT_COLLECT_NUM == uiWidgetID) || (IDC_EDIT_COLLECT_SPACE == uiWidgetID) ||
		(IDC_EDIT_LOG == uiWidgetID) || (IDC_EDIT_IMG == uiWidgetID))
	{
		((CEdit*)GetDlgItem(uiWidgetID))->SetWindowTextW(strUIData);
	}
	else if ((IDC_RADIO_ONEBIT == uiWidgetID) || (IDC_RADIO_ONE5BITS == uiWidgetID) ||
			 (IDC_RADIO_TWOBITS == uiWidgetID) || (IDC_RADIO_NO == uiWidgetID) || 
			 (IDC_RADIO_ODD == uiWidgetID) || (IDC_RADIO_EVEN == uiWidgetID) ||
			 (IDC_RADIO_BLOCK == uiWidgetID) || (IDC_RADIO_NOBLOCK == uiWidgetID))
	{
		if (_T("true") == strUIData)
		{
			SetPreRadio(uiWidgetID);
			((CButton *)GetDlgItem(uiWidgetID))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(uiWidgetID))->SetCheck(FALSE);
		}
	}
}

void CSetParam::InitCombo(UINT uiWidgetID, const CString *pstrSet, int iSetNum)
{
	for (int iNum = 0; iNum < iSetNum; iNum++)
	{
		((CComboBox *)GetDlgItem(uiWidgetID))->InsertString(iNum, pstrSet[iNum]);
	}
}

void CSetParam::GetIniFileToUI()
{
	for (int iModule = 0; iModule < MOD_NUMBER; iModule++)
	{
		for (int iWidget = 0; iWidget < WIDGET_NUMBER; iWidget++)
		{
			if (0 != g_astIni[iModule][iWidget].uiWidgetID)
			{
				CString strRecvData;
				READ_INI_FILE(iModule, g_astIni[iModule][iWidget].uiWidgetID, strRecvData);
				SetPrmUI(g_astIni[iModule][iWidget].uiWidgetID, strRecvData);
			}
		}
	}
}

void CSetParam::InitIniFile()
{
	for (int iModule = 0; iModule < MOD_NUMBER; iModule++)
	{
		for (int iWidget = 0; iWidget < WIDGET_NUMBER; iWidget++)
		{
			if (0 != g_astIni[iModule][iWidget].uiWidgetID)
			{
				SetPrmUI(&g_astIni[iModule][iWidget]);
				if ((IDC_EDIT_LOG == g_astIni[iModule][iWidget].uiWidgetID) || (IDC_EDIT_IMG == g_astIni[iModule][iWidget].uiWidgetID))
				{
					CString strSavePath;
					::GetCurrentDirectory(MAX_PATH, strSavePath.GetBuffer(MAX_PATH));
					WRITE_INI_FILE(iModule, g_astIni[iModule][iWidget].uiWidgetID, strSavePath);
				}
				else
				{
					WRITE_INI_FILE(iModule, g_astIni[iModule][iWidget].uiWidgetID, g_astIni[iModule][iWidget].strPrmIni);
				}
			}
		}
	}
}

void CSetParam::EraseMap()
{
	//清除单个节点信息
	for (int iNumber = 0; iNumber < MOD_NUMBER; iNumber++)
	{
		m_amapWidget[iNumber].erase(m_amapWidget[iNumber].begin(), m_amapWidget[iNumber].end());
	}
	//清除所有节点信息
	m_mapModule.erase(m_mapModule.begin(), m_mapModule.end());
}

void CSetParam::Init()
{
	InitCombo(IDC_COMBO_BAUD, g_astrBaud, sizeof (g_astrBaud) / sizeof (g_astrBaud[0]));
	InitCombo(IDC_COMBO_DRVNAME, g_astrDrvName, sizeof (g_astrDrvName) / sizeof (g_astrDrvName[0]));

	if (-1 == _access(SETPRM_INI_PATH, 0))
	{
		InitIniFile();
	}
	else
	{
		GetIniFileToUI();
	}
}

void CSetParam::Uninit()
{
	EraseMap();
}