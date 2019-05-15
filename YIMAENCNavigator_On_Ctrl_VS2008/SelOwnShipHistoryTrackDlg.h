#pragma once
#include "afxdtctl.h"


// CSelOwnShipHistoryTrackDlg �Ի���

class CSelOwnShipHistoryTrackDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelOwnShipHistoryTrackDlg)

public:
	CSelOwnShipHistoryTrackDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelOwnShipHistoryTrackDlg();

// �Ի�������
	enum { IDD = IDD_SEL_OWN_SHIP_HISTORY_TRACK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	TrackPoint m_arrTrackPoints[5000];
	M_TIME m_mHistoryTrackStartTime;
	int m_iCurTrackCount;
	int m_iLinePos;
	afx_msg void OnBnClickedOk();
	CString m_strMsg;
	CDateTimeCtrl m_dtStartTime;
	COleDateTime m_startDate;
	COleDateTime m_startTimeMini;
	CDateTimeCtrl m_dtEndTime;
	COleDateTime m_endDate;
	COleDateTime m_endTimeMini;
	afx_msg void OnBnClickedButtonSel();
	afx_msg void OnBnClickedButtonDrawInMap();
};