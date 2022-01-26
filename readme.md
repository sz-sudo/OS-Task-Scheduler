# Scheduling Algorithm

## 1. General Information
This is a program for scheduling tasks in operating systems written in CPP. We have simulated 4 processors using threads. We have created a thread for each processor, and the fifth thread is used for printing the information about Ready and Waiting queues. The algorithms implemented in this project are [FCFS](https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics)), [RR](https://en.wikipedia.org/wiki/Round-robin_scheduling) and [SJF](https://en.wikipedia.org/wiki/Shortest_job_next). We have three types of Tasks X, Y and Z and three types of resources R1, R2, R3.
Task X needs R1 and R2, task Y needs R2 and R3 and task Z needs R1 and R3.

## 2. Input 
The input must be provided as below:
2<br/>
2<br/>
2<br/>
4<br/>
T1 Y 3<br/>
T2 X 6<br/>
T3 X 5<br/>
T4 Z 1<br/>
 
The first three integers represent the number of each type of resource available (in this example we have R1 = 2, R2 = 2 and R3 = 2) and the fourth integer represents the number of tasks that are going to be entered. After that, for each task, we must enter its name (e. g. T1), its type (e. g. Y) and its duration (e. g. 3).
A class called Task is created to represent each task as an object with the attributes we mentioned. Each Task also has a State (or Status) which can be set to Ready, Running or Waiting.
For each algorithm, we have a separate CPP file with it's own main function.

## 3. Output
The program's output in every step is the contents of Waiting and Ready queues and The status of the CPUs.
