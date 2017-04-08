/*
�������� 1613�� 20165248 �����
�ù���Ϣ���� Structs.h
���ļ������о����������ͷ�ļ����ṹ�嶨��ͺ�����������Ϣ��
*/

//���������ͷ�ļ����궨��
#include <stdio.h>//��׼�������
#include <stdlib.h>//��׼��
#include <conio.h>//����̨�������
#include <string.h>
#include <time.h>
#include <locale.h>

//�ṹ�嶨��
typedef enum roomType{Single = 1, Double = 2, Triangle = 3}roomType;//ö�ٶ��巿������

struct Rooms
{
	int roomNum;//�����
	int checkinNum;//��ס����
	int roomPrice;//����۸�
	roomType roomtype;//��������
	struct Rooms *next;
};//���淿����Ϣ������
struct Rooms *room_head, *room_tail;

struct Guests
{
	char name[20];//�ÿ�����
	char ID[25];//�ÿ����֤��
	char sex[10];//�ÿ��Ա�
	struct Guests *next;
};//�����ÿ���Ϣ������
struct Guests  *guest_head, *guest_tail;

struct GuestAndRoom
{
	char guestID[20];//�ÿ����֤��
	int guestRoom;//�ÿ���ס�ķ���
	char checkInTime[30];//��סʱ��
	char checkOutTime[30];//�˷�ʱ��
	struct GuestAndRoom *next;
};
struct GuestAndRoom *GAR_head, *GAR_tail;

//mainbody.c��������
void PrintMain();//��ӡ�˵�����
void HandleMain();//����˵�����
void printline();//������
void InitializeLinkedList();//��ʼ������
void ChangeTheme();//���������е�����
void LoadTheme();//��������

//Hotel.c��������
void LoadHotelInfo();//���ļ��ж�ȡ������Ϣ��Rooms������
void SaveHotelInfo();//�����е�Rooms�����е���Ϣ���浽�ļ�
void ViewAllHotel();//�鿴���з�����ס���
void ViewOneRoom();//�鿴ĳ�����ÿ���Ϣ
int ViewAvaRoom();//��ʾ���÷���
void CntCheckinNum();//ͳ�Ƹ���������

//Guest.c��������
void LoadGuestInfo();//���ļ��ж�ȡ�ÿ���Ϣ��Guests������
void SaveGuestInfo();//�����е�Guests�����е���Ϣ���浽�ļ�
void ViewOneGuest();//�鿴ĳ�ÿ���Ϣ
void ViewAllGuest();//�鿴�����ÿ���Ϣ
int IsOldGuest(char ID[]);//�ж��Ƿ�Ϊ�Ϲ˿�
int UnitPrice(int roomChoice);//���ҷ��䵥��

//GAR.c��������
void GuestCheckIn();//�ÿ���ס
void GuestChangeRoom();//�ÿͻ���
void GuestCheckOut();//�ÿ��˷�
void LoadGARInfo();//���ļ���ȡ�ÿ��뷿����Ϣ������GuestAndRoom
void SaveGARInfo();//�ӵ�ǰGuestAndRoom�������ÿ��뷿����Ϣ���ļ�
