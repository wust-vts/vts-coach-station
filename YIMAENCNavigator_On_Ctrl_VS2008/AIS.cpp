#include "StdAfx.h"
#include "AIS.h"

static int fragment_index=0;
CAIS::CAIS(void)
{
	/*
	if (!mscomm.Create(NULL, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), AfxGetApp()->m_pMainWnd, 9000))
	{
		AfxMessageBox("串口创建失败！");
	}
	if(mscomm.get_PortOpen())
		mscomm.put_PortOpen(FALSE);
	mscomm.put__CommPort(2);
	mscomm.put_Settings(_T("9600,n,8,1"));
	mscomm.put_InBufferSize(1024);
	mscomm.put_InBufferCount(0);
	mscomm.put_InputMode(0);
	mscomm.put_InputLen(0);
	mscomm.put_RThreshold(1);
	if(!mscomm.get_PortOpen())
	{
		mscomm.put_PortOpen(TRUE);
		//MessageBox(_T("com2,ok!"));
		//::MessageBox(_T("com2,ok!"));
		MessageBox(NULL, _T("com2初始化失败"), _T("警告"), MB_OK);  
	}*/
}

CAIS::~CAIS(void)
{
}
CString CAIS::AIS_encode(unsigned char const* bytes_to_encode, unsigned int in_len, int fill_part)
{

	CString base64_chars (_T("0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVW`abcdefghijklmnopqrstuvw"));  
	CString ret;
	int i=0;
	int j=0;
	//unsigned char verifying=0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	while(in_len--)
	{
		char_array_3[i++]=*(bytes_to_encode++);   //参照base64  的加密方式，每次提取三个字符，然后按六为单位截取之后，生成四个字符，然后参照base64_chars找到对应的char
		if(i==3)
		{
			char_array_4[0]=(char_array_3[0] & 0xfc)>>2;
			char_array_4[1]=((char_array_3[0] & 0x03)<<4)+((char_array_3[1] & 0xf0)>>4);
			char_array_4[2]=((char_array_3[1] & 0x0f)<<2)+((char_array_3[2] & 0xc0)>>6);
			char_array_4[3]=char_array_3[2] &0x3f;
			for(i=0;i<4;i++)
			{
		    ret += base64_chars[char_array_4[i]];  
			//verifying=verifying ^(char_array_4[i]);
			}
			i=0;                                      //由于校验是在分割为6bits之后进行的，所以直接在这里就完成校验
		}

	}

	if (i)     //此时还有一些没有取完，则分情况考虑
	{  
		/*for (j = i; j < 3; j++)  
		char_array_3[j] = '\0';  

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;  
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);  
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);  
		char_array_4[3] = char_array_3[2] & 0x3f;  

		for (j = 0; (j < i + 1); j++)  
		ret += base64_chars[char_array_4[j]];  
		if(i==2)
		fill_part=2;
		if(i==1)
		fill_part=4;*/
		if(i==1)  //当只剩下一个字符时

		{
			fill_part=4;
			char_array_4[0]=(char_array_3[0] & 0xfc)>>2;
			char_array_4[1]=(char_array_3[0]& 0x03)<<4;
			for(j=0;j<2;j++)
			{
				ret += base64_chars[char_array_4[i]]; 
				//verifying=verifying^char_array_4[j];
			}
		}
		if(i==2)
		{
			fill_part=4;
			char_array_4[0]=(char_array_3[0] & 0xfc)>>2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4); 
			char_array_4[2]=(char_array_3[1] & 0x0f) << 2;
			for(j=0;j<3;j++)
			{
				ret += base64_chars[char_array_4[i]]; 
				//verifying=verifying^char_array_4[j];
			}
		}
	}  
	// retverify=verify_char(verifying);//为什么我在这里加了link时候就出错呢？

	//retverify=verify_char(verifying);
	return ret;  

}
CString CAIS::verify_char(unsigned char verify)   //将校验信息转为16进制
{
	CString retvalue;
	unsigned char left;
	unsigned char rght=0;
	if(((verify &0x0f)>>4)<10)
		left=((verify & 0xf0)>>4)+48;
	else left=((verify & 0xf0)>>4)+65;


	if((verify &0x0f)<10)
		rght=(verify &0x0f)+48;
	else rght=(verify &0x0f)+65;
	retvalue+=left;
	retvalue+=rght;
	//return retvalue;
	return retvalue;

}
CString CAIS::AIS_assamble(CString &mainstr, int isOwn)
{

	CString assambleresult;
    if(mainstr.GetAt(0)=='1')
	{
		CString verstr;
		//verstr=check_result(mainstr);
		if (isOwn == 1)
		{
			assambleresult+="AIVDO,1,1,2,A,";
		}
		else
		{
			assambleresult+="AIVDM,1,1,1,A,";
		}
		 assambleresult+=mainstr;
		 assambleresult+=",0";
		 int parity = 0;
		 for(int i=0;i<assambleresult.GetLength();i++)
		 {
			 parity=parity^assambleresult.GetAt(i);
		 }
		 verstr.Format("%.2X", parity);
		 assambleresult="!" + assambleresult + "*" + verstr;
	}
	else if(mainstr.GetAt(0)=='5')
	{

		CString index_msg;   
		int j =fragment_index;   
		index_msg.Format(_T("%d"),j);  //将suquential message ID  转为CString

		CString check_1_msg;
		CString check_2_msg;

		CString msg5_1;    //原始信息
		CString msg5_2;
		CString msg5_1_result; //结果信息
		CString msg5_2_result;
		
		check_1_msg=check_result(msg5_1);  //获得校验信息
		check_2_msg=check_result(msg5_2);
		chop_message5(mainstr,msg5_1,msg5_2);
	   /* msg5_1_result+="!AIVDM,2,1,";
		msg5_1_result+=str1;
		msg5_1_result+=",B,";
		msg5_1_result+=msg5_1;*/
		msg5_1_result=_T("!AIVDM,2,1,")+index_msg+_T(",B,")+msg5_1+_T("0*")+check_1_msg;
		msg5_2_result=_T("!AIVDM,2,2,")+index_msg+_T(",B,")+msg5_2+_T("0*")+check_2_msg;
		
		assambleresult=msg5_1_result+msg5_2_result;
	
	}
	
	
	return assambleresult;
}

void CAIS::chop_message5(CString & meta_msg5,CString &chop1,CString & chop2)
{

	chop1=meta_msg5.Left(56);
	chop2=meta_msg5.Right(15);   //总共有71个字符，前面取56个，后面取15个

}
CString CAIS::check_result(CString & meta_msg)
{

	CString check_str;
	unsigned char verifying=0;
	int i=meta_msg.GetLength();    //数据校验就是将信息字段全部异或
	for(int j=0;j<i;j++)
		verifying=verifying^meta_msg.GetAt(j);
	check_str=verify_char(verifying);
	return check_str;
}
CString CAIS::sendStr(CString msg, int isOwn)
{  

	CString send_msg;
	if(msg.GetAt(0)=='1')
	{   
		
		CAisType1 *msg_type1=new CAisType1(msg);
		unsigned char result[22];
		memset(result,0,sizeof(result));
		msg_type1->message1_parse_encode(msg,result);
		//CString retting;
		int leng5=0;
	    send_msg=AIS_assamble(AIS_encode(result,21,leng5), isOwn);

		delete msg_type1;
	}
	else if(msg.GetAt(0)=='5')
	{
		CAisType5 *msg_type5=new CAisType5(msg);
		unsigned char result_7[54];
		memset(result_7,0,sizeof(result_7));
		msg_type5->message5_parse_encode(msg,result_7);
		int leng7=0;
		send_msg=AIS_assamble(AIS_encode(result_7,53,leng7));

		delete msg_type5;
	}

	return send_msg;
	//mscomm.put_Output(COleVariant(send_msg));
}