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
	void SetInterval(int intr);
	void Draw(void);
	bool alive(void);
	void alive(bool alive);
	bool SoftDrop(void);
	bool Downnow(void);
	bool Updata(void);
	bool CheckPuyon(void);
	bool SetDirParmit(Dirpermit dirparmit);

	Dirpermit DirPermit(void);

	PuyoID GetID(void);
	PuyoID ReturnID(void);
	const Vector2 GetGrid(int size);
	void pos(Vector2& vec);

	const Vector2& pos(void) const;

private:

	static Puyocolor _puyocolor;		//�Ղ�̐F

	Dirpermit _olddirparmit;
	Dirpermit _dirparmit;

	Vector2 _size;
	Vector2 _pos;
	PuyoID _id;

	bool _alive;

	int _dropcnt;
	int _dropinter;
	int _dropspeed;
};


