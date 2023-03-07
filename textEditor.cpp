#include <iostream>
#include <string>
#include<fstream>
#include<stack>
using namespace std;

class Node{
    public:
    string data;
    Node* next;
// Creating strorage=====================================================
    Node(string val){
        data = val;
        next = NULL;
    }
};
// creating stack for undo operation ==============
stack<string> undo;
stack<string> redo;

// show commands==================================================
void showCommands(){
    cout<<" ********************************************"<<endl;
    cout<<" * Enter 1 for help"<<endl;
    cout<<" * Enter 2 for insert the data at any line"<<endl;
    cout<<" * Enter 3 for updating the data"<<endl;
    cout<<" * Enter 4 for append the data at end "<<endl;
    cout<<" * Enter 5 for search a particuler data"<<endl;
    cout<<" * Enter 6 for deleting a particuler data"<<endl;
    cout<<" * Enter 7 for dispaly all the data"<<endl;
    cout<<" * Enter 8 for saving the data permanently"<<endl;
    cout<<" * Enter 10 for undo"<<endl;
    cout<<" * Enter 11 for redo"<<endl;
    cout<<" * Enter 12 for seeing the data from file"<<endl;
    cout<<" * Enter 9 for exit "<<endl;
    cout<<" ********************************************"<<endl;
}

// function for pushing and converting data into string for stack operations....
void pushIntoStack(int id,int loc,string data){
    string value = to_string(id)+to_string(loc)+data;
        undo.push(value);
}

//insert data =====================================================
// function to check wheather the given location exits or not.....
bool locExists(Node*head,int loc){
    Node*temp = head;
    int count = 1;
    while(temp->next != NULL){
        temp = temp->next;
        count++;
    }
    if(count >= loc){
        return true;
    }else{
        return false;
    }
}
//insertion at given LOCATION...............
void insertAtLoc(Node* &head,string val,int loc,int condition){
    Node*n =  new Node(val);
    int i = 1;
    Node*temp = head;
    while(i < loc-1){
        temp = temp->next;
        i++;
    }
    n->next = temp->next;
    temp->next = n;
    if(condition == 1){
    pushIntoStack(1,loc,val);
    }
}
//insertion at Begining...........
void insertAtBegin(Node* &head,string val,int loc,int condition){
    Node*n = new Node(val);
    Node*temp = head;
    n->next = temp;
    head = n;
    if(condition == 1){
    pushIntoStack(1,loc,val);
    }
}

//append data=====================================================
void appendData(Node* &head,string val){
    Node*n = new Node(val);
    if(head == NULL){
        head = n;
        return;
    }
    Node*temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = n;
    n->next = NULL;
}

//update data=====================================================
Node*fetchData(Node* &head ,int loc){
    Node*temp = head;
    int i = 1;
    while(i<loc){
        temp = temp->next;
        i++;
    }
    return temp;
}

//search data=====================================================
int searchData(Node*head,string value){
    Node*temp = head;
    int i = 0;
    while(temp != NULL){
        i++;
        if(temp->data.find(value) != -1){
            return i;
        }
        temp = temp->next;
    }
    return 0;
}

//delete data=====================================================
void deleteNodeAtLoc(Node* &head,int loc,int condition){
    Node*temp = head;
    int i = 1;
    while (i < loc-1)
    {
        temp =temp->next;
        i++;
    }
    if(condition == 1){
    pushIntoStack(0,loc,temp->next->data);
    }
    Node*freeNodeMemory = temp->next;
    temp->next = temp->next->next;
    delete freeNodeMemory;
}
//deletion at beging...........
void deleteAtBeging(Node* &head,int condition){
    Node*temp = head;
    if(condition == 1){
        pushIntoStack(0,1,temp->data);
    }
    head = temp->next;
    delete temp;
}

//display data=====================================================
void displayData(Node*head){
    if(head == NULL){
        cout<<"No data is available !! "<<endl;
        return;
    }
    int i = 1;
    Node*temp = head;
    cout<<"--textEditor----------------"<<endl;
    while(temp != NULL){
        cout<<i<<".  "<<temp->data<<endl;
        temp = temp->next;
        i++;
    }
}

//save data in permanent storage=====================================================
void saveData(Node*head){
        Node*temp = head;
        ofstream fileInput("texteditor.txt");
        while(temp != NULL){
            fileInput<<temp->data<<endl;
            temp = temp->next;
        }
        fileInput.close();
        cout<<"Your data has been saved successfully !!"<<endl;
}

// function which shows the data of the file ==============================
void showfiledata(){
    ifstream fileOutput("texteditor.txt");
    string line;
    int i =0;
    while (fileOutput) {
        i++;
        getline(fileOutput, line);
        cout << line << endl;
    }
    if(i == 0){
        cout<<"No data is available in the file."<<endl;
    }
}

// function to read a line ==============================================
string readLine(){
    string ans ="";
    int exit =1;
    while(exit){
        string data;
        cin>>data;
        if(data =="." && ans == ""){
            return "qlpo12311";  // this is a random string, if there is no data  and input data is 0 then return "qlpo12311".
        }else{
            if(data == "."){
                exit = 0;
            }else{
            ans += data;
            ans+=" ";
            }
        }
    }
    return ans;
}

//undo and redo operation===============================================
void undoAndRedoOpertion(Node* &head,string s,char opCheck){
    int id = (int(s[0])-'0');
    int loc = 0;
    string data;
    for(int i = 1;i<s.size();){
        if(s[i] >= '0' && s[i]<='9'){
            loc = ((loc *10) + int(s[i]) - '0');
            i++;
        }else{
            data += s[i];
            i++;
        }
    }
    int v1=1,v2=0;
    if(opCheck == 'r'){
        v1 = 0;
        v2 = 1;
    }
    if(id == v1){
        if(loc == 1){
            deleteAtBeging(head,0);
        }else{
            deleteNodeAtLoc(head,loc,0);
        }
    }else if(id == v2){
        if(loc == 1 || loc == 0){
            insertAtBegin(head,data,loc,0);
        }else{
            insertAtLoc(head,data,loc,0);
        }
    }else{
        cout<<"some error occured !!"<<endl;
    }
}

int main(){
    Node*head = NULL;
    int query;
    int check = 1;
    int exit = 1;
    cout<<"   ---------WELCOME TO TEXTEDITOR---------"<<endl;
    showCommands();
    while(exit){
        if(check){
            cout<<"Enter Your Query: ";
            check = 0;
        }else{
            cout<<"Enter Your next Query: ";
        }
        cin>>query;
        if(query == 9){
            exit = 0;
            break;
        }
        switch(query){
            case 1:{
                showCommands();
                break;
            }
            // insertion            
            case 2:{
                string data;
                int loc;
                if(head == NULL){
                     cout<<"Enter your data to insert [ENTER (.) to EXIT] :";
                     data = readLine();
                     if(data != "qlpo12311"){
                         insertAtBegin(head,data,1,1);
                        cout<<"Data Inserted !!"<<endl;
                     }
                }else if(head->next == NULL){
                     cout<<"Enter your data to insert [ENTER (.) to EXIT] :";
                     data = readLine();
                     if(data != "qlpo12311"){
                        insertAtBegin(head->next,data,2,1);
                        cout<<"Data Inserted !!"<<endl;
                     }
                }else{
                    cout<<"In which line you want to insert data: ";
                    cin>>loc;
                    if(loc == 1){
                        cout<<"Enter your data to insert [ENTER (.) to EXIT] :";
                        data = readLine();
                        if(data != "qlpo12311"){
                            insertAtBegin(head,data,loc,1);
                            cout<<"Data Inserted !!"<<endl;
                         }
                    }else if(locExists(head,loc)){                    
                        cout<<"Enter your data to insert [ENTER (.) to EXIT] :";
                        data = readLine();
                        if(data != "qlpo12311"){
                            insertAtLoc(head,data,loc,1);
                            cout<<"Data Inserted !!"<<endl;
                        }
                    }else{
                        cout<<"index does not exist !!"<<endl;
                    }
                }
                break;  
            }
            //updation
            case 3:{
                int loc;
                if(head == NULL){
                    cout<<" List is Empty !, there is Nothing is to be updated."<<endl;
                    break;
                }else{
                    cout<<"Enter the line number of which data you want to update: ";
                    cin>>loc;
                    if(locExists(head,loc)){
                        string data;
                        // show the data
                        Node*temp = fetchData(head,loc);
                        cout<<"Your Data is: "<<temp->data<<endl;
                        cout<<"Enter your updated Data [ENTER (.) to EXIT] : ";
                        data = readLine();
                        if(data != "qlpo12311"){
                            //updating the data;
                            temp->data = data;
                            cout<<"Data updated !!"<<endl;
                        }
                    }else{
                        cout<<"index does not exist !!"<<endl;
                    }
                }
                break;
            }
            // append             
            case 4:{
                string data;
                cout<<"Enter Your Data to Append [ENTER (.) to EXIT] : ";
                data = readLine();
                if(data != "qlpo12311"){
                    appendData(head,data);
                    cout<<"Data Inserted !!"<<endl;
                }
                break;
            }
            // search
            case 5:{
                string data;
                cout<<"Enter Your Word to search : ";
                cin>>data;
                int wordInLine = searchData(head,data);
                if(wordInLine == 0){
                    cout<<"Data Not Found"<<endl;
                }else{
                    cout<<"Data Found in line "<<wordInLine<<endl;
                }
                break;
            }
            //deletion
            case 6:{
                int loc;
                if(head == NULL){
                    cout<<" List is Empty !, there is Nothing is to be Deleted."<<endl;
                }else{
                    cout<<"Enter the line you want to Delete: ";
                    cin>>loc;
                    if(loc == 1){
                        deleteAtBeging(head,1);
                        cout<<"Data Deleted !!"<<endl;
                    }else if(locExists(head,loc)){                    
                        deleteNodeAtLoc(head,loc,1);
                        cout<<"Data Deleted !!"<<endl;
                    }else{
                        cout<<"index does not exist !!"<<endl;
                    }
                }
                break;
            }
            // display 
            case 7:{
                displayData(head);
                break;
            }
            //save the data in file
            case 8:{
                if(head == NULL){
                    cout<<" List is Empty !, there is Nothing is to be saved."<<endl;
                }else{
                    saveData(head);
                }
                break;
            }
            case 10:{
                if(undo.empty() == false){
                string data = undo.top();
                undo.pop();
                redo.push(data);
                undoAndRedoOpertion(head,data,'u');
                cout<<"Undo Done!"<<endl;
                }else{
                    cout<<"undo is empty !!"<<endl;
                }
                break;
            }
            case 11:{
                if(redo.empty() == false){
                    string data = redo.top();
                    redo.pop();
                    undo.push(data);
                    undoAndRedoOpertion(head,data,'r');
                cout<<"Redo Done!"<<endl;
                }else{
                    cout<<"redo is empty !!"<<endl;
                }
                break;
            }
            case 12:{
                    showfiledata();
                    break;
            }
            default:{
                cout<<"INVALID COMMAND !!"<<endl;
                exit = 0;
                break;
            }
        }
    }
return 0;
}