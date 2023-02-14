#include"Func.h"
#include"DxLib.h"
#include"Piece.h"

Osero::Osero():PosX(0), PosY(0), SelectCount(10),BW(-1) {}

int InK()
{
	return GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
int AD()
{
	if (InK() & PAD_INPUT_LEFT || InK() & PAD_INPUT_4)return -1;
	if (InK() & PAD_INPUT_RIGHT || InK() & PAD_INPUT_6)return 1;
	return 0;
}
int WS()
{
	if (InK() & PAD_INPUT_UP || InK() & PAD_INPUT_8)return -1;
	if (InK() & PAD_INPUT_DOWN || InK() & PAD_INPUT_5)return 1;
	return 0;
}

void Osero::SetPiece()
{
	if (CheckHitKey(KEY_INPUT_SPACE) == true&&isPlace(PosX,PosY,BW)==true)
	{
		Place(PosX, PosY, BW);
		BW *= -1;
	}
}

void Osero::Updata()
{
	if (--SelectCount == 0)
	{
		PassTurn();
		PosX = (PosX + AD()) < 0 ? 0 :
			(PosX + AD()) > 7 ? 7 :
			PosX + AD();
		PosY = (PosY + WS()) < 0 ? 0 :
			(PosY + WS()) > 7 ? 7 :
			PosY + WS();
		SetPiece();
		SelectCount = 7;
	}
}