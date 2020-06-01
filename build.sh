#!/usr/bin/env bash
[ -d build ] || mkdir build
set -e
cd build && cmake .. -DBUILD_TESTS=ON -G Ninja || exit $? && ninja || exit $? && \
[ "$1" == "run" ] && ./tests/test_runner && exit 0
[ "$1" == "val" ] && valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./tests/test_runner
exit $?
