/*
 * C Program to List All Lines containing a given String
 */
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

void selectOperation(string queryStatment) ;
void deleteOperation(string queryStatment);
void updateOpertaion(string queryStatment);
void insertOpertaion(string insetQuery);
bool isFileCreated(string fileName);
bool isValidColumns(vector<string> column,string fileName);
vector<string> splitColumn (string columns);
string removeSpaces(string spaceToRemove);
void analyseQuery(string query) ;


const string INVALID_QUERY="query out of scope \n " ;

struct Condition
{
    string name;
    string value;
    Condition(string _name,string _value)
    {
        name=_name;
        value=_value;
    }
    Condition() {}
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
    void displayNode(vector<string> column,vector<Node<Department>* > nodes)
    {
        for(int i=0; i<column.size(); i++)
        {
            cout<<"\t"<<column[i]<<"\t";
        }
        for(int i=0; i<nodes.size(); i++)
        {
            for(int j=0; j<column.size(); j++)
            {
                if(column[j]=="departmentId")
                    cout<<"\t"<<nodes[i]->data.departmentId<<"\t";
                else if(column[j]=="departmentName")
                    cout<<"\t"<<nodes[i]->data.departmentName<<"\t"<<endl;
            }

        }


    }

//just generate temp carry updated value
    Department generateUpdated(vector<Condition> attribute)
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
class Student;

template <class L>
class Table
{
    Node<L>* head;
    Node<L>* tail;
    int count;
    int length;
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

    int getIndexOf(Node<L>* node)
    {
        int counter = 0;
        Node<L>* temp= head;
        while(temp !=NULL)
        {
            if ( node == temp)
            {
                return counter;
            }
            temp =  temp -> next;
            counter++;
        }

        return -1;

    }
    /* ******* */
    void insertIntoPosition(Node<L>* node,int index)
    {
        /*    Node<L>* temp= head;
            for (int i = 1 ; i < index ; i++){
                 temp =  temp -> next;
            }
            */

        if (index < -1 || index > length)
        {
            cout << "Your List max index is : " << length - 1 << " and you can not do this step\n";
        }
        else if ((head == NULL && length == 0)||index==0)
            insertFirst(node);
        else if (index == length)
            append(node);
        else if (index <= length / 2)
        {
            Node<L>* temp = head;
            for (int i = 1 ; i < index ; i++)
            {
                temp =  temp -> next;
            }
            node->next = temp->next;
            node->prev = temp;
            temp->next = node;
            length++;
        }
        else
        {
            int count  = length - 1;
            Node<L>* temp = tail;
            while (index + 1 < count)
            {
                temp = temp->prev;
                count--;
            }
            node ->prev = temp->prev;
            node ->next = temp;
            temp ->prev = node;
            length++;
        }

    }

    void deleteFromPosition(int index)
    {
        if (index <= -1 || index >= length)
        {
            cout << "Your List max index is : " << length - 1 << " and you can not do this step\n";
        }
        else if (index == 0)
        {
            Node<L>* temp = head;
            /* Node *a;
             a = head;*/

            head = temp->next;
            if (length == 1)
                tail = NULL;
            else
                temp->next->prev = NULL;
            delete temp;
            length--;
        }
        else if (index == length - 1)
        {
            Node<L>* temp = tail;
            /* Node *a;
             a = tail;
             */

            tail = temp->prev;
            temp->prev->next = NULL;
            delete temp;
            length--;
        }
        else if (index<length / 2)
        {
            Node<L>* b;
            Node<L>* temp = head;
            /*    Node *a, *b;
                a = head;
            */
            for(int i=0; i<index; i++)
            {
                temp = temp->next;
            }
            b = temp;
            temp = temp->next;
            b->next = temp->next;
            temp->next->prev = b;
            delete temp;
            length--;
        }
        else
        {
            count = length - 1;
            Node<L>* b;
            Node<L>* temp = tail;
            /* Node *a, *b;
             temp = tail;
              */
            while (index + 1 < count)
            {
                temp = temp->prev;
                count--;
            }
            b = temp;
            temp = temp->prev;
            b->prev = temp->prev;
            temp->prev->next = b;
            delete temp;
            length--;
        }
    }


    void insertFirst(Node<L>* temp)
    {
        temp->next = head;
        temp->prev = NULL;
        if(head!=NULL)
            head->prev = temp;
        head = temp;
        if (tail == NULL)
            tail = temp;
        length++;
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

    bool append(Node<L>* temp)
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
            return true;
        }
        else
            return false;
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

template <class T >
class StackNode
{
public:
    string operation;
    vector<int> index;
    Table<T> *table;
    vector<Node<T> *> node;
};

template <class L>
class UndoStack
{
public:
    stack<StackNode<L> > S1;
    void undo()
    {
        StackNode<L> stackNode =  S1.top();
        S1.pop();
        if(stackNode.operation == "update")
        {
            undoUpdate(stackNode);
        }
        else if(stackNode.operation == "insert")
        {
            undoInsert(stackNode); // make delete inside table
        }

        else if (stackNode.operation == "delete")
        {
            undoDelete(stackNode); // make insert inside table
        }
    }

    void undoUpdate(StackNode<L> stackNode) // make update inside table with previous values
    {
        for(int i = 0 ; i < stackNode.index.size(); i++)
        {
            stackNode.table ->deleteFromPosition(stackNode.index[i]);
            stackNode.table ->insertIntoPosition(stackNode.node[i],stackNode.index[i]);
        }
        /*
                vector<int> updatedNodeIndex = stackNode.table ->getIndexOf(stackNode);
                for(int i =0 ; i < updatedNodeIndex.size();i++){
                    stackNode.table->append()
                }
                */
    }

    void undoInsert(StackNode<L> stackNode) // make delete inside table
    {
        for(int i = 0 ; i < stackNode.index.size(); i++)
        {
            stackNode.table ->deleteFromPosition(stackNode.index[i]);
        }
        /*
        vector<int> updatedNodeIndex = stackNode.table ->getIndexOf(stackNode);
        for(int i =0 ; i < updatedNodeIndex.size();i++){
            stackNode.table->deleteFromPosition(updatedNodeIndex[i]);
        }

        */

    }

    void undoDelete(StackNode<L> stackNode) // make insert inside table
    {

        for(int i = 0 ; i < stackNode.index.size(); i++)
        {
            stackNode.table ->insertIntoPosition(stackNode.node[i],stackNode.index[i]);
        }

        /*    vector<int> updatedNodeIndex = stackNode.table ->getIndexOf(stackNode);
         for(int i =0 ; i < updatedNodeIndex.size();i++){
             stackNode.table->insertIntoPosition(stackNode.node,updatedNodeIndex);
         }
         */
    }


    void doUpdate( vector<int> index,Table<L> *table,vector<Node<L>* > node)
    {
        StackNode<L> stackNode;
        stackNode.operation = "update";
        stackNode.node = node;
        stackNode.table = table;
        stackNode.index = index;
        S1.push(stackNode);

    }

    void doDelete(vector<int> index,Table<L>* table,vector<Node<L>* > node)
    {
        StackNode<L> stackNode;
        stackNode.operation = "delete";
        stackNode.node=node;
        stackNode.table = table;
        stackNode.index = index;
        S1.push(stackNode);
    }

    void doInsert(vector<int> index,Table<L>* table,vector<Node<L>* > node)
    {
        StackNode<L> stackNode;
        stackNode.operation = "insert";
        stackNode.node = node;
        stackNode.table = table;
        stackNode.index = index;
        S1.push(stackNode);
    }

};


UndoStack<Student> undoStudentStack;
UndoStack<Department> undoDepartmentStack;

class Utilities
{
public:
    static vector<string> undoTypeName;

    static bool checkValidationDepartment( Table<Department>* departmentLinkedList,int departmentId)
    {
        stringstream sstm;
        sstm << departmentId;
        vector<Condition> temp;
        temp.push_back(Condition("departmentId",sstm.str()));
        if(departmentLinkedList->search(generateUpdatedClass<Department>(temp)).size() >0)
            return true;
        else
            return false;

    }


    template <class T>
    static T generateUpdatedClass(vector<Condition> attribute)
    {
        T temp;
        return temp.generateUpdated(attribute);
    }

    static bool undo(string table)
    {
        if(table=="student")
            undoStudentStack.undo();
        else if(table=="department")
            undoDepartmentStack.undo();
        return true;
    }



    static vector<Condition> convetStringToData(vector<string> data,string fileName)
    {
        vector<Condition> temp;
        if(fileName=="student")
        {
            temp.push_back(Condition("studentId",data[0]));
            temp.push_back(Condition("studentFirstName",data[1]));
            temp.push_back(Condition("studentLastName",data[2]));
            temp.push_back(Condition("studentAge",data[3]));
            temp.push_back(Condition("departmentId",data[4]));
        }
        else if(fileName=="department")
        {
            temp.push_back(Condition("departmentId",data[0]));
            temp.push_back(Condition("departmentName",data[1]));
        }
        return temp;
    }

};
vector<string> Utilities::undoTypeName;
Table<Department> departmentTable;


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


    void displayNode(vector<string> column,vector<Node<Student>* > nodes)
    {
        for(int i=0; i<column.size(); i++)
        {
            cout<<"\t"<<column[i]<<"\t";
        }
        cout<<endl;
        for(int i=0; i<nodes.size(); i++)
        {
            for(int j=0; j<column.size(); j++)
            {
                if(column[j]=="studentId")
                    cout<<"\t"<<nodes[i]->data.studentId<<"\t";
                else if(column[j]=="studentFirstName")
                    cout<<"\t"<<nodes[i]->data.studentFirstName<<"\t";
                else if(column[j]=="studentLastName")
                    cout<<"\t"<<nodes[i]->data.studentLastName<<"\t";
                else if(column[j]=="studentAge")
                    cout<<"\t"<<nodes[i]->data.studentAge<<"\t";
                else if(column[j]=="departmentId")
                    cout<<"\t"<<nodes[i]->data.departmentId<<"\t"<<endl;
            }
            cout<<endl;
        }

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


//just generate temp carry updated Condition
    Student generateUpdated(vector<Condition> attribute)
    {
        Student tempStudent(-1,"","",-1,-1);
        for(int i=0; i<attribute.size(); i++)
        {
            if(attribute[i].name=="studentId")
                tempStudent.setStudentId(atoi(attribute[i].value.c_str()));
            else if(attribute[i].name=="studentFirstName")
                tempStudent.setStudentFirstName(attribute[i].value);
            else if(attribute[i].name=="studentLastName")
                tempStudent.setStudentLastName(attribute[i].value);
            else if(attribute[i].name=="studentAge")
                tempStudent.setStudentAge(atoi(attribute[i].value.c_str()));
            else if(attribute[i].name=="departmentId")
                tempStudent.setDepartmentId(atoi(attribute[i].value.c_str()));
        }
        return tempStudent;
    }

    Node<Student>* genarateNode()
    {

        //TODO check if department exist
        if(Utilities::checkValidationDepartment(&departmentTable,departmentId))
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



class OurSQL
{
public:

    template <class L,class N,class C>
    static vector<N*> updateQuery(L  tableAsLinkedList,vector<Condition> conditions,vector<Condition> setOfValues)
    {
        C condition=Utilities::generateUpdatedClass<C>(conditions);
        vector<N*> searched=tableAsLinkedList.search(condition);
        vector<N*> beforeResult;
        if(searched.size()>0)
        {
            C comperable=Utilities::generateUpdatedClass<C>(setOfValues);
            for(int i=0; i<searched.size(); i++)
            {
                beforeResult.push_back(searched[i]->data.genarateNode());
                searched[i]->data.swap(comperable); //ToDo Change Node To be generic
            }
        }
        return beforeResult;
    }


    template <class L,class N,class C>
    static vector<N*> deleteQuery(L& tableAsLinkedList,vector<Condition> conditions)
    {
        C condition=Utilities::generateUpdatedClass<C>(conditions);
        vector<N*> searched=tableAsLinkedList.search(condition);
        vector<N*> beforeResult;
        if(searched.size() > 0)
        {
            for(int i= 0 ; i< searched.size() ; i++)
            {
                beforeResult.push_back(searched[i]->data.genarateNode());
                tableAsLinkedList.deleteMethod(searched[i]);
            }
        }
        return beforeResult;
    }
    template <class L,class N,class C>
    static vector<N*>  insertQuery(L & tableAsLinkedList,vector<Condition> data)
    {
        vector<Condition> id;
        id.push_back(data[0]);
        vector<N*> beforeResult;
        C uniqueID=Utilities::generateUpdatedClass<C>(id);
        vector<N*> searched=tableAsLinkedList.search(uniqueID);
        if(searched.size()==0)
        {
            C comperable=Utilities::generateUpdatedClass<C>(data);
            beforeResult.push_back(searched[0]->data.genarateNode());
            tableAsLinkedList.append(comperable.genarateNode());

        }

        return beforeResult;
    }

    template <class L,class N,class C>
    static bool selectQuery(L  tableAsLinkedList,vector<Condition> conditions,vector<string> columns)
    {
        C condition=Utilities::generateUpdatedClass<C>(conditions);
        vector<N*> searched=tableAsLinkedList.search(condition);
        if(searched.size()>0)
        {
            condition.displayNode(columns,searched);
            return true;
        }
        else
            return false;
    }
};
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

Table<Student> studentTable;


bool isValidColumns(vector<Condition> column,string fileName);

string removeSpaces(string spaceToRemove)
{
    int found= -1;
    do
    {
        found = spaceToRemove.find(" ");
        if (found!=-1)
        {
            spaceToRemove=spaceToRemove.substr(0,found) + spaceToRemove.substr(found+1,spaceToRemove.length());
        }
    }
    while(found!=-1);

    return spaceToRemove;
}
vector<string> splitColumn(string columns)
{
    int pos=0;
    vector<string> column;
    do
    {
        column.push_back(columns.substr(0,columns.find(",")));
        pos = columns.find(",")+1;
        columns= columns.substr(pos,columns.length());
    }
    while(pos != 0);
    return column;
}
vector<Condition> splitCondition(string  conditionsStatment)
{
    vector<Condition> conditionVector ;
    Condition condition;
    int pos=0 ;
    do
    {
        condition.name=conditionsStatment.substr(0,conditionsStatment.find("="));
        pos = conditionsStatment.find("=")+1;
        conditionsStatment= conditionsStatment.substr(pos,conditionsStatment.length());
        if(conditionsStatment.find("and")!=-1)
        {
            condition.value=conditionsStatment.substr(0,conditionsStatment.find("and"));
            pos = conditionsStatment.find("and")+3;
            conditionsStatment= conditionsStatment.substr(pos,conditionsStatment.length());
        }
        else
        {
            condition.value=conditionsStatment;
            conditionsStatment="";
        }
        conditionVector.push_back(condition);
    }
    while (conditionsStatment!="");

    return conditionVector ;
}
vector<Condition> splitColumnToUpdate(string  conditionsStatment)
{
    //cout<<conditionsStatment<<"conditionsStatment";
    vector<Condition> conditionVector ;
    Condition condition;
    int pos=0 ;
    do
    {
        condition.name=conditionsStatment.substr(0,conditionsStatment.find("="));
        pos = conditionsStatment.find("=")+1;
        conditionsStatment= conditionsStatment.substr(pos,conditionsStatment.length());
        if(conditionsStatment.find(",")!=-1)
        {
            condition.value=conditionsStatment.substr(0,conditionsStatment.find(","));
            pos = conditionsStatment.find(",")+1;
            conditionsStatment= conditionsStatment.substr(pos,conditionsStatment.length());
        }
        else
        {
            condition.value=conditionsStatment;
            conditionsStatment="";
        }
        conditionVector.push_back(condition);
    }
    while (conditionsStatment!="");

    return conditionVector ;
}
void selectOperation(string queryStatment)
{
    string columnStatment,conditionStatment,fileName;
    vector<string> columns ;
    vector<Condition> condition ;
    columnStatment = queryStatment.substr(0, queryStatment.find("from"));
    queryStatment = queryStatment.substr(queryStatment.find("from")+4,queryStatment.length()) ;
    if(queryStatment.find("where")!=-1)
    {
        fileName = removeSpaces(queryStatment.substr(0,queryStatment.find("where"))) ;
        fileName=removeSpaces(fileName);
        queryStatment = queryStatment.substr(queryStatment.find("where")+5,queryStatment.length()) ;
        conditionStatment = queryStatment.substr(0,queryStatment.length());
        columns=splitColumn(removeSpaces(columnStatment));

        condition=splitCondition(removeSpaces(conditionStatment));

    }
    else
    {

        fileName = removeSpaces(queryStatment) ;
        columns=splitColumn(removeSpaces(columnStatment));
        // condition=splitCondition(removeSpaces(conditionStatment)) ;
    }

    if(isFileCreated(fileName))
    {
        if(isValidColumns(columns,fileName)&&isValidColumns(condition,fileName))
        {
            if(fileName=="student")
            {


                if (columns[0]=="*")
                {
                    columns.push_back("studentId");
                    columns.push_back("studentFirstName");
                    columns.push_back("studentLastName");
                    columns.push_back("studentAge");
                    columns.push_back("departmentId");
                }

                OurSQL::selectQuery<Table<Student>,Node<Student>,Student>(studentTable,condition,columns);
            }
            else if (fileName=="department")
            {
                if (columns[0]=="*")
                {
                    columns.push_back("departmentId");
                    columns.push_back("departmentName");

                }
                OurSQL::selectQuery<Table<Department>,Node<Department>,Department>(departmentTable,condition,columns);
            }
        }
        else
        {
            cout<<INVALID_QUERY<<endl;
        }
    }
    else
    {
        cout<<INVALID_QUERY<<endl;

    }



}
void deleteOperation(string queryStatment)
{
    string conditionStatment,fileName;
    if(queryStatment.find("from")!=-1 && queryStatment.find("where")!=-1)
    {
        fileName = removeSpaces(queryStatment.substr(queryStatment.find("from")+4,queryStatment.find("where")-5));
        queryStatment = removeSpaces(queryStatment.substr(queryStatment.find("from")+4,queryStatment.length())) ;
        conditionStatment = queryStatment.substr(queryStatment.find("where")+5,queryStatment.length());
        if(isFileCreated(removeSpaces(fileName)))
        {
            vector<Condition> conditons=splitCondition(removeSpaces(conditionStatment));
            if(isValidColumns(conditons,fileName))
                if(fileName == "student")
                {
                    vector<Node<Student>*> beforeUpdate=OurSQL::deleteQuery<Table<Student>,Node<Student>,Student>(studentTable,conditons);
                    vector<int> index;
                    for(int i=0; i<beforeUpdate.size(); i++)
                    {
                        index.push_back(studentTable.getIndexOf(beforeUpdate[i]));
                    }
                    undoStudentStack.doDelete(index,&studentTable,beforeUpdate);
                    Utilities::undoTypeName.push_back("student");
                }
                else if(fileName == "department")
                {
                    vector<Node<Department>*> beforeUpdate=OurSQL::deleteQuery<Table<Department>,Node<Department>,Department>(departmentTable,conditons);
                    vector<int> index;
                    for(int i=0; i<beforeUpdate.size(); i++)
                    {
                        index.push_back(departmentTable.getIndexOf(beforeUpdate[i]));
                    }
                    undoDepartmentStack.doDelete(index,&departmentTable,beforeUpdate);
                    Utilities::undoTypeName.push_back("department");
                }
                else
                {
                    cout<<INVALID_QUERY;
                }

        }
        else
        {
            cout<<INVALID_QUERY;
        }
    }
    else
    {
        cout<<INVALID_QUERY;
    }
}
void updateOpertaion(string queryStatment)
{
    string fileName, columnsToUpdate,conditions;
    fileName = removeSpaces(queryStatment.substr(0, queryStatment.find("set")));
    if(isFileCreated(removeSpaces(fileName))&& queryStatment.find("set")!=-1)
    {
        queryStatment=queryStatment.substr(queryStatment.find("set")+3,queryStatment.length());
        if(queryStatment.find("where")!=-1)
        {
            columnsToUpdate = queryStatment.substr(0,queryStatment.find("where")) ;
            queryStatment=queryStatment.substr(queryStatment.find("where")+5,queryStatment.length());
            conditions = queryStatment.substr(0,queryStatment.length()) ;
            vector<Condition> columnsAndValuesToUpdate= splitColumnToUpdate(removeSpaces(columnsToUpdate));
            vector<Condition> condition=splitCondition(removeSpaces(conditions));
            if (isValidColumns(columnsAndValuesToUpdate,fileName))
            {
                vector<int> index;
                cout<<endl<< "check if column is valid "<<endl;
                if(fileName == "student")
                {
                    vector<Node<Student>*> beforeUpdate=OurSQL::updateQuery<Table<Student>,Node<Student>,Student>(studentTable,condition,columnsAndValuesToUpdate);

                    for(int i=0; i<beforeUpdate.size(); i++)
                    {
                        index.push_back(studentTable.getIndexOf(beforeUpdate[i]));
                    }
                    undoStudentStack.doUpdate(index,&studentTable,beforeUpdate);
                    Utilities::undoTypeName.push_back("student");

                }
                else if (fileName=="department")
                {
                    vector<Node<Department>*> beforeUpdate=OurSQL::updateQuery<Table<Department>,Node<Department>,Department>(departmentTable,condition,columnsAndValuesToUpdate);

                    for(int i=0; i<beforeUpdate.size(); i++)
                    {
                        index.push_back(departmentTable.getIndexOf(beforeUpdate[i]));
                    }
                    undoDepartmentStack.doDelete(index,&departmentTable,beforeUpdate);
                    Utilities::undoTypeName.push_back("department");


                }
            }
            else
            {
                cout<<INVALID_QUERY;

            }

        }
        else
        {
            columnsToUpdate = queryStatment ;
            vector<Condition> columnsAndValuesToUpdate= splitCondition(columnsToUpdate);

            for(int i=0; i<columnsAndValuesToUpdate.size(); i++)
            {
                cout<<columnsAndValuesToUpdate[i].name<<endl;
                cout<<columnsAndValuesToUpdate[i].value<<endl;
            }
        }
    }
    else
    {
        cout<<INVALID_QUERY;


    }
}
bool isFileCreated(string fileName)
{
    if(fileName=="student" || fileName=="department")
        return true;
}
void insertOperation(string insertQuery)
{

    string fileName, attribute;
    insertQuery=removeSpaces(insertQuery);
    if(insertQuery.find("into")!=-1 && insertQuery.find("values")!=-1&&insertQuery.find("(")!=-1)
    {
        fileName = insertQuery.substr(insertQuery.find("into")+4, insertQuery.find("values")-4);
        insertQuery=removeSpaces(insertQuery);
        if(isFileCreated(fileName))
        {
            attribute=insertQuery.substr(insertQuery.find("(")+1, insertQuery.find(")"));
            attribute=attribute.substr(0, attribute.find(")"));


            cout<<"attribute"<<attribute <<endl ;
            vector<string> valuesToInsert=splitColumn(attribute);
            vector<Condition> data =Utilities::convetStringToData(valuesToInsert,fileName);
            vector<int> index;
            if(fileName=="student" && valuesToInsert.size()==5)
            {

                vector<Node<Student>*> beforeUpdate=OurSQL::insertQuery<Table<Student>,Node<Student>,Student>(studentTable,data);

                for(int i=0; i<beforeUpdate.size(); i++)
                {
                    index.push_back(studentTable.getIndexOf(beforeUpdate[i]));
                }
                undoStudentStack.doDelete(index,&studentTable,beforeUpdate);
                Utilities::undoTypeName.push_back("student");


            }
            else if (fileName=="department" && valuesToInsert.size()==2)
            {
                vector<Node<Department>*> beforeUpdate=OurSQL::insertQuery<Table<Department>,Node<Department>,Department>(departmentTable,data);

                for(int i=0; i<beforeUpdate.size(); i++)
                {
                    index.push_back(departmentTable.getIndexOf(beforeUpdate[i]));
                }
                undoDepartmentStack.doInsert(index,&departmentTable,beforeUpdate);
                Utilities::undoTypeName.push_back("department");

            }
            else
                cout <<"you should enter valid table name and values"<<endl;
        }
    }
    else
    {
        cout<<" invalid query "<<endl;
    }
}
//template<class T>
bool isValidColumns(vector<string> column,string fileName)
{
    vector<string> studentColumns ;
    vector<string> departmentColumns ;
    studentColumns.push_back("*");
    studentColumns.push_back("studentId");
    studentColumns.push_back("studentFirstName");
    studentColumns.push_back("studentLastName");
    studentColumns.push_back("studentAge");
    studentColumns.push_back("departmentId");

    departmentColumns.push_back("departmentId");
    departmentColumns.push_back("departmentName");
    departmentColumns.push_back("*");
    if (fileName == "student")
    {
        cout <<"colimn [0]"<<column[0]<<"&" ;
        if (studentColumns[0]=="*")
            return  true;

        for(int i=0; i<column.size(); i++)
        {

            if(column[i] == studentColumns[0]||column[i] == studentColumns[1]
                    || column[i] == studentColumns[2]||column[i] == studentColumns[3]||column[i]== studentColumns[4]||column[i] == studentColumns[5])
            {
            }
            else
            {
                return false;
            }

        }
        return true ;
    }
    else if (fileName=="department")
    {
        cout <<"colimn [0] "<<column[0]<<"&";
        if (departmentColumns[0]=="*"&&departmentColumns.size()==0)
            return  true;
        for(int i=0; i<column.size(); i++)
        {
            if(column[i]== departmentColumns[0] || column[i]==departmentColumns[1]||column[i] == studentColumns[2])
            {


            }
            else
            {

                return false;
            }

        }
        return true ;
    }

}
bool isValidColumns(vector<Condition> column,string fileName)
{
    vector<string> studentColumns ;
    vector<string> departmentColumns ;
    studentColumns.push_back("studentId");
    studentColumns.push_back("studentFirstName");
    studentColumns.push_back("studentLastName");
    studentColumns.push_back("studentAge");
    studentColumns.push_back("departmentId");
    departmentColumns.push_back("departmentId");
    departmentColumns.push_back("departmentName");
    if (fileName=="student")

    {
        for(int i=0; i<column.size(); i++)
        {
            cout <<"$"<<column[i].name<<"$";
            if(column[i].name == studentColumns[0]||column[i].name == studentColumns[1] || column[i].name == studentColumns[2]
                    ||column[i].name == studentColumns[3]||column[i].name == studentColumns[4])
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return true ;
    }
    else if (fileName=="department")
    {
        for(int i=0; i<column.size(); i++)
        {

            if(column[i].name== departmentColumns[0] || column[i].name==departmentColumns[1])
            {
                return true;
            }
            else
            {
                return false;

            }
        }
        return true ;
    }
}
void help()
{
    cout<<endl;
    cout<<"\t\t\t\t\tSQL Commands:"<<endl;
    cout<<"  _______________________________"<<endl;
    cout<<" |you can select using : SELECT column_name FROM table_name;                                   |"<<endl;
    cout<<" |For example : SELECT fname FROM student;                                                     |"<<endl;
    cout<<" |_______________________________|"<<endl;
    cout<<" |you can select using : SELECT column_names FROM table_name;                                  |"<<endl;
    cout<<" |For example : SELECT fname,lname FROM student;                                               |"<<endl;
    cout<<" |_______________________________|"<<endl;
    cout<<" |you can select using : SELECT All_columns FROM table_name;                                   |"<<endl;
    cout<<" |For example : SELECT * FROM student;                                                         |"<<endl;
    cout<<" |_______________________________|"<<endl;
    cout<<" |you can insert data  using : INSERT INTO table_name VALUES (value1, value2, value3, ...);    |"<<endl;
    cout<<" |For example : insert into student values (1,Asmaa,Fathy,25,1);                               |"<<endl;
    cout<<" |_______________________________|"<<endl;
    cout<<" |you can delete from table using : DELETE FROM table_name WHERE some_column = some_value;     |"<<endl;
    cout<<" |For example : delete from student where departmentId = 1;                                    |"<<endl;
    cout<<" |_______________________________|"<<endl;
    cout<<" |you can modify data  using : DELETE FROM table_name WHERE some_column = some_value;          |"<<endl;
    cout<<" |For example : update student set student fname = Asmaa where studentId = 3;                  |"<<endl;
    cout<<" |_______________________________|"<<endl;
}
int main()
{
//    departmentTable.append( Department(1,"dept").genarateNode());
//    departmentTable.append(Department(2,"dept").genarateNode());
//    departmentTable.append(Department(3,"dept").genarateNode());
//    departmentTable.append(Department(4,"dept").genarateNode());
//
////    departmentLinkedList.display();
//    cout<<"------------------------------------------"<<endl;
//    studentTable.append(Student(1,"ismail","hamda",15,8).genarateNode());
//    studentTable.append(Student(2,"ahmed","hamda",15,3).genarateNode());
////    studentLinkedList.display();
//    studentTable.append(Student(3,"hassan","mostafe",20,1).genarateNode());
//    studentTable.append(Student(9,"mostafe","mostafe",50,1).genarateNode());
//    studentTable.append(Student(7,"hamda","ismail",38,1).genarateNode());
//
//    vector<Node<Student>* > temp=studentTable.search(Student(-1,"","",-1,-1));
//    for(int i=0; i<temp.size(); i++)
//    {
//        cout<<(temp[i]->data.toString())<< "   *^%    ";
//    }


    // update and insert finished validation;
    //string sqlStatement = "update student set student FirstName = abdelrahman where studentId = 3";

    // = "delete from student where departmentId = 1 ";
    // string sqlStatement = "insert into student values (1,abdelrahman,awad,25,1";
    // string sqlS = "insert into student values (9,abdo,amin,25,1";
//    string sqlStatement = "select * from student  ";
//    string sqlStatement="undo";

    // cout<<sqlStatement<<endl;
    // analyseQuery(sqlStatement);
//    analyseQuery(sqlS);
//    studentTable.display();
    string sqlStatement ;


    while(true)
    {
        cout<< " enter your query" <<endl;
        std::getline(std::cin,sqlStatement)  ;
        if(sqlStatement=="exit")
            break;
        else
            analyseQuery(sqlStatement);
    }
//
//    studentTable.display();
    return 0;

}

void analyseQuery(string query)
{
    string remainingStatement;
    std::string  token = query.substr(0, query.find(" "));

    if(token == "select")
    {
        remainingStatement = query.substr(query.find(" ") + 1,query.length());
        selectOperation(remainingStatement);
    }
    else if (token =="delete")
    {
        remainingStatement = query.substr(query.find(" ") + 1,query.length());
        deleteOperation(remainingStatement);
    }

    else if (token == "update")
    {
        remainingStatement = query.substr(query.find(" ") + 1,query.length());
        updateOpertaion(remainingStatement);

    }
    else if (token =="insert")
    {
        remainingStatement = query.substr(query.find(" ") + 1,query.length());
        insertOperation(remainingStatement);
    }
    else if (token=="undo")
    {
        Utilities::undo(Utilities::undoTypeName.back());
        Utilities::undoTypeName.pop_back();

    }
    else if (token =="help")
        help();
    else
        cout<<"query out of scope "<<endl ;
}

