#include "StdAfx.h"
#include "AisType1.h"
#include "math.h"
CAisType1::CAisType1(void)
{
}

CAisType1::~CAisType1(void)
{
}
CAisType1::CAisType1(CString str)
{
	this->str=str;
 }
void CAisType1::message1_parse_encode(CString &str,unsigned char *result)
{

	CString message_type;
	CString repeat_indicator;
	CString mmsi;
	CString navigetion_status;
	CString ROT;
	CString SOG;
	CString position_accuracy;
	CString longitude;
	CString latitude;
	CString COG;
	CString HDG;
	CString time_stamp;
	CString maneuver_indicator;
	CString spare;
	CString raim_flag;
	CString radio_status;
	//return (_T("ok"));
	AfxExtractSubString(message_type,str,0,',');
	AfxExtractSubString(repeat_indicator,str,1,',');
	AfxExtractSubString(mmsi,str,2,',');
	AfxExtractSubString(navigetion_status,str,3,',');
	AfxExtractSubString(ROT,str,4,',');
	AfxExtractSubString(SOG,str,5,',');
	AfxExtractSubString(position_accuracy,str,6,',');
	AfxExtractSubString(longitude,str,7,',');
	AfxExtractSubString(latitude,str,8,',');
	AfxExtractSubString(COG,str,9,',');
	AfxExtractSubString(HDG,str,10,',');
	AfxExtractSubString(time_stamp,str,11,',');
	AfxExtractSubString(maneuver_indicator,str,12,',');
	AfxExtractSubString(spare,str,13,',');
	AfxExtractSubString(raim_flag,str,14,',');
	AfxExtractSubString(radio_status,str,15,',');
	//unsigned char result[22];

	memset(result,0,sizeof(result));


	result[0]=(result[0]^_ttoi(message_type))<<2;  //��message_type��result[0]�����Ȼ��������λ
	if(!repeat_indicator.IsEmpty())                 //����ǿգ�����Ҫ��6-7����repeat indicator�ֶΣ����Ϊ�գ����ùܣ�Ĭ����0��
	{
		result[0]=result[0] ^(_ttoi(repeat_indicator));
	}
	//Ĭ�������128��û��д
	//������int  ����char�ڼ�����ڲ�������2 ���ƴ��ڣ������ڴ˴�����ֱ����int��ʹ��һλ����
	unsigned int mmsi_num=_ttoi(mmsi);              //�˴�����Ϊunsigned����Ȼ����λ�ǻ���ָ�����unsigned֮��������λ�����λ�Ƿ�Ϊ1�������������Դ�
	result[1]= result[1]^(mmsi_num>>22);
	result[2]= result[2]^((mmsi_num<<10)>>24);
	result[3]= result[3]^((mmsi_num<<18)>>24);
	result[4]= (result[4]^(mmsi_num & 0x0000003f ))<<2;   //Ϊ�����������뽫ĳһ��ǰ��Ĳ���ȫ����Ϊ0��Ȼ���Ƴ��öκ���Ĳ��֣���ʱresult[4]�ĵ���λ����Ҫ�����ƶ�2λ
	unsigned  int navi_status=_ttoi(navigetion_status);
	//navi_status = navi_status & 0x0000000f;			//����״̬��Χ0-15(4λ)
	result[4]= result[4]^(navi_status>>2);
	result[5]= (result[5]^ (navi_status & 0x03))<<6;


	//signed char ROT_num=(unsigned char)_ttoi(ROT);   //�����ĵ�˵����ROT��һ��signed integer,���Ե���С��0ʱ��Ӧ��ʹ�ò���
	//if(ROT_num<0)  
	//{//�����Ƿ���λ���䣬����λȡ����Ȼ���1,�պ�signed char��ȡֵ��Χ��-128-127
	//	ROT_num =ROT_num ^0x7f;     //��011111111���ֻ�����ܱ��ַ���λ���䣬����λȡ��
	//	ROT_num++;   
	//}//����1����
	//result[5]=result[5]^(ROT_num>>2); //���ﻹ�����⣡
	//result[6]=(result[6]^(ROT_num & 0x03))<<6;  //��0x03���ֻ�����������λ��Ȼ�������֮����������6λ

	/*
	int ROT_num=_ttoi(ROT);
	if(ROT_num<0)
	{
		result[5]=result[5]+32;
		ROT_num=abs(ROT_num);

	}
	float rot_temp=sqrt((float)ROT_num);  //����sqrt���������غ������������������ʾת��
	rot_temp=rot_temp*4.733;   //����֮�����4.733
	ROT_num=(int)(rot_temp+0.5);
	result[5]+=(ROT_num>>3);
	result[6]=(result[6]^(ROT_num & 0x00000003))<<6;
	*/
	int ROT_num = _ttoi(ROT);
	//ת����ֻ��8λ������ȡ����
	if (ROT_num < 0)
	{
		ROT_num += 256;
	}
	result[5]^= ((ROT_num>>2) & 0x0000003f);
	result[6]=(result[6]^(ROT_num & 0x00000003))<<6;



	unsigned int SOG_num=_ttoi(SOG);
	result[6]=result[6]^(SOG_num>>4);
	result[7]=(result[7]^(SOG_num & 0x00F))<<4;  //��0x0f��֮��ֻ���������4λ��Ȼ�������֮����������4λ
	if(_ttoi(position_accuracy)==1)
	{
		result[7]=result[7]+8;
	}
	//bool East=false;
	unsigned int pos_longtitude=0;
	//��ȡ����
	pos_longtitude=titude_parse(longitude, false);
	//if(East)
	//	result[7]=result[7]+4;
	result[7]=result[7]^(pos_longtitude>>25);
	result[8]=result[8]^((pos_longtitude<<7)>>24);
	result[9]=result[9]^((pos_longtitude<<15)>>24);
	result[10]=result[10]^((pos_longtitude<<23)>>24);
	result[11]=(result[11]^(pos_longtitude & 0x00000001))<<7;//ǰ�ڴ���������д����&&���������߼�����

	//bool North=false;
	unsigned int pos_latitude=0;
	//��ȡ����
	pos_latitude=titude_parse(latitude, false);
	//if (North)
	//	result[11]=result[11]+64;
	//result[11]=(result[11]^(pos_latitude<<6))>>26;
	result[11] = result[11] ^ ((pos_latitude >> 20) & 0x0000007f);
	//result[12]=(result[11]^(pos_latitude<<12))>>24;
	result[12]=result[12]^(pos_latitude >> 12);
	//result[13]=(result[11]^(pos_latitude<<20))>>24;
	result[13]=(result[13]^(pos_latitude >> 4));
	//result[14]= result[14]^(pos_latitude & 0x0000000F)<<4;  //result[14]ֻ����4λ
	result[14]= result[14]^(pos_latitude & 0x0000000F)<<4;  //result[14]ֻ����4λ

	unsigned int COG_num=0;
	if(COG.IsEmpty())
		COG_num=3600;
	else COG_num=_ttoi(COG);
	result[14]=result[14]^(COG_num>>8);   
	result[15]=result[15]^(COG_num & 0x000000FF);

	unsigned int HDG_num=0;
	if(HDG.IsEmpty())
		HDG_num=511;
	else  HDG_num=_ttoi(HDG);
	result[16]=result[16]^(HDG_num>>1);
	result[17]=(result[17]^ (HDG_num & 0x00000001))<<7;

	unsigned int time_stamp_num=_ttoi(time_stamp);
	result[17]=result[17]^ (time_stamp_num<<1);  //�����������Ҫtime_stamp_num��λȻ��������

	unsigned int maneuver_indicator_num=_ttoi(maneuver_indicator);
	/*if(maneuver_indicator_num==1)
	result[18]=result[18]+128;
	else if(maneuver_indicator_num==2)
	result[17]++;
	else if(maneuver_indicator_num==3)
	{
	result[17]++;
	result[18]=result[18]+128;

	}*/
	result[17]=result[17]+(maneuver_indicator_num>>3);    //����maneuver_indicator_numֻ����λ������ֱ������3λ����

	result[18]=(result[18]^ (maneuver_indicator_num & 0x00000007))<<5;

	if(_ttoi(spare)==1)
		result[18]=result[18]+16;
	if(_ttoi(raim_flag)==1)
		result[18]=result[18]+8;

	//return result;//�˴���Ҫ��result[]תΪCString
	//mainstr.Format("%s", result);  

}
unsigned int  CAisType1::titude_parse(CString  &titude, bool position)
{

	unsigned int lontitude=0;
	int po_num=titude.Find(':');
	CString substring=titude.Mid(po_num+1);
	lontitude=_ttoi(substring);   //���⣺���ͨ��lontitude�ж��Ƕ�����������������γ���Ǳ�γ
	return lontitude;
}