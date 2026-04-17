/*
 * Copyright (c) ghgltggamer 2026
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 * This is just a headerfile - Means it doesn't contains any of the implementations with it , For implementation look for the corrosponding .cc file or .cpp file instead
 */

// This file containes the subfunction normalizer for the Origami Language
#ifndef ORIGAMI_SUBFUNCTION
#define ORIGAMI_SUBFUNCTION

#include <vector>
#include <string>
#include <cctype>
#include "subfunction.hh"

namespace origami {
namespace oint {

bool is_identifier(const std::string& s) {
    if (s.empty()) return false;
    if (!std::isalpha(s[0]) && s[0] != '_') return false;
    for (char c : s) {
        if (!std::isalnum(c) && c != '_') return false;
    }
    return true;
}

// =========================
// Extract ( ... ) safely
// =========================
Tokens extract_paren(const Tokens& tokens, int& i) {
    Tokens out;

    if (i >= tokens.size() || tokens[i] != "(") return out;

    int depth = 0;

    while (i < tokens.size()) {
        if (tokens[i] == "(") depth++;
        if (tokens[i] == ")") depth--;

        out.push_back(tokens[i]);
        i++;

        if (depth == 0) break;
    }

    return out;
}

// forward declaration
Tokens process(const Tokens& tokens);

// =========================
// Recursive argument processing
// =========================
Tokens process_args(const Tokens& args) {
    if (args.size() <= 2) return args; // ()

    Tokens inner(args.begin() + 1, args.end() - 1);

    // 🔥 recursion
    inner = process(inner);

    Tokens result;
    result.push_back("(");
    result.insert(result.end(), inner.begin(), inner.end());
    result.push_back(")");

    return result;
}

// =========================
// Join tokens → string
// =========================
std::string join_tokens(const Tokens& tokens) {
    std::string result;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& t = tokens[i];

        if (t == "\n") {
            result += "\n";
            continue;
        }

        if (t == "(" || t == ")" || t == "," || t == ".") {
            result += t;
            continue;
        }

        if (!result.empty() &&
            result.back() != '\n' &&
            result.back() != '(' &&
            result.back() != ' ')
            result += " ";

        result += t;
    }

    return result;
}

// =========================
// MAIN PROCESSOR
// =========================
Tokens process(const Tokens& tokens) {
    Tokens out;

    for (int i = 0; i < tokens.size();) {

        // Detect base call
        if (i + 1 < tokens.size() &&
            is_identifier(tokens[i]) &&
            tokens[i + 1] == "(") {

            std::string base = tokens[i];
            i++; // move to '('

            Tokens base_args = extract_paren(tokens, i);
            base_args = process_args(base_args);

            struct Part {
                std::string name;
                Tokens args;
            };

            std::vector<Part> chain;
            chain.push_back({base, base_args});

            // Collect chained calls (supports newline)
            while (true) {
                int j = i;

                // skip newlines
                while (j < tokens.size() && tokens[j] == "\n") j++;

                if (j >= tokens.size() || tokens[j] != ".")
                    break;

                j++; // skip '.'

                while (j < tokens.size() && tokens[j] == "\n") j++;

                if (j < tokens.size() &&
                    is_identifier(tokens[j]) &&
                    j + 1 < tokens.size() &&
                    tokens[j + 1] == "(") {

                    std::string name = tokens[j];
                    j++; // move to '('

                    Tokens args = extract_paren(tokens, j);
                    args = process_args(args);

                    chain.push_back({name, args});
                    i = j; // commit
                } else {
                    break;
                }
            }

            // =========================
            // EMIT (FIXED ORDER)
            // =========================

            if (chain.size() == 1) {
                out.push_back(base);
                out.insert(out.end(), base_args.begin(), base_args.end());
                continue;
            }

            // 🔥 1. Emit SUBFUNC first
            for (size_t k = 1; k < chain.size(); ++k) {
                out.push_back(base + "_SUBFUNC_" + chain[k].name);
                out.insert(out.end(), chain[k].args.begin(), chain[k].args.end());
                out.push_back("\n");
            }

            // 🔥 2. Then emit original call
            if (base_args.size() > 2) {
                out.push_back(base);
                out.insert(out.end(), base_args.begin(), base_args.end());
                out.push_back("\n");
            }

            continue;
        }

        // Default copy
        out.push_back(tokens[i++]);
    }

    return out;
}

// =========================
// FINAL API
// =========================
std::string subfunction(const Tokens& tokens) {
    Tokens processed = process(tokens);
    return join_tokens(processed);
}

} // namespace oint
} // namespace origami
#endif