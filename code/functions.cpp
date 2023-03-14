//
// Created by 15129 on 2023/2/1.
//
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include <fstream>
#include"functions.h"
using namespace std;
//实现日志功能，记录本系统的所有使用记录
void get_Time(int i) {
    FILE *fp;
    if ((fp = fopen ("log.txt","at" )) == NULL) {
        printf ("无法打开\n");
        exit (0);
    }
    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    fprintf(fp,"%d年 ",1900+p->tm_year);/*获取当前年份,从1900开始，所以要加1900*/
    fprintf(fp,"%d月 ",1+p->tm_mon);/*获取当前月份,范围是0-11,所以要加1*/
    fprintf(fp,"%d日",p->tm_mday);/*获取当前月份日数,范围是1-31*/
    fprintf(fp,"%d时",8+p->tm_hour);/*获取当前时,这里获取西方的时间,刚好相差八个小时*/
    fprintf(fp,"%d分 ",p->tm_min); /*获取当前分*/
    fprintf(fp,"%d秒\n",p->tm_sec); /*获取当前秒*/
    switch(i) {
        case 1: {
            fprintf(fp,"input information\n");
            break;
        }
        case 2: {
            fprintf(fp,"view the information\n");
            break;
        }
        case 3: {
            fprintf(fp,"delete the information\n");
            break;
        }
        case 4: {
            fprintf(fp,"find the information\n");
            break;
        }
        case 5: {
            fprintf(fp,"blur find the information\n");
            break;
        }
        case 6: {
            fprintf(fp,"change the information\n");
            break;
        }
        case 7:{
            fprintf(fp,"view the information following the grade\n");
            break;
        }
        default: {
            fprintf(fp,"drop out the system\n");
            break;
        }
    }
    fclose(fp);
}
//初始化链表  本项目中，链表自带两个结点---头结点与尾结点
void creat_List(LinkList head) {
    LinkList end=(LinkList)malloc(sizeof(Node));
    if(end==NULL) {
        cout<<"memory deficient"<<endl;
        exit(1);
    }
    head->next=end;
    end->next=NULL;
}
void destory_List(LinkList &head) {
    LinkList q;
    while(head) {
        q=head->next;
        free(head);
        head=q;
    }
    cout<<"destory done"<<endl;
    system("pause");
    system("cls");
}
/* ofstream的使用方法举例
ofstream p;
    p.open("output.csv",ios::out|ios::trunc);                //打开文件路径
    p<<"学号"<<","<<"名字"<<","<<"总分"<<","<<"名次"<<endl;    //输入内容，注意要用逗号，隔开
    p<<"010101"<<","<<"张三"<<","<<"98"<<","<<"1"<<endl;
    p<<"010102"<<","<<"李四"<<","<<"88"<<","<<"2"<<endl;
    p.close();

	关于排序功能实现的思考
	1.中文排序，首先C语言中，汉字是按照字符串来处理的，一个汉字占用2个字节，汉字的排序就是按照汉字的编码进行排序
	接着具体汉字的编码，就不是那么容易的了，编码一般以0x开头，表示是用一个十六进制数表示的。
	这种排序对我们理解排序并无优势
	2.若以学号排序，程序健壮性会受到较大影响
	3. 所以加了一个成绩作为结构体成员，理论上可以实现排序，但是要解决链表排序问题

*/
//对链表长度进行统计
int static_List(LinkList head){
    int i=0;
    while(head->next->next){
        i++;
        head=head->next;
    }
    return i;
}
//快速排序
void Quick_Sort(int *arr, int begin, int end){
    if(begin > end)
        return;
    int tmp = arr[begin];
    int i = begin;
    int j = end;
    while(i != j){
        while(arr[j] >= tmp && j > i)
            j--;
        while(arr[i] <= tmp && j > i)
            i++;
        if(j > i){
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    arr[begin] = arr[i];
    arr[i] = tmp;
    Quick_Sort(arr, begin, i-1);
    Quick_Sort(arr, i+1, end);
}
//将通讯录csv格式导出到output.csv文件
void output_csv(LinkList head) {
    ofstream p;
    p.open("output.csv",ios::out|ios::trunc);
    p<<"学号"<<","<<"姓名"<<","<<"性别"<< ","<<"学院"<<","<<"qq账户"<<","<<"电子邮箱"<<","<<"通讯地址"<<","<<"电话"<<
     "," <<"学生成绩"<<endl;
    while(head->next->next) {
        p<<head->next->s.StuNumber<<","<<head->next->s.Name<<","<<head->next->s.Gender
         <<","<<head->next->s.Institute<<","<<head->next->s.QqNumber<<","<<head->next->s.email<<","<<head->next->s.address<<","<<head->next->s.phone<<","
         <<head->next->s.grade<<endl;
        head=head->next;
    }
    p.close();
    cout<<"csv has been built up"<<endl;
}
int whether_Exist2(char*arr,LinkList head) {
    if(head->next->next->next==NULL)
        return 0;
    while(head->next->next->next!=NULL) {
        if(strcmp(head->next->s.StuNumber,arr)==0)
            return 1;
        else
            head=head->next;
    }
    return 0;
}
//添加数据
void insert_List(LinkList &head) {
    int i=1;
    LinkList temp=head;
    while(i) {
        while(temp->next->next!=NULL) {
            temp=temp->next;
        }
        LinkList r=(LinkList)malloc(sizeof(Node));
        r->next=temp->next;
        temp->next=r;
        /*if(r==NULL) {
            cout<<"memory deficient "<<endl;
            exit(1);
        }*/
        fflush(stdin);
        cout<<"now input the Student Number"<<endl;
        while(true) {
            gets(r->s.StuNumber);
            int k=whether_Exist2(r->s.StuNumber,head);
            if(k==1) {
                cout<<"have input the same student Number before, please try again"<<endl;
                continue;
            } else break;
        }
        cout<<"input the Name"<<endl;
        scanf("%s",r->s.Name);


        cout<<"input the gender(man is M ,woman is F)(be carefully,you can not change your gender later)"<<endl;
        while(true) {
            cin>>r->s.Gender;
            fflush(stdin);
            if(r->s.Gender=='M'||r->s.Gender=='F')
                break;
            else {
                cout<<"input wrong ,try again"<<endl;
                continue;
            }
        }
        cout<<"input the institute"<<endl;
        gets(r->s.Institute);
        cout<<"input the QQ number"<<endl;
        gets(r->s.QqNumber);
        cout<<"input the email"<<endl;
        gets(r->s.email);
        cout<<"input the address"<<endl;
        gets(r->s.address);
        cout<<"input the phone"<<endl;
        gets(r->s.phone);
        while(true){
            cout<<"input the grade"<<endl;
            scanf("%d",&r->s.grade) ;
            fflush(stdin);
            if(r->s.grade<=100&&r->s.grade>0)
                break;
            else{
                cout<<"input wrong ,please try again"<<endl;
                continue;
            }
        }
        fflush(stdin);
        cout<<"all put down"<<endl;
        system("pause");
        system("cls");
        cout<<"  input 0 to out, the other to continue"<<endl;
        scanf("%d",&i);
        fflush(stdin);
        system("pause");
        system("cls");
    }
}

//展示单个成员的信息
void show_Onelist(LinkList k) {
    cout<<"Student Number    :"<<k->s.StuNumber<<endl ;
    cout<<"Student Name      :"<<k->s.Name<<"\t";
    cout<<"Student Gender    :"<<k->s.Gender<<endl;
    cout<<"Student Institute :"<<k->s.Institute<<"\t";
    cout<<"Student QQ number :"<<k->s.QqNumber<<"\t";
    cout<<"Student email     :"<<k->s.email<<endl;
    cout<<"Student Address   :"<<k->s.address<<"\t";
    cout<<"Student Phone     :"<<k->s.email<<endl;
    cout<<"Student grade     :"<<k->s.grade<<endl;
    cout<<endl;
}
//展示全部数据信息
void show_AllList(LinkList &head) {
    LinkList k=head;
    if(k->next->next==NULL) {
        cout<<"sorry,the list is empty"<<endl;
    }
    while(k->next->next!=NULL) {
        k=k->next;
        show_Onelist(k);
    }
    system("pause");
    system("cls");
}
int if_Exist(char*arr,LinkList head) {
    LinkList p=head;
    if(p->next->next==NULL)
        return 0;
    while(p->next!=NULL) {
        if(strcmp(arr,p->s.StuNumber)==0) {
            show_Onelist(p);
            return 1;
        }
        p=p->next;
    }
    return 2;
}
int if_Exist1(char*arr,LinkList head) {
    LinkList p=head;
    if(p->next->next==NULL)
        return 0;
    while(p->next!=NULL) {
        if(strcmp(arr,p->s.Name)==0) {
            cout<<" get it! "<<endl;
            show_Onelist(p);
            return 1;
        }
        p=p->next;
    }
    cout<<"what you look for does not exist"<<endl;
}
int if_Exist2(char*arr,LinkList head) {
    LinkList p=head;
    if(p->next->next==NULL)
        return 0;
    while(p->next!=NULL) {
        if(strcmp(arr,p->s.StuNumber)==0) {
            cout<<" get it! "<<endl;
            show_Onelist(p);
            return 1;
        }
        p=p->next;
    }
    cout<<"what you look for does not exist"<<endl;
}
int if_Exist3(char*arr,LinkList head) {
    LinkList p=head;
    if(p->next->next==NULL)
        return 0;
    while(p->next!=NULL) {
        if(strcmp(arr,p->s.email)==0) {
            cout<<" get it! "<<endl;
            show_Onelist(p);
            return 1;
        }
        p=p->next;
    }
    cout<<"what you look for does not exist"<<endl;
}
//精确查找
void find_List(LinkList &head) {
    cout<<"请选择查找方式"<<endl;
    cout<<"1.姓名查找"<<"\t";
    cout<<"2.学号查找"<<"\t";
    cout<<"3.邮箱查找"<<"\t";
    int i=0;
    while(true) {
        cin>>i;
        fflush(stdin);
        if(i==1||i==2||i==3) {
            switch(i) {
                case 1: {
                    cout<<"please input which name you wanna to find "<<endl;
                    char arr[30];
                    gets(arr);
                    int j=if_Exist1(arr,head);
                    if(!j)	{
                        cout<<"List is empty"<<endl;
                        break;
                    } else
                        break;
                }
                case 2: {
                    cout<<"please input which student number you wanna to find"<<endl;
                    char arr1[30];
                    gets(arr1);
                    int j1=if_Exist2(arr1,head);
                    if(!j1)	{
                        cout<<"List is empty"<<endl;
                        break;
                    } else
                        break;
                }
                case 3: {
                    cout<<"please input which email you wanna to find"<<endl;
                    char arr2[30];
                    gets(arr2);
                    int j2=if_Exist3(arr2,head);
                    if(!j2)	{
                        cout<<"List is empty"<<endl;
                        break;
                    } else
                        break;
                }
            }
            break;
        } else {
            cout<<"input wrong,please try again"<<endl;
            continue;
        }
    }
    system("pause");
    system("cls");
}
void part_Find1(LinkList head,char *arr) {
    while(head->next!=NULL) {
        if(strstr(head->s.Name,arr)) {
            show_Onelist(head);
            head=head->next;
        } else
            head=head->next;
    }
    system("pause");
    system("cls");
}
void part_Find2(LinkList head,char *arr) {
    while(head->next!=NULL) {
        if(strstr(head->s.StuNumber,arr)) {
            show_Onelist(head);
            head=head->next;
        } else
            head=head->next;
    }
    system("pause");
    system("cls");
}
//模糊查找
int blurfind_list(LinkList head) {
    if(head->next->next==NULL) {
        cout<<"sorry,list is empty"<<endl;
        system("pause");
        system("cls");
        return 0;
    }
    cout<<"please input the type of the blur information"<<endl;
    cout<<"1.姓名"<<endl;
    cout<<"2.学号"<<endl;
    int i=0;
    char arr[30];
    while(true) {
        cin>>i;
        fflush(stdin);
        if(i==1) {
            cout<<"please input your blur information"<<endl;
            gets(arr);
            part_Find1(head,arr);
            break;
        }
        else if(i==2) {
            cout<<"please input your blur information"<<endl;
            gets(arr);
            part_Find2(head,arr);
            break;
        } else {
            cout<<"input wrong ,please correct your choice "<<endl;
            continue;
        }
    }
}
//删除数据
int delete_List(LinkList &head) {
    cout<<"please input the Student Number you wanna get"<<endl;
    char arr[30];
    scanf("%s",arr);
    fflush(stdin);
    LinkList p=head;
    int i=if_Exist(arr,head);
    if(i==1){
        cout<<"are you sure to delete the information ?you will lost it foverer"<<endl;
        cout<<"input 1 to continue , the other to quit the delete"<<endl;
        char k;
        scanf("%c",&k);
        fflush(stdin);
        if(k!='1') {
            cout<<"delete has been cancelled"<<endl;
            system("pause");
            system("cls");
            return 0;
        }
    }
    switch(i) {
        case 0:
            cout<<"List is empty "<<endl;
            break;
        case 1:
            while(p->next!=NULL) {
                if(strcmp(arr,p->next->s.StuNumber)==0) {
                    LinkList temp=p->next;
                    p->next=p->next->next;
                    free(temp);
                    cout<<"delete done"<<endl;
                    break;
                } else p=p->next;
            }
            break;
        case 2:
            cout<<"fail to find,for it does not exist"<<endl;
            break;
    }
    system("pause");
    system("cls");
}
//根据成绩对学生信息进行排序
int BigSort(LinkList head){
    int num=static_List(head);
    if(num==0){
        cout<<"list is empty"<<endl;
        system("pause");
        system("cls");
        return 0;
    }
    int *arr=(int *)malloc((num+1)*sizeof(int));
    LinkList p=head;
    LinkList h=head;
    int i;
    for(i=0;i<num;i++){
        arr[i]=p->next->s.grade;
        p=p->next;
    }
    arr[num]=-1;
    Quick_Sort(arr,0,num-1);
    for(int j=num-1;j>=0;){
        if(arr[j]==h->next->s.grade){
            show_Onelist(h->next);

            if(arr[j]==arr[j-1]){
                h=h->next;
            }
            else{
                h=head;
            }
            j--;
        }
        else
            h=h->next;
    }
    free(arr);
    arr=NULL;
    system("pause");
    system("cls");
}
//更改学生信息
int change_List(LinkList head) {
    if(head->next->next==NULL) {
        cout<<"List is empty, can not change any information"<<endl;
        system("pause");
        system("cls");
        return 0;
    }
    fflush(stdin);
    cout<<"please input the student number whose information you wanna change"<<endl;
    char arr[30];
    gets(arr);
    while(head->next) {
        if(strcmp(arr,head->next->s.StuNumber)==0) {
            cout<<"find that one,now begin the change"<<endl;
            show_Onelist(head->next);
            cout<<endl;
            while(true) {
                cout<<"please chang the student number"<<endl;
                char arr1[30];
                gets(arr1);
                fflush(stdin);
                if(strcmp(arr1,head->next->s.StuNumber)==0){
                    break;
                }
                int k=whether_Exist2(arr,head);
                if(k==1) {
                    cout<<"have input the same student Number before, please try again"<<endl;
                    continue;
                }
                else
                {   strcpy(head->next->s.StuNumber,arr1);
                    break;}
            }
            cout<<"please change the name"<<endl;
            gets(head->next->s.Name);
            cout<<"please chang your institute"<<endl;
            gets(head->next->s.Institute);
            cout<<"please change qqnumber"<<endl;
            gets(head->next->s.QqNumber);
            cout<<"please change the email"<<endl;
            gets(head->next->s.email);
            cout<<"please change address"<<endl;
            gets(head->next->s.address);
            cout<<"please change phone"<<endl;
            gets(head->next->s.phone);
            while(true){
                cout<<"input the grade"<<endl;
                scanf("%d",&head->next->s.grade) ;
                fflush(stdin);
                if(head->next->s.grade<=100&&head->next->s.grade>0)
                    break;
                else{
                    cout<<"input wrong ,please try again"<<endl;
                    continue;
                }
            }
            cout<<"change done"<<endl;
            fflush(stdin);
            system("pause");
            system("cls");
            return 0;
        } else
            head=head->next;
    }
    cout<<"input wrong ,please try again"<<endl;
    system("pause");
    system("cls");
}
//将所有录入的信息保存到writer.txt文件中
void conserve_List(LinkList head) {
    FILE *fp;
    if((fp=fopen("writer.txt","w"))==NULL) {
        printf ("无法打开\n");
        exit (0);
    }
    while(head->next->next) {
        fprintf(fp,"stuNumber\t:%s\n",head->next->s.StuNumber);
        fprintf(fp,"stuName\t:%s\n",head->next->s.Name);
        fprintf(fp,"stuGender\t:%c\n:",head->next->s.Gender);
        fprintf(fp,"stuInstitute\t:%s\n",head->next->s.Institute);
        fprintf(fp,"stuQQNum\t:%s\n",head->next->s.QqNumber);
        fprintf(fp,"stuEmail\t:%s\n",head->next->s.email);
        fprintf(fp,"stuAddress\t:%s\n",head->next->s.address);
        fprintf(fp,"stuPhone\t:%s\n",head->next->s.phone);
        fprintf(fp,"stuGrade\t:%d\n",head->next->s.grade);
        fprintf(fp,"\n");
        head=head->next;
    }
    fclose(fp);
    cout<<"information has been input to writer.txt"<<endl;
}
//显示菜单
void showMenu() {
    cout<<"1.添加学生联系人"<<endl;
    cout<<"2.显示学生联系人"<<endl;
    cout<<"3.删除学生联系人"<<endl;
    cout<<"4.查找学生联系人"<<endl;
    cout<<"5.模糊查找学生联系人"<<endl;
    cout<<"6.修改学生联系人"<<endl;
    cout<<"7.按成绩排序显示"<<endl;
    cout<<"0.退出通讯录并保存数据"<<endl;
}
//创建Vcard格式数据并存储
void creat_VCard(LinkList head) {
    LinkList p=head;
    while(p->next->next) {
        char FileName[50];
        sprintf(FileName,"./vcard/%s.vcard",p->next->s.Name);
        FILE *file=fopen(FileName,"w");
        if(file) {
            fprintf(file,"BEGIN:VCARD\nVERSION:2.1\n");
            fprintf(file,"ID:%s\n",p->next->s.StuNumber);
            fprintf(file,"N:%s\n",p->next->s.Name);
            fprintf(file,"GEN:%c\n",p->next->s.Gender);
            fprintf(file,"ORG:%s\n",p->next->s.Institute);
            fprintf(file,"QQ:%s\n",p->next->s.QqNumber);
            fprintf(file,"EMAIL:%s\n",p->next->s.email);
            fprintf(file,"ADDRESS:%s\n",p->next->s.address);
            fprintf(file,"PHONE:%d\n",p->next->s.phone);
            fprintf(file,"GRADE:%d\n",p->next->s.grade);
            fprintf(file,"END:VCARD");
        }
        fclose(file);
        p=p->next;
    }
    cout<<"information has been input into vcard"<<endl;
}
