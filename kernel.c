// ============ DARK-OS v2.5 - kernel.c - CLEAN WHOLE FILE ============
// Powered by SAIDER AI
// Single file: VGA + Memory + FS + Keyboard + Shell

#define VGA ((volatile unsigned short*)0xB8000)
int cursor_x = 0;
int cursor_y = 0;

void put_char(char c) {
    if (c == '\n') { cursor_x = 0; cursor_y++; return; }
    if (c == '\r') { cursor_x = 0; return; }
    if (cursor_y >= 25) { cursor_x = 0; cursor_y = 0; }
    VGA[cursor_y * 80 + cursor_x] = (0x1F << 8) | (unsigned char)c;
    cursor_x++;
    if (cursor_x >= 80) { cursor_x = 0; cursor_y++; }
}

void print_string(char *str) {
    for (int i = 0; str[i] != 0; i++) put_char(str[i]);
}

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) VGA[i] = (0x1F << 8) | ' ';
    cursor_x = 0;
    cursor_y = 0;
}

// ---------- STRING ----------
int strlen(char *s) { int l = 0; while (s[l]) l++; return l; }
void strcpy(char *d, char *s) { int i = 0; while (s[i]) { d[i] = s[i]; i++; } d[i] = 0; }
int strcmp(char *a, char *b) {
    int i = 0; while (a[i] && b[i]) { if (a[i] != b[i]) return 1; i++; }
    return a[i] != b[i];
}
int strncmp(char *a, char *b, int n) {
    for (int i = 0; i < n; i++) { if (a[i] != b[i]) return 1; if (a[i] == 0) return 0; }
    return 0;
}

// ---------- PORTS ----------
unsigned char port_in(unsigned short port) {
    unsigned char r;
    __asm__ volatile("inb %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}

// ---------- MEMORY ----------
unsigned int total_pages = 0;
unsigned int used_pages = 0;
unsigned int heap_ptr = 0x200000;

void pmm_init(unsigned int mem_kb) { total_pages = mem_kb / 4; used_pages = 0; }
unsigned int pmm_alloc_page() {
    if (used_pages >= total_pages) return 0;
    used_pages++;
    return (used_pages * 4096);
}
void print_num(unsigned int n) {
    char buf[12]; int i = 0;
    if (n == 0) { put_char('0'); return; }
    while (n > 0) { buf[i++] = '0' + (n % 10); n /= 10; }
    while (i > 0) put_char(buf[--i]);
}
void mem_info() {
    print_string("Total Pages: "); print_num(total_pages); print_string("\n");
    print_string("Used Pages: "); print_num(used_pages); print_string("\n");
    print_string("Free Pages: "); print_num(total_pages - used_pages); print_string("\n");
}

// ---------- FILE SYSTEM ----------
struct File { char name[32]; char content[128]; };
struct File files[3];

void fs_init() {
    strcpy(files[0].name, "readme.txt");
    strcpy(files[0].content, "DARK-OS v2.5 - Memory Manager Added");
    strcpy(files[1].name, "about.txt");
    strcpy(files[1].content, "Built by invisibleman31coder - custom x86 OS - Powered by SAIDER AI");
    strcpy(files[2].name, "version.txt");
    strcpy(files[2].content, "DARK-OS v2.5");
}
void fs_list() {
    for (int i = 0; i < 3; i++) { print_string(files[i].name); print_string("\n"); }
}
void fs_read(char *name) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(files[i].name, name) == 0) { print_string(files[i].content); print_string("\n"); return; }
    }
    print_string("File not found\n");
}

// ---------- KEYBOARD ----------
char get_key() {
    unsigned char scancode;
    while (1) {
        while (!(port_in(0x64) & 1));
        scancode = port_in(0x60);
        if (scancode & 0x80) continue;
        static const char map[128] = {0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b',0,'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'',0,0,'\\','z','x','c','v','b','n','m',',','.','/',0,0,0,' '};
        if (scancode < 128 && map[scancode]) return map[scancode];
    }
}

// ---------- SHELL ----------
void shell() {
    char buffer[128]; int idx = 0;
    print_string("DARK> ");
    while (1) {
        char c = get_key();
        if (c == '\n') {
            buffer[idx] = 0; put_char('\n');
            if (strcmp(buffer, "help") == 0) print_string("Commands: help, clear, version, ls, mem, alloc, cat, echo\n");
            else if (strcmp(buffer, "clear") == 0) clear_screen();
            else if (strcmp(buffer, "version") == 0) print_string("DARK-OS v2.5 - Powered by SAIDER AI\n");
            else if (strcmp(buffer, "ls") == 0) fs_list();
            else if (strcmp(buffer, "mem") == 0) mem_info();
            else if (strcmp(buffer, "alloc") == 0) { unsigned int p = pmm_alloc_page(); print_string("Allocated page: 0x"); print_num(p); print_string("\n"); }
            else if (strncmp(buffer, "cat ", 4) == 0) fs_read(buffer + 4);
            else if (strncmp(buffer, "echo ", 5) == 0) { print_string(buffer + 5); put_char('\n'); }
            else if (buffer[0] != 0) print_string("Unknown: type 'help'\n");
            idx = 0; print_string("DARK> ");
        } else if (c == '\b') { if (idx > 0) idx--; }
        else { if (idx < 127) { buffer[idx++] = c; put_char(c); } }
    }
}

// ---------- MAIN ----------
void kernel_main() {
    cursor_x = 0; cursor_y = 0;
    total_pages = 0; used_pages = 0
