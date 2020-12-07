#ifndef _COMMON_H__
#define _COMMON_H__

#include <assert.h>

/*============================������Ϣ===============================*/
#define DRV_COUNT			(2)
#define DRV_ID_ERROR		(-1)
#define SEND_RECV_ERROR		(-1)
#define RECV_BUF_SIZE		(512)
/*==============================֡����===============================*/
#define FRAME_DATA_LEN		(123)
#define FRAME_TOTAL_LEN		sizeof (ST_CMD_HANDSHAKE)
/*============================�ͷ��ڴ�================================*/
#define FREE_MALLOC(ptr)	{if(nullptr != ptr) delete ptr; ptr = nullptr;}
/*============================�Զ�����Ϣ===============================*/
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
	EN_TYPE_HANDSHAKE = 0x0001, //������Ϣ
	EN_TYPE_READCMOS,			//��CMOS����
	EN_TYPE_SETCMOS,			//����CMOS����
	EN_TYPE_GETDATA_SOFTWARE,	//���жϲɼ����� 
	EN_TYPE_GETDATA_HARDWARE,	//Ӳ�жϲɼ�����
	EN_TYPE_MODE_BATCH,			//����ģʽ�ɼ�
	EN_TYPE_MODE_NORMAL,		//����ģʽ�ɼ�
	EN_TYPE_ALG_RECUART,		//�㷨ʶ��UART
	EN_TYPE_ALG_RECRESULT,		//�㷨ʶ���� 
}EN_FRAME_TYPE;

/*============================֡�ṹ==================================*/
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

/*-*-*-*-*-*-*-*-*-*-*������Ϣ֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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

/*-*-*-*-*-*-*-*-*-*-*��CMOS����֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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

/*-*-*-*-*-*-*-*-*-*-*��CMOS����֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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

/*-*-*-*-*-*-*-*-*-*-*���жϲɼ�����֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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

/*-*-*-*-*-*-*-*-*-*-*���жϲɼ�����֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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

/*-*-*-*-*-*-*-*-*-*-*�����ɼ�ģʽ֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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

/*-*-*-*-*-*-*-*-*-*-*�����ɼ�ģʽ֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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

/*-*-*-*-*-*-*-*-*-*-*�㷨ʶ��UART����֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct
{
	ST_FRAME_HEADER stHeader;
	UINT uiBaudRate;//������
	UCHAR ucStopBit;//ֹͣλ
	UCHAR ucCheckType;//У�鷽ʽ
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

/*-*-*-*-*-*-*-*-*-*-*�㷨ʶ����֡-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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