#include "course.h"
#include "Student.h"
#include "StudentGroup.h"
#include "logic_engine.h"
#include "SetOperations.h"
#include "SetOperationsH.h"
#include <iostream>
using namespace std;

int main() {
    
    CourseSchedule cs;
    cs.addCourse("CS101", "");
    cs.addCourse("CS102", "CS101");
    cs.addCourse("CS103", "CS102");
    cs.addCourse("Math101", "");

    cout << "All valid course sequences:" << endl;
    cs.generateOrder();

    StudentGroup sg;

    int n,nextId=0;
    cout << "Enter number of students: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name;
        cout << "Enter name of student " << i + 1 << ": ";
        cin >> name;

        Student* s = new Student(name, nextId);
        nextId++;
        sg.addStudent(s);

        int m;
        cout << "How many courses " << name << " wants to take? ";
        cin >> m;

        for (int j = 0; j < m; j++) {
            string course;
            cout << "Enter course " << j + 1 << ": ";
            cin >> course;

            sg.assignCourse(s, course, cs);
        }
    }

   /* int groupSize;
    cout << "Enter group size to generate: ";
    cin >> groupSize;
    cout << "Student groups of size " << groupSize << ":" << endl;
    sg.generateGroups(groupSize);*/

    //module4
    LogicEngine engine;

    engine.addRule("CS101", "Adeel", "LabA");
    engine.addRule("CS102", "DrKhan", "LabC");
    engine.printRules();

   
    cout << "Checking rule consistency:"<<endl;

    string course = "CS101";
    string prof = "Adeel";
    string lab = "LabA";   

    if (engine.checkConsistency(course, prof, lab)) {
        cout << "Allocation valid." << endl;
    }
    else {
        cout << "Allocation rejected." << endl;
    }
    //...........................SETS................MOdule5.
   
// ---------------- Module 5 SETS ------------------

    SetOperationsStudent csStudents;
    SetOperationsStudent mathStudents;

    Student** list = sg.getAllStudents();
    int count = sg.getStudentCount();

    for (int i = 0; i < count; i++) {
        Student* s = list[i];

        if (sg.isEnrolledIn(s, "CS101"))
            csStudents.add(s);

        if (sg.isEnrolledIn(s, "Math101"))
            mathStudents.add(s);
    }

    cout << "CS Students: ";
    csStudents.print();

    cout << "Math Students: ";
    mathStudents.print();

    cout << "Union: ";
    SetOperationsStudent u = csStudents.unionWith(mathStudents);
    u.print();

    cout << "Intersection: ";
    SetOperationsStudent inter = csStudents.intersectionWith(mathStudents);
    inter.print();

    cout << "Difference: ";
    SetOperationsStudent diff = csStudents.differenceWith(mathStudents);
    diff.print();

    cout << "\nPower Set of CS Students:"<<endl;
    csStudents.printPowerSet();

    cout << "\nIs CS Students a subset of Math Students? ";
    cout << (csStudents.isSubsetOf(mathStudents) ? "Yes" : "No") << endl;
    // ---------------- STRING SETS ------------------

    SetOperationsString CS_Prof;
    CS_Prof.add("Adeel");
    CS_Prof.add("Khan");
    CS_Prof.add("Ahmed");

    SetOperationsString Math_Prof;
    Math_Prof.add("Adeel");
    Math_Prof.add("Zara");

    SetOperationsString p_in = CS_Prof.intersectionWith(Math_Prof);

    SetOperationsString CSRooms;
    CSRooms.add("LabA");
    CSRooms.add("LabC");

    SetOperationsString MathRooms;
    MathRooms.add("LabB");
    MathRooms.add("LabC");

    SetOperationsString r_in = CSRooms.intersectionWith(MathRooms);

    cout << "Professor Intersection: ";
    p_in.print();
    cout << "Room Intersection: ";
    r_in.print();

    return 0;
}
