/*��дһ���˵������ĳ�����������ĳ��ѧ����������ִ�����²���
a.��ʾ�������������
b.�༭ָ��ѧ������ϸ��Ϣ
c.����������������ѧ��������*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct linked_list//��������
{
	char name[50];
	int age;
	float weight;
	struct linked_list *next;//ָ����һ����ָ��
};
typedef struct linked_list Student;
Student *head,*tail;//����������β

void initialize(void);
void print(Student *stu);
void printAll(void);
void insert(void);
void showMenu(void);
int getChoice(void);
void modify(void);
Student *searchByname(char *);
void countWeight(void);
void countAge(void);

main()
{
	int choice;
	initialize();
	while(1)
	{
		showMenu();
		choice=getChoice();
		switch(choice)
		{
			case 1:
				insert();break;
			case 2:
				printAll();break;
			case 3:
				modify();break;
			case 4:
				countAge();break;
			case 5:
				countWeight();break;
			case 0:
				exit(0);break;
			default:
                break;
		}
	}
}

void showMenu()
{
	printf("\n*******MENU*******\n");
	printf("1.Insert a student\n");
	printf("2.List all students\n");
	printf("3.Modify a student's info\n");
	printf("4.Age statistics\n");
	printf("5.Weight statistics\n");
	printf("0.Quit\n");
	printf("******************\n");
}

int getChoice()
{
	int c;
	printf("Your choice:");
	scanf("%d",&c);
	return c;
}

void initialize()//��ʼ������
{
	head=(Student *)malloc(sizeof(Student));//��̬�����ڴ�
	head->next=NULL;
	tail=head;
}

void print(Student *stu)
{
	printf("\nName:\t%s\nAge:\t%d\nWeight:\t%.2f\n",stu->name,stu->age,stu->weight);
}

void printAll()
{
	Student *cur=head->next;//head���һ��Ԫ��
	while(cur!=NULL)
	{
		print(cur);
		cur=cur->next;
	}
}

void insert()
{
	Student *stu=(Student *)malloc(sizeof(Student));//����һ���µ��ڴ��������ǰ���stu
	printf("Insert a student.\n");
	printf("Please input info of the student:\n");
	printf("Name:");
	scanf("%s",stu->name);
	printf("Age:");
	scanf("%d",&(stu->age));
	printf("Weight:");
	scanf("%f",&(stu->weight));
	tail->next=stu;//����stu���뵽�������
	stu->next=NULL;
	tail=stu;
}

void modify()
{
	char name[50];
	Student *stu;
	printf("Please input the name of the student you want to modify:");
	scanf("%s",name);
	stu=searchByname(name);//����������ѧ��
	if(stu==NULL)//δ�ҵ�ѧ����Ϣ
		printf("%s is not found.\n",name);
	else//�ҵ�ѧ����Ϣ���޸�
	{
		printf("Please input info of the student:\n");
		printf("Name:");
		scanf("%s",stu->name);
		printf("Age:");
		scanf("%d",&(stu->age));
		printf("Weight:");
		scanf("%f",&(stu->weight));
		printf("Modification succeed.\n");
	}
}

Student *searchByname(char *name)
{
	Student *cur=head->next;
	while(cur!=NULL)
	{
		if(strcmp(cur->name,name)==0)//�ҵ����������ѧ��
			break;
		cur=cur->next;//��ǰ��ƥ�䣬��������
	}
	return cur;
}

void countWeight()
{
	Student *cur=head->next;
	int count=0;
	float w;
	printf("Input the weight:");
	scanf("%f",&w);
	while(cur!=NULL)
	{
		if(abs(cur->weight-w)<0.00001)
			count++;
		cur=cur->next;
	}
	printf("Number of students with weight %.2f:%d\n",w,count);
}

void countAge()
{
	Student *cur=head->next;
	int count=0;
	int a;
	printf("Input the age:");
	scanf("%d",&a);
	while(cur!=NULL)
	{
		if(cur->age==a)
			count++;
		cur=cur->next;
	}
	printf("Number of students with age %d:%d\n:",a,count);
}
