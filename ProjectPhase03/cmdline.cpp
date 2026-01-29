#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.h"


void use_arguments(int argc, char **argv){
    bool testCheck = false;
    for(int i =1; i < argc; i++){
        if (std::string(argv[i]) == "--help"){
            std::cout << "Here is some help instructions...\n";
            std::cout << "------Scream\n";
            std::cout << "------Panic\n";
            std::cout << "------Pull yourself together\n";
            exit(0);
        } else if (std::string(argv[i]) == "--test"){
            int result = Catch::Session().run(argc, argv);
            if (result != 0) {
                exit(1);
            }
            else {
                exit(0);
            }
        }
        else {
            std::cerr << "I didn't understand your command";
            exit(1);
        }
    }
}