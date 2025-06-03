#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include "LZ4/include/lz4.h"

#include "Compressor.h"

void Compressor::compress(std::string outputPath)
{
	// Open the file for reading raw data
	std::ifstream inputFile(outputPath, std::ios::binary | std::ios::ate);
	if (!inputFile.is_open()) {
		throw std::runtime_error("Failed to open file for compression.");
	}

	// Get the size of the file
	std::streamsize inputSize = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);

	// Read the file's raw data into a buffer
	std::vector<char> inputBuffer(inputSize);
	if (!inputFile.read(inputBuffer.data(), inputSize)) {
		throw std::runtime_error("Failed to read file data.");
	}
	inputFile.close();

	// Allocate a buffer for the compressed data
	int maxCompressedSize = LZ4_compressBound(static_cast<int>(inputSize));
	std::vector<char> compressedBuffer(maxCompressedSize);

	// Perform LZ4 compression
	int compressedSize = LZ4_compress_default(
		inputBuffer.data(),
		compressedBuffer.data(),
		static_cast<int>(inputSize),
		maxCompressedSize
	);

	if (compressedSize <= 0) {
		throw std::runtime_error("Compression failed.");
	}

	// Write the compressed data to a new file
	std::string compressedPath = std::filesystem::path(outputPath).replace_extension(".uif.lz4").string();
	std::ofstream compressedFile(compressedPath, std::ios::binary);
	if (!compressedFile.is_open()) {
		throw std::runtime_error("Failed to open compressed file for writing.");
	}

	compressedFile.write(compressedBuffer.data(), compressedSize);
	compressedFile.close();
}

Compressor::Compressor()
{
}