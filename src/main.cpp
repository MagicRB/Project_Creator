#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>

#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif // WIN32

int main(int argc, char** argv)
{
    // 0 - c
    // 1 - c++
    short unsigned int lang = 1;
    std::string pp = "pp";

    if (argc < 3) {
        fprintf(stderr, "Incorrect number of arguments!\nFormat: [-l {c, c++}] [PROJECT_NAME] [DIRECTORY_TO_CREATE_PROJECT_IN(excluding project name)]");
        exit(EXIT_FAILURE);
    }

    unsigned int offset;
    for (offset = 0; offset < argc - 2; offset++) {
        if (argc - 2 == 0) {
            break;
        }
        if (strcmp(argv[offset], "-l") == 0) {
            offset++;
            if (strcmp(argv[offset], "c++") == 0) {
                lang = 1;
                pp = "pp";
            } if (strcmp(argv[offset], "c") == 0) {
                lang = 0;
                pp = "";
            }
        }
    }
    offset--;


    std::string cmake_lists =   "cmake_minimum_required(VERSION 2.8.9)\n"
                                "project(" + std::string(argv[1 + offset]) + ")\n"
                                "\n"
                                "set(CMAKE_CXX_STANDARD 17)\n"
                                "\n"
                                "include_directories(include)\n"
                                "\n"
                                "link_directories(link)\n"
                                "\n"
                                "if(WIN32)\n"
                                "   include_directories(include_win32)\n"
                                "   link_directories(link_win32)\n"
                                "endif(WIN32)\n"
                                "\n"
                                "file(GLOB SOURCES 'src/*.c" + pp + "' 'include/*.h" + pp + "')\n"
                                "\n"
                                "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../run)\n"
                                "\n"
                                "add_executable(" + std::string(argv[1 + offset]) + " ${SOURCES})\n"
                                "\n"
                                "if(WIN32)\n"
                                "    target_link_libraries(" + std::string(argv[1 + offset]) + " )\n"
                                "elseif(UNIX)\n"
                                "    target_link_libraries(" + std::string(argv[1 + offset]) + " )\n"
                                "endif(WIN32)\n";

    std::cout << "The project will be created in '" + std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) << "'\nIs that OK? [y/N]" << std::endl;
    char yn;
    yn = getchar();
    if (yn != 'y') {
        exit(EXIT_FAILURE);
    }
#ifdef WIN32
    if (!CreateDirectory((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset])).c_str(), NULL)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!CreateDirectory((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/build").c_str(), NULL)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!CreateDirectory((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/run").c_str(), NULL)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!CreateDirectory((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/src").c_str(), NULL)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!CreateDirectory((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/include").c_str(), NULL)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    }
#else
    if (!mkdir((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset])).c_str(), 770)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!mkdir((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/build").c_str(), 770)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!mkdir((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/run").c_str(), 770)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!mkdir((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/src").c_str(), 770)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    } else if (!mkdir((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/include").c_str(), 770)) {
        fprintf(stderr, "Failed to create directory!");
        exit(EXIT_FAILURE);
    }
#endif //WIN32
    printf("%s", (std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/CMakeLists.txt").c_str());

    std::ofstream f;
    f.open((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/CMakeLists.txt").c_str());
    if (!f) {
        fprintf(stderr, "Failed to create CMakeLists.txt");
        exit(EXIT_FAILURE);
    }
    f << cmake_lists;
    f.close();

    if (lang == 0) f.open((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/src/main.c").c_str());
    if (lang == 1) f.open((std::string(argv[2 + offset]) + "/" + std::string(argv[1 + offset]) + "/src/main.cpp").c_str());
    if (!f) {
        if (lang == 0) fprintf(stderr, "Failed to create main.c");
        else if (lang == 1) fprintf(stderr, "Failed to create main.cpp");
        exit(EXIT_FAILURE);
    }
    f << "\n\nint main()\n{\n\n}";
    f.close();
    return 0;
}
