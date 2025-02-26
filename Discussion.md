Discussion.md

Solutions Considered

1️⃣ Naive Approach (Linear Search)

Method: Read the log file line by line and check if the date at the beginning matches the target date.

Pros: Simple to implement.

Cons: Inefficient for large files (~5GB or more) since it reads the entire file sequentially.

2️⃣ Index-Based Search

Method: Pre-process the file and create an index mapping each date to its byte offset, then directly seek to the target date.

Pros: Fast retrieval.

Cons: Requires additional storage for the index and preprocessing time.

3️⃣ Binary Search on File (Final Approach)

Method:

Perform a binary search to locate the first occurrence of the target date.

Seek to this location and extract logs sequentially until the next date appears.

Pros: Efficient in handling large files as it minimizes reads.

Cons: Slightly complex implementation but provides significant performance benefits.

Final Solution Summary

The Binary Search approach was chosen because:

It optimizes log extraction for large files, significantly reducing search time.

It does not require preprocessing like indexing methods.

It efficiently skips unnecessary log entries, making it ideal for time-sensitive applications.

Steps to Run

1️⃣ Compile the C++ Code
cd src
g++ -o extract_logs extract_logs.cpp

2️⃣ Run the Program
./extract_logs YYYY-MM-DD

3️⃣ Output Location

Extracted logs are saved in:
output/output_YYYY-MM-DD.txt