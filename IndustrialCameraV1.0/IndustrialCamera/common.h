#ifndef _COMMON_H__
#define _COMMON_H__

#include <assert.h>

/*============================驱动信息===============================*/
#define DRV_COUNT			(2)
#define DRV_ID_ERROR		(-1)
#define SEND_RECV_ERROR		(-1)
#define RECV_BUF_SIZE		(512)
/*==============================帧长度===============================*/
#define FRAME_DATA_LEN		(123)
#define FRAME_TOTAL_LEN		sizeof (ST_CMD_HANDSHAKE)
/*============================释放内存================================*/
#define FREE_MALLOC(ptr)	{if(nullptr != ptr) delete ptr; ptr = nullptr;}
/*============================自定义消息===============================*/
#define WM_SEND_DATA		(WM_USER + 100)
#define WM_RECV_DATA		(WM_USER + 101)

typedef enum
{
	EN_DRV_SOCK  = 0x00,
	EN_DRV_UART,
	EN_DRV_USB,
}EN_DRV_TYPE;

typedef enum
{
	EN_FRAME_HEADER = 0x3C,
	EN_FRAME_TAIL = 0x3E,
}EN_FRAME_DATA;

typedef enum
{
	EN_TYPE_HANDSHAKE = 0x0001, //握手信息
	EN_TYPE_READCMOS,			//读CMOS参数
	EN_TYPE_SETCMOS,			//配置CMOS参数
	EN_TYPE_GETDATA_SOFTWARE,	//软中断采集数据 
	EN_TYPE_GETDATA_HARDWARE,	//硬中断采集数据
	EN_TYPE_MODE_BATCH,			//批量模式采集
	EN_TYPE_MODE_NORMAL,		//正常模式采集
	EN_TYPE_ALG_RECUART,		//算法识别UART
	EN_TYPE_ALG_RECRESULT,		//算法识别结果 
}EN_FRAME_TYPE;

/*============================帧结构==================================*/
#pragma pack(1)
typedef struct
{
	UCHAR ucFrameHeader;
	USHORT usFrameType;
}ST_FRAME_HEADER, *PST_FRAME_HEADER;

typedef struct
{
	UCHAR ucCheckSum;
	UCHAR ucFrameTail;
}ST_FRAME_TAIL, *PST_FRAME_TAIL;

/*-*-*-*-*-*-*-*-*-*-*握手信息帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_CMD_HANDSHAKE, *PST_CMD_HANDSHAKE;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucVersionFPGA[10];
	UCHAR aucVersionSOCALG[10];
	UCHAR aucVersionSOCLINUX[10];
	UCHAR aucData[93];
	ST_FRAME_TAIL stTial;
}ST_RSP_HANDSHAKE, *PST_RSP_HANDSHAKE;

/*-*-*-*-*-*-*-*-*-*-*读CMOS参数帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_CMD_READCMOS, *PST_CMD_READCMOS;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_RSP_READCMOS, *PST_RSP_READCMOS;

/*-*-*-*-*-*-*-*-*-*-*读CMOS参数帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_CMD_SETCMOS, *PST_CMD_SETCMOS;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR ucSetResult;
	UCHAR aucData[FRAME_DATA_LEN - 1];
	ST_FRAME_TAIL stTail;
}ST_RSP_SETCMOS, *PST_RSP_SETCMOS;

/*-*-*-*-*-*-*-*-*-*-*软中断采集数据帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UINT uiNumber;
	UINT uiSpace;
	UCHAR aucData[115];
	ST_FRAME_TAIL stTail;
}ST_CMD_GETDATA_SOFTWARE, *PST_CMD_GETDATA_SOFTWARE;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR ucResult;
	UCHAR aucData[FRAME_DATA_LEN - 1];
	ST_FRAME_TAIL stTail;
}ST_RSP_GETDATA_SOFTWARE, *PST_RSP_GETDATA_SOFTWARE;

/*-*-*-*-*-*-*-*-*-*-*软中断采集数据帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_CMD_GETDATA_HARDWARE, *PST_CMD_GETDATA_HARDWARE;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR ucResult;
	UCHAR aucData[FRAME_DATA_LEN - 1];
	ST_FRAME_TAIL stTail;
}ST_RSP_GETDATA_HARDWARE, *PST_RSP_GETDATA_HARDWARE;

/*-*-*-*-*-*-*-*-*-*-*批量采集模式帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_CMD_MODE_BATCH, *PST_CMD_MODE_BATCH;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR ucResult;
	UCHAR aucData[FRAME_DATA_LEN - 1];
	ST_FRAME_TAIL stTail;
}ST_RSP_MODE_BATCH, *PST_RSP_MODE_BATCH;

/*-*-*-*-*-*-*-*-*-*-*正常采集模式帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_CMD_MODE_NORMAL, *PST_CMD_MODE_NORMAL;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR ucResult;
	UCHAR aucData[FRAME_DATA_LEN - 1];
	ST_FRAME_TAIL stTail;
}ST_RSP_MODE_NORMAL, *PST_RSP_MODE_NORMAL;

/*-*-*-*-*-*-*-*-*-*-*算法识别UART配置帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UINT uiBaudRate;//波特率
	UCHAR ucStopBit;//停止位
	UCHAR ucCheckType;//校验方式
	UCHAR ucDataBit;
	UCHAR aucData[116];
	ST_FRAME_TAIL stTail;
}ST_CMD_ALG_RECUART, *PST_CMD_ALG_RECUART;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR ucResult;
	UCHAR aucData[FRAME_DATA_LEN - 1];
	ST_FRAME_TAIL stTail;
}ST_RSP_ALG_RECUART, *PST_RSP_ALG_RECUART;

/*-*-*-*-*-*-*-*-*-*-*算法识别结果帧-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR aucData[FRAME_DATA_LEN];
	ST_FRAME_TAIL stTail;
}ST_CMD_ALG_RECRESULT, *PST_CMD_ALG_RECRESULT;

typedef struct
{
	ST_FRAME_HEADER stHeader;
	UCHAR ucResult;
	UCHAR ucQRCodeType;
	UCHAR ucQRCodeNum;
	UCHAR ucQRCodeValue[120];
	ST_FRAME_TAIL stTail;
}ST_RSP_ALG_RECRESULT, *PST_RSP_ALG_RECRESULT;
#pragma pack()

#endif /*_COMMON_H__*/