#ifndef _NPC_H
#define _NPC_H
class OseroNPC
{
public:
	//置ける場所の採点をする関数
	void Scoring(int BW,int count);
	//駒を置く関数
	void SetPlace(int BW);
protected:
	double NPCPiece[8][8];
};
#endif // !_NPC_H
