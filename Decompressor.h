#pragma once
#include "File.h"

// Абстрактный класс реализующий расжатие данных.
class Decompressor
{
public:
	// Метод, производящий расжатие данных из файла source и записывающий сжатые данные в файл dest.
	virtual void decompress(File & source, File & dest) = 0;
};
