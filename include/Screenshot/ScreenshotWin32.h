#pragma once
#include "ScreenshotImpl.h"

#if SCREENSHOT_PLATFORM == SCREENSHOT_PLATFORM_WIN32

#include <windows.h>

class ScreenshotWin32 : public ScreenshotImpl {
  public:
    ScreenshotWin32(int const x_, int const y_, int const w_, int const h_);
    virtual ~ScreenshotWin32();
    void* takeScreenshot();
  public:
    int x,y,w,h;
  private:
    bool init = false;
    void *data;

    HDC hwindowDC,hwindowCompatibleDC;

    HBITMAP hbwindow;
    BITMAPINFOHEADER  bi;
};
#endif
