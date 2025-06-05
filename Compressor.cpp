#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include "LZ4/include/lz4.h"

#include "Compressor.h"
#include "Pixel.h"

void Compressor::compress(std::string outputPath, std::vector<Pixel> pixels, int height, int width)
{
	std::cout << "Compressing file: " << outputPath << std::endl;

	// Gets the input size
	// Multiply by the size of the pixels vector
	int inputSize = (3 * sizeof(uint8_t) * pixels.size());

	// Allocate a buffer for the compressed data
	int maxCompressedSize = LZ4_compressBound(static_cast<int>(inputSize));
	std::vector<char> compressedBuffer(maxCompressedSize);

	std::cout << "Maximum compressed size: " << maxCompressedSize << " bytes" << std::endl << std::endl;

	// Writes the header
	std::string compressedPath = std::filesystem::path(outputPath).replace_extension(".cuif").string();

	std::fstream compressedFile(compressedPath, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
	if (!compressedFile.is_open()) {
		throw std::runtime_error("Failed to open compressed file for writing.");
	}
	std::cout << "Writing Header..." << std::endl;
	compressedFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
	compressedFile.write(reinterpret_cast<const char*>(&height), sizeof(height));

	// Sets the pointer to the correct location
	compressedFile.seekg(1, std::ios::cur);

	// Prepare and fill the inputBuffer with pixel data
	std::vector<char> inputBuffer(inputSize);

	size_t bufferIndex = 0;
	for (const Pixel& pixel : pixels) {
		inputBuffer[bufferIndex++] = static_cast<char>(pixel.red);   // Add red channel
		inputBuffer[bufferIndex++] = static_cast<char>(pixel.green); // Add green channel
		inputBuffer[bufferIndex++] = static_cast<char>(pixel.blue);  // Add blue channel
	}

	// Perform LZ4 compression
	std::cout << "Compressing..." << std::endl << std::endl;
	int compressedSize = LZ4_compress_default(
		inputBuffer.data(),
		compressedBuffer.data(),
		static_cast<int>(inputSize),
		maxCompressedSize
	);

	std::cout << "DONE." << std::endl;
	std::cout << "Compressed size: " << compressedSize + 2 * sizeof(int) << " bytes" << std::endl;

	if (compressedSize <= 0) {
		throw std::runtime_error("Compression failed. Error on Byte " + compressedSize);
	}

	compressedFile.write(compressedBuffer.data(), compressedSize - 1); // -1 to transform an index to a size
	compressedFile.close();
}

Compressor::Compressor()
{
}