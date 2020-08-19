#pragma once
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

/*
	This class is a windows only class.
	Creates a map object from a refrance memory location
	on the disk. This map object can be read from.

*/

class MapFile
{
public:
	//Get the memory address
	LPVOID getAddress(const char* file) {
		mapFile(file);
		return n_viewMap;
	}

	//Delete the address
	void deleteAddress();

private:
	void mapFile(const char* file);

	LPVOID n_viewMap;

};

