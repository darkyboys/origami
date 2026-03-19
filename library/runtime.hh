/*
 * Copyright (c) ghgltggamer 2026
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 * This is just a headerfile - Means it doesn't contains any of the implementations with it , For implementation look for the corrosponding .cc file or .cpp file instead
 */

// This file containes the runtime for the Origami Language
#ifndef ORIGAMI_INT_RUNTIME
#define ORIGAMI_INT_RUNTIME
#define ORIGAMI_ARGUMENT 0

#include "lexer.hh"

namespace origami {
    namespace oint {
        struct Type{
            std::string name = "";
            std::vector <std::string> value = {};
        };

        // struct SubFunction{
        //     std::string name;
        //     std::vector<std::string> (*func)(std::vector <std::string> args);
        // };

        struct Function{
            std::string name;
            std::vector<std::string> (*func)(std::vector <std::string> args);
            // std::vector<SubFunction> subfunctions = {};
        };

        bool is_number(std::string token); // tells if is number or not
        bool is_sign(std::string token); // tells if is sign or not
        std::string evaluate(std::vector <std::string> tokens); // Can evaluate operators

        class Runtime{
            private:
                std::vector <origami::oint::Type> variables;
                std::vector <origami::oint::Function> functions;
                friend class Variable;

            public:
                Type* variable(std::string name); // Locate , Set and get a variable directly
                void execute (std::vector <std::string> tokens); // execute the program
                int make_normal (std::string variable, int i); // variation for different type
                std::string make_normal (std::string variable);
                std::vector <std::string> normalize_expression(std::vector <std::string> tokens, uint line = 1); // for normalizing the variable names
                void make_function(std::string name, std::vector<std::string> (*function)(std::vector <std::string> args));
                // void make_sub_function(std::string fname, std::string name, std::vector<std::string> (*function)(std::vector <std::string> args)); // This code is depreceated but might be used in future
                std::string sub_function(std::string fname, std::string name);
        };
    }
}

#endif