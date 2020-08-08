#include <Screenshot/Screenshot.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <assert.h>
int main(int argc, char *argv[])
{
  // Initialize
  sh::Screenshot screen{100, 100, 100, 100};

  // Grab screenshot
  void *data = screen(); // or screen.takeScreenshot()

  // Create cv::Mat 8bit RGBA
  cv::Mat img = cv::Mat(screen.height, screen.width, CV_8UC4, (unsigned char*)data);

  assert(!img.empty());

  cv::imshow("raw", img);
  cv::waitKey(0);

  img.release();

  return 0;
}
