#pragma once
//#include "mscomm.h"
#include "AisType1.h"
#include "AisType5.h"

class CAIS
{
public:
	CAIS(void);
	~CAIS(void);

	//CMSComm mscomm;
	CString CAIS::AIS_encode(unsigned char const* bytes_to_encode, unsigned int in_len,int fill_part);//��base����64��λencodeΪ6λ
	CString CAIS::verify_char(unsigned char verify) ;   //��У����ϢתΪ16����
	CString CAIS::AIS_assamble(CString &mainstr, int isOwn = 1);  //������Ϣ����װ�䣬�õ����ķ�����Ϣ
	void CAIS::chop_message5(CString & meta_msg5,CString &chop1,CString & chop2);     //��type5���зָ̫���˾���Ҫ�ֳ����Σ�

	CString CAIS::check_result(CString & meta_msg);   
	CString CAIS::sendStr(CString msg, int isOwn = 1);   //����������
};