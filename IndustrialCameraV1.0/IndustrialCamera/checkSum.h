#ifndef _CHECKSUM_H__
#define _CHECKSUM_H__

/*****************************Define Checksum*******************************/
#define CAL_CHKSUM				(0x7F)
/*****************************Deine Min CRC Length**************************/
#define DEF_CRC_LEN_MIN			(0x04)
/*****************************Define Initial Value**************************/
#define DEF_CRC_INIT_VALUE		(0x0000) 		
/*****************************Define Polynomial*****************************/
#define DEF_CRC_POLINOMIAL 		(0x1021) 

class CCheckSum
{
private:
	unsigned short CalCRC(unsigned short usDstCrc, unsigned short usCalCrc);
public:
	//***************************和校验*******************************************************/ 
	unsigned char GetChkSum(unsigned char *pucData, unsigned long ulDataSize);
	bool CompChkSum(unsigned char *pucData, unsigned long ulDataSize, unsigned char ucChkSum);
	//***************************CRC16校验****************************************************/
	unsigned short GetChkCRC(unsigned char *pucData, unsigned long ulDataSize);
	bool CompChkCRC(unsigned char *pucData, unsigned long ulDataSize, unsigned short usChkSum);
public:
	CCheckSum();
	~CCheckSum();
};

#endif /*_CHECKSUM_H__*/