#define _USE_MATH_DEFINES
#include"NPC.h"
#include"Piece.h"
#include<cmath>


//まだ弱い
void OseroNPC::Scoring(int BW, int count)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//点数版初期化
			NPCPiece[i][j] = 0;
			//採点時の盤面保存用配列(一手先)
			int JudgeBoard1[8][8];
			//採点時の盤面保存用配列(二手先)
			int JudgeBoard2[8][8];
			//相手のおける場所をカウント
			int IsPlaceCount1(0);
			//開放度 
			int FreeCount(0);
			double Weight(1.);
			if (isPlace(i, j, BW) == true)
			{
				//盤面の保存
				for (int k = 0; k < 8; k++) { for (int l = 0; l < 8; l++) { JudgeBoard1[k][l] = Piece[k][l]; } }
				//全マスに置いたときの一手先の仮盤面から採点
				Place(i, j, BW);
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						//相手のおける場所の数を保存
						if (isPlace(k, l, -BW) == true) { IsPlaceCount1++; }
						if ((Piece[k][l] - JudgeBoard1[k][l]) != 0)
						{
							//開放度の計算
							int kp = (k + 1) < 8 ? k + 1 : k, km = (k - 1) < 0 ? k : k - 1, lp = (l + 1) < 8 ? l + 1 : l, lm = (l - 1) < 0 ? l : l - 1;
							if (JudgeBoard1[kp][l] == 0) { FreeCount++; }
							if (JudgeBoard1[km][l] == 0) { FreeCount++; }
							if (JudgeBoard1[k][lp] == 0) { FreeCount++; }
							if (JudgeBoard1[k][lm] == 0) { FreeCount++; }
							if (JudgeBoard1[kp][lp] == 0) { FreeCount++; }
							if (JudgeBoard1[kp][lm] == 0) { FreeCount++; }
							if (JudgeBoard1[km][lp] == 0) { FreeCount++; }
							if (JudgeBoard1[km][lm] == 0) { FreeCount++; }
							//淵を裏返せるなら加点
							if (k == 0) { Weight *= 1.5; }
							if (k == 7) { Weight *= 1.5; }
							if (l == 0) { Weight *= 1.5; }
							if (l == 7) { Weight *= 1.5; }
							//角を取れたら中加点
							if ((k == 0 || k == 7) && (l == 0 || l == 7)) { Weight *= 1.e10; }
							//対角線は中心に近いほど加点
							if (k == l || (k + l) == 7) { Weight *= (2 - cos((2 * k + 1) / 8. * M_PI)); }
							//空いている角の周りに置きたくない(角0かつ周りの差分アリなら減点)
							if (JudgeBoard1[0][0] == 0 && ((k == 1 && l < 2) || (l == 1 || k < 2))) { Weight /= 1.e5; }
							if (JudgeBoard1[0][7] == 0 && ((k == 6 && l < 2) || (l == 1 || k > 5))) { Weight /= 1.e5; }
							if (JudgeBoard1[7][0] == 0 && ((k == 1 && l > 5) || (l == 6 || k < 2))) { Weight /= 1.e5; }
							if (JudgeBoard1[7][7] == 0 && ((k == 6 && l > 5) || (l == 6 || k > 5))) { Weight /= 1.e5; }
						}
						//角にはおかれたくない　重減点
						if ((k == 0 || k == 7) && (l == 0 || l == 7) && isPlace(k, l, -BW) == true) { Weight /= 1.e20; }
						//もう一手先を読むループ実装
						if (isPlace(k, l, -BW) == true)
						{
							//盤面の保存
							for (int m = 0; m < 8; m++) { for (int n = 0; n < 8; n++) { JudgeBoard2[m][n] = Piece[m][n]; } }
							//全マスに置いたときの一手先の仮盤面から採点
							Place(k, l, -BW);
							int isPlaceCount2(0);
							for (int m = 0; m < 8; m++)
							{
								for (int n = 0; n < 8; n++)
								{
									if ((Piece[m][n] - JudgeBoard2[m][n]) != 0)
									{
										//淵を裏返されるなら減点
										if (m == 0) { Weight /= 5.; }
										if (m == 7) { Weight /= 5.; }
										if (n == 0) { Weight /= 5.; }
										if (n == 7) { Weight /= 5.; }
										//角を取れるなら加点
										if ((m == 0 || m == 7) && (n == 0 || n == 7)&&isPlace(m,n,BW==true)) { Weight *= 2.; }
									}
									if (isPlace(m, n, BW) == true) { isPlaceCount2++; }
								}
							}
							//置ける場所がなくなるなら減点大
							if (isPlaceCount2 == 0) { Weight /= 1.e20; }
							//盤面をもとに戻す
							for (int m = 0; m < 8; m++) { for (int n = 0; n < 8; n++) { Piece[m][n] = JudgeBoard2[m][n]; } }
						}
					}
					//相手に淵に置かれる場所は点数を低く
					if (isPlace(0, k, -BW) == true) { Weight /= 3.; }
					if (isPlace(7, k, -BW) == true) { Weight /= 3.; }
					if (isPlace(k, 0, -BW) == true) { Weight /= 3.; }
					if (isPlace(k, 7, -BW) == true) { Weight /= 3.; }
				}
				//仮想的に変異させた盤面を元に戻す
				for (int k = 0; k < 8; k++) { for (int l = 0; l < 8; l++) { Piece[k][l] = JudgeBoard1[k][l]; } }
				NPCPiece[i][j] = (4 * exp(1 - FreeCount / 2.) + exp(1 - IsPlaceCount1 / 2.)) * Weight;
			}
		}
	}
}

void OseroNPC::SetPlace(int BW)
{
	int MaxI(0), MaxJ(0);
	double MaxScore(0);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (NPCPiece[i][j] > MaxScore)
			{
				MaxI = i;
				MaxJ = j;
				MaxScore = NPCPiece[i][j];
			}
		}
	}
	if (isPlace(MaxI, MaxJ, BW) == true) { Place(MaxI, MaxJ, BW); }
}