/*
 * Copyright (c) ghgltggamer 2026
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 * This is just a headerfile - Means it doesn't contains any of the implementations with it , For implementation look for the corrosponding .cc file or .cpp file instead
 */

// This file containes the lexer/tokenizer for the Origami Language

#ifndef ORIGAMI_INT_LEXER
#define ORIGAMI_INT_LEXER 

#include <iostream>
#include   <vector>
#include   <string>

namespace origami {
    namespace oint{
        std::vector <std::string> Lexer(std::string code, bool ignore_comma = true, bool keep_strings = false);
        bool is_brekable(char c);
    }
}

#endif