/*
 * FileReader.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "Cities.h"
#include "Library.h"

class FileReader {
public:
	FileReader();
	virtual ~FileReader();
	void readFile(const char *fileName, Cities *cities);
};

#endif /* FILEREADER_H_ */
