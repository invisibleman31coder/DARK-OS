#include "keyboard.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

static char scancode_to_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0, 'a','s','d','f','g','h','j','k','l',';','\'','`',0,
    '\\','z','x','c','v','b','n','m',',','.','/',0,
    '*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline int is_key_pressed() {
    return (inb(KEYBOARD_STATUS_PORT) & 1);
}

char keyboard_getchar() {
    while (!is_key_pressed());
    unsigned char scancode = inb(KEYBOARD_DATA_PORT);
    if (scancode & 0x80) return 0;
    if (scancode < 128) return scancode_to_ascii[scancode];
    return 0;
}

int keyboard_has_char() {
    return is_key_pressed();
}

void keyboard_init() {
    // PS/2 keyboard ready by default in QEMU
}
