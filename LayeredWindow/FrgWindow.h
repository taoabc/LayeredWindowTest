#pragma once

#include "resource.h"
#include "ult-tray.h"

#define UM_TRAY                    WM_USER + 101

class FrgWindow : public CFrameWindowImpl<FrgWindow>
{
public:
  FrgWindow(void);
  ~FrgWindow(void);

  DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME);

  BEGIN_MSG_MAP(FrgWindow)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    COMMAND_HANDLER(IDC_BUTTON_CLOSE, BN_CLICKED, OnButtonClose)
    CHAIN_MSG_MAP(CFrameWindowImpl<FrgWindow>)
  END_MSG_MAP()

private:
  LRESULT OnCreate(UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled);
  LRESULT OnEraseBkgnd(UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled);

  LRESULT OnButtonClose(WORD notify_code, WORD id, HWND hwnd_ctrl, BOOL& bhandled);

  void SetStyle();
  void SetTransparent(COLORREF color);

  CButton button_;
  HWND hparent_;
  ult::Tray tray_;

  static const COLORREF trans_color_;
};

