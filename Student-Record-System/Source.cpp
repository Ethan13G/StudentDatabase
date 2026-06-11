// Lab05 Student-Record-System
// Client Code File Source.cpp
// Ethan Gee

#include "Student-Record-System.h"

using namespace std;

int main()
{
    srand(time(0));

	Student students[MAX_STUDENTS]; // 23 max students
	double grades[MAX_STUDENTS][NUM_ASSIGNMENTS]; 
	int count = 0, choice;

	loadStudents(students, count);
	generateGrades(grades, count); // Initializes grades for existing students
	calculateAverages(grades, students, count);

	do
	{
		cout << "\n----- Student Record System -----" << endl
			<< "1. Display All Student Info" << endl
			<< "2. Update Assignment" << endl
			<< "3. Add Student" << endl
			<< "4. Save to File" << endl
			<< "5. Highlight Student / Assignment" << endl
			<< "6. Exit" << endl;

		cout << "Please enter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			displayAllStudentInfo(grades, students, count);
			break;

		case 2:
			updateAssignment(grades, students, count);
			break;

		case 3:
			addStudent(students, grades, count);
			break;

		case 4:
			saveStudents(students, count);
			break;

		case 5:
			highlightSearch(grades, students, count);
			break;

		case 6:
			cout << "Exiting program. Goodbye!" << endl;
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}

	} while (choice != 6);

    return 0;
}


