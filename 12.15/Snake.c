#include <stdio.h>   // �⺻���� �Լ����� �ҷ���
#include <stdlib.h>  // rand() �Լ� �ҷ���
#include <Windows.h> // Sleep() �Լ� �ҷ���
#include <conio.h>   // getch(), getche(), kbhit() �Լ� �ҷ���

/* ���α׷� ���࿡ �ʿ��� ���� ���� */
int i;				// �ٿ뵵

char key;			// �Է¹��� Ű���� ������ ����
int dir;			// ������ ������ ������ ���� _ 0:������(�⺻��), 1:����, 2:��, 3:�Ʒ�
int cnt;			// �񵿱� ������ ���� ����

int item_x, item_y;	// ������ ��ǥ�� ������ ����
int item_cnt;		// ���� ���� ���� ������ ����

int length = 1;		// �������� ���̸� ������ ����
int speed = 5;		// �������� �ӵ��� ������ ����
int score = 0;		// ������ ������ ����

int is_feed = 0;	// ���̸� �Ծ����� ���θ� ������ ���� _ 0: �� ����, 1: ���� 
int is_collide = 0;	// �浹 ���θ� ������ ���� _ 0: �浹 ����, 1: �浹

int x[100];			// ó�� ��ġ (x��ǥ)
int y[100];			// ó�� ��ġ (y��ǥ)
int new_x, new_y;	// ���̿� �浹�� �� ��ǥ�� �ӽ������� ������ ����

char restart;		// ���� ����� ���θ� ������ ����

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
	if (x[length-1] <= 0 || x[length-1] >= 50 || y[length-1] <= 0 || y[length-1] >= 23)
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
	Start:	// ���� ������� ���� ���̺�

	/* ��������� ��츦 ����� ���Ӱ� ���õ� �������� ���⼭ �ʱ�ȭ */
	i = 0;
	restart = 0;	// ����� ���� ������ ���� �ʱ�ȭ
	dir = 0;		// ���������� �̵��ϵ��� �ʱ�ȭ
	cnt = 0;		// �񵿱� ������ ���� ���� �ʱ�ȭ

	item_cnt = 0;	// ���� ���� �� �ʱ�ȭ
	score = 0;		// ���� �ʱ�ȭ
	length = 1;		// ������ ���� �ʱ�ȭ (ó�� ����: 1)
	x[0] = 3;		// ������ �ʱ� x��ǥ �ʱ�ȭ
	y[0] = 3;		// ������ �ʱ� y��ǥ �ʱ�ȭ

	for (i = 1 ; i < 100 ; i++) // ���̰� 1�̰� �迭�� ũ�Ⱑ 100�̹Ƿ� ������ 1~99 �迭������ 0���� �ʱ�ȭ
	{
		x[i] = 0;
	}

	/* �׵θ� ��� */
	gotoxy(0,0);
	printf("+-------------------------------------------------+\n"); // �� ���� ���
	for (i = 1 ; i <= 22 ; i++)
	{
	printf("|                                                 |\n");
	}
	printf("+-------------------------------------------------+\n"); // �� �Ʒ��� ���

	/* ������ �κп� ���� �̸� �Ұ� */
	gotoxy(52,0);
	printf("+-----------------------+\n");
	for (i = 1 ; i <= 3 ; i++)
	{
	gotoxy(52,i);
	printf("|                       |\n");
	}
	gotoxy(52,4);
	printf("+-----------------------+\n");
	
	gotoxy(56,2);
	printf("������ ���� : 9��");
	
	/* ������ �κп� ����(�ʱⰪ 0)�� ��� */
	gotoxy(57,7);
	printf("Score : %d     ", score);

	/* ������ �κп� ������ ���̸� ��� */
	gotoxy(56,9);
	printf("Length : %d    ", length);
	
	/* ������ ��ǥ�� �������� ���� */
	item_x = (rand() % 49) + 1; // x��ǥ ��� ����: 1 ~ 49 
	item_y = (rand() % 22) + 1; // y��ǥ ��� ����: 1 ~ 22

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

		/* ���̳� �ڱ� ���� �ε����� ���� */
		if (collisionDetect() == 1)
			break;

		/* ���̿� �ε����� �� ���� �� ī��Ʈ, ���� �ø��� */
		if (collisionDetect() == 2)
		{
			is_feed = 1;				// ���̸� �Ծ���

			/* ���ο� ������ ��ǥ�� ���� */
			item_x = (rand() % 49) + 1; // x��ǥ ��� ����: 1 ~ 49
			item_y = (rand() % 22) + 1; // y��ǥ ��� ����: 1 ~ 22

			/* ���ο� ������ ��ġ�� ���ο� ���̸� ��� */
			gotoxy(item_x, item_y);
			printf("@");

			item_cnt++;						// ���� ���� ���� ����
			score = score + (length * 10);	// ������ �ø�

			gotoxy(57,7);					
			printf("Score : %d", score);	// ������ ������ ���

			/* ���� �Ծ��� �� �����̰� ���ϴ� ���⿡ ���� �� �����̰� �����Ǵ� ��ġ�� �޸� �� */
			if (dir == 0)				// �������� ���� ��
			{
				new_x = x[length-1] + 1;
				new_y = y[length-1];
			}

			else if (dir == 1)			// ������ ���� ��
			{
				new_x = x[length-1] - 1;
				new_y = y[length-1];
			}
				
			else if (dir == 2)			// ������ ���� ��
			{
				new_x = x[length-1];
				new_y = y[length-1] - 1;
			}

			else if (dir == 3)			// �Ʒ����� ���� ��
			{
				new_x = x[length-1];
				new_y = y[length-1] + 1;
			}

			/* ���ο� �Ӹ��� ��� */
			gotoxy(new_x,new_y);
			printf("*");
				
			length++;		// ���̸� ����

			/* �� ��ǥ�� �̽� */
			x[length-1] = new_x;
			y[length-1] = new_y;

			is_feed = 0;	// is_feed�� ���� �ٽ� 0���� ȯ��

			gotoxy(56,9);
			printf("Length : %d", length);	// ������ ���̸� ���
		}

		while ((cnt++) % speed == 0) // �񵿱� ���� (ū while�� �ݺ��ø��� cnt�� ����)
		{
			is_collide = collisionDetect();

			if (is_collide == 1) // is_collide�� 1�� �� ��������
			{
				break;
			} 
			else 
			{
				/* ���� ����� */
				gotoxy(x[0], y[0]);
				printf(" ");

				/* ���� �����̱� */
				i = 1;
				while (i < length)	// ���� ���� ��ǥ���� �ϳ��� �б�
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
				gotoxy(x[length-1], y[length-1]);
				printf("*");
			}

		Sleep(1000/(5+item_cnt));	// ���� ���� ���� ���� ������ �ӵ� ����

		}
	}

	/* �׵θ��� ��Ƽ� while�� ���������� ���� ���� ���� ��� */
	gotoxy(58,12);
	printf("< Game Over >"); // ���� ���� ���

	/* ������ ���� ������� ���� ��� */
	if (score >= 0 && score <= 550)		// 0 ~ 550: �ϼ�
	{
		gotoxy(56,14);
		printf("����� �ϼ��Դϴ�.");
	}
	else if (score > 550 && score <= 1200)	// 551 ~ 1200: �߼�
	{
		gotoxy(56,14);
		printf("����� �߼��Դϴ�.");
	}
	else if (score > 1200 && score <= 2100)	// 1201 ~ 2100: ���
	{
		gotoxy(56,14);
		printf("����� ����Դϴ�!");
	}
	else if (score > 2100)	// 2101 ~ : ����
	{
		gotoxy(56,14);
		printf("����� �����Դϴ�!!");
	}

	Continue:

	/* ����� ���� ���� ���� Ű �Է� ���� */
	gotoxy(55,16);
	printf("Continue? (Y/N) : ");

	restart = getche();			// Ű���� �ϳ� �Է¹����� �Է¹��� ���� ��� �� �ٷ� ���� �� ����

	if (restart == 'y' || restart == 'Y')	// 'y'�� 'Y'�� �Է¹޾��� ��
	{
		/* ������ �׸��� ��� ���� */
		for (i = 0 ; i <= 23 ; i++)
		{
			gotoxy(51,i);
			printf("                                                                                     ");
		}
		goto Start;	// ���� ���� �κ����� ����
	}
	else if (restart == 'n' || restart == 'N')	// 'n'�̳� 'N'�� �Է¹޾��� ��
	{
		/* Ű �߸� �Է��� ���� ���� ��� �޽����� �־��ٸ� ���� */
		gotoxy(53,18);
		printf("                                ");

		/* 5�� �Ŀ� ���� */
		for (i=0 ; i<=4 ; i++)
		{
			gotoxy(55,16);
			printf("%d�� �Ŀ� ����˴ϴ�.", 5-i); // �� �� ���Ҵ��� ���
			Sleep(1000); // 1�ʰ� �޽�
		}
	}
	else // ���� �� ��쿡 �ش����� �ʴ� ���ڸ� �Է¹޾��� ��
	{
		/* �߸� �Է½� �߸� �Է��� ���ڸ� ���� */
		gotoxy(73,16);
		printf(" ");
		
		gotoxy(53,18);
		printf("* Y,y,N,n �� �ϳ� �Է� *");

		goto Continue;	// ������ �ٽ� ���
	}

	return 0;
}