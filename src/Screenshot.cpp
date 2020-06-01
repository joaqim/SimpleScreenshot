
#include <Screenshot/Screenshot.h>
#include <Screenshot/ScreenshotImpl.h>

#if SCREENSHOT_PLATFORM == SCREENSHOT_PLATFORM_WIN32
# include <Screenshot/ScreenshotWin32.h>
# define SCREENSHOT_IMPL ScreenshotWin32
#elif SCREENSHOT_PLATFORM == SCREENSHOT_PLATFORM_LINUX
# include <Screenshot/ScreenshotLinux.h>
# define SCREENSHOT_IMPL ScreenshotLinux
#endif

namespace sh {
  Screenshot::Screenshot(int const x_, int const y_, int const w_, int const h_) : x(x_), y(y_), width(w_), height(h_)
  {
    mImpl = new SCREENSHOT_IMPL(x_, y_, w_, h_);
  }
  Screenshot::~Screenshot()
  {
    delete mImpl;
    mImpl = 0;
  }
  void* Screenshot::operator()() {
    return mImpl->takeScreenshot();
  }
  void* Screenshot::takeScreenshot() {
    return mImpl->takeScreenshot();
  }
  void Screenshot::setCrop(std::pair<int,int> const &resolution_, int const x_, int const y_) {
    //mImpl->setCrop(resolution_, x_, y_);
  }
 }
