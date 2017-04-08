/*
�ù���Ϣ���� GAR.c
GAR:GuestAndHotel
���ļ������˹���GuestAndRoom����ĺ�����
*/

#include"Structs.h"

extern int guestNum;

void LoadGARInfo()//���ļ���ȡ�ÿ��뷿����Ϣ������GuestAndRoom
{
	FILE* fp;
	char title[20] = "";
	if ((fp = fopen("GuestAndRoom.txt.", "r")) == NULL)
	{
		printf("�ļ���ȡʧ��");
		exit(0);
	}
	fscanf(fp, "%s %s %s %s\n", title, title, title, title);
	while (!feof(fp))//�˴���feof�������ϸ���Ϊ�ļ�ĩβ���пո���˺����ж�fscanf�ķ���ֵ�������жϡ�
	{
		struct GuestAndRoom* insert = (struct GuestAndRoom *)malloc(sizeof(struct GuestAndRoom));
		if (fscanf(fp, "%d %s ", &insert->guestRoom, insert->guestID) != 2)
		{
			free(insert);
			break;
		}
		fgets(insert->checkInTime, 25, fp);
		strcpy(insert->checkOutTime, " ");
		GAR_tail->next = insert;
		insert->next = NULL;
		GAR_tail = insert;
	}
	fclose(fp);
}

void SaveGARInfo()
{
	FILE* fp;
	if ((fp = fopen("GuestAndRoom.txt", "w")) == NULL)
	{
		printf("�ļ���ȡʧ��");
		exit(0);
	}
	fprintf(fp, "%s %s %s %s", "����", "���֤", "��סʱ��", "�˷�ʱ��");
	struct GuestAndRoom* cur = GAR_head->next;
	while (cur != NULL)
	{
		fprintf(fp, "\n%d %s %s %s", cur->guestRoom, cur->guestID, cur->checkInTime, cur->checkOutTime);
		cur = cur->next;
	}
	fclose(fp);
}

void GuestCheckIn()//�ÿ���ס
{
	int roomChoice = 0;
	int sexchoice = 0;
	char name_input[20] = {0};
	char ID_insert[20] = {0};
	char sex[10] = {0};
	char time_insert[30] = {0};//�ֲ������ʼ������ֵ��
	time_t t = time(NULL);//���ڼ�¼��סʱ��

	printf("====================������Ϣ====================\n");
	ViewAvaRoom();//��ʾ���÷���
	printline();
	printf("�������ÿ����֤�ţ�\n");
	scanf("%s", ID_insert);
	//����Ƿ��Ѿ���ס��
	struct Guests* cur = guest_head->next;
	while (cur != NULL)
	{
		if (strcmp(cur->ID, ID_insert) == 0)
		{
			printf("���ÿ��ѵǼ���ס.����ס���ÿͿ�ѡ�񻻷�.");
			return;//����ִ�е�ǰ����
		}
		cur = cur->next;
	}
	//�����Ϣ��Guests����
	struct Guests* guest_insert = (struct Guests *)malloc(sizeof(struct Guests));
	strcpy(guest_insert->ID, ID_insert);
	printf("�������ÿ�������\n");
	scanf("%s", name_input);
	strcpy(guest_insert->name, name_input);
	printf("��ѡ���Ա�\n1 ��  2 Ů\n");
	scanf("%d", &sexchoice);
	switch (sexchoice)
	{
	default:
		break;
	case 1:
		strcpy(guest_insert->sex, "��");
		break;
	case 2:
		strcpy(guest_insert->sex, "Ů");
		break;
	}
	strcpy(sex, guest_insert->sex);

	guest_tail->next = guest_insert;
	guest_insert->next = NULL;
	guest_tail = guest_insert;
	//�޸�Rooms�����е���Ϣ
	printf("�������ÿͽ���ס�ķ���ţ�\n");
	int findChoice;//����ķ�����Ƿ��Ǵ��ڵ�
	int checkIn;//�Ƿ�ɹ���ס
	while (1)// �ж� ������Ƿ����� �� �����Ƿ����
	{
		struct Rooms* room_cur = room_head->next;
		findChoice = 0;
		checkIn = 0;
		scanf("%d", &roomChoice);
		while (room_cur != NULL)
		{
			if (room_cur->roomNum == roomChoice && ((room_cur->roomtype) - (room_cur->checkinNum)) > 0)
			{
				(room_cur->checkinNum)++;//�÷�����ס������1
				findChoice = 1;
				checkIn = 1;
				break;
			}
			else if (room_cur->roomNum == roomChoice && ((room_cur->roomtype) - (room_cur->checkinNum)) <= 0)
			{
				findChoice = 1;
				checkIn = 0;
				printf("ѡ��ķ�����������ѡ�����ס�ķ���:\n");
				break;
			}
			room_cur = room_cur->next;
		}
		if (!findChoice)//��������
		{
			printf("����ķ����������������ȷ�ķ���ţ�\n");
			continue;
		}
		else if (findChoice && !checkIn)//��������
		{
			continue;
		}
		else if (checkIn && findChoice)//��ס�ɹ�
			break;
	}

	//����ÿ���Ϣ��GuestAndRoom����
	struct GuestAndRoom* GAR_insert = (struct GuestAndRoom *)malloc(sizeof(struct GuestAndRoom));
	GAR_insert->guestRoom = roomChoice;
	strcpy(GAR_insert->guestID, ID_insert);
	strncpy(GAR_insert->checkInTime, ctime(&t), strlen(ctime(&t)) - 1);//ctime()����ֵĩβ�л��з���
	GAR_insert->checkInTime[strlen(ctime(&t)) - 1] = '\0';//strncpy()�������Ҫ�ֶ����'\0'
	printf("��ס��¼�ɹ�����סʱ��Ϊ��%s", GAR_insert->checkInTime);
	strcpy(GAR_insert->checkOutTime, " ");

	GAR_tail->next = GAR_insert;
	GAR_insert->next = NULL;
	GAR_tail = GAR_insert;

	guestNum++;
	//��ס����Guest.txt�������Ϣ
	FILE* Guest_p;
	if ((Guest_p = fopen("Guest.txt", "a")) == NULL)
	{
		printf("Guest.txt�ļ���ȡʧ��");
		exit(0);
	}
	fprintf(Guest_p, "\n%s %s %s", name_input, sex, ID_insert);
	fclose(Guest_p);

	//��ס����GuestAndRoom.txt�������Ϣ
	FILE* GAR_p;
	if ((GAR_p = fopen("GuestAndRoom.txt", "a")) == NULL)
	{
		printf("GuestAndRoom.txt�ļ���ȡʧ��");
		exit(0);
	}
	strncpy(time_insert, ctime(&t), strlen(ctime(&t)) - 1);//ctime()����ֵĩβ�л��з���
	time_insert[strlen(ctime(&t)) - 1] = '\0';//strncpy()�������Ҫ�ֶ����'\0'
	fprintf(GAR_p, "\n%d %s %s %s", roomChoice, ID_insert, time_insert, " ");
	fclose(GAR_p);
}

void GuestChangeRoom()//�ÿͻ���
{
	char IDchoice[25] = {0};
	int oldRoomNum = 0;//ԭ�����
	int roomChoice = 0;
	int findChoice;//����ķ�����Ƿ��Ǵ��ڵ�
	int ifCheckIn;//�Ƿ�ɹ���ס
	printf("���������֤�ţ�\n");
	scanf("%s", IDchoice);
	//����Ƿ�����ס
	struct Guests* guest_cur = guest_head->next;
	int isCheckedIn = 0;
	while (guest_cur != NULL)
	{
		if (strcmp(guest_cur->ID, IDchoice) == 0)
		{
			isCheckedIn = 1;
			struct GuestAndRoom* GAR_cur = GAR_head->next;
			while (GAR_cur != NULL)
			{
				if (strcmp(GAR_cur->guestID, IDchoice) == 0)//ͨ�����֤����GuestAndRoom�������ҵ�����š���סʱ��
				{
					printline();
					printf("����\t�Ա�\t���֤\t\t\t����\t��סʱ��");
					printf("\n%s\t%s\t%s\t%d\t%s\t", guest_cur->name, guest_cur->sex, IDchoice, GAR_cur->guestRoom, GAR_cur->checkInTime);
					printline();
					break;
				}
				GAR_cur = GAR_cur->next;
			}
			break;
		}
		guest_cur = guest_cur->next;
	}
	if (!isCheckedIn)//û����ס��
	{
		printf("���ÿ���δ������ס.�ѷ������˵�.\n");
		return;
	}

	if (ViewAvaRoom() == 0)//����޿շ� //�������ӡ����ס������Ϣ
		return;
	printf("�����뽫����ķ���ţ�\n");

	//�ж� �Ƿ���ԭ���䡢������Ƿ����󡢷����Ƿ����
	while (1)
	{
		scanf("%d", &roomChoice);
		int oldRoomFlag = 0;//�Ƿ�ѡ����ԭ����
		struct GuestAndRoom* GAR_cur = GAR_head->next;
		while (GAR_cur != NULL)
		{
			if (GAR_cur->guestRoom == roomChoice && strcmp(GAR_cur->guestID, guest_cur->ID) == 0)
			{
				printf("���ܻ���ԭ���䣬��ѡ���·��䣺\n");
				oldRoomFlag = 1;
				break;
			}
			GAR_cur = GAR_cur->next;
		}
		if (oldRoomFlag == 1)//�����ԭ����
		{
			continue;//�������뷿���
		}
		//ѡ������·��䣬����ִ��
		struct Rooms* room_cur = room_head->next;
		findChoice = 0;
		ifCheckIn = 0;
		while (room_cur != NULL)
		{
			if (room_cur->roomNum == roomChoice && ((room_cur->roomtype) - (room_cur->checkinNum)) > 0)
			{
				(room_cur->checkinNum)++;//�·�����ס������1
				//ԭ�������ס������1
				GAR_cur = GAR_head->next;
				while (GAR_cur != NULL)
				{
					if (strcmp(GAR_cur->guestID, IDchoice) == 0)
					{
						oldRoomNum = GAR_cur->guestRoom;//ԭ�����������ٽ��ں������
						GAR_cur->guestRoom = roomChoice;//����GAR�����еķ����
						break;
					}
					GAR_cur = GAR_cur->next;
				}
				if (!oldRoomNum)
				{
					printf("�޷��ҵ�ԭ����.�ѷ������˵�.");
					return;
				}
				findChoice = 1;
				ifCheckIn = 1;
				break;
			}
			else if (room_cur->roomNum == roomChoice && ((room_cur->roomtype) - (room_cur->checkinNum)) <= 0)
			{
				findChoice = 1;
				ifCheckIn = 0;
				printf("ѡ��ķ�����������ѡ�����ס�ķ���:\n");
				break;
			}
			room_cur = room_cur->next;
		}
		if (!findChoice)//��������
		{
			printf("����ķ����������������ȷ�ķ���ţ�\n");
			continue;
		}
		else if (findChoice && !ifCheckIn)//��������
		{
			continue;
		}
		else if (ifCheckIn && findChoice)//��ס�ɹ�
			break;
	}

	//����
	char checkInTime[30] = {0};
	struct GuestAndRoom* GAR_cur = GAR_head->next;
	while (GAR_cur != NULL)
	{
		if (strcmp(GAR_cur->guestID, IDchoice) == 0)
		{
			strcpy(checkInTime, GAR_cur->checkInTime);
			break;
		}
		GAR_cur = GAR_cur->next;
	}
	struct tm checkIn = {0};//���� �·� ���� ʱ���֣��� ��
	checkIn.tm_isdst = -1;
	char week[10] = {0};
	char month[10] = {0};
	sscanf(checkInTime, "%s %s %d %d:%d:%d %d", week, month, &checkIn.tm_mday, &checkIn.tm_hour, &checkIn.tm_min, &checkIn.tm_sec, &checkIn.tm_year);
	checkIn.tm_year -= 1900;//tm_year�Ǵ�1900�꿪ʼ����ģ�
	if (strcmp(week, "Sun") == 0)//C������switch�ı��ʽֻ����������C++�п������ַ���
		checkIn.tm_wday = 0;
	else if (strcmp(week, "Mon") == 0)
		checkIn.tm_wday = 1;
	else if (strcmp(week, "Tue") == 0)
		checkIn.tm_wday = 2;
	else if (strcmp(week, "Wed") == 0)
		checkIn.tm_wday = 3;
	else if (strcmp(week, "Thu") == 0)
		checkIn.tm_wday = 4;
	else if (strcmp(week, "Fri") == 0)
		checkIn.tm_wday = 5;
	else if (strcmp(week, "Sat") == 0)
		checkIn.tm_wday = 6;
	if (strcmp(month, "Jan") == 0)
		checkIn.tm_mon = 0;
	else if (strcmp(month, "Feb") == 0)
		checkIn.tm_mon = 1;
	else if (strcmp(month, "Mar") == 0)
		checkIn.tm_mon = 2;
	else if (strcmp(month, "Apr") == 0)
		checkIn.tm_mon = 3;
	else if (strcmp(month, "May") == 0)
		checkIn.tm_mon = 4;
	else if (strcmp(month, "Jun") == 0)
		checkIn.tm_mon = 5;
	else if (strcmp(month, "Jul") == 0)
		checkIn.tm_mon = 6;
	else if (strcmp(month, "Aug") == 0)
		checkIn.tm_mon = 7;
	else if (strcmp(month, "Sep") == 0)
		checkIn.tm_mon = 8;
	else if (strcmp(month, "Oct") == 0)
		checkIn.tm_mon = 9;
	else if (strcmp(month, "Nov") == 0)
		checkIn.tm_mon = 10;
	else if (strcmp(month, "Dec") == 0)
		checkIn.tm_mon = 11;
	time_t checkOutTime = time(NULL);
	double money;//Ӧ������
	double discount = 1;//�ۿ���
	double duration = difftime(checkOutTime, mktime(&checkIn));//��סʱ�����������
	duration = (int)duration / 86400 + 1;//����Ϊ����
	money = duration * (double)UnitPrice(oldRoomNum);
	printf("����ǰ��֧���Ѳ����ķ���.\n");
	printf("�������ۿ��ʣ�(0-1)\n");
	while (1)
	{
		scanf("%lf", &discount);
		if (discount <= 1 && discount >= 0)
		{
			printf("����ǰ Ӧ����%.2lfԪ\n", discount * money);
			break;
		}
	}

	//�޸�Rooms������ԭ������������·��������������������ʵ�֣�
	struct Rooms* room_cur = room_head->next;
	while (room_cur != NULL)
	{
		if (room_cur->roomNum == oldRoomNum)
			room_cur->checkinNum--;
		room_cur = room_cur->next;
	}

	//�޸�GAR�ļ��еķ����
	SaveGARInfo();
	//��������˷�ʱ�䣡
}

void GuestCheckOut()//�ÿ��˷�
{
	time_t t = time(NULL);
	char IDchoice[25] = {0};
	struct Guests** guest_delete = NULL;
	struct GuestAndRoom** GAR_delete = NULL;
	int flag = 0;//�ҵ��ÿ�Ϊ1��δ�ҵ��ÿ�Ϊ0

	printf("���������֤�ţ�\n");
	scanf("%s", IDchoice);

	struct Guests* guest_cur = guest_head->next;
	while (guest_cur != NULL)
	{
		if (strcmp(guest_cur->ID, IDchoice) == 0)//�ҵ����֤ƥ����ÿ� //�ַ����Ƚ���Ҫʹ��strcmp����
		{
			guest_delete = &guest_cur;//�ö���ָ���¼Ҫɾ����Guests����ĵ�ַ
			flag = 1;//�ҵ��ÿ�Ϊ1��δ�ҵ��ÿ�Ϊ0
			struct GuestAndRoom* GAR_cur = GAR_head->next;
			while (GAR_cur != NULL)
			{
				if (strcmp(GAR_cur->guestID, IDchoice) == 0)//�ַ����Ƚ���Ҫʹ��strcmp����
				{
					GAR_delete = &GAR_cur;
					break;
				}
				GAR_cur = GAR_cur->next;
			}
			break;
		}
		guest_cur = guest_cur->next;
	}

	if (!flag)
	{
		printf("û���ҵ����ÿ�\n");
		return;
	}

	//�ļ������¼�ÿ���Ϣ
	FILE* GH_p;//GuestHistoryInfo_pointer
	if ((GH_p = fopen("GuestHistoryInfo.txt", "a")) == NULL)
	{
		printf("�ļ���ȡʧ��");
		exit(0);
	}
	strncpy((*GAR_delete)->checkOutTime, ctime(&t), strlen(ctime(&t)) - 1);
	(*GAR_delete)->checkOutTime[strlen(ctime(&t)) - 1] = '\0';//��¼�˷�ʱ��
	fprintf(GH_p, "\n%s %s %d %s %s", (*guest_delete)->name, (*guest_delete)->ID, (*GAR_delete)->guestRoom, (*GAR_delete)->checkInTime, (*GAR_delete)->checkOutTime);//���� ���֤ ����� ��סʱ�� �˷�ʱ��
	fclose(GH_p);

	//��Ļ����˷���Ϣ
	printline();
	printf("�˴��Ǹ��ÿ͵�%d��ס��.\n", IsOldGuest(IDchoice) + 1);
	printf("���ÿ���סʱ��Ϊ%s\n", (*GAR_delete)->checkInTime);
	printf("�˷�ʱ��Ϊ%s\n", (*GAR_delete)->checkOutTime);
	struct tm checkIn = {0};//���� �·� ���� ʱ���֣��� ��
	checkIn.tm_isdst = -1;
	char week[10] = {0};
	char month[10] = {0};
	sscanf((*GAR_delete)->checkInTime, "%s %s %d %d:%d:%d %d", week, month, &checkIn.tm_mday, &checkIn.tm_hour, &checkIn.tm_min, &checkIn.tm_sec, &checkIn.tm_year);
	checkIn.tm_year -= 1900;//tm_year�Ǵ�1900�꿪ʼ����ģ�
	if (strcmp(week, "Sun") == 0)//C������switch�ı��ʽֻ����������C++�п������ַ���
		checkIn.tm_wday = 0;
	else if (strcmp(week, "Mon") == 0)
		checkIn.tm_wday = 1;
	else if (strcmp(week, "Tue") == 0)
		checkIn.tm_wday = 2;
	else if (strcmp(week, "Wed") == 0)
		checkIn.tm_wday = 3;
	else if (strcmp(week, "Thu") == 0)
		checkIn.tm_wday = 4;
	else if (strcmp(week, "Fri") == 0)
		checkIn.tm_wday = 5;
	else if (strcmp(week, "Sat") == 0)
		checkIn.tm_wday = 6;
	if (strcmp(month, "Jan") == 0)
		checkIn.tm_mon = 0;
	else if (strcmp(month, "Feb") == 0)
		checkIn.tm_mon = 1;
	else if (strcmp(month, "Mar") == 0)
		checkIn.tm_mon = 2;
	else if (strcmp(month, "Apr") == 0)
		checkIn.tm_mon = 3;
	else if (strcmp(month, "May") == 0)
		checkIn.tm_mon = 4;
	else if (strcmp(month, "Jun") == 0)
		checkIn.tm_mon = 5;
	else if (strcmp(month, "Jul") == 0)
		checkIn.tm_mon = 6;
	else if (strcmp(month, "Aug") == 0)
		checkIn.tm_mon = 7;
	else if (strcmp(month, "Sep") == 0)
		checkIn.tm_mon = 8;
	else if (strcmp(month, "Oct") == 0)
		checkIn.tm_mon = 9;
	else if (strcmp(month, "Nov") == 0)
		checkIn.tm_mon = 10;
	else if (strcmp(month, "Dec") == 0)
		checkIn.tm_mon = 11;
	struct tm checkOut = {0};//���� �·� ���� ʱ���֣��� ��
	checkOut.tm_isdst = -1;
	sscanf((*GAR_delete)->checkOutTime, "%s %s %d %d:%d:%d %d", week, month, &checkOut.tm_mday, &checkOut.tm_hour, &checkOut.tm_min, &checkOut.tm_sec, &checkOut.tm_year);
	checkOut.tm_year -= 1900;//tm_year�Ǵ�1900�꿪ʼ����ģ�
	if (strcmp(week, "Sun") == 0)//C������switch�ı��ʽֻ����������C++�п������ַ���
		checkOut.tm_wday = 0;
	else if (strcmp(week, "Mon") == 0)
		checkOut.tm_wday = 1;
	else if (strcmp(week, "Tue") == 0)
		checkOut.tm_wday = 2;
	else if (strcmp(week, "Wed") == 0)
		checkOut.tm_wday = 3;
	else if (strcmp(week, "Thu") == 0)
		checkOut.tm_wday = 4;
	else if (strcmp(week, "Fri") == 0)
		checkOut.tm_wday = 5;
	else if (strcmp(week, "Sat") == 0)
		checkOut.tm_wday = 6;
	if (strcmp(month, "Jan") == 0)
		checkOut.tm_mon = 0;
	else if (strcmp(month, "Feb") == 0)
		checkOut.tm_mon = 1;
	else if (strcmp(month, "Mar") == 0)
		checkOut.tm_mon = 2;
	else if (strcmp(month, "Apr") == 0)
		checkOut.tm_mon = 3;
	else if (strcmp(month, "May") == 0)
		checkOut.tm_mon = 4;
	else if (strcmp(month, "Jun") == 0)
		checkOut.tm_mon = 5;
	else if (strcmp(month, "Jul") == 0)
		checkOut.tm_mon = 6;
	else if (strcmp(month, "Aug") == 0)
		checkOut.tm_mon = 7;
	else if (strcmp(month, "Sep") == 0)
		checkOut.tm_mon = 8;
	else if (strcmp(month, "Oct") == 0)
		checkOut.tm_mon = 9;
	else if (strcmp(month, "Nov") == 0)
		checkOut.tm_mon = 10;
	else if (strcmp(month, "Dec") == 0)
		checkOut.tm_mon = 11;
	double money;//Ӧ������
	double discount = 1;//�ۿ���
	double duration = difftime(mktime(&checkOut), mktime(&checkIn));//��סʱ�����������
	duration = (int)duration / 86400 + 1;//����Ϊ����
	money = duration * (double)UnitPrice((*GAR_delete)->guestRoom);
	printf("�������ۿ��ʣ�(0-1)\n");
	while (1)
	{
		scanf("%lf", &discount);
		if (discount <= 1 && discount >= 0)
		{
			printf("Ӧ����%.2lfԪ\n", discount * money);
			break;
		}
	}

	//ɾ��Guests�����е���Ϣ
	if ((*guest_delete)->next != NULL)//���Ҫɾ���Ľڵ㲻�����������
	{
		//ע��ָ�뱾��ĵ�ַ&p��ָ��ָ�������*p��ָ��洢�ĵ�ַp���߲�ͬ //ע��˴�ʹ���˶���ָ��
		struct Guests* temp = (*guest_delete)->next;//��¼��ɾ����һ��ָ��ĵ�ַ
		**guest_delete = *(*guest_delete)->next;//�ǽ�һ��ָ��ָ������ݸ�ֵ
		free(temp);//free()�����ͷŶ�̬������ڴ�
	}
	else if ((*guest_delete)->next == NULL)//���Ҫɾ���Ľڵ������������
	{
		struct Guests* end = guest_head->next;
		while (end != NULL)
		{
			if (end->next == NULL)//������ֻ��һ��
			{
				free(end);
				guest_head->next = NULL;
				guest_tail = guest_head;
				break;
			}
			else if (end->next->next == NULL)//end��ʱ�ǵ����ڶ���
			{
				free(end->next);
				end->next = NULL;
				guest_tail = end;
				*guest_delete = NULL;
				break;
			}
			end = end->next;
		}
	}

	//ɾ��GAR�����е���Ϣ
	if ((*GAR_delete)->next != NULL)//Ҫɾ���Ľڵ㲻�����һ��
	{
		struct GuestAndRoom* temp = (*GAR_delete)->next;
		**GAR_delete = *(*GAR_delete)->next;
		free(temp);
	}
	else if ((*GAR_delete)->next == NULL)//Ҫɾ���Ľڵ������һ��
	{
		struct GuestAndRoom* end = GAR_head->next;
		while (end != NULL)
		{
			if (end->next == NULL)//������ֻ��һ��
			{
				free(end);
				GAR_head->next = NULL;
				GAR_tail = GAR_head;
				break;
			}
			else if (end->next->next == NULL)//end��ʱ�ǵ����ڶ���
			{
				free(end->next);
				end->next = NULL;
				GAR_tail = end;
				*GAR_delete = NULL;
				break;
			}
			end = end->next;
		}
	}
	guestNum--;
	//���������ļ�
	SaveGARInfo();
	SaveGuestInfo();
	SaveHotelInfo();
}