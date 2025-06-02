#include <fstream>
#include <vector>
#include <string>
#include "Filereader.h"
#include "Pixel.h"

bool Filereader::does_file_exist(const char* filename)
{
	std::ifstream infile(filename);
	return infile.good();
}

std::string Filereader::readUntilDelimiter(std::fstream& file, const char* delimiters) {
	std::string result;
	char ch;

	while (file.get(ch)) {
		// Vérifie si le caractère lu est un délimiteur
		if (std::strchr(delimiters, ch)) {
			break; // Arrête la lecture si un délimiteur est rencontré
		}
		result += ch; // Ajoute le caractère au résultat
	}

	return result;
}

void Filereader::parse_file(const char* filename, std::vector<Pixel>& pixels, int& width, int& height)
{
	// For more info on the PPM format, check
	// https://fr.wikipedia.org/wiki/Portable_pixmap
	//
	// PPM P3 File format composition:
	// - 2 Bytes for Format/Variant
	// - Separation char
	// - Width (in Ascii)
	// - Separation char
	// - Height (in Ascii)
	// - Separation char
	// - Image Data

	std::fstream ImgFile(filename, std::ios::in | std::ios::binary);

	// Checks if possible
	if (!ImgFile.is_open())
	{
		throw std::runtime_error("Unable to open file.");
	}

	// Prepares useful vars
	char separationChars[] = { '\n', ' ', '\t' };

	// Start reading
	// Ignore 2 Bytes magic number
	ImgFile.seekg(2, std::ios::beg);

	// Gets the width
	std::string widthStr = readUntilDelimiter(ImgFile, separationChars);
	width = std::stoi(widthStr);

	// Gets the height
	std::string heightStr = readUntilDelimiter(ImgFile, separationChars);
	height = std::stoi(widthStr);

	// reads Pixel data
	int8_t r, g, b;
	while (ImgFile >> r >> g >> b) { // Reads RGB values
		pixels.emplace_back(r, g, b); // Adds a pixel to the Pixels vector
	}

	ImgFile.close();
}

Filereader::Filereader()
{
}

Filereader::~Filereader()
{
}