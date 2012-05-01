#include "StdAfx.h"
#include "FrgWindow.h"


FrgWindow::FrgWindow(void)
{
}


FrgWindow::~FrgWindow(void)
{
}

LRESULT FrgWindow::OnCreate( UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled )
{
  SetStyle();
  SetTransparent(RGB(255, 0, 255));

  RECT rc;
  rc.left = 100;
  rc.top = 100;
  rc.right = 150;
  rc.bottom = 120;
  button_.Create(m_hWnd, &rc, NULL, WS_CHILD | WS_VISIBLE);

  HWND hparent = GetParent();

  ::GetWindowRect(hparent, &rc);
  MoveWindow(&rc);

  return 0;
}

void FrgWindow::SetStyle()
{
  LONG style = WS_POPUP;
  LONG exstyle = WS_EX_TOOLWINDOW | WS_EX_LAYERED;
  SetWindowLong(GWL_STYLE, style);
  SetWindowLong(GWL_EXSTYLE, exstyle);
}

void FrgWindow::SetTransparent( COLORREF color )
{
  SetLayeredWindowAttributes(m_hWnd, color, 0, LWA_COLORKEY);
}

LRESULT FrgWindow::OnEraseBkgnd( UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled )
{
  CDCHandle dc((HDC)wparam);
  RECT rc;
  GetClientRect(&rc);
  HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 255));
  dc.FillRect(&rc, hbrush);
  return 1;
}