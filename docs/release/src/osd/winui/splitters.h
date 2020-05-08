// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, Ren� Single, Mamesick

#ifndef SPLITTER_H
#define SPLITTER_H

#if !defined(MAX)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

enum eSplitterHits
{
	SPLITTER_HITNOTHING = 0,
	SPLITTER_HITITEM
};

typedef struct horzSplitter
{
	HWND m_hWnd;
	HWND m_hWndLeft;
	HWND m_hWndRight;
	RECT m_limitRect;
	RECT m_dragRect;
	void (*m_func)(HWND hWnd, LPRECT lpRect);
} HZSPLITTER, *LPHZSPLITTER;

typedef struct
{
	double dPosition;
	int nSplitterWindow;
	int nLeftWindow;
	int nRightWindow;
	void (*pfnAdjust)(HWND hWnd,LPRECT lpRect);
} SPLITTERINFO;

/* Splitter routines */
void OnMouseMove(HWND hWnd, UINT nFlags, POINTS p);
void OnLButtonDown(HWND hWnd, UINT nFlags, POINTS p);
void OnLButtonUp(HWND hWnd, UINT nFlags, POINTS p);
void OnSizeSplitter(HWND hWnd);
void AddSplitter(HWND hWnd, HWND hWndLeft, HWND hWndRight, void (*func)(HWND hWnd,LPRECT lpRect));
void RecalcSplitters(void);
bool InitSplitters(void);
void SplittersExit(void);
int GetSplitterCount(void);
extern int *nSplitterOffset;
extern const SPLITTERINFO g_splitterInfo[];

#endif
