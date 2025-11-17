#include "course.h"
#include <iostream>
using namespace std;

CourseSchedule::CourseSchedule(int cap) {
    capacity = cap;
    total = 0;
    courses = new string[capacity];
    prereq = new string[capacity];
}

CourseSchedule::~CourseSchedule() {
    delete[] courses;
    delete[] prereq;
}

void CourseSchedule::addCourse(string courseName, string prerequisite) {
    if (total == capacity) {
        capacity *= 2;
        string* newCourses = new string[capacity];
        string* newPrereq = new string[capacity];

        for (int i = 0; i < total; i++) {
            newCourses[i] = courses[i];
            newPrereq[i] = prereq[i];
        }

        delete[] courses;
        delete[] prereq;
        courses = newCourses;
        prereq = newPrereq;
    }

    courses[total] = courseName;
    prereq[total] = prerequisite;
    total++;
}

static void traverseFrom(const string rootCourse, string* courses, string* prereq, int totalCourses, string* done, int doneCount, int capacity) {
    
    if (doneCount < capacity)
        done[doneCount] = rootCourse;
    else
        return; 

    doneCount++;

    bool extended = false;
    for (int i = 0; i < totalCourses; i++) {
        
        if (prereq[i] == rootCourse) {
            extended = true;
            traverseFrom(courses[i], courses, prereq, totalCourses, done, doneCount, capacity);
        }
    }

    if (!extended) {
        for (int k = 0; k < doneCount; k++) {
            cout << done[k] << " ";
        }
        cout << endl;
    }
}

void CourseSchedule::generateOrder() {
   
    for (int i = 0; i < total; i++) {
        if (prereq[i] == "") {
            string* done = new string[capacity];
            traverseFrom(courses[i], courses, prereq, total, done, 0, capacity);
            delete[] done;
        }
    }
}

void CourseSchedule::generateOrderRecursive(string* done, int doneCount) {
    
    if (doneCount > 0) {
        for (int i = 0; i < doneCount; i++)
            cout << done[i] << " ";
        cout << endl;
    }
}

bool CourseSchedule::isPrerequisiteChainSatisfied(string course) {
    int index = -1;
    for (int i = 0; i < total; i++) {
        if (courses[i] == course) {
            index = i;
            break;
        }
    }

    if (index == -1) return true;
    if (prereq[index] == "") return true;

    string pre = prereq[index];

    bool prereqExists = false;
    for (int i = 0; i < total; i++) {
        if (courses[i] == pre) {
            prereqExists = true;
            break;
        }
    }

    if (!prereqExists) {
        cout << "Warning: Prerequisite course \"" << pre << "\" not found."<<endl;
        return false;
    }

    return isPrerequisiteChainSatisfied(pre);
}

bool CourseSchedule::isPrerequisiteSatisfiedForStudent(string course, string* completedCourses, int completedCount) {
    int index = -1;
    for (int i = 0; i < total; i++) {
        if (courses[i] == course) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Course " << course << " not found in the schedule." << endl;
        return false;
    }
    if (prereq[index] == "") return true;
    string pre = prereq[index];
    for (int i = 0; i < completedCount; i++) {
        if (completedCourses[i] == pre) {
            return true;
        }
    }
    return false;
}
