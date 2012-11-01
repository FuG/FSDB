#!/bin/bash

g++ Library/mysql_interface.cpp Testing/driver.cpp Testing/unit_tests.cpp libmysqlcppconn.so
g++ -c Library/mysql_interface.cpp
mv mysql_interface.o dist/lib/
cp Library/mysql_interface.h dist/include/
