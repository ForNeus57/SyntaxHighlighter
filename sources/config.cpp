//
// Created by Dominik on 28.03.2023.
//

#include "config.h"

template<>struct std::tuple_size<Config> : std::integral_constant<std::size_t, 6> {};
template<std::size_t N> struct std::tuple_element<N, Config> { using type = decltype(std::declval<Config>().get<N>());};


bool Config::has_been_parsed = false;
bool Config::flag_input_files = false;
bool Config::flag_output_files = false;
bool Config::flag_statistics = false;
bool Config::flag_html = false;
bool Config::flag_threads = false;
bool Config::flag_help = false;
bool Config::flag_version = false;


Config::Config(): files(), requires_statistics(), should_output_be_html(), how_many_threads_to_use(), display_help(), display_version() {}

void Config::parse(int argc, char** argv) {
	if(Config::has_been_parsed) throw std::runtime_error("Cannot parse commandline arguments twice!");
	Config::has_been_parsed = true;

	const std::vector<std::string_view> args(argv + 1, argv + argc);

	size_t cursor_jump;
	for(size_t i = 0; i < args.size(); i += cursor_jump) {
		cursor_jump = 1;
		switch(hash(args[i].data())) {
			case hash("-i"):
			case hash("--input"): {
				if(Config::flag_input_files) throw std::runtime_error("BasicCompiler.exe: cannot use -i/--input parameter twice!");
				Config::flag_input_files = true;

				if(this->files.empty()) {
					while(args[i + cursor_jump][0] != '-') {
						if (!std::filesystem::exists(args[i + cursor_jump])) throw std::runtime_error(std::string("BasicCompiler.exe: ") + std::string(args[i + cursor_jump]) + ": No such file or directory");
						this->files.emplace_back(args[i + cursor_jump], "");
						cursor_jump++;
					}
				} else {
					auto it = this->files.begin();
					while(args[i + cursor_jump][0] != '-') {
						if (!std::filesystem::exists(args[i + cursor_jump])) throw std::runtime_error(std::string("BasicCompiler.exe: ") + std::string(args[i + cursor_jump]) + ": No such file or directory");
						it->first = args[i + cursor_jump];
						cursor_jump++;
					}
				}
				break;
			}
			case hash("-o"):
			case hash("--output"): {
				if(Config::flag_output_files) throw std::runtime_error("BasicCompiler.exe: cannot use -o/--output parameter twice!");
				Config::flag_output_files = true;

				if(this->files.empty()) {
					while(args[i + cursor_jump][0] != '-') {
						if (!std::filesystem::exists(args[i + cursor_jump])) throw std::runtime_error(std::string("BasicCompiler.exe: ") + std::string(args[i + cursor_jump]) + ": No such file or directory");
						this->files.emplace_back("", args[i + cursor_jump]);
						cursor_jump++;
					}
				} else {
					auto it = this->files.begin();
					while(args[i + cursor_jump][0] != '-') {
						if (!std::filesystem::exists(args[i + cursor_jump])) throw std::runtime_error(std::string("BasicCompiler.exe: ") + std::string(args[i + cursor_jump]) + ": No such file or directory");
						it->second = args[i + cursor_jump];
						cursor_jump++;
					}
				}

				break;
			}
			case hash("-s"):
			case hash("--statistics"): {
				if(Config::flag_statistics) throw std::runtime_error("BasicCompiler.exe: cannot use -s/--statistics parameter twice!");
				Config::flag_statistics = true;
				this->requires_statistics = true;
				break;
			}
			case hash("-H"):
			case hash("--HTML"): {
				if(Config::flag_html) throw std::runtime_error("BasicCompiler.exe: cannot use -H/--HTML parameter twice!");
				Config::flag_html = true;
				this->should_output_be_html = true;
				break;
			}
			case hash("-t"):
			case hash("--threads"): {
				if(Config::flag_threads) throw std::runtime_error("BasicCompiler.exe: cannot use -t/--threads parameter twice!");
				Config::flag_threads = true;
				this->how_many_threads_to_use = std::stoi(args[i + cursor_jump].data());
				if(this->how_many_threads_to_use < 1 and this->how_many_threads_to_use != -1) throw std::runtime_error("BasicCompiler.exe: number of threads to run must be grater or equal one or be equal to minus one!");
				break;
			}
			case hash("-h"):
			case hash("--help"): {
				if(Config::flag_help) throw std::runtime_error("BasicCompiler.exe: cannot use -h/--help parameter twice!");
				Config::flag_help = true;
				this->display_help = true;
				break;
			}
			case hash("-v"):
			case hash("--version"): {
				if(Config::flag_version) throw std::runtime_error("BasicCompiler.exe: cannot use -v/--version parameter twice!");
				Config::flag_version = true;
				this->display_version = true;
				break;
			}
			default: {
				throw std::runtime_error("BasicCompiler.exe: unknown commandline argument: " + std::string(args[i].data()));
			}
		}
	}
	//	Check if we have got the same number of input files and output files.
	if(!this->files.begin()->second.empty() and (this->files.begin()++ != this->files.end()) and !(this->files.begin()++)->second.empty() and !this->files.end()->first.empty())
		throw std::runtime_error("BasicCompiler.exe: number of output files is grater then 1 and is lower then input file number therefore not every input has a pair!");
}