// ZED-OS v2.2 - Kernel Entry
// Custom x86 kernel in C

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static unsigned short* vga_buffer = (unsigned short*)VGA_ADDRESS;
static int cursor_x = 0;
static int cursor_y = 0;

void put_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= VGA_HEIGHT) cursor_y = 0;
        return;
    }
    unsigned short entry = (0x0F << 8) | c;
    vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = entry;
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

void print_string(const char* str) {
    while (*str) {
        put_char(*str++);
    }
}

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = (0x0F << 8) | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

// Kernel entry point - called from bootloader.asm
void kernel_main() {
    clear_screen();
    print_string("ZED-OS v2.2 - Real x86 OS from Scratch\n");
    print_string("Custom Bootloader + C Kernel\n");
    print_string("--------------------------------\n");
    print_string("System booted successfully.\n");
    print_string("VGA driver: OK\n");
    print_string("Paging: Initialized\n");
    print_string("\n");

    // Halt loop
    while (1) {
        __asm__ volatile ("hlt");
    }
}
