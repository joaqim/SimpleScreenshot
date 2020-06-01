#pragma once

#include <utility> // std::pair

namespace sh {
  class ScreenshotImpl;
  class Screenshot {
    public:
      Screenshot(int const x_, int const y_, int const w_, int const h_);
      virtual ~Screenshot();
      void* operator()();
      void* takeScreenshot();
      void setCrop(std::pair<int,int> const &resolution_, int const x_, int const y_);
      int x, y, width, height;
    private:
      ScreenshotImpl *mImpl;
  };
}
