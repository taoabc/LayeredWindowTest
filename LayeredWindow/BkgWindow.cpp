#include "StdAfx.h"
#include "BkgWindow.h"


BkgWindow::BkgWindow(void)
{
}


BkgWindow::~BkgWindow(void)
{
}


void PreMultiply1( CImage& image )
{
  int width = image.GetWidth();
  int height = image.GetHeight();
  byte* p;
  byte alpha;
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      p = (byte*)image.GetPixelAddress(col, row);
      alpha = p[3];
      if (255 > alpha) {
        p[0] = ((p[0] * alpha) + 127) / 255;
        p[1] = ((p[1] * alpha) + 127) / 255;
        p[2] = ((p[2] * alpha) + 127) / 255;
      }
    }
  }
}

LRESULT BkgWindow::OnCreate( UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled )
{
  LONG exstyle = WS_EX_TOOLWINDOW | WS_EX_LAYERED;
  SetWindowLong(GWL_EXSTYLE, exstyle);

  LONG style = WS_VISIBLE | WS_POPUP;
  SetWindowLong(GWL_STYLE, style);

  HDC hWndDC = GetDC();
  HDC hMemDC = CreateCompatibleDC(hWndDC);
  CImage image;
  //载入一幅自己的图片
  image.Load(L"res/bkg.png");
  //将图片预乘
  PreMultiply1(image);
  //创建兼容Bitmap，并将其select进去
  HBITMAP hMemBmp = CreateCompatibleBitmap(hWndDC, image.GetWidth(), image.GetHeight());
  SelectObject(hMemDC, hMemBmp);
  //画入到DC
  image.Draw(hMemDC, 0, 0, image.GetWidth(), image.GetHeight());
  CRect rc;
  GetWindowRect(&rc);
  CPoint leftTop(rc.TopLeft());
  CPoint ptDC(0, 0);
  CSize wndSize(image.GetWidth(), image.GetHeight());
  BLENDFUNCTION bf;
  bf.BlendOp = AC_SRC_OVER;
  bf.AlphaFormat = AC_SRC_ALPHA;
  bf.SourceConstantAlpha = 0xff;
  bf.BlendFlags = 0;
  bool bRet = UpdateLayeredWindow(m_hWnd, NULL, &leftTop, &wndSize, hMemDC, &ptDC,
    0, &bf, ULW_ALPHA);
  return 0;
}

LRESULT BkgWindow::OnLButtonDown( UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled )
{
  if (MK_LBUTTON == wparam) {
  int y = GET_Y_LPARAM(lparam);
  if (30 > y) {
    PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, lparam);
  }
  }
  return 0;
}

LRESULT BkgWindow::OnMove( UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled )
{
  RECT rc;
  GetWindowRect(&rc);
  WPARAM wparam_send = MAKEWPARAM(rc.left, rc.top);
  LPARAM lparam_send = MAKELPARAM(rc.right, rc.bottom);
  HWND hparent = GetParent();
  ::SendMessage(hparent, UM_BKG_WINDOW_MOVE, wparam_send, lparam_send);
  SetWindowPos(hparent, &rc, SWP_SHOWWINDOW);
  return 0;
}
