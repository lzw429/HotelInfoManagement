/*
�ù���Ϣ���� mainbody.c
1.	Ҫ��ʵ���ÿ͵���ס���������˷���
	�鿴�ÿͺͷ�����Ϣ��
	�Լ����ļ���ȡ�����Ϣ���������Ϣ���浽�ļ��Ĺ��ܣ��Ӷ�ʵ���ù���Ϣ����Ļ������ܡ�
2.	Ҫ���������ṹ��ֱ�洢�ÿͺͷ������Ϣ����һ��ö�����Ͷ��巿������͡�
3.	ʹ�ýṹ������ʵ���ÿ���ס���������˷�������Ϊ��
4.	�ܽ��ļ��е���Ϣ�����ṹ���У��ܽ��ṹ�����Ϣ���浽�ļ��С�
*/

#include "Structs.h"

extern int guestNum = 0;//��ס�ÿ��� ȫ�����ͱ�������

void main()
{
	InitializeLinkedList();//��ʼ������
	LoadTheme();//��������
	LoadGuestInfo();
	LoadGARInfo();
	LoadHotelInfo();//���ļ��ж�ȡ������Ϣ��Rooms������
	HandleMain();
}

//��������
void PrintMain()
{
	printf("********************\n");
	printf("1 �鿴�õ���Ϣ\n");
	printf("2 �鿴ĳһ������Ϣ\n");
	printf("3 �鿴�ÿ���Ϣ\n");
	printf("4 ����ĳһ�ÿ���Ϣ\n");
	printf("5 �ÿ���ס\n");
	printf("6 �ÿͻ���\n");
	printf("7 �ÿ��˷�\n");
	printf("8 ������Ϣ���˳�\n");
	printf("9 ��������\n");
	printf("********************\n");
}

void printline()
{
	printf("\n\n");
}

void HandleMain()
{
	while (1)
	{
		PrintMain();
		int choice = 0;
		scanf("%d", &choice);
		fflush(stdin);//�����д������
		if (choice <= 9 && choice >= 1)
		{
			switch (choice)
			{
			case 1: //�鿴�õ���Ϣ
				printline();
				ViewAllHotel();
				printline();
				break;
			case 2: //�鿴ĳһ������Ϣ
				printline();
				ViewOneRoom();
				printline();
				break;
			case 3: //�鿴�ÿ���Ϣ
				ViewAllGuest();
				printline();
				break;
			case 4: //����ĳһ�ÿ���Ϣ
				printline();
				ViewOneGuest();
				printline();
				break;
			case 5: //�ÿ���ס
				printline();
				GuestCheckIn();
				printline();
				break;
			case 6: //�ÿͻ���
				GuestChangeRoom();
				printline();
				break;
			case 7: //�ÿ��˷�
				GuestCheckOut();
				printline();
				break;
			case 8: //������Ϣ���˳�
				SaveGARInfo();
				SaveGuestInfo();
				SaveHotelInfo();
				exit(0);
			case 9:
				ChangeTheme();
				break;
			default:
				break;
			}
		}
		else
		{
			printline();
			continue;
		}
	}
}

void InitializeLinkedList()//��ʼ������
{
	guest_head = (struct Guests *)malloc(sizeof(struct Guests));
	guest_head->next = NULL;
	guest_tail = guest_head;

	room_head = (struct Rooms *)malloc(sizeof(struct Rooms));
	room_head->next = NULL;
	room_tail = room_head;

	GAR_head = (struct GuestAndRoom *)malloc(sizeof(struct GuestAndRoom));
	GAR_head->next = NULL;
	GAR_tail = GAR_head;
}

void ChangeTheme()
{
	int choice = 0;

	printf("********************\n");
	printf("1.��ɫ����\n");
	printf("2.��ɫ����\n");
	printf("3.��ɫ����\n");
	printf("4.����ɫ����\n");
	printf("5.��ɫ����\n");
	printf("6.��ɫ����\n");
	printf("7.��ɫ����\n");
	printf("8.��ɫ����\n");
	printf("9.��ɫ����\n");
	printf("********************\n");

	while (1)
	{
		scanf("%d", &choice);
		if (choice >= 1 && choice <= 9)
			break;
	}

	FILE* fp;
	if ((fp = fopen("Theme.txt", "w")) == NULL)
	{
		printf("������Ϣ��ȡʧ��\n");
		exit(0);
	}

	switch (choice)
	{
	default: break;
	case 1:
		system("color 0F");
		fprintf(fp, "%s", "0F");
		break;
	case 2:
		system("color 1F");
		fprintf(fp, "%s", "1F");
		break;
	case 3:
		system("color 2F");
		fprintf(fp, "%s", "2F");
		break;;
	case 4:
		system("color 3F");
		fprintf(fp, "%s", "3F");
		break;
	case 5:
		system("color 4F");
		fprintf(fp, "%s", "4F");
		break;
	case 6:
		system("color 5F");
		fprintf(fp, "%s", "5F");
		break;
	case 7:
		system("color 6F");
		fprintf(fp, "%s", "6F");
		break;
	case 8:
		system("color 70");
		fprintf(fp, "%s", "70");
		break;
	case 9:
		system("color F0");
		fprintf(fp, "%s", "F0");
	}

	fclose(fp);
}

void LoadTheme()
{
	FILE* fp;
	if ((fp = fopen("Theme.txt", "r")) == NULL)
	{
		printf("������Ϣ��ȡʧ��.\n");
		exit(0);
	}
	char color[10] = {0};
	fscanf(fp, "%s", color);
	if (strcmp(color, "0F") == 0)
	{
		system("color 0F");
	}
	else if (strcmp(color, "1F") == 0)
	{
		system("color 1F");
	}
	else if (strcmp(color, "2F") == 0)
	{
		system("color 2F");
	}
	else if (strcmp(color, "3F") == 0)
	{
		system("color 3F");
	}
	else if (strcmp(color, "4F") == 0)
	{
		system("color 4F");
	}
	else if (strcmp(color, "5F") == 0)
	{
		system("color 5F");
	}
	else if (strcmp(color, "6F") == 0)
	{
		system("color 6F");
	}
	else if (strcmp(color, "70") == 0)
	{
		system("color 70");
	}
	else if (strcmp(color, "F0") == 0)
	{
		system("color F0");
	}
	fclose(fp);
}