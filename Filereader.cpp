#include <fstream>
#include <vector>
#include <string>
#include <iostream>
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
	std::cout << "File opened" << std::endl;

	// Prepares useful vars
	char separationChars[] = { '\n', ' ', '\t', '\r' };

	// Start reading
	// Ignore 2 Bytes magic number
	ImgFile.seekg(3, std::ios::beg);

	// Gets the width
	std::string widthStr = readUntilDelimiter(ImgFile, separationChars);

	std::cout << "Width: " << widthStr << std::endl;

	width = std::stoi(widthStr);

	// Gets the height
	std::string heightStr = readUntilDelimiter(ImgFile, separationChars);

	std::cout << "Height: " << heightStr << std::endl;

	height = std::stoi(heightStr);

	ImgFile.seekg(0, std::ios::cur);

	// reads Pixel data
	int i = 1;
	while (!ImgFile.eof()) { // Reads RGB values
		if (std::strchr(separationChars, ImgFile.peek()))
		{
			ImgFile.seekg(1, std::ios::cur); // Skip the separation char
		}
		else
		{
			std::string temp_r = readUntilDelimiter(ImgFile, separationChars);
			std::string temp_g = readUntilDelimiter(ImgFile, separationChars);
			std::string temp_b = readUntilDelimiter(ImgFile, separationChars);

			uint8_t r = std::stoi(temp_r);
			uint8_t g = std::stoi(temp_g);
			uint8_t b = std::stoi(temp_b);

			pixels.emplace_back(r, g, b);
			// Adds a pixel to the Pixels vector and converts the strings to int8_t
		}
	}

	ImgFile.close();
}

Filereader::Filereader()
{
}

Filereader::~Filereader()
{
}