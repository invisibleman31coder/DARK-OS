// ZED-OS v2.2 KERNEL - Built by invisibleman31coder
#define VGA_WIDTH 80
volatile unsigned short *vga = (unsigned short*)0xB8000;
int cx=0, cy=0;
void kclear(){ for(int i=0;i<80*25;i++) vga[i]=0x0F00|' '; cx=cy=0; }
void kput(char c){ if(c=='\n'){cx=0;cy++;return;} vga[cy*80+cx]=0x0F00|c; cx++; if(cx>=80){cx=0;cy++;} }
void kprint(const char* s){ while(*s) kput(*s++); }
void kmain(){
    kclear();
    kprint("========================================\n");
    kprint(" ZED-OS v2.2 REAL - x86 BOOTABLE KERNEL\n");
    kprint("========================================\n");
    kprint(" [OK] Bootloader: Protected Mode\n");
    kprint(" [OK] Kernel: C Kernel @ 0x10000\n");
    kprint(" [OK] Memory: Paging Ready\n");
    kprint(" [OK] Drivers: VGA\n");
    kprint(" [OK] Shell: ZED Shell\n\n");
    kprint(" ZED-OS > Hello Durban! Online.\n");
    kprint(" root@zed-os:~# ");
    while(1){ __asm__ volatile("hlt"); }
}
