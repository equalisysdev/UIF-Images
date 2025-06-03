#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "Encoder.h"
#include "Compressor.h"
#include "Pixel.h"
#include "LZ4/include/lz4.h"

// Parses the PPM P3 image file before sending it to a file
void Encoder::encode(const char* pixmapPath, Filereader& filereader, Compressor& compressor)
{
	// R : Int
	// G : Int
	// B : Int
	// just use Pixel Object
	std::vector<Pixel> pixels;
	int32_t width;
	int32_t height;

	std::cout << "<----- Parsing ------>\n" << std::endl;
	// Gets the parsed data from the PPM P3
	filereader.parse_file(pixmapPath, pixels, width, height);
	std::cout << "\nDONE.\n" << std::endl;

	std::cout << "\n<----- Encoding ----->\n" << std::endl;
	// Creates a file

	std::string outputPath = std::filesystem::path(pixmapPath).replace_extension(".uif").string();

	std::fstream file(outputPath, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

	// We use file.write() because file.put() only puts 1 single Byte and the int is encoded in 4
	file.write(reinterpret_cast<const char*>(&width), sizeof(width));
	file.write(reinterpret_cast<const char*>(&height), sizeof(height));

	for (Pixel pixel : pixels)
	{
		file.write(reinterpret_cast<const char*>(&pixel.red), sizeof(pixel.red));
		file.write(reinterpret_cast<const char*>(&pixel.green), sizeof(pixel.green));
		file.write(reinterpret_cast<const char*>(&pixel.blue), sizeof(pixel.blue));

		std::string tmp_r = std::to_string(pixel.red);
		const char* r = tmp_r.c_str();

		std::string tmp_g = std::to_string(pixel.green);
		const char* g = tmp_g.c_str();

		std::string tmp_b = std::to_string(pixel.blue);
		const char* b = tmp_b.c_str();

		std::cout << "Wrote pixel: " << r << ", " << g << ", " << b << std::endl;
	}

	std::cout << "\nDONE.\n" << std::endl;
	file.close();

	std::cout << "<----- Compressing ----->" << std::endl;
	compressor.compress(outputPath);
}

Encoder::Encoder()
{
}

Encoder::~Encoder()
{
}