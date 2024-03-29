
/* Because boot env does not have access to any libraries, printf function must be
created from scratch by placing chars into the 0xb8000 memory location (which are 
automagically displayed onto the monitor) */

void printf(char* str)
{
	unsigned short* VideoMemory = (unsigned short*)0xb8000;

	for(int i = 0; str[i] != '\0'; ++i)
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

typedef void (*constructor)();
extern "C" constructor* start_ctors;
extern "C" constructor* end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != end_ctors; i++)
		(*i)();
}

extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
	printf("Hello Welcome to my OS!");
	
	while(1);
}