#include "StdAfx.h"
#include "AisType5.h"

CAisType5::CAisType5(void)
{
}

CAisType5::~CAisType5(void)
{
}
CAisType5::CAisType5(CString str)
{
	this->str=str;
}
void CAisType5::message5_parse_encode(CString & st,unsigned char *result_7)
{
	CString mgs_type;
	CString repeat_indicator;
	CString mmsi;
	// CString ais_version; 由于文档上说  1-3=future editions，所以按照 ITU1371 这个字段暂不处理
	CString imo;
	CString call_sign;
	CString vessel_name;
	CString ship_type;
	CString dimension_bow;
	CString dimension_stern;
	CString dimension_port;
	CString dimension_start;
	CString pos_fix_type;
	CString eta_month;
	CString eta_day;
	CString eta_hour;
	CString eta_minute;
	CString draught;
	CString destination;
	CString DTE;
	// CString spare（文档上，它是 not used，所以这里不用）


	AfxExtractSubString(mgs_type,str,0,',');
	AfxExtractSubString(repeat_indicator,str,1,',');
	AfxExtractSubString(mmsi,str,2,',');
	// AfxExtractSubString(ais_version,str,3,',');
	AfxExtractSubString(imo,str,4,',');
	AfxExtractSubString(call_sign,str,5,',');
	AfxExtractSubString(vessel_name,str,6,',');
	AfxExtractSubString(ship_type,str,7,',');
	AfxExtractSubString(dimension_bow,str,8,',');
	AfxExtractSubString(dimension_stern,str,9,',');
	AfxExtractSubString(dimension_port,str,10,',');
	AfxExtractSubString(dimension_start,str,11,',');
	AfxExtractSubString(pos_fix_type,str,12,',');
	AfxExtractSubString(eta_month,str,13,',');
	AfxExtractSubString(eta_day,str,14,',');
	AfxExtractSubString(eta_hour,str,15,',');
	AfxExtractSubString(eta_minute,str,16,',');
	AfxExtractSubString(draught,str,17,',');
	AfxExtractSubString(destination,str,18,',');
	AfxExtractSubString(DTE,str,19,',');

	//unsigned char result_7[54];
	memset(result_7,0,sizeof(result_7));
	result_7[0]=(result_7[0]^_ttoi(mgs_type))<<2;  //将message_type和resul_7t[0]相与，然后左移两位
	if(!repeat_indicator.IsEmpty())                 //如果非空，则需要在6-7加上repeat indicator字段，如果为空，则不用管（默认是0）
	{
		result_7[0]=result_7[0] ^(_ttoi(repeat_indicator));
	}

	unsigned int mmsi_num=_ttoi(mmsi);              //此处必须为unsigned，不然在移位是会出现负数，unsigned之后无论移位后最高位是否为1，都当做正数对待
	result_7[1]= result_7[1]^(mmsi_num>>22);
	result_7[2]= result_7[2]^((mmsi_num<<10)>>24);
	result_7[3]= result_7[3]^((mmsi_num<<18)>>24);
	result_7[4]= (result_7[4]^(mmsi_num &0x0000003f))<<2;  //这里为了与上面的不同，采用 与的方式提取最后的六位

	unsigned imo_num=_ttoi(imo);   //从result_7[5]开始
	result_7[5]=result_7[5]^(imo_num>>22);
	result_7[6]=result_7[6]^((imo_num<<10)>>24);
	result_7[7]=result_7[7]^((imo_num<<18)>>24);
	result_7[8]=(result_7[8]^(imo_num & 0x0000003f))<<2;  //到这里result_7[8]还有两位没有填满
	//这里要解决的问题，如何从CString转为char[]
	char c_sign[6];
	memcpy(c_sign,call_sign,call_sign.GetLength());
	result_7[8]=result_7[8]+(c_sign[0]>>6);  //需要验证，能不能直接加上，c_sign的高两位组成的数
	result_7[9]=(result_7[9]^(c_sign[0] & 0x3f))<<2;
	result_7[9]=result_7[9]+(c_sign[1]>>6);
	result_7[10]=(result_7[10]^(c_sign[1] & 0x3f))<<2;
	result_7[10]=result_7[10]+(c_sign[2]>>6);
	result_7[11]=(result_7[11]^(c_sign[2] & 0x3f))<<2;
	result_7[11]=result_7[11]+(c_sign[3]>>6);
	result_7[12]=(result_7[12]^(c_sign[3] & 0x3f))<<2;
	result_7[12]=result_7[12]+(c_sign[4]>>6);
	result_7[13]=(result_7[13]^(c_sign[4] & 0x3f))<<2;
	result_7[13]=result_7[13]+(c_sign[5]>>6);  //到这里42位已经完全填满到了result_7[13]

	unsigned char v_name[16];
	memcpy(v_name,vessel_name,vessel_name.GetLength());
	for(int i=0;i<15;i++)
		result_7[i+14]=v_name[i];   //由于刚好有120个字符，又刚好到了result_7[13]填满，所以直接赋值即可

	if(!ship_type.IsEmpty())    //当此字段不存在时，默认为0，当有值时，是一个<127的数，所以直接赋值即可
		result_7[29]+=(_ttoi(ship_type));

	unsigned int d_bow=_ttoi(dimension_bow);  //总有九位
	result_7[30]+=(d_bow>>1);
	if((d_bow & 0x00000001)==1)  //由于这里当最后一位是0时什么都不做，所以没用逗号表达式
		result_7[31]+=128;       //result[31]还有7位没有填充

	unsigned int d_stern=_ttoi(dimension_stern);//共有9位：7+2
	result_7[31]+=(d_stern>>2);
	result_7[32]=(result_7[32]^(d_stern & 0x00000003))<<6;  //result_7[32]还有6位木有填满

	result_7[32]+=(_ttoi(dimension_port));  //dimension_port刚好六位，所以刚好填满 result_7[32];

	result_7[33]=(result_7[33]^(_ttoi(dimension_start)))<<2;  //result_7[33]还有两位没有填满,还可以: result_7[33]=(result_7[33]+(_ttoi(dimension_start)))<<2;

	if(!pos_fix_type.IsEmpty())
	{
		unsigned int epfd_num=_ttoi(pos_fix_type);
		result_7[33]+=(epfd_num & 0x0000000c);
		result_7[34]=(result_7[34]^(epfd_num & 0x00000003))<<6;  //result_7[34]只填充了两位
	}

	if(!eta_month.IsEmpty())
	{
		unsigned int eta_month_num=_ttoi(eta_month);
		result_7[34]+=(eta_month_num<<2);    //result_7[34]还有两位没有填满
	}

	if(!eta_day.IsEmpty())
	{
		unsigned int eta_day_num=_ttoi(eta_day);
		result_7[34]+=((eta_day_num &0x00000018)>>3);  //result_7[34]已经填满，但是 eat_day还有三位需要填充
		result_7[35]=(result_7[35]^(eta_day_num & 0x00000007))<<5;  //result_7[35]还有5位没有填满，eta_day已填完
	}
	if(!eta_hour.IsEmpty())
		result_7[35]+=(_ttoi(eta_hour));    //result_7[35]已经填满

	if(!eta_minute.IsEmpty())
	{
		result_7[36]+=(_ttoi(eta_minute));
		result_7[36]=result_7[36]<<2;        //result_7[36]还有两位没有填满
	}

	unsigned int draught_num=_ttoi(draught);
	result_7[36]+=((draught_num &0x000000c0)>>6);
	result_7[37]+=(draught_num &0x0000003f);
	result_7[37]=result_7[37]<<2;  //result_7[37]还有两位没有填满   


	unsigned char destination_name[16];
	memcpy(destination_name,destination,destination.GetLength());
	for(int j=0;j<15;j++)
	{
		result_7[37+j]+=(destination_name[j]>>6);
		result_7[38+j]=result_7[38+j]^(destination_name[j] & 0xfc);

	}
	if(DTE.IsEmpty())
		result_7[52]+=2;
	//return result_7;
}
