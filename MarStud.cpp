#include "pch.h"
#include "HuffCompressor.h"
#include "HuffDecompressor.h"

int main()
{	
	Compressor * d = new HuffCompressor();
	Decompressor * e = new HuffDecompressor();

	File * a = new File("test.txt");
	File * b = new File("huff.txt");
	File * c = new File("test1.txt");

	d->compress(a, b);
	e->decompress(b, c);

	delete d;
	delete e;
	delete a;
	delete b;
	delete c;

	return 0;
}