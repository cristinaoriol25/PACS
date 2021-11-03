# Introduction to Parallel Programming

## Summary

This lab will cover several basic aspects of parallel programming that we are
studying in the class. For the sake of completeness, in the first part of the
lab, you will code a sequential program without threads, and, after that, the
lab asks you to implement a parallel version of the same program.  Also, you
will learn a bit about numeric precision.

Completing this assignment requires to submit both the sequential and the
parallel version of a &pi; approximation algorithm with the responses to the
specific questions of this document in an up to 4-page report, which should be submitted through moodle.
The source codes of your programs should be submitted as well in another moodle assignment.
The deadline for the submission is **November, 20<sup>th</sup> 2020, end of day**. Please remember to
concisely answer the questions in your final report. 

Fixes, comments, suggestions... to improve this lab are welcome. Please send them to @dariosg.

## Preliminaries

As previous labs, the code is available in the [class
repo](https://github.com/universidad-zaragoza/pacs/Laboratory-3). Please ensure
that you have downloaded the lastest version of the code, and remember that to
avoid issues compiling the program, the repository uses `cmake` as build
system. The main
[README.md](https://github.com/universidad-zaragoza/PACS/blob/master/README.md)
file of the repo provides extra information on `cmake` and how to build and run
the applications on Linux, mac OS, and Windows. _Please note that this last
platform is not officially supported_.

## Sequential &pi; computation

The &pi; number represents the ratio of a circle's circumference to its
diameter, and its value was already approximated before the Common Era. The
ancient Greek Archimedes already devised a [&pi; approximation
algorithm](https://en.wikipedia.org/wiki/Approximations_of_%CF%80). In this
lab, we are going to implement another approximation based on Taylor series.

With a Taylor series, &pi; can be approximated as

<img src=figures/pi_taylor.png width=300 height=100>

### Code 1: sequential

Inside the Laboratory-3 directory of the [PACS
repo](https://github.com/universidad-zaragoza/pacs/), there is a file called
`pi_taylor_sequential.cc`. Open the file and complete the body of the pi_taylor
function with the aforementioned formula for a given number of steps. Instead
of computing from 0 to infinite steps, your function will compute "steps"
elements of the series.

The `pi_taylor_sequential.cc` program skeleton already reads the number of
steps and calls the `pi_taylor` function that you need to complete. Also note
that the floating point type can be selected with the `my_float` defined type
at the beginning of the program. The current `long double` float type increases
numeric precision. Also, the program uses
[std::setprecision](https://en.cppreference.com/w/cpp/io/manip/setprecision) to
print as many decimal digits as possible.

### Question 1

What is the goal of the `std::stoll` function?

### Question 2

Once you have completed the function, please copy the time measurement code
from any of the code snippets that uses `std::chrono` and run the program for
16, 128, 1024, 1048576, and 4294967295 steps. Does the execution time
scales linearly with the number of steps?

### Question 3

Please measure with `perf` the number of cycles, instructions and
context-switches for the application with 4294967295 steps.

## Parallel PI

### Code 2: Parallel threaded version

Now, we are going to implement a parallel version of the same &pi;
approximation algorithm. The new `pi_taylor_parallel` program will have two
arguments, the number of steps and the number of threads, and the first value
has to be larger than the second.

The
[Laboratory-3](https://github.com/universidad-zaragoza/PACS/tree/master/Laboratory-3)
directory includes a
[pi_taylor_parallel.cc](https://github.com/universidad-zaragoza/PACS/blob/master/Laboratory-3/pi_taylor_parallel.cc)
skeleton that can help you with the task.  Please note that the implementation
can split the work among threads in a similar way that the
[saxpy-scaling](https://github.com/universidad-zaragoza/PACS/blob/master/code_examples/saxpy_scaling.cc)
does. Also, you are free to change the arguments of the `pi_taylor_chunk`
function at your own convenience.

The main required tasks are the completion of the `pi_taylor_chunk` function
that computes the coefficients for certain steps, the thread creation and
management, and the final add reduction to get the &pi; value.

Your implementation cannot use any mechanism, such as `std::mutex`, to protect
concurrent access to not thread-safe methods and shared variables. For example,
if you want to concurrently fill a vector from multiple threads, do not use
the `push_back` method. Instead, create an empty vector before spawning
the threads, and ensure that each threads writes to a different position.   

### Question 4

Run `pi_taylor_parallel` for 4294967295 steps and 1, 2, 4, 8, and 16 threads,
and perform an scalability analysis, including a plot and some measurement of 
the variability of the program, such as the
[coefficient of variation](https://en.wikipedia.org/wiki/Coefficient_of_variation).

`pilgor.cps.unizar.es` can be your testing machine to avoid thread over-suscription,
a situation that occurs when the number of threads is larger than the number of execution
contexts of the physical hardware.  

### Question 5

If you compare the parallel version with 8 threads and the same number of steps; e.g.,
4294967295, than the sequential version, do you obtain the same exact &pi;
approximation value?

Before answering, please read sections from 2.1 to 2.4 of the book [Handbook
of Floating Point
Arithmetic](https://doc.lagout.org/science/0_Computer%20Science/3_Theory/Handbook%20of%20Floating%20Point%20Arithmetic.pdf)
, and think whether floating point addition preserves the associativity property.

### \[Optional\] Question &alpha;

Depending on your implementation, you may be using an accumulator variable or a large arrays of floating
point values that you add by reduction at the end of the chunk of the program.
This type of additions can also reduce numeric precision, but, fortunately,
there are algorithms such as the [Kahan summation
algorithm](https://en.wikipedia.org/wiki/Kahan_summation_algorithm) that reduce
the error. Modify the code to include Kahan summation and compare the execution time
for 4294967295 steps and 4 threads. To enhance Kahan's advantage, switch the floating
point type to `float`.

### Question 6

Please repeat `perf` measurements of the number of cycles, instructions and
context-switches for `pi_taylor_parallel` with 4294967295 steps, and 4 and 8
threads to perform the comparison with the sequential version.

### \[Optional\] Question &beta;

One key aspect of every parallel application is load balancing, because if
one thread ends later than the rest, it will set the execution time. To verify if 
the &pi; taylor parallel is balanced, please add some timers at the beginning and end of
your chunk function and print with a thread identifier, the thread beginning, end, and execution times. Please run two configurations with 1048576 steps and for the number of threads, one
with the number of cores in the testing machine and another with 8 times that value to check the effect of thread over-suscription.

When you run the program with as many threads as cores on the testing machine,
is the work balanced among the threads and in the over-suscription case?

_Comment: If you run this test in `pilgor.cps.unizar.es`, remember that it has 96 execution contexts
divided into 2 sockets with 2-SMT, simultaneous multithreading, 24-core processor with the [ThaiSan](https://en.wikichip.org/wiki/hisilicon/microarchitectures/taishan_v110) microarchitecture. So running this test in your regular computer or another machine from the lab, reduces the number of required threads to reach over-suscription._ 