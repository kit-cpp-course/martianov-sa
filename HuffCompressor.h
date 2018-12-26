#pragma once
#include "Compressor.h"
#include "HuffTree.h"
#include "HuffDict.h"

/**
 * ����� ����������� ������ ������ ������� ��������.
 */
class HuffCompressor : public Compressor
{
	HuffDict * huffDict;	// ������� "������ ��������"
	HuffTree * huffTree;	// ������ ��������

	/**
	 * �������� "������� ��������" �� ������ ������ � �����.
	 */
	void createHuffDict(File * source);

	/**
	 * ������ "������� ��������" � �������� ����.
	 */
	void writeHuffDict(File * dest);

	/**
	 * ������ ������ ������� � �������� ����.
	 */
	bool writeOneSymbol(char symbol, char & lastByte, File * dest);
	
	/**
	 * ������ ������ ������ � �������� ����.
	 */
	void writeCompressedData(File * source, File * dest);

public:
	/**
	* �������� �����������.
	*/
	HuffCompressor();

	/**
	* �������� ����������.
	*/
	virtual ~HuffCompressor();

	/**
	* �����, ������������ ������ ������ �� ����� source � ������������ ������ ������ � ���� dest.
	*/
	void compress(File * source, File * dest);
};
