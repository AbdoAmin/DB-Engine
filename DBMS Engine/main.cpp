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
using namespace std;

struct Condition
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

class Utilities
{
public:
    static bool checkValidationDepartment( Table<Department>* departmentLinkedList,int departmentId)
    {
        stringstream sstm;
        sstm << departmentId;
        Condition paramter;
        paramter.name="departmentId";
        paramter.value=sstm.str();
        vector<Condition> temp;
        temp.push_back(paramter);
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

};
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
    static bool updateQuery(L & tableAsLinkedList,vector<Condition> conditions,vector<Condition> setOfValues)
    {
        C condition=Utilities::generateUpdatedClass<C>(conditions);
        vector<N*> searched=tableAsLinkedList.search(condition);
        if(searched.size()>0)
        {
            C comperable=Utilities::generateUpdatedClass<C>(setOfValues);
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
    static bool deleteQuery(L& tableAsLinkedList,vector<Condition> conditions)
    {
        C condition=Utilities::generateUpdatedClass<C>(conditions);
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
    static void insertQuery(L& tableAsLinkedList,vector<Condition> data)
    {
        C comperable=Utilities::generateUpdatedClass<C>(data);
        tableAsLinkedList.append(comperable);
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
        found = spaceToRemove.find(" ",found+1);
        if (found!=-1)
        {
            spaceToRemove=spaceToRemove.substr(0,found) + spaceToRemove.substr(found+1);
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
        cout<<fileName<<"fileName"<<endl;

        fileName = removeSpaces(queryStatment) ;
        columns=splitColumn(removeSpaces(columnStatment));
        condition=splitCondition(removeSpaces(conditionStatment)) ;
    }

    cout<<fileName<<"fileName"<<endl;
    if(isFileCreated(fileName))
    {

        if(isValidColumns(columns,fileName)&&isValidColumns(condition,fileName))
        {
            cout<<"valid query " <<endl;
        }
        else
        {
            cout<<INVALID_QUERY<<endl;
        }
//        for(int i=0; i<c.size(); i++)
//        {
//            cout<<" condition name "<<c[i].name ;
//            cout<<" condition value "<<c[i].value<<endl;
//        }
//        for(int i=0; i<l.size(); i++)
//        {
//            cout<<" coulmn  "<<l[i]<<endl;
//        }
//        cout<<fileName<<" = file name ";
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
        cout<<endl<<queryStatment<<endl;
        fileName = removeSpaces(queryStatment.substr(queryStatment.find("from")+4,queryStatment.find("where")-5));
        queryStatment = removeSpaces(queryStatment.substr(queryStatment.find("from")+4,queryStatment.length())) ;
        conditionStatment = queryStatment.substr(queryStatment.find("where")+5,queryStatment.length());
        cout <<endl<<fileName <<"file name "<<endl;
        if(isFileCreated(removeSpaces(fileName)))
        {
            vector<Condition> conditons=splitCondition(removeSpaces(conditionStatment));
            if(isValidColumns(conditons,fileName))
                cout<<"query  valid "<<endl;
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
              if(fileName=="student")
              {
                  OurSQL::updateQuery(studentTable,condition,columnsAndValuesToUpdate)
              }
              else if (fileName=="department")
              {

              }
            }
            else
            {
                cout<<INVALID_QUERY;

            }


        }
        // no condition and will update all
        // specific case need to handle it
        else
        {
            columnsToUpdate = queryStatment ;
            vector<Condition> columnsAndValuesToUpdate= splitCondition(columnsToUpdate);

            for(int i=0; i<columnsAndValuesToUpdate.size(); i++)
            {
                cout<<columnsAndValuesToUpdate[i].name<<endl;
                cout<<columnsAndValuesToUpdate[i].value<<endl;
            }
            cout<<"update with no condition";
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
        cout<<fileName<<endl;
        insertQuery=removeSpaces(insertQuery);
        if(isFileCreated(fileName))
        {
            attribute=insertQuery.substr(insertQuery.find("(")+1, insertQuery.find(")")-8);
            vector<string> valuesToInsert=splitColumn(attribute);

            if(fileName=="student" && valuesToInsert.size()==5)
            {
                //OurSQL::insertQuery(studentTable,valuesToInsert);
            }
            else if (fileName=="department" && valuesToInsert.size()==2)
            {

            }



            }
        //attribute=insertQuery.substr(insertQuery.find(into)+4,insertQuery.length())
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
    studentColumns.push_back("studentId");
    studentColumns.push_back("studentFirstName");
    studentColumns.push_back("studentLastName");
    studentColumns.push_back("studentAge");
    studentColumns.push_back("departmentId");
    departmentColumns.push_back("departmentId");
    departmentColumns.push_back("departmentName");
    cout <<fileName;
    if (fileName == "student")
    {

        for(int i=0; i<column.size(); i++)
        {
            cout<<endl <<column[i] <<"is equal ";
            cout <<studentColumns[0] <<endl;
            if(column[i] == studentColumns[0]||column[i] == studentColumns[1]
                    || column[i] == studentColumns[2]||column[i] == studentColumns[3]||column[i] == studentColumns[4])
            {
                return true ;
            }
            else
            {
                return false;
            }
        }
    }
    else if (fileName=="department")
    {
        for(int i=0; i<column.size(); i++)
        {
            for(int j=0; j<column.size(); j++)
            {
                if(column[i]== departmentColumns[0] || column[i]==departmentColumns[1])
                {
                    cout<<column[i] <<endl;
                    cout<< departmentColumns[0]<<endl;
                    cout<<departmentColumns[1]<<endl;

                    return true ;
                }
                else
                {
                    cout<<column[i] << departmentColumns[0]<<endl;
                    cout<<departmentColumns[1]<<endl;
                    return false;
                }
            }
        }
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
    }
}
int main()
{
    departmentTable.append( Department(1,"dept").genarateNode());
    departmentTable.append(Department(2,"dept").genarateNode());
    departmentTable.append(Department(3,"dept").genarateNode());
    departmentTable.append(Department(4,"dept").genarateNode());
//    departmentLinkedList.display();
    cout<<"------------------------------------------"<<endl;
    studentTable.append(Student(1,"ismail","hamda",15,8).genarateNode());
    studentTable.append(Student(2,"ahmed","hamda",15,3).genarateNode());
//    studentLinkedList.display();
    studentTable.append(Student(3,"hassan","mostafe",20,1).genarateNode());

    // update and insert finished validation;
    3;hassan;mostafe;20;1
    string sqlStatement = "update student set studentFirstName = abdelrahman where studentId = 3";
    //string sqlStatement = "delete from department where departmentId = 5 ";
   // string sqlStatement = " insert into student values (abdelrahman,awad,25,4";
    //string sqlStatement = "select departmentId,  from  student where departmentId = 5";
//    string sqlStatement="undo";

    cout<<sqlStatement<<endl;
    analyseQuery(sqlStatement);
        studentTable.display();

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
        cout<<"i want to undo ya ismail beeh " ;
    else
        cout<<"query out of scope "<<endl ;
}

