## Simple scanner that constructs tokens, which then are used to make C language syntax highlighter. [2023 April]

---
### Description:
1. Language of implementation: `C++20 and CMake as a project manager`. The main CMake file is located on the same level as `main.cpp` file.
2. Input alphabet:
   * `'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'` (letters),
   * `'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'` (numbers),
   * `' ', '\n', '\t', '\v', '\f', '\r'` (white symbols),
   * `';', ':','#', '{', '}', '[',']', '(', ')', '*', '+', '-', '/', '&', '|', '!', '=', '<', '>', ',', '.', '^', '~', '"', '%'` (Operator symbols)
3. Input format: `C programing language` [\[Link\]](https://en.wikipedia.org/wiki/C_(programming_language)) with some limitations such as:
   * No hexadecimal / octal constraints like `Oxadf` or `06615`.
   * Only two constraint types: INT and DOUBLE.
   * No modulo operator and it's derivatives.
   * No advanced compiler variables.
   * Strings are very basic.
   * No character chains.
   * Maybe some other limitations, that I'm not aware at the moment.
4. Tokens list:
   * `KEYWORD` - All `C programing language` keywords like `struct`, `int`, `valotile` [\[Link\]](https://en.cppreference.com/w/c/keyword). With two additions: `false`, `true` boolean constraint values.
   * `IDENTIFIER` - `[a-zA-Z][a-zA-Z0-9]*` that is not a keyword.
   * `LITERAL_INT` - `[0-9]+` stored inside as integer.
   * `LITERAL_DOUBLE` -`[0-9]+\.[0-9]+` stored inside as double.
   * `SPECIAL_CHARACTERS` - `[(){}[]#:;]` single value token.
   * `STRINGS` - `\"[^"]*\"` see no character chains.
   * `OPERATOR` - [\[Link to all the operators implemented\]](https://www.scaler.com/topics/c/operators-in-c/) no modulo related stuff.
   * `WHITE_SYMBOL` - `[ \n\t\v\f\r]+` used to make the output file have the same structure as input file.
5. Transition diagram is located at: `./documentatin/module/automata_table.xlsx`
   * All the state corresponding to a given token code are grouped together. Example: `Operator` token is related to states: *10 - 18*.
   * `Blue` state is the initial state.
   * `Red` state is not accepting state. If the automata finish in this state an error is thrown.
   * `Green` accepting state. If the input stops at this state the corresponding Code token is returned and input is formatted accordingly.
---
### How to use and compilation tips:
1. Used compiler is: `gcc (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders) 12.2.0`
2. Executable file is provided in `./documentation/` directory if you do not feel able to compile this project on your own.
3. How to compile on your own:
   ```shell
   ./config/build_ios.sh    #   Require to set up path to c and cxx compiler in your system in this file.
   make
   make install
   ```
4. Use the program:
   ```shell
   Syntax_Highlighter.exe <path/to/input/file.c> <path/to/output/file.html> [;|\n]
   ```
---
### Important:
1. Example output and input files are provided in `./documentation/example_output/`, `./tests/input/c_programs/` directory accordingly.
2. The only external library is `googletest`, it is used only to test code and is not being used as external code for this program source code. The proof for this is in **all the CMakeLists.txt** files in the project.
3. If you have any problems / concerns regarding a project code please contact project owner. Or create a GitHub Issue and assign the owner.
---
### Algorithm:
1. Inside a scanner object there is a DFA (see `./documentation/module/automata_table.xlsx`)
2. Input from the input file provided is feed to automata and then if accepting state is reached further instructions are given (function pointer) from the current state.
3. The instruction contain how to deal with given data, for example input that lead to double token generation is stored as a double inside a program memory, not as a string.
4. After the token is generated it has print method is run and the output is saved.
5. **O(n)**.
---
### Author:
* Dominik Breksa, dominikbreksa@gmail.com - [\[Link to GitHub profile\]](https://github.com/ForNeus57).
