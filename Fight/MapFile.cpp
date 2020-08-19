#include "MapFile.h"
/*
	Creates a pointer to the memory adress of the first object in a chunck of memory
	@param file
	-The file address to be turned into a pointer.
	@return
	-The address of the first byte of the block of data.
*/
void MapFile::mapFile(const char* file)
{
	HANDLE fileHandle = CreateFileA(file, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE fileObjectHandle = CreateFileMappingA(fileHandle, NULL, PAGE_READONLY, 0, 0,NULL);

	n_viewMap = MapViewOfFile(fileObjectHandle, FILE_MAP_READ, 0, 0, 0); //This returns the memmory address

	CloseHandle(fileObjectHandle);
	CloseHandle(fileHandle);
}

void MapFile::deleteAddress() {
	//Closes/Cleans everything
	UnmapViewOfFile(n_viewMap);
}
