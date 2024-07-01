#include <DxLib.h>
int STRANGE=5, size = 25;
int Count = 0;

int Check(short int x, short int y,short int dx,short int dy,short int color, short int mas[10][10],short int count)
{
	x += dx;
	y += dy;
	if (mas[x][y] == 0 || (mas[x][y] == color && count == 0) )return 0;
	else {
		if (mas[x][y] == color )return count;
		return Check(x, y, dx, dy, color, mas, count + 1);
	}
}

int ccheck(short int x, short int y,short int T, short int mas[10][10]) {
	int L=0;
	for (short int i = -1; i < 2;i++) {
		for (short int j = -1; j < 2; j++) {
			if(i!=0||j!=0)
				L += Check(x, y, i, j, T, mas,0);
		}
	}
	return L;
}

int rCheck(short int x, short int y, short int dx, short int dy, short int color, short int mas[10][10], short int count)
{
	short int L;
	x += dx;
	y += dy;
	if (mas[x][y] == 0 || (mas[x][y] == color && count == 0))return 0;
	else {
		if (mas[x][y] == color)return 1;
		else {
			L = rCheck(x, y, dx, dy, color, mas, count + 1);
			if (L == 1) mas[x][y] = color;
			return L;
		}
		
	}
}

void creverse(short int x, short int y, short int T, short int mas[10][10])
{
	mas[x][y] = T;
	//int i, j;
	for (short int i = -1; i < 2; i++) {
		for (short int j = -1; j < 2; j++) {
			if (i != 0 || j != 0)
				 rCheck(x, y, i, j, T, mas, 0);
		}
	}
}

void lcopy(short int mas[10][10], short int mas2[10][10])
{
	//short int i, j;
	for (short int i = 0; i < 10; i++) {
		for (short int j = 0; j < 10; j++) {
			mas2[i][j] = mas[i][j];
		}
	}

}

int lcheck( short int turn,short int mas[10][10],short int count) 
{
	short int  L, m_point = -100, mas2[10][10];
	Count++;
	for (short int i = 1; i < 9; i++) {
		for (short int j = 1; j < 9; j++) {
			if (mas[i][j] == 0) {
				L = ccheck(i, j, turn, mas);
				if (L != 0) {
					lcopy(mas, mas2);
					creverse(i, j, turn, mas2);
					if (count + 1 < STRANGE) {
						L -= lcheck(-turn, mas2, count + 1);
					}
					if (m_point < L) {
						m_point = L;
					}
				}
			}
		}
	}
	if (m_point == -100)
		return 0;
	else
		return m_point;
}

int lcheck0(short int turn, short int mas[10][10], short int count)
{
	Count = 0;
	short int i, j, L, m_point = -100, where = -1, mas2[10][10];
	unsigned int C = GetColor(255, 255, 255);
	for (i = 1; i < 9; i++) {
		DrawLine(size, size * 17 + 10, i * size*2+10 , size * 17 + 10, C, 4);
		ScreenFlip();
		for (j = 1; j < 9; j++) {
			//DrawLine(size * 17 + 10, size * 17 + 10, i * size +j, size * 17 + 10, C, 4);
			//ScreenFlip();
			if (mas[i][j] == 0) {
				L = ccheck(i, j, turn, mas);
				if (L != 0) {
					lcopy(mas, mas2);
					creverse(i, j, turn, mas2);
					L -= lcheck(-turn, mas2, count + 1);
					if (m_point < L) {
						m_point = L;
						where = i * 100 + j;
					}
				}
			}
		}
	}
	if (count == 0)
		return where;
}



int DROW(short int mas[10][10],short int check[10][10])
{
	int i, j, flag_b = 0, flag_w = 0;
	unsigned int C;
	ClearDrawScreen();
	

	C = GetColor(255, 255, 255);
	DrawLine(size, +size, size * 17 + 8, size, C);
	DrawLine(size, size, size, size * 17 + 8, C);
	for (i = 1; i < 9; i++) {
		C = GetColor(255, 255, 255);
		DrawLine(i * (size * 2 + 1) + size, size, i * (size * 2 + 1) + size, size * 17 + 8, C);
		DrawLine(size, i * (size * 2 + 1) + size, size * 17 + 8, i * (size * 2 + 1) + size, C);
		for (j = 1; j < 9; j++) {
			C = GetColor(255, 255, 255);
			if (mas[i][j] != 0) {
				if (mas[i][j] != 1) {
					C = GetColor(70, 70, 70);
					flag_w += 1;
				}
				else {
					
					flag_b += 1;
				}
				DrawCircle(i * (size * 2 + 1), j * (size * 2 + 1), size -1, C, 1);
			}
			else
				if (check[i][j] != 0)
					DrawCircle(i * (size * 2 + 1), j * (size * 2 + 1), size /2, C, 0);
		}
	}
	DrawFormatString(200, 400, C, "%d\n", Count);
	ScreenFlip();
	if (flag_w + flag_b == 64||flag_w==0||flag_b==0) {
		if (flag_b > flag_w)
			return 1;
		else return -1;
	}
	else
		return 0;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//初期化
	short int mas[10][10], check[10][10], i, j, turn, does, mode,CCHECK;
	int MouseX, MouseY;
	unsigned int C = GetColor(255, 255, 255);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			mas[i][j] = 0;
			check[i][j] = 0;
		}
	}
	mas[4][4] = 1;
	mas[4][5] = -1;
	mas[5][4] = -1;
	mas[5][5] = 1;
	SetDrawScreen(DX_SCREEN_BACK);



	//select mode
	does = 1;
	C = GetColor(255, 255, 255);
	DrawBox(size, size, size * 4 - 5, size * 4, C, 1);
	C = GetColor(55, 55, 55);
	DrawFormatString(size * 1.5, size * 1.5, C, "PLAYER\n  VS\n  CPU");
	DrawBox(size * 4 + 5, size, size * 7, size * 4, C, 1);
	C = GetColor(255, 255, 255);
	DrawFormatString(size * 4, size * 1.5, C, "   CPU\n   VS\n   CPU");
	ScreenFlip();
	while (does == 1) {
		WaitKey();				// キー入力待ち
		GetMousePoint(&MouseX, &MouseY);
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 &&
			((size < MouseX && MouseX < size * 4 - 5 && size < MouseY && MouseY < size * 4)
				|| (size * 4 + 5 < MouseX && MouseX < size * 7 && size < MouseY && MouseY < size * 4)))
			does = 0;
	}
	if (MouseX < size * 4) {
		mode = 1;
	}
	else mode = 2;
	while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) { WaitTimer(1); }
	does = 1;//select LEVEL OF CPU
	while (does == 1) {
		ClearDrawScreen();
		C = GetColor(255, 255, 255);
		DrawFormatString(size, size, C, "SELECT LEVEL OF CPU");
		DrawFormatString(size, size * 2.2, C, "       %d", STRANGE);
		DrawTriangle(size * 1.5, size * 2.5, size * 2, size * 2, size * 2, size * 3, C, TRUE);
		DrawTriangle(size * 6.5, size * 2.5, size * 6, size * 2, size * 6, size * 3, C, TRUE);
		DrawBox(size * 2.5, size * 3.5, size * 5.5, size * 5, C, 1);
		C = GetColor(0, 0, 0);
		DrawFormatString(size * 3, size * 4, C, "START");
		ScreenFlip();

		
		//while ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) { WaitTimer(1); }
		WaitKey();				// キー入力待ち
		GetMousePoint(&MouseX, &MouseY);
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 &&
			((size * 1.5 < MouseX && MouseX < size * 2 && size * 2 < MouseY && MouseY < size * 3)) && 1 < STRANGE) {
			STRANGE--;
			//WaitTimer(300);
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 &&
			((size * 6 < MouseX && MouseX < size * 6.5 && size * 2 < MouseY && MouseY < size * 3)) && STRANGE<12) {
			STRANGE++;
			//WaitTimer(300);
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 &&
			((size * 2.5 < MouseX && MouseX < size * 5.5 && size * 3.5 < MouseY && MouseY < size * 5.5))) {
			does = 0;
			//WaitTimer(300);
		}
		//WaitTimer(1);
		//while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) { WaitTimer(1); }
		
	}

	// 先手後手
	if (mode == 1) {
		ClearDrawScreen();
		C = GetColor(255, 255, 255);
		DrawBox(size, size, size * 4 - 5, size * 4, C, 1);
		C = GetColor(55, 55, 55);
		DrawFormatString(size * 1.5, size * 2.2, C, "先手");
		DrawBox(size * 4 + 5, size, size * 7, size * 4, C, 1);
		C = GetColor(255, 255, 255);
		DrawFormatString(size * 4.5, size * 2.2, C, "後手");
		ScreenFlip();
		does = 1;
		while (does == 1) {
			WaitKey();				// キー入力待ち
			GetMousePoint(&MouseX, &MouseY);
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 &&
				((size < MouseX && MouseX < size * 4 - 5 && size < MouseY && MouseY < size * 4)
					|| (size * 4 + 5 < MouseX && MouseX < size * 7 && size < MouseY && MouseY < size * 4)))
				does = 0;
		}
		if (MouseX < size * 4) {
			turn = -1;
		}
		else turn = 1;
	}
	else
		turn = -1;
	does = 0;
	//ループ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	while (does == 0 && CheckHitKey(KEY_INPUT_0)!=1) {
		CCHECK = 0;
		for (i = 1; i < 9; i++) {
			for (j = 1; j < 9; j++) {
				if (mas[i][j] == 0) {
					check[i][j] = ccheck(i, j, -turn, mas);
					if (check[i][j] != 0)
						CCHECK = 1;
				}
			}
		}

		//drow and judge

		does = DROW(mas, check);
		if (does != 0)break;
		else {
			C = GetColor(255, 255, 255);
			if (mode == 2 || (mode == 1 && turn == 1))DrawFormatString(size, size*18, C, "Press any key");
			ScreenFlip();
		}

		WaitKey();				// キー入力待ち
		turn *= -1;
		if (CCHECK == 1) {
			if (mode == 2 || (mode == 1 && turn == -1)) {    //CPU
				i = lcheck0(turn, mas, 0);
				
				if (i != -1)
					creverse(int(i / 100), i % 100, turn, mas);
				else {
					DrawFormatString(200, 200, C, "PASS");
					ScreenFlip();
				}
			}
			else {											//PLAYER
				i = 4;  j = 4;
				while (mas[i][j] != 0 || check[i][j] == 0) {
					if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
					{
						GetMousePoint(&MouseX, &MouseY);
						i = int((MouseX - size) / (size * 2)) + 1;
						j = int((MouseY - size) / (size * 2)) + 1;
					}
				}
				creverse(i, j, turn, mas);
			}
		}
		else {
			DrawFormatString(200, 200, C, "PASS");
			ScreenFlip();
		}
		
	}
	does = DROW(mas, check);
	//finish
	if(does<0)
		DrawFormatString(200, 500, C, "BRACK");
	else
		DrawFormatString(200, 500, C, "WHITE");
	ScreenFlip();
	WaitKey();				// キー入力待ち
	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}