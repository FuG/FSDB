/*
 * unit_tests.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: gary
 */

#include "testing.h"

void test_get_spot_status() {
	bool testFlag = false;
	MySQL_Interface interface;

	setup_test_table(interface.get_con());
	print_test_f_name("get_spot_status");
	handle_test_id("1.1");
	cout << "\tAll 100 entries should have SpotStatus initialized to 0." << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (interface.get_spot_status(i, j))
				testFlag = true;
		}
	}
	_AssertFlag(testFlag);
}

void test_set_spot_status() {
	bool testFlag = false;
	MySQL_Interface interface;

	setup_test_table(interface.get_con());
	print_test_f_name("set_spot_status");
	handle_test_id("2.1");
	cout << "\tAll 100 entries' SpotStatus initialized to 0." << endl;
	cout << "\tSwitching all entries' SpotStatus to 1." << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			interface.set_spot_status(i, j, true);
		}
	}
	cout << "\tAll 100 entries should now have SpotStatus of 1." << endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (!interface.get_spot_status(i, j))
				testFlag = true;
		}
	}
	_AssertFlag(testFlag);

	handle_test_id("2.2");
	cout << "\tTrying to set SpotStatus in a non-existing entry should create it instead." << endl;
	cout << "\tSpotStatus should be initialized to 0 by default." << endl;
	cout << "\tNote: Indirectly tests function create_spot." << endl;
	interface.create_spot(15, 15);

	testFlag = false;
	testFlag = interface.get_spot_status(15, 15);
	_AssertFlag(testFlag);
}

void test_create_spot() {
	bool testFlag = false;
	MySQL_Interface interface;

	setup_test_table(interface.get_con());
	print_test_f_name("create_spot");
	handle_test_id("3.1");
	cout << "\tDefault create_spot without spotStatus field should create" << endl;
	cout << "\tan entry with SpotStatus set to 0." << endl;

	interface.create_spot(20, 20);
	testFlag = interface.get_spot_status(20, 20);
	_AssertFlag(testFlag);

	handle_test_id("3.2");
	cout << "\tOverloaded create_spot should create an entry with" << endl;
	cout << "\tSpotStatus set to the passed in spotStatus." << endl;

	interface.create_spot(30, 30);
	testFlag = interface.get_spot_status(30, 30);
	_AssertFlag(testFlag);
}

void test_get_entry_count() {
	bool testFlag = false;
	MySQL_Interface interface;

	setup_test_table(interface.get_con());
	print_test_f_name("get_entry_count");
	handle_test_id("4.1");
	cout << "\tGets the count of entries for a table." << endl;
	cout << "\tShould return 100 for this test case." << endl;

	testFlag = (interface.get_entry_count() != 100);
	_AssertFlag(testFlag);
}
