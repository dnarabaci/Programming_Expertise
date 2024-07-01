#include <iostream>
#include "include/argparse.hpp"

void showHelp() {
    std::cout << "Usage: Goobo_Parser [options]\n"
              << "Options:\n"
              << "  -h, --help      Show this help message and exit\n"
              << "  -v, --version   Show the application version and exit\n"
              << "  --name NAME     Specify the name\n"
              << std::endl;
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program("Goobo_Parser");

    program.add_argument("-v", "--version")
        .help("show the application version")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("--name")
        .help("specify the name")
        .default_value(std::string("default_name"))
        .required();

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        showHelp();
        return 1;
    }

    if (program["-v"] == true) {
        std::cout << "Goobo_Parser version 1.0" << std::endl;
        return 0;
    }

    if (program.is_used("--help")) {
        showHelp();
        return 0;
    }

    std::string name = program.get<std::string>("--name");
    std::cout << "Name specified: " << name << std::endl;

    return 0;
}
