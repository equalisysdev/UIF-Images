#include <vector>
#include <fstream>
#include <string>
#include "Encoder.h"
#include "Pixel.h"

// Parses the PPM P3 image file before sending it to a file
void Encoder::encode(const char* pixmapPath, Filereader& filereader)
{
	// R : Int
	// G : Int
	// B : Int
	// just use Pixel Object
	std::vector<Pixel> pixels;
	int width;
	int height;

	// Gets the parsed data from the PPM P3
	filereader.parse_file(pixmapPath, pixels, width, height);

	// Creates a file
	std::fstream file("img.uif", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

	// We use file.write() because file.put() only puts 1 single Byte and the int is encoded in 4
	file.write(reinterpret_cast<const char*>(&width), sizeof(width));
	file.write(reinterpret_cast<const char*>(&height), sizeof(height));
}

Encoder::Encoder()
{
}

Encoder::~Encoder()
{
}