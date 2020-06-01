
#define SCREENSHOT_PLATFORM = SCREENSHOT_PLATFORM_LINUX
#include <Screenshot/Screenshot.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <assert.h>
int main(int argc, char *argv[])
{
  sh::Screenshot screen{100, 100, 100, 100};
  void *data = screen.takeScreenshot();
  cv::Mat img = cv::Mat(screen.height, screen.width, CV_8UC4, (unsigned char*)data);

  cv::imshow("raw", img);
  cv::waitKey(0);
  img.release();
  return 0;
}
