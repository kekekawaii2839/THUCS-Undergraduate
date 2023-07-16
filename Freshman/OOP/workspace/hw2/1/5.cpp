#include <iostream>

class Student{
    friend class School;
private: // (B)
    ~Student(){std::cout<<"Student fired.";}
public:
    class School* school;
    void interfereSchool();
};

class School{
private:
    void access(){std::cout<<"School accessed.";}
public:
    Student* student;
    void fireStudent();
};

void Student::interfereSchool(){
    //school -> access(); // (A)
}
void School::fireStudent(){
    delete student;
}

int main(){
    School* school = new School();
    Student* student = new Student();
    school -> student = student;
    student -> school = school;

    student -> interfereSchool();
    school->fireStudent();  // (C)
}
