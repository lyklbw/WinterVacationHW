//
// Created by 15129 on 2023/2/1.
//

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H
typedef struct person {
    char StuNumber[30];
    char Name[30];
    char Gender;
    char Institute[30];
    char QqNumber[30];
    char email[30];
    int grade;
    char address[30];
    char phone[30];
} STUDENT;
/*基本信息:
	学号，姓名，性别，学院，qq账号，邮箱
	地址，成绩
*/
typedef struct linknode {
    STUDENT s;
    struct linknode *next;
} Node,*LinkList;

void get_Time(int i);

void creat_List(LinkList head);

void destory_List(LinkList &head);

int static_List(LinkList head);

void Quick_Sort(int *arr, int begin, int end);

void output_csv(LinkList head);

int whether_Exist2(char*arr,LinkList head);

void insert_List(LinkList &head);

void show_Onelist(LinkList k);

void show_AllList(LinkList &head);

int if_Exist(char*arr,LinkList head);

int if_Exist1(char*arr,LinkList head);

int if_Exist2(char*arr,LinkList head);

int if_Exist3(char*arr,LinkList head);

void find_List(LinkList &head);

void part_Find1(LinkList head,char *arr);

void part_Find2(LinkList head,char *arr);

int blurfind_list(LinkList head);

int delete_List(LinkList &head);

int BigSort(LinkList head);

int change_List(LinkList head);

void conserve_List(LinkList head);

void showMenu();

void creat_VCard(LinkList head);

#endif //UNTITLED_FUNCTIONS_H
