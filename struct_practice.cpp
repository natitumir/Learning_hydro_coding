//To some extent, struct is a simplified form of class. It just has 
//properties and no methods, as opposed to classes that has both
//properties and methods
#include<iostream>
using namespace std;

struct Student{
    string name;
    int age;
    double gpa;
};

int main(){
    Student student1;
    Student student2;

    cout<<"Give me the name of the first student: ";
    cin>> student1.name;
    cout<<"\nGive me the age of the first student: ";
    cin>> student1.age;
    cout<<"\nGive me the gpa of the first student: ";
    cin>> student1.gpa;
    

    cout<<"Give me the name of the second student: ";
    cin>> student2.name;
    cout<<"\nGive me the age of the second student: ";
    cin>> student2.age;
    cout<<"\nGive me the gpa of the second student: ";
    cin>> student2.gpa;

    cout<<student1.name<<", age "<<student1.age<<", has gpa "<<student1.gpa<<endl;
    cout<<student2.name<<", age "<<student2.age<<", has gpa "<<student2.gpa<<endl;

    return 0;
}



