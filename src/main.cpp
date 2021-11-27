#include <cstdlib>
#include <memory>
#include <functional>
#include <map>

#include <iostream>

#include "ezOptionParser.hpp"

#include "Parser.h"
#include "Compiler.h"

#define EXEHEADER16 "GR16"
#define EXEHEADER32 "GR32"

int main(int argc, char **argv) {
    ez::ezOptionParser opt;

    opt.overview = "soda compiler";
    opt.syntax = std::string(argv[0]) + " [OPTIONS] [runfile]\n";
    opt.example = std::string(argv[0]) + " -o test.obj file.soda\n";
    opt.footer = std::string(argv[0]) + " v" + std::string(VERSION) + "\n";

    opt.add(
        "", // Default.
        0, // Required?
        0, // Number of args expected.
        0, // Delimiter if expecting multiple args.
        "Display usage instructions.", // Help description.
        "-h"     // Flag token.
    );

    opt.add(
        "a.obj", // Default.
        0, // Required?
        1, // Number of args expected.
        0, // Delimiter if expecting multiple args.
        "Output file", // Help description.
        "-o"     // Flag token.
    );

    opt.add(
        "32", // Default.
        0, // Required?
        0, // Number of args expected.
        0, // Delimiter if expecting multiple args.
        "CPU type (16,32)", // Help description.
        "-c"     // Flag token.
    );

    opt.add(
        "", // Default.
        0, // Required?
        0, // Number of args expected.
        0, // Delimiter if expecting multiple args.
        "assembly output", // Help description.
        "-s"     // Flag token.
    );

    opt.parse(argc, (const char**)argv);

    if (opt.isSet("-h")) {
        std::string usage;
        opt.getUsage(usage);
        std::cout << usage << std::endl;
        exit(1);
    }

    int cpu;
    opt.get("-c")->getInt(cpu);

    std::string filename = *opt.lastArgs[0];
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Could not open `" << filename << "'" << std::endl;
        exit(-1);
    }

    std::stringstream buffer;
    buffer << infile.rdbuf();

    auto tokens = parse(buffer.str());
    //for (auto token : tokens) {
    //    std::cerr << token.toString() << std::endl;
    //}

    auto asmTokens = compile(cpu, tokens);
    std::cerr << asmTokens.size() << std::endl;
    for (const auto token : asmTokens) {
        std::cout << token.toString() << std::endl;
    }
}
