
// ExamRectMouseMoveDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ExamRectMouseMove.h"
#include "ExamRectMouseMoveDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamRectMouseMoveDlg 대화 상자



CExamRectMouseMoveDlg::CExamRectMouseMoveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMRECTMOUSEMOVE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_rect1.SetRect(10, 10, 100, 100);
	m_rect2.SetRect(110, 110, 200, 200);
	m_rect3.SetRect(210, 210, 300, 300);
}

void CExamRectMouseMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExamRectMouseMoveDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CExamRectMouseMoveDlg 메시지 처리기

BOOL CExamRectMouseMoveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamRectMouseMoveDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic()) // 최소화가 되었을 경우
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		dc.Rectangle(m_rect1);
		dc.Rectangle(m_rect2);
		dc.Rectangle(m_rect3);
		/*CDialogEx::OnPaint();*/
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExamRectMouseMoveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExamRectMouseMoveDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*if (point.x >= m_rect.left && point.y >= m_rect.top &&
		point.x <= m_rect.right && point.y <= m_rect.bottom) {*/
	if (m_rect1.PtInRect(point)) m_is_clicked = 1;// 사각형 안에 점이 있느냐 체크해주는 함수
	else if (m_rect2.PtInRect(point)) m_is_clicked = 2;
	else if (m_rect3.PtInRect(point)) m_is_clicked = 3;
	

	if(m_is_clicked){
		 // 사각형이 클릭되었다고 알리는 flag
		m_prev_pos = point;
		SetCapture(); // 마우스 커서가 내 client 영역을 넘어가도 계속 마우스 메시지를 나한테 달라.
						// 이 함수 쓰면 반드시 빠지는 부분에서 ReleaseCapture 할것.
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CExamRectMouseMoveDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_is_clicked)
	{
		m_is_clicked = 0;
		ReleaseCapture();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CExamRectMouseMoveDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_is_clicked)
	{
		CPoint move_pos = point - m_prev_pos; // 클래스 내 연산자 오버로딩되어있음
		/*
		CPoint move_pos;
		move_pos.x = point.x = m_prev_pos.x;
		move_pos.y = point.y = m_prev_pos.y;
		*/

		if (m_is_clicked == 1)
		{
			m_rect1 += move_pos; // 클래스 내 연산자 오버로딩되어있음
								// 마우스 이동거리만큼 사각형을 이동한다.

			CRect r;

			if (r.IntersectRect(m_rect1, m_rect2) || r.IntersectRect(m_rect1, m_rect3))
			{
				m_rect1 = m_rect1 - move_pos;
			}
		}

		if (m_is_clicked == 2)
		{
			m_rect1 += move_pos; // 클래스 내 연산자 오버로딩되어있음
								// 마우스 이동거리만큼 사각형을 이동한다.

			CRect r;

			if (r.IntersectRect(m_rect2, m_rect1) || r.IntersectRect(m_rect2, m_rect3))
			{
				m_rect2 = m_rect2 - move_pos;
			}
		}

		if (m_is_clicked == 3)
		{
			m_rect1 += move_pos; // 클래스 내 연산자 오버로딩되어있음
								// 마우스 이동거리만큼 사각형을 이동한다.
			CRect r;

			if (r.IntersectRect(m_rect3, m_rect1) || r.IntersectRect(m_rect3, m_rect2))
			{
				m_rect3 = m_rect3 - move_pos;
			}
		}
		
		
		/*
		m_rect.left += move_pos.x;
		m_rect.top += move_pos.y;
		m_rect.right += move_pos.x;
		m_rect.bottom += move_pos.y;
		*/

		m_prev_pos = point; // 현재점이 이후의 작업에서 이전점이 되야하니까.

		Invalidate();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
