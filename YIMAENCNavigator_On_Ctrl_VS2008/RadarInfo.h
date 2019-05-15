#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <string>

using namespace std;

class RadarInfo
{
private:
	CString op;				//������
	CString id;				//���
	CString ip;				//IP
	short port;				//Port
	double lon;				//����
	double lan;				//γ��
	double height;			//�߶�
	double range;			//����
	double level;			//ˮƽ��߶�

public:
	long radInnerLayerPos;		//�״������ͼ���е�����
public:
	RadarInfo();
	~RadarInfo();
};