//
// Created by Dominik on 11.04.2023.
//

#ifndef BASIC_COMPILER_FOUNDATION_H
#define BASIC_COMPILER_FOUNDATION_H

#include <string>

class PrimitiveToken {
	public:
		std::string virtual print() const = 0;
		std::string virtual printHTML() const = 0;
};


#endif	//	BASIC_COMPILER_FOUNDATION_H
