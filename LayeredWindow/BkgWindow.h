#pragma once

#include "resource.h"

#define UM_BKG_WINDOW_MOVE         WM_USER + 100

class BkgWindow : public CFrameWindowImpl<BkgWindow>
{
public:
  BEGIN_MSG_MAP(BkgWindow)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_MOVE, OnMove)
    MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
    CHAIN_MSG_MAP(CFrameWindowImpl<BkgWindow>)
  END_MSG_MAP()
  BkgWindow(void);
  ~BkgWindow(void);

private:
  LRESULT OnCreate(UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled);
  LRESULT OnLButtonDown(UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled);
  LRESULT OnMove(UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled);
};

