#pragma once


// CWaterColorSettingDlg �Ի���

class CWaterColorSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaterColorSettingDlg)

public:
	CWaterColorSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWaterColorSettingDlg();

// �Ի�������
	enum { IDD = IDD_WATER_COLOR_SETTING_DLG };
private:
	CColorDialog m_ColorSel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧�� 
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonColorVs();
	afx_msg void OnBnClickedButtonColorMs();
	afx_msg void OnBnClickedButtonColorMd();
	afx_msg void OnBnClickedButtonColorDw();
	afx_msg void OnBnClickedButtonApply();
	int m_VsR;
	int m_VsG;
	int m_VsB;		
	int m_MsR;
	int m_MsG;
	int m_MsB;
	int m_MdR;
	int m_MdG;
	int m_MdB;
	int m_DwR;
	int m_DwG;
	int m_DwB;
};