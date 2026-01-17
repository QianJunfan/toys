typedef unsigned short uint16_t;

void outb(unsigned short port, unsigned char val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void init_uart()
{
    outb(0x3f8 + 1, 0x00);
    outb(0x3f8 + 3, 0x80);
    outb(0x3f8 + 0, 0x03);
    outb(0x3f8 + 1, 0x00);
    outb(0x3f8 + 3, 0x03);
    outb(0x3f8 + 4, 0x0b);
}

void putc_uart(char c)
{
    outb(0x3f8, c);
}

void puts_uart(const char *s)
{
    while (*s)
        putc_uart(*s++);
}

void putc_video(char c, unsigned char color, int x, int y)
{
    volatile uint16_t *video_memory = (uint16_t *)0xb8000;
    const int width = 80;
    video_memory[y * width + x] = (uint16_t)c | (uint16_t)color << 8;
}

void puts_video(const char *s, unsigned char color, int x, int y)
{
    int i = 0;
    while (s[i]) {
        putc_video(s[i], color, x + i, y);
        i++;
    }
}

void clear_screen()
{
    volatile uint16_t *video_memory = (uint16_t *)0xb8000;
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = (uint16_t)' ' | (uint16_t)0x07 << 8;
    }
}

int main(void)
{
    init_uart();
    clear_screen();

    puts_uart("Terminal: Hello from Baremetal!\n");

    puts_video("VGA: Hello from Baremetal!", 0x1F, 0, 0);
    puts_video("Status: Running in QEMU", 0x2E, 0, 1);

    while (1);

    return 0;
}
