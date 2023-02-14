#include"DxLib.h"
#include"GameMode.h"
#include"Piece.h"
#include"Func.h"
#include"NPC.h"
//sleep�֐������p
#include<io.h>



static int HMenuBGM, HGameBGM, MHselect, MHenter, MHplace, MHfin;


int SelectMenu()
{
	MenuElement Select[4] = { {100,250,"�ΐl��"},{100,300,"NPC��"},{100,350,"�V�ѕ�"},{100,400,"��߂�"} };
	int SelectMenuCursor = 0;
	int NumOfChoices = 4;
	int SelectCount = 10;
	int FontHandle = CreateFontToHandle(NULL, 80, 8);
	HMenuBGM = LoadSoundMem("MenuBGM.mp3");
	HGameBGM = LoadSoundMem("MainGameBGM.mp3");
	MHselect = LoadSoundMem("MoveCursor.wav");
	MHenter = LoadSoundMem("Enter.wav");
	MHfin = LoadSoundMem("GameFin.wav");
	ChangeVolumeSoundMem(100, HMenuBGM);
	ChangeVolumeSoundMem(70, HGameBGM);
	ChangeVolumeSoundMem(100, MHenter);
	PlaySoundMem(HMenuBGM, DX_PLAYTYPE_LOOP);
	while (CheckHitKey(KEY_INPUT_SPACE)==0&&CheckHitKey(KEY_INPUT_RETURN)==0)
	{
		ClearDrawScreen();
		if (--SelectCount == 0)
		{
			switch (WS())
			{
			case -1:
				PlaySoundMem(MHselect, DX_PLAYTYPE_BACK);
				SelectMenuCursor += NumOfChoices - 1;
				break;
			case 0:
				break;
			case 1:
				PlaySoundMem(MHselect, DX_PLAYTYPE_BACK);
				SelectMenuCursor += 1;
			}
			SelectMenuCursor %= NumOfChoices;
			SelectCount = 5;
		}
		//��������Menu�̕\��
		//�I��\��
		for (int i = 0; i < NumOfChoices; i++)
		{
			int StringColor = (i == SelectMenuCursor)
				? GetColor(255, 255, 255)
				: GetColor(100, 100, 100);
			DrawFormatString(Select[i].SelX, Select[i].SelY, StringColor, Select[i].name);
		}
		DrawStringToHandle(100, 100, "OSERO", GetColor(255, 255, 255), FontHandle);
		DrawString(500, 400, "�Q�[���G���W��:DX���C�u����", GetColor(255, 255, 255));
		DrawString(500, 430, "�@ �T�E���h �@:������", GetColor(255, 255, 255));
		ScreenFlip();
	}
	PlaySoundMem(MHenter, DX_PLAYTYPE_BACK);
	return SelectMenuCursor;
}

void VSFriendGame()
{
	PieceInit();

	Osero* Rev = new Osero();

	StopSoundMem(HMenuBGM);


	PlaySoundMem(HGameBGM,DX_PLAYTYPE_LOOP);
	while (ProcessMessage() == 0)
	{
		Rev->Updata();
		//����ʏ���
		ClearDrawScreen();
		Rev->DRAW();
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) { PlaySoundMem(MHplace, DX_PLAYTYPE_BACK); }
		//����ʂ�\��ʂ����ւ���
		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || Rev->isGameEnd() == true)
		{
			StopSoundMem(HGameBGM);
			PlaySoundMem(MHfin,DX_PLAYTYPE_BACK);
			Rev->GameEnd();
			break;
		}
	}
	InitSoundMem();
	delete Rev;
}

void VSNPCGame()
{
	Osero* Rev = new Osero();
	OseroNPC* NPC = new OseroNPC();
	MenuElement Select[2] = { {250,250,"���:BLACK"},{ 400,250,"���:WHITE"} };
	int TurnCount(0);
	int SelectMenuCursor = 0;
	int NumOfChoices = 2;
	int SelectCount = 5;

	Sleep(200);
	while (!(CheckHitKey(KEY_INPUT_SPACE) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1))
	{
		ClearDrawScreen();
		if (--SelectCount == 0)
		{
				switch (AD())
				{
				case -1:
					PlaySoundMem(MHselect, DX_PLAYTYPE_BACK);
					SelectMenuCursor++;
					break;
				case 0:
					break;
				case 1:
					PlaySoundMem(MHselect, DX_PLAYTYPE_BACK);
					SelectMenuCursor++;
				}
			
			SelectMenuCursor %= NumOfChoices;
			SelectCount = 5;
		}
		//��������Menu�̕\��
		//�I��\��
		for (int i = 0; i < NumOfChoices; i++)
		{
			int StringColor = (i == SelectMenuCursor)? GetColor(255, 255, 255): GetColor(100, 100, 100);
			DrawString(325, 200, "�N�͔����ǂ����H", GetColor(255, 255, 255));
			DrawFormatString(Select[i].SelX, Select[i].SelY, StringColor, Select[i].name);
		}
		DrawFormatString(275, 300, GetColor(255,255,255), "HIT SPACE TO START GAME!!");
		ScreenFlip();
	}
	PlaySoundMem(MHenter, DX_PLAYTYPE_BACK);
	StopSoundMem(HMenuBGM);
	


	PlaySoundMem(HGameBGM, DX_PLAYTYPE_LOOP);
	PieceInit();
	Rev->DRAW();
	ScreenFlip();
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();

		if ((SelectMenuCursor == 0&& Rev->GetBW()==-1)||(SelectMenuCursor==1&&Rev->GetBW()==1))
		{
			Rev->Updata();
			if (CheckHitKey(KEY_INPUT_SPACE) == true) { TurnCount++; }
			PlaySoundMem(MHplace, DX_PLAYTYPE_BACK);
		}
		else
		{
			Sleep(500);
			TurnCount++;
			PlaySoundMem(MHplace, DX_PLAYTYPE_BACK);
			NPC->Scoring(Rev->GetBW(), TurnCount);
			NPC->SetPlace(Rev->GetBW());
			Rev->SetBW(-Rev->GetBW());
		}
		//����ʂ�\��ʂ����ւ���
		Rev->DRAW();
		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || Rev->isGameEnd() == true)
		{
			StopSoundMem(HGameBGM);
			PlaySoundMem(MHfin,DX_PLAYTYPE_BACK);
			Rev->GameEnd();
			break;
		}
	}
	InitSoundMem();
	delete Rev;
	delete NPC;
}

void HowPlay()
{
	int timer(50);
	int TitleFontHandle = CreateFontToHandle(NULL, 50, 8);
	while (ProcessMessage() == 0)
	{
		timer = (timer <= 0) ? 0 : timer - 1;
		if (CheckHitKeyAll() != 0 && timer == 0) { break; }
		ClearDrawScreen();
		DrawStringToHandle(10, 10, "���[��", GetColor(255, 255, 255), TitleFontHandle);
		DrawString(20, 100, "�o���u���Ȃ��Ȃ�܂ő���̋�����񂾂Ƃ���Ɍ��ŋ��u���Ă�����", GetColor(255, 255, 255));
		DrawString(20, 130, "�Ō�ɋ�̑��������l���������I", GetColor(255, 255, 255));
		DrawString(20, 160, "���͍�", GetColor(255, 255, 255));
		DrawString(20, 190, "�u����ꏊ���Ȃ��Ȃ�����p�X���ł���悤�ɂȂ邼", GetColor(255, 255, 255));
		ScreenFlip();
	}
	StopSoundMem(HMenuBGM);
	InitSoundMem();
}