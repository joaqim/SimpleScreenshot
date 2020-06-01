#include <Screenshot/ScreenshotWin32.h>

#if SCREENSHOT_PLATFORM == SCREENSHOT_PLATFORM_WIN32

namespace sh
{
  ScreenshotWin32::ScreenshotWin32(int const x_, int const y_, int const w_, int const h_) : ScreenshotImpl(x_, y_, w_, h_),x(x_), y(y_), w(w_), h(h_) {
#if 0
        // copy screen to bitmap
        hScreen = GetDC(NULL);
        hDC     = CreateCompatibleDC(hScreen);
        hBitmap = CreateCompatibleBitmap(hScreen, w, h);

        old_obj = SelectObject(hDC, hBitmap);
        BOOL    bRet    = BitBlt(hDC, 0, 0, w, h, hScreen, x, y, SRCCOPY);


#endif
        init = true;
  };
  ScreenshotWin32::~ScreenshotWin32() {
    // clean up
#if 0
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
#endif
    free(data);
  };

  void* ScreenshotWin32::takeScreenshot() {
    HDC hwindowDC,hwindowCompatibleDC;

    int height,width,srcheight,srcwidth;
    HBITMAP hbwindow;
    BITMAPINFOHEADER  bi;

    hwindowDC=GetDC(0);
    hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);

#if 0
    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom/2;  //change this to whatever size you want to resize to
    width = windowsize.right/2;
#else
    srcwidth = 100;
    srcheight = 100;
    width = 100;
    height = 100;
#endif

    //src.create(height,width,CV_8UC4);

    // create a bitmap
    hbwindow = CreateCompatibleBitmap( hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
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
    StretchBlt( hwindowCompatibleDC, 0,0, width, height, hwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    if(data)free(data);
    data = malloc((sizeof(unsigned char) * width*height*4));
    GetDIBits(hwindowCompatibleDC,hbwindow,0,height, data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject (hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(0, hwindowDC);

    return data;
  };
}
#endif
