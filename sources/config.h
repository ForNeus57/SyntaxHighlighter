//
// Created by Dominik on 28.03.2023.
//

#ifndef BASIC_COMPILER_CONFIG_H
#define BASIC_COMPILER_CONFIG_H

#include <list>
#include <vector>
#include <string_view>
#include <filesystem>
#include <stdexcept>

uint64_t constexpr mix(char m, uint64_t s) {
	return ((s<<7) + ~(s>>3)) + static_cast<uint64_t>(~m);
}
uint64_t constexpr hash(const char * m) {
	return (*m) ? mix(*m,hash(m+1)) : 0;
}

/**
 * @brief
 */
class Config final {
public:
	/**
	 * @brief
	 *
	 */
	Config();
public:
	std::list<std::pair<std::string_view, std::string_view>> getFiles();
	bool getStatistics();
	bool getHTML();
	int getThreadsCount();
	bool getHelp();
	bool getVersion();
	bool getStatus();
public:
	template <std::size_t N> decltype(auto) get() const {
		switch (N) {
			case 0:
				return files;
			case 1:
				return requires_statistics;
			case 2:
				return should_output_be_html;
			case 3:
				return how_many_threads_to_use;
			case 4:
				return display_help;
			case 5:
				return display_version;
			default:
				throw std::out_of_range("");
		}
	}
public:
	void parse(int, char**);
public:
	/**
	 * @brief
	 *
	 * @param	first	input file
	 * @param 	second	output file
	 */
	std::list<std::pair<std::string_view, std::string_view>> files;
	bool requires_statistics;
	bool should_output_be_html;
	int how_many_threads_to_use;
	bool display_help;
	bool display_version;
private:
	static bool has_been_parsed;
	static bool flag_input_files;
	static bool flag_output_files;
	static bool flag_statistics;
	static bool flag_html;
	static bool flag_threads;
	static bool flag_help;
	static bool flag_version;
};


#endif	//	BASIC_COMPILER_CONFIG_H
