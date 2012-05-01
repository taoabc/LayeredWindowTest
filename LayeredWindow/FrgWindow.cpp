#include "StdAfx.h"
#include "FrgWindow.h"


const COLORREF FrgWindow::trans_color_ = RGB(255, 0, 255);


FrgWindow::FrgWindow(void)
{
}


FrgWindow::~FrgWindow(void)
{
}

LRESULT FrgWindow::OnCreate( UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled )
{
  SetStyle();
  SetTransparent(trans_color_);

  RECT rc;
  rc.left = 300;
  rc.top = 5;
  rc.right = 320;
  rc.bottom = 25;
  button_.Create(m_hWnd, &rc, NULL, WS_CHILD | WS_VISIBLE, NULL, IDC_BUTTON_CLOSE);

  hparent_ = GetParent();

  ::GetWindowRect(hparent_, &rc);
  MoveWindow(&rc);


  HICON htray_icon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MAINFRAME),
      IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
  tray_.Create(m_hWnd, IDC_TRAY, UM_TRAY, htray_icon, L"asdf");
  tray_.ShowBallonInfo(L"迅雷游戏盒子", L"当前下载进度 100%", 2*1000);

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
  HBRUSH hbrush = CreateSolidBrush(trans_color_);
  dc.FillRect(&rc, hbrush);
  return 1;
}

LRESULT FrgWindow::OnButtonClose( WORD notify_code, WORD id, HWND hwnd_ctrl, BOOL& bhandled )
{
  ::PostMessage(hparent_, WM_CLOSE, NULL, NULL);
  return 0;
}
