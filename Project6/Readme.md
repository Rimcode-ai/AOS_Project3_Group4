# UNIX I/O Multiplexing Project

## Introduction
This project is an exercise in making UNIX I/O system calls using C. It involves creating a multiplexed environment where the main process reads from multiple pipes, from the standard input (terminal), and writes to the file system.

## Objective
The aim is to demonstrate proficiency in handling UNIX I/O, process management, and inter-process communication using pipes in a C programming environment.

## Procedure

### Overview
- Create five pipes and spawn five child processes.
- Each child process writes to its respective pipe.
- The parent process reads from all pipes.
- Implement a timeout mechanism to terminate the processes after 30 seconds.

### Detailed Steps
1. **Pipe Creation and Child Process Spawning**:
   - Each of the five child processes is connected to a dedicated pipe.
2. **Child Processes Behavior**:
   - The first four child processes generate timestamped messages.
   - Each message is to the nearest 1000th of a second.
   - Random sleep interval of 0, 1, or 2 seconds between messages.
   - Example message: `0:00.123: Child 1 message 1`.
3. **Fifth Child Process**:
   - Repeatedly prompts for user input on the terminal.
   - Reads a line of input and writes it with a timestamp to its pipe.
   - Continuously prompts for the next message.
4. **Parent Process**:
   - Uses `select()` system call to read lines from the pipes.
   - Writes messages read from pipes to `output.txt`, each with two timestamps.
   - The output contains a mix of lines from all child processes.



## Run below commands in the src folder:

# Provide message input after running the program, as shown below
```
$ gcc -o pipe main.c
$ ./pipe
```

## Output
- **File**: `output.txt`
  - Contains lines from child processes, each with double timestamps.

### Authors
Rima Modak(W1650730), 
Gouri Lalitha Priyanka Tummalapenta(W1650617),
Ragha Srilakshmi Sumithra Mounika Yalamarty(7700012596)



