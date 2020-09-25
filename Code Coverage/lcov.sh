#!/bin/bash
lcov --zerocounters --directory $PWD
lcov --capture --initial --directory $PWD --output-file app.info
./run_files
lcov --no-checksum --directory $PWD --capture --output-file app2.info
genhtml --highlight --legend -output-directory $PWD/html-coverage/ $PWD/app2.info
