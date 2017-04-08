/*MainBody.c*/
#include"Structs.h"
extern int GuestNumber;
int GuestNumber=0;//���е��ÿ���
void main(void)
{
    LoadHotelInfo(rooms);
    LoadGuestInfo();
    LoadGARInfo();
    handlemenu();
}
void printMenu()
{
    printf(
        "1 �鿴�õ���Ϣ\n"
        "2 �鿴ĳһ������Ϣ\n"
        "3 �鿴�ÿ���Ϣ\n"
        "4 ����ĳһ�ÿ���Ϣ\n"
        "5 �ÿ���ס\n"
        "6 �ÿͻ���\n"
        "7 �ÿ��˷�\n"
        "8 �˳�\n"
    );
}
void handlemenu()
{
    int i=0;
    do
    {
        printMenu();
        printf("��ѡ��:");
        scanf("%d",&i);
        fflush(stdin);
        switch(i)
        {
        case 1:
            ViewAllHotel();
            printf("\n\n");
            break;
        case 2:
            ViewOneRoom();
            printf("\n\n");
            break;
        case 3:
            ViewAllGuest();
            printf("\n\n");
            break;
        case 4:
            ViewOneGuest();
            printf("\n\n");
            break;
        case 5:
            GuestCheckIn();
            printf("\n\n");
            break;
        case 6:
            GuestChangeRoom();
            printf("\n\n");
            break;
        case 7:
            GuestCheckOut();
            printf("\n\n");
            break;
        case 8:
        {
            SaveGARInfo();
            SaveGuestInfo();
            SaveHotelInfo(rooms);
            exit(0);
        }
        }
    }
    while(1);
}
/*Structs.c*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#define FLOORNUMBER 4
#define ROOMNUMBER 5
typedef enum RoomType {Single=1,Double=2,Triangle=3} RoomType; //��������
typedef struct room
{
    int RoomNumber;//�����
    RoomType roomtype;//��������
    int CheckInNumber;//��ס����
    int RoomPrice;//����۸�
} Room; //������صĳ�Ա�Ķ���
typedef struct guestandroom
{
    char GuestID[20];//�ÿ����֤��
    int GuestInRoom;//�ÿ���ס�ķ���
    char CheckInTime[30];//ס���ʱ��
    char CheckOutTime[30];//�˷���ʱ��
} GuestAndRoom; //������صĳ�Ա�Ķ���
typedef struct guest
{
    char Name[10];//����
    char sex[3];//�Ա�
    char ID[20];//���֤����
} Guest; //�ÿ͵�������ԵĶ���
void menu();
void LoadHotelInfo(Room pararoom[FLOORNUMBER][]);
void ViewAllHotel();
void SaveHotelInfo(Room pararoom[FLOORNUMBER][]);
void LoadGuestInfo();
void SaveGuestInfo();
void ViewOneGuest();
void ViewAllGuest();
void AppendGuestInfo();
void GuestCheckIn();
void GuestChangeRoom();
void GuestCheckOut();
void ChangeBookDay();
void AppendGARInfo();
void LoadGARInfo();
void SaveGARInfo();
void AppendGuestHistoryInfo(int Guesti,int GARj);
void handlemenu();
void printMenu();
void ViewOneRoom();
int IsOldGuest();
int DelGuest(char ID[]);
int CountGuest(Room pararoom[FLOORNUMBER][]);
int CheckRAGIndex(char ID[]);
int CheckFreeRoom(char Sex[]);
int FindOneGuest();
char *CheckRoomSex(int RoomNumber);
Room rooms[FLOORNUMBER][ROOMNUMBER];//�淿����Ϣ�Ľṹ����
Guest ptoguest[55];//���ÿ���Ϣ������
GuestAndRoom GAR[55];//���ÿ���ס���������
/*GAR.c*/
#include"Structs.h"
extern int GuestNumber;
//��gusetandroom�ļ��������Ϣ
void AppendGARInfo()
{
    FILE *fp;
    if((fp=fopen("guestandroom.txt","a"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fprintf(fp,"%d\t%s\t\t%s\n",GAR[GuestNumber-1].GuestInRoom,GAR[GuestNumber-1].GuestID,GAR[GuestNumber-1].CheckInTime);
    fclose(fp);
}
//��ʼ��GAR����
void LoadGARInfo()
{
    /*��̬�����洢�ÿ���Ϣ������*/
    FILE *fp;
    int iCount=0;
    char temp[10]="";
    if((fp=fopen("guestandroom.txt","r"))==NULL)
    {
        printf("�ļ���ȡʧ��!\n");
        exit(0);
    }
    fscanf(fp,"%*s %*s %*s %*s",temp,temp,temp,temp);
    for(iCount=0; iCount<GuestNumber; iCount++)
    {
        fscanf(fp,"%d %s\t\t\t",&GAR[iCount].GuestInRoom,GAR[iCount].GuestID);
        fgets(GAR[iCount].CheckInTime,25,fp);
        strcpy(GAR[iCount].CheckOutTime," ");
    }
    fclose(fp);
}
void SaveGARInfo()
{
    FILE *fp;
    int iCount=0;
    if((fp=fopen("guestandroom.txt","w"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fprintf(fp,"%s\t%s\t%s\t%s\n","����","���֤","��סʱ��","�˷�ʱ��");
    for(iCount=0; iCount<GuestNumber; iCount++)
        fprintf(fp,"%d\t\t%s\t\t\t%s\t\t\t%s\n",GAR[iCount].GuestInRoom,GAR[iCount].GuestID,GAR[iCount].CheckInTime,GAR[iCount].CheckOutTime);
    fclose(fp);
}
//��������ID��RAG�����λ��
int CheckRAGIndex(char ID[])
{
    int gindex=-1;
    int garindex=-1;
    int icount;
    for(icount=0; icount<GuestNumber; icount++)
    {
        if(!strcmp(ID,ptoguest[icount].ID))
        {
            gindex=icount;
            break;
        }
    }
    if(gindex!=-1) //�����
    {
        for(icount=0; icount<GuestNumber; icount++)
        {
            if(!strcmp(ptoguest[gindex].ID,GAR[icount].GuestID))
            {
                garindex=gindex;
                break;
            }
        }
    }
    return garindex;
}
//�ÿ���ס
void GuestCheckIn()
{
    int NewRoomNumber;
    int NewGuestSexN;
    int i;
    int j;
    int CheckSex=0;
    time_t t;
    t=time(NULL);
    printf("�������ÿ�����:\n");
    scanf("%s",ptoguest[GuestNumber].Name);
    do
    {
        printf("��ѡ���ÿ��Ա�:\n");
        printf("1 ��\n2 Ů\n");
        scanf("%d",&NewGuestSexN);
        switch(NewGuestSexN)
        {
        case 1:
            strcpy(ptoguest[GuestNumber].sex,"��");
            break;
        case 2:
            strcpy(ptoguest[GuestNumber].sex,"Ů");
            break;
        }
    }
    while(NewGuestSexN!=1&&NewGuestSexN!=2);
    printf("�������ÿ����֤����:\n");
    scanf("%s",ptoguest[GuestNumber].ID);
    CheckSex=CheckFreeRoom(ptoguest[GuestNumber].sex);
    if(!CheckSex)
    {
//��������
        strcpy(ptoguest[GuestNumber].ID,"");
        strcpy(ptoguest[GuestNumber].Name,"");
        strcpy(ptoguest[GuestNumber].sex,"");
        return;
    }
    printf("�������ÿ�ѡ����ס�������:\n");
    scanf("%d",&NewRoomNumber);//��α�֤ѡ������ȷ����
//���ķ���״̬,�·���
    for(i=0; i<4; i++)
    {
        for(j=0; j<5; j++)
        {
            if(rooms[i][j].RoomNumber==NewRoomNumber)
            {
                rooms[i][j].CheckInNumber=rooms[i][j].CheckInNumber+1;
            }
        }
    }
    GuestNumber+=1;//��������
    strcpy(GAR[GuestNumber-1].CheckInTime,ctime(&t));
    printf("��סʱ��Ϊ%s\n",GAR[GuestNumber-1].CheckInTime);
    strcpy(GAR[GuestNumber-1].GuestID,ptoguest[GuestNumber-1].ID);
    GAR[GuestNumber-1].GuestInRoom=NewRoomNumber;
//����Ϣ��ӵ��ļ���
    AppendGuestInfo();
    AppendGARInfo();
    SaveHotelInfo(rooms);
}
//�ÿ��˷�
void GuestCheckOut()
{
    float discount=0,money=0;
    int Days=0,i;
    char ID[20]="";
    do
    {
        printf("�������ÿ����֤:");
        scanf("%s",ID);
        for(i=0; i<=GuestNumber-1; i++)
        {
            if(!strcmp(ID,ptoguest[i].ID))
            {
                break;
            }
        }
        if(i==GuestNumber)
        {
            printf("��������û������ڣ�");
            i=-1;
        }
    }
    while(i==-1);
    discount=(IsOldGuest(ID)<=2)?1:(IsOldGuest(ID)<=4)?0.9:(IsOldGuest(ID)<=6)?0.8:0.7;
    printf("��λ�˿ʹ˴�Ϊ��%d��ס��,������Ϊ:%f\n",IsOldGuest(ID)+1,discount);
    money=(float)DelGuest(ID);
    printf("��������ס����:\n");
    scanf("%d",&Days);
    money=money*Days*discount;
    printf("Ӧ�ø�%fԪ.\n",money);
    SaveGARInfo();
    SaveGuestInfo();
    SaveHotelInfo(rooms);
}
//�ÿͻ���
//�ÿͻ�����ֻ�ܻ����շ������ˣ�
void GuestChangeRoom()
{
    char name[10]="";
    char ID[19]="";
    int RAGindex=-1;
    int GuestIndex=-1;
    char choice='\0';
    int day=0;
    int i=0,j=0;
    int sum=0;
    int roomnumber=0;
//�����ÿ���Ϣ
    printf("�������ÿ͵�����:\n");
    gets(name);
//�ҵ��ÿ����ÿͽṹ���е��±�
    printf("��������Ҫ�������ÿ͵����֤��\n");
    gets(ID);
    RAGindex=CheckRAGIndex(ID);
    for(i=0; i<=GuestNumber; i++)
    {
        if(!strcmp(ID,ptoguest[i].ID))   //Ҫ����ͬ���ľ��鷳��
        {
            printf("���ÿ͵���Ϣ����\n"
                   "����\t�Ա�\t��ס�ķ���\t��ס��ʱ��\n");
            printf("%s\t%s\t%d\t%s\n",ptoguest[i].Name,ptoguest[i].sex,GAR[RAGindex].GuestInRoom,GAR[RAGindex].CheckInTime);
            GuestIndex=i;
            break;
        }
    }
    printf("ȷ��������Ϣ��(y/n)\n");
    choice=getchar();
    if(choice=='N'||choice=='n')
    {
        return;
    }
//����
    printf("��������ÿ͵���ס������\n");
    scanf("%d",&day);
    for(i=0; i<FLOORNUMBER; i++)
    {
        for(j=0; j<ROOMNUMBER; j++)
        {
            if(rooms[i][j].RoomNumber==GAR[RAGindex].GuestInRoom)
            {
                sum=day*rooms[i][j].RoomPrice;
                break;
            }
        }
        if(sum)
        {
            break;
        }
    }
    printf("���ÿͽ���ǰ��ķ���%d.\n",sum);
//��ӡ�ܻ���ķ���
    CheckRAGIndex(ptoguest[GuestIndex].sex);
    printf("������Ҫ����ķ���ţ�\n");
    scanf("%d",&roomnumber);
//����
    if(roomnumber==GAR[RAGindex].GuestInRoom)
    {
        printf("���ܻ���ԭ����");
        return;
    }
//״̬����
//ԭ����
    GAR[RAGindex].GuestInRoom=roomnumber;
    rooms[i][j].CheckInNumber--;
    for(i=0; i<FLOORNUMBER; i++)
        for(j=0; j<ROOMNUMBER; j++)
        {
            if(rooms[i][j].RoomNumber==roomnumber)
            {
                rooms[i][j].CheckInNumber++;
                break;
            }
        }
    SaveGARInfo();
    SaveGuestInfo();
    SaveHotelInfo(rooms);
}
Guests.c:
#include"Structs.h"
extern int GuestNumber;
//����ÿ���Ϣ
void AppendGuestInfo()
{
    FILE *fp;
    if((fp=fopen("guest.txt","a"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fprintf(fp,"%s\t%s\t%s\t\n",ptoguest[GuestNumber-1].Name,ptoguest[GuestNumber-1].sex,ptoguest[GuestNumber-1].ID);
    fclose(fp);
}
int CountGuest(Room pararoom[FLOORNUMBER][ROOMNUMBER])
{
    int iFloor=0;
    int jRoom=0;
    int sum=0;
    for(iFloor=0; iFloor<FLOORNUMBER; iFloor++)
        for(jRoom=0; jRoom<ROOMNUMBER; jRoom++)
        {
            if(pararoom[iFloor][jRoom].CheckInNumber>0)
            {
                sum+=pararoom[iFloor][jRoom].CheckInNumber;
            }
        }
    return sum;
}
//���������Ϣ
void LoadGuestInfo()
{
    FILE *fp;
    int iCount=0;
    char temp[10]="";
    if((fp=fopen("guest.txt","r"))==NULL)
    {
        printf("�ļ���ȡʧ��!\n");
        exit(0);
    }
    GuestNumber=CountGuest(rooms);

    fscanf(fp,"%*s %*s %*s",temp,temp,temp);
    for(iCount=0; iCount<GuestNumber; iCount++)
    {
        fscanf(fp,"%s\t%s\t%s",ptoguest[iCount].Name,ptoguest[iCount].sex,ptoguest[iCount].ID);
//strcpy(GAR[iCount].GuestID,ptoguest[iCount].ID);
    }
    fclose(fp);
}
//�����ÿ���Ϣ
void SaveGuestInfo()
{
    FILE *fp;
    int iCount=0;
    if((fp=fopen("guest.txt","w"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fprintf(fp,"%s\t%s\t%s\n","����","�Ա�","���֤");
    for(iCount=0; iCount<GuestNumber; iCount++)
        fprintf(fp,"%s\t%s\t%s\n",ptoguest[iCount].Name,ptoguest[iCount].sex,ptoguest[iCount].ID);
    fclose(fp);
}
//�����ÿ���Ϣ
void ViewOneGuest()
{
    int i=FindOneGuest();
    int GARNUM;
    if(i!=-1)
    {
        GARNUM=CheckRAGIndex(ptoguest[i].ID);
        printf("����\t�Ա�\t���֤\t\t����\t��סʱ��\n");
        printf("%s\t%s\t%s\t\t%d\t%s\t\n",ptoguest[i].Name,ptoguest[i].sex,ptoguest[i].ID,GAR[GARNUM].GuestInRoom,GAR[GARNUM].CheckInTime);
        return;
    }
    else
    {
        printf("û�д��û���Ϣ��\n");
        return;
    }
}
//�����ÿ���Ϣ��������һ������
int FindOneGuest()
{
    int i;
    char GuestID[25];
    printf("\n�������ÿ͵����֤:\n");
    scanf("%s",GuestID);
    fflush(stdin);
    for(i=0; i<GuestNumber; i++)
    {
        if(!strcmp(GuestID,ptoguest[i].ID))
        {
            return i;
        }
    }
    printf("û�д����˿ͣ�");
    return -1;
}
//�鿴�����ÿ͵���Ϣ
void ViewAllGuest()
{
    int i=0;
    int GARNUM;
    printf("---------�����ÿ���Ϣ------------\n");
    printf("����\t�Ա�\t���֤\t����\t��סʱ��\n");
    for(i=0; i<GuestNumber; i++)
    {
        GARNUM=CheckRAGIndex(ptoguest[i].ID);//���±�
        printf("%s\t%s\t%s\t%d\t%s\t\n",ptoguest[i].Name,ptoguest[i].sex,ptoguest[i].ID,GAR[GARNUM].GuestInRoom,GAR[GARNUM].CheckInTime);
    }
    printf("��ӡ����!\n");
}
//�ж��Ƿ�����ǰ���ÿ�
int IsOldGuest(char NewID[])
{
    FILE *fp;
    char temp[20]="";
    char name[10]="";
    char ID[20]="";
    int Room=0;
    char CheckInTime[30]="";
    char CheckOutTime[30]="";
    int a=0;
    if((fp=fopen("guesthistory.txt","r"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fscanf(fp,"%*s %*s %*s %*s %*s",temp,temp,temp,temp,temp);
    while(!feof(fp))
    {
        fscanf(fp,"%s %s %d %s %s",name,ID,&Room,CheckInTime,CheckOutTime);
        if(!strcmp(NewID,ID))
        {
            a++;
        }
    }
    return a;
}
//����µ���ʷ��¼
void AppendGuestHistoryInfo(int Guesti,int GARj)
{
    FILE *fp;
    if((fp=fopen("guesthistory.txt","a"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fprintf(fp,"%s\t%s\t%d\t\t\t%s\t\t\t%s\n",ptoguest[Guesti].Name,ptoguest[Guesti].ID,GAR[GARj].GuestInRoom,GAR[GARj].CheckInTime,GAR[GARj].CheckOutTime);
}
//��ӡ��ס��¼
void ViewOldGuest()
{
    FILE *fp;
    char name[10];
    int ID;
    int Room;
    char CheckInTime[30];
    char CheckOutTime[30];
    if((fp=fopen("guesthistory.txt","r"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    printf("����\t\t ���֤\t\t �����\t\t ��סʱ��\t\t �˷�ʱ��\t\t\n");
    do
    {
        fscanf(fp,"%s %d %d %s %s\n",name,&ID,&Room,CheckInTime,CheckOutTime);
        printf("%s\t\t %d\t\t %d\t\t %s\t\t %s\t\t\n",name,ID,Room,CheckInTime,CheckOutTime);
    }
    while(!feof(fp));
}
//ɾ��Guest�����е�һ����Ϣ,ͬʱɾ����Ӧ��GAR
int DelGuest(char ID[])
{
    int i=0,j=0,GARj=0,roomi=0,roomj=0;
    int money=0;
    int out=1;
    time_t t;
    t=time(NULL);
    for(i=0; i<GuestNumber; i++)
    {
        if(!strcmp(ID,ptoguest[i].ID))
        {
            GARj=CheckRAGIndex(ptoguest[i].ID);
            printf("���ʱ��Ϊ%s\n",GAR[GARj].CheckInTime);
            strcpy(GAR[GARj].CheckOutTime,ctime(&t));
            printf("�˵�ʱ��Ϊ%s\n",GAR[GARj].CheckOutTime);
            for(roomi=0; roomi<4&&out; roomi++)
            {
                for(roomj=0; roomj<5; roomj++)
                {
                    if(GAR[GARj].GuestInRoom==rooms[roomi][roomj].RoomNumber)
                    {
                        money=rooms[roomi][roomj].RoomPrice;
                        rooms[roomi][roomj].CheckInNumber=rooms[roomi][roomj].CheckInNumber-1;
                        SaveHotelInfo(rooms);
                        out=0;
                        break;
                    }
                }
            }
            AppendGuestHistoryInfo(i,GARj);
            GuestNumber=GuestNumber-1;
            for(j=i; j<GuestNumber; j++)
            {
                ptoguest[j]=ptoguest[j+1];
            }
            for(j=GARj; j<GuestNumber; j++)
            {
                GAR[j]=GAR[j+1];
            }
            break;
        }
    }
    return money;
}
Hotels.c:
#include"Structs.h"
extern int GuestNumber;
//��鷿��Ӧס���Ա�
char *CheckRoomSex(int RoomNumber)
{
    int i,j;
    for(i=0; i<GuestNumber; i++) //�����������GuestNumber{
        if(RoomNumber==GAR[i].GuestInRoom) //�õ������������������±�
        {
            for(j=0; j<GuestNumber; j++)
            {
                if(!strcmp(GAR[i].GuestID,ptoguest[j].ID))//�ҵ���Ӧ�Ŀ���
                    return ptoguest[j].sex;
            }
            break;
        }
}
return NULL;
}
//���շ�
int CheckFreeRoom(char Sex[])
{
    int i,j,find=0;
    char roomsex[3];
    printf("����ס�ķ���:\n");
    for(i=0; i<4; i++)
    {
        for(j=0; j<5; j++)
        {
            if(!rooms[i][j].CheckInNumber) //����Ϊ��
            {
                printf("%d\t",rooms[i][j].RoomNumber);
                find=1;
            }
            else //��������
            {
                strcpy(roomsex,CheckRoomSex(rooms[i][j].RoomNumber));
                if((
                            rooms[i][j].roomtype>rooms[i][j].CheckInNumber
//��ס���������ڷ�������
                            && (strcmp(Sex,roomsex)==0)//��ס������ͬ�Ա���
                        )
                  )
                {
                    printf("%d\t",rooms[i][j].RoomNumber);
                    find=1;
                }
                else
                {
                    printf("\t");
                }
            }
        }
        printf("\n");
    }
    if(!find)
    {
        printf("û�к��ʷ���!\n��������.\n");
    }
    return find;
}
//�������з�����ס�����Ϣ
void LoadHotelInfo(Room innerroom[FLOORNUMBER][ROOMNUMBER])
{
    FILE *fp;
    int iFloor=0;
    int jRoom=0;
    char temp[9];
    if((fp=fopen("hotel.txt","r"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fscanf(fp,"%*s %*s %*s %*s\n",temp,temp,temp,temp);
    for(iFloor=0; iFloor<FLOORNUMBER; iFloor++)
        for(jRoom=0; jRoom<ROOMNUMBER; jRoom++)
        {
            fscanf(fp,"%d %d %d
                   %d\n",&innerroom[iFloor][jRoom].RoomNumber,&innerroom[iFloor][jRoom].roomtype,&innerroom[iFloor][jRoom].CheckInNumber,&innerroom[iFloor][jRoom].RoomPrice);
        }
    fclose(fp);
}
//��ӡ���з�����ס���
void ViewAllHotel()
{
    int i,j;
    printf("�������\t��������\t��ס����\t ����۸�\t\n");
    for(i=0; i<4; i++)
    {
        for(j=0; j<5; j++)
        {
            printf(" %d\t\t",rooms[i][j].RoomNumber);
            switch(rooms[i][j].roomtype)
            {
            case 1:
                printf(" ���˷�\t\t ");
                break;
            case 2:
                printf(" ˫�˷�\t\t ");
                break;
            case 3:
                printf(" ���˷�\t\t ");
                break;
            }
            printf("%d\t\t%d\t\t\n",rooms[i][j].CheckInNumber,rooms[i][j].RoomPrice);
        }
        printf("\n");
    }
}
//�������з�����Ϣ
void SaveHotelInfo(Room pararoom[FLOORNUMBER][ROOMNUMBER])
{
    FILE *fp;
    int iFloor=0;
    int jRoom=0;
    if((fp=fopen("hotel.txt","w"))==NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    fprintf(fp,"�����\t��������\t��ס����\t����۸�\t\n");
    for(iFloor=0; iFloor<FLOORNUMBER; iFloor++)
    {
        for(jRoom=0; jRoom<ROOMNUMBER; jRoom++)
        {
            fprintf(fp," %d\t\t%d\t\t%d\t\t\t%d\t\n",pararoom[iFloor][jRoom].RoomNumber,pararoom[iFloor][jRoom].roomtype,pararoom[iFloor][jRoom].CheckInNumber,pararoom[iFloor][jRoom].RoomPrice);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
//��ӡĳһ�������
void ViewOneRoom()
{
    int RoomNum,i,j,IsNull=0;
    printf("�����뷿����룺");
    scanf("%d",&RoomNum);
    for(i=0; i<GuestNumber; i++)
    {
        if(RoomNum==GAR[i].GuestInRoom)
        {
            for(j=0; j<GuestNumber; j++)
            {
                if(strcmp(ptoguest[j].ID,GAR[i].GuestID)==0)
                {
                    printf("����:%s\t���֤:%s\t�Ա�:%s\t��סʱ��:%s\n",ptoguest[j].Name,ptoguest[j].ID,ptoguest[j].sex,GAR[i].CheckInTime);
                    IsNull=1;
                }
            }
        }
    }
    if(!IsNull)
    {
        printf("����Ϊ�գ�\n");
    }
}
