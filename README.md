# High-Performance Vaccine Monitor

A robust C++ system designed to manage and query large-scale vaccination records with high efficiency. This project focuses on the manual implementation of advanced data structures to optimize memory usage and search complexity.



---

## ## System Architecture & Data Structures

To handle thousands of records with minimal latency, the system utilizes a multi-layered data architecture:

### ### 1. Bloom Filters (Probabilistic Indexing)
* **Purpose:** Provides a lightning-fast $O(1)$ check to see if a citizen has *likely* been vaccinated before querying heavier structures.
* **Implementation:** A custom bit-array using bitwise manipulation and three distinct hash functions (**djb2**, **sdbm**, **hash_i**) to minimize false positives.

### ### 2. Skip Lists (Probabilistic Search)
* **Purpose:** Replaces standard linked lists to provide $O(log N)$ search and insertion.
* **Implementation:** Every virus maintains two Skip Lists (Vaccinated vs. Non-Vaccinated). This allows for rapid range queries and population status reports.

### ### 3. AVL Tree (Balanced Storage)
* **Purpose:** Acts as the primary "Citizen Registry" to store unique records.
* **Implementation:** A self-balancing Binary Search Tree ensures the system never degrades to $O(N)$ search time, maintaining a guaranteed $O(log N)$ depth.



---

## ## Features & Functionality

### ### Data Integrity & Error Handling
* **Strict Validation:** Validates IDs (0-9999), Age (1-120), and Date formats (dd-mm-yyyy).
* **Conflict Resolution:** Intelligently handles duplicate IDs by verifying credentials (name, country, age) and managing vaccination status transitions (e.g., upgrading a 'NO' status to 'YES' upon new vaccination).

### ### Analytical Commands
* `/vaccineStatusBloom`: Quick-check via Bloom Filter.
* `/populationStatus`: Generates real-time vaccination statistics by country.
* `/popStatusByAge`: Breaks down statistics into four age demographics (0-20, 20-40, 40-60, 60+).
* `/vaccinateNow`: Instant record update using the current system date.

---

## ## Getting Started

### ### Build
```bash
make
```

### 🎓 Academic Context
Developed as part of the Systems Programming course at the National and Kapodistrian University of Athens (UoA). Based on the UC Berkeley CS188 framework.

### Execution
```bash
./vaccineMonitor -c inputFile.txt -b bloomFilterSizeInBytes
```

### Test Data Generation
A provided Shell script (testFile.sh) can be used to generate large, valid datasets for stress testing the system.
```bash
./testFile.sh virusesFile countriesFile numLines duplicatesAllowed
```
## Performance Analysis
- Bloom Filter - $O(1)$ - Immediate membership "maybe/no" check
- Skip List - $O(log N)$ - Fast retrieval of status by Virus
- AVL Tree - $O(log N)$ - Primary Citizen ID lookup
