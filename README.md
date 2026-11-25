# Employee Management System (DSA Mini-Project in C)

### Project Overview (Project #2 from Specification)
A pure, terminal-based **Employee Management System** implemented in **C language** demonstrating foundational **Data Structures and Algorithms (DSA)** concepts:
- **Linear Data Structures:** Contiguous array of structs (`Employee`).
- **Array Mutation:** Insertion at tail, in-place field updates, and deletion via left element shifting (`array[i] = array[i + 1]`).
- **Sorting Algorithms:** Bubble Sort algorithm to order records in ascending order by Employee ID.
- **Searching Algorithms:** 
  - **Linear Search:** Sequential scanning through unsorted datasets by name or department ($O(N)$).
  - **Binary Search:** Divide-and-conquer search on sorted employee IDs ($O(\log N)$).
- **Algorithmic Benchmarking:** Real-time side-by-side comparison tracking exact comparisons between Linear and Binary search.

---

### 4 Module Division & Specifications

| Module | Module Name | DSA Concepts & Implementation Details |
| :--- | :--- | :--- |
| **Module 1** | **Employee Data Entry and Update** | **Array Operations & Validation:**<br>• Add new employee with uniqueness validation for ID.<br>• Modify individual fields (Name, Dept, Salary, Joining Date) or all fields.<br>• Delete employee by searching index and shifting subsequent array elements left by 1 position. |
| **Module 2** | **Employee Display and Salary Report** | **Array Traversal & Aggregations:**<br>• Format and display all active employee records in structured tables.<br>• Filter records by department name.<br>• Calculate total payroll, average salary, highest paid employee, and lowest paid employee. |
| **Module 3** | **Linear Search Module** | **Sequential Search on Unsorted Data:**<br>• Case-insensitive substring search across employee names and departments.<br>• Operates without requiring prior sorting ($O(N)$ worst-case).<br>• Displays matched records alongside the exact number of comparisons performed. |
| **Module 4** | **Binary Search Module** | **Divide-and-Conquer Search & Benchmark:**<br>• Sort employee records by ID in ascending order using Bubble Sort.<br>• Fast Binary Search on sorted IDs with comparison counters ($O(\log N)$).<br>• Interactive benchmark comparing Linear Search vs Binary Search comparisons on identical targets. |

---

### Algorithmic Complexity Reference

| Operation / Algorithm | Best Case | Average Case | Worst Case | Space Complexity |
| :--- | :---: | :---: | :---: | :---: |
| **Array Insertion** | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| **Array Deletion (Shift)** | $O(1)$ | $O(N)$ | $O(N)$ | $O(1)$ |
| **Linear Search** | $O(1)$ | $O(N/2)$ | $O(N)$ | $O(1)$ |
| **Bubble Sort** | $O(N)$ *(optimized)* | $O(N^2)$ | $O(N^2)$ | $O(1)$ |
| **Binary Search** | $O(1)$ | $O(\log_2 N)$ | $O(\log_2 N)$ | $O(1)$ |

---

### Files in this Directory
- [main.c](main.c) — Complete, modular, documented C source code.
- [run.bat](run.bat) — One-click launcher script.
- [README.md](README.md) — Documentation and DSA analysis.

---

### How to Run

#### Option 1: One-Click Launcher (Windows)
Double-click `run.bat`. It compiles `main.c` automatically if the exe is missing (needs GCC/MinGW).

#### Option 2: Compile and Run Manually
```bash
gcc -std=c99 -Wall -Wextra main.c -o EmployeeManagement.exe
./EmployeeManagement.exe
```
