//
// Created by Dominik on 28.03.2023.
//

#ifndef BASIC_COMPILER_RUN_H
#define BASIC_COMPILER_RUN_H


#include <list>
#include <vector>
#include <string_view>
#include <algorithm>
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <ranges>

#include "../model/token/token.h"
#include "../model/scanner.h"
#include "file_wrapper.h"
#include "config.h"


uint64_t constexpr mix(char m, uint64_t s) {
	return ((s<<7) + ~(s>>3)) + static_cast<uint64_t>(~m);
}
uint64_t constexpr hash(const char * m) {
	return (*m) ? mix(*m,hash(m+1)) : 0;
}

/**
 * @brief
 * @note	This class uses the OOP singleton design pattern.
 *
 * @todo	Make this help method be more useful...
 * @todo	Make the .parse() method use iterators instead of index.
 */
class Run final {
	private:
		/**
		 * @brief
		 *
		 */
		Run(int, char**);
		~Run() = default;
	public:
		Run(const Run&) = delete;
	public:
		void operator=(const Run&) = delete;
		/**
		 * @brief	Main functor of Run object, after processing the commandline parameters...
		 * @note	This functor should be called only once in a program.
		 */
		void operator()(std::istream*, std::ostream*);
	public:
		static Run& getInstance(int, char**);
	private:
		void parse(int, char**);
		void process_input_files(const std::vector<std::string_view>&, std::size_t&);
		void process_output_files(const std::vector<std::string_view>&, std::size_t&);
		void process_statistics() const;
		void process_html_output();
		void process_threads(const std::vector<std::string_view>&, std::size_t&);
		void process_version();
		void process_help();
		void adjust_thread_behaviour();
		static std::string initialize_output_normal();
		static std::string end_output_normal();
		static std::string initialize_output_html();
		static std::string end_output_html();
	public:
		const static std::string NORMAL_START;
		const static std::string NORMAL_END;
		const static std::string HTML_START;
		const static std::string HTML_END;
	private:
		std::string program_name;
		std::list<FileWrapper<std::ifstream, std::ios_base::in>> input;
		std::list<FileWrapper<std::ofstream, std::ios_base::out>> output;
		std::string (Token::*output_contents)() const;
		std::string (*output_start)();
		std::string (*output_end)();
		int thread_count;
	private:								//	Flag variables, that return True / False depending on if a corresponding argument have been set using commandline.
		static bool flag_input_files;
		static bool flag_output_files;
		static bool flag_statistics;
		static bool flag_html;
		static bool flag_threads;
		static bool flag_version;
		static bool flag_help;
};


#endif	//	BASIC_COMPILER_RUN_H
