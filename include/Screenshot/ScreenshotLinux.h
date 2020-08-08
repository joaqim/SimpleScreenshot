#pragma once
#include "ScreenshotImpl.h"

#if SCREENSHOT_PLATFORM == SCREENSHOT_PLATFORM_LINUX

#include <cstdio> // puts, printf

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <png.h>

static void die(const char *s) {
  fprintf(stderr, "xscreenshot: %s\n", s);
  exit(EXIT_FAILURE);
}

/* LSBFirst: BGRA -> RGBA */
static void convertrow_lsb(unsigned char *drow, unsigned char *srow, XImage *img);
/* MSBFirst: ARGB -> RGBA */
static void convertrow_msb(unsigned char *drow, unsigned char *srow, XImage *img);
static void pngstdout(XImage *img);

class ScreenshotLinux : public ScreenshotImpl {
  public:
    ScreenshotLinux(int const x_, int const y_, int const w_, int const h_);
    virtual ~ScreenshotLinux();
    void* takeScreenshot();
  public:
    //      int x,y,w,h;
  private:
    void *data;

    Display* mDisplay;
    Window mRoot;
    XWindowAttributes mWindow_attributes;
    Screen* mScreen;
    XImage* mXimg;
    XShmSegmentInfo mShminfo;
};
#endif
