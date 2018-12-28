#include "pch.h"
#include "HuffCompressor.h"
#include "HuffDecompressor.h"

using namespace std;

int main(int argc, char ** argv)
{	
	
	string action = argv[1];
	File source(argv[2], File::READ_ONLY);
	File dest(argv[3], File::WRITE_ONLY);

	if (argc != 4 && (action != "/c" || action != "/d"))
	{
		cout << "Incorrect command!" << endl;
	}
	else if (action == "/c")
	{
		Compressor && com = HuffCompressor();
		com.compress(source, dest);
		cout << "Successfully compressed!" << endl;
	}
	else if (action == "/d")
	{
		Decompressor && dec = HuffDecompressor();
		dec.decompress(source, dest);
		cout << "Successfully decompressed!" << endl;
	}

	return 0;
}