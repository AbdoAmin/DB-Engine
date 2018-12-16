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

class Student
{
    int studentId;
    string studentFirstName;
    string studentLastName;
    int studentAge;
    int departmentId;
public:
    static string fileName;
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

//    Node<Student>* genarateNode()
//    {
//        //TODO check if department exist
//        Node<Student>* temp=new Node<Student>;
//        temp->data=*this;
//        return temp;
//    }
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
class Department
{
    int departmentId;
    string departmentName;
public:
    static string fileName;
    Department()
    {

    }
    void swap(Department newDepartment)
    {
        departmentId=newDepartment.departmentId != -1 ? newDepartment.departmentId : departmentId;
        departmentName=newDepartment.departmentName !="" ? newDepartment.departmentName : departmentName;
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


};

string Department::fileName="department.txt";

template <class T>
struct Node
{
    T data;
    Node* next;
    Node* prev;

};

struct DepartmentNode
{
    Department department;
    DepartmentNode* next;
    DepartmentNode* prev;
};


class DepartmentLinkedList
{
    DepartmentNode* head;
    DepartmentNode* tail;
public:
    DepartmentLinkedList()
    {
        head=tail=NULL ;
    }



    DepartmentNode* searchById(int id)
    {

        DepartmentNode* temp = head;
        while(temp !=NULL)
        {
            if (id == temp->department.getDepartmentId())
            {
                return temp;
            }
            temp =  temp -> next;
        }
        return NULL;
    }


    DepartmentNode*  searchByName(string departmentName)
    {

        DepartmentNode*  temp = head;
        while(temp !=NULL)
        {
            if (departmentName== temp->department.getDepartmentName())
            {
                return temp;
            }
            temp =  temp -> next;
        }
        return NULL;

    }


    void deleteById(int id)
    {

        DepartmentNode* temp = searchById(id);
        if(temp == NULL)
        {
            return;
        }
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

    void deleteByName(string name)
    {

        DepartmentNode* temp = searchByName(name);
        if(temp == NULL)
        {
            return;
        }
        if(head == tail)
        {
            head = tail  = NULL;
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


    void  append( int departmentId,string departmentName)
    {

        DepartmentNode* temp =  new DepartmentNode;
        temp->department.setDepartmentId(departmentId);
        temp->department.setDepartmentName(departmentName);

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


    void display ()
    {

        DepartmentNode* temp =  head;
        while(temp != NULL)
        {
            cout<< temp ->department.getDepartmentId() << ":"<<
                temp ->department.getDepartmentName()<<endl;
            temp = temp ->next;
        }
    }
};



int checkValidationDepartment( DepartmentLinkedList departmentLinkedList,int departmentId)
{
    if(departmentLinkedList.searchById(departmentId) != NULL)
        return 1;
    else
        return -1;
}

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
        vector<Node<L>*> founedStudentList;
        Node<L>* temp = head;
        while(temp !=NULL)
        {
            if (temp->data.compare(requierdNode))
            {
                founedStudentList.push_back(temp);
            }
            temp =  temp -> next;
        }
        return founedStudentList;
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


    void  append(int studentId,string studentFirstName, string studentLastName,int studentAge,
                 int departmentId,DepartmentLinkedList departmentLinkedList)
    {

        if (checkValidationDepartment(departmentLinkedList,departmentId) == 1)
        {
            Node<L>* temp =  new Node<L>;
            temp ->data.setStudentId(studentId);
            temp ->data.setStudentFirstName(studentFirstName);
            temp ->data.setStudentLastName(studentLastName);
            temp ->data.setStudentAge(studentAge);
            temp ->data.setDepartmentId(departmentId);

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
        else
        {
            cout<<"Id is not available in department table"<<endl;
        }
    }


    void display ()
    {

        Node<L>* temp =  head;
        while(temp != NULL)
        {
            cout<< temp ->data.getStudentId() << ":"<< temp ->data.getStudentFirstName()
                << ":"<<temp->data.getStudentLastName()<<":"<<temp->data.getStudentAge()
                <<":"<< temp->data.getDepartmentId()<<endl;
            temp = temp ->next;
        }
    }

};

template <class L>
bool update(L tableAsLinkedList,vector<Value> conditions,vector<Value> setOfValues);

template <class L,class C>
void insertMembers(L tableAsLinkedList,vector<Value> data);

template <class L,class N,class C>
bool deleteMembers(L tableAsLinkedList,vector<Value> condition);

template <class T>
T generateUpdatedClass(Value attribute[],int size);

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

int main()
{
    DepartmentLinkedList departmentLinkedList;
    departmentLinkedList.append(1,"dept");
    departmentLinkedList.append(2,"dept");
    departmentLinkedList.append(3,"dept");
    departmentLinkedList.append(4,"dept");
//    departmentLinkedList.display();
    cout<<"------------------------------------------"<<endl;
    Table<Student> studentLinkedList;
    studentLinkedList.append(1,"ismail","hamda",15,2,departmentLinkedList);
    studentLinkedList.append(2,"ahmed","hamda",15,3,departmentLinkedList);
//    studentLinkedList.display();
    studentLinkedList.append(3,"hassan","mostafe",20,5,departmentLinkedList);
//    cout<<"------------------------------------------"<<endl;
//    studentLinkedList.deleteById(1);
//    studentLinkedList.display();
//    cout<<"------------------------------------------"<<endl;
//    studentLinkedList.append(3,"hassan","mostafe",20,3,departmentLinkedList);
//    studentLinkedList.display();
//    cout<<"------------------------------------------"<<endl;
    Student ss(-1,"","hamda",-1,-1);
    vector<Node<Student>*> list =studentLinkedList.search(ss);
    cout<<list.size();
    for(int i=0; i<list.size(); i++)
        cout<<list[i]->data.toString();

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
//
//void solveSetClause(string condition)
//{
//    char * pch;
//    pch = strtok (condition.c_str(),',');
//    while (pch != NULL)
//    {
//        printf ("%s\n",pch);
//        pch = strtok (NULL, " ,.-".c_str());
//    }
//}


