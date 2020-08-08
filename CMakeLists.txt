project(simplescreenshot)
cmake_minimum_required(VERSION 3.11)

SET(STATIC_FLAGS "-static-libgcc -static-libstdc++ -Bstatic")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wl,-allow-multiple-definition ${STATIC_FLAGS}")

add_library(simplescreenshot
    src/Screenshot.cpp
    src/ScreenshotLinux.cpp
    src/ScreenshotWin32.cpp
    )


  #if(CMAKE_CROSSCOMPILING)
  #else()
  #endif(CMAKE_CROSSCOMPILING)

find_package(X11 REQUIRED)

target_link_libraries(
  simplescreenshot
  ${X11_LIBRARIES}
  )

target_include_directories(
  simplescreenshot
  PRIVATE
  ${X11_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
  )

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
