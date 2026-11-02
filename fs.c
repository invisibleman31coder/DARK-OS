#include "fs.h"
#include "vga.h"

struct File {
    char name[32];
    char content[256];
};

struct File files[3];

void fs_init() {
    // file 1
    __builtin_strcpy(files[0].name, "readme.txt");
    __builtin_strcpy(files[0].content, "ZED-OS v2.6 - In-memory FS");
    // file 2
    __builtin_strcpy(files[1].name, "about.txt");
    __builtin_strcpy(files[1].content, "Built by ZED, custom x86 OS");
    // file 3
    __builtin_strcpy(files[2].name, "version.txt");
    __builtin_strcpy(files[2].content, "ZED-OS v2.6");
}

void fs_list() {
    print_string("Files:\n");
    for(int i=0; i<3; i++) {
        print_string("  - ");
        print_string(files[i].name);
        print_string("\n");
    }
}

void fs_read(const char* name) {
    for(int i=0; i<3; i++) {
        if(__builtin_strcmp(files[i].name, name)==0) {
            print_string(files[i].content);
            print_string("\n");
            return;
        }
    }
    print_string("File not found\n");
}
