
## Extended System Programming Laboratory

In this course we focus on low-level system programming principles. The labs are
based on interaction with the LINUX operating system, mostly using C, but also some
assembly language. Issues covered in the course are:
1. Processes, memory models, and interaction with the operating system.
2. A programmer’s introduction to C: storage types, pointers, structures.
3. The raw machine: basics of (x86) assembly language, linking to functions written in C.
4. Direct system calls: a programmer’s interface with system services.
5. User’s view of the Linux file system, processes, and access permissions.
6. Command interpreters: Unix “shell”.
7. “Binary” files: formats, manipulation.
8. The ELF format, linking and loading.



# LAB 1 - Introduction to C Programming in a Unix (Linux 32 bits) Environment
Lab goals:
- C primer
- Parsing command-line arguments
-	Undestanding character (ASCII) and hexadecimal encodings
-	Implementing a debug mode for your program
-	Introduction to standard streams (stdin, stdout, stderr)
-	Simple stream IO library functions


# LAB 2 - Program Memory and Pointers, Debugging and Simulating Object Oriented Programming

Lab goals:
- C primer - continued.
- Understanding storage addresses, introduction to pointers.
- Pointers to basic data types, to structures, and to functions.
- Simulating object-like behavior in C.
 

# LAB 3 - C Programming: debugging, dynamic data structures: linked lists, patching binary files.

Lab goals:
- Pointers and dynamically allocated structures and the valgrind utility.
- Understanding data structures: linked lists in C.
- Basic access to "binary" files, with application: simplified virus detection in executable files.

# LAB 4 - 
Lab goals: 

- To get acquainted with the low-level interface to system calls.
- To understand how programs can work without the standard library.
- Basics of directory listings, through a first attempt at executable file viruses.
- Debugging programs via printouts (the idea of debug mode, continued).


# LAB 5 - Implementing a Command Interpreter (Shell)

Lab goals:
- get acquainted with command interpreters ("shell") by implementing a simple command interpreter.
- Understand how Unix/Linux fork() and exec() work.
- Intruduction to Linux signals.


# LAB 6 - Standard Input/Output Redirection, Introduction to Pipelines
Lab goals:

- To enrich the set of capabilities of your shell by implementing input/output redirection and pipelines.
The shell will then be able to execute non-trivial commands such as "tail -n 2 in.txt| cat > out.txt",
demonstrating the power of these simple concept.


# LAB 7 - AWK Command

Lab goal:
- Learn awk syntax, records, fileds, line Separator and the overall picture of the awk command.


# LAB 8 - ELF-Introduction with Code
Lab goals:

- Learn how to manipulate ELF files by writing a simplified version of the readelf program.
- Parsing the ELF file and extract useful information from it. 
- Access the data in the section header table, and in the symbol table.
- Learn to use the mmap system call.

# Lab 9: ELF - Virus (Architecture and SPlab)
Lab goal:
- In this lab, You are requested to write and run Proto program which will attach itself to executable files and infect them.
