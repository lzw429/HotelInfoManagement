/*
�ù���Ϣ���� Hotel.c
*/

#include"Structs.h"

void LoadHotelInfo()//���ļ��ж�ȡ������Ϣ��Rooms������
{
	FILE* fp;
	char title[30] = "";
	if ((fp = fopen("Hotel.txt", "r")) == NULL)
	{
		printf("�ļ���ȡʧ��");
		exit(0);
	}
	fscanf(fp, "%s %s %s\n", title, title, title);
	while (!feof(fp))
	{
		struct Rooms* insert = (struct Rooms *)malloc(sizeof(struct Rooms));
		fscanf(fp, "%d%d%d\n", &insert->roomNum, &insert->roomtype, &insert->roomPrice);
		//ͨ������GuestAndRoom�����ȡÿ�����������
		insert->checkinNum = 0;
		struct GuestAndRoom* GAR_cur = GAR_head->next;;
		while (GAR_cur != NULL)
		{
			if (GAR_cur->guestRoom == insert->roomNum)
				insert->checkinNum++;
			GAR_cur = GAR_cur->next;
		}
		room_tail->next = insert;
		insert->next = NULL;
		room_tail = insert;
	}
	fclose(fp);
}

void SaveHotelInfo()//�����е�Rooms�����е���Ϣ���浽�ļ�
{
	FILE* fp;
	if ((fp = fopen("Hotel.txt", "w")) == NULL)
	{
		printf("�ļ���ȡʧ��");
		exit(0);
	}
	fprintf(fp, "����� �������� ����۸�");
	struct Rooms* cur = room_head->next;
	while (cur != NULL)
	{
		fprintf(fp, "\n%d %d %d", cur->roomNum, cur->roomtype, cur->roomPrice);
		cur = cur->next;
	}
	fclose(fp);
}

void ViewAllHotel()//�鿴���з�����ס���
{
	printf("�����\t��������\t��ס����\t����۸�\t\n");
	struct Rooms* cur = room_head->next;//����Rooms����
	while (cur != NULL)
	{
		struct GuestAndRoom* GAR_cur = GAR_head->next;
		cur->checkinNum = 0;
		while (GAR_cur != NULL)
		{
			if (GAR_cur->guestRoom == cur->roomNum)
				cur->checkinNum++;
			GAR_cur = GAR_cur->next;
		}
		printf("%d\t", cur->roomNum);
		switch (cur->roomtype)
		{
		case 1:
			printf("���˷�\t");
			break;
		case 2:
			printf("˫�˷�\t");
			break;
		case 3:
			printf("���˷�\t");
			break;
		}
		printf("\t%d\t\t%d\n", cur->checkinNum, cur->roomPrice);
		cur = cur->next;
	}
	printf("\n");
}

void ViewOneRoom()//�鿴ĳ�����ÿ���Ϣ
{
	int roomchoice;
	int findRoom = 0;//�жϷ����Ƿ����
	int flag = 0;//�ÿ���Ϣ������Ϊ1�����ÿ���Ϣ���Ϊ0
	printf("�����뷿��ţ�");
	scanf("%d", &roomchoice);
	struct GuestAndRoom* GAR_cur = GAR_head->next;
	while (GAR_cur != NULL)
	{
		if (GAR_cur->guestRoom == roomchoice)//ͨ���������GAR�������ҵ���סʱ������֤
		{
			struct Guests* guest_cur = guest_head->next;
			while (guest_cur != NULL)
			{
				if (strcmp(guest_cur->ID, GAR_cur->guestID) == 0)//ͨ�����֤�ҵ�Guests�����е��������Ա�
				{
					printf("����:%s ���֤:%s �Ա�:%s ��סʱ��:%s\n", guest_cur->name, guest_cur->ID, guest_cur->sex, GAR_cur->checkInTime);
					flag = 1; 
					findRoom = 1;
				}
				guest_cur = guest_cur->next;
			}
		}
		GAR_cur = GAR_cur->next;
	}
	if (!flag)
	{
		struct Rooms* room_cur = room_head->next;
		while(room_cur!=NULL)
		{
			if (room_cur->roomNum == roomchoice && room_cur->checkinNum == 0)
			{
				printline();
				printf("�÷������.\n");
				findRoom = 1;
				break;
			}
			room_cur = room_cur->next;
		}
	}
	if(!findRoom)
	{
		printf("��������ȷ�ķ���ţ�\n");
		ViewOneRoom();
	}
}

void CntCheckinNum()//ͳ�Ƹ���������
{
	struct Rooms* cur = room_head->next;//����Rooms����
	while (cur != NULL)
	{
		struct GuestAndRoom* GAR_cur = GAR_head->next;
		cur->checkinNum = 0;
		while (GAR_cur != NULL)
		{
			if (GAR_cur->guestRoom == cur->roomNum)
				cur->checkinNum++;
			GAR_cur = GAR_cur->next;
		}
		cur = cur->next;
	}
}

int ViewAvaRoom()//��ʾ���÷���
{
	CntCheckinNum();
	FILE* fp;
	char title[10] = {0};
	int roomNum = 0;
	int roomtype = 0;
	int roomPrice = 0;
	int flag = 0;
	if ((fp = fopen("Hotel.txt", "r")) == NULL)
	{
		printf("������Ϣ��ȡʧ��.");
		exit(0);
	}
	fscanf(fp, "%s %s %s", title, title, title);
	printf("����ס�ķ��䣺\n");
	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &roomNum, &roomtype, &roomPrice);
		struct Rooms* cur = room_head->next;//����Rooms����
		while (cur != NULL)
		{
			if (roomNum == cur->roomNum && roomtype > (cur->checkinNum))
			{
				printf("����ţ�%d �������ͣ�", roomNum);
				switch (cur->roomtype)
				{
				case 1:
					printf("���˷� ");
					break;
				case 2:
					printf("˫�˷� ");
					break;
				case 3:
					printf("���˷� ");
					break;
				}
				printf("����۸�%d\t", cur->roomPrice);
				if (cur->checkinNum != 0)
					printf("��������ס\n");
				else
					printf("����\n");
				flag = 1;
			}
			cur = cur->next;
		}
	}
	if (!flag)
	{
		printf("��Ǹ���ù����޿��÷��䣬��ӭ�´ι��٣�\n");
		return 0;//�޿��÷���
	}
	else return 1;//�п��÷���
}
