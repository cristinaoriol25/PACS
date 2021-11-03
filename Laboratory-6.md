# Heterogeneous Programming in OpenCL

The objectives of the current laboratory session are the following:
* Implement a runtime engine that uses the two acceleration devices, multicore CPU and GPU, available on the department's machines of both labs 0.06 and 1.02.
* Design a concurrent application that takes advantage of all possible parallelism. 
* Characterize the concurrent application by measuring time of either the communication or the computation (kernel).

# Problem Description
Let's assume that we have a set of images in JPG format. For that set of images, we will apply some transformation like the ones seen in the previous lab session (you can also propose another transformations of similar complexity). This transformation will be applied to all the images of the original image set. 

The processing of the image stream must concurrently use the two acceleration devices available in labs 0.06 and 1.02, both multi-core and GPU. Workload balancing can adopt two approaches: issue each image of the stream to a device, or split each image among both devices.


## The set of images
Space limitations in the DIIS department's user accounts make it impossible to store a large number of different images in your accounts. The same applies to the result of processing the stream of images. We propose to simulate this large set of images in the following way. We can use a very reduced set of images and replicate it in memory many times. For example, if we use the same image as in the previous lab session, we can replicate it in memory 5000 times. That is, if this image occupies 64 KiB, we would have a stream of 5000 images to process in memory, which occupies a total of 64KiB * 5000 = 320 MiB. This is just an example, you are encouraged to consider different replication strategies.

Concerning the results of this heterogeneous application, we cannot save in our account such a complete result (i.e. 5000 output images). Since we know that many of these images are the same, by saving the result of just one of them we can check the correctness of the transformation. Anyway, this does not mean we can avoid getting the result back to the host memory from the device memory.

# Once the application is implemented, it is requested: 
* A detailed analysis of the execution times and performance of the application.
* A measurement of the workload unbalance of the two devices in your approach.
* Determine the bottleneck of the heterogeneous execution.
* Comparison of the execution time with the non-heterogeneous alternative: multi-core or GPU only.

# What should I submit?

The following documents and resources must be delivered at Moodle. The material requested below will refer to at least one of the three implementations proposed in the "Basic kernel programming" of the previous lab session.

Specifically, it must be delivered:

* A **report** detailing: the answers to the requests asked in the present script and an explanation of your approach to solving the problem on the heterogeneous platform (and whatever you consider important enough). Pay special attention to describe load balancing, memory management, and kernels running on each device. An analysis of the capacity of your implementation to adapt to new execution environments, different set of input images or different transformations to be carried out. Length: approximately 10 to 15 pages. 

* **Source files** used.

Deadline: The deadline for the submission is January, 15th 2021.

# Final notes

Please share your feedback on this laboratory with me, thanks.

