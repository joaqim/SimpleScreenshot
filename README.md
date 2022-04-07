SimpleScreenshot
================
A small library I created for a need in my OCR projects.

The `Screenshot` class stores an area of the screen `(x, y, width, height)` where it is expected to take frequent screenshots (see [Usage](#usage)).

The `Screenshot` class returns Raw Image data of that area when called with `operator()` or `takeScreenshot().`

This Raw Image can then be used to create a desired image object.
e.g: `cv::Mat` (see [Usage](#usage)).

The raw image data is a 2-dimensional array containing one `uchar` element per channel, representing (R, G, B, A) of the pixel at that point:

```cpp
  *img_data[x][y][0] = (uchar)255; // (RED)
  *img_data[x][y][1] = (uchar)255; // (GREEN)
  *img_data[x][y][2] = (uchar)255; // (BLUE)
  *img_data[x][y][3] = (uchar)0;   // (ALPHA)
```

You can get `width` and `height` from `Screenshot` class members.

SimpleScreenshot is compatible with Linux and Windows ( only tested cross-compiling with mingw and running with Wine.)

Prerequisites
=============
* g++, cmake
* X11, xshm ( for Linux )

Arch Linux:
    ```
    sudo pacman -S libx11 libxext
    ```

Ubuntu:
    ```
    sudo apt-get install libx11-dev libxext-dev
    ```

Usage
=====

* CMakeLists:

```cmake
    add_subdirectory(SimpleScreenshot)
    include_directories(SimpleScreenshot/include)
    target_link_libraries(
        ${EXECUTABLE}
        simplescreenshot)
```

* C++
```cpp
    #include <Screenshot/Screenshot.h>

    // This is just initialization of the area where you would take screenshots
    Screenshot screenshot{x, y, width, height};
    
    // Takes the screenshot and returns raw Image data  width*height*(8bits RGBA)
    void *data = screenshot(); // or screenshoot.takeScreenshot();

    // Creating a OpenCV Matrix ( 8bit RGBA Image)
    cv::Mat img = cv::Mat(screen.height, screen.width, CV_8UC4, (unsigned char*)data);
```
Build Test
==========
A very simple test:
```cpp
#include <Screenshot/Screenshot.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <assert.h>

int main() {
    // Initialize
    sh::Screenshot screen{100, 100, 100, 100};

    // Grab screenshot
    void *data = screen();
    // or alternatively:
    // void *data = screen.takeScreenshot();

    // Create cv::Mat 8bit RGBA
    cv::Mat img = cv::Mat(screen.height, screen.width, CV_8UC4, (unsigned char*)data);

    assert(!img.empty());

    cv::imshow("raw", img);
    cv::waitKey(0);

    img.release();

    return 0;
};
```

Requires OpenCV:

```sudo pacman -S opencv```

or

```sudo apt-get install libopencv-dev```

Build with:
```
    cd build
    cmake .. -DBUILD_TESTS=ON
    cmake --build .
```
or
```
    ./build.sh run
```

License
=======

Copyright 2015,2020 Joaqim Planstedt

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
