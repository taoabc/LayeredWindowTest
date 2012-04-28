#pragma once

#include "resource.h"

class BkgWindow : public CDialogImpl<BkgWindow>
{
public:
  enum {IDD = IDD_BKG_WINDOW};
  BEGIN_MSG_MAP(BkgWindow)
    
  END_MSG_MAP()
  BkgWindow(void);
  ~BkgWindow(void);
};

