#ifndef _NPC_H
#define _NPC_H
class OseroNPC
{
public:
	//’u‚¯‚éêŠ‚ÌÌ“_‚ğ‚·‚éŠÖ”
	void Scoring(int BW,int count);
	//‹î‚ğ’u‚­ŠÖ”
	void SetPlace(int BW);
protected:
	double NPCPiece[8][8];
};
#endif // !_NPC_H
