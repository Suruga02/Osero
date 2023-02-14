//DrawPlayerNameé¿ëïÇ©ÇÁ
#define _USE_MATH_DEFINES
#include"Func.h"
#include"DxLib.h"
#include"Piece.h"
#include<cmath>

//î’ç∂è„200,25 àÍï”50


void Osero::DrawGreenBack()
{
	DrawBox(0, 0, 800, 450, GetColor(50, 205, 50),true);
}

void Osero::DrawCursor()
{
	int Color = (isPlace(PosX, PosY, BW) == false) ? GetColor(255, 0, 0) ://íuÇØÇ»Ç¢Ç»ÇÁê‘
						 (BW == 1)           ? GetColor(169, 169, 169) ://éËî‘Ç™îíÇ»ÇÁñæÇÈÇ¢äDêF
											   GetColor(80, 80, 80);//çïÇ»ÇÁà√Ç¢äDêF
	int Cx = 200 + 50 * PosX, Cy = 25 + 50 * PosY;
	DrawBox(Cx, Cy, Cx + 50, Cy + 50, Color, true);
}

void Osero::DrawBoard()
{
	for (int i = 0; i <= 8; i++)
	{
		DrawLine(200 + 50 * i, 25, 200 + 50 * i, 425, GetColor(0, 0, 0), true);
		DrawLine(200, 25 + 50 * i, 600, 25 + 50 * i, GetColor(0, 0, 0), true);
	}
}

void Osero::DrawPoint()
{
	for (int i = 0; i < 4; i++)
	{
		DrawCircle(400 + 100 *sqrt(2) * cos(M_PI_4 + i * M_PI_2), 225 + 100 * sqrt(2) * sin(M_PI_4 + i * M_PI_2),5, GetColor(0, 0, 0), true, true);
	}
}



void Osero::DrawPiece(int Px, int Py, int PBW)
{
	int Co(0);
	switch (PBW)
	{
	case 0:
		return;
		break;
	case 1:
		Co = 255;
		break;
	case -1:
		Co = 0;
	}
	DrawCircle(225 + 50 * Px, 50 + 50 * Py, 20, GetColor(Co, Co, Co));
}


void Osero::DrawAllPiece()
{
	for (int x = 0; x < 8; x++){for (int y = 0; y < 8; y++){DrawPiece(x, y, Piece[x][y]);}}
}

void Osero::DrawHowOperation()
{
	int BL = GetColor(0, 0, 0);
	DrawString(10, 340, "OPERATION", BL);
	DrawString(10, 360, "MOVE : Å™Å©Å´Å®", BL);
	DrawString(10, 380, "PLACE: SPACE", BL);
	DrawString(10, 400, "SKIP : P", BL);
	DrawString(10, 420, "EXIT : ESCAPE", BL);
}

void Osero::DrawSituation()
{
	int B(0), W(0);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Piece[i][j] == -1) { B++; }
			if (Piece[i][j] == 1) { W++; }
		}
	}
	double BarX = B / static_cast<double>(B + W) * 800;
	BarX = static_cast<int>(BarX);
	DrawBox(0, 0, BarX, 10, GetColor(0, 0, 0), true);
	DrawBox(BarX, 0, 800, 10, GetColor(255, 255, 255), true);
}
/*ñv
void Osero::DrawName()
{
	player1 = new char[15];
	player2 = new char[15];
	if (GameMode == 0)
	{
		player1 = "Player White";
		player2 = "Player Black";
	}
	if (GameMode == 1)
	{
		if (PlayerCursor == 1)
		{
			player1 = "Player";
			player2 = "Oseron";
		}
		else
		{
			player2 = "Player";
			player1 = "Oseron";
		}
	}
	DrawString(5, 10, player1, GetColor(0, 0, 0));
	DrawString(600, 10, player2, GetColor(255, 255, 255));
	delete player1, player2;
}
*/
void Osero::DRAW()
{
	DrawGreenBack();
	DrawCursor();
	DrawBoard();
	DrawPoint();
	DrawHowOperation();
	DrawSituation();
	//DrawName();
	DrawAllPiece();
}