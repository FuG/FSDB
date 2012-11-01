/*
 * mysql_interface.h
 *
 *  Created on: Oct 31, 2012
 *      Author: gary
 */

#ifndef MYSQL_INTERFACE_H_
#define MYSQL_INTERFACE_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

#define DEFAULT_HOST 	"tcp://127.0.0.1"
#define DEFAULT_USER 	"root"
#define DEFAULT_PASS 	"root"
#define DEFAULT_SCHEMA 	"test"
#define DEFAULT_TABLE	"ParkingSpot"

class MySQL_Interface {
  public:
	MySQL_Interface();
	MySQL_Interface(string schema);
	~MySQL_Interface();

	// Getters
	bool get_spot_status(int pocID, int sensorID);
	// Setters
	void set_spot_status(int pocID, int sensorID, bool status);

	void create_table();
	void create_table(string tableName);
	void create_spot(int pocID, int sensorID);
	void create_spot(int pocID, int sensorID, bool status);
	int get_entry_count();

	// Testing helper
	sql::Connection *get_con();
  private:
	sql::Driver 	*driver;
	sql::Connection *con;

	void print_error(sql::SQLException e, string function_name);
};

#endif /* MYSQL_INTERFACE_H_ */
