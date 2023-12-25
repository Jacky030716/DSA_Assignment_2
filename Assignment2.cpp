//Utilization of linked-list to create a hostel management system

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Struct for storing information

class hostelNode{
    private:
        int roomNum;
        string collegeName;
        float hostelFee;
        string matricNo;
    
    public:
        hostelNode *next;

        hostelNode(){
            roomNum = 0;
            collegeName = "";
            hostelFee = 0.0;
            matricNo = "";
            next = NULL;
        }

        hostelNode(int id, string name, float fee, string mNo) : roomNum(id), collegeName(name), hostelFee(fee), matricNo(mNo), next(NULL){} 

        int getroomNum() {return roomNum;}
        string getcollegeName() {return collegeName;}
        float getHostelFee() {return hostelFee;}
        string getMatricNo() {return matricNo;}
};

class List{
    private:
        hostelNode *head;

    public:
        // Constructor
        List() {head = NULL;}

        // Check whether the room is empty
        bool isEmpty() {return head == NULL;}

        // Insert a new room at the front
        void insertFront(int id, string name, float fee, string mNo){
            hostelNode *newNode = new hostelNode(id, name, fee, mNo);

            if(isEmpty()){
                head = newNode;
            }
            else{
                newNode->next = head;
                head = newNode;
            }
        }

        // Insert a new room at the end
        void insertEnd(int id, string name, float fee, string mNo){
            hostelNode *temp = head;
            hostelNode *newNode = new hostelNode(id, name, fee, mNo);
            newNode->next = NULL;

            if(isEmpty()){
                head = newNode;
            }
            
            else{
                while (temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }

        void insertCertain(int id, string name, float fee, string mNo, int p){
            hostelNode *newNode = new hostelNode(id, name, fee, mNo);

            if (p == 0) {
                newNode->next = head;
                head = newNode;
            } else {
                hostelNode *temp = head;
                int currIndex = 0;
                while (temp != nullptr && currIndex < p - 1){
                    temp = temp->next;
                    currIndex++;
                }
                if (temp != nullptr) {
                    newNode->next = temp->next;
                    temp->next = newNode;
                } else {
                    cout << "Index out of range" << endl;
                }
            }
        }

        int findRoom(int id){
            hostelNode *temp = head;
            int currIndex = 0;
            while(temp && temp->getroomNum() != id){
                temp = temp->next;
                currIndex++;
            }
            if(currIndex){
                return currIndex;
            }
            else{
                cout << "Room not found" << endl;
                return 0;
            }
        }

        void deleteRoomFromFront(){
            hostelNode *temp = head;

            if(head == NULL){
                return;
            }

            head = temp->next;
            delete(temp);
        }

        void deleteCertainRoom(int id){
            hostelNode *temp = head;
            hostelNode *prev = NULL;
            int currIndex = 1;

            while (temp && temp->getroomNum() != id){
                prev = temp;
                temp = temp->next;
                currIndex++;
            }
            if(temp){
                if(prev){
                    prev->next = temp->next;
                    delete temp;
                }
                else{
                    head = temp->next;
                    delete temp;
                }
            }
        }

        void deleteRoomFromEnd(){
            hostelNode *temp = head;
            hostelNode *prev = NULL;

            if(isEmpty()){
                cout << "The list is empty. Cannot delete!" << endl;
                return;
            }

            while(temp->next != NULL){
                prev = temp;
                temp = temp->next;
            }

            if(prev){
                delete(temp);
                prev->next = NULL;
            }

            else{
                delete head;
                head = NULL;
            }
        }

        void displayRoomList(){
            hostelNode *temp = head;
            int currIndex = 1;

            if(isEmpty()){
                cout << "\nThere is no room currently!" << endl;
                return;
            }

            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "                     Room List                    " << endl;
            cout << "--------------------------------------------------" << endl;
            cout << left << setw(10) << "Room ID " 
                    << setw(15) << "College Name"
                    << setw(15) << "Hostel Fee"
                    << setw(15) << "Matric No" 
                    << endl;
            cout << "--------------------------------------------------" << endl;
                    
            while(temp != NULL){
                cout << left << setw(10) << temp->getroomNum()
                     << setw(15) << temp->getcollegeName()
                     << setw(15) << temp->getHostelFee()
                     << setw(15) << temp->getMatricNo()
                     << endl << endl;;
                temp = temp->next;
                currIndex++;
            }
        }
};

void displayInsertMenu(){
    cout << "\nPlease choose your choice" << endl;
    cout << "1. Insert From Front" << endl;
    cout << "2. Insert At End" << endl;
    cout << "3. Insert At Certain Position" << endl;
    cout << "Your choice: ";
}

void displayDeleteMenu(){
    cout << "\nPlease choose your choice" << endl;
    cout << "1. Delete From Front" << endl;
    cout << "2. Delete At End" << endl;
    cout << "3. Delete At Certain Position" << endl;
    cout << "Your choice: ";
}

int main(){
    List hostelList;
    int choice;
    int id;
    string name, mNo;
    float fee;

    fstream inFile("hostel.txt", ios::in);

    if(!inFile.is_open()){
        cout << "Error when opening the file!";
        return 0;
    }

    while(!inFile.eof()){
        inFile >> id;
        inFile.ignore();
        getline(inFile, name, ' ');
        inFile >> fee;
        inFile.ignore();
        getline(inFile, mNo, '\n');

        hostelList.insertEnd(id, name, fee, mNo);
        inFile.ignore();
    }

    do{
        cout << " --------------------------" << endl;
        cout << "| Hostel Management System |" << endl;
        cout << " --------------------------" << endl;
        cout << "1. Insert Room" << endl;
        cout << "2. Delete Room" << endl;
        cout << "3. Find a room" << endl;
        cout << "4. Display all rooms" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Enter room ID: ";
                cin >> id;
                cout << "Enter room name: ";
                cin >> name;
                cout << "Enter room fee: ";
                cin >> fee;
                cout << "Enter student matric no: ";
                cin >> mNo;
                int insertChoice;

                do{
                    displayInsertMenu();
                    cin >> insertChoice;
                    if(insertChoice == 1){
                    hostelList.insertFront(id, name, fee, mNo);
                    }

                    else if(insertChoice == 2){
                        hostelList.insertEnd(id, name, fee, mNo);
                    }

                    else if(insertChoice == 3){
                        int insertPosition;
                        cout << "Enter the position that you want to insert: ";
                        cin >> insertPosition;
                        hostelList.insertCertain(id, name, fee, mNo, insertPosition);
                    }

                    else{
                        cout << "\nInvalid choice" << endl;
                    }
                }while(insertChoice < 1 || insertChoice > 3);

                break;

            case 2:
                int deleteChoice;

                do{
                    displayDeleteMenu();
                    cin >> deleteChoice;

                    if(deleteChoice == 1){
                        hostelList.deleteRoomFromFront();
                    }

                    else if(deleteChoice == 2){
                        hostelList.deleteRoomFromEnd();
                    }

                    else if(deleteChoice == 3){
                        int tempId;
                        cout << "Enter the room id that you want to delete: ";
                        cin >> tempId;
                        hostelList.deleteCertainRoom(tempId);
                    }

                    else{
                        cout << "\nInvalid choice! ";
                    }
                }while(deleteChoice < 1 || deleteChoice > 3);
                
                break;

            case 3:
                int tempRoom, indexNum;
                cout << "Enter the room ID that you want to find: ";
                cin >> tempRoom;
                indexNum = hostelList.findRoom(tempRoom);
                cout << "The room is at " << indexNum + 1 << endl;
                break;
            
            case 4:
                hostelList.displayRoomList();
                break;

            case 5:
                cout << "\nThank you for using this system" << endl;
                break;
            default:
                cout << "\nInvalid choice" << endl;
                break;
        }
    }while(choice > 0 && choice <= 5);

    return 0;
}







