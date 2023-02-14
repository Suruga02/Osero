#include"Piece.h"

int OriginalPiece[8][8] =
{
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,1,-1,0,0,0},
	{0,0,0,-1,1,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};
int Piece[8][8]=
{
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,1,-1,0,0,0},
	{0,0,0,-1,1,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

void PieceInit()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece[i][j] = OriginalPiece[i][j];
		}
	}
}

//この辺三角関数とfor文で書き直したい
bool isPlace(int x, int y, int BW)
{
	if (Piece[x][y] != 0)return false;//すでに駒が置かれているところには設置できない
	int X = x, Y = y;
	while (X < 6 && Piece[++X][Y] == -BW)
	{
		if (Piece[X + 1][Y] == BW) 
		{
			return true;
			break;//いらない?
		}
	}	//相手の駒を挟めるところには置ける
	X = x;
	while (X > 1 && Piece[--X][Y] == -BW) { if (Piece[X - 1][Y] == BW) { return true; break; } }
	X = x;
	while (Y < 6 && Piece[X][++Y] == -BW) { if (Piece[X][Y + 1] == BW) { return true; break; } }
	Y = y;
	while (Y > 1 && Piece[X][--Y] == -BW) { if (Piece[X][Y - 1] == BW) { return true; break; } }
	Y = y;
	while (X < 6 && Y < 6 && Piece[++X][++Y] == -BW) { if (Piece[X + 1][Y + 1] == BW) { return true; break; } }
	X = x, Y = y;
	while (X < 6 && Y > 1 && Piece[++X][--Y] == -BW) { if (Piece[X + 1][Y - 1] == BW) { return true; break; } }
	X = x, Y = y;
	while (X > 1 && Y < 6 && Piece[--X][++Y] == -BW) { if (Piece[X - 1][Y + 1] == BW) { return true; break; } }
	X = x, Y = y;
	while (X > 1 && Y > 1 && Piece[--X][--Y] == -BW) { if (Piece[X - 1][Y - 1] == BW) { return true; break; } }
	X = x, Y = y;
	return false; //上記で置けると判断されなかったところはもれなく置けない
}

void Place(int x, int y, int BW)
{
	if (isPlace(x, y, BW) == false)return;//選択されたマスが本当に駒をおけるか確認
	Piece[x][y] = BW;//選択されたマスに駒を設置
	int X = x, Y = y;
	int R;

	//論理関係は以下のようになっている　縦横斜の８方向において同様の処理を行う

	while (X < 6 && Piece[++X][Y] == -BW) //設置位置から特定方向に並んでいる相手の駒の端まで飛ぶ
	{

		if (Piece[X + 1][Y] == BW)//相手の駒の端の隣に自分の駒が並んでいるか調べる
		{

			for (R = x + 1; R <= X; R++)//挟まれている駒を自分の駒に置き換える
			{
				Piece[R][Y] = BW;
			}
			break;//余計な動作をしないようにループの脱出
		}
	}
	X = x;//ループで動かした変数を初期化
	while (X > 1 && Piece[--X][Y] == -BW) { if (Piece[X - 1][Y] == BW) { for (R = X; R < x; R++) { Piece[R][Y] = BW; } break; } }
	X = x;
	while (Y < 6 && Piece[X][++Y] == -BW) { if (Piece[X][Y + 1] == BW) { for (R = y + 1; R <= Y; R++) { Piece[X][R] = BW; } break; } }
	Y = y;
	while (Y > 1 && Piece[X][--Y] == -BW) { if (Piece[X][Y - 1] == BW) { for (R = Y; R < y; R++) { Piece[X][R] = BW; } break; } }
	Y = y;
	while (X < 6 && Y < 6 && Piece[++X][++Y] == -BW) { if (Piece[X + 1][Y + 1] == BW) { for (R = 1; R <= X - x; R++) { Piece[x + R][y + R] = BW; } break; } }
	X = x, Y = y;
	while (X < 6 && Y > 1 && Piece[++X][--Y] == -BW) { if (Piece[X + 1][Y - 1] == BW) { for (R = 1; R <= X - x; R++) { Piece[x + R][y - R] = BW; } break; } }
	X = x, Y = y;
	while (X > 1 && Y < 6 && Piece[--X][++Y] == -BW) { if (Piece[X - 1][Y + 1] == BW) { for (R = 1; R <= x - X; R++) { Piece[x - R][y + R] = BW; } break; } }
	X = x, Y = y;
	while (X > 1 && Y > 1 && Piece[--X][--Y] == -BW) { if (Piece[X - 1][Y - 1] == BW) { for (R = 1; R <= x - X; R++) { Piece[x - R][y - R] = BW; } break; } }
	X = x, Y = y;
}