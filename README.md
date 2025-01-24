# Salad Preparation Parallelism

## Description

This project simulates a parallel process where a chef and three salad makers work together to prepare salads. The chef selects ingredients randomly and assigns them to the salad makers, who then prepare the salads concurrently. Shared memory and synchronization mechanisms such as semaphores are used to coordinate the actions and ensure proper task distribution among the salad makers.

## Key Features
- **Parallel Processing**: The chef and salad makers run in parallel processes, making use of shared memory to communicate and synchronize their actions.
- **Concurrency Management**: The project uses semaphores and mutexes to handle concurrency between the chef and salad makers, ensuring that resources are shared and operations are coordinated.
- **Log Files**: The project generates detailed log files, including a global log file and individual logs for each salad maker, to track the progress of the parallel tasks.
- **Time Intervals**: The project tracks and outputs time intervals during which multiple salad makers are working concurrently, giving insights into the performance of parallel execution.

## Execution

1. **Compiling the Program**:
   The project consists of several modules and helper functions, with the two main programs being `chef.c` and `saladmaker.c`. Use the `Makefile` to compile the programs:
   ```bash
   $ make chef           # To compile the chef program
   $ make saladmaker     # To compile the saladmaker program
   $ make                # To compile both programs at once

2. **Running the Program**:
   You can run the programs using the following commands:
   ```bash
   $ make run            # To run the chef program
   $ make runn           # To run the saladmaker program
   
3. **Parallel Execution**:
   
   The chef program and saladmaker programs run in **separate terminal windows** (TTYs). The chef assigns ingredients to the salad makers, and the salad makers prepare the salads concurrently.

4. **Log Files**:

   The program generates log files for each run, located in the misc folder. These logs contain detailed information about the tasks performed, the time intervals, and the actions taken by the chef and salad makers.

## Parallelism in Action
The project demonstrates parallelism using the following key mechanisms:

- **Shared Memory**: The chef and salad makers communicate using a shared memory segment, allowing them to share data such as the remaining salads and log file paths.
- **Semaphores**:
    - A semaphore array `notifySaladmakers` is used to notify the salad makers when ingredients are ready.
    - The chef waits for the salad makers to finish preparing the salads using the `notifyChef` semaphore.
- **Mutexes**:
    - `mutexForSaladsCS` ensures mutual exclusion when modifying the shared data on the number of remaining salads.
    - `writingToGLogMutex` prevents concurrent writes to the global log file.
