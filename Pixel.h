#pragma once
#include <cstdint> // Ajout de l'en-t�te pour int8_t

class Pixel
{
public:
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	Pixel(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
};
