#include"Func.h"
#include"DxLib.h"
#include"Piece.h"


void Osero::PassTurn()
{
	int isPassCount(0);
	for (int i = 0; i < 8; i++)	 
	{
		for (int j = 0; j < 8; j++)
		{
			if (isPlace(i, j, BW) == true)
			{
				isPassCount++; 
			}
		}
	}
	if (isPassCount==0&& CheckHitKey(KEY_INPUT_P) == 1){BW *= -1;}
}

bool Osero::isGameEnd()
{
	int BWCount(0), ZeroCount(0), VSisPlaceCount(0);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (isPlace(i, j, BW) == true) { return false; }
			if (isPlace(i, j, -BW) == true) { VSisPlaceCount++; }
			if (Piece[i][j] == 0) { ZeroCount++; }
			if (Piece[i][j] == BW) { BWCount++; }
		}
	}
	if (BWCount==0||ZeroCount==0||VSisPlaceCount==0)
	{
		return true;
	}
	return false;
}

void Osero::GameEnd()
{
	int BCount(0), WCount(0);
	Winner WinArg;
	Winner White = { GetColor(255,255,255),"WHITE" };
	Winner Black = { GetColor(0,0,0),"BLACK" };
	Winner Draw = { GetColor(128,128,128),"DRAW" };
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int P = Piece[i][j];
			WCount += (P == 1) ? 1 : 0;
			BCount += (P == -1) ? 1 : 0;
		}
	}
	if (WCount > BCount) { WinArg = White; }
	if (WCount < BCount) { WinArg = Black; }
	if (WCount == BCount) { WinArg = Draw; }

	int FontHandle = CreateFontToHandle(NULL, 80, 8);
	DrawBox(0, 0, 800, 450, GetColor(0, 255, 0),true);
	DrawStringToHandle(200, 130, "Game End!!", GetColor(255, 0, 0), FontHandle);
	WaitTimer(500);
//	DrawFormatString(0, 0, GetColor(0, 0, 0), "%d,%d", WCount, BCount);
	DrawStringToHandle(260, 200, "WINNER", GetColor(255, 0, 0), FontHandle);
	WaitTimer(1000);
	DrawStringToHandle(300,270, WinArg.Name, WinArg.Color, FontHandle);
	WaitTimer(2000);
	CheckHitKeyAll();
}
void Osero::SetBW(int NewBW) { BW = NewBW; }
int Osero::GetBW() { return BW; }
//void Osero::SetGameMode(int GM, int PC) { GameMode = GM; PlayerCursor = PC; }