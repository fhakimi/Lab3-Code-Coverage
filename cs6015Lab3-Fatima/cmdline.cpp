//
//  cmdline.cpp
//  ProjectPhase3
//
//  Created by Fatima on 1/29/26.
//

#include <iostream>
#include <string>
#include "cmdline.h"
#define CATCH_CONFIG_RUNNER
#include "catch.h"


// declared in tests.cpp

void use_arguments(int argc, char ** argv){

    if (argc == 1) {
        return;
    }
    int count = 0;
    for (int i = 1; i < argc; i++){

        if ((std::string)argv[i] == "--help"){
            std::cout << "Arguments allowed are --help and --test\n";
            exit(0);
        }

    //  Remove if tests already passed?
        else if ((std::string)argv[i] == "--test"){
            if (count == 0){
                int result = Catch::Session().run(1,argv);
                if (result != 0){
                    exit(1);
                }
            //std::cout << "Tests passed\n";
                count ++;
                continue;
            }
            std::cerr << "Duplicate --tests argumenet passed\n";
        }

        else {
            std::cerr << "Please enter valid arguments\n";
            exit(1);
        }
    }

}
