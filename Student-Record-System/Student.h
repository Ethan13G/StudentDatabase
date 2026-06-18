// Lab07 - Student Database: Linked List
// Specification file - Student.h
// Ethan Gee

#pragma once

#include <string>

using namespace std;

// ================= CONSTANTS =================
const int STUDENT_MAX = 100;
const int NUM_ASSIGNMENTS = 5;
const int NUM_COURSES = 3;

// ================= STRUCT =================
struct Student
{
    string firstName;
    string lastName;
    int id; // Note: Kept as int to match your Lab 6 precisely

    double assignments[NUM_ASSIGNMENTS];
    double average;

    string courses[NUM_COURSES];
};

// ================= LINKED LIST NODE =================
struct StudentNode
{
    Student data;         // Original struct used as cargo
    StudentNode* next;    // Link to the next student
};

// ================= FUNCTION PROTOTYPES =================
void loadStudents(StudentNode*& head);
void displayStudents(StudentNode* head);

void calculateAverage(Student* s);
void calculateAllAverages(StudentNode* head);

void searchByCourse(StudentNode* head);
void showAssignmentAverage(StudentNode* head);
void showHardestAssignment(StudentNode* head);
void courseEnrollment(StudentNode* head);

void sortByAverage(StudentNode* head);

void addStudent(StudentNode*& head);
void atRiskStudents(StudentNode* head);
void saveStudents(StudentNode* head);

void deleteList(StudentNode*& head); // New cleanup function requirement