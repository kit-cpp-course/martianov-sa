#pragma once
#include "Decompressor.h"
#include "HuffTree.h"
#include "HuffDict.h"

/**
 * Класс реализующий расжатие данных методом Хаффмана.
 */
class HuffDecompressor : public Decompressor
{
	HuffDict * huffDict;	// Словарь "лексем Хаффмана"
	HuffTree * huffTree;	// Дерево Хаффмана
	size_t * freqs;			// Вспомогательная таблица частот

	/**
	 * Создание "словаря Хаффмана" на основе данных в файле.
	 */
	void createHuffDict(File * source);

	/**
	 * Запись расжатых данных в выходной файл.
	 */
	void writeDecompressedData(File * source, File * dest);

	/**
	 * Запись одного расжатого символа из дерева.
	 */
	void writeOneSymbol(HuffTree * T, File * dest);

	/**
	 * Запись всех расжатых символа из дерева.
	 */
	void writeAllSymbols(File * source, File * dest);

	/**
	 * Запись только первого расжатого символа.
	 */
	void writeOnlyFirstSymbol(File * dest);

	/**
	 * Заполнение вспомогательной таблицы частот.
	 */
	void fillFreqs();

public:
	/**
	* Основной конструктор.
	*/
	HuffDecompressor();

	/**
	* Основной Деструктор.
	*/
	virtual ~HuffDecompressor();

	/**
	* Метод, производящий сжатие данных из файла source и записывающий сжатые данные в файл dest.
	*/
	void decompress(File * source, File * dest);
};

