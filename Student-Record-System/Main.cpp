// Lab06 - Student Record System (Enhanced)
// Client Code file - Main.cpp
// Ethan Gee

#include "Student.h"

using namespace std;

int main()
{
	Student students[STUDENT_MAX];
	int count = 0;

	loadStudents(students, count);
	calculateAllAverages(students, count);

	int choice;

	do
	{
		cout << "\n===== STUDENT DATABASE =====\n";
		cout << "1. Display Students\n";
		cout << "2. Search by Course\n";
		cout << "3. Assignment Averages\n";
		cout << "4. Hardest Assignment\n";
		cout << "5. Course Enrollment\n";
		cout << "6. Sort by Averages\n";
		cout << "7. Add Student\n";
		cout << "8. At Risk Students\n";
		cout << "9. Save Students\n";
		cout << "10. Exit\n";
		cout << endl;
		cout << "Enter Choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			displayStudents(students, count);
			break;

		case 2:
			searchByCourse(students, count);
			break;
		

		case 3:
			showAssignmentAverage(students, count);
			break;

		case 4:
			showHardestAssignment(students, count);
			break;

		case 5:
			courseEnrollment(students, count);
			break;

		case 6:
			sortByAverage(students, count);
			displayStudents(students, count);
			break;

		case 7:
			addStudent(students, count);
			saveStudents(students, count);
			loadStudents(students, count);
			calculateAllAverages(students, count);
			displayStudents(students, count);
			break;

		case 8:
			atRiskStudents(students, count);
			break;

		case 9:
			saveStudents(students, count);
			break;

		case 10:
			cout << "\nExiting Program. Goodbye!" << endl;
			break;

		default:
			cout << "\nInvalid choice!" << endl;
		}//end of switch

	} while (choice != 10);

	return 0;
}//end of main