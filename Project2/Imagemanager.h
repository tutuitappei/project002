#pragma once
#include<map>
#include"ImageID.h"

using Tbl = std::map<ImageID, char>;

class Imagemanager
{
public:
	Imagemanager();
	~Imagemanager();
private:
	static Tbl _imageTble;
};

