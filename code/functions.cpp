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
//ʵ����־���ܣ���¼��ϵͳ������ʹ�ü�¼
void get_Time(int i) {
    FILE *fp;
    if ((fp = fopen ("log.txt","at" )) == NULL) {
        printf ("�޷���\n");
        exit (0);
    }
    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    fprintf(fp,"%d�� ",1900+p->tm_year);/*��ȡ��ǰ���,��1900��ʼ������Ҫ��1900*/
    fprintf(fp,"%d�� ",1+p->tm_mon);/*��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1*/
    fprintf(fp,"%d��",p->tm_mday);/*��ȡ��ǰ�·�����,��Χ��1-31*/
    fprintf(fp,"%dʱ",8+p->tm_hour);/*��ȡ��ǰʱ,�����ȡ������ʱ��,�պ����˸�Сʱ*/
    fprintf(fp,"%d�� ",p->tm_min); /*��ȡ��ǰ��*/
    fprintf(fp,"%d��\n",p->tm_sec); /*��ȡ��ǰ��*/
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
//��ʼ������  ����Ŀ�У������Դ��������---ͷ�����β���
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
/* ofstream��ʹ�÷�������
ofstream p;
    p.open("output.csv",ios::out|ios::trunc);                //���ļ�·��
    p<<"ѧ��"<<","<<"����"<<","<<"�ܷ�"<<","<<"����"<<endl;    //�������ݣ�ע��Ҫ�ö��ţ�����
    p<<"010101"<<","<<"����"<<","<<"98"<<","<<"1"<<endl;
    p<<"010102"<<","<<"����"<<","<<"88"<<","<<"2"<<endl;
    p.close();

	����������ʵ�ֵ�˼��
	1.������������C�����У������ǰ����ַ���������ģ�һ������ռ��2���ֽڣ����ֵ�������ǰ��պ��ֵı����������
	���ž��庺�ֵı��룬�Ͳ�����ô���׵��ˣ�����һ����0x��ͷ����ʾ����һ��ʮ����������ʾ�ġ�
	��������������������������
	2.����ѧ�����򣬳���׳�Ի��ܵ��ϴ�Ӱ��
	3. ���Լ���һ���ɼ���Ϊ�ṹ���Ա�������Ͽ���ʵ�����򣬵���Ҫ���������������

*/
//�������Ƚ���ͳ��
int static_List(LinkList head){
    int i=0;
    while(head->next->next){
        i++;
        head=head->next;
    }
    return i;
}
//��������
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
//��ͨѶ¼csv��ʽ������output.csv�ļ�
void output_csv(LinkList head) {
    ofstream p;
    p.open("output.csv",ios::out|ios::trunc);
    p<<"ѧ��"<<","<<"����"<<","<<"�Ա�"<< ","<<"ѧԺ"<<","<<"qq�˻�"<<","<<"��������"<<","<<"ͨѶ��ַ"<<","<<"�绰"<<
     "," <<"ѧ���ɼ�"<<endl;
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
//�������
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

//չʾ������Ա����Ϣ
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
//չʾȫ��������Ϣ
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
//��ȷ����
void find_List(LinkList &head) {
    cout<<"��ѡ����ҷ�ʽ"<<endl;
    cout<<"1.��������"<<"\t";
    cout<<"2.ѧ�Ų���"<<"\t";
    cout<<"3.�������"<<"\t";
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
//ģ������
int blurfind_list(LinkList head) {
    if(head->next->next==NULL) {
        cout<<"sorry,list is empty"<<endl;
        system("pause");
        system("cls");
        return 0;
    }
    cout<<"please input the type of the blur information"<<endl;
    cout<<"1.����"<<endl;
    cout<<"2.ѧ��"<<endl;
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
//ɾ������
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
//���ݳɼ���ѧ����Ϣ��������
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
//����ѧ����Ϣ
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
//������¼�����Ϣ���浽writer.txt�ļ���
void conserve_List(LinkList head) {
    FILE *fp;
    if((fp=fopen("writer.txt","w"))==NULL) {
        printf ("�޷���\n");
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
//��ʾ�˵�
void showMenu() {
    cout<<"1.���ѧ����ϵ��"<<endl;
    cout<<"2.��ʾѧ����ϵ��"<<endl;
    cout<<"3.ɾ��ѧ����ϵ��"<<endl;
    cout<<"4.����ѧ����ϵ��"<<endl;
    cout<<"5.ģ������ѧ����ϵ��"<<endl;
    cout<<"6.�޸�ѧ����ϵ��"<<endl;
    cout<<"7.���ɼ�������ʾ"<<endl;
    cout<<"0.�˳�ͨѶ¼����������"<<endl;
}
//����Vcard��ʽ���ݲ��洢
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
