#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class CourseSchedule {
private:
    string* courses;
    string* prereq;
    int total;
    int capacity;

    void generateOrderRecursive(string* done, int doneCount);

public:
    CourseSchedule(int cap = 10);
    ~CourseSchedule();

    void addCourse(string courseName, string prerequisite);
    void generateOrder();
    bool isPrerequisiteChainSatisfied(string course);
    bool isPrerequisiteSatisfiedForStudent(string course, string* completedCourses, int completedCount);
};

#endif
