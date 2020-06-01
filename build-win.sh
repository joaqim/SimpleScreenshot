#!/usr/bin/env bash
[ -d build-win ] || mkdir build-win
set -e
cd build-win && x86_64-w64-mingw32-cmake .. -DCROSS_WIN=ON -DBUILD_TESTS=ON || exit $? && x86_64-w64-mingw32-make || exit $? && \
[ "$1" == "run" ] && wine ./tests/test_runner.exe && exit 0
[ "$1" == "deps" ] && ../mingw-copy-deps.sh /usr/x86_64-w64-mingw32/bin ./tests/test_runner.exe
exit $?
