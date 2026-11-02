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
    if(cursor_row>=25)cursor_row=24;
}
void print_string(const char* s){for(int i=0;s[i];i++)put_char(s[i]);}
void clear_screen(){for(int i=0;i<80*25;i++)vga_buffer[i]=0x0F00|' ';cursor_row=0;cursor_col=0;}
int strcmp(const char* a,const char* b){int i=0;while(a[i]&&b[i]&&a[i]==b[i])i++;return a[i]-b[i];}
int strncmp(const char* a,const char* b,int n){for(int i=0;i<n;i++){if(a[i]!=b[i]||!a[i])return a[i]-b[i];}return 0;}
int strlen(const char* s){int i=0;while(s[i])i++;return i;}
void strcpy(char* d, const char* s){int i=0;while(s[i]){d[i]=s[i];i++;}d[i]=0;}

struct File { char name[32]; char content[128]; };
struct File files[3];

void fs_init(){
    strcpy(files[0].name, "readme.txt");
    strcpy(files[0].content, "ZED-OS v2.6 - In-memory FS");
    strcpy(files[1].name, "about.txt");
    strcpy(files[1].content, "Built by ZED - custom x86 OS");
    strcpy(files[2].name, "version.txt");
    strcpy(files[2].content, "ZED-OS v2.6");
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
            if(strcmp(buffer,"help")==0) print_string("Commands: help, clear, version, echo <text>, ls, cat <file>\n");
            else if(strcmp(buffer,"clear")==0) clear_screen();
            else if(strcmp(buffer,"version")==0) print_string("ZED-OS v2.6\n");
            else if(strcmp(buffer,"ls")==0) fs_list();
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
    fs_init();
    print_string("ZED-OS v2.6 Booted\n");
    print_string("Type 'help' for commands\n");
    shell();
}
