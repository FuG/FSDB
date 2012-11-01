/*
 * main.c
 *
 *  Created on: Oct 31, 2012
 *      Author: gary
 */

#include "testing.h"

int main() {
	bool boolResults;
	int pocID = 2, sensorID = 3;
	MySQL_Interface interface;
	masterTestFlag = false;

	cout << "MySQL_Interface Unit Testing: " << endl << endl;

	test_get_spot_status();
	test_set_spot_status();
	test_create_spot();

	return 0;
}

/*
 * Function: _AssertFlag
 * 	Notes: Custom testing assertion function
 */
void _AssertFlag(bool condition) {
	cout << "   Test Result: ";
	if (condition) {
		masterTestFlag = true;
		cout <<  "Fail" << endl << endl;
	} else {
		cout << "Pass" << endl << endl;
	}
}

/*
 * Function: new_test()
 */
void new_test(string testID)
{
	Test t;
	t.testID = testID;
	t.result = false;
	t.next = NULL;

	if (curr != NULL) {
		curr->next = &t;
	} else {
		start = &t;
	}
	curr = &t;
}

/*
 * Function: print_test_id
 */
void handle_test_id(string testID) {
	new_test(testID);
	cout << " --Test Id: " << testID << endl;
}

/*
 * Function: print_test_f_name
 */
void print_test_f_name(string functionName) {
	cout << "### Function: " << functionName << " ###" << endl;
}

/*
 * Function: setup_test_table
 */
void setup_test_table(Connection *con) {
	setup_test_table(con, 10, 10);
}

/*
 * Overload Function: setup_test_table
 */
void setup_test_table(Connection *con, int numOfPocs, int sensorsPerPoc) {
	int i, j;
	Statement *stmt;
	PreparedStatement *pstmt;

	try {
		stmt = con->createStatement();
		stmt->execute("DROP TABLE IF EXISTS ParkingSpot");
		stmt->execute("CREATE TABLE ParkingSpot ("
				"PocID int NOT NULL,"
				"SensorID int NOT NULL,"
				"SpotStatus int NOT NULL,"
				"StartTime datetime DEFAULT NULL,"
				"ExpireTime datetime DEFAULT NULL,"
				"PRIMARY KEY (PocID, SensorID),"
				"UNIQUE KEY LocationSensor_UNIQUE (PocID, SensorID))");
		delete stmt;

		pstmt = con->prepareStatement("INSERT INTO ParkingSpot (PocID, SensorID, SpotStatus) VALUES (?, ?, 0)");
		for(i = 0; i < numOfPocs; i++)
		{
			pstmt->setInt(1, i);
			for(j = 0; j < sensorsPerPoc; j++)
			{
				pstmt->setInt(2, j);
				pstmt->execute();
			}
		}
	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << " (function: " << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	delete pstmt;
}

/*
 * Function: print_test_master
 */
void print_test_master() {
	if (!masterTestFlag) {
		cout << "All tests passed!" << endl << endl;
	} else {

	}
}
