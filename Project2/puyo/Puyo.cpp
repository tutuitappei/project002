#include<DxLib.h>
#include "Puyo.h"

Puyo::Puyo(Vector2 vec, PuyoID id)
{
    _pos = vec;
    _size = { 32, 32 };
    _id = id;

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
        _pos.y -= _size.y;
        break;
    case InputID::Down:
        break;
    case InputID::Left:
        _pos.x -= _size.x;
        break;
    case InputID::Right:
        _pos.x += _size.x;
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
    //if ()
    //{

    //}

    return true;
}

PuyoID Puyo::GetID(void)
{
    return PuyoID((rand() % (static_cast<int>(PuyoID::MAX) - 3)) + 1);
}

const Vector2 Puyo::GetGrid(int size)
{
    return Vector2((_pos.x - size / 2) / size, (_pos.y - size / 2) / size);
}


bool Puyo::SoftDrop(void)
{
    _dropcnt += _dropinter;
    return false;
}
