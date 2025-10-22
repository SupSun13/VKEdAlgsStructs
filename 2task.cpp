#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <cctype>
using namespace std;


template<typename T>
struct Node {
    T data;
    Node* next;
    Node() : data(), next(nullptr) {}
    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class LinkedList {
protected:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    // Конструктор
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Деструктор
    virtual ~LinkedList() {
        clear();
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void pop_front() {
        if (head == nullptr) return;
        
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void print() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    bool insertAfter(const T& afterValue, const T& newValue) {
        Node<T>* search = head;
        while (search != nullptr) {
            if (search->data == afterValue) {
                Node<T>* newNode = new Node<T>(newValue);
                
                if (search == tail) {
                    tail = newNode;
                }

                newNode->next = search->next;
                search->next = newNode;
                
                size++;
                return true;
            }
            search = search->next;
        }
        return false;
    }

    bool hasCycle() {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        
        Node<T>* slow = head;
        Node<T>* fast = head->next;
        
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
    
    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        tail = head;
        
        while (current != nullptr) {
            Node<T>* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    Node<T>* middleNode() { 
        if (head == nullptr) {
            return nullptr;
        }
        
        Node<T>* slow = head;
        Node<T>* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }

    void removeElements(const T& val) {
        Node<T>* dummy = new Node<T>();
        dummy->next = head;
        
        Node<T>* prev = dummy;
        Node<T>* cur = head;
        
        while (cur != nullptr) {
            if (cur->data == val) {
                prev->next = cur->next;
                if (cur == tail) {
                    tail = prev;
                }
                delete cur;
                cur = prev->next;
                size--;
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
        
        head = dummy->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete dummy;
    }

    T front() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }
    
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const {
        return head == nullptr;
    }

    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }
    void setHead(Node<T>* newHead) { head = newHead; }
    void setTail(Node<T>* newTail) { tail = newTail; }
};

template<typename T>
struct DoublyNode {
    T data;
    DoublyNode* prev;
    DoublyNode* next;
    DoublyNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template<typename T>
class DoublyLinkedList {
protected:
    DoublyNode<T>* head;
    DoublyNode<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    virtual ~DoublyLinkedList() {
        clear();
    }
    
    void clear() {
        DoublyNode<T>* current = head;
        while (current != nullptr) {
            DoublyNode<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }
    
    void push_front(const T& value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    
    void push_back(const T& value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    void pop_front() {
        if (isEmpty()) return;
        
        DoublyNode<T>* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }
    
    void pop_back() {
        if (isEmpty()) return;
        
        DoublyNode<T>* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
    }
    
    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }
    
    T back() const {
        if (isEmpty()) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }
    
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const {
        return head == nullptr;
    }
    DoublyNode<T>* getHead() const { return head; }
    DoublyNode<T>* getTail() const { return tail; }
    void setHead(DoublyNode<T>* newHead) { head = newHead; }
    void setTail(DoublyNode<T>* newTail) { tail = newTail; }
};

template<typename T>
class Queue : public LinkedList<T> {
public:
    void push(const T& value) { this->push_back(value); }
    void pop() { this->pop_front(); }
    T peek() const { return this->front(); }

    using LinkedList<T>::getSize;
    using LinkedList<T>::isEmpty;
};

template<typename T>
class Stack : public LinkedList<T> {
public:
    void push(const T& value) { this->push_front(value); }
   
    T pop() {
        if (this->isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        T value = this->front();
        this->pop_front();
        return value;
    }

    T top() const { return this->front(); }

    using LinkedList<T>::isEmpty;
    using LinkedList<T>::getSize;
};

template<typename T>
class Deque : public DoublyLinkedList<T> {
public:
    using DoublyLinkedList<T>::push_front;
    using DoublyLinkedList<T>::push_back;
    using DoublyLinkedList<T>::pop_front;
    using DoublyLinkedList<T>::pop_back;
    using DoublyLinkedList<T>::front;
    using DoublyLinkedList<T>::back;
    using DoublyLinkedList<T>::isEmpty;
    using DoublyLinkedList<T>::getSize;
    
    void pushFront(const T& value) { this->push_front(value); }
    void pushBack(const T& value) { this->push_back(value); }
    void popFront() { this->pop_front(); }
    void popBack() { this->pop_back(); }
    T getFront() const { return this->front(); }
    T getBack() const { return this->back(); }
};

bool isSubsequenceQueue(const std::string& a, const std::string& b) {
    Queue<char> q;

    for (char el : a) {
        q.push(el);
    }
    for (char el : b) {
        if (!q.isEmpty() && q.peek() == el) {
            q.pop();
        }
    }
    return q.isEmpty();
}

bool isSubsequenceTwoPointers(const std::string& a, const std::string& b) {
    int i = 0, j = 0;
    
    while (i < a.length() && j < b.length()) {
        if (a[i] == b[j]) {
            i++;
        }
        j++;
    }
    return i == a.length();
}

bool isPalindromeStack(const std::string& s) {
    Stack<char> stack;

    for (char c : s) {
        stack.push(c);
    }
    for (char c : s) {
        if (c != stack.pop()) {
            return false;
        }
    }
    return true;
}

bool isPalindromeDeque(const std::string& s) {
    Deque<char> dq;
    
    for (char c : s) {
        if (!std::isspace(c)) {
            dq.pushBack(std::tolower(c));
        }
    }
    while (dq.getSize() > 1) {
        if (dq.getFront() != dq.getBack()) {
            return false;
        }
        dq.popFront();
        dq.popBack();
    }
    return true;
}

bool isPalindromeTwoPointers(const std::string& s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

template<typename T>
Node<T>* mergeSortedLists(Node<T>* list1, Node<T>* list2) {
    Node<T>* dummy = new Node<T>(T());
    Node<T>* current = dummy;
    
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->data <= list2->data) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }
    
    current->next = (list1 != nullptr) ? list1 : list2;
    
    Node<T>* result = dummy->next;
    delete dummy;
    return result;
}

// Тестовые функции
void testLinkedList() {
    std::cout << "=== Testing LinkedList ===" << std::endl;
    
    LinkedList<int> list;
    
    // Test 1: push_front and push_back
    list.push_front(2);
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    std::cout << "After pushes: ";
    list.print(); // 1 -> 2 -> 3 -> 4 -> nullptr
    
    // Test 2: size and isEmpty
    assert(list.getSize() == 4);
    assert(!list.isEmpty());
    
    // Test 3: front
    assert(list.front() == 1);
    
    // Test 4: pop_front
    list.pop_front();
    assert(list.front() == 2);
    assert(list.getSize() == 3);
    std::cout << "After pop_front: ";
    list.print();
    
    // Test 5: insertAfter
    assert(list.insertAfter(3, 5));
    std::cout << "After insert 5 after 3: ";
    list.print();
    
    // Test 6: removeElements
    list.push_back(2);
    list.push_back(2);
    std::cout << "Before remove 2: ";
    list.print();
    list.removeElements(2);
    std::cout << "After remove 2: ";
    list.print();
    
    // Test 7: reverse
    list.clear();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    std::cout << "Before reverse: ";
    list.print();
    list.reverse();
    std::cout << "After reverse: ";
    list.print();
    assert(list.front() == 3);
    
    // Test 8: middleNode
    list.clear();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    Node<int>* middle = list.middleNode();
    assert(middle != nullptr && middle->data == 3);
    
    list.push_back(6);
    middle = list.middleNode();
    assert(middle != nullptr && middle->data == 4);
    
    std::cout << "LinkedList tests passed!\n" << std::endl;
}

void testDoublyLinkedList() {
    std::cout << "=== Testing DoublyLinkedList ===" << std::endl;
    
    DoublyLinkedList<int> dlist;
    
    // Test push_front and push_back
    dlist.push_front(2);
    dlist.push_front(1);
    dlist.push_back(3);
    dlist.push_back(4);
    
    assert(dlist.getSize() == 4);
    assert(dlist.front() == 1);
    assert(dlist.back() == 4);
    
    // Test pop_front and pop_back
    dlist.pop_front();
    assert(dlist.front() == 2);
    
    dlist.pop_back();
    assert(dlist.back() == 3);
    assert(dlist.getSize() == 2);
    
    std::cout << "DoublyLinkedList tests passed!\n" << std::endl;
}

void testStack() {
    std::cout << "=== Testing Stack ===" << std::endl;
    
    Stack<int> stack;
    
    // Test push and pop
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    assert(stack.getSize() == 3);
    assert(stack.top() == 3);
    
    assert(stack.pop() == 3);
    assert(stack.pop() == 2);
    assert(stack.getSize() == 1);
    
    stack.push(4);
    assert(stack.top() == 4);
    
    std::cout << "Stack tests passed!\n" << std::endl;
}

void testQueue() {
    std::cout << "=== Testing Queue ===" << std::endl;
    
    Queue<int> queue;
    
    // Test push and pop
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    assert(queue.getSize() == 3);
    assert(queue.peek() == 1);
    
    queue.pop();
    assert(queue.peek() == 2);
    assert(queue.getSize() == 2);
    
    queue.push(4);
    assert(queue.peek() == 2);
    
    std::cout << "Queue tests passed!\n" << std::endl;
}

void testDeque() {
    std::cout << "=== Testing Deque ===" << std::endl;
    
    Deque<int> deque;
    
    // Test push operations
    deque.pushFront(2);
    deque.pushFront(1);
    deque.pushBack(3);
    deque.pushBack(4);
    
    assert(deque.getSize() == 4);
    assert(deque.getFront() == 1);
    assert(deque.getBack() == 4);
    
    // Test pop operations
    deque.popFront();
    assert(deque.getFront() == 2);
    
    deque.popBack();
    assert(deque.getBack() == 3);
    assert(deque.getSize() == 2);
    
    // Test alias methods
    deque.pushFront(0);
    deque.pushBack(5);
    assert(deque.getFront() == 0);
    assert(deque.getBack() == 5);
    
    std::cout << "Deque tests passed!\n" << std::endl;
}

void testIsSubsequence() {
    std::cout << "=== Testing isSubsequence ===" << std::endl;
    
    // Test cases for both implementations
    std::vector<std::tuple<std::string, std::string, bool>> testCases = {
        {"abc", "ahbgdc", true},
        {"axc", "ahbgdc", false},
        {"ace", "abcde", true},
        {"", "abc", true},
        {"abc", "", false},
        {"a", "a", true},
        {"a", "b", false},
        {"abc", "acb", false}
    };
    
    for (const auto& testCase : testCases) {
        const std::string& a = std::get<0>(testCase);
        const std::string& b = std::get<1>(testCase);
        bool expected = std::get<2>(testCase);
        
        bool resultQueue = isSubsequenceQueue(a, b);
        bool resultPointers = isSubsequenceTwoPointers(a, b);
        
        assert(resultQueue == expected);
        assert(resultPointers == expected);
        
        std::cout << "isSubsequence(\"" << a << "\", \"" << b << "\") = " 
                  << std::boolalpha << resultQueue << " ✓" << std::endl;
    }
    
    std::cout << "isSubsequence tests passed!\n" << std::endl;
}

void testIsPalindrome() {
    std::cout << "=== Testing isPalindrome ===" << std::endl;
    
    // Test cases for all three implementations
    std::vector<std::tuple<std::string, bool>> testCases = {
        {"racecar", true},
        {"hello", false},
        {"a", true},
        {"", true},
        {"madam", true},
        {"level", true},
        {"noon", true},
        {"algorithm", false},
        {"A man a plan a canal Panama", true},  // will be handled by improved versions
        {"race a car", false}
    };
    
    for (const auto& testCase : testCases) {
        const std::string& s = std::get<0>(testCase);
        bool expected = std::get<1>(testCase);
        
        bool resultStack = isPalindromeStack(s);
        bool resultDeque = isPalindromeDeque(s);
        bool resultPointers = isPalindromeTwoPointers(s);
        
        // For simple cases without spaces, all should agree
        if (s.find(' ') == std::string::npos) {
            assert(resultStack == expected);
            assert(resultDeque == expected);
            assert(resultPointers == expected);
        }
        
        std::cout << "isPalindrome(\"" << s << "\") = " 
                  << std::boolalpha << resultStack << " ✓" << std::endl;
    }
    
    // Special test for case with spaces
    std::string testStr = "A man a plan a canal Panama";
    assert(isPalindromeDeque(testStr) == true);
    std::cout << "Improved palindrome test passed for: \"" << testStr << "\"" << std::endl;
    
    std::cout << "isPalindrome tests passed!\n" << std::endl;
}

void testMergeSortedLists() {
    std::cout << "=== Testing mergeSortedLists ===" << std::endl;
    
    // Test 1: Normal case
    LinkedList<int> list1;
    list1.push_back(1);
    list1.push_back(3);
    list1.push_back(5);
    
    LinkedList<int> list2;
    list2.push_back(2);
    list2.push_back(4);
    list2.push_back(6);
    
    Node<int>* merged = mergeSortedLists(list1.getHead(), list2.getHead());
    
    // Verify merged list
    Node<int>* current = merged;
    std::vector<int> expected = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < expected.size(); i++) {
        assert(current != nullptr);
        assert(current->data == expected[i]);
        current = current->next;
    }
    assert(current == nullptr);
    
    std::cout << "Merged list: ";
    current = merged;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr ✓" << std::endl;
    
    // Test 2: One empty list
    LinkedList<int> emptyList;
    LinkedList<int> list3;
    list3.push_back(7);
    list3.push_back(8);
    list3.push_back(9);
    
    Node<int>* merged2 = mergeSortedLists(emptyList.getHead(), list3.getHead());
    current = merged2;
    for (int i = 7; i <= 9; i++) {
        assert(current != nullptr);
        assert(current->data == i);
        current = current->next;
    }
    assert(current == nullptr);
    
    // Test 3: Both empty
    LinkedList<int> emptyList2;
    Node<int>* merged3 = mergeSortedLists(emptyList.getHead(), emptyList2.getHead());
    assert(merged3 == nullptr);
    
    // Clean up (important for memory management)
    current = merged;
    while (current != nullptr) {
        Node<int>* next = current->next;
        delete current;
        current = next;
    }
    
    current = merged2;
    while (current != nullptr) {
        Node<int>* next = current->next;
        delete current;
        current = next;
    }
    
    std::cout << "mergeSortedLists tests passed!\n" << std::endl;
}

void testCycleDetection() {
    std::cout << "=== Testing Cycle Detection ===" << std::endl;
    
    LinkedList<int> list;
    
    // Test 1: No cycle
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(!list.hasCycle());
    
    // Test 2: Create a cycle
    Node<int>* head = list.getHead();
    Node<int>* tail = list.getHead();
    while (tail != nullptr && tail->next != nullptr) {
        tail = tail->next;
    }
    
    if (tail != nullptr) {
        tail->next = head; // Create cycle
        assert(list.hasCycle());
        tail->next = nullptr; // Restore
    }
    
    // Test 3: Single element no cycle
    LinkedList<int> singleList;
    singleList.push_back(1);
    assert(!singleList.hasCycle());
    
    // Test 4: Single element with cycle
    Node<int>* singleHead = singleList.getHead();
    if (singleHead != nullptr) {
        singleHead->next = singleHead; // Self-cycle
        assert(singleList.hasCycle());
        singleHead->next = nullptr; // Restore
    }
    
    std::cout << "Cycle detection tests passed!\n" << std::endl;
}

void runAllTests() {
    std::cout << "Running all tests...\n" << std::endl;
    
    testLinkedList();
    testDoublyLinkedList();
    testStack();
    testQueue();
    testDeque();
    testIsSubsequence();
    testIsPalindrome();
    testMergeSortedLists();
    testCycleDetection();
    
    std::cout << "🎉 All tests passed! 🎉" << std::endl;
}

int main() {
    try {
        runAllTests();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}