#pragma once

#include "resource.h"

class FrgWindow : public CFrameWindowImpl<FrgWindow>
{
public:
  FrgWindow(void);
  ~FrgWindow(void);

  BEGIN_MSG_MAP(FrgWindow)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
  END_MSG_MAP()

private:
  LRESULT OnCreate(UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled);
  LRESULT OnEraseBkgnd(UINT umsg, WPARAM wparam, LPARAM lparam, BOOL& bhandled);

  void SetStyle();
  void SetTransparent(COLORREF color);

  CButton button_;
};

