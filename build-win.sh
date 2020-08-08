#!/usr/bin/env bash
set -e
[ "$1" == "deps" ] && ./third_party/mingw-copy-deps.sh /usr/x86_64-w64-mingw32/bin ./build-win/tests/test_runner.exe && exit 0

[ -d build-win ] || mkdir build-win
cd build-win
x86_64-w64-mingw32-cmake .. -DCROSS_WIN=ON -DBUILD_TESTS=ON || exit $? && x86_64-w64-mingw32-make || exit $? && \
if [ "$1" == "run" ]; then
  [ -f ./build-win/tests/*.dll ] || (cd .. && exec $0 deps)
  wine ./tests/test_runner.exe && exit 0
fi
exit $?
