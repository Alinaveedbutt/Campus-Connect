#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Person {
protected:
    string name;
    int personID;
public:
    Person(string name = "", int personID = 0) {
        this-> name = name;
        this-> personID = personID;
    }
    virtual void display() {
        cout<<"Name: "<<name<<endl;
        cout<<"Person ID: "<<personID<<endl;
    }
    virtual void writeToFile(ofstream &out) {
        out<<"Name: "<<name<<endl;
        out<<"Person ID: "<<personID<<endl;
    }
    virtual ~Person() {}
};
class Student : public Person {
protected:
    string programEnrolled;
    int semester;
public:
    Student(string name = "", int personID = 0, string programEnrolled = "", int semester = 0): Person(name, personID) {
        this-> programEnrolled = programEnrolled;
        this-> semester = semester;
    }
    void display() override {
        Person::display();
        cout<<"Program Enrolled: "<<programEnrolled<<endl;
        cout<<"Semester: "<<semester<<endl;
    }
    void writeToFile(ofstream &out) override {
        Person::writeToFile(out);
        out<<"Program Enrolled: "<<programEnrolled<<endl;
        out<<"Semester: "<<semester<<endl;
    }
};
class Faculty : public Person {
protected:
    string department;
    int coursesTeaching;
public:
    Faculty(string name = "", int personID = 0, string department = "", int coursesTeaching = 0) : Person(name, personID) {
        this-> department = department;
        this-> coursesTeaching = coursesTeaching;
    }
    void display() override {
        Person::display();
        cout<<"Department: "<<department<<endl;
        cout<<"Courses Teaching: "<<coursesTeaching<<endl;
    }
    void writeToFile(ofstream &out) override {
        Person::writeToFile(out);
        out<<"Department: "<<department<<endl;
        out<<"Courses Teaching: "<<coursesTeaching<<endl;
    }
};
class Visitor : public Person {
protected:
    string visitPurpose;
    int visitDuration;
public:
    Visitor(string name = "", int personID = 0, string visitPurpose = "", int visitDuration = 0) : Person(name, personID) {
        this-> visitPurpose = visitPurpose;
        this-> visitDuration = visitDuration;
    }
    void display() override {
        Person::display();
        cout<<"Visit Purpose: "<<visitPurpose<<endl;
        cout<<"Visit Duration: "<<visitDuration<<" day(s)"<<endl;
    }
    void writeToFile(ofstream &out) override {
        Person::writeToFile(out);
        out<<"Visit Purpose: "<<visitPurpose<<endl;
        out<<"Visit Duration: "<<visitDuration<<" day(s)"<<endl;
    }
};
int main() {
    Person* people[100];
    int count = 0;
    int choice;
    do {
        cout<<endl;
        cout<<"=== MENU ==="<<endl;
        cout<<"1. Add Student"<<endl;
        cout<<"2. Add Faculty"<<endl;
        cout<<"3. Add Visitor"<<endl;
        cout<<"4. Display All"<<endl;
        cout<<"5. Save All to File"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if (choice == 1) {
            string name, program;
            int id, semester;
            cout<<"Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout<<"Enter ID: ";
            cin>>id;
            cout<<"Enter program enrolled: ";
            cin.ignore();
            getline(cin, program);
            cout<<"Enter semester: ";
            cin>>semester;
            people[count++] = new Student(name, id, program, semester);
        }
        else if (choice == 2) {
            string name, dept;
            int id, courses;
            cout<<"Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout<<"Enter ID: ";
            cin>>id;
            cout<<"Enter department: ";
            cin.ignore();
            getline(cin, dept);
            cout<<"Enter number of courses teaching: ";
            cin>>courses;
            people[count++] = new Faculty(name, id, dept, courses);
        }
        else if (choice == 3) {
            string name, purpose;
            int id, duration;
            cout<<"Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout<<"Enter ID: ";
            cin>>id;
            cout<<"Enter visit purpose: ";
            cin.ignore();
            getline(cin, purpose);
            cout<<"Enter visit duration (in days): ";
            cin>>duration;
            people[count++] = new Visitor(name, id, purpose, duration);
        }
        else if (choice == 4) {
            for (int i = 0; i < count; i++) {
                cout<<endl;
                cout<<"---Person "<<(i + 1)<<"---"<<endl;
                people[i]->display();
            }
        }
        else if (choice == 5) {
            ofstream out("File.txt");
            if (!out) {
                cout<<"Error opening file!"<<endl;
            }
            else {
                for (int i = 0; i < count; i++) {
                    out<<"=== Person"<< (i + 1) <<" ==="<<endl;
                    people[i]->writeToFile(out);
                    out<<endl;
                }
                out.close();
                cout<<"Data saved to File.txt"<<endl;
            }
        }
        else if (choice != 6) {
            cout<<"Invalid choice. Try again."<<endl;
        }
    }
    while (choice != 6);
    for (int i = 0; i < count; i++) {
        delete people[i];
    }
    return 0;
}
