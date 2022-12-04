
// dDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "d.h"
#include "dDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BLOCKWIDTH 20
#define BLOCKHEIGHT 20
#define WIDTH 600
#define HEIGHT 600
#define OFFSET CPoint(pos.x,pos.y) //좌표계 중간점
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdDlg 대화 상자



CdDlg::CdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CdDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CdDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ERASE, &CdDlg::OnBnClickedBtnErase)
	ON_BN_CLICKED(IDC_BTN_ALLDELETE, &CdDlg::OnBnClickedBtnAlldelete)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CdDlg::OnBnClickedButtonColor)
	ON_BN_CLICKED(IDC_BTNSAVE, &CdDlg::OnBnClickedBtnsave)
	ON_BN_CLICKED(IDC_BTNLOAD, &CdDlg::OnBnClickedBtnload)
END_MESSAGE_MAP()


// CdDlg 메시지 처리기

BOOL CdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	PresentState = State::CREATE;
	CRect m_rect;
	this->GetWindowRect(m_rect);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);

	
		// 전체 화면의 중앙값
		pos.x = GetSystemMetrics(SM_CXSCREEN) / 2.0f - rect.Width() / 2.0f;
		pos.y = GetSystemMetrics(SM_CYSCREEN) / 2.0f - rect.Height() / 2.0f;


		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//한 칸 길이는 20
		//가로, 세로 전체 길이는 20*30=600
		dc=new CPaintDC(this);
		for (int y = 0; y < 30; y++)
			for (int x = 0; x < 30; x++)
				dc->Rectangle((1 + x) * BLOCKWIDTH, (1 + y) * BLOCKWIDTH, (BLOCKWIDTH * (x + 2)) + 1, (BLOCKWIDTH * (y + 2)) + 1);
		CDC MemDC;
		MemDC.CreateCompatibleDC(dc);
		CBitmap image;
		image.LoadBitmap(IDB_IMAGE);
		CBitmap* oldImage = MemDC.SelectObject(&image);
		dc->BitBlt(20, 20, 620, 620, &MemDC, 30, 40, SRCAND);
		dc->SelectObject(oldImage);
		

		rdc = new CClientDC(this);
		dotimage.Create(600, 400, 24);


	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdDlg::OnLButtonDown(UINT nFlags, CPoint point) // 왼쪽 마우스 버튼 콜백함수
{
	
	if (point.x > WIDTH+20 || point.x < 20) return;
	if (point.y> HEIGHT+20 || point.y <20 ) return;
	CPoint temp = ConvertGlobalCoorToBlockCoor(point);
	CPoint temp2 = ConvertBlockCoorToGlobalCoor(temp);
	
	CBrush brush;
	brush.CreateSolidBrush(m_color);
	CBrush* oldBrush = rdc->SelectObject(&brush);


	if (PresentState==State::CREATE) {
		/*CString str;
		str.Format(_T("%d %d"), temp.x, temp.y);
		dc.TextOut(300,500,str);*/
		
		if (blockData[temp.x-301][temp.y-301] != 1) {
			createBlock(temp.x-301, temp.y-301, NULL);
			rdc->Rectangle(temp2.x - 10, temp2.y - 10, temp2.x + 10, temp2.y + 10);
		}
	}
	else if (PresentState == State::ERASE) {
		if (blockData[temp.x - 301][temp.y - 301] == 1) {
			deleteBlock(temp.x - 301, temp.y - 301);
			
			//dc.Rectangle(temp2.x - 10, temp2.y - 10, temp2.x + 10, temp2.y + 10);
			
		}

	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CdDlg::createBlock(int x, int y, CString color) //블럭 생성 함수
{
	blockData[x][y] = 1;
	blockColor[x][y] = m_color;
}

void CdDlg::deleteBlock(int x, int y) //블록 제거 함수
{
	blockData[x][y] = 0;
}

CPoint CdDlg::ConvertGlobalCoorToBlockCoor(CPoint GlobalCoor) //좌표계 변환 함수(전역 -> 블록)
{
	CPoint newpos;

	CPoint Origin = OFFSET - CPoint((BLOCKWIDTH * WIDTH) / 2, (BLOCKHEIGHT * HEIGHT) / 2) + CPoint(BLOCKWIDTH/2, BLOCKHEIGHT/2); 
	CPoint delta = GlobalCoor - Origin;
	newpos = CPoint((int)(delta.x/BLOCKWIDTH+0.5), (int)(delta.y/BLOCKHEIGHT+0.5));
	return newpos;
}

CPoint CdDlg::ConvertBlockCoorToGlobalCoor(CPoint BlockCoor) //좌표계 변환 함수(블록 -> 전역)
{
	CPoint globalpos;

	CPoint Origin = OFFSET - CPoint((BLOCKWIDTH * WIDTH) / 2, (BLOCKHEIGHT * HEIGHT) / 2) + CPoint(BLOCKWIDTH / 2, BLOCKHEIGHT / 2);
	return Origin + CPoint(BLOCKWIDTH * BlockCoor.x, BLOCKHEIGHT * BlockCoor.y);
}


void CdDlg::OnBnClickedBtnDraw() //그리기 버튼 콜백
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PresentState = State::CREATE;
}


void CdDlg::OnBnClickedBtnErase() // 지우기 버튼 콜백
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PresentState = State::ERASE;
}


void CdDlg::OnBnClickedBtnAlldelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate(TRUE);
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			blockData[i][j] = 0;
		}
	}
}


void CdDlg::OnBnClickedButtonColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog colorDlg(RGB(0, 0, 0));
	if (colorDlg.DoModal() == IDOK)
	{
		m_color = colorDlg.GetColor();
	}
}


void CdDlg::OnBnClickedBtnsave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CDC* temp = CDC::FromHandle(dotimage.GetDC());
	CPen* oldPen, pen;
	
	temp->Rectangle(20, 20, 620, 620);

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (blockData[i][j] == 1) {
				CBrush brush;
				brush.CreateSolidBrush(blockColor[i][j]);
				CBrush* oldBrush = temp->SelectObject(&brush);
				

				pen.CreatePen(PS_SOLID, 1, blockColor[i][j]);
				oldPen = temp->SelectObject(&pen);
				

				CPoint temp2 = ConvertBlockCoorToGlobalCoor(CPoint(i+301,j+301));
				temp->Rectangle(temp2.x - 10, temp2.y - 10, temp2.x + 10, temp2.y + 10);
				brush.DeleteObject();
				pen.DeleteObject();
			}
		}
	}
	
	ReleaseDC(rdc);
	dotimage.ReleaseDC();
	

	dotimage.Save(TEXT("DottedImage.jpg"));
	dotimage.Destroy();
	MessageBox(_T("저장 완료"));
	OnOK();
}


void CdDlg::OnBnClickedBtnload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
