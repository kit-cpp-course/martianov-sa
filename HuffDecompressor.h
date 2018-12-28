#pragma once
#include "Decompressor.h"
#include "HuffTree.h"
#include "HuffDict.h"

// Класс реализующий расжатие данных методом Хаффмана.
class HuffDecompressor : public Decompressor
{
	// Словарь "лексем Хаффмана"
	HuffDict huffDict;
	
	// Дерево Хаффмана
	HuffTree huffTree;
	
	// Вспомогательная таблица частот
	size_t freqs[256] { 0 };

	// Создание "словаря Хаффмана" на основе данных в файле.
	void createHuffDict(File & source);

	// Запись расжатых данных в выходной файл.
	void writeDecompressedData(File & source, File & dest);

	// Запись одного расжатого символа из дерева.
	void writeOneSymbol(HuffTree & T, File & dest);

	// Запись всех расжатых символа из дерева.
	void writeAllSymbols(File & source, File & dest);

	// Запись только первого расжатого символа.
	void writeOnlyFirstSymbol(File & dest);

	// Заполнение вспомогательной таблицы частот.
	void fillFreqs();

public:

	HuffDecompressor();

	// Метод, производящий сжатие данных из файла source и записывающий сжатые данные в файл dest.
	void decompress(File & source, File & dest);
};

