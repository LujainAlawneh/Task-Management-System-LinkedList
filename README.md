**Task Management System (Linked List, Stack & Queue)**

This project is a task management system written in C.
It was done for the course COMP2421 (Data Structures).

Tasks are stored in a linked list.
A stack is used to undo performed tasks, and a queue is used to keep track of performed tasks.

The program allows the user to:
- Load tasks from a file
- Add a new task
- Delete a task by ID
- Search for a task by ID or name
- Perform a task (remove it from the list)
- Undo the last performed task
- View performed and unperformed tasks
- Generate a summary report saved in Report.txt

**Input file:**
The input file must be named `tasks.txt`.
Each task is written in this format:
`TaskID#TaskName#Date#Duration`

Example:
`10#meeting#22/3/2025#1.5`

**How to run:**
Compile the program using:
`gcc P1_1230127_LujainAlawneh_sec4.c -o task_manager`
Then run:
`./task_manager`

**Author:**
Lujain Alawneh  
COMP2421 – Birzeit University
