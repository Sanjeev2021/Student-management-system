#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

const int MAX_STUDENTS = 500;  // Renamed from 'size' to avoid conflicts

class Student
{
public:
    string name;
    string program;
    int rollno;
    float cgpa;
    string cnic;
    string phone;

    void show_all_students(Student s[], int currentSize);
    void search_by_rollno(Student s[], int rollno, int currentSize);
    void find_max_cgpa(Student s[], int currentSize);
    void sortby_name(Student s[], int currentSize);
    void sortby_cgpa(Student s[], int currentSize);
    void add_new_student(Student s[], int &currentSize);
    void save_students_to_file(Student s[], int currentSize, const string &filename);
};

void Student::show_all_students(Student s[], int currentSize)
{
    for (int i = 0; i < currentSize; i++)
    {
        cout << "Name of the student: " << s[i].name << '\t'
             << "Cnic of the Student: " << s[i].cnic << '\t'
             << "Roll no of the student: " << s[i].rollno << '\t'
             << "CGPA: " << s[i].cgpa << '\t'
             << "Degree Program: " << s[i].program << '\t'
             << "Phone Number of the student: " << s[i].phone << endl;
    }
}

void Student::search_by_rollno(Student s[], int rollno, int currentSize)
{
    bool found = false;
    for (int i = 0; i < currentSize; i++)
    {
        if (s[i].rollno == rollno)
        {
            found = true;
            cout << "Name of the student: " << s[i].name << '\t'
                 << "Cnic of the Student: " << s[i].cnic << '\t'
                 << "Roll no of the student: " << s[i].rollno << '\t'
                 << "CGPA: " << s[i].cgpa << '\t'
                 << "Degree Program: " << s[i].program << '\t'
                 << "Phone Number of the student: " << s[i].phone << endl;
        }
    }
    if (!found)
    {
        cout << "Student with the following roll no is not found!" << endl;
    }
}

void Student::find_max_cgpa(Student s[], int currentSize)
{
    float max_cgpa = s[0].cgpa;
    int index = 0;
    for (int i = 1; i < currentSize; i++)
    {
        if (s[i].cgpa > max_cgpa)
        {
            max_cgpa = s[i].cgpa;
            index = i;
        }
    }
    cout << "Student with the maximum CGPA is: " << endl;
    cout << "Name of the student: " << s[index].name << '\t'
         << "Cnic of the Student: " << s[index].cnic << '\t'
         << "Roll no of the student: " << s[index].rollno << '\t'
         << "CGPA: " << s[index].cgpa << '\t'
         << "Degree Program: " << s[index].program << '\t'
         << "Phone Number of the student: " << s[index].phone << endl;
}

void Student::sortby_name(Student s[], int currentSize)
{
    for (int i = 0; i < currentSize - 1; i++)
    {
        for (int j = 0; j < currentSize - i - 1; j++)
        {
            if (s[j].name > s[j + 1].name)
            {
                Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
    cout << "Students sorted by name are: " << endl;
    show_all_students(s, currentSize);  // Reuse existing function instead of duplicating code
}

void Student::sortby_cgpa(Student s[], int currentSize)
{
    for (int i = 0; i < currentSize - 1; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < currentSize; j++)
        {
            if (s[j].cgpa > s[max_index].cgpa)
            {
                max_index = j;
            }
        }
        Student temp = s[max_index];
        s[max_index] = s[i];
        s[i] = temp;
    }
    cout << "Students with sorted CGPA's are: " << endl;
    show_all_students(s, currentSize);  // Reuse existing function instead of duplicating code
}

void Student::add_new_student(Student s[], int &currentSize)
{
    if (currentSize >= MAX_STUDENTS)
    {
        cout << "Cannot add students! Maximum capacity reached." << endl;
        return;
    }
    Student newStudent;
    cout << "Enter the name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter the Cnic: ";
    getline(cin, newStudent.cnic);
    cout << "Enter the roll no: ";
    cin >> newStudent.rollno;
    cout << "Enter the Cgpa: ";
    cin >> newStudent.cgpa;
    cout << "Enter the degree program(BTech/MTech): ";
    cin.ignore();
    getline(cin, newStudent.program);
    cout << "Enter the phone number: ";
    getline(cin, newStudent.phone);
    s[currentSize] = newStudent;
    currentSize++;
    cout << "Student has been added successfully!" << endl;
}

void Student::save_students_to_file(Student s[], int currentSize, const string &filename)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cout << "Unable to open the file for writing!" << endl;
        return;
    }
    outfile << "Name\tCNIC\tRollNo\tCGPA\tProgram\tPhone" << endl;
    for (int i = 0; i < currentSize; i++)
    {
        outfile << s[i].name << '\t'
                << s[i].cnic << '\t'
                << s[i].rollno << '\t'
                << s[i].cgpa << '\t'
                << s[i].program << '\t'
                << s[i].phone << endl;
    }
    outfile.close();
    cout << "Students have been saved successfully!" << endl;
}

int main()
{
    Student students[MAX_STUDENTS];  // Changed array name to be more descriptive
    Student studentObj;  // Create an object to call member functions
    
    ifstream infile("Student.txt");
    string line;
    int currentSize = 0;
    
    // Skip header line
    getline(infile, line);
    
    while (getline(infile, line) && currentSize < MAX_STUDENTS)
    {
        stringstream ss(line);
        ss >> students[currentSize].name 
           >> students[currentSize].cnic 
           >> students[currentSize].rollno 
           >> students[currentSize].cgpa 
           >> students[currentSize].program 
           >> students[currentSize].phone;
        currentSize++;
    }
    infile.close();

    int choice;
    do
    {
        cout << "\n--------MENU--------" << endl;
        cout << "1. Show All Students" << endl;
        cout << "2. Search a student by roll no" << endl;
        cout << "3. Find the student with max CGPA" << endl;
        cout << "4. Sort the students by name" << endl;
        cout << "5. Sort the students by CGPA" << endl;
        cout << "6. Add a new student" << endl;
        cout << "7. Save the students to the file" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            studentObj.show_all_students(students, currentSize);
            break;
        case 2:
        {
            int rollno;
            cout << "Enter the roll no to be searched: ";
            cin >> rollno;
            studentObj.search_by_rollno(students, rollno, currentSize);
            break;
        }
        case 3:
            studentObj.find_max_cgpa(students, currentSize);
            break;
        case 4:
            studentObj.sortby_name(students, currentSize);
            break;
        case 5:
            studentObj.sortby_cgpa(students, currentSize);
            break;
        case 6:
            studentObj.add_new_student(students, currentSize);
            break;
        case 7:
            studentObj.save_students_to_file(students, currentSize, "Student.txt");
            break;
        case 8:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    } while (choice != 8);
    return 0;
}