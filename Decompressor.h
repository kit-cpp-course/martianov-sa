#pragma once
#include "File.h"

class Decompressor
{
public:
	virtual void decompress(File * source, File * dest) = 0;
};
