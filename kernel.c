#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000
static unsigned short* const vga_buffer = (unsigned short*) VGA_MEMORY;
static int cursor_row=0,cursor_col=0;

static unsigned char port_in(unsigned short port){ unsigned char r; __asm__ volatile("inb %1,%0":"=a"(r):"Nd"(port)); return r; }

void put_char(char c){
    if(c=='\n'){cursor_row++;cursor_col=0;}
    else if(c=='\b'){if(cursor_col>0){cursor_col--; vga_buffer[cursor_row*80+cursor_col]=0x0F00|' ';}}
    else{vga_buffer[cursor_row*80+cursor_col]=0x0F00|c; cursor_col++; if(cursor_col>=80){cursor_col=0;cursor_row++;}}
    if(cursor_row>=25){cursor_row=24;}
}
void print_string(const char* s){for(int i=0;s[i];i++)put_char(s[i]);}
void clear_screen(){for(int i=0;i<80*25;i++)vga_buffer[i]=0x0F00|' ';cursor_row=0;cursor_col=0;}
int strcmp(const char* a,const char* b){int i=0;while(a[i]&&b[i]&&a[i]==b[i])i++;return a[i]-b[i];}
int strncmp(const char* a,const char* b,int n){for(int i=0;i<n;i++){if(a[i]!=b[i]||!a[i])return a[i]-b[i];}return 0;}
int strlen(const char* s){int i=0;while(s[i])i++;return i;}
void strcpy(char* d, const char* s){int i=0;while(s[i]){d[i]=s[i];i++;}d[i]=0;}

// ===== MEMORY MANAGER v2.7 - START =====
#define PAGE_SIZE 4096
static unsigned char pmm_bitmap[32768]; // 128MB max
static unsigned int total_pages = 0;
static unsigned int used_pages = 0;
static unsigned int heap_ptr = 0x200000; // Heap at 2MB, safe after kernel

void pmm_init(unsigned int mem_kb){
    total_pages = (mem_kb * 1024) / PAGE_SIZE;
    for(unsigned int i=0;i<32768;i++) pmm_bitmap[i]=0;
    // Reserve first 512 pages = 2MB (BIOS + kernel + VGA)
    for(unsigned int i=0;i<512;i++){ pmm_bitmap[i/8] |= (1 << (i%8)); used_pages++; }
}
unsigned int pmm_alloc_page(){
    for(unsigned int i=0;i<total_pages;i++){
        if(!(pmm_bitmap[i/8] & (1 << (i%8)))){
            pmm_bitmap[i/8] |= (1 << (i%8));
            used_pages++;
            return i * PAGE_SIZE;
        }
    }
    return 0;
}
void pmm_free_page(unsigned int addr){
    unsigned int page = addr / PAGE_SIZE;
    pmm_bitmap[page/8] &= ~(1 << (page%8));
    used_pages--;
}
void* kmalloc(unsigned int size){
    void* ptr = (void*)heap_ptr;
    heap_ptr += size;
    heap_ptr = (heap_ptr + 3) & ~3; // align 4
    return ptr;
}
void print_num(unsigned int n){
    char buf[12]; int i=0;
    if(n==0){ put_char('0'); return; }
    while(n>0){ buf[i++]='0'+(n%10); n/=10; }
    while(i>0){ put_char(buf[--i]); }
}
void mem_info(){
    print_string("Total Pages: "); print_num(total_pages); print_string("\n");
    print_string("Used Pages: "); print_num(used_pages); print_string("\n");
    print_string("Free Pages: "); print_num(total_pages-used_pages); print_string("\n");
    print_string("Heap Ptr: 0x"); print_num(heap_ptr); print_string("\n");
}
// ===== MEMORY MANAGER - END =====

struct File { char name[32]; char content[128]; };
struct File files[3];

void fs_init(){
    strcpy(files[0].name, "readme.txt");
    strcpy(files[0].content, "ZED-OS v2.7 - Memory Manager Added");
    strcpy(files[1].name, "about.txt");
    strcpy(files[1].content, "Built by ZED - custom x86 OS");
    strcpy(files[2].name, "version.txt");
    strcpy(files[2].content, "ZED-OS v2.7");
}
void fs_list(){
    print_string("Files:\n");
    for(int i=0;i<3;i++){ print_string("  - "); print_string(files[i].name); print_string("\n"); }
}
void fs_read(const char* name){
    for(int i=0;i<3;i++){ if(strcmp(files[i].name,name)==0){ print_string(files[i].content); print_string("\n"); return; } }
    print_string("File not found\n");
}

char get_key(){
    unsigned char scancode;
    while(1){
        while(!(port_in(0x64)&1));
        scancode=port_in(0x60);
        if(scancode&0x80)continue;
        static const char map[128]={0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,0,0,' '};
        if(scancode<128&&map[scancode])return map[scancode];
    }
}

void shell(){
    char buffer[128]; int idx=0;
    print_string("\n> ");
    while(1){
        char c=get_key();
        if(c=='\n'){
            buffer[idx]=0; put_char('\n');
            if(strcmp(buffer,"help")==0) print_string("Commands: help, clear, version, echo <text>, ls, cat <file>, mem, alloc\n");
            else if(strcmp(buffer,"clear")==0) clear_screen();
            else if(strcmp(buffer,"version")==0) print_string("ZED-OS v2.7\n");
            else if(strcmp(buffer,"ls")==0) fs_list();
            else if(strcmp(buffer,"mem")==0) mem_info();
            else if(strcmp(buffer,"alloc")==0){ unsigned int p=pmm_alloc_page(); print_string("Allocated page at: 0x"); print_num(p); print_string("\n"); }
            else if(strncmp(buffer,"cat ",4)==0) fs_read(buffer+4);
            else if(strncmp(buffer,"echo ",5)==0) { print_string(buffer+5); put_char('\n'); }
            else if(buffer[0]!=0) print_string("Unknown: type 'help'\n");
            idx=0; print_string("> ");
        } else if(c=='\b'){ if(idx>0){idx--; put_char(c);} }
        else{ if(idx<127){buffer[idx++]=c; put_char(c);} }
    }
}

void kernel_main(){
    clear_screen();
    pmm_init(128 * 1024); // 128MB for QEMU
    fs_init();
    print_string("ZED-OS v2.7 Booted\n");
    print_string("Memory Manager: OK\n");
    print_string("Type 'help' for commands\n");
    shell();
}
