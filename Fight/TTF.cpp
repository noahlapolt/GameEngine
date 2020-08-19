#include "TTF.h"

TTF::TTF(const char* file)
{
	n_address = n_file.getAddress(file);
	loadFileToStruct();
}


TTF::~TTF()
{
}

void TTF::loadFileToStruct() {
	TTFFont fd;

	//Can read data from file on heap
	memcpy(&fd, n_address, sizeof(fd));

	std::cout << std::hex << _byteswap_ulong(fd.version) << std::endl
		<< _byteswap_ushort(fd.numTables) << std::endl
		<< _byteswap_ushort(fd.searchRange) << std::endl
		<< _byteswap_ushort(fd.entrySelector) << std::endl
		<< _byteswap_ushort(fd.rangeShift) << std::endl
		<< fd.tableTag[0] << fd.tableTag[1] << fd.tableTag[2] << fd.tableTag[3] << std::endl
		<< _byteswap_ulong(fd.checkSum) << std::endl
		<< _byteswap_ulong(fd.offset) << std::endl
		<< _byteswap_ulong(fd.length) << std::endl
		<< sizeof(fd) << std::endl;
}


uint32_t CalcTableChecksum(uint32_t *Table, uint32_t Length)
{
	uint32_t Sum = 0L;
	uint32_t *Endptr = Table + ((Length + 3) & ~3) / sizeof(uint32_t);
	while (Table < Endptr) {
		Sum += *Table++;
	}
	return Sum;
}