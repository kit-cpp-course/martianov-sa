#pragma once
#include "File.h"

// Абстрактный класс реализующий сжатие данных.
class Compressor
{
public:
	// Метод, производящий сжатие данных из файла source и записывающий сжатые данные в файл dest.
	virtual void compress(File & source, File & dest) = 0;
};
