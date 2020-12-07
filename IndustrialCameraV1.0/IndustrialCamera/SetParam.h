#pragma once
//CSetParam 对话框

#include "setprminfo.h"
#include <map>

typedef std::map<UINT, CString> MAPWIDGET;
typedef std::map<EN_MOD_ID, MAPWIDGET> MAPMODULE;
/*==========================================================*/
class CSetParam : public CDialogEx
{
	DECLARE_DYNAMIC(CSetParam)
public:
	CSetParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetParam();
//UI========================================
	enum { IDD = IDD_CHILD_PRM };
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//uart===================================
	afx_msg void OnComboUartName();
	afx_msg void OnComboBaud();
	afx_msg void OnEditByte();
	afx_msg void OnRadioOneBit();
	afx_msg void OnRadioOne5Bits();
	afx_msg void OnRadioTwoBits();
	afx_msg void OnRadioNoParity();
	afx_msg void OnRadioODD();
	afx_msg void OnRadioEven();
	//sock===================================
	afx_msg void OnEditPort();
	afx_msg void OnRadioBlock();
	afx_msg void OnRadioNoblock();
	//collect================================
	afx_msg void OnEditNumber();
	afx_msg void OnEditSpace();
	//log====================================
	afx_msg void OnEditLogPath();
	afx_msg void OnEditImgPath();
	afx_msg void OnClickedLogPath();
	afx_msg void OnClickedImgPath();
	//cmos===================================
	afx_msg void OnClickedSave();
	afx_msg void OnClickedCancel();
	DECLARE_MESSAGE_MAP()
private:
	UINT m_uiPreParity;
	UINT m_uiPreStopBit;
	UINT m_uiPreSockMode;
private:
	void ButtonToEdit(MAPWIDGET &mapWidget, UINT uiWidgetID, CString &strDirPath);
private:
	void ManageEdit(MAPWIDGET &mapWidget, UINT uiWidgetID);
	void ManageCombo(MAPWIDGET &mapWidget, UINT uiWidgetID);
	void ManageButton(MAPWIDGET &mapWidget, UINT uiWidgetID);
	void ManageRadio(MAPWIDGET &mapWidget, UINT uiPreWidgetID, UINT uiCurWidgetID);
private:
	void SetUItoMap(EN_MOD_ID enModID, UINT uiWidgetID);
//app======================================
private:
	MAPMODULE	m_mapModule;
	MAPWIDGET	m_amapWidget[MOD_NUMBER];
private:
	void SetPreRadio(UINT uiWidgetID);
private:
	void SetPrmUI(const ST_INI_NODE* pstIniNode);
	void SetPrmUI(UINT uiWidgetID, CString strUIData);
private:
	void InitCombo(UINT uiWidgetID, const CString *pstrSet, int iSetNum);

	void InitIniFile();
	void GetIniFileToUI();

	void EraseMap();
private:
	void Init();
	void Uninit();
//app======================================
};
