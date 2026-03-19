/*
 * Copyright (c) ghgltggamer 2026
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 * This is a source file - Means it contains all of the implementations for the corrosponding headerfile with it.
 */

//  A Simple modable lexer for any language.
#include "lexer.hh"


namespace origami {
    namespace oint{
        bool is_brekable(char c){
            if (c == '='){
                return 1;
            }
            else if (c == ' '){
                return true;
            }
            else if (c == '.'){
                return true;
            }
            else if (c == ','){
                return true;
            }
            else if (c == '('){
                return true;
            }
            else if (c == ')'){
                return true;
            }
            else if (c == '{'){
                return true;
            }
            else if (c == '}'){
                return true;
            }
            // else if (c == '['){ // Optional , You can make your own language by moding this config, These 3 lines enables parsing C lol, Because i tested this lexer on C Language and it worked flawlessly
            //     return true;
            // }
            // else if (c == ']'){
            //     return true;
            // }
            // else if (c == ';'){
            //     return true;
            // }
            else if (c == '+'){
                return true;
            }
            else if (c == '-'){
                return true;
            }
            else if (c == '*'){
                return true;
            }
            else if (c == '/'){
                return true;
            }
            else if (c == '%'){
                return true;
            }
            else if (c == '&'){
                return true;
            }
            else if (c == '!'){
                return true;
            }
            else if (c == '|'){
                return true;
            }
            else {
                return false;
            }
        }


        std::vector <std::string> Lexer(std::string code, bool ignore_comma,  bool keep_strings){
            std::vector <std::string> return_value; // tokens

            // Process the code here
            bool is_string_open = false,
                 is_assignment = false,
                 is_comment = false,
                 is_assignment_just_started = false,
                 is_line_just_read = true;
            std::string buffer;
            std::string string_buffer;
            for (std::size_t i = 0;i < code.length();i++){
                if (code[i] == '#' and not is_string_open) is_comment = true;
                if (code[i] == '\n' and not is_string_open){
                    if (is_comment){
                        
                    }
                    // std::cout << "New line!";
                    is_line_just_read = true;
                    is_string_open = false;
                    is_comment = false;
                    is_assignment_just_started = false;
                    is_assignment = false;

                    if (buffer != ""){
                        return_value.push_back(buffer);
                        // std::cout << "Adding buffer, "<<buffer<<"\n";// For debugging 
                    } 
                    if (string_buffer != "") {
                        if (keep_strings){
                            return_value.push_back("\"" + string_buffer + "\"");
                        }
                        else {
                            return_value.push_back("\"" + string_buffer);
                        }
                        // std::cout << "Adding str buffer, "<<buffer<<"\n";// For debugging 
                    }

                    buffer.clear();
                    string_buffer.clear();
                    return_value.push_back("\n");
                    continue;
                }

                if (is_comment) continue;

                if (code[i] != ' ' and is_line_just_read) is_line_just_read = false;

                if (code[i] == '"'){
                    if (is_string_open and code[i-1] == '\\'){
                        string_buffer.pop_back();
                        string_buffer += '"';
                        continue;
                    }
                    is_string_open = not (is_string_open); // Change the state to exact opposite
                    continue;
                }


                if (is_brekable(code[i]) and not is_string_open){
                    // std::cout << "Adding BFR: "<<buffer<<"\n";
                    if (buffer != ""){
                        return_value.push_back(buffer);
                        buffer.clear();
                    }


                    if (string_buffer != ""){
                        if (keep_strings){
                            return_value.push_back("\"" + string_buffer + "\""), string_buffer.clear();
                        }
                        else {
                            return_value.push_back("\"" + string_buffer), string_buffer.clear();
                        }
                    }

                    // State machine
                    if (code[i] == '='){
                        is_assignment = true;
                        is_assignment_just_started = true;
                    }
                    else if (code[i] == '=' and is_assignment){
                        std::cerr << "Error: Can not assign the value multiple times in an ongoing assignment.\n";
                        std::exit (1);
                    }


                    // Feel free to remove this , symbol , And add here other symbols that you wanna break but not include, This is here because it's easier for origami's parser to parse origami from it, But if you are writing a lexer for something like python , Java or C or even C++ then feel free to write exactly what you want and what you don't.
                    if (code[i] == ',' and ignore_comma){
                        continue;
                    }

                    if (code[i] == '-'){
                        if (code[i+1] != ' '){
                            buffer = "-";
                            for (std::size_t x = i+1;x < code.length();x++){
                                if (is_brekable(code[x])){
                                    break;
                                }
                                if (code[x] > '9' or code[x] < '0'){
                                    std::cerr << "Error: Can not use - symbol to declare variable names.\n";
                                    std::exit (3);
                                }
                                buffer += code[x];
                                i = x;
                            }
                            continue;
                        }
                    }


                    // Remove this if statement if you want whitespaces in your code to be tracked as well.
                    if (code[i] == ' ') continue;

                    std::string symbol = "";
                    symbol += code[i];
                    return_value.push_back(symbol);
                    // std::cout << "Adding: "<<symbol<<"\n"; // For debugging 
                    continue;
                }



                if (is_string_open){
                    string_buffer += code[i];
                }


                else {
                    buffer += code[i];
                }
            }


            if (!buffer.empty()) {
               return_value.push_back(buffer);
            }
            if (!string_buffer.empty()) {
                if (keep_strings){
                    return_value.push_back("\"" + string_buffer + "\"");
                }
                else {
                    return_value.push_back("\"" + string_buffer); // keep the quote prefix for parser
                }
            }
        
            return return_value;
        }
    }
}
