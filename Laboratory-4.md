# Some Building Blocks of Parallel Programming

## Introduction

This lab advances the knowledge on parallel programming and builds two key
components often present in parallel applications: a multi-producer
multi-consumer queue and a thread pool. The first provides an element to store
and feed tasks or works to the working threads that continuously try to fetch
tasks from the queue and then execute them. To code both components, you will
extensively manage `std::mutex`, `std::condition_variable`, and
`std::thread`. The goals of the lab are: i) think in possible parallelization
strategies based on splitting the work into task, ii) implement a simple thread pool that decouples
the creation and the execution of the tasks, and iii) test and explore the devised
parallelization strategies (splitting by rows, by columns, by square regions...).

As an example of a parallel application that can benefit from working in parallel, this lab
employs a ray tracer. The idea of this application comes from a [teaching
innovation project](https://doi.org/10.1145/3338698.3338886) done by multiple
faculty of the [Computer Science](https://diis.unizar.es) at the University of
Zaragoza.

Completing this assignment requires to submit the 2-page report and the source
code of the thread-safe queue and the thread pool. The deadline for the
submission is **December, 4<sup>th</sup> 2020**. Please remember to concisely
answer the questions in your final report.

## Preliminaries

As previous labs, the code is available in the [class
repo](https://github.com/universidad-zaragoza/PACS/tree/master/Laboratory-4). Please ensure
that you have downloaded the last version of the code, and remember that to
avoid issues compiling the program, the repository uses `cmake` as build
system. The main
[README.md](https://github.com/universidad-zaragoza/PACS/blob/master/README.md)
file of the repo provides extra information on `cmake` and how to build and run
the applications on Linux, mac OS, and Windows. _Please note that this last
platform is not officially supported_.

## Application architecture

The ray tracer generates a 2D image from a 3D representation of a virtual
scene, including geometry and optical properties of the objects and physical
characterizations of cameras and light sources. In practice, the algorithm
simulates light transport paths across the virtual scene in order to obtain the
final color that reaches each of the pixels of the image. Paths are generated
from the camera and traverse each pixel independently. Since the computation
associated to each pixel is independent, the algorithm is highly
parallelizable. Moreover, such a parallelization is worthwhile because the
algorithm is computational intensive and takes quite a long time to converge
(about 1 or 2 hours for a good quality result for a simple virtual scene, and
even days in the case of more complex scenes).

A common ray tracing parallelization strategy is to subdivide the image into
different tiles or regions, converting the computation of each of the tiles
into a render task to be executed. Since the amount of work per task varies
depending on the geometry and other properties of the virtual scene, this
problem can benefit from a dynamic task scheduling, where threads pick tasks
from a thread-safe queue instead of executing a static assignment as in
Laboratory 3. The parallelization strategies can be based on:

* Different image tiles: rows, columns, or rectangles.
* Different tile sizes: from small rectangles to multiple column batches.

A general thread pool allows to receive tasks during all its lifetime, but for
this particular problem, we are going to enqueue all the tasks at the beginning
of the application, and then, wait for their completion.

## Code organization

The main file of this assignment is `smallpt_thread_pool.cpp`. It includes the
main function and all the code related to the ray tracer. To complete the
assignment, you only need to instantiate the thread pool, launch the tasks, and
wait for their completion. Internally, the thread pool includes the queue that
stores the assignments.

Both the queue and
the thread pool are located inside the [include
directory](https://github.com/universidad-zaragoza/PACS/blob/master/Laboratory-4/include),
since they are templated files that need to be always compiled. The queue and
thread pool files are `threadsafe_queue.hpp` and `thread_pool.hpp`. Together
with these two files, there is a third `join_threads.hpp`, whose main goal is
to guarantee that when the thread pool is destroyed, it waits for all threads
to finish execution. Contrary to `threadsafe_queue.hpp` and `thread_pool.hpp`,
the file `join_threads.hpp` does not require any change.

By default, the queue stores invocations to functions without arguments, so
when you are invoking the `submit` function member of the thread pool to queue
a task, please encapsulate the call inside a lambda function:

```C++
Region reg(xmin, xmax, ymin, ymax);
pool.submit([=]{ render(w, y, samps, cam, cx, cy, c_ptr, reg); });
```

## Implementing a Thread-safe Queue

The first step of the lab is to complete the [threadsafe_queue.hpp](https://github.com/universidad-zaragoza/PACS/blob/master/Laboratory-4/include/threadsafe_queue.hpp) file. In particular, you have to fill the following function members:

```C++
 void push(T new_value)
{
  // to-do
}

bool try_pop(T& value)
{
  // to-do: this function does not block,
  // if the queue is empty, it returns false, otherwise
  // it writes the front of the queue in value and returns true
}

void wait_and_pop(T& value)
{
  // to-do
}

std::shared_ptr<T> wait_and_pop()
{
  // to-do
}

bool empty() const
{
  // to-do
}
```

To implement the `empty()` function member, you may need to use the type specifier [mutable](https://en.cppreference.com/w/cpp/language/cv) that permits modification of the class member declared mutable even if the containing object is declared const. 

### Question 1 

Do we need to protect the function members with mutual exclusion to guarantee correctness? How `std::mutex`and `std::condition_variable` help with this task?

## Implementing a Thread Pool

The second step of the lab is to complete the [thread_pool.hpp](https://github.com/universidad-zaragoza/PACS/blob/master/Laboratory-4/include/thread_pool.hpp) file. This simple thread pool can run jobs until a variable flags the termination of all the threads, and the workers can either spin for tasks or call [std::this_thread::yield](https://en.cppreference.com/w/cpp/thread/yield) to notify the OS the worker does not have work to do.

To execute the ray tracer application, you have to fill the following function members:

```C++
private:
  void worker_thread()
  {
     // function member that the threads are running

  }
public:
  thread_pool(size_t num_threads = std::thread::hardware_concurrency())
    : // to-do
  {
      // to-do

  }

  ~thread_pool()
  {
    wait(); // ensure no pending tasks
  }

  void wait()
  {
    // wait for completion

    // active waiting
  }

  template<typename F>
  void submit(F f)
  {
        // to-do
  }
};
```

### Question 2

Is it possible to implement the thread pool, so that it waits for the completion of all the tasks with the help of the thread_pool destructor?

## Compiling the application

Please follow the same cmake steps as in previous laboratories. Since this lab deals with templates and their errors can be very verbose, consider redirecting the output of the compiler to a file or at least to pipe the compiler output to [less](https://man7.org/linux/man-pages/man1/less.1.html) or save the output to a file with [tee](https://man7.org/linux/man-pages/man1/tee.1.html) at the same time you can read the output from the terminal.

```bash
$ make 2>&1 | less # redirect error to standard output and read with less
$ make 2>&1 | tee compiler_output.txt | less # redirect the output, save it to compiler_output.txt at the same time you can read it on the screen
```

## Testing the application

One approach to test the ray tracer is to compare the output file `image3.ppm` with the [reference image](https://github.com/universidad-zaragoza/PACS/blob/master/Laboratory-4/extra/reference_image.ppm) from the `extra` directory. Please remember that since the ray tracer uses random numbers, the files will _not_ be exactly equal. 

## Measuring performance

Think in possible parallelization strategies and run them with the `smallpt_thread_pool` binary. The `w_div` and `h_div`, read from the command line, can help you with sizing the regions for your tasks. As possible strategies, please consider: columns, rows, tiles, such as 128 128 1 1...

### Question 3

Plot the execution times (with the tested configurations on the X axe) and try to justify your findings.
For example, does working with large regions provide more or less opportunities for speeding up the applications? Why?

## [Optional] Question &alpha;: Use the thread pool with another problem

Once you have run the parallel ray tracer and verify that the queue and the
thread pool work, you can reuse them to run tasks in other applications. Please
talk with me before following this path to ensure you do not overcommit. Depending
on the application, `std::packaged_task` could help to write a better implementation.
Also, you would only need to measure performance for your application and not the ray
tracer.

## [Optional] Question &beta;: Implement a lock free queue with `std::atomic`

More advanced queues use lock-free operations to reduce their serial parts. Michael and Scott 
wrote a seminal [paper](https://www.cs.rochester.edu/u/scott/papers/1996_PODC_queues.pdf) where 
they describe a non-blocking concurrent queue. Implement Michael and Scott's queue and compare its
performance with the blocking, `std::mutex` version. For the comparison, write a small benchmark
where multiple threads continuously push and pop integer values from a queue. For the implementation, you
will need compare and swap operations such as the ones provided by the [atomic](https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange) header.

## Final notes

Please share your feedback on this laboratory with me, thanks.

