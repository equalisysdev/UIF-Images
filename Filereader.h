#include <vector>
#include "Pixel.h"

#pragma once
class Filereader
{
public:
	static bool does_file_exist(const char* filename);

	// Reads and parses a PPM file (type 3) into multiple vectors
	static void parse_file(const char* filename, std::vector<Pixel>& pixels, int& width, int& height);

	static std::string readUntilDelimiter(std::fstream& file, const char* delimiters);

	Filereader();
	~Filereader();
};
