#pragma once
#include <iostream>

#include "MapFile.h"

//notes for reading file
/*
 Five Tables GSUB, GPOS, BASE, JSTF, and GDEF

GSUB: Contains information about glyph substitutions to handle single glyph substitution, one-to-many substitution (ligature decomposition), aesthetic alternatives,
		multiple glyph substitution (ligatures), and contextual glyph substitution.

GPOS: Contains information about X and Y positioning of glyphs to handle single glyph adjustment, adjustment of paired glyphs, cursive attachment, mark attachment,
		and contextual glyph positioning.

BASE: Contains information about baseline offsets on a script-by-script basis.

JSTF: Contains justification information, including whitespace and Kashida adjustments.

GDEF: Contains information about all individual glyphs in the font: type (simple glyph, ligature, or combining mark), attachment points (if any), and ligature 
		caret (if a ligature glyph).

*/

struct TTFFont {
	//Table 1
	uint32_t version; //The version of ttf 4 bytes
	uint16_t numTables; //Number of tables //2 bytes
	uint16_t searchRange; //(Maximum power of 2 <= numTables) x 16. //2 bytes
	uint16_t entrySelector; //(Maximum power of 2 <= numTables) x 16. //2 bytes
	uint16_t rangeShift; //NumTables x 16-searchRange. //2 bytes
	//Table 2
	uint8_t tableTag[4];	//4 bytes
	uint32_t checkSum;	//4 bytes
	uint32_t offset;	//4 bytes
	uint32_t length;	//4 bytes
};

class TTF
{
public:
	TTF(const char* file);
	~TTF();

private:
	void loadFileToStruct();

	MapFile n_file;
	LPVOID n_address;
};

