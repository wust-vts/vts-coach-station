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
	CString CAIS::AIS_encode(unsigned char const* bytes_to_encode, unsigned int in_len,int fill_part);//仿base——64将位encode为6位
	CString CAIS::verify_char(unsigned char verify) ;   //将校验信息转为16进制
	CString CAIS::AIS_assamble(CString &mainstr, int isOwn = 1);  //将主信息进行装配，得到最后的发送信息
	void CAIS::chop_message5(CString & meta_msg5,CString &chop1,CString & chop2);     //将type5进行分割（太长了就需要分成两段）

	CString CAIS::check_result(CString & meta_msg);   
	CString CAIS::sendStr(CString msg, int isOwn = 1);   //经过它发送
};
