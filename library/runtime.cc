/*
 * Copyright (c) ghgltggamer 2026
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 * This is a source file - Means it contains all of the implementations for the corrosponding headerfile with it.
 */

// This file containes the runtime for the Origami Language
#include "runtime.hh"
#include <string>

namespace origami {
    namespace oint {

        bool is_number(std::string token){
            bool rval = 1;

            for (char c : token){
                if (c == '-') continue;
                if (c > '9' or c < '0'){
                    rval = 0;
                    break;
                }
            }

            return rval;
        }

        bool is_sign(std::string token){
            bool sign = 0;
            if (
                token == "+" ||
                token == "-" ||
                token == "*" ||
                token == "/" ||
                token == "%" ||
                token == "&" ||
                token == "|" ||
                token == "=" ||
                token == "<" ||
                token == ">" ||
                token == "!" 
            ) sign = 1;
            return sign;
        }


        std::string evaluate(std::vector <std::string> tokens){
            std::string result = "0";

            if (tokens.size() == 1){
                return tokens[0];
            }
            if (tokens.size() == 0){
                return result;
            }

            if(tokens.size() == 2){
                if (tokens[0] == "!"){
                    if (not is_number(tokens[1])){
                        std::cerr << "Error: Needs a valid number.\n";
                        std::exit(3);
                    }
                    result = std::to_string(!std::stoi(tokens[1]));
                    // std::cout << "Result: "<<result<<"\n";

                }

                if (is_sign(tokens[0])){
                    tokens.insert(tokens.begin(), "0");
                }
                else if (is_sign(tokens[1])){
                    tokens.insert(tokens.end(), "0");
                }
                else {
                    tokens.insert(tokens.begin()+1, "*");
                }
            }

            for (std::size_t i = 0; i < tokens.size(); i++){
                if (tokens[i] == "") continue;
                if (tokens[i] == "!"){
                    // std::cout << "Got it!\n";
                    std::vector<std::string> rside_tokens = {};
                    for (std::size_t x = i+1; x < tokens.size(); x++){
                        rside_tokens.push_back(tokens[x]);
                        tokens[x] = "";
                    }

                    std::string rside = evaluate(rside_tokens);

                    result = std::to_string(!std::stoi(rside));
                    // std::cout << "Result: "<<result<<"\n";
                    tokens[i+1] = result;
                    continue;
                }
                if (i > 0 && i < tokens.size()-1){

                    // ---------------- + ----------------
                    if (tokens[i] == "+"){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        if (lside[0] == '"'){
                            result = "\"" + lside.substr(1) + rside;
                        }
                        else {
                            if (!(is_number(lside)) || !(is_number(rside))){
                                std::cerr << "Error\n";
                                std::exit(3);
                            }
                            result = std::to_string(std::stoi(lside) + std::stoi(rside));
                        }

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- - ----------------
                    else if (tokens[i] == "-"){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        if (!(is_number(lside)) || !(is_number(rside))){
                            std::cerr << "Error\n";
                            std::exit(3);
                        }

                        result = std::to_string(std::stoi(lside) - std::stoi(rside));

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- * ----------------
                    else if (tokens[i] == "*"){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        if (!(is_number(lside)) || !(is_number(rside))){
                            std::cerr << "Error\n";
                            std::exit(3);
                        }

                        result = std::to_string(std::stoi(lside) * std::stoi(rside));

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- / ----------------
                    else if (tokens[i] == "/"){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        if (!(is_number(lside)) || !(is_number(rside))){
                            std::cerr << "Error\n";
                            std::exit(3);
                        }

                        if (rside == "0"){
                            std::cerr << "Divide by zero\n";
                            std::exit(0);
                        }

                        result = std::to_string(std::stoi(lside) / std::stoi(rside));

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- % ----------------
                    else if (tokens[i] == "%"){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        if (!(is_number(lside)) || !(is_number(rside))){
                            std::cerr << "Error\n";
                            std::exit(3);
                        }

                        if (rside == "0"){
                            std::cerr << "Divide by zero\n";
                            std::exit(0);
                        }

                        result = std::to_string(std::stoi(lside) % std::stoi(rside));

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- < ----------------
                    else if (tokens[i] == "<"){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        result = std::to_string(std::stoi(lside) < std::stoi(rside));

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- > ----------------
                    else if (tokens[i] == ">"){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        result = std::to_string(std::stoi(lside) > std::stoi(rside));

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- = ----------------
                    else if (tokens[i] == "="){
                        std::vector<std::string> lside_tokens = {};
                        for (std::size_t x = 0; x < i; x++){
                            lside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string lside = evaluate(lside_tokens);
                        std::string rside = evaluate(rside_tokens);

                        if (lside[0] == '"' or rside[0] == '"'){
                            result = (lside == rside) ? "1" : "0";
                        }
                        else {
                            result = std::to_string(std::stoi(lside) == std::stoi(rside));
                        }

                        tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- & ----------------
                    else if (tokens[i] == "&"){
                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string rside = evaluate(rside_tokens);

                        result = std::to_string(std::stoi(tokens[i-1]) && std::stoi(rside));

                        tokens[i-1] = tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- | ----------------
                    else if (tokens[i] == "|"){
                        std::vector<std::string> rside_tokens = {};
                        for (std::size_t x = i+1; x < tokens.size(); x++){
                            rside_tokens.push_back(tokens[x]);
                            tokens[x] = "";
                        }

                        std::string rside = evaluate(rside_tokens);

                        result = std::to_string(std::stoi(tokens[i-1]) || std::stoi(rside));

                        tokens[i-1] = tokens[i] = "";
                        tokens[i+1] = result;
                    }

                    // ---------------- ! ----------------
                    // else if (tokens[i] == "!"){
                        
                    // }
                }
            }

            return result;
        }













        // Class functions
        Type* Runtime::variable(std::string name) {
            for (Type& t : variables) {
                if (t.name == name) {
                    return &t;
                }
            }
            return nullptr;
        }



        int Runtime::make_normal (std::string variable, int i){
            int rval = 0;
            if (is_number(variable)){
                rval = std::stoi(variable);
            }
            return rval;
        }



        std::string Runtime::make_normal (std::string variable){
            std::string rval = variable;
            if (variable[0] == '"'){
                rval = variable.substr(1);
            }
            return rval;
        }




        void Runtime :: make_function(std::string name, std::vector<std::string> (*function)(std::vector <std::string> args)){
            bool is_defined = false;
            for (Function func: functions){
                if (func.name == name){
                    is_defined = true;
                    func.func = function;
                    break;
                }
            }

            if (not is_defined){
                Function new_function;
                new_function.name = name;
                new_function.func = function;
                functions.push_back(new_function);
            }
        }



        std::vector <std::string> Runtime :: normalize_expression(std::vector <std::string> tokens, uint line){
            std::vector <std::string> rval;
            for (long long i = 0;i < tokens.size();i++){
                // std::cout << tokens[i]<<"\n";
                if (not(is_number(tokens[i])) and not(tokens[i][0] == '"') and not(tokens[i][0] == '(') and not (is_sign(tokens[i]))){
                    bool is_var = false;
                    if (i+1 < tokens.size()){
                        if (tokens[i+1][0] == '(') continue;
                    }
                    // std::cout << "Inside: "<<tokens[i]<<"\n\n";
                    for (Type& t : variables){
                        if (t.name == tokens[i]){
                            // std::cout << "Set: "<<tokens[i]<<"\n";
                            // value = t.value;
                            for (std::size_t y = 0;y < t.value.size();y++){
                                rval.push_back(t.value[y]);
                                // std::cout << "Pushing: "<<t.value[y]<<"\n";
                            }
                            is_var = true;
                            break;
                        }
                    }
                    if (not is_var){
                        std::cout << tokens[i+1]<<"\n";
                        std::cerr << "Error: At line "<<line<<", Can not assign a value of an undefined variable.\n"<<tokens[i]<<"\n";
                        std::exit (3);      
                    }
                }
                else if (tokens[i][0] == '('){
                    if (i-1 < 0){
                        std::cerr << "Error: At line "<<line<<", Can not call an unnamed function.\n";
                        std::exit (3);
                    }

                    std::string func_name = tokens[i-1];
                    std::vector <std::string> args;
                    std::size_t parenthesis_level = 0;
                    bool is_nested_function_present = false;
                    for (std::size_t x = i+1;x < tokens.size();x++){
                        if (tokens[x] == "\n") continue;
                        if (tokens[x][0] == '(') parenthesis_level += 1, is_nested_function_present = true;
                        if (tokens[x][0] == ')' and not parenthesis_level) {i = x+1;break;}
                        if (tokens[x][0] == ')' and parenthesis_level) parenthesis_level -= 1;
                        args.push_back(tokens[x]);
                    }

                    // std::cout << "Came here!\n";
                    
                    std::vector <std::string> real_args = normalize_expression(args);
                    for (std::size_t z = 0;z < real_args.size();z++){
                        if (real_args[z][0] == '"'){
                            real_args[z] = real_args[z].substr(1);
                        }
                    }

                    bool is_called = false;

                    for (std::size_t y = 0;y < functions.size();y++){
                        if (functions[y].name == func_name){
                            std::vector <std::string> rvalx = functions[y].func(real_args);
                            for (std::string s : rvalx){
                                if (is_number(s)){
                                    rval.push_back(s);
                                }
                                else {
                                    rval.push_back("\"" + s);
                                }
                            }

                            // for (std::string st : rval){
                            //     std::cout << st << "\n";
                            // }
                            
                            is_called = true;
                            break;
                        }
                    }

                    if (not is_called){
                        std::cerr << "Error: At line "<<line<<", Can not call an undefined function.\n";
                        std::exit (3);
                    }
                }
                else {
                    // std::cout << "Lushing: "<<tokens[i]<<"\n";
                    rval.push_back(tokens[i]);
                }
            }
            return rval;
        }


        void Runtime :: execute (std::vector <std::string> tokens){
            uint lines = 0;
            // std::cout << "St\n";
            // for (long long i = 0;i < tokens.size();i++){
            //     // std::cout << tokens[i]<<"\n";
            // }
            // std::cout << "End\n";

            for (long long i = 0;i < tokens.size();i++){
                // std::cout << i<<" and "<<tokens[i]<<'\n';

                // if else statements
                if (tokens[i] == "if"){
                    // std::cout << "If is called!\n";
                    std::vector <std::string> condition;
                    for (long long x = i+1;x < tokens.size();x++){
                        i = x;
                        if (tokens[x] == "\n") continue;
                        if (tokens[x] == "{") break;
                        condition.push_back(tokens[x]);
                        // std::cout << "Condition Token:"<<tokens[x]<<"\n";
                    }
                    // std::cout << i<<" and "<<tokens[i]<<'\n';
                    


                    std::size_t bracket_level = 0;
                    std::vector <std::string> body;
                    for (long long y = i+1;y < tokens.size();y++){
                        // if (tokens[y] == "\n") continue;
                        if (tokens[y] == "{") bracket_level += 1;
                        if (tokens[y] == "}" and not bracket_level){
                            i = y;
                            break;
                        }
                        if (tokens[y] == "}" and bracket_level) bracket_level -= 1;
                        body.push_back(tokens[y]);
                    }

                    // for (std::string s : body){
                    //     // std::cout <<"Body: "<< s << "\n";
                    // }

                    // std::cout << "This if ran till here!\n";
                    if (evaluate(normalize_expression(condition)) != "0"){
                        execute(body);
                    }
                    else {
                        if (i+1 < tokens.size()){
                            if (tokens[i+1] == "{"){
                                // std::cout << "Can run else !\n";
                                std::size_t bracket_level = 0;
                                std::vector <std::string> body;
                                for (long long y = i+1;y < tokens.size();y++){
                                    // if (tokens[y] == "\n") continue;
                                    if (tokens[y] == "{") bracket_level += 1;
                                    if (tokens[y] == "}" and not bracket_level){
                                        i = y;
                                        break;
                                    }
                                    if (tokens[y] == "}" and bracket_level) bracket_level -= 1;
                                    body.push_back(tokens[y]);
                                }

                                execute(body);
                            } 
                            else {
                                // std::cout << "Can not run else!\n";
                            }
                        }
                    }
                }







                if (tokens[i] == "while"){
                    // std::cout << "If is called!\n";
                    std::vector <std::string> condition;
                    for (long long x = i+1;x < tokens.size();x++){
                        i = x;
                        if (tokens[x] == "\n") continue;
                        if (tokens[x] == "{") break;
                        condition.push_back(tokens[x]);
                        // std::cout << "Condition Token:"<<tokens[x]<<"\n";
                    }
                    // std::cout << i<<" and "<<tokens[i]<<'\n';
                    


                    std::size_t bracket_level = 0;
                    std::vector <std::string> body;
                    for (long long y = i+1;y < tokens.size();y++){
                        // if (tokens[y] == "\n") continue;
                        if (tokens[y] == "{") bracket_level += 1;
                        if (tokens[y] == "}" and not bracket_level){
                            i = y;
                            break;
                        }
                        if (tokens[y] == "}" and bracket_level) bracket_level -= 1;
                        body.push_back(tokens[y]);
                    }

                    // for (std::string s : body){
                    //     // std::cout <<"Body: "<< s << "\n";
                    // }

                    // std::cout << "This if ran till here!\n";
                    while (evaluate(normalize_expression(condition)) != "0"){
                        execute(body);
                    }
                }





                if (tokens[i] == "times"){
                    // std::cout << "If is called!\n";
                    if (i+2 == tokens.size()){
                        std::cerr << "Error: times needs an identifier value at the least\n";
                        std::exit (3);
                    }
                    if (tokens[i+1] == "{"){
                        std::cerr << "Error: times needs an identifier value at the least\n";
                        std::exit (3);
                    }

                    std::string name = tokens[i+1];
                    std::vector <std::string> condition;
                    for (long long x = i+2;x < tokens.size();x++){
                        i = x;
                        if (tokens[x] == "\n") continue;
                        if (tokens[x] == "{") break;
                        condition.push_back(tokens[x]);
                        // std::cout << "Condition Token:"<<tokens[x]<<"\n";
                    }
                    // std::cout << i<<" and "<<tokens[i]<<'\n';
                    


                    std::size_t bracket_level = 0;
                    std::vector <std::string> body;
                    for (long long y = i+1;y < tokens.size();y++){
                        // if (tokens[y] == "\n") continue;
                        if (tokens[y] == "{") bracket_level += 1;
                        if (tokens[y] == "}" and not bracket_level){
                            i = y;
                            break;
                        }
                        if (tokens[y] == "}" and bracket_level) bracket_level -= 1;
                        body.push_back(tokens[y]);
                    }

                    // for (std::string s : body){
                    //     // std::cout <<"Body: "<< s << "\n";
                    // }

                    // std::cout << "This if ran till here!\n";
                    Type var_temp;
                    var_temp.name = name;
                    var_temp.value = {};
                    variables.insert(variables.begin(), var_temp);


                    std::vector <std::string> cond = normalize_expression(condition);

                    for (long long i = 0;i < cond.size();i++){
                        variable(name)->value = {cond[i]};
                        execute(body);
                    }
                }







                if (tokens[i] == "="){
                    if (i-1 < 0){
                        std::cerr << "Error: At line "<<lines<<", Can not define a variable without it's name.\n";
                        std::exit (3);                 
                    }
                    else {
                        std::vector <std::string> value;
                        std::size_t x_loc = 0;
                        for (std::size_t x = i+1;x < tokens.size();x++){
                            if (tokens[x] == "\n") break;
                            value.push_back(tokens[x]);
                            x_loc = x;
                            // std::cout << tokens[x]<<"\n\n";
                        }

                        value = normalize_expression(value);
                        lines += 1;
                        x_loc++;
                        
                        bool is_array = true;
                        for (std::string v : value){
                            if (v[0] != '"') {
                                is_array = false;
                                break;
                            }
                        }

                        // for (std::string s : value){
                        //             std::cout <<"Value: "<< s<<"\n";
                        //         }

                        bool is_var = false;
                        for (Type& t : variables){
                            if (t.name == tokens[i-1]){
                                t.value = {evaluate(value)};
                                is_var = true;
                                break;
                            }
                        }

                        if (not is_var){
                            Type var;
                            var.name = tokens[i-1];
                            // for (std::string s : value){
                            //         std::cout <<"Value: "<< s<<"\n";
                            //     }
                            var.value = {evaluate(value)};
                            // std::cout << "Made variable, "<<tokens[i-1]<<"\n";
                            variables.push_back(var);
                            // std::cout << variables.size()<<"\n";
                        }
                        i = x_loc;
                    }
                    continue;
                }



                if (tokens[i] == "("){
                    if (i-1 < 0){
                        std::cerr << "Error: Can not call an unnamed function.\n";
                        std::exit(3);
                    }

                    std::vector <std::string> function = {tokens[i-1], tokens[i]};
                    std::size_t parenthesis_level = 0;
                    for (long long x = i+1;x < tokens.size();x++){
                        // std::cout << "Token: "<<tokens[x]<<"\n";
                        i = x;
                        if (tokens[x] == "\n") continue;
                        if (tokens[x] == "("){
                            parenthesis_level += 1;
                        }
                        if (tokens[x] == ")" and not parenthesis_level){
                            function.push_back(tokens[x]);
                            break;
                        }
                        if (tokens[x] == ")" and parenthesis_level){
                            parenthesis_level -= 1;
                        }
                        function.push_back(tokens[x]);
                    }

                    std::vector <std::string> result = normalize_expression(function);

                    // for (std::string func : function){
                    //     // std::cout << func << "\n\n\n";
                    // }
                }
            }
        }
    }
}