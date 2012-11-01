/*
 * unit_tests.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gary
 */

#ifndef UNIT_TESTS_H_
#define UNIT_TESTS_H_

#include "../Library/mysql_interface.h"

typedef struct test {
	string testID;
	bool result;
	Test *next;
} Test;

Test *start, *curr;
bool masterTestFlag;

void _AssertFlag(bool condition);
void handle_test_id(string testID);
void print_test_f_name(string functionName);
void setup_test_table(Connection *con);
void setup_test_table(Connection *con, int numOfPocs, int sensorsPerPoc);
void print_master_test();

// Test Functions
void test_get_spot_status();
void test_set_spot_status();
void test_create_spot();

#endif /* UNIT_TESTS_H_ */
