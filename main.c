    /**
 * ============================================================================
 * PROJECT: Employee Management System (Data Structures & Algorithms in C)
 * LOCATION: C:\CodeDirectory\SE_NonGit\DSAProject\
 * 
 * CORE DSA CONCEPTS:
 * - Linear Data Structures: Contiguous Arrays of Structs
 * - Array Operations: Insertion, In-place Updating, Element Deletion by Left Shifting
 * - Sorting Algorithm: Bubble Sort (Ascending by Employee ID)
 * - Searching Algorithms: Linear Search (O(N)) vs Binary Search (O(log N))
 * - Complexity Benchmark: Real-time Comparison of Search Comparisons
 * 
 * MODULE ARCHITECTURE:
 * - Module 1: Employee Data Entry and Update (Add, Modify, Delete using Array Shifting)
 * - Module 2: Employee Display and Salary Report (All records, Dept-wise, Total/Avg)
 * - Module 3: Linear Search Module (Search by Name or Dept on unsorted data)
 * - Module 4: Binary Search Module (Sort by ID, Binary Search, Comparison vs Linear)
 * ============================================================================
 */     

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 100
#define NAME_LEN 50
#define DEPT_LEN 30
#define DATE_LEN 15

/* Employee Data Structure */
typedef struct {
    int id;
    char name[NAME_LEN];
    char department[DEPT_LEN];
    double salary;
    char joining_date[DATE_LEN];
} Employee;

/* Global State */
static Employee employeeList[MAX_EMPLOYEES];
static int employeeCount = 0;
static bool isSortedById = false;

/* Utility Prototypes */
void clearInputBuffer(void);
void getSafeString(char *buffer, int maxLen);
int getSafeInt(void);
double getSafeDouble(void);
bool caseInsensitiveContains(const char *haystack, const char *needle);
void printTableHeader(void);
void printEmployeeRow(const Employee *emp);
void printTableFooter(void);

/* Module Prototypes */
/* Module 1: Data Entry & Update */
void addEmployee(void);
void modifyEmployee(void);
void deleteEmployee(void);

/* Module 2: Display & Salary Report */
void displayAllEmployees(void);
void displayDepartmentWise(void);
void displaySalaryReport(void);

/* Module 3: Linear Search */
void linearSearchByName(void);
void linearSearchByDepartment(void);
int linearSearchById(int targetId, int *comparisons);

/* Module 4: Binary Search & Analysis */
void sortEmployeesById(void);
int binarySearchById(int targetId, int *comparisons);
void searchEmployeeBinary(void);
void compareLinearVsBinarySearch(void);

/* Data Initialization */
void loadSampleData(void);

/* ============================================================================
 * MAIN DRIVER FUNCTION
 * ============================================================================
 */
int main(void) {
    int choice;

    /* Initialize with sample records for immediate testing */
    loadSampleData();

    do {
        printf("\n");
        printf("====================================================================\n");
        printf("            EMPLOYEE MANAGEMENT SYSTEM (DSA IN C)                   \n");
        printf("====================================================================\n");
        printf(" [ MODULE 1: DATA ENTRY & UPDATE ]\n");
        printf("   1. Add New Employee\n");
        printf("   2. Modify Existing Employee Details\n");
        printf("   3. Delete Employee (Array Shift)\n");
        printf("\n");
        printf(" [ MODULE 2: DISPLAY & REPORTS ]\n");
        printf("   4. List All Employees\n");
        printf("   5. Department-wise Employee Listing\n");
        printf("   6. Total & Average Salary Report\n");
        printf("\n");
        printf(" [ MODULE 3: LINEAR SEARCH (UNSORTED DATA) ]\n");
        printf("   7. Linear Search by Name\n");
        printf("   8. Linear Search by Department\n");
        printf("\n");
        printf(" [ MODULE 4: BINARY SEARCH & COMPARISON ]\n");
        printf("   9. Sort Employees by ID (Bubble Sort)\n");
        printf("  10. Binary Search by Employee ID\n");
        printf("  11. Compare Linear Search vs Binary Search (Benchmark)\n");
        printf("\n");
        printf(" [ UTILITIES ]\n");
        printf("  12. Reset / Reload Sample Data\n");
        printf("   0. Exit System\n");
        printf("====================================================================\n");
        printf("Enter your choice (0-12): ");

        choice = getSafeInt();

        printf("\n");
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                modifyEmployee();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4:
                displayAllEmployees();
                break;
            case 5:
                displayDepartmentWise();
                break;
            case 6:
                displaySalaryReport();
                break;
            case 7:
                linearSearchByName();
                break;
            case 8:
                linearSearchByDepartment();
                break;
            case 9:
                sortEmployeesById();
                break;
            case 10:
                searchEmployeeBinary();
                break;
            case 11:
                compareLinearVsBinarySearch();
                break;
            case 12:
                loadSampleData();
                printf("[+] Sample employee records reloaded successfully!\n");
                break;
            case 0:
                printf("[*] Thank you for using Employee Management System. Goodbye!\n");
                break;
            default:
                printf("[!] Invalid selection! Please enter a number between 0 and 12.\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

/* ============================================================================
 * MODULE 1: EMPLOYEE DATA ENTRY AND UPDATE
 * - Add employee: Inserts at the end of the array.
 * - Modify employee: Finds by ID and updates selected fields.
 * - Delete employee: Performs array deletion via left-shifting elements.
 * ============================================================================
 */

void addEmployee(void) {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("[!] Error: Employee array is full! Maximum capacity is %d.\n", MAX_EMPLOYEES);
        return;
    }

    printf("--- [MODULE 1: Add New Employee] ---\n");
    printf("Enter Employee ID: ");
    int newId = getSafeInt();

    /* Validate ID uniqueness using linear scan */
    for (int i = 0; i < employeeCount; i++) {
        if (employeeList[i].id == newId) {
            printf("[!] Error: Employee with ID %d already exists!\n", newId);
            return;
        }
    }

    Employee newEmp;
    newEmp.id = newId;

    printf("Enter Full Name: ");
    getSafeString(newEmp.name, NAME_LEN);

    printf("Enter Department (e.g. Engineering, Sales, HR, Finance): ");
    getSafeString(newEmp.department, DEPT_LEN);

    printf("Enter Salary (INR / USD): ");
    newEmp.salary = getSafeDouble();

    printf("Enter Joining Date (DD-MM-YYYY): ");
    getSafeString(newEmp.joining_date, DATE_LEN);

    /* Insert into array at index employeeCount */
    employeeList[employeeCount++] = newEmp;
    isSortedById = false; /* Adding at end may disrupt sorted order */

    printf("[+] Employee successfully added at array index %d! Total count: %d\n", 
           employeeCount - 1, employeeCount);
}

void modifyEmployee(void) {
    if (employeeCount == 0) {
        printf("[!] Employee list is currently empty.\n");
        return;
    }

    printf("--- [MODULE 1: Modify Employee Details] ---\n");
    printf("Enter Employee ID to modify: ");
    int targetId = getSafeInt();

    int foundIndex = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeList[i].id == targetId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("[!] Employee with ID %d not found in the records.\n", targetId);
        return;
    }

    printf("\nCurrent details of Employee (ID %d):\n", targetId);
    printTableHeader();
    printEmployeeRow(&employeeList[foundIndex]);
    printTableFooter();

    printf("\nChoose field to update:\n");
    printf("1. Name\n");
    printf("2. Department\n");
    printf("3. Salary\n");
    printf("4. Joining Date\n");
    printf("5. Update All Fields\n");
    printf("0. Cancel\n");
    printf("Select option (0-5): ");

    int opt = getSafeInt();
    switch (opt) {
        case 1:
            printf("Enter New Name: ");
            getSafeString(employeeList[foundIndex].name, NAME_LEN);
            printf("[+] Name updated successfully.\n");
            break;
        case 2:
            printf("Enter New Department: ");
            getSafeString(employeeList[foundIndex].department, DEPT_LEN);
            printf("[+] Department updated successfully.\n");
            break;
        case 3:
            printf("Enter New Salary: ");
            employeeList[foundIndex].salary = getSafeDouble();
            printf("[+] Salary updated successfully.\n");
            break;
        case 4:
            printf("Enter New Joining Date: ");
            getSafeString(employeeList[foundIndex].joining_date, DATE_LEN);
            printf("[+] Joining date updated successfully.\n");
            break;
        case 5:
            printf("Enter New Name: ");
            getSafeString(employeeList[foundIndex].name, NAME_LEN);
            printf("Enter New Department: ");
            getSafeString(employeeList[foundIndex].department, DEPT_LEN);
            printf("Enter New Salary: ");
            employeeList[foundIndex].salary = getSafeDouble();
            printf("Enter New Joining Date: ");
            getSafeString(employeeList[foundIndex].joining_date, DATE_LEN);
            printf("[+] All fields updated successfully.\n");
            break;
        case 0:
            printf("[*] Modification cancelled.\n");
            break;
        default:
            printf("[!] Invalid option. No changes made.\n");
            break;
    }
}

void deleteEmployee(void) {
    if (employeeCount == 0) {
        printf("[!] Employee list is currently empty.\n");
        return;
    }

    printf("--- [MODULE 1: Delete Employee (Array Shift)] ---\n");
    printf("Enter Employee ID to delete: ");
    int targetId = getSafeInt();

    int foundIndex = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeList[i].id == targetId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("[!] Employee with ID %d not found.\n", targetId);
        return;
    }

    printf("[*] Found Employee: %s (ID: %d, Dept: %s)\n", 
           employeeList[foundIndex].name, employeeList[foundIndex].id, employeeList[foundIndex].department);
    printf("Are you sure you want to delete this record? (1 = Yes, 0 = No): ");
    int confirm = getSafeInt();

    if (confirm != 1) {
        printf("[*] Deletion cancelled.\n");
        return;
    }

    /*
     * DSA Array Deletion Concept:
     * Shift all elements to the left by 1 position starting from foundIndex.
     * array[i] = array[i + 1]
     */
    for (int i = foundIndex; i < employeeCount - 1; i++) {
        employeeList[i] = employeeList[i + 1];
    }
    employeeCount--;

    printf("[+] Employee with ID %d deleted. Shifted %d elements left. New count: %d.\n",
           targetId, employeeCount - foundIndex, employeeCount);
}

/* ============================================================================
 * MODULE 2: EMPLOYEE DISPLAY AND SALARY REPORT
 * - List all employees in tabular format.
 * - Department-wise filtered listing.
 * - Total, Average, Maximum, and Minimum salary calculation.
 * ============================================================================
 */

void displayAllEmployees(void) {
    if (employeeCount == 0) {
        printf("[!] No employees to display. List is empty.\n");
        return;
    }

    printf("\n--- [MODULE 2: Master Employee Directory] (Total: %d) ---\n", employeeCount);
    printTableHeader();
    for (int i = 0; i < employeeCount; i++) {
        printEmployeeRow(&employeeList[i]);
    }
    printTableFooter();
}

void displayDepartmentWise(void) {
    if (employeeCount == 0) {
        printf("[!] No employees found.\n");
        return;
    }

    printf("--- [MODULE 2: Department-wise Employee Listing] ---\n");
    printf("Enter Department to filter (or type 'all' for grouped overview): ");
    char deptQuery[DEPT_LEN];
    getSafeString(deptQuery, DEPT_LEN);

    int matchCount = 0;
    double deptTotalSalary = 0.0;

    printTableHeader();
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(deptQuery, "all") == 0 || strcasecmp(employeeList[i].department, deptQuery) == 0) {
            printEmployeeRow(&employeeList[i]);
            deptTotalSalary += employeeList[i].salary;
            matchCount++;
        }
    }
    printTableFooter();

    if (matchCount == 0) {
        printf("[!] No employees found in department '%s'.\n", deptQuery);
    } else {
        printf("Matches found: %d | Total Salary: $%.2f | Avg Salary: $%.2f\n",
               matchCount, deptTotalSalary, deptTotalSalary / matchCount);
    }
}

void displaySalaryReport(void) {
    if (employeeCount == 0) {
        printf("[!] No employees found to generate salary report.\n");
        return;
    }

    double totalSalary = 0.0;
    double minSalary = employeeList[0].salary;
    double maxSalary = employeeList[0].salary;
    int minIndex = 0;
    int maxIndex = 0;

    for (int i = 0; i < employeeCount; i++) {
        double currentSalary = employeeList[i].salary;
        totalSalary += currentSalary;

        if (currentSalary < minSalary) {
            minSalary = currentSalary;
            minIndex = i;
        }
        if (currentSalary > maxSalary) {
            maxSalary = currentSalary;
            maxIndex = i;
        }
    }

    double averageSalary = totalSalary / employeeCount;

    printf("\n====================================================================\n");
    printf("             EXECUTIVE SALARY ANALYTICS & REPORT                   \n");
    printf("====================================================================\n");
    printf(" Total Headcount          : %d\n", employeeCount);
    printf(" Total Monthly Payroll    : $%.2f\n", totalSalary);
    printf(" Average Employee Salary  : $%.2f\n", averageSalary);
    printf(" Highest Paid Employee    : %s (ID: %d) -> $%.2f (%s)\n",
           employeeList[maxIndex].name, employeeList[maxIndex].id, 
           maxSalary, employeeList[maxIndex].department);
    printf(" Lowest Paid Employee     : %s (ID: %d) -> $%.2f (%s)\n",
           employeeList[minIndex].name, employeeList[minIndex].id, 
           minSalary, employeeList[minIndex].department);
    printf("====================================================================\n");
}

/* ============================================================================
 * MODULE 3: LINEAR SEARCH MODULE
 * - Searches unsorted data element by element.
 * - Time Complexity: O(N) Worst Case, O(1) Best Case.
 * - Tracks and displays exact comparison counts.
 * ============================================================================
 */

void linearSearchByName(void) {
    if (employeeCount == 0) {
        printf("[!] Employee list is empty.\n");
        return;
    }

    printf("--- [MODULE 3: Linear Search by Name (Unsorted Data)] ---\n");
    printf("Enter Name (or partial name): ");
    char query[NAME_LEN];
    getSafeString(query, NAME_LEN);

    int comparisons = 0;
    int matches = 0;

    printTableHeader();
    for (int i = 0; i < employeeCount; i++) {
        comparisons++;
        if (caseInsensitiveContains(employeeList[i].name, query)) {
            printEmployeeRow(&employeeList[i]);
            matches++;
        }
    }
    printTableFooter();

    printf("\n[DSA Metric] Linear Search completed in %d comparisons across %d elements.\n",
           comparisons, employeeCount);
    printf("[Result] Total matches found: %d\n", matches);
}

void linearSearchByDepartment(void) {
    if (employeeCount == 0) {
        printf("[!] Employee list is empty.\n");
        return;
    }

    printf("--- [MODULE 3: Linear Search by Department (Unsorted Data)] ---\n");
    printf("Enter Department name: ");
    char query[DEPT_LEN];
    getSafeString(query, DEPT_LEN);

    int comparisons = 0;
    int matches = 0;

    printTableHeader();
    for (int i = 0; i < employeeCount; i++) {
        comparisons++;
        if (caseInsensitiveContains(employeeList[i].department, query)) {
            printEmployeeRow(&employeeList[i]);
            matches++;
        }
    }
    printTableFooter();

    printf("\n[DSA Metric] Linear Search completed in %d comparisons across %d elements.\n",
           comparisons, employeeCount);
    printf("[Result] Total matches found: %d\n", matches);
}

/* Internal helper: linear search by ID returning index and comparison count */
int linearSearchById(int targetId, int *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < employeeCount; i++) {
        (*comparisons)++;
        if (employeeList[i].id == targetId) {
            return i;
        }
    }
    return -1;
}

/* ============================================================================
 * MODULE 4: BINARY SEARCH MODULE & COMPARISON
 * - Sort employees by ID using Bubble Sort.
 * - Perform fast Binary Search on sorted ID: O(log N).
 * - Side-by-side comparison of Linear vs Binary Search comparisons.
 * ============================================================================
 */

void sortEmployeesById(void) {
    if (employeeCount <= 1) {
        printf("[*] %d records present. Already sorted.\n", employeeCount);
        isSortedById = true;
        return;
    }

    printf("--- [MODULE 4: Sorting Employees by ID (Bubble Sort)] ---\n");
    int comparisons = 0;
    int swaps = 0;

    for (int i = 0; i < employeeCount - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < employeeCount - i - 1; j++) {
            comparisons++;
            if (employeeList[j].id > employeeList[j + 1].id) {
                /* Swap records */
                Employee temp = employeeList[j];
                employeeList[j] = employeeList[j + 1];
                employeeList[j + 1] = temp;
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break; /* Optimized early exit */
    }

    isSortedById = true;
    printf("[+] Array sorted successfully in ascending order by Employee ID!\n");
    printf("    Comparisons executed : %d\n", comparisons);
    printf("    Swaps executed       : %d\n", swaps);
    printf("    Array state          : Sorted (Binary Search ready)\n");

    displayAllEmployees();
}

/* Binary Search on sorted array */
int binarySearchById(int targetId, int *comparisons) {
    *comparisons = 0;
    int low = 0;
    int high = employeeCount - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparisons)++;

        if (employeeList[mid].id == targetId) {
            return mid;
        } else if (employeeList[mid].id < targetId) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

void searchEmployeeBinary(void) {
    if (employeeCount == 0) {
        printf("[!] Employee list is empty.\n");
        return;
    }

    /* Binary search requires array sorted by ID */
    if (!isSortedById) {
        printf("[!] Notice: Array is not currently sorted by ID.\n");
        printf("[*] Automatically sorting by ID first to enable Binary Search...\n");
        sortEmployeesById();
    }

    printf("\n--- [MODULE 4: Binary Search by Employee ID] ---\n");
    printf("Enter Employee ID to search: ");
    int targetId = getSafeInt();

    int comparisons = 0;
    int foundIndex = binarySearchById(targetId, &comparisons);

    if (foundIndex != -1) {
        printf("\n[+] MATCH FOUND at array index %d!\n", foundIndex);
        printTableHeader();
        printEmployeeRow(&employeeList[foundIndex]);
        printTableFooter();
        printf("[DSA Metric] Binary Search found ID %d in only %d comparison(s)!\n", 
               targetId, comparisons);
    } else {
        printf("\n[-] Employee with ID %d not found in records.\n", targetId);
        printf("[DSA Metric] Binary Search checked %d comparison(s) before concluding not found.\n", 
               comparisons);
    }
}

void compareLinearVsBinarySearch(void) {
    if (employeeCount == 0) {
        printf("[!] Employee list is empty.\n");
        return;
    }

    printf("--- [MODULE 4: Benchmark: Linear Search vs Binary Search] ---\n");
    printf("Enter Employee ID to benchmark: ");
    int targetId = getSafeInt();

    /* 1. Run Linear Search */
    int linearComparisons = 0;
    int linearResult = linearSearchById(targetId, &linearComparisons);

    /* Ensure array is sorted for binary search */
    if (!isSortedById) {
        printf("[*] Note: Sorting array by ID to prepare for Binary Search...\n");
        sortEmployeesById();
    }

    /* 2. Run Binary Search */
    int binaryComparisons = 0;
    int binaryResult = binarySearchById(targetId, &binaryComparisons);

    printf("\n====================================================================\n");
    printf("             DSA SEARCH ALGORITHM PERFORMANCE COMPARISON            \n");
    printf("====================================================================\n");
    printf(" Target ID Searched        : %d\n", targetId);
    printf(" Total Records in Array (N): %d\n", employeeCount);
    printf(" Record Status             : %s\n", 
           (linearResult != -1 && binaryResult != -1) ? "FOUND IN BOTH" : 
           (linearResult == -1 && binaryResult == -1) ? "NOT FOUND IN BOTH" : "MISMATCH");
    printf("--------------------------------------------------------------------\n");
    printf(" Metric                     Linear Search       Binary Search       \n");
    printf("--------------------------------------------------------------------\n");
    printf(" Actual Comparisons Made    %-19d %-19d\n", linearComparisons, binaryComparisons);
    printf(" Best Case Complexity       O(1)                O(1)                \n");
    printf(" Average Case Complexity    O(N/2)              O(log2 N)           \n");
    printf(" Worst Case Complexity      O(N)                O(log2 N)           \n");
    printf(" Prerequisite               Unsorted / Any      Must Be Sorted by ID\n");
    printf("--------------------------------------------------------------------\n");

    if (linearComparisons > binaryComparisons) {
        int saved = linearComparisons - binaryComparisons;
        double reduction = ((double)saved / linearComparisons) * 100.0;
        printf("[Summary] Binary Search was %.1f%% faster (saved %d comparisons)!\n",
               reduction, saved);
    } else if (linearComparisons == binaryComparisons) {
        printf("[Summary] Both algorithms required the same number of comparisons (%d).\n", 
               linearComparisons);
    } else {
        printf("[Summary] Linear Search reached the element earlier in this specific scenario.\n");
    }
    printf("====================================================================\n");
}

/* ============================================================================
 * SAMPLE DATA SEEDING
 * ============================================================================
 */
void loadSampleData(void) {
    employeeCount = 0;

    Employee samples[] = {
        {105, "Ananya Sharma",   "Engineering", 85000.0, "15-06-2022"},
        {101, "Rohit Verma",     "Sales",       62000.0, "10-01-2021"},
        {108, "Pooja Hegde",     "HR",          58000.0, "01-08-2023"},
        {102, "Vikram Malhotra", "Finance",     92000.0, "12-11-2020"},
        {104, "Sneha Patel",     "Engineering", 88000.0, "20-03-2022"},
        {107, "Karan Johar",     "Marketing",   67000.0, "05-09-2023"}
    };

    int numSamples = sizeof(samples) / sizeof(samples[0]);
    for (int i = 0; i < numSamples; i++) {
        employeeList[i] = samples[i];
    }
    employeeCount = numSamples;
    isSortedById = false; /* Intentionally unsorted to demonstrate sorting & unsorted search */
}

/* ============================================================================
 * TABLE FORMATTING UTILITIES
 * ============================================================================
 */
void printTableHeader(void) {
    printf("+-------+----------------------+--------------------+-------------+--------------+\n");
    printf("| %-5s | %-20s | %-18s | %-11s | %-12s |\n", 
           "ID", "Name", "Department", "Salary", "Join Date");
    printf("+-------+----------------------+--------------------+-------------+--------------+\n");
}

void printEmployeeRow(const Employee *emp) {
    printf("| %-5d | %-20s | %-18s | $%-10.2f | %-12s |\n",
           emp->id, emp->name, emp->department, emp->salary, emp->joining_date);
}

void printTableFooter(void) {
    printf("+-------+----------------------+--------------------+-------------+--------------+\n");
}

/* ============================================================================
 * INPUT SANITIZATION & SAFE READING UTILITIES
 * ============================================================================
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void getSafeString(char *buffer, int maxLen) {
    if (fgets(buffer, maxLen, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            clearInputBuffer();
        }
    } else {
        buffer[0] = '\0';
    }
}

int getSafeInt(void) {
    int val;
    while (scanf("%d", &val) != 1) {
        printf("[!] Invalid input. Please enter a valid number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return val;
}

double getSafeDouble(void) {
    double val;
    while (scanf("%lf", &val) != 1) {
        printf("[!] Invalid input. Please enter a valid decimal number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return val;
}

bool caseInsensitiveContains(const char *haystack, const char *needle) {
    if (!haystack || !needle) return false;
    if (strlen(needle) == 0) return true;

    char h[256], n[256];
    size_t hlen = strlen(haystack);
    size_t nlen = strlen(needle);

    if (hlen >= sizeof(h) || nlen >= sizeof(n)) return false;

    for (size_t i = 0; i <= hlen; i++) h[i] = (char)tolower((unsigned char)haystack[i]);
    for (size_t i = 0; i <= nlen; i++) n[i] = (char)tolower((unsigned char)needle[i]);

    return (strstr(h, n) != NULL);
}
