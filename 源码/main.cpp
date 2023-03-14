#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include <fstream>
#include"functions.h"
using namespace std;
int main() {
    LinkList head=(LinkList)malloc(sizeof(Node));
    creat_List(head);
    int choice=1;
    while(choice) {
        showMenu();
        cin>>choice;
        fflush(stdin);
        switch(choice) {
            case 1: {
                insert_List(head);
                get_Time(choice);
                break;
            }
            case 2: {
                show_AllList(head);
                get_Time(choice);
                break;
            }
            case 3: {
                delete_List(head);
                get_Time(choice);
                break;
            }
            case 4: {
                find_List(head);
                get_Time(choice);
                break;
            }
            case 5: {
                blurfind_list(head);
                get_Time(choice);
                break;
            }
            case 6: {
                change_List(head);
                get_Time(choice);
                break;
            }
            case 7:{
                BigSort(head);
                get_Time(choice);
                break;
            }
            case 0: {
                cout<<"waiting for your next use"<<endl;
                get_Time(choice);
            }
            default: {
                system("pause");
                system("cls");
                break;
            }
        }
    }
    conserve_List(head);
    output_csv(head);
    creat_VCard(head);
    destory_List(head);
    head=NULL;
}




