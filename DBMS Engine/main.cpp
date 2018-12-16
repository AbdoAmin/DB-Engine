/*
 * C Program to List All Lines containing a given String
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct Value
{
    string name;
    string value;
};

template <class T>
struct Node
{
    T data;
    Node* next;
    Node* prev;

};

class Department
{
    int departmentId;
    string departmentName;
public:
    static string fileName;
    Department()
    {

    }

    Department(int id, string name)
    {
        departmentId =id;
        departmentName=name ;
    }

    void setDepartmentId(int deptId)
    {

        departmentId = deptId;
    }

    int getDepartmentId()
    {
        return departmentId;
    }

    void setDepartmentName(string deptName)
    {
        departmentName = deptName;
    }

    string getDepartmentName()
    {
        return departmentName;
    }




//just generate temp carry updated value
    Department generateUpdated(vector<Value> attribute)
    {
        Department tempDepartment(-1,"");
        for(int i=0; i<attribute.size(); i++)
        {
            if(attribute[i].name=="departmentId")
                tempDepartment.setDepartmentId(atoi(attribute[i].value.c_str()));
            else if(attribute[i].name=="departmentName")
                tempDepartment.setDepartmentName(attribute[i].value);
        }
        return tempDepartment;
    }

    Node<Department>* genarateNode()
    {
        //TODO check if department exist
        Node<Department>* temp=new Node<Department>;
        temp->data=*this;
        return temp;
    }

    bool compare(Department checkedDepartment)
    {
        bool a=true;
        checkedDepartment.departmentId!= -1 ?
        (this->departmentId==checkedDepartment.departmentId ? a &= true : a &= false ) :(a&=true);

        checkedDepartment.departmentName != "" ?
        (this->departmentName==checkedDepartment.departmentName ? a &= true : a &= false ) :(a&=true);
        return a;
    }

    void swap(Department newDepartment)
    {
        departmentId=newDepartment.departmentId != -1 ? newDepartment.departmentId : departmentId;
        departmentName=newDepartment.departmentName !="" ? newDepartment.departmentName : departmentName;
    }


    string toString()
    {
        stringstream sstm;
        sstm << departmentId <<";"<< departmentName<<"\n";
        return sstm.str();
    }



    friend istream &operator >> (istream &is,Department &t);
};

string Department::fileName="department.txt";
template <class L>
class Table;
template <class T>
T generateUpdatedClass(vector<Value> attribute);
bool checkValidationDepartment( Table<Department>* departmentLinkedList,int departmentId);


template <class L>
class Table
{
    Node<L>* head;
    Node<L>* tail;
public:
    Table()
    {
        head=tail=NULL ;
    }

    void saveToFile()
    {
        fstream file;
        file.open (L::fileName.c_str(),ios::out | ios::trunc);
        file.seekp (0);
        Node<L>* temp;
        temp = head;
        while (temp != NULL)
        {
            file<<temp->data.toString();
            temp = temp->next;
        }
        file.close();
    }

    void getFromFile()
    {
        ifstream outfile;
        outfile.open (L::fileName.c_str());
        L data;
        while ( outfile >>data )
        {
            cout<<data.toString();
            append(data.genarateNode());
        }
        outfile.close();
    }


    vector<Node<L>*> search(L requierdNode)
    {
        bool a=true;
        vector<Node<L>*> founedDataList;
        Node<L>* temp = head;
        while(temp !=NULL)
        {
            if (temp->data.compare(requierdNode))
            {
                founedDataList.push_back(temp);
            }
            temp =  temp -> next;
        }
        return founedDataList;
    }

    void deleteMethod(Node<L>* temp)
    {

        if(head == tail)
        {
            head = tail = NULL;
        }
        else if(temp == head)
        {
            head =  temp -> next;
            head ->prev = NULL;
        }
        else if (temp == tail)
        {
            tail = temp ->prev;
            tail ->next = NULL;
        }
        else
        {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
        delete temp;
    }

    void append(Node<L>* temp)
    {
        if(temp!=NULL)
        {
            if(head == NULL)
            {
                head = tail = temp ;
                temp -> prev = NULL;
                temp -> next = NULL;
            }
            else
            {

                temp -> prev = tail;
                temp -> next = NULL;
                tail -> next = temp;
                tail = temp;
            }
        }
    }

    void display ()
    {

        Node<L>* temp =  head;
        while(temp != NULL)
        {
            cout<<temp->data.toString()<<endl;
            temp = temp ->next;
        }
    }

};


class Student
{
    int studentId;
    string studentFirstName;
    string studentLastName;
    int studentAge;
    int departmentId;
public:
    static string fileName;
    static Table<Department>* dependantDepartmentTable;
    Student()
    {
    }
    Student (int id, string firstName, string lastName,int age, int depId)
    {
        studentId = id;
        studentFirstName = firstName;
        studentLastName =lastName ;
        studentAge = age;
        departmentId =  depId;
    }

    void setDepartmentId(int deptId)
    {
        departmentId = deptId;
    }

    int getDepartmentId( )
    {
        return departmentId;
    }

    void setStudentAge(int age)
    {
        studentAge = age;
    }

    int getStudentAge( )
    {
        return studentAge;
    }
    void setStudentFirstName(string firstName)
    {
        studentFirstName = firstName;
    }

    string getStudentFirstName ()
    {
        return studentFirstName;
    }

    void setStudentLastName (string lastName)
    {
        studentLastName = lastName;
    }

    string getStudentLastName()
    {
        return studentLastName;
    }
    void setStudentId(int id)
    {
        studentId = id;
    }

    int getStudentId( )
    {
        return studentId;
    }


//just generate temp carry updated value
    Student generateUpdated(vector<Value> attribute)
    {
        Student tempStudent(-1,"","",-1,-1);
        for(int i=0; i<attribute.size(); i++)
        {
            if(attribute[i].name=="id")
                tempStudent.setStudentId(atoi(attribute[i].value.c_str()));
            else if(attribute[i].name=="firstName")
                tempStudent.setStudentFirstName(attribute[i].value);
            else if(attribute[i].name=="lastName")
                tempStudent.setStudentLastName(attribute[i].value);
            else if(attribute[i].name=="age")
                tempStudent.setStudentAge(atoi(attribute[i].value.c_str()));
            else if(attribute[i].name=="depId")
                tempStudent.setDepartmentId(atoi(attribute[i].value.c_str()));
        }
        return tempStudent;
    }

    Node<Student>* genarateNode()
    {

        //TODO check if department exist
        if(checkValidationDepartment(Student::dependantDepartmentTable,departmentId))
        {
            Node<Student>* temp=new Node<Student>;
            temp->data=*this;
            return temp;
        }
        else
            cout<<"Can't Add This Student , his Department not in list"<<endl;
        return NULL;
    }

    bool compare(Student checkedStudent)
    {
        bool a=true;
        checkedStudent.getStudentId() != -1 ?
        (this->studentId==checkedStudent.getStudentId() ? a &= true : a &= false ) :(a&=true);
        checkedStudent.getStudentAge() != -1 ?
        (this->studentAge==checkedStudent.getStudentAge() ? a &= true : a &= false ) :(a&=true);
        checkedStudent.getDepartmentId() != -1 ?
        (this->departmentId==checkedStudent.getDepartmentId() ? a &= true : a &= false ) :(a&=true);
        checkedStudent.getStudentFirstName() != "" ?
        (this->studentFirstName==checkedStudent.getStudentFirstName() ? a &= true : a &= false ) :(a&=true);
        checkedStudent.getStudentLastName() != "" ?
        (this->studentLastName==checkedStudent.getStudentLastName() ? a &= true : a &= false ) :(a&=true);
        return a;
    }

    void swap(Student newStudent)
    {
        studentId=newStudent.studentId != -1 ? newStudent.studentId :studentId;
        studentAge=newStudent.studentAge != -1 ? newStudent.studentAge : studentAge;
        departmentId=newStudent.departmentId != -1 ? newStudent.departmentId : departmentId;
        studentFirstName=newStudent.studentFirstName !="" ? newStudent.studentFirstName : studentFirstName;
        studentLastName=newStudent.studentLastName !="" ? newStudent.studentLastName:studentLastName;
    }

    string toString()
    {
        stringstream sstm;
        sstm << studentId <<";"<< studentFirstName<<";"<< studentLastName<<";"<< studentAge<<";"<< departmentId<<"\n";
        return sstm.str();
    }

    friend istream &operator >> (istream &is,Student &t);

};
string Student::fileName="student.txt";
Table<Department>* Student::dependantDepartmentTable;


bool checkValidationDepartment( Table<Department>* departmentLinkedList,int departmentId)
{
    stringstream sstm;
    sstm << departmentId;
    Value paramter;
    paramter.name="departmentId";
    paramter.value=sstm.str();
    vector<Value> temp;
    temp.push_back(paramter);
    if(departmentLinkedList->search(generateUpdatedClass<Department>(temp)).size() >0)
        return true;
    else
        return false;

}


template <class L>
bool update(L tableAsLinkedList,vector<Value> conditions,vector<Value> setOfValues);

template <class L,class C>
void insertMembers(L tableAsLinkedList,vector<Value> data);

template <class L,class N,class C>
bool deleteMembers(L tableAsLinkedList,vector<Value> condition);



istream &operator >> (istream &is,Student &t)
{

    string f,l;
    int id,age,depID;

    is >> id;
    is.ignore(1,';');
    getline(is,f,';');
    getline(is,l,';');
    is >> age;
    is.ignore(1,';');
    is >> depID;

    t.setStudentId(id);
    t.setStudentFirstName(f);
    t.setStudentLastName(l);
    t.setStudentAge(age);
    t.setDepartmentId(depID);
    return is;
}

istream &operator >> (istream &is,Department &t)
{

    is >> t.departmentId;
    is.ignore(1,';');
    getline(is,t.departmentName);
    return is;
}



int main()
{
    Table<Department> departmentLinkedList;
    Student::dependantDepartmentTable=&departmentLinkedList;
    departmentLinkedList.append( Department(1,"dept").genarateNode());
    departmentLinkedList.append(Department(2,"dept").genarateNode());
    departmentLinkedList.append(Department(3,"dept").genarateNode());
    departmentLinkedList.append(Department(4,"dept").genarateNode());
//    departmentLinkedList.display();
    cout<<"------------------------------------------"<<endl;
    Table<Student> studentLinkedList;
    studentLinkedList.append(Student(1,"ismail","hamda",15,8).genarateNode());
    studentLinkedList.display();
    studentLinkedList.append(Student(2,"ahmed","hamda",15,3).genarateNode());
    studentLinkedList.display();
//    studentLinkedList.display();
    studentLinkedList.append(Student(3,"hassan","mostafe",20,1).genarateNode());
    studentLinkedList.display();
//    cout<<"------------------------------------------"<<endl;
//    studentLinkedList.deleteById(1);
//    studentLinkedList.display();
//    cout<<"------------------------------------------"<<endl;
//    studentLinkedList.append(3,"hassan","mostafe",20,3,departmentLinkedList);
//    studentLinkedList.display();
//    cout<<"------------------------------------------"<<endl;
//    Student ss(-1,"","hamda",-1,-1);
//    vector<Node<Student>*> list =studentLinkedList.search(ss);
//    cout<<list.size();
//    for(int i=0; i<list.size(); i++)
//        cout<<list[i]->data.toString();

//
//    Table<Student> temp;
//    studentLinkedList.saveToFile();

    return 1;
}

template <class L,class N,class C>
bool update(L tableAsLinkedList,vector<Value> conditions,vector<Value> setOfValues)
{
    C condition=generateUpdatedClass<C>(conditions);
    vector<N*> searched=tableAsLinkedList.search(condition);
    if(searched.size()>0)
    {
        C comperable=generateUpdatedClass<C>(setOfValues);
        for(int i=0; i<searched.size(); i++)
        {
            searched[i]->data.swap(comperable); //ToDo Change Node To be generic
        }

        return true;
    }
    else
        return false;
}


template <class L,class N,class C>
bool deleteMembers(L tableAsLinkedList,vector<Value> conditions)
{
    C condition=generateUpdatedClass<C>(conditions);
    vector<N*> searched=tableAsLinkedList.search(condition);
    if(searched.size() > 0)
    {
        for(int i= 0 ; i< searched.size() ; i++)
        {
            tableAsLinkedList.deleteMethod(searched[i]);
        }
        return true;
    }
    else
        return false;
}
template <class L,class C>
void insertMembers(L tableAsLinkedList,vector<Value> data)
{
    C comperable=generateUpdatedClass<C>(data);
    tableAsLinkedList.append(comperable);
}


template <class T>
T generateUpdatedClass(vector<Value> attribute)
{
    T temp;
    return temp.generateUpdated(attribute);
}



