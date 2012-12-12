#include <stdio.h>   // �⺻���� �Լ����� �ҷ���
#include <stdlib.h>  // rand() �Լ� �ҷ���
#include <Windows.h> // Sleep() �Լ� �ҷ���
#include <conio.h>   // getch(), kbhit() �Լ� �ҷ���

/* ���α׷� ���࿡ �ʿ��� ���� ���� */
int i;				// �ٿ뵵

char key;			// �Է¹��� Ű���� ������ ����
int dir = 0;		// ������ ������ ������ ���� _ 0:������(�⺻��), 1:����, 2:��, 3:�Ʒ�
int cnt = 0;

int item_x, item_y;	// ������ ��ǥ�� ������ ����
int item_cnt = 0;	// ���� ���� ���� ������ ����

int length = 3;		// �������� ���̸� ������ ����
int speed;			// �������� �ӵ��� ������ ����

int is_feed;		// ���̸� �Ծ����� ���θ� ������ ���� _ 0: �� ����, 1: ���� 
int is_collide = 0;	// �浹 ���θ� ������ ���� _ 0: �浹 ����, 1: �浹

int x[100] = {3,4,5};		// ó�� ��ġ (x��ǥ)
int y[100] = {3,3,3};		// ó�� ��ġ (y��ǥ)

int new_x, new_y;			// ��������

/* gotoxy �Լ� : �Է¹��� ��ǥ�� Ŀ���� �̵���Ŵ */
int gotoxy(int x,int y) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.Y=y;
	pos.X=x;
	SetConsoleCursorPosition(hConsole, pos); 
	return 0;
}

/* collisionDetect �Լ� : �浹�ϴ� ��쿡 ���� ������ �� ��ȯ *
 * 0: �浹 ����, 1: ���̳� ����� �浹, 2: ���̿� �浹        */
int collisionDetect()
{
	i = 0;

	/* ���� �浹���� ��� */
	if (x[length-1] <= 0 || x[length-1] >= 30 || y[length-1] <= 0 || y[length-1] >= 16)
		return 1;

	/* ���̿� �浹���� ��� */
	if (x[length-1] == item_x && y[length-1] == item_y)
		return 2;

	/* ����� �浹���� ��� */
	for (i = 0 ; i < length-1 ; i++)
	{
		if (x[length-1] == x[i] && y[length-1] == y[i])
			return 1;
	}

	return 0; // �ƹ� ��쿡�� �ɸ��� ������ 0�� ��ȯ
}

int main()
{	
	i = 0;
	speed = 5;

	/* �׵θ� ��� */
	printf("+-----------------------------+\n"); // �� ���� ���
	for (i = 1 ; i <= 15 ; i++)
	{
	printf("|                             |\n");
	}
	printf("+-----------------------------+\n"); // �� �Ʒ��� ���
	
	/* ���� ���� ��(�ʱⰪ 0)�� ��� */
	gotoxy(0,17);
	printf("���� ���� ��: %d", item_cnt);
	
	/* ������ ��ǥ�� �������� ���� */
	item_x = (rand() % 29) + 1; // x��ǥ ��� ����: 1 ~ 29 
	item_y = (rand() % 15) + 1; // y��ǥ ��� ����: 1 ~ 15

	/* �ʱ� ��ġ�� �����̸� ��� */
	for (i = 0 ; i < length ; i++)
	{
		gotoxy(x[i],y[i]);
		printf("*");
	}

	/* �ʱ� ��ġ�� ���̸� ��� */
	gotoxy(item_x,item_y);
	printf("@");

	while (1)
	{
		if (_kbhit()) // Ű���� ���� �Է¹޴� ��쿡�� ����
		{
			key = _getch();       // �Է¹��� Ű���� key�� ����
					
			if (key == 'w')       // w�� �Է¹����� ����
				dir = 2;
			else if (key == 's')  // s�� �Է¹����� �Ʒ���
				dir = 3;
			else if (key == 'a')  // a�� �Է¹����� ����
				dir = 1;
			else if (key == 'd')  // d�� �Է¹����� ������
				dir = 0;
		}

		if (collisionDetect() == 1)
			break;

		if (collisionDetect() == 2)
		{
			is_feed = 1;

			item_x = (rand() % 29) + 1; // x��ǥ ��� ����: 1 ~ 29
			item_y = (rand() % 15) + 1; // y��ǥ ��� ����: 1 ~ 15

			gotoxy(item_x,item_y);
			printf("@");

			item_cnt++;
			gotoxy(0,17);
			printf("���� ���� ��: %d", item_cnt);

			if (dir == 0)
			{
				new_x = x[length-1] + 1;
				new_y = y[length-1];
			}

			else if (dir == 1)
			{
				new_x = x[length-1] - 1;
				new_y = y[length-1];
			}
				
			else if (dir == 2)
			{
				new_x = x[length-1];
				new_y = y[length-1] - 1;
			}

			else if (dir == 3)
			{
				new_x = x[length-1];
				new_y = y[length-1] + 1;
			}

			gotoxy(new_x,new_y);
			printf("*");
				
			length++;

			x[length-1] = new_x;
			y[length-1] = new_y;

			is_feed = 0;
		}

		while ((cnt++) % speed == 0)
		{
			is_collide = collisionDetect();

			if (is_collide == 1)
			{
				break;
			} else 
			{
				/* ���� ����� */
				gotoxy(x[0],y[0]);
				printf(" ");

				/* ���� �����̱� */
				i = 1;
				while (i < length)
				{
					x[i-1] = x[i];
					y[i-1] = y[i];
					i++;
				}

				if (dir == 0)
					x[length-1]++;	// ������ �̵�
				else if (dir == 1)
					x[length-1]--;	// ���� �̵�
				else if (dir == 2)
					y[length-1]--;	// ���� �̵�
				else if (dir == 3)
					y[length-1]++;	// �Ʒ��� �̵�

				/* �� �Ӹ� �׸��� */
				gotoxy(x[length-1],y[length-1]);
				printf("*");
			}
		Sleep(1000/(10+item_cnt));
		}
	}
}