#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <vector>

#include "record.h"
#include "fraction.h"

using namespace std;

template<class value> class Database {
public:
	Database() : num_records(0), num_selected(0) {}
	~Database() {}
	int numRecords() const {return num_records;}
	int numSelected() const {return num_selected;}
	void write(ostream& out, DBScope scope) const;
	void read(istream& in);
	void deleteRecords(DBScope scope);
	void selectAll();
	void deselectAll();
	void select(DBSelectOperation selOp, const string& attr, DBQueryOperator op,
			const value& val);
private:
	vector<Record<value>> _database;
	int num_records;
	int num_selected;
};

#include "database.tem"

#endif
