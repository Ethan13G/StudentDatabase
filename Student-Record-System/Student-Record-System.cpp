// Lab05 Student-Record-System
// Implementation File Student-Record-System.cpp
// Ethan Gee

#include "Student-Record-System.h"

// Loads student data from a file into the students array and updates the count of students
void loadStudents(Student students[], int& count)
{
    ifstream inputFile("students.txt");

    if (!inputFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    count = 0;

    while (count < MAX_STUDENTS &&
        inputFile >> students[count].firstName
        >> students[count].lastName
        >> students[count].id
		>> students[count].grade)
    {
        count++;
    }

    inputFile.close();
}

// Displays all student information
// Added optional parameters so I can reuse this function for the highlight search function to avoid duplicate code
void displayAllStudentInfo(double grades[][NUM_ASSIGNMENTS], Student students[], int count, int highlightID, int highlightAssignment)
{
    cout << left
        << setw(10) << "ID"
        << setw(15) << "FName"
        << setw(15) << "LName";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        cout << setw(6) << ("A" + to_string(j + 1));
    }

    cout << setw(8) << "AVG" << endl;

    cout << string(74, '-') << endl;

	for (int i = 0; i < count; i++)
	{
		bool highlightRow = (students[i].id == highlightID);

		if (highlightRow)
			cout << "\033[1;32m";

		cout << left
			<< setw(10) << students[i].id
			<< setw(15) << students[i].firstName
			<< setw(15) << students[i].lastName;

		for (int j = 0; j < NUM_ASSIGNMENTS; j++)
		{
			if (j == highlightAssignment - 1)
				cout << "\033[1;34m";

			cout << setw(6) << fixed << setprecision(0) << grades[i][j];

			if (j == highlightAssignment - 1)
				cout << "\033[0m";
		}

		cout << setw(8) << fixed << setprecision(1)
			<< students[i].grade;

		if (highlightRow)
			cout << "\033[0m";

		cout << endl;
	}
}

// Generate random grades for 5 assignments to each student
void generateGrades(double grades[][NUM_ASSIGNMENTS], int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < NUM_ASSIGNMENTS; j++)
		{
			grades[i][j] = rand() % 41 + 60; 
		}
	}
}

// Calculates the average grade for each student and updates the grade field in the Student struct
void calculateAverages(double grades[][NUM_ASSIGNMENTS], Student students[], int count)
{
	for (int i = 0; i < count; i++)
	{
		double sum = 0;

		for (int j = 0; j < NUM_ASSIGNMENTS; j++)
		{
			sum += grades[i][j];
		}

		students[i].grade = sum / NUM_ASSIGNMENTS;
	}
}

// Update the grade for a specific assignment for a student
void updateAssignment(double grades[][NUM_ASSIGNMENTS], Student students[], int count)
{
	int id, assignment, index = -1;
	double newGrade;

	do
	{
		cout << "Enter student ID: ";
		cin >> id;

		index = -1;

		for (int i = 0; i < count; i++)
		{
			if (students[i].id == id)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			cout << "Student not found. Try again.\n";
		}

	} while (index == -1);

	do
	{
		cout << "Enter assignment number (1-" << NUM_ASSIGNMENTS << "): ";
		cin >> assignment;

		if (assignment < 1 || assignment > NUM_ASSIGNMENTS)
		{
			cout << "Invalid assignment number. Try again.\n";
		}

	} while (assignment < 1 || assignment > NUM_ASSIGNMENTS);

	do
	{
		cout << "Enter new grade (0-100): ";
		cin >> newGrade;

		if (newGrade < 0 || newGrade > 100)
		{
			cout << "Invalid grade. Try again.\n";
		}

	} while (newGrade < 0 || newGrade > 100);

	grades[index][assignment - 1] = newGrade;

	cout << "Assignment grade updated successfully!" << endl << endl;

	calculateAverages(grades, students, count);
	displayAllStudentInfo(grades, students, count);
}

// Add a student
void addStudent(Student students[], double grades[][NUM_ASSIGNMENTS], int& count)
{
	Student newStudent;
	bool duplicate;
	int index;

	if (count >= MAX_STUDENTS)
	{
		cout << "Cannot add more students. Maximum capacity reached." << endl;
		return;
	}

	cout << "Enter first name: ";
	cin >> newStudent.firstName;

	cout << "Enter last name: ";
	cin >> newStudent.lastName;

	do
	{
		duplicate = false;

		cout << "Enter ID: ";
		cin >> newStudent.id;

		for (int i = 0; i < count; i++)
		{
			if (students[i].id == newStudent.id)
			{
				cout << "ID already exists. Try again.\n";
				duplicate = true;
				break;
			}
		}

	} while (duplicate);

	students[count] = newStudent;

	index = count;
	count++;

	for (int j = 0; j < NUM_ASSIGNMENTS; j++)
	{
		grades[index][j] = rand() % 41 + 60;
	}

	calculateAverages(grades, students, count);

	cout << "Student added successfully!" << endl << endl;

	displayAllStudentInfo(grades, students, count);
}

// Saves all student data back to a file
void saveStudents(Student students[], int count)
{
	ofstream outputFile("students.txt");

	if (!outputFile)
	{
		cout << "Error opening file!" << endl;
		return;
	}

	for (int i = 0; i < count; i++)
	{
		outputFile << students[i].firstName << " "
			<< students[i].lastName << " "
			<< students[i].id << " "
			<< students[i].grade << endl;
	}

	outputFile.close();

	cout << "Data saved successfully!" << endl;
}

// Highlights a specific student row or an assignment column based on user input for better visibility
void highlightSearch(double grades[][NUM_ASSIGNMENTS], Student students[], int count)
{
	int choice;
	int id, assignment;
	int index = -1;

	do
	{
		cout << "Highlight by:" << endl
			<< "1. Student ID" << endl
			<< "2. Assignment Number" << endl
			<< "Enter choice: ";
		cin >> choice;

		if (choice != 1 && choice != 2)
		{
			cout << "Invalid choice. Try again.\n";
		}

	} while (choice != 1 && choice != 2);

	if (choice == 1)
	{
		cout << "Enter Student ID: ";
		cin >> id;
		cout << endl;

		for (int i = 0; i < count; i++)
		{
			if (students[i].id == id)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			cout << "Student not found." << endl;
			return;
		}

		displayAllStudentInfo(grades, students, count, students[index].id, -1);
	}

	else
	{
		do
		{
			cout << "Enter Assignment Number (1-" << NUM_ASSIGNMENTS << "): ";
			cin >> assignment;
			cout << endl;

			if (assignment < 1 || assignment > NUM_ASSIGNMENTS)
			{
				cout << "Invalid assignment number. Try again.\n";
			}

		} while (assignment < 1 || assignment > NUM_ASSIGNMENTS);

		displayAllStudentInfo(grades, students, count, -1, assignment);
	}
}

