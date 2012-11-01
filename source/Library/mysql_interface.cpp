/*
 * interface.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: gary
 */

#include "mysql_interface.h"

/*
 * Default Constructor
 */
MySQL_Interface::MySQL_Interface() {
	driver = get_driver_instance();
	con = driver->connect(DEFAULT_HOST, DEFAULT_USER, DEFAULT_PASS);
	con->setSchema(DEFAULT_SCHEMA);
}

/*
 * Constructor
 */
MySQL_Interface::MySQL_Interface(string schema) {
	driver = get_driver_instance();
	con = driver->connect(DEFAULT_HOST, DEFAULT_USER, DEFAULT_PASS);
	con->setSchema(schema);
}

/*
 * Destructor
 */
MySQL_Interface::~MySQL_Interface() {
	delete con;
}

/*
 * Public Function: create_table
 */
void MySQL_Interface::create_table() {
	create_table(DEFAULT_SCHEMA);
}

/*
 * Public Overloaded Function: create_table
 */
void MySQL_Interface::create_table(string tableName) {
	sql::PreparedStatement *pstmt;

	try {
		pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS ParkingSpot ("
				"PocID int NOT NULL,"
				"SensorID int NOT NULL,"
				"SpotStatus int NOT NULL,"
				"StartTime datetime DEFAULT NULL,"
				"ExpireTime datetime DEFAULT NULL,"
				"PRIMARY KEY (PocID, SensorID),"
				"UNIQUE KEY LocationSensor_UNIQUE (PocID, SensorID))");
		pstmt->execute();
		delete pstmt;
	} catch (sql::SQLException &e) {
		print_error(e, "get_spot_status");
	}
}

/*
 * Public Function: get_spot_status
 * *(bool *status) set to:	- 'true' signifying spot is taken
 * 							- 'false' signifying spot is available
 */
bool MySQL_Interface::get_spot_status(int pocID, int sensorID) {
	bool status;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;

	try {
		pstmt = con->prepareStatement("SELECT SpotStatus FROM ParkingSpot WHERE PocID = ? AND SensorID = ?");
		pstmt->setInt(1, pocID);
		pstmt->setInt(2, sensorID);
		res = pstmt->executeQuery();

		res->next();
		status = res->getBoolean("SpotStatus");
	} catch (sql::SQLException &e) {
		print_error(e, "get_spot_status");
	}

	delete pstmt;
	return status;
}

/*
 * Public Function: set_spot_status
 */
void MySQL_Interface::set_spot_status(int pocID, int sensorID, bool status) {
	sql::PreparedStatement *pstmt;
	sql::ResultSet * res;

	try {
		pstmt = con->prepareStatement("SELECT * FROM ParkingSpot WHERE PocID = ? AND SensorID = ?");
		pstmt->setInt(1, pocID);
		pstmt->setInt(2, sensorID);
		res = pstmt->executeQuery();

		if (res->rowsCount() > 0)
		{
			pstmt = con->prepareStatement("UPDATE ParkingSpot SET SpotStatus = ? WHERE PocID = ? AND SensorID = ?");
			pstmt->setInt(1, status);
			pstmt->setInt(2, pocID);
			pstmt->setInt(3, sensorID);
			pstmt->execute();
		} else {
			create_spot(pocID, sensorID);
		}
	} catch (sql::SQLException &e) {
		print_error(e, "set_spot_status");
	}

	delete pstmt;
}

/*
 * Public Function: create_spot
 */
void MySQL_Interface::create_spot(int pocID, int sensorID) {
	sql::PreparedStatement *pstmt;

	try {
		pstmt = con->prepareStatement("INSERT INTO ParkingSpot (PocID, SensorID, SpotStatus) VALUES (?, ?, 0)");
		pstmt->setInt(1, pocID);
		pstmt->setInt(2, sensorID);
		pstmt->execute();
	} catch (sql::SQLException &e) {
		print_error(e, "create_spot");
	}

	delete pstmt;
}

/*
 * Public Overloaded Function: create_spot
 */
void MySQL_Interface::create_spot(int pocID, int sensorID, bool status) {
	sql::PreparedStatement *pstmt;

	try {
		pstmt = con->prepareStatement("INSERT INTO ParkingSpot (PocID, SensorID, SpotStatus) VALUES (?, ?, ?)");
		pstmt->setInt(1, pocID);
		pstmt->setInt(2, sensorID);
		pstmt->setInt(3, status);
		pstmt->execute();
	} catch (sql::SQLException &e) {
		print_error(e, "create_spot");
	}

	delete pstmt;
}

/*
 * Public Function: get_entry_count
 */
int MySQL_Interface::get_entry_count() {
	int count = -1;
	sql::Statement *stmt;
	sql::ResultSet *res;

	try {
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM ParkingSpot");
		count = res->rowsCount();
	} catch (sql::SQLException &e) {
		print_error(e, "get_entry_count");
	}

	delete stmt;
	delete res;
	return count;
}

/*
 * Public Function: get_con
 * Notes: Strictly for testing purposes
 */
sql::Connection *MySQL_Interface::get_con() {
	return con;
}

/*
 * Private Function: print_error
 */
void MySQL_Interface::print_error(sql::SQLException e, string function_name) {
	cout << "# ERR: SQLException in " << __FILE__;
	cout << " (function: " << function_name << ")" << endl;
	cout << "# ERR: " << e.what();
	cout << " (MySQL error code: " << e.getErrorCode();
	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}
