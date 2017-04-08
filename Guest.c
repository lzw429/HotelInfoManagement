/*
�ù���Ϣ���� Guests.c
*/

#include"Structs.h"

extern int guestNum;

void LoadGuestInfo()//���ļ��е��ÿ���Ϣ���뵽Guests�ṹ��������
{
	FILE* fp;
	char title[20] = "";
	if ((fp = fopen("Guest.txt", "r")) == NULL)
	{
		printf("�ļ���ȡʧ��");
		exit(0);
	}
	fscanf(fp, "%s %s %s", title, title, title);
	while (!feof(fp))//EOF֮ǰ���ؼ٣�ֱ��EOF������
	{
		struct Guests* insert = (struct Guests *)malloc(sizeof(struct Guests));//ÿ�β�����Ϣ����������Ҫ�����µ��ڴ档
		fscanf(fp, "%s %s %s", insert->name, insert->sex, insert->ID);
		guest_tail->next = insert;
		insert->next = NULL;
		guest_tail = insert;
	}
	//�����ļ��д洢���ÿ�����
	struct Guests* cur = guest_head->next;
	while (cur != NULL)
	{
		guestNum++;
		cur = cur->next;
	}
	fclose(fp);
}

void SaveGuestInfo(int LocalGuestNum)//Guests�ṹ�������е���Ϣ���浽�ļ�
{
	FILE* fp;
	if ((fp = fopen("Guest.txt", "w")) == NULL)
	{
		printf("�ļ���ȡʧ��");
		exit(0);
	}
	fprintf(fp, "%s %s %s", "����", "�Ա�", "���֤");
	struct Guests* cur = guest_head->next;
	while (cur != NULL)
	{
		fprintf(fp, "\n%s %s %s", cur->name, cur->sex, cur->ID);
		cur = cur->next;
	}
	fclose(fp);
}

void ViewOneGuest()//�鿴ĳ�ÿ���Ϣ
{
	char IDchoice[25];
	int flag = 0;//�ҵ�Ϊ1��δ�ҵ�Ϊ0
	struct Guests* cur = guest_head->next;
	printf("�������ÿ����֤��:");
	scanf("%s", &IDchoice);
	while (cur != NULL)
	{
		if (strcmp(cur->ID, IDchoice) == 0)//ͨ�����֤����Guests�������ҵ��ÿ��������Ա�
		{
			struct GuestAndRoom* GAR_cur = GAR_head->next;
			while (GAR_cur != NULL)
			{
				if (strcmp(GAR_cur->guestID, IDchoice) == 0)//ͨ�����֤����GuestAndRoom�������ҵ�����š���סʱ��
				{
					flag = 1;
					printf("����\t�Ա�\t���֤\t\t\t����\t��סʱ��");
					printf("\n%s\t%s\t%s\t%d\t%s\t", cur->name, cur->sex, IDchoice, GAR_cur->guestRoom, GAR_cur->checkInTime);
					break;
				}
				GAR_cur = GAR_cur->next;
			}
			break;
		}
		cur = cur->next;
	}
	if (!flag)
	{
		printline();
		printf("δ�ҵ����ÿ�.");
	}
}

void ViewAllGuest()//�鿴�����ÿ���Ϣ
{
	printline();
	printf("-----------------------------����%d���ÿ�----------------------------\n", guestNum);
	printf("----------------------------�����ÿ���Ϣ----------------------------\n");
	printf("����\t�Ա�\t���֤\t\t\t����\t��סʱ��");
	struct Guests* cur = guest_head->next;//����Guest��������ÿ���Ϣ��
	while (cur != NULL)
	{
		struct GuestAndRoom* GAR_cur = GAR_head->next;
		int guestRoom = 0;
		char checkInTime[30] = {0};
		while (GAR_cur != NULL)//�����ÿ���Ϣ��ͨ�������������GuestAndRoom�����в�ѯ����ź���סʱ��
		{
			if (strcmp(GAR_cur->guestID, cur->ID) == 0)//�ַ�������ֱ����==�Ƚϣ�����ʹ��strcmp����
			{
				guestRoom = GAR_cur->guestRoom;
				strcpy(checkInTime, GAR_cur->checkInTime);
			}
			GAR_cur = GAR_cur->next;
		}
		printf("\n%s\t%s\t%s\t%d\t%s", cur->name, cur->sex, cur->ID, guestRoom, checkInTime);
		cur = cur->next;
	}
	printf("\n--------------------------------��----------------------------------");
}

int IsOldGuest(char IDtar[])//�ж��Ƿ�Ϊ�Ϲ˿�
{
	//�β�char IDtar[]��Ҫ���ҵ����֤��
	FILE* fp;
	char title[30] = {0};
	char name[20] = {0};
	char ID[25] = {0};
	int roomNum;
	char checkTime[60] = {0};
	int historyTimes = 0;//��ʷ��ס����
	if ((fp = fopen("GuestHistoryInfo.txt", "r")) == NULL)
	{
		printf("�ÿ���ʷ��Ϣ�޷���ȡ.");
		exit(0);
	}
	fscanf(fp, "%s%s%s%s%s", title, title, title, title, title);//���� ���֤ ����� ��סʱ�� �˷�ʱ��
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d ", name, ID, &roomNum);//ע�����͵�ȡ��ַ
		fgets(checkTime, 51, fp);
		if (strcmp(IDtar, ID) == 0)//�ȶ����֤��
			historyTimes++;
	}
	fclose(fp);
	return historyTimes;
}

int UnitPrice(int roomChoice)//���ҷ��䵥��
{
	FILE* fp;
	if ((fp = fopen("Hotel.txt", "r")) == NULL)
	{
		printf("������Ϣ��ȡʧ��.");
		exit(0);
	}
	char title[30] = {0};
	int roomNum = 0;
	int roomtype = 0;
	int roomPrice = 0;

	fscanf(fp, "%s%s%s", title, title, title);
	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &roomNum, &roomtype, &roomPrice);
		if (roomChoice == roomNum)
			return roomPrice;
	}
	fclose(fp);
	return 0;
}
