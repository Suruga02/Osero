#ifndef _PIECE_H
#define _PIECE_H

//�I�Z���̋�̏����z�u���L������z��
extern int OriginalPiece[8][8];
//�Q�[�������ۂɍs���Ֆʂ��L������z��
extern int Piece[8][8];
//Piece�̏��������s���֐�
void PieceInit();
//�w�肳�ꂽ�}�X�ɋ��u�����Ƃ��ł��邩�m�F
bool isPlace(int x,int y,int BW);
//���u���֐�
void Place(int x, int y, int BW);
#endif // !_PIECE_H
