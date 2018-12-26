#pragma once
#include "File.h"

/**
 * ����������� ����� ����������� ������ ������.
 */
class Compressor
{
public:
	/**
	* �����, ������������ ������ ������ �� ����� source � ������������ ������ ������ � ���� dest.
	*/
	virtual void compress(File * source, File * dest) = 0;
};
