#ifndef _NPC_H
#define _NPC_H
class OseroNPC
{
public:
	//�u����ꏊ�̍̓_������֐�
	void Scoring(int BW,int count);
	//���u���֐�
	void SetPlace(int BW);
protected:
	double NPCPiece[8][8];
};
#endif // !_NPC_H
