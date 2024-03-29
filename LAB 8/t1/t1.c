#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int debug = 0;
int currentFD = -1;
char* currentOpenFile = NULL; // Current opened file name
void* map_start;
struct stat fd_stat; // Holds the stats of the current opened fd
Elf32_Ehdr *header; // Pointer to current mapped ELF file header struct

typedef struct fun_desc {
  char *name;
  char (*fun)(char);
}fun_desc;

void toggleDebug();
void examineELF();
int mapFile();
int isELFFile(Elf32_Ehdr *header);
char* checkDataType(Elf32_Ehdr *header);
void printSectionNames();
char* sectionType(int val);
void quit();

void toggleDebug() 
{
    if (debug)
    {
        debug--;
        fprintf(stderr, "Debug is now off\n");
        return;
    }
    debug++;
    printf("Debug is now on\n");
}

void examineELF() 
{
    printf("Please enter a file name\n");
    mapFile();
    header = (Elf32_Ehdr*)map_start; // Sets the pointer to the beginning of the mapped file
    if (isELFFile(header))
    {
        printf("Magic number:\t\t\t %x %x %x\n", header->e_ident[EI_MAG0], header->e_ident[EI_MAG1], header->e_ident[EI_MAG2]);
        printf("Data Encoding Scheme:\t\t %s\n", checkDataType(header));
        printf("Address of entry point:\t\t 0x%x\n", header->e_entry);
        printf("Section header offset:\t\t %d\n", header->e_shoff);
        printf("Number of section header entries:%d\n", header->e_shnum);
        printf("Size of section headers:\t %d\n", header->e_shentsize);
        printf("Program header offset:\t\t %d\n", header->e_phoff);
        printf("Number of program header entries:%d\n", header->e_phnum);
        printf("Size of program headers:\t %d\n", header->e_phentsize);
    }
    else
    {
        printf("%s is not an ELF file\n", currentOpenFile);
        munmap(map_start, fd_stat.st_size);
        close(currentFD);
        currentFD = -1;
        currentOpenFile = NULL;
    }
}

int mapFile()
{
    char fileName[100];
    int fd;
    fscanf(stdin, "%s", fileName);
    if ((fd = open(fileName, O_RDWR)) < 0)
    {
        if (debug) perror("Can't open file");
        exit(1);
    }
    if (fstat(fd, &fd_stat) != 0)
    {
        if (debug) perror("FStat failed");
        exit(1);
    }
    if ((map_start = mmap(0, fd_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        if (debug) perror("MMap Failed");
        exit(1);
    }

    if (currentFD != -1) close(currentFD);
    currentFD = fd;
    strcpy((char*)&currentOpenFile, fileName);
    return currentFD;
}

int isELFFile(Elf32_Ehdr *header) // Checks if first 4 bytes of header are exact to the ones that identify an ELF file
{
    return (strncmp((char*)header->e_ident, (char*)ELFMAG, 4) == 0) ? 1 : 0;
}

char* checkDataType(Elf32_Ehdr *header)
{
    return 
    header->e_ident[EI_DATA] == ELFDATANONE ? "Invalid Encoding" :
    header->e_ident[EI_DATA] == ELFDATA2MSB ? "2's complement, big endian" :
    header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" :
    "There is no data";
}

void printSectionNames()
{
    if (currentFD == -1)
    {
        fprintf(stderr, "Current FD is invalid\n");
        return;
    }
    Elf32_Shdr *sectionsTable = map_start + header->e_shoff; // Pointer to sections table
    Elf32_Shdr *stringTables = map_start + header->e_shoff + header->e_shstrndx * header->e_shentsize; // Pointer to string table, necessary for debug mode
    if (debug)
    {
        fprintf(stderr, "Section Table Address: %p\n", sectionsTable);
        printf("Num:  Value \tSize\tType\t\tName\t\t\tOffset(bytes)\n");
        
    }
    else printf("Num:  Value \tSize\tType\t\tName\n");

    for (int i = 0; i<header->e_shnum; i++)
    {   
        Elf32_Shdr *entry = map_start + header->e_shoff + i * header->e_shentsize;
        char *entName = map_start + stringTables->sh_offset + entry->sh_name;
        debug ?
        printf("%2d:   %06x\t%06x\t%-13.10s\t%-18.18s\t%06x\n",i, entry->sh_addr, entry->sh_size, sectionType(entry->sh_type), entName, entry->sh_offset) :
        printf("%2d:   %06x\t%06x\t%-13.10s\t%-18.18s\n",i, entry->sh_addr, entry->sh_size, sectionType(entry->sh_type), entName);
    }
}

char* sectionType(int val)
{
    return val == SHT_NULL ? "NULL" :
    val == SHT_PROGBITS ? "PROGBITS" :
    val == SHT_SYMTAB ? "SYMTAB" :
    val == SHT_STRTAB ? "STRTAB" :
    val == SHT_RELA ? "RELA" :
    val == SHT_HASH ? "HASH" :
    val == SHT_DYNAMIC ? "DYNAMIC" :
    val == SHT_NOTE ? "NOTE" :
    val == SHT_NOBITS ? "NOBITS" :
    val == SHT_REL ? "REL" :
    val == SHT_SHLIB ? "SHLIB" :
    val == SHT_DYNSYM ? "DYNSYM" :
    "UNKNOWN";
}

void quit()
{
    if (debug) fprintf(stderr, "Quitting\n");
    if (currentFD != -1)
    {
        munmap(map_start, fd_stat.st_size);
        close(currentFD);
        currentFD = -1;
        currentOpenFile = NULL;
    }
    exit(0);
}

int getUserInput()
{
  int opCode;
  scanf("%d", &opCode);
  if (opCode >= 0 && opCode < 5)
  {
    printf("Within bounds\n");
    return opCode;
  }
  else
  {
    printf("Not within bounds\n");
    return -1;
  }
}

int main(int argc, char **argv){
	fun_desc menu[] = {
	{"Toggle Debug Mode", toggleDebug},
	{"Examine ELF File", examineELF},
    {"Print Section Names", printSectionNames},
	{"Quit", quit},
	{NULL, NULL}
	};
	do {
		printf("Please choose a function:\n");
		int len = sizeof(menu)/sizeof(struct fun_desc) - 1;
		for(int i = 0; i < len; i++)
			printf("%d) %s\n", i, menu[i].name);
		int input = getUserInput();
        if (input != -1) menu[input].fun(0);
        printf("\n");
	}while(1);
    return 0;
}