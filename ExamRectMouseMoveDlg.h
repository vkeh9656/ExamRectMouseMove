
// ExamRectMouseMoveDlg.h: 헤더 파일
//

#pragma once


// CExamRectMouseMoveDlg 대화 상자
class CExamRectMouseMoveDlg : public CDialogEx
{
private:
	CRect m_rect1, m_rect2, m_rect3;
	char m_is_clicked = 0;
	CPoint m_prev_pos;

	CRgn m_star_region, m_ellipse_region;
	CBrush m_fill_brush;
	CRgn m_temp_region; // 영역 비교용 region

// 생성입니다.
public:
	CExamRectMouseMoveDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMRECTMOUSEMOVE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
