#include "Calculator.h"

Calculator::Calculator(const string& server, const string& name, const string& pass)
{
	this->DB = new MYSQL_Con(server, name, pass);
	this->S = nullptr;
	this->subject = "";
}

Calculator::~Calculator()
{
	if (this->DB)
		delete this->DB;
	if (this->S)
		delete this->S;
}

void Calculator::run()
{
	if (this->DB->connect())
	{
		this->DB->setSchema("gpacalculator");
		int in = 0;
		this->student();
		while (1)
		{
			in = this->menu();
			char dec = 'y';
			if (in == 9)
				break;
			else if (in == 1)
			{
				system("CLS");
				if (this->addSubject())
				{
					cout << " Subject Added Successfully" << endl;
					bool isAss = false, isCP = false, isQuiz = false, isFinals = false,
						isMids = false, isPP = false;
					while (1)
					{
						in = this->subjectMenu();
						dec = 'y';
						if (in == 7)
						{
							if (!isAss || !isCP || !isQuiz || !isFinals || !isMids)
							{
								cout << " Warning: You haven't added all of asses " << endl;
								cout << " yet! this may give you unexpect result " << endl;
								cout << " Do you still want to exit ? y/n : ";
								cin >> dec;
							}
							if (dec == 'y' || dec == 'Y')
							{
								system("CLS");
								break;
							}
						}
						else if (in == 1)
						{
							if (isAss)
							{
								cout << " Note: You have already added assignment" << endl;
								cout << " want to add again? y/n: ";
								cin >> dec;
								if (dec == 'y')
								{
									this->DB->select("DELETE FROM `assignment` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + this->subject + "'; ");
									isAss = false;
								}
							}
							if (!isAss && this->insertData("assignment"))
							{
								cout << " Assignment Added Successfully" << endl;
								isAss = true;
							}
						}
						else if (in == 2)
						{
							if (isCP)
							{
								cout << " Note: You have already added CP" << endl;
								cout << " want to add again? y/n: ";
								cin >> dec;
								if (dec == 'y')
								{
									this->DB->select("DELETE FROM `cp` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + this->subject + "'; ");
									isCP = false;
								}
							}
							if (!isCP && this->insertData("cp"))
							{
								cout << " CP Added Successfully" << endl;
								isCP = true;
							}
						}
						else if (in == 3)
						{
							if (isQuiz)
							{
								cout << " Note: You have already added quiz" << endl;
								cout << " want to add again? y/n: ";
								cin >> dec;
								if (dec == 'y')
								{
									this->DB->select("DELETE FROM `quiz` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + this->subject + "'; ");
									isQuiz = false;
								}
							}
							if (!isQuiz && this->insertData("quiz"))
							{
								cout << " Quiz Added Successfully" << endl;
								isQuiz = true;
							}
						}
						else if (in == 4)
						{
							if (isMids)
							{
								cout << " Note: You have already added Mids" << endl;
								cout << " want to add again? y/n: ";
								cin >> dec;
								if (dec == 'y')
								{
									this->DB->select("DELETE FROM `mids` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + this->subject + "'; ");
									isMids = false;
								}
							}
							if (!isMids && this->insertData("mids"))
							{
								cout << " Mids Added Successfully" << endl;
								isMids = true;
							}
						}
						else if (in == 5)
						{
							if (isFinals)
							{
								cout << " Note: You have already added Finals" << endl;
								cout << " want to add again? y/n: ";
								cin >> dec;
								if (dec == 'y')
								{
									this->DB->select("DELETE FROM `finals` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + this->subject + "'; ");
									isFinals = false;
								}
							}
							if (!isFinals && this->insertData("finals"))
							{
								cout << " Finals Added Successfully" << endl;
								isFinals = true;
							}
						}
						else if (in == 6)
						{
							if (isPP)
							{
								cout << " Note: You have already added Project" << endl;
								cout << " want to add again? y/n: ";
								cin >> dec;
								if (dec == 'y')
								{
									this->DB->select("DELETE FROM `projectpresentation` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + this->subject + "'; ");
									isPP = false;
								}
							}
							if (!isPP && this->insertData("projectPresentation"))
							{
								cout << " Project Added Successfully" << endl;
								isPP = true;
							}
						}
					}
				}
				else
					cout << " Subject can't be added" << endl;
			}
			else if (in == 2)
				this->printGrades();
			else if (in == 3)
				this->printResult();
			else if (in == 4)
				this->printSoftCopy();
			else if (in == 5)
				this->modifySubject();
			else if (in == 6)
				this->modifySubject(1);
			else if (in == 7)
			{
				system("CLS");
				cin.ignore();
				this->student();
			}
			else if (in == 8)
			{
				cout << " Want to delete Record of: " << this->S->getRegNo() << endl;
				cout << " Press Y for yes and N for no: ";
				cin >> dec;
				if (dec == 'y' || dec == 'Y')
				{
					system("CLS");
					this->DB->select("DELETE FROM `student` WHERE `regNo` = '" + this->S->getRegNo() + "'; ");
					cout << " STUDENT RECORD DELETED SUCCESSFULL" << endl;
					cin.ignore();
					this->student();
				}
				else
					cout << " DECLINED" << endl;
			}
		}
		if (this->DB->disconnect())
			cout << " DATABASE DISCONNECTED SUCCESSFULLY";
	}
	else
		cout << " DATABASE CONNECTION FAILED" << endl;
}
void Calculator::student()
{
	if (this->S)
		delete this->S;
	string name = "", regNo = "";
	while (name == "")
	{
		cout << " Enter Student Name: ";
		getline(cin, name);
	}
	while (regNo == "")
	{
		cout << " Enter Registration No: ";
		getline(cin, regNo);
	}
	this->S = new Student(name, regNo);
	this->DB->insert("INSERT INTO `student` VALUES ('" + regNo + "','" + name + "',NULL,NULL);");
}
int Calculator::menu()
{
	int in = -1, flag = 0;
	cout << " +---------------------------------------+" << endl;
	cout << " | ******** * GPA CALCULATOR * ********* |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " | Press [1]: To Add Subject             |" << endl;
	cout << " | Press [2]: To Get Grades              |" << endl;
	cout << " | Press [3]: To Get Result              |" << endl;
	cout << " | Press [4]: To Get Result in SoftCopy  |" << endl;
	cout << " | Press [5]: To Modify Subject          |" << endl;
	cout << " | Press [6]: To Delete Subject          |" << endl;
	cout << " | Press [7]: To Change Student          |" << endl;
	cout << " | Press [8]: To Delete Student Record   |" << endl;
	cout << " | Press [9]: To Exit                    |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " Enter Choice: ";
	while (in < 0 || in > 9)
	{
		if (flag)
			cout << " Invalid Input Enter again: ";
		cin >> in;
		flag = 1;
	}
	return in;
}

int Calculator::subjectMenu()
{
	int in = -1, flag = 0;
	this->printAssesData();
	cout << " +---------------------------------------+" << endl;
	cout << " | ******** *  SUBJECT MENU  * ********* |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " | Press [1]: To add Assignment          |" << endl;
	cout << " | Press [2]: To add CP                  |" << endl;
	cout << " | Press [3]: To add Quiz                |" << endl;
	cout << " | Press [4]: To add Mids                |" << endl;
	cout << " | Press [5]: To add Finals              |" << endl;
	cout << " | Press [6]: To add Project             |" << endl;
	cout << " | Press [7]: To Exit                    |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " Enter Choice: ";
	while (in < 0 || in > 7)
	{
		if (flag)
			cout << " Invalid Input Enter again: ";
		cin >> in;
		flag = 1;
	}
	return in;
}

int Calculator::modificationMenu()
{
	int in = -1, flag = 0;
	cout << " +---------------------------------------+" << endl;
	cout << " | ******* * MODIFICATION MENU * ******* |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " | Press [1]: To Modify Assignmet        |" << endl;
	cout << " | Press [2]: To Modify CP               |" << endl;
	cout << " | Press [3]: To Modify Quiz             |" << endl;
	cout << " | Press [4]: To Modify Mids             |" << endl;
	cout << " | Press [5]: To Modify Finals           |" << endl;
	cout << " | Press [6]: To Modify Project          |" << endl;
	cout << " | Press [7]: To Exit                    |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " | Note: Your previous data will delete  |" << endl;
	cout << " | when modify any of these asses        |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " Enter Choice: ";
	while (in < 0 || in > 7)
	{
		if (flag)
			cout << " Invalid Input Enter again: ";
		cin >> in;
		flag = 1;
	}
	return in;
}

void Calculator::printGrades(int flag)
{
	system("CLS");
	ofstream fout("result.txt", ios::app);
	this->DB->select("SELECT * FROM `subject` WHERE `regNo` = '" + this->S->getRegNo() + "' ORDER BY `grade`;");
	sql::ResultSet* R = this->DB->getResult();
	if (R->next()) {
		if (flag == 1)
		{
			fout << " | SUBJECT       Percentage      Grade   |" << endl;
		}
		else
		{
			cout << " +---------------------------------------+" << endl;
			cout << " |                 GRADES                |" << endl;
			cout << " +---------------------------------------+" << endl;
			cout << " | Note: Grades are calculated with the  |" << endl;
			cout << " | bases of UCP criteria                 |" << endl;
			cout << " +---------------------------------------+" << endl;
			cout << " | SUBJECT       Percentage      Grade   |" << endl;
		}
		this->DB->select("SELECT * FROM `subject` WHERE `regNo` = '" + this->S->getRegNo() + "' ORDER BY `grade`;");
		sql::ResultSet* R = this->DB->getResult();

		while (R->next())
		{
			string name = R->getString(2);
			string perc = R->getString(4);
			string grade = R->getString(5);
			if (perc == "")
				perc = "--";
			if (grade == "")
				grade = "--";
			name = this->styleDiff(name, 14);
			perc = this->styleDiff(perc, 16);
			grade = this->styleDiff(grade, 8);
			if (flag == 1)
				fout << " | " << name << perc << grade << "|" << endl;
			else
				cout << " | " << name << perc << grade << "|" << endl;
		}
		if (flag == 1)
			fout << " +---------------------------------------+" << endl;
		else
			cout << " +---------------------------------------+" << endl;
		fout.close();
	}
	else
		cout << "  Note: No Subject Added Yet" << endl;
}

void Calculator::printResult(int flag)
{
	ofstream fout("result.txt");
	if (flag == 1)
	{
		fout << " +---------------------------------------+" << endl;
		fout << " |                 RESULT                |" << endl;
		fout << " +---------------------------------------+" << endl;
		fout << " | regNo   Full Name        GPA     CGPA |" << endl;
	}
	else
	{
		system("CLS");
		cout << " +---------------------------------------+" << endl;
		cout << " |                 RESULT                |" << endl;
		cout << " +---------------------------------------+" << endl;
		cout << " | regNo   Full Name        GPA     CGPA |" << endl;
	}
	this->DB->select("SELECT * FROM `student` WHERE `regNo` = '" + this->S->getRegNo() + "';");
	sql::ResultSet* R = this->DB->getResult();

	while (R->next())
	{
		string regNo = R->getString(1);
		string name = R->getString(2);
		string GPA = R->getString(3);
		string CGPA = R->getString(4);
		if (CGPA == "")
			CGPA = "--";
		regNo = this->styleDiff(regNo, 4);
		name = this->styleDiff(name, 17);
		GPA = this->styleDiff(GPA, 8);
		CGPA = this->styleDiff(CGPA, 5);
		if (flag == 1)
			fout << " | " << regNo << "    " << name << GPA << CGPA << "|" << endl;
		else
			cout << " | " << regNo << "    " << name << GPA << CGPA << "|" << endl;
	}
	if (flag == 1)
		fout << " +---------------------------------------+" << endl;
	else
		cout << " +---------------------------------------+" << endl;
	fout.close();
}

void Calculator::printSoftCopy()
{
	system("CLS");
	this->printResult(1);
	this->printGrades(1);
	cout << " Your Result Has Been Printed in Soft Copy" << endl;
}

void Calculator::printAssesData()
{
	system("CLS");
	cout << " +---------------------------------------+" << endl;
	string subj = "Subject: " + this->subject;
	subj = this->styleDiff(subj, 37);
	cout << " | " << subj << " |" << endl;
	cout << " +---------------------------------------+" << endl;
	cout << " | Assessments ObtNo T.No   ObtPer T.Per |" << endl;
	this->printAssesDataHelper("Assignment");
	this->printAssesDataHelper("CP");
	this->printAssesDataHelper("Quiz");
	this->printAssesDataHelper("Mids");
	this->printAssesDataHelper("Finals");
	this->printAssesDataHelper("Project");
}

void Calculator::printAssesDataHelper(string asses)
{
	sql::ResultSet* R = nullptr;
	string obtNo = "", totalNo = "", obtPer = "", totalPer = "";
	if (asses == "Project")
		this->DB->select("SELECT `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage` FROM `ProjectPresentation` WHERE `regNo` = '" +
			this->S->getRegNo() + "' AND `subName` = '" + this->subject + "';");
	else
		this->DB->select("SELECT `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage` FROM `" + asses + "` WHERE `regNo` = '" +
			this->S->getRegNo() + "' AND `subName` = '" + this->subject + "';");
	R = this->DB->getResult();
	if (R->next())
	{
		obtNo = R->getString(1);
		totalNo = R->getString(2);
		obtPer = R->getString(3);
		totalPer = R->getString(4);
	}
	asses = this->styleDiff(asses, 10);
	cout << " | " << asses << ": ";
	if (obtNo != "")
	{
		obtNo = this->styleDiff(obtNo, 6);
		totalNo = this->styleDiff(totalNo, 7);
		obtPer = this->styleDiff(obtPer, 7);
		totalPer = this->styleDiff(totalPer, 5);
		cout << obtNo << totalNo << obtPer << totalPer << " |" << endl;
	}
	else
		cout << "  --- Data Not Found ---  |" << endl;
}

int Calculator::getKey(const string asses)
{
	int k = 0;
	if (this->DB->select("SELECT `ID` FROM " + asses + " where regNo = '" + this->S->getRegNo() + "' AND `subName` = '" + this->subject + "';"));
	{
		sql::ResultSet* R = this->DB->getResult();
		if (R->next())
		{
			return stoi(R->getString(1));
		}
	}
	return 0;
}

bool Calculator::addSubject()
{
	cin.ignore();
	string subName = "", grade = "";
	int creditHours = 0; float gradePoints = 0.f;
	cout << " +---------------------------------------+" << endl;
	cout << " |                SUBJECT                |" << endl;
	cout << " +---------------------------------------+" << endl;
	while (subName == "")
	{
		cout << " Enter Subject Name: ";
		getline(cin, subName);
	}
	while (creditHours <= 0)
	{
		cout << " Enter Credit Hours: ";
		cin >> creditHours;
	}

	if (this->DB->select("INSERT INTO `subject` VALUES ('" + this->S->getRegNo() + "','" + subName + "'," + to_string(round(creditHours)) + ",NULL, NULL, NULL);"))
	{
		this->subject = subName;
		return true;
	}
	return false;
}

bool Calculator::insertData(const string asses)
{
	float totalNo = 0, totalPerc = 0.f, num = -1.f;
	int count = 1, flag = 0;
	system("CLS");
	if (asses == "assignment") {
		cout << " +---------------------------------------+" << endl;
		cout << " |              ASSIGNMENT               |" << endl;
		flag = 1;
	}
	else if (asses == "quiz") {
		cout << " +---------------------------------------+" << endl;
		cout << " |                 QUIZ                  |" << endl;
		flag = 3;
	}
	else if (asses == "cp") {
		cout << " +---------------------------------------+" << endl;
		cout << " |          CLASS PARTICIPATION          |" << endl;
		flag = 2;
	}
	else if (asses == "mids") {
		cout << " +---------------------------------------+" << endl;
		cout << " |                 MIDS                  |" << endl;
		flag = 4;
	}
	else if (asses == "finals") {
		cout << " +---------------------------------------+" << endl;
		cout << " |                FINALS                 |" << endl;
		flag = 5;
	}
	else {
		cout << " +---------------------------------------+" << endl;
		cout << " |         PROJECT PRESENTATION          |" << endl;
		flag = 6;
	}
	cout << " +---------------------------------------+" << endl;
	cout << " | Note: Enter Digit < 0 to break the    |" << endl;
	cout << " | Loop after inserting all numbers      |" << endl;
	cout << " +---------------------------------------+" << endl;
	while (totalNo <= 0)
	{
		cout << " Enter Total Numbers: ";
		cin >> totalNo;
	}
	while (totalPerc <= 0)
	{
		cout << " Enter Total Percentage: ";
		cin >> totalPerc;
	}

	if (this->DB->select("CALL `Insert" + asses + "`('" + this->S->getRegNo() + "','" + this->subject + "'," + to_string(round(totalNo)) + ", " + to_string(round(totalPerc)) + "); "))
	{
		int key = this->getKey(asses);
		while (1)
		{
			cout << " Enter Num in : ";
			cin >> num;
			if (num < 0)
				break;
			if (!this->DB->insert("INSERT INTO `" + asses + "Numbers` values(" + to_string(key) + ", " + to_string(round(num)) + "); "))
			{
				return false;
			}
		}
		this->updateData(key, flag);
		return true;
	}
	return false;
}

void Calculator::updateData(int key, int flag)
{
	if (flag == 1)
		this->DB->select("CALL `UpdateAssignment`(" + to_string(key) + ",'" + this->subject + "','" + this->S->getRegNo() + "');");
	else if (flag == 2)
		this->DB->select("CALL `UpdateCP`(" + to_string(key) + ",'" + this->subject + "','" + this->S->getRegNo() + "');");
	else if (flag == 3)
		this->DB->select("CALL `UpdateQuiz`(" + to_string(key) + ",'" + this->subject + "','" + this->S->getRegNo() + "');");
	else if (flag == 4)
		this->DB->select("CALL `UpdateMids`(" + to_string(key) + ",'" + this->subject + "','" + this->S->getRegNo() + "');");
	else if (flag == 5)
		this->DB->select("CALL `UpdateFinals`(" + to_string(key) + ",'" + this->subject + "','" + this->S->getRegNo() + "');");
	else if (flag == 6)
		this->DB->select("CALL `UpdateProjectPresentation`(" + to_string(key) + ",'" + this->subject + "','" + this->S->getRegNo() + "');");
	else
	{
		cout << " Error: Invalid Calls" << endl;
		return;
	}
	this->DB->select("CALL `calculateSubjectPercentage`('" + this->S->getRegNo() + "','" + this->subject + "');");
	this->DB->select("CALL `CalculateGradeAndGradePoints`('" + this->S->getRegNo() + "','" + this->subject + "');");
	this->DB->select("CALL `CalculateGPA` ('" + this->S->getRegNo() + "');");
}

void Calculator::modifySubject(int flag)
{
	system("CLS");
	if (flag == 1) {
		cout << " +---------------------------------------+" << endl;
		cout << " |            DELETE SUBJECT             |" << endl;
		cout << " +---------------------------------------+" << endl;

	}
	else {
		cout << " +---------------------------------------+" << endl;
		cout << " |         MODIFICATION SUBJECT          |" << endl;
		cout << " +---------------------------------------+" << endl;
	}
	this->DB->select("SELECT `subName` FROM `subject` WHERE `regNo` = '" + this->S->getRegNo() + "';");
	sql::ResultSet* R = this->DB->getResult();
	vector<string> sub;
	while (R->next())
		sub.push_back(R->getString(1));
	if (sub.size() == 0)
	{
		cout << " |    You Have not Added Subjects Yet    |" << endl;
		return;
	}
	else
		cout << " |     You Have Added These Subjects     |" << endl;
	string s = "";
	for (int i = 0; i < sub.size(); i++)
	{
		s = "[" + to_string(i + 1) + "]: " + sub[i];
		s = this->styleDiff(s, 38);
		cout << " | " << s << "|" << endl;
	}
	cout << " +---------------------------------------+" << endl;

	char dec = {}; bool isFound = false;
	cout << " Enter Name: ";
	cin >> s;
	for (auto& i : sub)
	{
		if (i == s)
			isFound = true;
	}
	if (!isFound)
	{
		cout << " Invalid Input! Declined Changes" << endl;
		return;
	}
	this->subject = s;
	if (flag == 1) {
		this->DB->select("DELETE FROM `subject` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + s + "';");
		cout << " Subject Deleted Successfully" << endl;
		return;
	}
	while (1)
	{
		this->printAssesData();
		int in = this->modificationMenu();
		if (in == 7)
			break;
		else if (in == 1)
		{
			this->DB->select("DELETE FROM `assignment` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + s + "'; ");
			this->insertData("assignment");
		}
		else if (in == 2)
		{
			this->DB->select("DELETE FROM `cp` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + s + "'; ");
			this->insertData("cp");
		}
		else if (in == 3)
		{
			this->DB->select("DELETE FROM `quiz` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + s + "'; ");
			this->insertData("quiz");
		}
		else if (in == 4)
		{
			this->DB->select("DELETE FROM `mids` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + s + "'; ");
			this->insertData("mids");
		}
		else if (in == 5)
		{
			this->DB->select("DELETE FROM `finals` WHERE `regNo` = '" + this->S->getRegNo() + "' ;");
			this->insertData("finals");
		}
		else if (in == 6)
		{
			this->DB->select("DELETE FROM `projectpresentation` WHERE `regNo` = '" + this->S->getRegNo() + "' AND `subName` = '" + s + "'; ");
			this->insertData("projectpresentation");
		}
	}
	system("CLS");
	cout << " MODIFICATION DONE" << endl;
}

string Calculator::styleDiff(string data, int diff)
{
	int dif = abs(int((data.size() - diff)));
	for (; dif > 0; dif--)
		data += " ";
	return data;
}
