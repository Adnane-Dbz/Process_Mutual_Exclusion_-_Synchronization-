# Process_Mutual_Exclusion_-_Synchronization-
This repository contains implementations of mutual exclusion (ME) and process synchronization methods in C. It includes classic algorithms like Peterson's algorithm, Dekker's algorithm, and examples of process concurrency for entering critical sections.
Mutual Exclusion & Process Synchronization

This repository contains C implementations of classic Mutual Exclusion (ME) and Process Synchronization algorithms.
📄 Contents

    Peterson's Algorithm

    Dekker's Algorithm

    Concurrency examples for entering critical sections

Each implementation demonstrates how processes can coordinate access to shared resources and avoid race conditions.
🛠️ Technologies

    Language: C

    OS concepts: Processes, Critical Sections, Synchronization

🚀 How to Run

    Clone the repository:

git clone https://github.com/Adnane-Dbz/Process_Mutual_Exclusion_-_Synchronization-.git

Compile the C programs:

gcc filename.c -o outputfile

Run the executable:

    ./outputfile

    Replace filename.c and outputfile with the appropriate file names.

📚 About

Mutual exclusion ensures that multiple processes do not enter their critical section at the same time. This repository shows basic ways to achieve synchronization without modern libraries, using only fundamental techniques like flags and turn variables.
🧠 Algorithms Covered

    Peterson's Algorithm:
    A classic solution for two-process mutual exclusion.

    Dekker's Algorithm:
    One of the earliest known correct solutions to mutual exclusion.

    Concurrency Examples:
    Demonstrations of how improper synchronization can lead to race conditions.

📜 License

This project is open source and available under the MIT License.
