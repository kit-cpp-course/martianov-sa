#pragma once

// ����� ��� ������ � �������.
class File
{
public:
	// ��������� ������� � �����
	enum mode
	{
		// ��������� ���� �� ������ � ������ � ����� �����
		FULL = std::ios::binary | std::ios::in | std::ios::out,
		// ��������� ���� ������ ��� ������ � ������ �����
		READ_ONLY = std::ios::binary | std::ios::in,
		// ��������� ���� ������ ��� ������ � ����� �����
		WRITE_ONLY = std::ios::binary | std::ios::out
	};

private:
	// ����� �����
	std::fstream f;
	
	// ������� ������� � �����
	mode access;
	
	// ����� � �����
	std::string fileName;
	
	// ��������� ������� � ����� ���� ��� ������� ���
	size_t writeBitPos;
	
	// ��������� ������� � ����� ������ ��� ������ ���
	size_t readBitPos;

public:
	/**
	  �������� �����������.

	  ��������� ���� � ����� � �����, � ����� �� ����� ������.
	*/
	File(std::string source, mode accessMode = FULL);

	// �������� ���������� �����.
	~File();

	/**
	  ���������� ���������� ������.

	  ��������� ������� ������, ���� ����� �������� ����������� ����� � ���������� ����,
	  ������� ����� ���������.
	*/
	bool readNextBytes(char * bytes, size_t numOfBytes = sizeof(char));

	/**
	  ������ ���������� ������.

	  ��������� ������� ������, ������ ����� �������� ����� � ���� � ���������� ����,
	  ������� ����� ��������.
	*/
	bool writeNextBytes(char * bytes, size_t numOfBytes = sizeof(char));

	/**
	  ���������� ���������� ����.

	  ��������� ������� ������, ���� ����� ������� ����������� ���.
	*/
	bool readNextBit(char & bit);

	/**
	  ������ ���������� ����.

	  ��������� ������� ������, ������ ����� ������� ��� � ����.
	*/
	bool writeNextBit(char bit, char & lastByte);

	/**
	  ��������� ���������� �����.

	  �������� ������� ���������� ������������ ����.
	*/
	void finishReadBits();

	/**
	  ��������� ������ �����.

	  �������� ������� ���������� ����������� ����.
	*/
	void finishWriteBits();

	// ������� ������� � ������ �����.
	void rewindToStart();

	// ������� ����.
	void clearData();
};
