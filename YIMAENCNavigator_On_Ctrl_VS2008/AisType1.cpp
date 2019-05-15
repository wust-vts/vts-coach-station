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


	result[0]=(result[0]^_ttoi(message_type))<<2;  //将message_type和result[0]相异或，然后左移两位
	if(!repeat_indicator.IsEmpty())                 //如果非空，则需要在6-7加上repeat indicator字段，如果为空，则不用管（默认是0）
	{
		result[0]=result[0] ^(_ttoi(repeat_indicator));
	}
	//默认情况下128还没有写
	//无论是int  还是char在计算机内部都是以2 进制存在，所以在此处可以直接在int上使用一位操作
	unsigned int mmsi_num=_ttoi(mmsi);              //此处必须为unsigned，不然在移位是会出现负数，unsigned之后无论移位后最高位是否为1，都当做正数对待
	result[1]= result[1]^(mmsi_num>>22);
	result[2]= result[2]^((mmsi_num<<10)>>24);
	result[3]= result[3]^((mmsi_num<<18)>>24);
	result[4]= (result[4]^(mmsi_num & 0x0000003f ))<<2;   //为了能异或，则必须将某一段前面的部分全部设为0，然后移除该段后面的部分，此时result[4]的低四位还需要往上移动2位
	unsigned  int navi_status=_ttoi(navigetion_status);
	//navi_status = navi_status & 0x0000000f;			//导航状态范围0-15(4位)
	result[4]= result[4]^(navi_status>>2);
	result[5]= (result[5]^ (navi_status & 0x03))<<6;


	//signed char ROT_num=(unsigned char)_ttoi(ROT);   //根据文档说明，ROT是一个signed integer,所以当它小于0时，应该使用补码
	//if(ROT_num<0)  
	//{//补码是符号位不变，其它位取反，然后加1,刚好signed char的取值范围是-128-127
	//	ROT_num =ROT_num ^0x7f;     //与011111111异或只有则能保持符号位不变，其它位取反
	//	ROT_num++;   
	//}//最后加1操作
	//result[5]=result[5]^(ROT_num>>2); //这里还有问题！
	//result[6]=(result[6]^(ROT_num & 0x03))<<6;  //与0x03与后，只保留了最后两位，然后再异或，之后再往上移6位

	/*
	int ROT_num=_ttoi(ROT);
	if(ROT_num<0)
	{
		result[5]=result[5]+32;
		ROT_num=abs(ROT_num);

	}
	float rot_temp=sqrt((float)ROT_num);  //由于sqrt有两个重载函数，所以这里必须显示转换
	rot_temp=rot_temp*4.733;   //开方之后乘以4.733
	ROT_num=(int)(rot_temp+0.5);
	result[5]+=(ROT_num>>3);
	result[6]=(result[6]^(ROT_num & 0x00000003))<<6;
	*/
	int ROT_num = _ttoi(ROT);
	//转向率只有8位，负数取补码
	if (ROT_num < 0)
	{
		ROT_num += 256;
	}
	result[5]^= ((ROT_num>>2) & 0x0000003f);
	result[6]=(result[6]^(ROT_num & 0x00000003))<<6;



	unsigned int SOG_num=_ttoi(SOG);
	result[6]=result[6]^(SOG_num>>4);
	result[7]=(result[7]^(SOG_num & 0x00F))<<4;  //与0x0f与之后，只保留了最后4位，然后再异或，之后再往上移4位
	if(_ttoi(position_accuracy)==1)
	{
		result[7]=result[7]+8;
	}
	//bool East=false;
	unsigned int pos_longtitude=0;
	//获取补码
	pos_longtitude=titude_parse(longitude, false);
	//if(East)
	//	result[7]=result[7]+4;
	result[7]=result[7]^(pos_longtitude>>25);
	result[8]=result[8]^((pos_longtitude<<7)>>24);
	result[9]=result[9]^((pos_longtitude<<15)>>24);
	result[10]=result[10]^((pos_longtitude<<23)>>24);
	result[11]=(result[11]^(pos_longtitude & 0x00000001))<<7;//前期错误，在这里写成了&&结果变成了逻辑运算

	//bool North=false;
	unsigned int pos_latitude=0;
	//获取补码
	pos_latitude=titude_parse(latitude, false);
	//if (North)
	//	result[11]=result[11]+64;
	//result[11]=(result[11]^(pos_latitude<<6))>>26;
	result[11] = result[11] ^ ((pos_latitude >> 20) & 0x0000007f);
	//result[12]=(result[11]^(pos_latitude<<12))>>24;
	result[12]=result[12]^(pos_latitude >> 12);
	//result[13]=(result[11]^(pos_latitude<<20))>>24;
	result[13]=(result[13]^(pos_latitude >> 4));
	//result[14]= result[14]^(pos_latitude & 0x0000000F)<<4;  //result[14]只用了4位
	result[14]= result[14]^(pos_latitude & 0x0000000F)<<4;  //result[14]只用了4位

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
	result[17]=result[17]^ (time_stamp_num<<1);  //在这里必须先要time_stamp_num移位然后才能异或

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
	result[17]=result[17]+(maneuver_indicator_num>>3);    //由于maneuver_indicator_num只有四位，所以直接右移3位即可

	result[18]=(result[18]^ (maneuver_indicator_num & 0x00000007))<<5;

	if(_ttoi(spare)==1)
		result[18]=result[18]+16;
	if(_ttoi(raim_flag)==1)
		result[18]=result[18]+8;

	//return result;//此处需要将result[]转为CString
	//mainstr.Format("%s", result);  

}
unsigned int  CAisType1::titude_parse(CString  &titude, bool position)
{

	unsigned int lontitude=0;
	int po_num=titude.Find(':');
	CString substring=titude.Mid(po_num+1);
	lontitude=_ttoi(substring);   //问题：如何通过lontitude判断是东经还是西经或者南纬还是北纬
	return lontitude;
}
