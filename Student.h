#pragma once
#include <string>
class Student
{
	std::string name;
	std::string regNo;
public:
	Student(const std::string& name, const std::string& regNo) :name(name), regNo(regNo) {}
	~Student() {}
	const std::string getName() {
		return this->name;
	}
	const std::string getRegNo() {
		return this->regNo;
	}
	void setName(const std::string& name) {
		this->name = name;
	}
	void setRegNo(const std::string& reg) {
		this->regNo = reg;
	}
};