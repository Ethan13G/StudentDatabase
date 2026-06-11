// Lab05 Student-Record-System
// Specification File Student-Record-System.h
// Ethan Gee

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STUDENTS = 23, NUM_ASSIGNMENTS = 5;

struct Student
{
	string firstName, lastName;
	int id;
	double grade;
};

// Loads student data from a file into the students array and updates the count of students
void loadStudents(Student students[], int& count);

// Displays all student information
void displayAllStudentInfo(double grades[][NUM_ASSIGNMENTS], Student students[], int count, int highlightID = -1, int highlightAssignment = -1);

// Assigns random grades to each student for each assignment, ensuring that the grades are between 60 and 100
void generateGrades(double grades[][NUM_ASSIGNMENTS], int count);

// Calculates the average grade for each student and updates the grade field in the Student struct
void calculateAverages(double grades[][NUM_ASSIGNMENTS], Student students[], int count);

// Update the grade for a specific assignment for a student
void updateAssignment(double grades[][NUM_ASSIGNMENTS], Student students[], int count);

// Searches for a student by ID and displays their information if found
void addStudent(Student students[], double grades[][NUM_ASSIGNMENTS], int& count);

// Saves all student data back to a file
void saveStudents(Student students[], int count);

// Highlights a specfic student row or an assignment column based on user input for better visibility
void highlightSearch(double grades[][NUM_ASSIGNMENTS], Student students[], int count);

