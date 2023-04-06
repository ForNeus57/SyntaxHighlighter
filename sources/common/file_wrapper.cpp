//
// Created by Dominik on 05.04.2023.
//

#include "file_wrapper.h"

template class FileWrapper<std::ifstream, std::ios_base::in>;
template class FileWrapper<std::ofstream, std::ios_base::out>;

template<typename T, std::ios_base::openmode O>
FileWrapper<T, O>::FileWrapper(const std::string& path): file(path, O) {
	if(!this->file.is_open()) throw std::runtime_error("File with provided path:" + path + ", could not be opened!");
}
template<typename T, std::ios_base::openmode O>
FileWrapper<T, O>::~FileWrapper() {
	this->file.close();
}
template<typename T, std::ios_base::openmode O>
T& FileWrapper<T, O>::getFile() const {
	return this->file;
}