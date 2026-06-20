// Lab07 - Student Database: Linked List
// Client Code file - Main.cpp
// Ethan Gee

#include <iostream>
#include "Student.h"

using namespace std;

int main()
{
    // Replaced array with a single pointer tracking the start of the list
    StudentNode* head = nullptr;    //empty list, no nodes yet!

    loadStudents(head);             //load 90 students info from file
    calculateAllAverages(head);

    int choice;

    do
    {
        cout << "\n===== STUDENT DATABASE =====\n";
        cout << "1. Display Students\n";
        cout << "2. Search by Course\n";
        cout << "3. Assignment Averages\n";
        cout << "4. Hardest Assignment\n";
        cout << "5. Course Enrollment\n";
        cout << "6. Sort By Average\n";
        cout << "7. Add Student\n";
        cout << "8. At Risk Students\n";
        cout << "9. Save Student\n";
        cout << "10. Exit\n";
        cout << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: displayStudents(head); break;
        case 2: searchByCourse(head); break;
        case 3: showAssignmentAverage(head); break;
        case 4: showHardestAssignment(head); break;
        case 5: courseEnrollment(head); break;
        case 6: sortByAverage(head); displayStudents(head); break;
        case 7: addStudent(head); break;
        case 8: atRiskStudents(head);  break;
        case 9: saveStudents(head); break;
		case 10: cout << "\nExiting program..." << endl; break;
		default: cout << "\nInvalid choice. Please enter a number between 1 and 10." << endl; break;
        }

    } while (choice != 10);

    // Free all dynamically allocated memory before program exit
    deleteList(head);
    cout << "Memory cleared safely. Goodbye!" << endl;
}