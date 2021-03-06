
#include < system.h >
#include " include/keyboard.h "


char* c_strcat(char* destination, const char* source)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // the destination is returned by standard `strcat()`
    return destination;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

char *bank_var[143] = {"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a"}

void terminal_xxx()
{
	char letter = 0;
	char letter2 = 0;
	int exitd = 0;
	const char* enda = 0;
    do{
        letter = keyboard_get_char();
        letter2 = keyboard_get_char();
        if(letter =! ".") {
            if(letter2 =! ".") {
                cmd = c_strcat(letter, letter2);
				
            }
			else {
			    exitd = 1;
			}
        }
		else {
			exitd = 1;
    }
    }while(exitd != 1)
	letter = 0;
	letter2 = 0;
	exitd = 0;
	enda = 0;
    do{
        letter = keyboard_get_char();
        letter2 = keyboard_get_char();
        if(letter =! ";") {
            if(letter2 =! ";") {
                value = c_strcat(letter, letter2);
				
            }
			else {
			    exitd = 1;
			}
			
        }
		else {
			exitd = 1;
                }
    
    
    }while(exitd != 1)
    if(cmd == "mkdir") {
        my_mkdir(value);
    }
    if(cmd == "rmdir") {
        my_rmdir(value);
    }
    if(cmd == "rename") {
	
	do{
        letter = keyboard_get_char();
        letter2 = keyboard_get_char();
        if(letter =! ";") {
            if(letter2 =! ";") {
                value2 = c_strcat(letter, letter2);
				
            }
			else {
			    exitd = 1;
			}
			
        }
		else {
			exitd = 1;
                }
        my_rename(value, value2);  
    }
    if(cmd == "mkroot") {
        mkroot();
    }
    if(cmd == "dir") {
        show_file_list();
    }
    if(cmd == "resetdisk") {
        reset_disk();
    }
    if(cmd == "fsbuild") {
        init();
    }
    if(cmd == "rm") {
        my_remove(value);
    }
    if(cmd == "fclose") {
        my_close(value);
    }
}

const char* keyboard_get_string()
{
char letter = keyboard_get_char();
    char letter2 = keyboard_get_char();
	const char* enda = 0;
    do{
        letter = keyboard_get_char();
        letter2 = keyboard_get_char();
        if(letter =! "}") {
            if(letter2 =! "}") {
                enda = c_strcat(letter, letter2);
            }
			else {
			    exitd = 1;
			}
        }
		else {
			exitd = 1;
		}
    }while(exitd != 1)
    return enda;
}

void file_bank_entry_var(location, id, value)
{
    bank_var[location] = id
    bank_var[location + 1] = value
}   

void main()
{
    int i;
    char letter = 0;
    char letter2 = 0;
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();
    timer_install();
    keyboard_install();
    init();
    mkroot();

    __asm__ __volatile__ ("sti");

    keyboard_push("ArdenWareOS Software\n");
    

//    i = 10 / 0;
//    putch(i);

    for (;;);
}

