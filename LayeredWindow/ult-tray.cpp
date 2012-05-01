#include "stdafx.h"
#include "ult-tray.h"
#include <ShellAPI.h>

namespace ult {

Tray::Tray( void )
{
  memset(&notify_icon_data_, 0, sizeof(notify_icon_data_));
  DWORD shell_version = GetShellVersion();
  shell_major_version_ = HIWORD(shell_version);
  shell_minor_version_ = LOWORD(shell_version);
}

Tray::~Tray( void )
{
  if (0 != notify_icon_data_.cbSize) {
    Shell_NotifyIcon(NIM_DELETE, &notify_icon_data_);
  }
}

bool Tray::Create( HWND hwnd, UINT uid, UINT ucallback_msg, HICON htray_icon, wchar_t* sztip )
{
  notify_icon_data_.cbSize = GetNOTIFYICONDATASizeForOS();
  notify_icon_data_.hWnd = hwnd;
  notify_icon_data_.uID = uid;
  notify_icon_data_.uCallbackMessage = ucallback_msg;
  notify_icon_data_.hIcon = htray_icon;
  wcscpy_s(notify_icon_data_.szTip, sizeof(notify_icon_data_.szTip)/sizeof(wchar_t), sztip);

  AddTrayIcon();

  return true;
}

bool Tray::ShowBallonInfo( wchar_t* info_title, wchar_t* info, UINT timeout )
{
  if (5 > shell_major_version_) {
    return false;
  }
  notify_icon_data_.dwInfoFlags = NIIF_USER;
  notify_icon_data_.uTimeout = timeout;
  wcscpy_s(notify_icon_data_.szInfoTitle, sizeof(notify_icon_data_.szInfoTitle)/sizeof(wchar_t),
      info_title);
  wcscpy_s(notify_icon_data_.szInfo, sizeof(notify_icon_data_.szInfo)/sizeof(wchar_t),
    info);
  ShowBallonInfo();
  return true;
}

bool Tray::ShowBallonInfo( void )
{
  notify_icon_data_.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
  Shell_NotifyIcon(NIM_MODIFY, &notify_icon_data_);
  return true;
}

DWORD Tray::GetShellVersion( void )
{
  HINSTANCE hinst_dll;
  DWORD dwversion = 0;
  hinst_dll = LoadLibrary(L"Shell32.dll");
  if (NULL != hinst_dll) {
    DLLGETVERSIONPROC pfn_dll_get_version;
    pfn_dll_get_version = (DLLGETVERSIONPROC)GetProcAddress(hinst_dll, "DllGetVersion");
    if (NULL != pfn_dll_get_version) {
      DLLVERSIONINFO dvi;
      HRESULT hr;

      memset(&dvi, 0, sizeof(dvi));
      dvi.cbSize = sizeof(dvi);
      hr = pfn_dll_get_version(&dvi);
      if (SUCCEEDED(hr)) {
        dwversion = MAKELONG(dvi.dwMinorVersion, dvi.dwMajorVersion);
      }
    }
    FreeLibrary(hinst_dll);
  }
  return dwversion;
}

DWORD Tray::GetNOTIFYICONDATASizeForOS( void )
{
  if (5 > shell_major_version_) {
    return NOTIFYICONDATA_V1_SIZE;
  } else if (5 == shell_major_version_) {
    return NOTIFYICONDATA_V2_SIZE;
  } else if (6 == shell_major_version_) {
    if (0 == shell_minor_version_) {
      //这里因为系统版本的定义而不能使用
      //return NOTIFYICONDATA_V3_SIZE;
      return sizeof (NOTIFYICONDATA);
    } else if (0 < shell_minor_version_) {
      return sizeof (NOTIFYICONDATA);
    }
  } else {
    return sizeof (NOTIFYICONDATA);
  }
}

bool Tray::AddTrayIcon( void )
{
  notify_icon_data_.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
  Shell_NotifyIcon(NIM_ADD, &notify_icon_data_);
  return true;
}

}