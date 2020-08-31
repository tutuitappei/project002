#include<DxLib.h>
#include "Puyo.h"

Puyocolor Puyo::_puyocolor = {
    {PuyoID::Red,0xff0000},
    {PuyoID::Blue,0x0000ff},
    {PuyoID::Green,0x00ff00},
    {PuyoID::Yellow,0xffff00},
    {PuyoID::Purpule,0xff00ff},
    {PuyoID::Ojama,0xaaaaaa}
};

Puyo::Puyo(Vector2 vec, PuyoID id)
{
    _pos = vec;
    _size = { 32, 32 };
    _id = id;

    _dirparmit.per = 0;
    _olddirparmit.per = 0;

    _dropcnt = 0;
    _dropinter = 30;
    _dropspeed = 8;
}

Puyo::~Puyo()
{
}

void Puyo::Move(InputID id)
{
    switch (id)
    {
    case InputID::Up:
        //if (_dirparmit.perBit.up)
        //{
        //    _pos.y -= _size.y / 2;
        //}
        break;
    case InputID::Down:
        break;
    case InputID::Left:
        if (_dirparmit.perBit.left)
        {
            _pos.x -= _size.x;
        }
        break;
    case InputID::Right:
        if (_dirparmit.perBit.right)
        {
            _pos.x += _size.x;
        }
        break;
    case InputID::Btn1:
        break;
    case InputID::Btn2:
        break;
    default:
        break;
    }
}

void Puyo::Draw(void)
{
    DrawCircle(_pos.x, _pos.y, _size.x / 2, _puyocolor[_id], true);
    //DrawCircle(0, 0, 16, _puyocolor[_id],true);
}

bool Puyo::Updata(void)
{
    if (_dropcnt < _dropinter)
    {
        _dropcnt++;
        return false;
    }
    else
    {
        _pos.y += _dropspeed;
        _dropcnt = 0;
        return true;
    }
    return false;
}

bool Puyo::SetDirParmit(Dirpermit dirparmit)
{
    _olddirparmit = _dirparmit;
    _dirparmit = dirparmit;
    return true;
}

PuyoID Puyo::GetID(void)
{
    return PuyoID((rand() % (static_cast<int>(PuyoID::MAX) - 4)) + 1);
}

PuyoID Puyo::ReturnID(void)
{
    return _id;
}

const Vector2 Puyo::GetGrid(int size)
{
    return Vector2((_pos.x - size - size / 2) / size, (_pos.y - size / 2) / size);
}


bool Puyo::SoftDrop(void)
{
    _dropcnt += _dropinter;
    return false;
}
