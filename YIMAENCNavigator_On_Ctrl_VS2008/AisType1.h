#pragma once

class CAisType1
{
public:
	CString str;
	CAisType1(void);
	CAisType1(CString str);
	~CAisType1(void);

	void CAisType1::message1_parse_encode(CString  &str,unsigned char *result);//����Ϣ��䵽��λ��unsigned char ������
	unsigned int  CAisType1::titude_parse(CString  &titude, bool position);  //�Ӿ�γ����Ϣ�н�������γ��
};