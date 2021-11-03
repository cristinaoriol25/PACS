# Getting Started: Environment, Command Line, Compiling, Debugging, and Programming Basics

## Goals of the Lab Session

- Set up the working environment.

- Learn basic commands of the command line interpreter or Shell.

- Learn what a compiler is and how to use it for a C++ sequential programming environment.

- Learn what a debugger is and how to use it for a C++ sequential programming environment.

- Code basic C++ sequential programs, learn how to use a library, Eigen math library, and evaluate performance.

## Lab Environment: Machine Names, Remote Access, and Terminal Sharing

All the lab sessions will take place at lab 0.06B. This lab consists of:

- 13 machines named from lab006-171 (IP: 10.3.17.171) to lab006-183 (IP: 10.3.17.183). Every machine has an Intel Core i3-6100 processor @ 3.70 GHz (2 x86_64 cores) with 8192 MB of RAM.

The installed Operating System (OS) is CentOS Linux 7.6.1810 in every lab machine. After the lab session, anyone wishing to use a lab machine remotely can do so through a Secure Shell (SSH) application protocol client program. This client will establish a connection with a chosen lab machine and will give you access to it. In the case of Linux/UNIX operating systems (including MacOS), the ssh command is installed by default.

Let's see how a remote connection works. Consider your own machine to be referred to as the local machine/host. Once a Shell terminal has been opened in the local host, the following command can be used to launch a Shell in a lab machine:

```
$localhost> ssh username@machine_IP
```

Where:

- `username` refers to the user identifier (character 'a' + NIP). If you still do not have a UZ account (or do not remember your password), log in as a guest using these credentials: guest/diis7d5 

- `machine_IP` is the IP assigned to the lab machine in front of you, which can be retrieved typing the command "ifconfig" in a lab machine Shell. Write down the IP of your lab machine so that you can access remotely to it whenever you want. It is convenient to use always the same lab machine and preferably outside lab hours. Otherwise other users working in the same machine may introduce some noise in your reported results.

Example:

```
$localhost> ssh a731730@10.3.17.174
```

**Important notice (1):** unless a [VPN connection to UNIZAR](https://sicuz.unizar.es/comunicaciones/vpn/conexi%C3%B3n-vpn-inicio) is configured in the local host, the SSH access to the lab machines has to be done through another server, such as pilgor, acting as a gateway. To do so, simply establish an SSH connection to the machine pilgor (pilgor.cps.unizar.es), and once logged in, establish a second SSH connection to the lab machine.

**Important notice (2):** for those who have used any lab machine (including hendrix) before and would like to change the access password, follow this [link](https://webdiis.unizar.es/cgi-bin/hendrix-pw). For those who have used any lab machine (including hendrix) before and do not remember the password, or simply have never used these services, follow this [link](https://webdiis.unizar.es/cgi-bin/hendrix-newpw) to set up a new password.

In the case of using a Windows OS in the local machine, the ssh command is not available by default. It is necessary to install additional software (e.g., puTTy or MobaXterm), which will establish a connection with the lab machine using the SSH protocol. Another option is to install a Linux/UNIX virtual machine (e.g., VirtualBox), start the virtual OS on top of the native Windows OS and make the SSH connection through the Shell as shown above. For Windows 10 users, Windows Subsystem for Linux (WSL) is another option to run a Linux terminal environment on a Windows OS. More details about how to configure WSL can be found [here](https://wiki.ubuntu.com/WSL).

For those applications that use the window manager and we want to run them in the lab machine, we must export/send the windows over the network from the lab machine to the local host so that it can show them to us. If the local host's OS is Linux/UNIX, just add the `–X` option to the ssh command as follows:

```
$localhost> ssh -X username@machine_IP
```

In the case of using Windows + puTTy, it will be necessary to execute a program (e.g., Xming) that emulates the windows of the lab machine since the Windows and Linux/UNIX window managers are not compatible. More details about how to configure ssh and Xming in a Windows environment can be found in this [link](http://webdiis.unizar.es/asignaturas/PROG1/doc/anuncios/programar_en_hendrix_desde_casa.pdf) facilitated by the faculty of the Programming course, where the machine name hendrix-ssh.cps.unizar.es should be replaced by your lab machine IP.

In regard of text editors to code C++ programs in the lab machine, we can use editors such as vi or vim, which will allow us to write programs without the need for windows, or others such as emacs or gedit where we will work with windows and therefore it will be necessary to add the –X option to the ssh command. The decision of which text editor to use is entirely up to you.

Last but not least, a Shell terminal can be shared using the tmate command. To do so, type "tmate" in the lab machine's Shell. Below the terminal window, highlighted in yellow color, a very large token after an "ssh session" message should be displayed (for example: 7smk4PxIiMtgjrr8DL5DiLObb@am2.tmate.io). Then, the ssh session connection can be shared using the generated token ID with your mates so that they can access your terminal. That is, your mate lauches this command in the local host: "ssh 7smk4PxIiMtgjrr8DL5DiLObb@am2.tmate.io" to start sharing a common Shell terminal.

For the first lab, it is highly recommended to follow the steps below individually and, presumably by the end or after the lab session, to complete the C++ code assignment working in pairs using tmate or sharing the screen with any other application.

## A Brief Summary of the Shell

A command line interpreter or Shell is a user interface that is navigated by typing commands at prompts (requests for input). Unlike a Graphical User Interface (GUI) OS, a Shell only uses a keyboard to navigate by entering commands and does not utilize a mouse for navigating. Although using a Shell requires to remember many different commands, it can be a valuable resource and should not be ignored. Using a Shell, you can perform almost all the same tasks that can be done with a GUI. However, many tasks can be performed quicker with powerful commands and can be easier to automate (through the execution of batch files or scripts) and do remotely.

Extended information and usage for every command can be obtained by typing: `man command_name`

The next subsections summarize basic commands about the management of files, directories, synchronous/asynchronous execution, standard input/output (I/O), processes, and so on. Unless otherwise stated, all the examples are to be run in the lab machine.

### Autocomplete function

Autocomplete is a useful function to speed up the writing of a command line. Press TAB at any time while writing a command to experience the effect. If the function does not seem to work, type the command `set +u` and try again.

### Files (Namespace)

- Path of the current directory: `pwd`
- Change current directory to dirname: `cd dirname`
- Change to home directory: `cd`, `cd $HOME`
- Change to root directory: `cd /`
- Change to parent directory: `cd ..`
- Change to current directory: `cd .`
- Listing contents of a directory: `ls dirname` (empty dirname refers to the current directory)
- Absolute and relative paths

#### Examples (try each command as a sorted list and check out the effect of each of them. Alternatively, you can add other commands in between and check out their effects as well)

```
01. pwd
02. ls
03. cd / 
04. ls 
05. cd proc
06. ls
07. pwd
08. cd
09. pwd
10. cd ..
11. ls
12. cd /home/username/Desktop
13. pwd
14. cd /proc
15. cd ../home/username/Desktop
16. pwd
```
**Important notice (3):** In the case of using the guest account instead of yours, commands #12 and #15 should be replaced by `cd /export/home/guest/Desktop` and `cd ../export/home/guest/Desktop`, respectively.

Commands #12 and #15 refer to the same directory. The difference lies in that the former uses an absolute path from "/" to reach the directory destination (no matter what the current directory is), whereas the latter uses a relative path from the current directory (/proc) to reach the destination.

### Copying Files and Directories between Two Different Machines

The secure copy (scp) command-line can be used to securely copying files and directories between two different locations. When copying data with scp, both the files and password are encrypted so that anyone snooping on the traffic does not get any sensitive information. The scp command syntax is as follows:

```
$localhost> scp source_file username@machine_IP:destination_file
```
Where:

- `source_file` refers to the source file to be transferred from the local host.
- `destination_file` refers to the absolute path where the source file is copied in the destination machine.

Example:

```
$localhost> scp lab1_materials.tar.gz a731730@10.3.17.174:/home/a731730
```
The above command copies the lab1_materials.tar.gz file to /home/a731730 in machine 10.3.17.174. This command should be run in a second Shell from the local host, after changing the current directory to that where lab1_materials.tar.gz is to be found. In other words, the command assumes that the user is located in the directory containing lab1_materials.tar.gz. Otherwise, the path to the compressed file should be included before the file name. Notice too that no previous ssh connection to the destination machine is required in the second Shell to copy the file with the scp command.

The following example, also launched in the local host, works the other way around. That is, copying a source file from the lab machine to the local host (remember that "." refers to the current directory -in the local host-):

```
$localhost> scp a731730@10.3.17.174:/home/a731730/lab1_materials.tar.gz .
```

In the case of Windows, applications like WinSCP or FileZilla allow to securely transfer files from one location to another using the graphical interface.

**Download the lab1_materials.tar.gz file from either Moodle or the GitHub code tab to the local host and copy it to your $HOME directory in the lab machine. If you do not have a local machine, simply download the zipped file to the lab machine. Then, unzip the file using the command:**

```
$labmachine> tar -xzvf lab1_materials.tar.gz
```

### Directories (Create, Remove, Listing)

- Creation of new directories: `mkdir`
- Removal of directories: `rmdir`
- Listing hidden files: `ls –a`
- Listing extended information: `ls –l`

#### Examples

```
01. cd
02. cd PACS
02. mkdir trash
03. mkdir dir1 dir2 dir3
04. ls -l
05. cd trash
06. pwd
07. cd ..
08. pwd
09. rmdir trash
10. ls dir1
11. ls –a
12. ls –a dir1
```

### Files (Copy, Move, Listing Contents)
	
- Copying files: `cp`
- Moving/changing name of files: `mv`
- Removal of files: `rm`
- Listing contents of files: `more`, `cat`
- Editing files: `vi`, `vim`, `emacs`, `gedit`, `nano` (and many others...)

#### Examples

```
01. cd
02. cp /home/username/PACS/lab1/HelloWorld.cpp . (using guest account: cp /export/home/guest/PACS/lab1/HelloWorld.cpp .)
03. ls
04. cp PACS/lab1/HelloWorld.cpp another.cpp
05. ls
06. mv another.cpp program.cpp
07. ls
08. mv program.cpp PACS/dir1
09. ls
10. cd PACS/dir1
11. ls
12. rm program.cpp
13. cd ..
14. rmdir dir1
15. ls
16. cp lab1/HelloWorld.cpp dir2
17. more lab1/HelloWorld.cpp
18. more dir2/HelloWorld.cpp
```

### Synchronous/Asynchronous Execution

Synchronous execution (step by step):

- Shell waits for a command.
- Shell launches the command to be executed.
- **Shell waits for the execution to finish.**
- Shell waits for a new command.

#### Example (with -X specified in the ssh connection)

```
$labmachine> gedit new.cpp
```

Asynchronous execution (step by step):

- Shell waits for a command.
- Shell launches the command to be executed.
- **Shell does not wait for the execution to finish and immediately waits for a new command that can be launched while the previous one is still running.**

#### Example

```
$labmachine> gedit new.cpp &
```

### Standard I/O

Every command/process launched by the Shell has three communication ways:

- Standard input: the process reads from the keyboard.
- Standard output: the process writes to the screen.
- Standard error output: the process writes error messages through an alternate way to the screen.

The above behavior can be changed from the Shell with alternate forwarding options as follows:

- prog > f: forwards the standard output of the prog command to the f file. The file is shorten if already exists and created if the file does not exist.
- prog >> f: forwards the standard output of the prog command to the f file, preserving the original content of f and adding the new content at the end of the file.
- prog < f: forwards the standard input to f. The file must exist.
- prog 2> f : forwards the standard error output to f. The file is shorten if already exists and created if the file does not exist.
- prog1 | prog2: forwards the standard output of prog1 to the standard input of prog2.

#### Examples

```
01. cd $HOME/PACS/lab1 
02. ls –l > trash
03. more trash
04. cat < trash
05. cat < trash > trash2
06. more trash2
07. cat < trash >> trash2
08. more trash2
09. cat < trash | wc
10. man wc
11. rm trash trash2
```

### Parameter Passing in C++

The main() routine of a C++ program can receive the following parameters: `argc` (argument count) and `argv` (argument vector).

```
int main (int argc, char *argv[]) { /* ... */ }
```

The Shell initializes these variables and they can be used later on by the program. The argc parameter contains the number of arguments (words) in the command line that launched the program, whereas argv is an array of character pointers listing all the arguments. For instance, for the following command line:

```
$labmachine> ./myprogram hey you 6
```
The Shell sets argc=4, argv[0]="myprogram" (i.e., the name of the program), argv[1]="hey", argv[2]="you", and argv[3]="6".

### Processes (Information and Removal)

- Information about processes: `ps`
- Information about user processes: `ps –u username`
- Extended information about user processes: `ps –lu username`
- Remove/killing a process: `kill -9 PID`, where PID refers to the process id, and can be retrieved from the output of the above command
		
#### Examples

```
01. ps
02. ps –u username
03. ps –lu username
04. man ps
05. kill -9 PID
```

Finally, you are encouraged to check out these games from [OverTheWire](https://overthewire.org/wargames/bandit/) and [MIT](https://web.mit.edu/mprat/Public/web/Terminus/Web/main.html) to learn more command line skills.

## Compiling C++ Tools: Compiler

Compilation tools help the programmer in the process of generating the binary (machine code) corresponding to the program to be implemented. When we think of compilation tools we should not limit ourselves to the compiler alone. We must add to the list debuggers and program behavior analyzers (performance, code, memory, parallelism...). These tools help the programmer to obtain a correct, safe, and efficient binary.

The compiler is a tool capable of translating a program written in high level (C, C ++, Ada, Pascal...) to machine or binary code that can be executed on the target processor (x86, x64, SPARC V9...).

Once the program of the application that we want to implement has been coded in a high-level language, we save it in a text file, which we will call a source file. The generation of a binary (executable file) from a source file in a high-level language requires two compilation phases: translation (transfer) and linking (link). In the first phase, the compiler analyzes the source file in high-level language and generates an equivalent program in native machine language of the processor architecture in which we want to execute the program. As a result, the translation phase generates an object file. To finish building a binary file of the complete program, all those functions and procedures that are used but whose implementation can be found in other object files (system library or user library) are required. In the linking phase, the objects (or a reference to them) containing the external functions and procedures (system or user) used by the original source are added.

The programs that we write in C++ language must be stored in a simple text file whose extension will be ".cpp". The default extension of the object files will be ".o". In the lab machines, we have the GNU g++ compiler for programs written in C++ language. This tool does the compilation phases, translation and linking, in a joint or separate manner.

To perform only the translation, use the `–c` flag:

```
$labmachine> g++ -Wall -c sourcecode.cpp
```
The `-Wall` flag enables all the warning messages from the compiler during the compilation process. It is encouraged to include such a flag in all compilations. On a successful translation, a sourcecode.o file is produced as a result. This file refers to the object file of the source file sourcecode.cpp. Try such a command with the HelloWorld.cpp example.

If we want to carry out the linking of several object files to generate the executable (named "binary_file" in the command below), we must use the `-o` flag. Only one of the object files must have the main symbol defined, which will be the entry point to the program. Those objects belonging to system libraries do not need to be specified as they are automatically added by the compiler:

```
$labmachine> g++ -Wall object0.o object1.o object2.o ... objectN-1.o -o binary_file
```

Try the above command using the HelloWorld2.cpp and func.cpp source files. Remember that the corresponding object files should be generated first.

Finally, if we want to generate the executable file corresponding to the source file in a single step, use the `–o` flag:

```
$labmachine> g++ -Wall source0.cpp source1.cpp ... sourceN-1.cpp -o binary_file
```

If the `-o` flag is not specified, an executable named "a.out" will be generated by default. Furthermore, this command allows specifying object files as input to the compilation tool.

With the `-v` flag specified in the compilation command, verbose information on all the steps the tool takes while compiling a source file is displayed. In addition to these options, compilers have many other available options. Type the following command for further information:

```
$labmachine> man g++
```

Once the executable file of our program has been generated, we can launch it from the command line itself using:

```
$labmachine> ./binary_file
```

## Compiling C++ Tools: Debugger

A debugger is an application for finding out how a program runs or for analyzing the moment a program crashes. Debuggers usually perform many useful tasks, including running the program, stopping the program under specific conditions, analyzing the situation, making modifications, and testing new changes.

GDB can be used as a C++ debugger if a program is compiled with the GNU g++ compiler and the `–g` flag is enabled. By debugging with GDB, you can detect errors and solve them before they cause severe issues. The first step of learning how to use GDB for C++ debugging is to compile the C++ code with the `-g` flag:

```
$labmachine> g++ -Wall -g sourcecode.cpp –o binary_file
```

The next step is calling GDB to start the debugging process for the program you wish to analyze:

```
$labmachine> gdb binary_file
```

Try the above command using the binary after compiling mult.cpp. The above command opens GDB but does not run the program. There are several ways of running the opened program. First, the program can be executed with the run command:

```
(gdb) run
```

Command-line arguments can be passed if the program needs them:

```
(gdb) run arg1 arg2 ... argN-1
```

A program can be debugged more efficiently using breakpoints. Breakpoints refer to instructions that stop the execution at specific code locations. For instance, breakpoints can be set in places suspected to be problematic. It is a common practice to set breakpoints before running the program. Breakpoints can be set in two ways:

- Setting a line at which the execution stops.
- Setting a function name to stop the execution at.

The following example sets a breakpoint at the start of the main function:

```
(gdb) b main
```

This example sets a breakpoint at a specific line (7):

```
$ (gdb) b 7
```

This example lists all of the breakpoints:

```
$ (gdb) info b
```

This command deletes the breakpoint at line 7:

```
$ (gdb) delete 2
```

You might need to execute a program slowly, moving from one line to the next one. There are two ways of making the program run step-by-step.
The command next, or simply n, executes the current command, stops, and displays the next line for execution. However, if the line is a function call, the debugger will fully execute the function before the execution stops again:

```
$ (gdb) n
```

To execute line after line, even if a new function is invoked so that the sequential program flow breaks, the command step (s) can be used.

The command continue (c) resumes the execution until the end or the next breakpoint:

```
$ (gdb) c
```

The values of variables can be checked during specific moments of the execution. The print command can be used for this task. It is possible to print more complicated expressions, type casts, call functions, etc.

Syntax for using print:

- print \<exp\>: to get values of expressions.
- print /x \<exp\>: to get the value of expressions in hexadecimal.
- print /t \<exp\>: to get the value of expressions in binary.
- print /d \<exp\>: to get the value of expressions as unsigned int format.
- print /c \<exp\>: to get the value of expressions as signed int format.

Use combinations of the above commands to show how the variables i, j, and v are updated after a few iterations of the innermost loop of mult.cpp.

More commands and further details can be seen typing:

```
(gdb) help
```	

The command quit (q) allows to exit from the gdb environment.

## Programming Basics

This section is organized in three parts: 1) program a basic code consisting of a matrix multiplication, 2) do the same as the previous part but using the Eigen C++ math library, and 3) compare both solutions in terms of execution time. This lab finishes upon completion of these three assignments and writing of a report to be submitted before **October, 24th** through Moodle. More details about what the report should contain can be found below in the third part.

### Standard Matrix Multiplication

Matrix multiplication is a very common operation found in many vision, robotics, and graphics algorithms. In addition, such an operation can be highly parallelized making use of a GPU, an FPGA, or other accelerator devices exploiting either CUDA or OpenCL programming models. For now, we are going to implement this algorithm in a CPU exploiting the C++ sequential programming model.

This assignment solicits to code variable sized NxN matrices to be multiplied. The figure below shows a diagram to refresh you about how the matrix multiplication is performed.

<img src=figures/matmult.png width=300 height=150>

Be sure that your matrix multiplication algorithm works by trying small matrix dimensions and debugging when necessary. Once the algorithm works, there is no need to print out the results of any computation. The data type of the matrices should be **double** and the elements should be prefixed at any value or randomly generated (prefixed here means that the program should not ask the user for values from the standard input). Either static or dynamic memory allocations can be used, although the use of the latter is preferred to adjust the memory requirements at runtime and to test the program with large matrices (e.g., N=1000).

### Eigen Math Library

The next part is to code the same algorithm using the Eigen library. To do so, download the Eigen 3.3.7 package version from Moodle or GitHub and unzip the contents in $HOME/PACS/lab1. The disk requirements of this library are just 13 MB. You can see this information by typing:

```
$labmachine> du -sh $HOME/PACS/lab1/eigen-3.3.7
```

The downloaded library is a headers-only Eigen implementation, meaning that the library compiles with the application, so just refer to the directory where the Eigen library is to be found when compiling your program with the flag `-I`. The flag `-O2` sets the optimization level of the compilation, please find the meaning in the [g++ manual](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html).

```
$labmachine> g++ -O2 -Wall -I $HOME/PACS/lab1/eigen-3.3.7/ my_eigen_matmult.cpp -o my_eigen_matmult
```

[Here](http://eigen.tuxfamily.org/dox/index.html) you will find detailed information about how to use Eigen for matrix multiplication. In contrast to the previous standard implementation, the Eigen-based version should occupy a fewer number of code lines. Assume the same conditions about the variable matrix sizes, generation of the element values, and the memory allocation policy as in the previous assignment for a fair performance comparison in the next part.

Eigen uses by default the available vectorization of Intel processors to compute the solution. Figure out how such a vectorization can be deactivated from the source code to come up with two different versions of an Eigen matrix multiplication implementation: with and [without vectorization](http://eigen.tuxfamily.org/index.php?title=FAQ#Vectorization).

### Performance Evaluation and Report

The last part deals with the performance evaluation of the three matrix multiplication versions: i) standard, ii) Eigen with vectorization (default in Eigen), and iii) Eigen without vectorization. Use the `time` command, already studied in theory lessons, to obtain the execution times.

The report should contain an **experimental evaluation consisting of a graph (or table) plotting the execution times for every coded version and reasonably varying the NxN matrix sizes to show significant performance differences, as well as a comparison/discussion of the plotted results (not only what can be seen in the graph but also why such performance differences appear)**. The source code of the three versions will be submitted in separate files through the same Moodle resource, and should not be included within the report. There is no template for the report, but it should contain the names of each of you and not to be longer than **2 single-column pages**. Of course, just one member of the couple has to submit the report through Moodle.

## Final notes

Feedback to improve this lab is very welcome. Thanks.