#pragma once

#include "Filereader.h"
#include "Compressor.h"
class Encoder
{
public:
	void encode(const char* pixmapPath, Filereader& filereader, Compressor& compressor);
	Encoder();
	~Encoder();
};
