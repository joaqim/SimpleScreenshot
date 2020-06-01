find_package( OpenCV 4 REQUIRED)

add_executable(test_runner ScreenshotTest.cpp)

target_include_directories(
  test_runner
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIR}
  )
target_link_libraries(test_runner
  simplescreenshot
  ${OpenCV_LIBRARIES}
  )
