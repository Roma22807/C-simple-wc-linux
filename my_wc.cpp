#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <memory>
#include <sys/stat.h>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: to little arguments\n";
        return 1;
    }
    bool ISstrings = false;
    bool ISbytes = false;
    bool ISsym = false;
    bool ISlongest = false;
    bool ISwords = false;
    std::string filename;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-l") ISstrings = true;
        else if (arg == "-w") ISwords = true;
        else if (arg == "-L") ISlongest = true;
        else if (arg == "-c") ISbytes = true;
        else if (arg == "-m") ISsym = true;
        else if (filename.empty()){
            filename = arg;
        } else {
            std::cerr << "ERORR: Invalid argument: " << arg << "\n";
            return 1;
        }
    }
     if (filename.empty()) {
        std::cerr << "ERROR: no such file in directory\n";
        return 1;
    }
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "ERROR: with opening the file\n";
        return 1;
    }
    const size_t buffer_size = 4096;
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(buffer_size);
    ssize_t read_bytes;
    ssize_t strings = 0;
    ssize_t words = 0;
    ssize_t sym = 0;
    ssize_t symb = 0;
    struct stat file_info;
    size_t bytes = 0;
    if (stat(filename.c_str(), &file_info) == 0) {
               bytes = file_info.st_size; 
        }
        if (bytes == 0) {
            std::cerr << "ERROR: invalid number of bytes\n";
            close(fd);
            return 1;
        }
        std::vector<ssize_t> arr;
        bool inword = false;
        bool instring = false;
    while ((read_bytes = read(fd, buffer.get(), buffer_size)) > 0) {
        for (ssize_t i = 0; i < read_bytes; i++) {
            if (buffer[i] != ' ') {
                inword = true;
            }
            if (buffer[i] != '\n') {
                instring = true;
            }
                sym++;
                symb++;
            if (buffer[i] == '\n' && instring) {
                strings++;
                words++;
                arr.push_back(symb);
                symb = 0;
                instring = false;
            }
            if (buffer[i] == ' ' && inword) {
                words++;
                inword = false;
            }
        }
    }
    ssize_t longest = 0;
    if (!arr.empty()) {
    longest = arr[0];
    for (ssize_t i = 1; i < arr.size(); i++) {
        if (arr[i] > longest) {
            longest = arr[i];
        }
    }
}
    if (read_bytes == -1) {
        std::cerr << "ERROR: with file reading\n";
        close(fd);
        return 1;
    }
    if (ISstrings) {
        std::cout << strings << " ";
    }
    if (ISwords) {
        std::cout << words << " ";
    }
    if (ISbytes) {
        std::cout << bytes << " ";
    }
    if (ISsym) {
        std::cout << sym << " ";
    }
    if (ISlongest) {
        std::cout << longest - 1 << " ";
    }
    if (!ISstrings && !ISwords && !ISbytes && !ISsym && !ISlongest) {
        std::cout << strings << " " << words << " " <<  bytes << "\n";
    }
    std::cout << filename << "\n";
    close(fd);
    return 0;
}