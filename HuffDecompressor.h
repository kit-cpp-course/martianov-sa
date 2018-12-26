#pragma once
#include "Decompressor.h"
#include "HuffTree.h"
#include "HuffDict.h"

/**
 * ����� ����������� �������� ������ ������� ��������.
 */
class HuffDecompressor : public Decompressor
{
	HuffDict * huffDict;	// ������� "������ ��������"
	HuffTree * huffTree;	// ������ ��������
	size_t * freqs;			// ��������������� ������� ������

	/**
	 * �������� "������� ��������" �� ������ ������ � �����.
	 */
	void createHuffDict(File * source);

	/**
	 * ������ �������� ������ � �������� ����.
	 */
	void writeDecompressedData(File * source, File * dest);

	/**
	 * ������ ������ ��������� ������� �� ������.
	 */
	void writeOneSymbol(HuffTree * T, File * dest);

	/**
	 * ������ ���� �������� ������� �� ������.
	 */
	void writeAllSymbols(File * source, File * dest);

	/**
	 * ������ ������ ������� ��������� �������.
	 */
	void writeOnlyFirstSymbol(File * dest);

	/**
	 * ���������� ��������������� ������� ������.
	 */
	void fillFreqs();

public:
	/**
	* �������� �����������.
	*/
	HuffDecompressor();

	/**
	* �������� ����������.
	*/
	virtual ~HuffDecompressor();

	/**
	* �����, ������������ ������ ������ �� ����� source � ������������ ������ ������ � ���� dest.
	*/
	void decompress(File * source, File * dest);
};

