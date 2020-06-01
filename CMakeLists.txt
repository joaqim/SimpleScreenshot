project(simplescreenshot)
cmake_minimum_required(VERSION 3.11)
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_BUILD_TYPE Debug)

SET(STATIC_FLAGS "-static-libgcc -static-libstdc++ -Bstatic -lpthread -Wl,-allow-multiple-definition,-Bdynamic")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${STATIC_FLAGS}")

add_library(simplescreenshot
    src/Screenshot.cpp
    src/ScreenshotLinux.cpp
    src/ScreenshotWin32.cpp
    #    src/ScreenshotWin32.cpp
    )


if(CROSS_WIN)
else()
  find_package(X11 REQUIRED)
  message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
endif(CROSS_WIN)

find_package(PNG REQUIRED)

target_link_libraries(
  simplescreenshot
  ${X11_LIBRARIES}
  ${PNG_LIBRARY}
  )

target_include_directories(
  simplescreenshot
  PRIVATE
  ${X11_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${PNG_INCLUDE_DIRS}
  )

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
