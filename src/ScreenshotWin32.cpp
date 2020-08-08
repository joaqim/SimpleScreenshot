#include <Screenshot/ScreenshotWin32.h>

#if SCREENSHOT_PLATFORM == SCREENSHOT_PLATFORM_WIN32

ScreenshotWin32::ScreenshotWin32(int const x_, int const y_, int const w_, int const h_) : ScreenshotImpl(x_, y_, w_, h_),x(x_), y(y_), w(w_), h(h_) {
#if 0
  //TODO: Maybe add support for defaulting to Fullscreen screenshots
  RECT windowsize;    // get the height and width of the screen
  GetClientRect(hwnd, &windowsize);

  height = windowsize.bottom;
  width = windowsize.right;
#endif
  hwindowDC=GetDC(0);
  hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
  SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);
  //
  // create a bitmap
  hbwindow = CreateCompatibleBitmap( hwindowDC, w, h);
  bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
  bi.biWidth = w;
  bi.biHeight = -h;  //this is the line that makes it draw upside down or not
  bi.biPlanes = 1;
  bi.biBitCount = 32;
  bi.biCompression = BI_RGB;
  bi.biSizeImage = 0;
  bi.biXPelsPerMeter = 0;
  bi.biYPelsPerMeter = 0;
  bi.biClrUsed = 0;
  bi.biClrImportant = 0;


  init = true;
};
ScreenshotWin32::~ScreenshotWin32() {
  // clean up
  DeleteObject (hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(0, hwindowDC);
  if(data) free(data);
};

void* ScreenshotWin32::takeScreenshot() {

  hwindowDC=GetDC(0);
  hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
  SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);

  // create a bitmap
  hbwindow = CreateCompatibleBitmap( hwindowDC, w, h);
  bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
  bi.biWidth = w;
  bi.biHeight = -h;  //this is the line that makes it draw upside down or not
  bi.biPlanes = 1;
  bi.biBitCount = 32;
  bi.biCompression = BI_RGB;
  bi.biSizeImage = 0;
  bi.biXPelsPerMeter = 0;
  bi.biYPelsPerMeter = 0;
  bi.biClrUsed = 0;
  bi.biClrImportant = 0;

  // use the previously created device context with the bitmap
  SelectObject(hwindowCompatibleDC, hbwindow);
  // copy from the window device context to the bitmap device context
  StretchBlt( hwindowCompatibleDC, 0,0, w, h, hwindowDC, x, y, w,h, SRCCOPY);

  if(data) free(data);
  data = malloc((sizeof(unsigned char) * w*h*4));

  GetDIBits(hwindowCompatibleDC,hbwindow,0, h, data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);

  // avoid memory leak
  ReleaseDC(0, hwindowDC);

  return data;
};
#endif
