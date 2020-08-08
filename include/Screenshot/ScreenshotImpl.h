#pragma once

#include "Screenshot.h"

#define SCREENSHOT_PLATFORM_WIN32 1
#define SCREENSHOT_PLATFORM_LINUX 2
#define SCREENSHOT_PLATFORM_KQUEUE 3

#if defined(_WIN32)
#	define SCREENSHOT_PLATFORM SCREENSHOT_PLATFORM_WIN32
#elif defined(__APPLE_CC__) || defined(BSD)
#	define SCREENSHOT_PLATFORM SCREENSHOT_PLATFORM_KQUEUE
#elif defined(__linux__)
#	define SCREENSHOT_PLATFORM SCREENSHOT_PLATFORM_LINUX
#endif

class ScreenshotImpl {
  public:
    ScreenshotImpl(int const x_, int const y_, int const w_, int const h_) : mX(x_), mY(y_), mW(w_), mH(h_) {}
    virtual ~ScreenshotImpl(){}
    virtual void* takeScreenshot() = 0;
    int mX, mY, mW, mH;
    bool mInit;
};
