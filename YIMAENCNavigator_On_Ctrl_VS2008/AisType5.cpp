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
	// CString ais_version; �����ĵ���˵  1-3=future editions�����԰��� ITU1371 ����ֶ��ݲ�����
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
	// CString spare���ĵ��ϣ����� not used���������ﲻ�ã�


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
	result_7[0]=(result_7[0]^_ttoi(mgs_type))<<2;  //��message_type��resul_7t[0]���룬Ȼ��������λ
	if(!repeat_indicator.IsEmpty())                 //����ǿգ�����Ҫ��6-7����repeat indicator�ֶΣ����Ϊ�գ����ùܣ�Ĭ����0��
	{
		result_7[0]=result_7[0] ^(_ttoi(repeat_indicator));
	}

	unsigned int mmsi_num=_ttoi(mmsi);              //�˴�����Ϊunsigned����Ȼ����λ�ǻ���ָ�����unsigned֮��������λ�����λ�Ƿ�Ϊ1�������������Դ�
	result_7[1]= result_7[1]^(mmsi_num>>22);
	result_7[2]= result_7[2]^((mmsi_num<<10)>>24);
	result_7[3]= result_7[3]^((mmsi_num<<18)>>24);
	result_7[4]= (result_7[4]^(mmsi_num &0x0000003f))<<2;  //����Ϊ��������Ĳ�ͬ������ ��ķ�ʽ��ȡ������λ

	unsigned imo_num=_ttoi(imo);   //��result_7[5]��ʼ
	result_7[5]=result_7[5]^(imo_num>>22);
	result_7[6]=result_7[6]^((imo_num<<10)>>24);
	result_7[7]=result_7[7]^((imo_num<<18)>>24);
	result_7[8]=(result_7[8]^(imo_num & 0x0000003f))<<2;  //������result_7[8]������λû������
	//����Ҫ��������⣬��δ�CStringתΪchar[]
	char c_sign[6];
	memcpy(c_sign,call_sign,call_sign.GetLength());
	result_7[8]=result_7[8]+(c_sign[0]>>6);  //��Ҫ��֤���ܲ���ֱ�Ӽ��ϣ�c_sign�ĸ���λ��ɵ���
	result_7[9]=(result_7[9]^(c_sign[0] & 0x3f))<<2;
	result_7[9]=result_7[9]+(c_sign[1]>>6);
	result_7[10]=(result_7[10]^(c_sign[1] & 0x3f))<<2;
	result_7[10]=result_7[10]+(c_sign[2]>>6);
	result_7[11]=(result_7[11]^(c_sign[2] & 0x3f))<<2;
	result_7[11]=result_7[11]+(c_sign[3]>>6);
	result_7[12]=(result_7[12]^(c_sign[3] & 0x3f))<<2;
	result_7[12]=result_7[12]+(c_sign[4]>>6);
	result_7[13]=(result_7[13]^(c_sign[4] & 0x3f))<<2;
	result_7[13]=result_7[13]+(c_sign[5]>>6);  //������42λ�Ѿ���ȫ��������result_7[13]

	unsigned char v_name[16];
	memcpy(v_name,vessel_name,vessel_name.GetLength());
	for(int i=0;i<15;i++)
		result_7[i+14]=v_name[i];   //���ڸպ���120���ַ����ָպõ���result_7[13]����������ֱ�Ӹ�ֵ����

	if(!ship_type.IsEmpty())    //�����ֶβ�����ʱ��Ĭ��Ϊ0������ֵʱ����һ��<127����������ֱ�Ӹ�ֵ����
		result_7[29]+=(_ttoi(ship_type));

	unsigned int d_bow=_ttoi(dimension_bow);  //���о�λ
	result_7[30]+=(d_bow>>1);
	if((d_bow & 0x00000001)==1)  //�������ﵱ���һλ��0ʱʲô������������û�ö��ű���ʽ
		result_7[31]+=128;       //result[31]����7λû�����

	unsigned int d_stern=_ttoi(dimension_stern);//����9λ��7+2
	result_7[31]+=(d_stern>>2);
	result_7[32]=(result_7[32]^(d_stern & 0x00000003))<<6;  //result_7[32]����6λľ������

	result_7[32]+=(_ttoi(dimension_port));  //dimension_port�պ���λ�����Ըպ����� result_7[32];

	result_7[33]=(result_7[33]^(_ttoi(dimension_start)))<<2;  //result_7[33]������λû������,������: result_7[33]=(result_7[33]+(_ttoi(dimension_start)))<<2;

	if(!pos_fix_type.IsEmpty())
	{
		unsigned int epfd_num=_ttoi(pos_fix_type);
		result_7[33]+=(epfd_num & 0x0000000c);
		result_7[34]=(result_7[34]^(epfd_num & 0x00000003))<<6;  //result_7[34]ֻ�������λ
	}

	if(!eta_month.IsEmpty())
	{
		unsigned int eta_month_num=_ttoi(eta_month);
		result_7[34]+=(eta_month_num<<2);    //result_7[34]������λû������
	}

	if(!eta_day.IsEmpty())
	{
		unsigned int eta_day_num=_ttoi(eta_day);
		result_7[34]+=((eta_day_num &0x00000018)>>3);  //result_7[34]�Ѿ����������� eat_day������λ��Ҫ���
		result_7[35]=(result_7[35]^(eta_day_num & 0x00000007))<<5;  //result_7[35]����5λû��������eta_day������
	}
	if(!eta_hour.IsEmpty())
		result_7[35]+=(_ttoi(eta_hour));    //result_7[35]�Ѿ�����

	if(!eta_minute.IsEmpty())
	{
		result_7[36]+=(_ttoi(eta_minute));
		result_7[36]=result_7[36]<<2;        //result_7[36]������λû������
	}

	unsigned int draught_num=_ttoi(draught);
	result_7[36]+=((draught_num &0x000000c0)>>6);
	result_7[37]+=(draught_num &0x0000003f);
	result_7[37]=result_7[37]<<2;  //result_7[37]������λû������   


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