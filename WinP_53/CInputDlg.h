﻿#pragma once
#include "afxdialogex.h"


// CInputDlg 대화 상자

class CInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nX;
	int m_nY;
	CString m_strText;
	CComboBox m_cbColor;
	afx_msg void OnSelchangeComboColor();
	virtual BOOL OnInitDialog();
};