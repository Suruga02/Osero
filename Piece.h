#ifndef _PIECE_H
#define _PIECE_H

//オセロの駒の初期配置を記憶する配列
extern int OriginalPiece[8][8];
//ゲームを実際に行う盤面を記憶する配列
extern int Piece[8][8];
//Pieceの初期化を行う関数
void PieceInit();
//指定されたマスに駒を置くことができるか確認
bool isPlace(int x,int y,int BW);
//駒を置く関数
void Place(int x, int y, int BW);
#endif // !_PIECE_H
