#pragma once
#include<vector>
#include<memory>
#include<functional>
#include<list>
#include"Vector2.h"
#include"input/Controller.h"
#include"PlayUnit.h"
#include"puyo/Puyo.h"


#define STAGE_MAP_X 8
#define STAGE_MAP_Y 14

class PlayUnit;
struct Dorop;
struct Elase;
struct Puyon;
struct Munyon;
struct Fall;
struct Ojamamode;


enum class StgMode
{
	DROP,
	PUYON,
	ERASE,
	MOVE,
	MUNYON,
	OJAMA,
	MAX
};

using Sharepuyo = std::shared_ptr<Puyo>;
using Unipuyo = std::unique_ptr<Puyo>;

class Stage
{
public:
	Stage();
	Stage(Vector2&& offset, Vector2&& size);
	~Stage();


	bool GameOver(void);
	bool DownMode(void);

	void GetStageDraw(void);
	void Draw(void);
	void Updata(void);
private:
	bool Init(void);
	bool InstancePuyo(void);
	bool OjamaInstance(void);
	bool SetWall(void);
	bool EleseData(PuyoID id, Vector2 vec);
	bool Movepuyo(Sharepuyo& puyo);
	bool GameOverChack(void);

	void Deletopuyo(void);

	int GetStageID(void);

	int _screenID;
	Vector2 _offset;
	Vector2 _size;

	StgMode _stgmode;

	Unipuyo puyo;
	std::vector<Sharepuyo> puyoVec;

	std::unique_ptr<Controller> controller;
	std::unique_ptr<PlayUnit> _playunit;

	std::vector<Sharepuyo*> _data;
	std::vector<Sharepuyo> _dataBase;
	std::vector<Sharepuyo*> _erasedata;
	std::vector<Sharepuyo> _erasedataBase;

	std::list<Sharepuyo> OjamaList;

	std::map<StgMode, std::function<bool(Stage&)>> _stagetype;

	//std::vector<int*> _data;
	//std::vector<int> _dataBase;
	//std::vector<int*> _erasedataBase;

	int _blocksize;
	int count;

	static int _stagecount;
	int _id;
	int _color;

	int _maxrensa;
	int _rensa;
	int _erasenum;
	int _ojamanum;

	bool _ojamaflag;
	bool _gameoverflag;
	bool _downFlag;

	friend PlayUnit;
	friend Dorop;
	friend Elase;
	friend Munyon;
	friend Puyon;
	friend Fall;
	friend Ojamamode;
};

