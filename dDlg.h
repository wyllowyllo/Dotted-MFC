
// dDlg.h: 헤더 파일
//

#pragma once

#define SAVEPATH "C:/Users\sea51/Documents/GitHub\Dotted-MFC/res"

enum class State { //생성 or 삭제
	CREATE, ERASE
};

// CdDlg 대화 상자
class CdDlg : public CDialogEx
{
// 생성입니다.
public:
	CdDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CPaintDC* dc;
	COLORREF m_color;
	CClientDC* rdc;
	CImage dotimage;
	CString strPathName;
	boolean imageLoad = false;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void createBlock(int x, int y, CString color);
	void deleteBlock(int x, int y);
	CPoint pos;
	CPoint ConvertGlobalCoorToBlockCoor(CPoint GlobalCoor);
	CPoint ConvertBlockCoorToGlobalCoor(CPoint BlockCoor);
	int blockData[30][30] = { 0 }; //각 칸의 블록 데이터
	COLORREF blockColor[30][30];
	State PresentState;

	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnErase();
	afx_msg void OnBnClickedBtnAlldelete();
	afx_msg void OnBnClickedButtonColor();
	afx_msg void OnBnClickedBtnsave();
	afx_msg void OnBnClickedBtnload();
};
