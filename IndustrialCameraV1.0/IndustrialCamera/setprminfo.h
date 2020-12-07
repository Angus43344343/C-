#ifndef _SETPRMINFO_H__
#define _SETPRMINFO_H__

#include "Resource.h"

/*=======================文件信息============================*/
#define MOD_NUMBER			(5)
#define WIDGET_NUMBER		(9)
#define FILE_PATH_MAX_LEN	(128)
#define SETPRM_INI_PATH		".//setParam.ini"
#define SETPRM_INI_PATH_EX	_T(".//setParam.ini")
/*======================控件初始值设定=========================*/
#define INI_UART_NAME		_T("COM1")
#define INI_UART_BAUD		_T("9600")
#define INI_UART_BYTE		_T("8")
#define INI_UART_ONEBIT		_T("true")
#define INI_UART_ONE5BIT	_T("false")
#define INI_UART_TWOBIT		_T("false")
#define INI_UART_NO			_T("true")
#define INI_UART_ODD		_T("false")
#define INI_UART_EVEN		_T("false")

#define INI_SOCK_PORT		_T("6000")
#define INI_SOCK_BLOCK		_T("true")
#define INI_SOCK_NOBLOCK	_T("false")

#define INI_COLLECT_NUM		_T("10")
#define INI_COLLECT_SPACE	_T("20")/*ms*/

#define INI_LOG_FILEPATH	_T("")
#define INI_LOG_IMGPATH		_T("")
/*========================读写ini文件===========================*/
#define WRITE_INI_FILE(mod, wid, str)\
do {\
	CString strWidgetID;\
	strWidgetID.Format(_T("%d"), wid);\
	::WritePrivateProfileString(g_astrModName[mod], strWidgetID, str, SETPRM_INI_PATH_EX);\
} while (0)

#define READ_INI_FILE(mod, wid, str)\
do {\
	CString strWidgetID;\
	strWidgetID.Format(_T("%d"), wid);\
	::GetPrivateProfileString(g_astrModName[mod], strWidgetID, 0, str.GetBuffer(MAX_PATH), MAX_PATH, SETPRM_INI_PATH_EX);\
}while (0)
/*=============================================================*/
typedef enum//.ini文件的模块ID
{
	EN_MOD_UART = 0x00,
	EN_MOD_SOCK,
	EN_MOD_COLLECT,
	EN_MOD_LOG,
	EN_MOD_CMOS,
}EN_MOD_ID;

typedef struct
{
	UINT uiWidgetID;
	CString strPrmIni;
}ST_INI_NODE, *PST_INI_NODE;

const CString g_astrModName[] = 
{ 
	_T("UART"), _T("SOCK"), _T("COLLECT"), _T("LOG"), _T("CMOS") 
};

const ST_INI_NODE g_astIni[MOD_NUMBER][WIDGET_NUMBER] =
{
	{/*uart*/
		{ IDC_COMBO_DRVNAME, INI_UART_NAME },	{ IDC_COMBO_BAUD, INI_UART_BAUD },			{ IDC_EDIT_BYTE, INI_UART_BYTE },
		{ IDC_RADIO_ONEBIT, INI_UART_ONEBIT },	{ IDC_RADIO_ONE5BITS, INI_UART_ONE5BIT },	{ IDC_RADIO_TWOBITS, INI_UART_TWOBIT },
		{ IDC_RADIO_NO, INI_UART_NO },			{ IDC_RADIO_ODD, INI_UART_ODD },			{ IDC_RADIO_EVEN, INI_UART_EVEN },
	},
	{/*sock*/
		{ IDC_EDIT_PORT, INI_SOCK_PORT },		{ IDC_RADIO_BLOCK, INI_SOCK_BLOCK },		{ IDC_RADIO_NOBLOCK, INI_SOCK_NOBLOCK },
	},
	{/*collect*/
		{ IDC_EDIT_COLLECT_NUM, INI_COLLECT_NUM }, { IDC_EDIT_COLLECT_SPACE, INI_COLLECT_SPACE },
	},
	{/*log*/
		{ IDC_EDIT_LOG, INI_LOG_FILEPATH },		{ IDC_EDIT_IMG, INI_LOG_IMGPATH },
	},
	{/*cmos*/
	},
};

#endif /*_SETPRMINFO_H__*/