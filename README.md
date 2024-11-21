# IPCdeliverable1
![Author](https://img.shields.io/badge/Author-Cornel%20Grigor-informational)

Repository created for the first deliverable of the "Introduction to Parallel Computing course" at UniTN.

## Assignment
The assignment consists of benchmarking and studying the effects of different parallelization techniques used to optimize a matrix transposition. The whole report can be found by opening the __report.pdf__ file.

## Reproducibility
All the tests were done using the University's cluster with _GCC version 9.1.0_.

The main project is written in C++ while the plotter program is written in Python.

Start by downloading the repository, where you can find multiple *methodX* folders, each folder contains a different algorithm that was tested during the making of the report, every algorithm has the same exact folder structure and the instructions below apply to all of them.

- method1: naivexx
- method2: naivexxx
- method3: blockbased

For the best performance overall run *method1*.

### Testing instructions
There are two ways to run the program inside the cluster:

#### PBS script:
1. Connect via SSH to the cluster: ` ssh username@hpc.unitn.it `
2. Upload the project folder into your personal directory on the cluster
3. Go to the `/IPCDeliverable/method1/src/` folder
4. Run `qsub runTranspose.pbs` to submit the pbs script that will do all the compiling and execute all the tests (Runs 5 times for every matrix size for the serial, implicit and OpenMP implementations, for OpenMP it runs 5 times for every number of threads configuration).
The output will be saved in the __runTranspose.o__ file and the csv files containing all the data will be saved into the `IPCDeliverable/method1/data/csv` folder

#### Interactive Session: 
1. Connect via ssh to the cluster: ` ssh username@hpc.unitn.it `
2. Upload the project folder to your personal directory on the cluster
3. Start an interactive session: `qsub -I -q short_cpuQ -l select=1:ncpus=96:ompthreads=96:mem=1mb ` (all tests were conducted using 96 threads in the short_cpuQ queue)
4. Go to the `/IPCDeliverable/method1/src/` folder
5. Run `chmod +x compile.sh` and then run `chmod +x runTests.sh`  to make the scripts executable
6. Run `./compile.sh` to compile the complete code
7. Run `./runTests.sh` to execute the program with all the test cases (same as above in the PBS script). 
The data will be printed on the console but it will also be saved to in the `/IPCDeliverable/method1/data/csv` folder

**The program can also be run manually specifying the matrix size (expressed as a power of 2, default=4), to do so run `./matTrans 12`  (execution with matrix size = 2^12)**

You can also find the `compileMAC.sh` script in the `/IPCDeliverable/method1/src` folder if you need to run the program with _GCC version 11.5.0_ as this was the first available gcc version available for the 2020+ Apple Silicon MacBooks (this was briefly used for some other testing purposes).
 

## Plotter
All the graphs used inside the report were generated using the __plotter.py__ Python program found inside the  `/IPCDeliverable/method1/python` folder.

### Reproducibility
All the testing was done using _Python 3.12.7_ and it runs with the following libraries:
- _Pandas 2.2.2_
- _Matplotlib 3.9.2_
- _Numpy 1.26.4_

Before running the python program you need to run the `/IPCDeliverable/method1/src/runTests.sh` script so that new data gets generated for every test case needed to generate the graphs (if no data is present inside the `IPCDeliverable/method1/data/csv` folder).

All the graphs generated will be saved into the `IPCDeliverable/method1/data/graphs` folder.
