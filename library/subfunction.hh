/*
 * Copyright (c) ghgltggamer 2026
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 * This is just a headerfile - Means it doesn't contains any of the implementations with it , For implementation look for the corrosponding .cc file or .cpp file instead
 */

// This file containes the subfunction normalizer for the Origami Language
#include <vector>
#include <string>
#include <cctype>
using Tokens = std::vector<std::string>;

namespace origami {
    namespace oint {
        // subfunction.hh
        bool is_identifier(const std::string& s);
        Tokens extract_paren(const Tokens&, int&);
        Tokens process_args(const Tokens&);
        std::string join_tokens(const Tokens&);
        Tokens process(const Tokens&);
        std::string subfunction(const Tokens&);
    }
}