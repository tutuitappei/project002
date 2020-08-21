#pragma once
#include<map>
#include"../Vector2.h"
#include"../input/Inputid.h"

enum class PuyoID
{
	Non,
	Red,
	Blue,
	Green,
	Yellow,
	Purpule,
	Ojama,
	Wall,
	MAX
};

struct DirBit
{
	unsigned int up : 1;
	unsigned int down : 1;
	unsigned int left : 1;
	unsigned int right : 1;
};

union Dirpermit
{
	DirBit perBit;
	unsigned int per;

};

using Puyocolor = std::map<PuyoID, int>;

class Puyo
{
public:
	Puyo(Vector2 vec, PuyoID id);
	~Puyo();
	void Move(InputID id);
	void Draw(void);
	bool SoftDrop(void);
	bool Updata(void);

	bool SetDirParmit(Dirpermit dirparmit);

	PuyoID GetID(void);
	const Vector2 GetGrid(int size);

private:
	static Puyocolor _puyocolor;		//Ç’ÇÊÇÃêF

	Dirpermit _olddirparmit;
	Dirpermit _dirparmit;

	Vector2 _size;
	Vector2 _pos;
	PuyoID _id;

	int _dropcnt;
	int _dropinter;
	int _dropspeed;
};


