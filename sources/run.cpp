//
// Created by Dominik on 28.03.2023.
//

#include "run.h"


bool Run::flag_input_files = false;
bool Run::flag_output_files = false;
bool Run::flag_statistics = false;
bool Run::flag_html = false;
bool Run::flag_threads = false;
bool Run::flag_version = false;
bool Run::flag_help = false;


Run::Run(int argc, char** argv): program_name(), input(), output(), output_format(&Token::print), thread_count(-1) {
	try {
		this->parse(argc, argv);
	} catch (const std::exception &exc) {
		std::cerr << exc.what() << '\n';
		std::cerr << "usage:" + this->program_name + " [-i|--input] <input_files> [-o|--output] <output_files> [-s|--statistics] [-H|--HTML] [-t|--threads] <integer_count> [-h|--help] [-v|--version];\n";
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
				break;
			case hash("-H"):
			case hash("--HTML"):
				++i;
				this->process_html_output();
				break;
			case hash("-t"):
			case hash("--threads"):
				this->process_threads(args, ++i);
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
}

void Run::start() {
	static bool hasRun = false;
	if(hasRun)
		throw std::runtime_error("This method cannot be ran twice!");
	hasRun = true;
/*
	if(files.empty()) {													//	User did not provide any '-i' or '-o' type commandline arguments therefore we take console as input and output
		if(threads != -1) std::cout << "BasicCompiler.exe warning: parameter -t|--threads " + std::to_string(threads) + " is not being used since the input is done by console.\n";
		if(statistics) {
			std::cerr << "BasicCompiler.exe: unable to calculate statistics of a file/files, without any input files!\n";
			exit(EXIT_FAILURE);
		}
		std::string line;
		Scanner s{};
		while(true) {
			std::cin >> line;
			s.addNextLine(line);
			while(!s.isEmpty()) {										//	Generate all the tokens in this line.
				try {
					Token t = s.getToken();									//	I use a method call instead of a function, but I think, that it isn't much of a problem.
					std::cout << (t.*token_output)() << '\n';
				} catch(const WrongInputAlphabet& err){
					std::cout << err.what();
					break;
				}
			}
		}
	} else if(files.size() == 1 and !files.begin()->first.empty()) {	//	No output files provided and at least one input file provided.

	} else if() {

	}

	for(const auto& [input, output] : files) {
		std::ifstream input_file(input.data(), std::ifstream::in);
		std::ofstream output_file(output.data(), std::ofstream::out);
		if(!input_file.is_open()) {
			std::cerr << "BasicCompiler.exe: could not open input file '" << input << "'!\n";
			exit(EXIT_FAILURE);
		}
		if(!output_file.is_open()) {
			std::cerr << "BasicCompiler.exe: could not open input file '" << output << "'!\n";
			exit(EXIT_FAILURE);
		}
	}*/
}
void Run::process_input_files(const std::vector<std::string_view>& arguments, std::size_t& index) {
	//	Make sure that in the future the argument will not be a duplicate
	if(Run::flag_input_files) throw std::runtime_error(this->program_name + " error: cannot use -i/--input parameter twice!");
	Run::flag_input_files = true;

	//	Read the next commandline argument;
	while(arguments[index][0] != '-' and index < arguments.size()) {
		if (!std::filesystem::is_character_file(arguments[index])) throw std::runtime_error(this->program_name + " error:" + std::string(arguments[index]) + " - No such file in provided path!");
			this->input.emplace_back(arguments[index].data());
		index++;
	}
	if(this->input.empty()) throw std::runtime_error(this->program_name + " error: No files provided after argument: -i/--input usage!");
}
void Run::process_output_files(const std::vector<std::string_view>& arguments, std::size_t& index) {
	if(Run::flag_output_files) throw std::runtime_error(this->program_name + " error: cannot use -o/--output parameter twice!");
	Run::flag_output_files = true;

	while(arguments[index][0] != '-' and index < arguments.size()) {
		if (!std::filesystem::is_character_file(arguments[index])) throw std::runtime_error(this->program_name + " error:" + std::string(arguments[index]) + " - No such file in provided path!");
			this->output.emplace_back(arguments[index].data());
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

	this->output_format = &Token::convertToHTML;
}
void Run::process_threads(const std::vector<std::string_view>& arguments, std::size_t& index) {
	if(Run::flag_threads) throw std::runtime_error(this->program_name + " error: cannot use -t/--threads parameter twice!");
	Run::flag_threads = true;

	//	Make sure the next argument is integer, because otherwise it would not be possible parse data.
	if(!std::all_of(arguments[index].begin(), arguments[index].end(), ::isdigit)) throw std::runtime_error(this->program_name + " error: The next argument in relation of -t/--threads is not a digit!");
	this->thread_count = std::stoi(arguments[index].data());
	if(this->thread_count < 1) throw std::runtime_error(this->program_name + " error: number of threads to run must be grater or equal one!");
}
void Run::process_version() {
	if(Run::flag_version) throw std::runtime_error(this->program_name + " error: cannot use -v/--version parameter twice!");
	Run::flag_version = true;

	std::cout << this->program_name << " version: " << VERSION;
}
void Run::process_help() {
	if(Run::flag_help) throw std::runtime_error(this->program_name + " error: cannot use -h/--help parameter twice!");
	Run::flag_help = true;

	std::cout << "usage:" << this->program_name << " " << HELP_INFO;
}