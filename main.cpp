#include <iostream>
#include <fstream>
#include "CImg-3.5.6_pre06022513/CImg.h"

#include "Filereader.h"
#include "Encoder.h"

using namespace std;

int main(int argc, char** argv) {
	// Prepares objects + vars
	Filereader filereader = Filereader();
	Encoder encoder = Encoder();

	const char* pixmapPath = nullptr;
	try
	{
		cout << "##############################################" << endl;
		cout << "### Unoptimized Image Format (UIF) Encoder ###" << endl;
		cout << "##############################################" << endl << endl;

		// Checks args
		if (argv[1] == NULL)
		{
			cout << "No path passed... exiting" << endl;
			return 1;
		}
		pixmapPath = argv[1];

		// Checks if file exists
		if (!filereader.does_file_exist(pixmapPath))
		{
			cout << "File does not exist... exiting" << endl;
			return 1;
		}

		// If all checks passed, call encode()
		encoder.encode(pixmapPath, filereader);
	}
	catch (const exception& e)
	{
		cout << "An unhandled exception happened : " << e.what() << endl;
		return 1;
	}

	return 0;
}