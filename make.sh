#!/bin/bash

g++ Library/mysql_interface.h Library/mysql_interface.cpp Testing/driver.cpp Testing/unit_tests.cpp libmysqlcppconn.so
