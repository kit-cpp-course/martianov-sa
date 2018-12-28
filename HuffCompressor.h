#pragma once
#include "Compressor.h"
#include "HuffTree.h"
#include "HuffDict.h"

// Класс реализующий сжатие данных методом Хаффмана.
class HuffCompressor : public Compressor
{
	// Словарь "лексем Хаффмана"
	HuffDict huffDict;
	
	// Дерево Хаффмана
	HuffTree huffTree;

	// Создание "словаря Хаффмана" на основе данных в файле
	void createHuffDict(File & source);

	// Запись "словаря Хаффмана" в выходной файл
	void writeHuffDict(File & dest);

	// Запись одного символа в выходной файл
	bool writeOneSymbol(char symbol, char & lastByte, File & dest);
	
	// Запись сжатых данных в выходной файл
	void writeCompressedData(File & source, File & dest);

public:

	HuffCompressor();

	// Метод, производящий сжатие данных из файла source и записывающий сжатые данные в файл dest.
	void compress(File & source, File & dest);
};
