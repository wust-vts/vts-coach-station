#pragma once


// CGetDepInfoDlg �Ի���

class CGetDepInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetDepInfoDlg)

public:
	CGetDepInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetDepInfoDlg();

// �Ի�������
	enum { IDD = IDD_GET_DEP_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	int m_iMemMapPos;
	int m_iMemMapCount;
	CString m_strCurMapName;
	CString m_strDepcntInfo;
	CString m_strCoalneInfo;
};