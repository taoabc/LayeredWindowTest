/* 
** 提供托盘图标操作
** author:
**   taoabc@gmail.com
*/
#ifndef ULT_TRAY_H_
#define ULT_TRAY_H_

#include <string>
#include <ShellAPI.h>

namespace ult {

class Tray {
public:
  Tray(void);
  ~Tray(void);

  bool Create(HWND hwnd, UINT uid, UINT ucallback_msg, HICON htray_icon, wchar_t* sztip);
  bool ShowBallonInfo(wchar_t* info_title, wchar_t* info, UINT timeout);

private:
  DWORD GetShellVersion(void);
  DWORD GetNOTIFYICONDATASizeForOS(void);

  NOTIFYICONDATA notify_icon_data_;
  WORD shell_major_version_;
  WORD shell_minor_version_;
};

}

#endif