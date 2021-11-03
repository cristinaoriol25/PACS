# Introduction to OpenCL programming
The objectives of the current laboratory session are the following:
* Fundamentals of OpenCL API:
  * Environment setup
  * Host <-> Device communication
  * Simple kernel programming
  * Host-Device synchronization basics 
* Basic kernel programming
  * Image flip
  * Histogram
  * Image rotation

# Previous steps
Before starting with the execises, we will install the CImg Library. The CImg Library is a small and open-source C++ toolkit for image processing. The library can be downloaded from: <http://cimg.eu/files/CImg_latest.zip>. You can also find more documentation and tutorials at <http://cimg.eu/>


In order to use this library you should include the following code in your .cpp file:
```cpp
#include "CImg.h" // Path to the previous download directory
using namespace cimg_library;
```

Let's start by writing the following simple code:

```cpp
#include "CImg.h"
using namespace cimg_library;
int main() {
  CImg<unsigned char> img(640,400,1,3);  // Define a 640x400 color image with 8 bits per color component
  img.fill(0);                           // Set pixel values to 0 (color : black)
  unsigned char purple[] = { 255,0,255 };        // Define a purple color
  img.draw_text(100,100,"Hello World",purple); // Draw a purple "Hello world" at coordinates (100,100)
  img.display("My first CImg code");             // Display the image in a display window
  return 0;
}
```


In order to compile you need the following order
```
$prompt> g++ source.cpp -o executable -I[PATH_TO_CIMG] -lm -lpthread -lX11
```

Next, we show a code that will load an image, dump some statistics about the loaded image and finally accessing to a given pixel. 
```cpp
int main(){
  CImg<unsigned char> img("image.jpg");  // Load image file "image.jpg" at object img

  std::cout << "Image width: " << img.width() << "Image height: " << img.height() << "Number of slices: " \\
      << img.depth() << "Number of channels: " << img.spectrum() \\
      << std::endl;  //dump some characteristics of the loaded image

  int i = XXX;
  int j = XXX;
  std::cout << std::hex << (int) img(i, j, 0, 0) << std::endl;  //print pixel value for channel 0 (red) 
  std::cout << std::hex << (int) img(i, j, 0, 1) << std::endl;  //print pixel value for channel 1 (green) 
  std::cout << std::hex << (int) img(i, j, 0, 2) << std::endl;  //print pixel value for channel 2 (blue) 
  
  img.display("My first CImg code");             // Display the image in a display window

  return 0;

}

```
**Task.** Write a code that reads an image from a file, dumps image data into an array and prompts the value of a chosen pixel in the screen. There is an example of a image in the repository, in any case, you can chose whatever image you want. 

**Task.** Extend the previous work by modifying the original image with a crossing blue line in the middle of the image and check the result by displaying it on the screen.

# Fundamentals of OpenCL API
In this part of the lab, we present the part of the OpenCL API to write code in order to: setup the environment, communicate host<->device, simple kernel programming, and synchronization basics.

Along this section, the following resources will be helpfull:
* Abbreviated reference card of the OpenCL API version 2.1 (https://www.khronos.org/files/opencl21-reference-guide.pdf)
* Reference manual of the OpenCL API version 2.1 (https://www.khronos.org/registry/OpenCL/specs/opencl-2.1.pdf)
 

## Environment Setup
In this section, we will develop a basic program to set up the basic OpenCL environment and to familiarize with the API for that purpose. To begin with, please have a look to `basic_environ.c`. In that file, you should find an "almost" complete scheme of an OpenCL program until the creation of the `command_queue`. The first task is completing the code in `basic_environ.c`, start by completing each appearance of  "/\*\*\*???\*\*\*/". Pay attention to the selection of the device to use. Next, complete this basic OpenCL program and dump on the screen more information about the platform and the devices.

In order to compile you need the following order
```
$prompt> g++ source.cpp -o executable -lOpenCL
```

***Question.*** How many platforms has this computing system? How many devices has each one of these platforms?

## First Kernel on the Device
Once the following steps from 1 to 4 are completed (they refer to the creation of a command_queue for the selected device), in this section we will proceed with the basics to create a new kernel to be launched in the devices. Let's proceed with the following steps, but take into account that some portions of the code must be completed /\*\*\*???\*\*\*/:

1. Create a new file with the kernel you would like to execute into the device. It can be named for example `kernel.cl` This kernel simply calculates the power of two of the elements of an input vector. Feel free to write any other simple kernel you would like to test.

```cpp
__kernel void pow_of_two(
  __global float *in,
  __global float *out,
  const unsigned int count){

  int i = get_global_id(/***???***/);

  if(i < count){
    out[i] = in[i] * in[i];
  }
}
```

2. Add code to the file `basic_environ.c` to load the source code of `kernel.cl` in an array of characters to be processed by the OpenCL runtime. In particular, we will use the procedure clCreateProgramWithSource(). Consider the following code:

```cpp
  // Calculate size of the file
  FILE *fileHandler = fopen(/***???***/, "r");
  fseek(/***???***/, 0, SEEK_END);
  size_t fileSize = ftell(fileHandler);
  rewind(fileHandler);

  // read kernel source into buffer
  char * sourceCode = (char*) malloc(fileSize + 1);
  sourceCode[fileSize] = '\0';
  fread(sourceCode, sizeof(char), fileSize, fileHandler);
  fclose(fileHandler);

  // create program from buffer
  program = clCreateProgramWithSource(/***???***/);
  cl_error(err, "Failed to create program with source\n");
  free(sourceCode);

``` 
3. Build the source code of the program for a given device with the procedure clBuildProgram(). In addition to this, it is convenient to ensure the correctness in the dumped log after the compilation process. 

```cpp
  // Build the executable and check errors
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err != CL_SUCCESS){
    size_t len;
    char buffer[2048];

    printf("Error: Some error at building process.\n");
    clGetProgramBuildInfo(/***???***/);
    printf("%s\n", buffer);
    exit(-1);
  }
```

4. Create a kernel with the selected kernel procedure from the file `kernel.cl: __kernel void pow_of_two ( ... )`. 
```cpp
  // Create a compute kernel with the program we want to run
  kernel = clCreateKernel(/***???***/);
  cl_error(err, "Failed to create kernel from the program\n");
```

5. Create and initialize the input and output arrays at the host memory. Taking into account the kernel definition, the data type of these arrays should be floating point.  

6. Create the input and output arrays at the device memory. Computing device will refer to these objects as the source and destination of the power of two calculations, and they will be referred as arguments of the kernel function at the file `kernel.cl`.

```cpp
  // Create OpenCL buffer visible to the OpenCl runtime
  cl_mem in_device_object  = clCreateBuffer(context, CL_MEM_READ_ONLY, /***???***/, NULL, &err);
  cl_error(err, "Failed to create memory buffer at device\n");
  cl_mem out_device_object = clCreateBuffer(context, CL_MEM_WRITE_ONLY, /***???***/, NULL, &err);
  cl_error(err, "Failed to create memory buffer at device\n");
```

7. Completely copy floating point values in the input array at the host memory to the corresponding input array at the device memory. 

```cpp
  // Write date into the memory object 
  err = clEnqueueWriteBuffer(command_queue, in_device_object, CL_TRUE, 0, sizeof(float) * count, \\
                             /***???***/, 0, NULL, NULL);
  cl_error(err, "Failed to enqueue a write command\n");
```
8. Set the proper arguments to the kernel OpenCL object, as they are specified in the kernel function in `kernel.cl`. First, a pointer to the input memory at the device which should hold the source values on which the power of two operation will be performed. Second, a pointer to the output memory at the device which should hold the result values after finishing the computations in the computation device. Third, the number of elements of the input and output arrays.

```cpp
  // Set the arguments to the kernel
  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &in_device_object);
  cl_error(err, "Failed to set argument 0\n");
  err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &out_device_object);
  cl_error(err, "Failed to set argument 1\n");
  err = clSetKernelArg(kernel, 2, /***???***/);
  cl_error(err, "Failed to set argument 2\n");
```

9. After all the previous steps, we are ready to launch the kernel function to be executed at the computing device.
```cpp
  // Launch Kernel
  local_size = 128;
  global_size = /***???***/;
  err = clEnqueueNDRangeKernel(/***???***/, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
  cel_error(err, "Failed to launch kernel to the device\n");
```

10. Completely read the results of the calculations from the output device memory object and copy them to host memory output array.
```cpp
  // Read data form device memory back to host memory
  err = clEnqueueReadBuffer(/***???***/, CL_TRUE, 0, /***???***/, 0, NULL, NULL);
  cl_error(err, "Failed to enqueue a read command\n");
```

11. Write code to check the correctness of the execution.

12. Release all the OpenCL memory objects allocated along this program.
```cpp
  clReleaseMemObject(/***???***/);
  clReleaseMemObject(/***???***/);
  clReleaseProgram(/***???***/);
  clReleaseKernel(/***???***/);
  clReleaseCommandQueue(/***???***/);
  clReleaseContext(/***???***/);
```

# Basic kernel programming
In this section we propose three basic problems[^1] to be implemented by launching an OpenCL kernel with the core computations for each one. As a result and in order to check the correctness of each problem, plot on the screen the corresponding results, either numerical or transformed images. 
  * Image flip. Transform an image by flipping it over a central vertical axis. That is, this transformation has the same effect as seeing that image reflected in a mirror. The transformation should be done in-place, meaning that the same source buffer for the former image should hold the transformed image after the kernel execution. 
  * Histogram. Process a given image and calculate the histogram for each color channel: red, green, and blue. Each histogram has 256 entries to classify any possible value of the given image.
  * Image rotation. Transform an image by rotating it over the center of the image. The rotation angle should be given as an argument to the kernel. The resulting rotated image should be stored in a new output buffer. Remember the following equations:

     x<sub>2</sub> = cos(angle) * (x<sub>1</sub> - x<sub>0</sub>) - sin(angle) * (y<sub>1</sub> - y<sub>0</sub>) + x<sub>0</sub>

     y<sub>2</sub> = sin(angle) * (x<sub>1</sub> - x<sub>0</sub>) + cos(angle) * (y<sub>1</sub> - y<sub>0</sub>) + y<sub>0</sub>

In these equations, (x<sub>0</sub>, y<sub>0</sub>) stand for the coordinates of the center point of the rotation transformation. (x<sub>1</sub>, y<sub>1</sub>) stand for the source point in the image and (x<sub>2</sub>, y<sub>2</sub>) refer to the destination point after the rotation transformations for the former point (x<sub>1</sub>, y<sub>1</sub>). More information at <https://homepages.inf.ed.ac.uk/rbf/HIPR2/rotate.htm>


[^1]: Feel free to implement any other problem of your consideration as far as the complexity is similar.

***UPDATED***

**Overall Task.** For this final part of the lab description, measure or elaborate the following metrics for *at least one of the* previous exercises. *These metrics are intended for characterizing the application itself, specially the OpenCL key points. Consider the methodological approaches seen in the course or anything else you consider. In any case, please, describe your approach in the report.*
* Execution time of the overall program
* Execution time of the kernel
* Bandwidth to/from memory to/from kernel. *Amount data interchanged with memory for every second*
* Throughput of the kernel. *Effective work per second*
* Memory footprint of the program. *Pay special attention to the OpenCL kernel*

***END UPDATED***

# What should I submit?
The following documents and resources must be delivered at Moodle. The material requested below will refer to at least one of the three implementations proposed in the "Basic kernel programming" section of this lab. Keep the obvious, the rest of the lab script is intended to help you with this final part, please, do not forget it. 

Specifically, it must be delivered:
- A **report** detailing: the answers to the questions asked in the "Basic kernel programming" section, the rationale behind the design and implementation decisions taken, and whatever you consider important enough. Length: approximately 10 to 15 pages. As expected, I do not just look for quantity but also I am looking for quality. Separately, they worth nothing.  
- *Source Files* used.

**Deadline**: The deadline for the submission is **December, 18th 2020**.

# Final notes

Please share your feedback on this laboratory with me, thanks.