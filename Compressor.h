#pragma once
#include <vector>
#include <string>
#include "Pixel.h"
class Compressor
{
public:
	void compress(std::string outputPath, std::vector<Pixel>, int height, int width);

	Compressor();
};
