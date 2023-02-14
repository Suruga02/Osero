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

//���̕ӎO�p�֐���for���ŏ�����������
bool isPlace(int x, int y, int BW)
{
	if (Piece[x][y] != 0)return false;//���łɋ�u����Ă���Ƃ���ɂ͐ݒu�ł��Ȃ�
	int X = x, Y = y;
	while (X < 6 && Piece[++X][Y] == -BW)
	{
		if (Piece[X + 1][Y] == BW) 
		{
			return true;
			break;//����Ȃ�?
		}
	}	//����̋�����߂�Ƃ���ɂ͒u����
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
	return false; //��L�Œu����Ɣ��f����Ȃ������Ƃ���͂���Ȃ��u���Ȃ�
}

void Place(int x, int y, int BW)
{
	if (isPlace(x, y, BW) == false)return;//�I�����ꂽ�}�X���{���ɋ�������邩�m�F
	Piece[x][y] = BW;//�I�����ꂽ�}�X�ɋ��ݒu
	int X = x, Y = y;
	int R;

	//�_���֌W�͈ȉ��̂悤�ɂȂ��Ă���@�c���΂̂W�����ɂ����ē��l�̏������s��

	while (X < 6 && Piece[++X][Y] == -BW) //�ݒu�ʒu�����������ɕ���ł��鑊��̋�̒[�܂Ŕ��
	{

		if (Piece[X + 1][Y] == BW)//����̋�̒[�ׂ̗Ɏ����̋����ł��邩���ׂ�
		{

			for (R = x + 1; R <= X; R++)//���܂�Ă����������̋�ɒu��������
			{
				Piece[R][Y] = BW;
			}
			break;//�]�v�ȓ�������Ȃ��悤�Ƀ��[�v�̒E�o
		}
	}
	X = x;//���[�v�œ��������ϐ���������
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