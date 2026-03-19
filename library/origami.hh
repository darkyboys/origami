/*
 * Copyright (c) ghgltggamer 2026
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 * This is just a headerfile - Means it doesn't contains any of the implementations with it , For implementation look for the corrosponding .cc file or .cpp file instead
 */

// This file containes the abstractions for the origami language
#ifndef ORIGAMI_LANG
#define ORIGAMI_LANG

#include "lexer.hh"
#include "runtime.hh"
#include "subfunction.hh"
#include <fstream>
#include <string>

namespace origami {
    typedef std::vector<std::string> function;
    class ProgramFile {
        public:
            std::string code;
            ProgramFile(std::string file_name){
                std::ifstream ifile (file_name);
                if (ifile.is_open()){
                    std::string temp;
                    while (std::getline(ifile, temp)){
                        code += temp + '\n';
                    }
                }
                else {
                    std::cerr << "Origami Startup Error: Couldn't load the file "<<file_name;
                    std::exit(2);
                }
            }
            oint::Runtime runtime;

            void run(){
                code = origami::oint::subfunction(
                    oint::Lexer(code, 0, 1)
                );

                runtime.execute(
                    origami::oint::Lexer(code)   
                );
            }
    };

    class Program{
        public:
            std::string code;
            Program(std::string code_) : code(code_){}
            oint::Runtime runtime;
            void run(){
                code = origami::oint::subfunction(
                    oint::Lexer(code, 0, 1)
                );
                runtime.execute(
                    origami::oint::Lexer(code)   
                );
            }
    };
}

#endif