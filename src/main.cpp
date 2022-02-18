//
// Created by Fatemeh Almodaresi on 2022-02-17.
//

#include "clipp.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <clocale>
#include <map>
#include <filesystem>

#include "progOpts.h"

int goMapMain(const goMap::MapOpts& mapOpts);

int main(int argc, char* argv[]) {
    using namespace clipp;
    using std::cout;
    std::setlocale(LC_ALL, "en_US.UTF-8");


    enum class mode {help, map};
    mode selected = mode::help;

    std::map<std::string, clipp::parameter> cmd_map = {
            {"map", command("map").set(selected, mode::map)}
    };

    goMap::MapOpts mapOpts ;

    auto ensure_file_exists = [](const std::string& s) -> bool {
        bool exists = std::filesystem::exists(s);
        if (!exists) {
            std::string e = "The required input file " + s + " does not seem to exist.";
            throw std::runtime_error{e};
        }
        return true;
    };


    auto mapMode = (
            command("map").set(selected, mode::map),
                    (required("-i", "--inputMap") & values(ensure_file_exists, "input_map_file", mapOpts.inputFile)) % "path to the input Go Map file"
    );


    auto cli = (
            (mapMode | command("help").set(selected,mode::help) ),
                    option("-v", "--version").call([]{std::cout << "version " << "0.0.1" << "\n"; std::exit(0);}).doc("show version"));

    decltype(parse(argc, argv, cli)) res;
    try {
        res = parse(argc, argv, cli);
    } catch (std::exception& e) {
        std::cout << "\n\nParsing command line failed with exception: " << e.what() << "\n";
        std::cout << "\n\n";
//        std::cout << make_man_page(cli, pufferfish::progname);
        return 1;
    }


    if(res) {
        switch(selected) {
            case mode::map: goMapMain(mapOpts);  break;
            case mode::help: std::cout << make_man_page(cli, "GoMap"); break;
        }
    } else {
        std::string nl = "The valid commands to GoMap are : ";
        bool first = true;
        for (auto& kv : cmd_map) {
            nl += (first ? "{" : " ") + kv.first + ",";
            first = false;
        }
        nl.pop_back();
        nl += "}";

        auto b = res.begin();
        auto e = res.end();
        // if there was a command provided
        if (std::distance(b,e) > 0) {
            if (b->arg() == "map") {
                std::cout << make_man_page(mapMode, "goMap");
            } else {
                std::cout << "There is no command \"" << b->arg() << "\"\n";
                std::cout << nl << '\n';
                return 1;
            }
        } else {
            std::cout << nl << '\n';
            return 1;
        }
    }

    return 0;
}
