#pragma once

#include "Filereader.h"
class Encoder
{
public:
	void encode(const char* pixmapPath, Filereader& filereader);
	Encoder();
	~Encoder();
};
