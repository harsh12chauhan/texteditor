#include <iostream>
#include <string>
#include<fstream>

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
    cout<<" * for exit press q "<<endl;
    cout<<" ********************************************"<<endl;
}
//insert data =====================================================
// function to check wheather the given location exits or not =====
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
//insertion at given LOCATION ==========================
void insertAtLoc(Node* &head,string val,int loc){
    Node*n =  new Node(val);
    int i = 1;
    Node*temp = head;
    while(i < loc-1){
        temp = temp->next;
        i++;
    }
    n->next = temp->next;
    temp->next = n;
}
//insertion at Begining =====================
void insertAtBegin(Node* &head,string val){
    Node*n = new Node(val);
    Node*temp = head;
    n->next = temp;
    head = n;
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
bool searchData(Node*head,string value){
    Node*temp = head;
    while(temp != NULL){
        if(temp->data == value){
            return true;
        }
        temp = temp->next;
    }
    return false;
}
//delete data=====================================================
void deleteNodeAtLoc(Node* &head,int loc){
    Node*temp = head;
    int i = 1;
    while (i < loc-1)
    {
        temp =temp->next;
        i++;
    }
    Node*freeNodeMemory = temp->next;
    temp->next = temp->next->next;
    delete freeNodeMemory;
}
void deleteAtBeging(Node* &head){
    Node*temp = head;
    head = temp->next;
    delete temp;
}
//display data=====================================================
void displayData(Node*head){
    if(head == NULL){
        cout<<"No data is available !! "<<endl;
    }
    int i = 1;
    Node*temp = head;
    while(temp != NULL){
        cout<<i<<".  "<<temp->data<<endl;
        temp = temp->next;
        i++;
    }
}
//undo operation=====================================================
// *is to be implemented...
//redo operation=====================================================
// *is to be implemented...

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
void showfiledata(){
    ifstream fileOutput("texteditor.txt");
    string line;
    while (fileOutput) {
        getline(fileOutput, line);
        cout << line << endl;
    }
    cout<<"========================================"<<endl;
}

int main(){
    Node*head = NULL;
    int query;
    int check = 1;
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
            break;
        }
        switch(query){
            case 1:{
                showCommands();
                break;
            }
            case 2:{
                string data;
                int loc;
                if(head == NULL){
                     cout<<"Enter your data to insert :";
                     cin>>data;
                    insertAtBegin(head,data);
                    cout<<"Data Inserted !!"<<endl;
                }else{
                    cout<<"In which line you want to insert data: ";
                    cin>>loc;
                    if(loc == 1){
                        cout<<"Enter your data to insert :";
                        cin>>data;
                        insertAtBegin(head,data);
                        cout<<"Data Inserted !!"<<endl;
                    }else if(locExists(head,loc)){                    
                        cout<<"Enter your data to insert :";
                        cin>>data;
                        insertAtLoc(head,data,loc);
                        cout<<"Data Inserted !!"<<endl;
                    }else{
                        cout<<"index does not exist !!"<<endl;
                    }
                }
                break;
            }
            case 3:{
                int loc;
                if(head == NULL){
                    cout<<" List is Empty !, there is Nothing is to be updated."<<endl;
                    break;
                }else{
                    cout<<"Enter the line number of which data you want ot update: ";
                    cin>>loc;
                    if(locExists(head,loc)){
                        string data;
                        // show the data
                        Node*temp = fetchData(head,loc);
                        cout<<"Your Data is: "<<temp->data<<endl;
                        cout<<"Enter your updated Data: ";
                        cin>>data;
                        //updating the data;
                        temp->data = data;
                        cout<<"Data updated !!"<<endl;
                    }else{
                        cout<<"index does not exist !!"<<endl;
                    }
                }
                break;
            }
            case 4:{
                string data;
                // cout<<"Enter Your Data to Append : ";
                // cin>>data;
                appendData(head,"data");
                appendData(head,"harsh");
                appendData(head,"yash");
                appendData(head,"buddy");
                appendData(head,"someone");
                appendData(head,"everyone");
                cout<<"Data Inserted !!"<<endl;
                break;
            }
            case 5:{
                string data;
                cout<<"Enter Your Data to search : ";
                cin>>data;
                if(searchData(head,data)){
                    cout<<"Data Found"<<endl;
                }else{
                    cout<<"Data Not Found"<<endl;
                }
                break;
            }
            case 6:{
                int loc;
                if(head == NULL){
                    cout<<" List is Empty !, there is Nothing is to be Deleted."<<endl;
                }else{
                    cout<<"Of which line you want to Delete data: ";
                    cin>>loc;
                    if(loc == 1){
                        deleteAtBeging(head);
                        cout<<"Data Deleted !!"<<endl;
                    }else if(locExists(head,loc)){                    
                        deleteNodeAtLoc(head,loc);
                        cout<<"Data Deleted !!"<<endl;
                    }else{
                        cout<<"index does not exist !!"<<endl;
                    }
                }
                break;
            }
            case 7:{
                displayData(head);
                break;
            }
            case 8:{
                if(head == NULL){
                    cout<<" List is Empty !, there is Nothing is to be saved."<<endl;
                    break;
                }else{
                    saveData(head);
                }
                break;
            }
            case 11:{
                    showfiledata();
                    break;
            }
            default:{
                cout<<"INVALID COMMAND !!"<<endl;
                break;
            }
        }
    }
return 0;
}