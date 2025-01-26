# C_Queue
Implement a simple queue module in C using TDD.

# Queue Implementation

## 1. Implementation Details

### 1.1 Advantages of Using Linked List
- **Dynamic Expansion:**  
  The queue size is not restricted by a fixed capacity during initialization (unless explicitly defined by `QUEUE_MAX_SIZE`), allowing flexibility to handle varying data sizes.
- **High Memory Utilization:**  
  Memory is allocated only when needed, avoiding waste associated with pre-allocated memory in array-based implementations.
- **Efficient Insertion and Deletion:**  
  Linked list operations do not require shifting elements, making both insertion and deletion operations have a time complexity of **O(1)**. This is particularly beneficial for handling large datasets compared to array-based queues.

### 1.2 Reasons for Setting `QUEUE_MAX_SIZE`
- **Resource Control:**  
  Limiting the queue size prevents excessive memory usage, which could lead to program crashes or unpredictable behavior.
- **Performance Balance:**  
  Restricting capacity ensures better control over system resources for specific use cases.

### 1.3 Object-Oriented Design Principles
- **OOP:**  
  This queue implementation reflects the principles of encapsulation and abstraction in object-oriented programming. Through function interfaces such as queue_construct, queue_push, and queue_pop, the internal implementation details (e.g., Node and Queue structures) are hidden, and external code cannot directly access internal members like p_front, p_rear, and i_size, ensuring data safety and control. Additionally, the interfaces abstract the queue's operations, allowing users to perform tasks like construction, destruction, enqueue, and dequeue without needing to understand the underlying linked-list implementation, significantly improving code maintainability and usability.
- **Type Restriction:**  
  The current implementation only supports elements of type int. However, by using typedef ElementType, the design provides flexibility for future extensions to support other data types, such as float or string.

---

## 2. Queue Structure Design

### Queue Structure (`Queue`)
- **`i_size`:**  
  Tracks the current number of elements in the queue, enabling quick checks for whether the queue is empty or full.
- **`i_capacity`:**  
  The maximum number of elements the queue can store, limited by `QUEUE_MAX_SIZE`.
- **`p_front`:**  
  A pointer to the front of the queue, used for dequeue operations.
- **`p_rear`:**  
  A pointer to the rear of the queue, used for enqueue operations.

### Node Structure (`Node`)
- **`t_data`:**  
  Stores the data of the node, defined as `ElementType`.
- **`p_next`:**  
  Points to the next node in the queue, maintaining the linked list structure.

---

## 3. Test-Driven Development (TDD)

### Unit Testing
- **Testing Scope:**  
  Comprehensive unit tests are implemented for all queue operations.
- **Scenarios Covered:**  
  1. **Normal Cases:** Ensure all operations behave as expected within their normal range.  
  2. **Boundary Cases:** Test edge cases such as dequeueing an empty queue, enqueueing a full queue, and handling `NULL` inputs.  
  3. **Error Cases:** Verify that functions return appropriate error codes for invalid inputs.

### Testing Framework
- **Unity Framework:**  
  The Unity testing framework is utilized for the following benefits:
  - Detailed assertions (e.g., `TEST_ASSERT`, `TEST_ASSERT_EQUAL_MESSAGE`).
  - Automated test execution.
  - Clear error reporting for quick debugging.

---

## 4. Extensibility

### Capacity Expansion
- The maximum queue capacity is controlled by `QUEUE_MAX_SIZE`, which can be adjusted for different application scenarios.
- Future implementations can introduce dynamic capacity adjustment (e.g., resizing `QUEUE_MAX_SIZE` when needed).

### Type Generalization
- Currently, `ElementType` is used to abstract the data type of nodes, simplifying future support for other types (e.g., `float`, `string`).

---

## 5. Potential Improvements

### 5.1 Interface Encapsulation
- **Problem:**  
  The current design allows users to access internal details of the `Queue` structure (e.g., `p_front`, `p_rear`).
- **Solution:**  
  Use stricter encapsulation by exposing only the `QueueOps` interface and hiding the `Queue` definition in the `.c` file.

### 5.2 Support for Multiple Data Types
- **Problem:**  
  The current implementation only supports `int` data types, limiting flexibility.
- **Solution:**  
  By replacing ElementType with void*, the implementation can support polymorphism, allowing the queue to store and process data of various types.

---

## How to Build and Run Tests

### Compilation and Testing
```bash
# Remove old test executable
rm test_queue.exe

# Compile the test and source files
gcc -o ./test_queue test/test_queue_simple.c src/queue_simple.c unity/unity.c -Iunity -Isrc

# Run the test executable
./test_queue.exe
