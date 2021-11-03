# Profiling: Instrumented and Event-based Techniques

Profiling is a form of dynamic program analysis that measures a variety of program statistics like the memory usage, the execution time, the usage of particular instructions, or the frequency and duration of function calls. Profiling serves two main purposes: i) understand program behavior and ii) aid program optimizations.

Profiling is achieved by instrumenting either the program source code or its binary executable form using a code profiler tool. Profilers may use a number of different techniques, such as event-based, statistical, instrumented, and simulation methods. This lab covers instrumented and event-based profiling.

The assignment of this lab consists of four exercises spread across the lab description. A **report with 4 single-column pages (at most)** summarizing the results and conclusions of the lab exercises should be submitted before **November, 7th** through Moodle. Only the **two source codes from the Exercise 2** should be submitted in separate files through the same Moodle resource. **See the last but one section of the lab description for further details about the report contents**.

## Goals of the Lab Session

- Learn instrumentation profiling techniques through the usage of library functions and commands.

- Learn how to use an event-based profiler: the Linux perf performance analyzing tool.

## Instrumentation Profiling

Manual code instrumentation is a technique that adds instructions to the target program to collect the required statistics. Instrumenting a program can cause performance changes, and may in some cases lead to inaccurate results. The effect will depend on what information is being collected and on the level of the reported timing details. In other words, the effect depends on the granularity of the instrumentation. For instance, adding code to count every procedure/routine call will probably have less side effects than counting how many times each statement is obeyed.

This section introduces two different library functions, `clock()` and `gettimeofday()`, that allow the user to manually instrument the code in order to obtain the execution time. In the case of `gettimeofday()`, we will define pieces of code where the execution time will be measured separately instead of for the whole program as we have seen so far with the `time` command. In addition, we will study how to use the `strace` command to monitorize the system calls of a program.

### clock()

The `clock()` function is defined in the `ctime` header file and returns the approximate execution time consumed by a program. Its syntax is as follows:

```
clock_t clock();
```
The function does not use any argument. On success, `clock()` returns the execution time of the program, referred to as the elapsed time from the program launch to the call of the function. On failure, it returns -1 casted to type `clock_t`. The value returned is expressed in clock ticks, which are units of time of a constant but system-specific length. The epoch used as reference by `clock()` varies between systems, but it is related to the program execution (generally its launch). To calculate the actual processing time of a program, the value returned by `clock()` shall be compared to a value returned by a previous call to the same function.

#### Example

```
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

long fibonacci (unsigned n) {
    if (n<2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    clock_t time;
    time = clock();
    cout << "f(45) = " << fibonacci(45) << endl;
    time = clock() - time;
    cout << "Seconds: " << fixed << setprecision(4)
        << ((float)time)/CLOCKS_PER_SEC << endl;
```

The above example shows in the standard output the execution time of a program computing some Fibonacci numbers. To convert the returned value to seconds, it is necessary to divide the returned value by the macro `CLOCKS_PER_SEC`. Options `fixed` and `setprecision()` are used to adjust the precision of the returned value.

#### Exercise 1: Measure the execution time of both your standard matrix multiplication and Eigen-based (only with vectorization) programs from the previous lab, including the memory allocations, matrix element initializations, and the actual matrix multiplication using `clock()`. Try different N sizes, compare the results with those from the `time` command, and extract conclusions. For a fair and meaningful comparison, run the instrumented program and `time` as a single command line. In case of no completion of the assignment from lab 1, the materials of this lab (See Moodle) include two versions of the matrix multiplication that can be used for this purpose.

### gettimeofday()

The `gettimeofday()` function from the `sys/time.h` library accurately measures the time it takes to execute certain operation or a piece of code of a program. The function gets the system's clock time. Such a time value is expressed in elapsed seconds and microseconds since 00:00:00, January 1st, 1970 (Unix Epoch). The `gettimeofday()` function theoretically offers a precision of microseconds. Its syntax is as follows:

```
int gettimeofday (struct timeval *tp, struct timezone *tz);
```

The first argument points to a `timeval` structure. This structure is declared as follows in `sys/time.h` header file:

```
struct timeval {
  time_t tv_sec;   //used to register seconds
  suseconds_t tv_usec;   //used to register microseconds
}
```
The `timeval` structure represents a calendar time. The `tv_sec` field refers to the number of seconds since the epoch, whereas `tv_usec` are the additional microseconds after the number of `tv_sec` seconds calculated since the epoch.

The second argument points to the `timezone` structure. It should normally be set to NULL because `struct timezone` is obsolete. This argument is for backwards compatibility only.

On success, `gettimeofday()` returns 0, for failure the function returns -1.

#### Example

```
#include <iostream>
#include <sys/time.h>

using namespace std;

int main() {
    struct timeval timestamp;
    gettimeofday(&timestamp, NULL);
    cout << "Seconds: " << timestamp.tv_sec << endl
        << "Microseconds: " << timestamp.tv_usec << endl;
    return 0;
}
```
The above program displays to the standard output the elapsed number of seconds (integer part) and the additional number of microseconds (fraction part) from January 1st, 1970.

Remember that you can always refer to the Linux manual for further details:

```
$labmachine> man gettimeofday
```

#### Exercise 2: Separate the clean standard matrix multiplication code from lab 1 (removing the `clock()` calls from the previous exercise) into two pieces of code and obtain the execution time of each piece using `gettimeofday()`. One piece of code should exclusively refer to the computation of the matrix multiplication. The other part should contain everything else, including the matrix declarations, memory allocations, and initializations. Try different N size values, compare the results with those from the `time` command, and extract conclusions. Again, for a fair comparison, run the instrumented program and `time` as a single command line. Finally, do the same with the clean Eigen-based version with vectorization and compare results.

### strace command

The `strace` command is a debugging tool to assist the programmer in the monitorization of system calls and signals of a specific program. This command is particularly helpful when the source code is not available and one would like to debug the execution of a program. More precisely, `strace` provides the user a system call execution sequence of a binary from start to end.

The `strace` command can be used to trace the execution of any binary. The following example launches `strace` for the Linux `ls` command.

```
$labmachine> strace ls
```

The output lists the sequence of system calls as a consequence of running `ls`. Among these systems calls, `execve` at the beginning and `write` at the end can be highlighted, respectively, as the system calls responsible to change the original process image (duplicated Shell) to the `ls` image and the writing of the current directory contents to the standard output.

By default, `strace` displays all system calls for the given executable. To display only a specific system call, the `-e` option can be used as follows:

```
$labmachine> strace -e execve,write ls
```

The above command filters all the system calls but the `execve` and `write` system calls.

To print the timestamp for each `strace` output line, use the option `-t` as shown below.

```
$labmachine> strace -t -e execve,write ls
```

Using option `-c`, the command provides a useful statistical report for the execution trace.

```
$labmachine> strace -c ls
```

The "calls" column indicates how many times a particular system call was executed. The "seconds" column states the accumulated amount of seconds running each type of system call. The "% time" indicates the percentage of the total system execution time dedicated to run a specific type of system call.

#### Exercise 3: For a sufficiently large N size value, run the `strace` command with the `-c` option for both the instrumented standard matrix multiplication and the Eigen-based (with vectorization) programs with the `clock()` and `gettimeofday()` functions. That is, four different runs of the `strace` command are requested: i) standard matmult + clock, ii) standard matmult + gettimeofday, iii) Eigen + clock, and iv) Eigen + gettimeofday. Include in the report the most interesting results from the four outputs, perform cross-comparisons among them stating the main differences, and reason about such differences.

## Event-based Profiling

Event-based profiling uses hardware performance event counters to measure a number of specific kinds of events that occur during the execution of a program. Examples of events include processor clock cycles, retired instructions, data cache hits, or data cache misses. The specific events to be measured are determined by the profile configuration that is used to set up data collection. This section introduces `perf`, a command-line profiling tool for Linux that provides access to the Performance Monitoring Unit (PMU) in a CPU, and thus allows the user to have a close look at the behavior of the hardware and its associated events. The available events are processor implementation specific. In addition, `perf` can also monitor software events through pure-kernel counters, such as context-switches or minor-faults, and create reports out of the data that is collected.

To obtain a full list of the supported events, type:

```
$labmachine> perf list
```

Press ENTER to scroll down in the list of events and `q` to exit from that list.

To filter the list just showing a list of events available in a specific category, use `perf list` followed by the category name: `hw`, `sw`, `cache`, `pmu`, etcetera. For instance, `perf list sw` displays the list of software pre-defined events in Linux.

With the `stat` option and no particular events specified in the command line, `perf` runs a command and collects by default some common performance statistics during the execution of such a command, which will be enough for our purpose. For example:

```
$labmachine> perf stat ls
```

The displayed stats indicate the following:

* `task-clock (msec)`: the amount of time that the command execution spent in the CPU (in milliseconds).
* `context-switches`: this stat (also known as process switches) indicates the number of times the CPUs were switched from one process (or thread) to another.
* `cpu-migrations`: in a multicore machine, CPU or process migrations happen as a standard part of the process scheduling, and it is relatively easy to migrate a process within a given machine, since most resources do not need to be changed but only the execution context (primarily the program counter and the registers).
* `page-faults`: refers to the number of page fault exceptions raised by the computer hardware when the running program accesses a memory page that is not currently mapped in the physical memory by the memory management unit.
* `cycles`: the total number of CPU cycles that are consumed.
* `instructions`: the total number of CPU instructions that are executed.
* `branches`: the total number of instruction branches encountered while executing the program. This is the CPU-level representation of decision points and loops in the code. The more branches, the lower the performance.
* `branch-misses`: to compensate for the above performance penalties, modern CPUs attempt to predict the flow the code will take. This stat indicates the number of branch misses and the percentage with respect to the overall number of branches.
* `seconds time elapsed`: refers to the overall execution time of the command. Dividing the first stat with the current stat gives the percentage of CPU utilization.

Note that other metrics like the operating frequency (in GHz) or the instructions per cycle (IPC) can be derived from the previous stats.

The `-e` option can be used to collect just specific events, which are separated with commas:

```
$labmachine> perf stat -e cycles,instructions ls
```

The above example just shows the cycles and instructions after the `ls` run.

It is also possible to use `perf stat` to run the same test workload multiple times and get for each count, the standard deviation from the mean. To do so, use the `-r` option as follows:

```
$labmachine> perf stat -r 5 ls
```

In the previous example, `ls` is run 5 times and the mean count for each event, along with a ratio of std-dev/mean is printed.

#### Exercise 4: Similarly to the previous exercise, for a sufficiently large N size value, run the `perf` profiler for four different runs: i) standard matmult + clock, ii) standard matmult + gettimeofday, iii) Eigen + clock, and iv) Eigen + gettimeofday. Dump the most interesting statistics in the report, perform cross-comparisons stating the main differences, and reason about such differences.

## Recommendations for the Report

* Run n times those experiments involving time to mitigate the effect of spurious results. Report mean values and the standard deviation.
* Exercise 1: Are there any differences between `time` (user and real) and `clock()`? Justify such differences.
* Exercise 2: What is the relative overhead of the initialization code section with respect to the entire execution as the problem size increases? Is it possible to relate somehow the system, user, and real times with the results given by `gettimeofday()`?
* Exercise 3: Choose at least 4 different system calls from the `strace` outputs showing differences in the number of calls (could be even 0 calls) between two different runs (e.g., Eigen + time vs. Eigen + gettimeofday, or standard matmult + gettimeofday vs. Eigen + gettimeofday) and reason about the differences. There is no need to dump in the report the entire outputs from `strace`, but just for the chosen system calls.
* Exercise 4: Choose at least 4 different metrics/stats from the `perf` outputs showing differences between two different runs (e.g., Eigen + time vs. Eigen + gettimeofday, or standard matmult + gettimeofday vs. Eigen + gettimeofday) and reason about the differences. There is no need to dump in the report the entire outputs from `perf`, but just for the chosen metrics.

Should you have any question about how to elaborate the report, please contact me at: alvabre@unizar.es

## Final Notes

Feedback to improve this lab is appreciated. Thanks.