#pragma once
#include "MYSQL_Con.h"
#include <fstream>
#include <vector>
#include "Student.h"

class Calculator
{
private:
	MYSQL_Con* DB;
	Student* S;
	string subject;
public:
	Calculator(const string& server, const string& name, const string& pass);
	~Calculator();
	void run();

private:
	void student();
	int menu();
	int subjectMenu();
	int modificationMenu();
	void printGrades(int flag = 0);
	void printResult(int flag = 0);
	void printSoftCopy();
	void printAssesData();
	void printAssesDataHelper(string asses);
	int getKey(const string asses);
	bool addSubject();
	bool insertData(const string asses);
	void updateData(int key, int flag);
	void modifySubject(int flag = 0);
	string styleDiff(string data, int diff);
};

