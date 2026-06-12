// Lab06 - Student Record System (Enhanced)
// Implementation file - Student.cpp
// Ethan Gee

#include "Student.h"
#include <fstream>
#include <iomanip>

using namespace std;

// Load students from file
void loadStudents(Student students[], int& count)
{
    ifstream fin("Students90.txt");

    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    count = 0;

    while (count < STUDENT_MAX)
    {
        fin >> students[count].firstName
            >> students[count].lastName
            >> students[count].id;

        if (fin.fail())
        {
            break;
        }

        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            fin >> students[count].assignments[i];
        }

        fin >> students[count].average;

        for (int i = 0; i < NUM_COURSES; i++)
        {
            fin >> students[count].courses[i];
        }

        count++;
    }

    fin.close();
}

// ================= DISPLAY =================
void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].assignments[j] << "\t";

        cout << students[i].average << "\t";

        for (int j = 0; j < NUM_COURSES; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
    }
}

// Calculate average for a single student
void calculateAverage(Student* s)
{
	
}

// Calculate averages for all students
void calculateAllAverages(Student students[], int count)
{

}

// Search for students taking a specfic course
void searchByCourse(Student students[], int count)
{
    string course;
    bool found = false;

    if (count == 0)
    {
        cout << "No students loaded.\n";
        return;
    }

    cout << "\nEnter course code: ";
    cin >> course;

    cout << "\nStudents enrolled in " << course << ":\n";

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (students[i].courses[j] == course)
            {
                cout << students[i].id << " " 
                    << students[i].firstName << " " 
                    << students[i].lastName << endl;

                found = true;
                break; 
            }
        }
    }

    if (!found)
    {
        cout << "No students found in that course.\n";
    }
}

// Show average for each assignment
void showAssignmentAverage(Student students[], int count)
{
    double total;

    cout << fixed << setprecision(4);

    if (count == 0)
    {
        cout << "No students loaded.\n";
        return;
    }

    cout << "\nAssignment Averages\n";
    cout << string(19, '-') << endl;

    for (int assignment = 0; assignment < NUM_ASSIGNMENTS; assignment++)
    {
        total = 0;

        for (int student = 0; student < count; student++)
        {
            total += students[student].assignments[assignment];
        }

        cout << "A" << assignment + 1 << ": "
            << total / count << endl;
    }
}

// Show the hardest assignment
void showHardestAssignment(Student students[], int count)
{
    double lowestAverage = 0;
    int hardestAssignment = 0;

    cout << fixed << setprecision(4);

    if (count == 0)
    {
        cout << "No students loaded.\n";
        return;
    }

    for (int assignment = 0; assignment < NUM_ASSIGNMENTS; assignment++)
    {
        double total = 0;

        for (int student = 0; student < count; student++)
        {
            total += students[student].assignments[assignment];
        }

        double average = total / count;

        if (assignment == 0 || average < lowestAverage)
        {
            lowestAverage = average;
            hardestAssignment = assignment;
        }
    }

    cout << "\nHardest Assignment: A"
        << hardestAssignment + 1
        << " (" << lowestAverage << ")" << endl;
}

// Show course enrollment numbers
void courseEnrollment(Student students[], int count)
{
    string countedCourses[STUDENT_MAX * NUM_COURSES];
    int uniqueCount = 0; // Number of unique courses currently stored in countedCourses

    if (count == 0)
    {
        cout << "No students loaded.\n";
        return;
    }

    cout << "\nCourse Enrollment\n";
    cout << string(17, '-') << endl;

    for (int i = 0; i < count; i++) // Check every course for every student
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            string currentCourse = students[i].courses[j];

            bool alreadyCounted = false; // Assume this course has not been processed yet

			for (int k = 0; k < uniqueCount; k++) // Check if this course has already been processed
            {
                if (countedCourses[k] == currentCourse)
                {
                    alreadyCounted = true;
                    break;
                }
            }

            if (!alreadyCounted) // New course found - counts how many students are enrolled in it
            {
                int enrollment = 0;

                for (int s = 0; s < count; s++)
                {
                    for (int c = 0; c < NUM_COURSES; c++)
                    {
                        if (students[s].courses[c] == currentCourse)
                        {
                            enrollment++;
                            break; // count each student only once
                        }
                    }
                }

                cout << currentCourse << ": "
                    << enrollment << endl;

                countedCourses[uniqueCount] = currentCourse;
                uniqueCount++;
            }
        }
    }
}

// Sort students by average grade
void sortByAverage(Student students[], int count)
{

}

// Add a new student
void addStudent(Student students[], int& count)
{

}

// Show at-risk students (at least one assignment below 50 and have an average between 50 and 59)
void atRiskStudents(Student students[], int count)
{
    bool found = false;

    cout << "\nAt-Risk Students\n";
    cout << string(16, '-') << endl;

    for (int i = 0; i < count; i++)
    {
        bool hasLowAssignment = false;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)  // Check if any assignment is below 50
        {
            if (students[i].assignments[j] < 50)
            {
                hasLowAssignment = true;
                break;
            }
        }

        if (hasLowAssignment &&  // Check both conditions
            students[i].average >= 50 &&
            students[i].average <= 59)
        {
            cout << students[i].id << " "
                << students[i].firstName << " "
                << students[i].lastName << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No at-risk students found.\n";
    }
}

// Save students to file
void saveStudents(Student students[], int count)
{

}