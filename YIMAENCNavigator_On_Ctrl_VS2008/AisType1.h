#pragma once

class CAisType1
{
public:
	CString str;
	CAisType1(void);
	CAisType1(CString str);
	~CAisType1(void);

	void CAisType1::message1_parse_encode(CString  &str,unsigned char *result);//将信息填充到八位的unsigned char 数组里
	unsigned int  CAisType1::titude_parse(CString  &titude, bool position);  //从经纬度信息中解析出经纬度
};
