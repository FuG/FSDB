/*
 * unit_tests.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gary
 */

#ifndef UNIT_TESTS_H_
#define UNIT_TESTS_H_

#include "../Library/mysql_interface.h"
#include <time.h>

#define start_t		start_time = clock()
#define end_t		end_time = clock()
#define calc_dif	time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC

#define stress_pocs 			100
#define stress_sensors_per_poc 	100
#define stress_cycles			10000

typedef struct test {
	string testID;
	bool result;
	struct test *next;
} Test;

extern Test *start, *curr;
extern bool masterTestFlag;
extern clock_t start_time, end_time;
extern double time_taken;

void _AssertFlag(bool condition);
void handle_test_id(string testID);
void print_test_f_name(string functionName);
void print_stress_f_name(string functionName);
void setup_test_table(Connection *con);
void setup_test_table(Connection *con, int numOfPocs, int sensorsPerPoc);
void print_test_master();

// Unit Test Functions
void test_get_spot_status();
void test_set_spot_status();
void test_create_spot();
void test_get_entry_count();
void test_create_table();

// Stress Test Functions
void stress_setup();
void stress_test_get_spot_status();
void stress_test_set_spot_status();

#endif /* UNIT_TESTS_H_ */
