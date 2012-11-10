#!/bin/bash

g++ source/Library/mysql_interface.cpp source/Testing/driver.cpp source/Testing/unit_tests.cpp source/Testing/stress_tests.cpp -o run_tests.bin libmysqlcppconn.so
g++ -c source/Library/mysql_interface.cpp
cp source/Library/mysql_interface.h dist/include
mv mysql_interface.o dist/lib

