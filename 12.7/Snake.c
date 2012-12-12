#include <stdio.h>   // 기본적인 함수들을 불러옴
#include <stdlib.h>  // rand() 함수 불러옴
#include <Windows.h> // Sleep() 함수 불러옴
#include <conio.h>   // getch(), kbhit() 함수 불러옴

/* gotoxy 함수(입력받은 좌표로 커서를 이동시킴) */
int gotoxy(int x,int y) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.Y=y;
	pos.X=x;
	SetConsoleCursorPosition(hConsole, pos); 
	return 0;
}

int main()
{	
	int x,y;            // 지렁이의 좌표를 저장할 변수
	int i;              // for문을 위한 변수
	int j, speed;       // 비동기 조작을 위한 변수
	int dir = 0;        // 움직일 방향을 저장할 변수 _ 0:오른쪽(기본값), 1:왼쪽, 2:위, 3:아래
	int item_x, item_y; // 먹이의 좌표를 저장할 변수
	int item_cnt = 0;   // 먹이 먹은 수를 저장할 변수
	char key;           // 입력받은 키값을 저장할 변수
	x = 3;              // 처음 위치 (x좌표)
	y = 3;              // 처음 위치 (y좌표)

	/* 테두리 장식 */
	printf("+-----------------------------+\n"); // 맨 윗줄 장식
	for (i=1 ; i<=15 ; i++)
	{
	printf("|                             |\n");
	}
	printf("+-----------------------------+\n"); // 맨 아랫줄 장식
	
	/* 먹은 먹이 수(초기값 0)를 출력 */
	gotoxy(0,17);
	printf("먹은 먹이 수: %d", item_cnt);

	/* 먹이의 좌표를 랜덤으로 지정 */
	item_x = (rand() % 29) + 1; // x좌표 출력 범위: 1 ~ 29 
	item_y = (rand() % 15) + 1; // y좌표 출력 범위: 1 ~ 15
	
	/* 반복을 제어 */
	j = 0;		// 반복 제어 변수
	speed = 5;	// 지렁이 이동 속도 (반복문을 5번 돌 때(i가 5의 배수가 될 때)마다 이동하도록 함, 값이 클수록 느려짐)

	while (1) // break하지 않는 이상 while문을 계속 반복
	{
		/* 랜덤하게 지정된 좌표에 먹이를 출력 */
		gotoxy(item_x,item_y);
		printf("@");

		/* 테두리에 닿으면 while문을 탈출 */
		if (x <= 0 || x >= 30 || y <= 0 || y >= 16)
			break;

		/* 먹이에 닿으면 카운트하고 먹이를 옮김 */
		if (x == item_x && y == item_y)
		{
			/* 먹이에 닿으면 먹이를 옮김 */
			item_x = (rand() % 29) + 1; // x좌표 출력 범위: 1 ~ 29
			item_y = (rand() % 15) + 1; // y좌표 출력 범위: 1 ~ 15

			/* 먹이에 닿으면 먹이 수를 1 증가 후 출력 */
			item_cnt++;
			gotoxy(0,17);
			printf("먹은 먹이 수: %d", item_cnt);
		}

		/* 키값을 입력받음 */
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

		if (i % speed == 0) 
		{
			/* 지정된 좌표에 출력한 지렁이를 가림 */
			gotoxy(x,y);
			printf(" ");

			/* 지렁이 이동 (지렁이 변수 i가 5의 배수일 때마다 이동시킴) */
			if (dir == 0)          // 오른쪽
				x++;
			else if (dir == 1)     // 왼쪽
				x--;
			else if (dir == 2)     // 위쪽
				y--;
			else if (dir == 3)     // 아래쪽
				y++;

			/* 지정된 좌표에 지렁이를 출력 */
			gotoxy(x,y);
			printf("*");
		}

		i++;            // 매 반복마다 i를 증가
		Sleep(1000/20);	// 반복 속도 조절 (1초에 20번 반복)
	}
	
	/* 테두리에 닿아서 while문 빠져나오면 게임 오버 문구 출력 */
	gotoxy(10,7);
	printf("Game Over"); // 게임 오버 출력

	for (j=0 ; j<=4 ; j++)
	{
		gotoxy(5,10);
		printf("%d초 후에 종료됩니다.", 5-j); // 몇 초 남았는지 출력
		Sleep(1000); // 1초간 휴식
	}

	return 0;

}
