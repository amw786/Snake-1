#include <stdio.h>   // 기본적인 함수들을 불러옴
#include <stdlib.h>  // rand() 함수 불러옴
#include <Windows.h> // Sleep() 함수 불러옴
#include <conio.h>   // getch(), kbhit() 함수 불러옴

/* 프로그램 실행에 필요한 변수 정의 */
int i;				// 다용도

char key;			// 입력받은 키값을 저장할 변수
int dir = 0;		// 움직일 방향을 저장할 변수 _ 0:오른쪽(기본값), 1:왼쪽, 2:위, 3:아래
int cnt = 0;		// 비동기 조작을 위한 변수

int item_x, item_y;	// 먹이의 좌표를 저장할 변수
int item_cnt = 0;	// 먹이 먹은 수를 저장할 변수

int length = 1;		// 지렁이의 길이를 저장할 변수
int speed;			// 지렁이의 속도를 저장할 변수
int score = 0;		// 점수를 저장할 변수

int is_feed = 0;	// 먹이를 먹었는지 여부를 저장할 변수 _ 0: 안 먹음, 1: 먹음 
int is_collide = 0;	// 충돌 여부를 저장할 변수 _ 0: 충돌 안함, 1: 충돌

int x[100] = {3};	// 처음 위치 (x좌표)
int y[100] = {3};	// 처음 위치 (y좌표)
int new_x, new_y;	// 먹이와 충돌시 새 좌표를 임시적으로 저장할 좌표

/* gotoxy 함수 : 입력받은 좌표로 커서를 이동시킴 */
int gotoxy(int x,int y) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.Y=y;
	pos.X=x;
	SetConsoleCursorPosition(hConsole, pos); 
	return 0;
}

/* collisionDetect 함수 : 충돌하는 경우에 따라 다음의 값 반환 *
 * 0: 충돌 없음, 1: 벽이나 몸통과 충돌, 2: 먹이와 충돌        */
int collisionDetect()
{
	i = 0;

	/* 벽과 충돌했을 경우 */
	if (x[length-1] <= 0 || x[length-1] >= 30 || y[length-1] <= 0 || y[length-1] >= 16)
		return 1;

	/* 먹이와 충돌했을 경우 */
	if (x[length-1] == item_x && y[length-1] == item_y)
		return 2;

	/* 몸통과 충돌했을 경우 */
	for (i = 0 ; i < length-1 ; i++)
	{
		if (x[length-1] == x[i] && y[length-1] == y[i])
			return 1;
	}

	return 0; // 아무 경우에도 걸리지 않으면 0을 반환
}

int main()
{	
	i = 0;
	speed = 5;

	/* 테두리 장식 */
	printf("+-----------------------------+\n"); // 맨 윗줄 장식
	for (i = 1 ; i <= 15 ; i++)
	{
	printf("|                             |\n");
	}
	printf("+-----------------------------+\n"); // 맨 아랫줄 장식
	
	/* 점수(초기값 0)을 출력 */
	gotoxy(0,17);
	printf("Score: %d", score);
	
	/* 먹이의 좌표를 랜덤으로 지정 */
	item_x = (rand() % 29) + 1; // x좌표 출력 범위: 1 ~ 29 
	item_y = (rand() % 15) + 1; // y좌표 출력 범위: 1 ~ 15

	/* 초기 위치에 지렁이를 출력 */
	for (i = 0 ; i < length ; i++)
	{
		gotoxy(x[i],y[i]);
		printf("*");
	}

	/* 초기 위치에 먹이를 출력 */
	gotoxy(item_x,item_y);
	printf("@");

	while (1)
	{
		if (_kbhit()) // 키보드 값을 입력받는 경우에만 실행
		{
			key = _getch();       // 입력받은 키값을 key에 저장
					
			if (key == 'w')       // w를 입력받으면 위쪽
				dir = 2;
			else if (key == 's')  // s를 입력받으면 아래쪽
				dir = 3;
			else if (key == 'a')  // a를 입력받으면 왼쪽
				dir = 1;
			else if (key == 'd')  // d를 입력받으면 오른쪽
				dir = 0;
		}

		/* 벽이나 자기 몸에 부딪히면 종료 */
		if (collisionDetect() == 1)
			break;

		/* 먹이에 부딪혔을 때 먹이 수 카운트, 점수 올리기 */
		if (collisionDetect() == 2)
		{
			is_feed = 1;				// 먹이를 먹었음

			/* 새로운 먹이의 좌표를 지정 */
			item_x = (rand() % 29) + 1; // x좌표 출력 범위: 1 ~ 29
			item_y = (rand() % 15) + 1; // y좌표 출력 범위: 1 ~ 15

			/* 새로운 먹이의 위치에 새로운 먹이를 출력 */
			gotoxy(item_x, item_y);
			printf("@");

			item_cnt++;						// 먹이 먹은 수를 증가
			score = score + (length * 10);	// 점수를 올림

			gotoxy(0,17);					
			printf("Score: %d", score);		// 점수 출력

			/* 먹이 먹었을 때 지렁이가 향하는 방향에 따라 새 지렁이가 생성되는 위치를 달리 함 */
			if (dir == 0)				// 오른쪽을 향할 때
			{
				new_x = x[length-1] + 1;
				new_y = y[length-1];
			}

			else if (dir == 1)			// 왼쪽을 향할 때
			{
				new_x = x[length-1] - 1;
				new_y = y[length-1];
			}
				
			else if (dir == 2)			// 위쪽을 향할 때
			{
				new_x = x[length-1];
				new_y = y[length-1] - 1;
			}

			else if (dir == 3)			// 아래쪽을 향할 때
			{
				new_x = x[length-1];
				new_y = y[length-1] + 1;
			}

			/* 새로운 머리를 출력 */
			gotoxy(new_x,new_y);
			printf("*");
				
			length++;			// 길이를 증가

			/* 새 좌표를 이식 */
			x[length-1] = new_x;
			y[length-1] = new_y;

			is_feed = 0;		// is_feed의 값을 다시 0으로 환원
		}

		while ((cnt++) % speed == 0)
		{
			is_collide = collisionDetect();

			if (is_collide == 1) // is_collide가 1일 때 빠져나옴
			{
				break;
			} 
			else 
			{
				/* 꼬리 지우기 */
				gotoxy(x[0], y[0]);
				printf(" ");

				/* 몸통 움직이기 */
				i = 1;
				while (i < length)
				{
					x[i-1] = x[i];
					y[i-1] = y[i];
					i++;
				}

				if (dir == 0)
					x[length-1]++;	// 오른쪽 이동
				else if (dir == 1)
					x[length-1]--;	// 왼쪽 이동
				else if (dir == 2)
					y[length-1]--;	// 위쪽 이동
				else if (dir == 3)
					y[length-1]++;	// 아래쪽 이동

				/* 새 머리 그리기 */
				gotoxy(x[length-1], y[length-1]);
				printf("*");
			}

		Sleep(1000/(5+item_cnt));

		}
	}

	/* 테두리에 닿아서 while문 빠져나오면 게임 오버 문구 출력 */
	gotoxy(10,7);
	printf("Game Over"); // 게임 오버 출력

	for (i=0 ; i<=4 ; i++)
	{
		gotoxy(5,10);
		printf("%d초 후에 종료됩니다.", 5-i); // 몇 초 남았는지 출력
		Sleep(1000); // 1초간 휴식
	}

	return 0;
}