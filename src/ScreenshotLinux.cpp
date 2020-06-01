#include <Screenshot/ScreenshotLinux.h>

#if SCREENSHOT_PLATFORM == SCREENSHOT_PLATFORM_LINUX
#include <string>
#include <stdio.h>
#include <algorithm>

namespace sh
{
  ScreenshotLinux::ScreenshotLinux(int const x_, int const y_, int const w_, int const h_) : ScreenshotImpl(x_,y_,w_,h_) {
    mDisplay = XOpenDisplay(nullptr);
    mRoot = DefaultRootWindow(mDisplay);

    XGetWindowAttributes(mDisplay, mRoot, &mWindow_attributes);
    mScreen = mWindow_attributes.screen;
    mXimg = XShmCreateImage(mDisplay, DefaultVisualOfScreen(mScreen), DefaultDepthOfScreen(mScreen), ZPixmap, NULL, &mShminfo, mW, mH);

    mShminfo.shmid = shmget(IPC_PRIVATE, mXimg->bytes_per_line * mXimg->height, IPC_CREAT|0777);
    mShminfo.shmaddr = mXimg->data = (char*)shmat(mShminfo.shmid, 0, 0);
    mShminfo.readOnly = False;
    if(mShminfo.shmid < 0) puts("Fatal shminfo error!");
    Status s1 = XShmAttach(mDisplay, &mShminfo);
#ifdef DEBUG
    printf("XShmAttach() %s\n", s1 ? "success!" : "failure!");
#endif

    mInit = true;
  };

  ScreenshotLinux::~ScreenshotLinux() {
    mInit = false;

    //if(data) free(data);
    XDestroyImage(mXimg);
    XShmDetach(mDisplay, &mShminfo);
    shmdt(mShminfo.shmaddr);
    XCloseDisplay(mDisplay);
  };

  void* ScreenshotLinux::takeScreenshot() {
    XShmGetImage(mDisplay, mRoot, mXimg, mX, mY, 0x00ffffff);
    //if(data) free(data);
    //data = malloc((sizeof(unsigned char) * mW*mH*4));
    data = mXimg->data;
    return data;
  };

  void setCrop(std::pair<int,int> const &resolution_, int const x_, int const y_) {
  };

}
#endif
