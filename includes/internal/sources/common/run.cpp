//
// Created by Dominik on 28.03.2023.
//

#include "../../headers/common/run.h"


const std::string Run::HTML_START =
	"<!DOCTYPE html>\n"
	"<html lang=\"en\">\n"
		"\t<head>\n"
			"\t\t<meta charset=\"UTF-8\">\n"
			"\t\t<title>Output file of colouring process</title>\n"
		"\t</head>\n"
		"\t<body>\n";
const std::string Run::HTML_END =
		"\t</body>\n"
	"</html>\n";
const std::string Run::NORMAL_START = "//  Output file of colouring process\n";
const std::string Run::NORMAL_END = "\n";

bool Run::flag_input_files = false;
bool Run::flag_output_files = false;
bool Run::flag_statistics = false;
bool Run::flag_html = false;
bool Run::flag_threads = false;
bool Run::flag_version = false;
bool Run::flag_help = false;


Run::Run(int argc, char** argv):
		program_name(),
		input(),
		output(),
		output_contents(&Token::print),
		output_start(&Run::initialize_output_normal),
		output_end(&Run::end_output_normal),
		thread_count(-1)
	{
	try {
		this->parse(argc, argv);
	} catch (const std::exception &exc) {
		std::cerr << exc.what() << '\n';
		std::cerr << "usage:" << this->program_name << BASIC_COMPILER_HELP_INFO;
		exit(EXIT_FAILURE);
	}
}

Run& Run::getInstance(int argc, char** argv) {
	static Run singleton_object(argc, argv);
	return singleton_object;
}

void Run::parse(int argc, char** argv) {
	const std::vector<std::string_view> args(argv, argv + argc);
	this->program_name = args[0].data();
	
	for(size_t i = 1; i < args.size();) {
		switch(hash(args[i].data())) {
			case hash("-i"):
			case hash("--input"):
				this->process_input_files(args, ++i);
				break;
			case hash("-o"):
			case hash("--output"):
				this->process_output_files(args, ++i);
				break;
			case hash("-s"):
			case hash("--statistics"):
				++i;
				this->process_statistics();
				std::cout << this->program_name << " warning: The statistics argument is currently disable due to it no being implemented as of yet.\n";
				break;
			case hash("-H"):
			case hash("--HTML"):
				++i;
				this->process_html_output();
				break;
			case hash("-t"):
			case hash("--threads"):
				this->process_threads(args, ++i);
				std::cout << this->program_name << " warning: The threads argument is currently disable due to it no being implemented as of yet.\n";
				break;
			case hash("-v"):
			case hash("--version"):
				++i;
				this->process_version();
				break;
			case hash("-h"):
			case hash("--help"):
				++i;
				this->process_help();
				break;
			default:
				throw std::runtime_error(this->program_name + " error: unknown commandline argument: " + std::string(args[i].data()));
		}
	}
	if(
		(this->input.empty() and this->output.size() > 1) or
		(this->input.size() == 1 and this->output.size() > 1) or
		(this->input.size() > 1 and this->output.size() > 1 and this->input.size() != this->output.size())
	) throw std::runtime_error(this->program_name + " error: Unable to convert input files to corresponding output files due to their number mismatch!");
	this->adjust_thread_behaviour();
}

void Run::operator()(std::istream* in, std::ostream* out) {
	static bool hasRun = false;
	if(hasRun)
		throw std::runtime_error("This method cannot be ran twice!");
	hasRun = true;
	
	if(this->input.empty() and this->output.empty()) {												//	User did not provide any '-i' or '-o' type commandline arguments therefore we take console as input and output
		*out << this->output_start();
		const auto stream = Scanner().operator()(in, out, output_contents);
		*out << stream.str() << this->output_end();
	} else if(this->input.empty() and this->output.size() == 1) {									//	No output files provided and at least one input file provided.
		this->output.begin()->getFile() << this->output_start();
		const auto stream = Scanner().operator()(in, out, output_contents);
		this->output.begin()->getFile() << stream.str() << this->output_end();
	} else if(!this->input.empty() and this->output.empty()) {										//	No output but many input files.
		*out << this->output_start();
		for(auto& in_file : this->input) {
			const auto stream = Scanner().operator()(in_file.getFile(), output_contents);
			*out << stream.str();
		}
		*out << this->output_end();
	}  else if(this->input.size() > 1 and this->output.size() == 1) {
		this->output.begin()->getFile() << this->output_start();
		for(auto& in_file : this->input) {
			const auto stream = Scanner().operator()(in_file.getFile(), output_contents);
			this->output.begin()->getFile() << stream.str();
		}
		this->output.begin()->getFile() << this->output_end();
	} else if(this->input.size() == this->output.size()) {
		auto in_file = std::begin(this->input);
		auto out_file = std::begin(this->output);
		
		while (in_file != std::end(this->input) && out_file != std::end(this->output)) {
			Scanner().operator()(in_file->getFile(), out_file->getFile(), output_contents);
			in_file = std::next(in_file);
			out_file = std::next(out_file);
		}
	}
}
void Run::process_input_files(const std::vector<std::string_view>& arguments, std::size_t& index) {
	//	Make sure that in the future the argument will not be a duplicate
	if(Run::flag_input_files) throw std::runtime_error(this->program_name + " error: cannot use -i/--input parameter twice!");
	Run::flag_input_files = true;
	
	//	Read the next commandline argument;
	while(index < arguments.size() and arguments[index][0] != '-') {
		if (std::filesystem::is_character_file(arguments[index])) {
			this->input.emplace_back(std::string(arguments[index].data()));
		} else if(std::filesystem::is_directory(arguments[index])) {
			for(const auto& file : std::filesystem::recursive_directory_iterator(arguments[index]))
				this->input.emplace_back(file.path().string());
		} else {
			throw std::runtime_error(this->program_name + " error:" + std::string(arguments[index]) + " - No such file or directory in provided path!");
		}
		index++;
	}
	if(this->input.empty()) throw std::runtime_error(this->program_name + " error: No files provided after argument: -i/--input usage!");
}
void Run::process_output_files(const std::vector<std::string_view>& arguments, std::size_t& index) {
	if(Run::flag_output_files) throw std::runtime_error(this->program_name + " error: cannot use -o/--output parameter twice!");
	Run::flag_output_files = true;

	while(index < arguments.size() and arguments[index][0] != '-') {
		if (std::filesystem::is_character_file(arguments[index])) {
			this->output.emplace_back(std::string(arguments[index].data()));
		} else if(std::filesystem::is_directory(arguments[index])) {
			for(const auto& file : std::filesystem::recursive_directory_iterator(arguments[index])) {
				this->output.emplace_back(file.path().string());
			}
		} else {
			throw std::runtime_error(this->program_name + " error:" + std::string(arguments[index]) + " - No such file or directory in provided path!");
		}
		index++;
	}
	if(this->output.empty()) throw std::runtime_error(this->program_name + " error: No files provided after argument: -o/--output usage!");
}
void Run::process_statistics() const {
	if(Run::flag_statistics) throw std::runtime_error(this->program_name + " error: cannot use -s/--statistics parameter twice!");
	Run::flag_statistics = true;
}
void Run::process_html_output() {
	if(Run::flag_html) throw std::runtime_error(this->program_name + " error: cannot use -H/--HTML parameter twice!");
	Run::flag_html = true;

	this->output_contents = &Token::convertToHTML;
	this->output_start = &Run::initialize_output_html;
	this->output_end = &Run::end_output_html;
}
void Run::process_threads(const std::vector<std::string_view>& arguments, std::size_t& index) {
	if(Run::flag_threads) throw std::runtime_error(this->program_name + " error: cannot use -t/--threads parameter twice!");
	Run::flag_threads = true;

	//	Make sure the next argument is integer, because otherwise it would not be possible parse data into an int.
	if(!std::all_of(arguments[index].begin(), arguments[index].end(), ::isdigit)) throw std::runtime_error(this->program_name + " error: The next argument in relation of -t/--threads is not a digit!");
	this->thread_count = std::stoi(arguments[index].data());
	if(this->thread_count < 1) throw std::runtime_error(this->program_name + " error: number of threads to run must be grater or equal one!");
}
void Run::process_version() {
	if(Run::flag_version) throw std::runtime_error(this->program_name + " error: cannot use -v/--version parameter twice!");
	Run::flag_version = true;

	std::cout << this->program_name << " version: " << BASIC_COMPILER_VERSION_MAJOR << "." << BASIC_COMPILER_VERSION_MINOR << "." << BASIC_COMPILER_VERSION_PATCH;
}
void Run::process_help() {
	if(Run::flag_help) throw std::runtime_error(this->program_name + " error: cannot use -h/--help parameter twice!");
	Run::flag_help = true;

	std::cout << "usage:" << this->program_name << " " << BASIC_COMPILER_HELP_INFO;
}
void Run::adjust_thread_behaviour() {

}
std::string Run::initialize_output_normal() {
	return Run::NORMAL_START;
}
std::string Run::end_output_normal() {
	return Run::NORMAL_END;
}
std::string Run::initialize_output_html() {
	return Run::HTML_START;
}
std::string Run::end_output_html() {
	return Run::HTML_END;
}
