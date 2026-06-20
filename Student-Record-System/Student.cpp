// Lab07 - Student Database: Linked List
// Implementation file - Student.cpp
// Ethan Gee

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.h"

using namespace std;

// ================= LOAD STUDENTS =================
void loadStudents(StudentNode*& head)
{
    ifstream file("Students90.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    // We no longer need a tail pointer tracking block here
    Student tempStudent;

    while (file >> tempStudent.firstName
        >> tempStudent.lastName
        >> tempStudent.id)
    {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            file >> tempStudent.assignments[j];

        file >> tempStudent.average;

        for (int j = 0; j < NUM_COURSES; j++)
            file >> tempStudent.courses[j];

        // 1. Allocate a brand new node on the heap
        StudentNode* newNode = new StudentNode();
        newNode->data = tempStudent;

        // 2. Point the new node's next to whatever the current head is pointing to
        newNode->next = head;

        // 3. Move the head pointer to point to our newly created node
        head = newNode;
    }

    file.close();
}

// ================ DISPLAY STUDENTS ================
void displayStudents(StudentNode* head)
{
    cout << fixed << setprecision(1); // Added this for output formatting

    cout << "\n"
        << setw(8) << "ID"
        << setw(15) << "LName"
        << setw(15) << "FName";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << setw(6) << ("A" + to_string(j + 1));

    cout << setw(8) << "AVG"
        << setw(10) << "C1"
        << setw(10) << "C2"
        << setw(10) << "C3"
        << endl;

    StudentNode* current = head;

    while (current != nullptr)
    {
        cout << setw(8) << current->data.id
            << setw(15) << current->data.lastName
            << setw(15) << current->data.firstName;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << setw(6) << current->data.assignments[j];

        cout << setw(8) << current->data.average;

        for (int j = 0; j < NUM_COURSES; j++)
            cout << setw(10) << current->data.courses[j];

        cout << endl;

        current = current->next; // move to next node
    }
}

// Calculate average for a single student
void calculateAverage(Student* s)
{
    if (s == nullptr)
        return;

    double total = 0;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        total += s->assignments[i];
    }

    s->average = total / NUM_ASSIGNMENTS;
}

// Calculate averages for all students
void calculateAllAverages(StudentNode* head)
{
    StudentNode* current = head;

    while (current != nullptr)
    {
        calculateAverage(&current->data);
        current = current->next;
    }
}

// Search for students taking a specfic course
void searchByCourse(StudentNode* head)
{
    string course;
    bool found = false;

    if (head == nullptr)
    {
        cout << "No students loaded.\n";
        return;
    }

    cout << "\nEnter course code: ";
    cin >> course;

    cout << "\nStudents enrolled in " << course << ":\n";

    StudentNode* current = head;

    while (current != nullptr)
    {
        for (int i = 0; i < NUM_COURSES; i++)
        {
            if (current->data.courses[i] == course)
            {
                cout << current->data.id << " "
                    << current->data.firstName << " "
                    << current->data.lastName << endl;

                found = true;
                break;
            }
        }

        current = current->next;
    }

    if (!found)
    {
        cout << "No students found in that course.\n";
    }
}

// Show average for each assignment
void showAssignmentAverage(StudentNode* head)
{
    if (head == nullptr)
    {
        cout << "No students loaded.\n";
        return;
    }

    cout << fixed << setprecision(4);
    cout << "\nAssignment Averages\n";
    cout << string(19, '-') << endl;

    for (int assignment = 0; assignment < NUM_ASSIGNMENTS; assignment++)
    {
        double total = 0;
        int count = 0;

        StudentNode* current = head;

        while (current != nullptr)
        {
            total += current->data.assignments[assignment];
            count++;
            current = current->next;
        }

        cout << "A" << assignment + 1 << ": "
            << total / count << endl;
    }
}

// Show the hardest assignment
void showHardestAssignment(StudentNode* head)
{
    cout << fixed << setprecision(4);

    if (head == nullptr)
    {
        cout << "No students loaded.\n";
        return;
    }

    double lowestAverage = 0;
    int hardestAssignment = 0;

    for (int assignment = 0; assignment < NUM_ASSIGNMENTS; assignment++)
    {
        double total = 0;
        int count = 0;

        StudentNode* current = head;

        while (current != nullptr)
        {
            total += current->data.assignments[assignment];
            count++;
            current = current->next;
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
void courseEnrollment(StudentNode* head)
{
    string countedCourses[STUDENT_MAX * NUM_COURSES];
    int uniqueCount = 0;

    if (head == nullptr)
    {
        cout << "No students loaded.\n";
        return;
    }

    cout << "\nCourse Enrollment\n";
    cout << string(17, '-') << endl;

    StudentNode* current = head;

    // Traverse linked list
    while (current != nullptr)
    {
        for (int i = 0; i < NUM_COURSES; i++)
        {
            string currentCourse = current->data.courses[i];

            bool alreadyCounted = false;

            // Check if course was already processed
            for (int j = 0; j < uniqueCount; j++)
            {
                if (countedCourses[j] == currentCourse)
                {
                    alreadyCounted = true;
                    break;
                }
            }

            if (!alreadyCounted)
            {
                int enrollment = 0;

                // Count how many students are in this course
                StudentNode* temp = head;

                while (temp != nullptr)
                {
                    for (int k = 0; k < NUM_COURSES; k++)
                    {
                        if (temp->data.courses[k] == currentCourse)
                        {
                            enrollment++;
                            break; // Count student once
                        }
                    }
                    temp = temp->next;
                }

                cout << currentCourse << ": " << enrollment << endl;

                countedCourses[uniqueCount] = currentCourse;
                uniqueCount++;
            }
        }

        current = current->next;
    }
}

// Sort students by average grade
void sortByAverage(StudentNode* head)
{
    if (head == nullptr)
    {
        cout << "No students loaded.\n";
        return;
    }

    bool swapped;

    do
    {
        swapped = false;

        StudentNode* current = head;

        while (current->next != nullptr)
        {
            if (current->data.average < current->next->data.average)
            {
                // Swap Student data (not nodes)
                Student temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = true;
            }

            current = current->next;
        }

    } while (swapped);
}

// Add a new student
void addStudent(StudentNode*& head)
{
    StudentNode* newNode = new StudentNode;

    newNode->next = nullptr;

    cout << "\nEnter first name: ";
    cin >> newNode->data.firstName;

    cout << "Enter last name: ";
    cin >> newNode->data.lastName;

    cout << "Enter ID: ";
    cin >> newNode->data.id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Enter Assignment " << i + 1 << ": ";
        cin >> newNode->data.assignments[i];
    }

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Enter Course " << i + 1 << ": ";
        cin >> newNode->data.courses[i];
    }

    calculateAverage(&newNode->data);

    newNode->next = head;
    head = newNode;

    cout << "Student added successfully.\n";
}

// Show at-risk students (at least one assignment below 50 and have an average between 50 and 59)
void atRiskStudents(StudentNode* head)
{
    bool found = false;

    if (head == nullptr)
    {
        cout << "No students loaded.\n";
        return;
    }

    cout << "\nAt-Risk Students\n";
    cout << string(16, '-') << endl;

    StudentNode* current = head;

    while (current != nullptr)
    {
        bool hasLowAssignment = false;

		// Check if any assignment is below 50
        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            if (current->data.assignments[i] < 50)
            {
                hasLowAssignment = true;
                break;
            }
        }

		// Check both conditions for at-risk status
        if (hasLowAssignment &&
            current->data.average >= 50 &&
            current->data.average <= 59)
        {
            cout << current->data.id << " "
                << current->data.firstName << " "
                << current->data.lastName << endl;

            found = true;
        }

        current = current->next;
    }

    if (!found)
    {
        cout << "No at-risk students found.\n";
    }
}

// Save students to file
void saveStudents(StudentNode* head)
{
    ofstream fout("Students90.txt");

    if (!fout)
    {
        cout << "Error opening file for writing.\n";
        return;
    }

    StudentNode* current = head;

    while (current != nullptr)
    {
        fout << current->data.firstName << " "
            << current->data.lastName << " "
            << current->data.id << " ";

        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            fout << current->data.assignments[i] << " ";
        }

        fout << current->data.average << " ";

        for (int i = 0; i < NUM_COURSES; i++)
        {
            fout << current->data.courses[i] << " ";
        }

        fout << endl;

        current = current->next;
    }

    fout.close();

    cout << "Students saved successfully.\n";
}

// Delete the linked list and free memory
void deleteList(StudentNode*& head)
{
    StudentNode* temp;

    while (head != nullptr)
    {
        temp = head;        
        head = head->next;  
        delete temp;        
    }

    head = nullptr; 
}