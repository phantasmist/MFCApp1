
// MFCApp1View.h: CMFCApp1View 클래스의 인터페이스
//

#pragma once


class CMFCApp1View : public CEditView
{
protected: // serialization에서만 만들어집니다.
	CMFCApp1View() noexcept;
	DECLARE_DYNCREATE(CMFCApp1View)

// 특성입니다.
public:
	CMFCApp1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApp1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMnZoomin();
	afx_msg void OnMnZoomout();
};

#ifndef _DEBUG  // MFCApp1View.cpp의 디버그 버전
inline CMFCApp1Doc* CMFCApp1View::GetDocument() const
   { return reinterpret_cast<CMFCApp1Doc*>(m_pDocument); }
#endif

