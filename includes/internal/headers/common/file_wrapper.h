//
// Created by Dominik on 05.04.2023.
//

#ifndef BASIC_COMPILER_FILE_WRAPPER_H
#define BASIC_COMPILER_FILE_WRAPPER_H

#include <fstream>
#include <iostream>


/**
 * @brief
 * @tparam	T
 */
template<typename T, std::ios_base::openmode O>
class FileWrapper {
public:
	explicit FileWrapper(const std::string& path);
	~FileWrapper();
public:
	T& getFile();
private:
	T file;
};


#endif	//	BASIC_COMPILER_FILE_WRAPPER_H
