/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Global function declarations and type definitions
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef int size_t;

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

/* MAIN.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* CONSOLE.C */
extern void init_video(void);
extern void puts(unsigned char *text);
extern void putch(unsigned char c);
extern void cls();

/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_wait(int ticks);
extern void timer_install();

/* KEYBOARD.C */
#include "x86.h"

struct keyboard_flags {
    unsigned char shift;
    unsigned char ctrl;
    unsigned char alt;
    unsigned char caps_lock;
    unsigned char num_lock;
    unsigned char scroll_lock;
};

void keyboard_handler(struct regs* r);

unsigned int keyboard_get_pointer();

void keyboard_update_flags(unsigned char code);

void keyboard_push(unsigned char data);

unsigned char keyboard_pull();

void keyboard_install();

unsigned char keyboard_get_char(int keycode);

#define VIDEO_MEMORY_ADDRESS 0xC00B8000

enum TTYColor {
    TTY_COLOR_BLACK = 0,
    TTY_COLOR_BLUE = 1,
    TTY_COLOR_GREEN = 2,
    TTY_COLOR_CYAN = 3,
    TTY_COLOR_RED = 4,
    TTY_COLOR_MAGENTA = 5,
    TTY_COLOR_BROWN = 6,
    TTY_COLOR_LIGHT_GREY = 7,
    TTY_COLOR_DARK_GREY = 8,
    TTY_COLOR_LIGHT_BLUE = 9,
    TTY_COLOR_LIGHT_GREEN = 10,
    TTY_COLOR_LIGHT_CYAN = 11,
    TTY_COLOR_LIGHT_RED = 12,
    TTY_COLOR_LIGHT_MAGENTA = 13,
    TTY_COLOR_LIGHT_BROWN = 14,
    TTY_COLOR_WHITE = 15,
};

struct io_buffer_mode {
    int width;
    int height;
} buffer_mode;

struct io_color_mode {
    char fg;
    char bg;
} color_mode;

struct io_cursor {
    int x;
    int y;
} cursor_position;

void io_init();

void io_set_color(char fg, char bg);

void io_clear_screen();

void io_put_char(unsigned char c);

void io_set_cursor(int x, int y);

void io_scroll_screen();

void io_outportb(unsigned short port, unsigned char data);

unsigned char io_inportb(unsigned short port);

void io_outportw(unsigned short port, unsigned short data);

unsigned short io_inportw(unsigned short port);

void io_outportsw(unsigned short port, unsigned char* data, int length);

void io_inportsw(unsigned short port, unsigned char* data, int length);

void io_printf(char* format, ...);

void io_cursor_enable(unsigned char start, unsigned char end);

void io_cursor_disable();

void io_cursor_move(int x, int y);

#define GDT_SIZE 0xFF
#define GDT_BASE 0xC0002800
#define IDT_BASE 0xC0002000

#include "system.h"

struct gdt_entry {
    unsigned short limit;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct gdt_descriptor {
    unsigned short size;
    unsigned int offset;
} __attribute__((packed));

struct idt_entry {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char reserved;
    unsigned char type;
    unsigned short offset_high;
} __attribute__((packed));

struct idt_descriptor {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt_entries[GDT_SIZE];
struct idt_entry idt_entries[256];

void gdt_load(unsigned int address);
void gdt_set_entry(int id, unsigned long base, unsigned long limit,
                   unsigned char access, unsigned char flags);

void idt_set();

void idt_load();

void idt_set_gate(unsigned char id, unsigned long base, unsigned short sel,
                  unsigned char flags);

void isr_load();

void irq_install_handler(int irq, void (*handler)(struct regs *r));

void irq_uninstall_handler(int irq);

void irq_remap(void);

void irq_install();

struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

#endif
