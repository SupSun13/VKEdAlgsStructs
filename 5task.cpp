#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stack>
using namespace std;


struct TreeNode {
    int val;
    int balanceFactor;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), balanceFactor(0), left(nullptr), right(nullptr) {}
};

bool isMaxHeap(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        // Проверяем левого потомка
        if (left < n && arr[i] < arr[left]) {
            return false;
        }
        // Проверяем правого потомка
        if (right < n && arr[i] < arr[right]) {
            return false;
        }
    }
    return true;
}

bool isMaxHeapBFS(const vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return true;
    }

    queue<int> q;
    q.push(0); // начинаем с корня
    
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        // Проверяем левого потомка
        if (left < n) {
            if (arr[i] < arr[left]) {
                return false;
            }
            q.push(left);
        }
        // Проверяем правого потомка
        if (right < n) {
            if (arr[i] < arr[right]) {
                return false;
            }
            q.push(right);
        }
    }
    return true;
}

bool isMaxHeapFLAG(TreeNode* root) {
    if (!root) {
        return true;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    bool shouldBeLeaf = false;
    
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        // Проверяем левый потомок
        if (current->left) {
            if (shouldBeLeaf || current->left->val > current->val) {
                return false;
            }
            q.push(current->left);
        } else {
            shouldBeLeaf = true; // Все следующие узлы должны быть листьями
        }
        // Проверяем правый потомок
        if (current->right) {
            if (shouldBeLeaf || current->right->val > current->val) {
                return false;
            }
            q.push(current->right);
        } else {
            shouldBeLeaf = true; // Все следующие узлы должны быть листьями
        }
    }
    return true;
}

bool isCompleteTree(TreeNode* root) {
    if (!root) {
        return true;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    bool shouldBeLeaf = false;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (!node) {
            shouldBeLeaf = true;
        } else {
            // Если мы уже встретили null, но сейчас видим не-null узел - нарушение
            if (shouldBeLeaf) {
                return false;
            }
            // Добавляем оба потомка (даже если они null)
            q.push(node->left);
            q.push(node->right);
        }
    }
    
    return true;
}



struct HeapNode {
    int value;
    int arrayIdx;    // индекс массива
    int elementIdx;  // индекс элемента в массиве
    
    HeapNode(int val, int arrIdx, int elemIdx) 
        : value(val), arrayIdx(arrIdx), elementIdx(elemIdx) {}
};

// Компаратор для минимальной кучи
struct Compare {
    bool operator()(const HeapNode& a, const HeapNode& b) {
        return a.value > b.value;
    }
};

vector<int> mergeKSortedArrays(vector<vector<int>>& sortedArrays) {
    vector<int> mergedArray;
    
    priority_queue<HeapNode, vector<HeapNode>, Compare> minHeap;
    
    // Инициализируем кучу с первым элементом каждого массива
    for (int i = 0; i < sortedArrays.size(); i++) {
        vector<int>& currentArray = sortedArrays[i];
        // Проверяем, что массив не пустой
        if (!currentArray.empty()) {
            // (значение, индекс массива, индекс элемента)
            minHeap.push(HeapNode(currentArray[0], i, 0));
        }
    }
    
    // Пока куча не пуста
    while (!minHeap.empty()) {
        // Извлекаем наименьший элемент из кучи
        HeapNode node = minHeap.top();
        minHeap.pop();
        
        // Добавляем его в итоговый массив
        mergedArray.push_back(node.value);
        
        // Проверяем, есть ли следующий элемент в том же массиве
        if (node.elementIdx + 1 < sortedArrays[node.arrayIdx].size()) {
            // Добавляем следующий элемент этого массива в кучу
            int nextElement = sortedArrays[node.arrayIdx][node.elementIdx + 1];
            minHeap.push(HeapNode(nextElement, node.arrayIdx, node.elementIdx + 1));
        }
    }
    
    return mergedArray;
}

int inorderMinIterative(TreeNode* node, int k) {
    stack<TreeNode*> st;
    int counter = 0;
    TreeNode* current = node;
    
    while (!st.empty() || current != nullptr) {
        // Спускаемся влево, добавляя узлы в стек
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }
        
        current = st.top();
        st.pop();
        counter++;
        
        if (counter == k) {
            return current->val;
        }   
        current = current->right;
    }
    return -1;
}

int inorderMin(TreeNode* root, int k, int& counter) {
    if (root == nullptr) {
        return -1;
    }
    // Обход левого поддерева
    int leftResult = inorderMin(root->left, k, counter);
    if (leftResult != -1) {
        return leftResult;
    }
    // Увеличиваем счетчик и проверяем текущий узел
    counter++;
    if (counter == k) {
        return root->val;
    }
    // Обход правого поддерева
    return inorderMin(root->right, k, counter);
}

// Обертка для удобного использования
int inorderMin(TreeNode* root, int k) {
    int counter = 0;
    return inorderMin(root, k, counter);
}

int calculateHeightsAndBalance(TreeNode* node) {
    if (!node) {
        return 0; // Высота пустого дерева равна 0
    }
    
    // Рекурсивно вычисляем высоты левого и правого поддеревьев
    int leftHeight = calculateHeightsAndBalance(node->left);
    int rightHeight = calculateHeightsAndBalance(node->right);
    
    // Проставляем баланс-фактор текущего узла
    node->balanceFactor = leftHeight - rightHeight;
    
    // Возвращаем высоту текущего поддерева
    return 1 + max(leftHeight, rightHeight);
}

TreeNode* mirrorTreeIterative(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    // Очередь для обхода в ширину (BFS)
    queue<TreeNode*> q;
    q.push(node);
    
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        // Меняем местами левого и правого потомка
        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;
        // Добавляем в очередь дочерние узлы
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
    
    return node;
}

TreeNode* mirrorTree(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    
    swap(node->left, node->right);
    
    // Рекурсивно отражаем поддеревья
    mirrorTree(node->left);
    mirrorTree(node->right);
    
    return node;
}



// ================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ==================
TreeNode* createBST() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createMaxHeapTree() {
    TreeNode* root = new TreeNode(90);
    root->left = new TreeNode(15);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(7);
    root->left->right = new TreeNode(12);
    return root;
}

TreeNode* createCompleteTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

TreeNode* createIncompleteTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    // Нет left->right, но есть right->left - нарушение
    root->right->left = new TreeNode(6);
    return root;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ================== ТЕСТЫ ==================
void runTests() {
    cout << "=== ТЕСТИРОВАНИЕ ВСЕХ ФУНКЦИЙ ===\n" << endl;

    // Тесты isMaxHeap
    cout << "1. Тесты isMaxHeap:" << endl;
    vector<int> maxHeap = {90, 15, 10, 7, 12, 2};
    vector<int> notMaxHeap = {10, 15, 20, 7, 12, 2};
    
    cout << "   {90,15,10,7,12,2} isMaxHeap: " << isMaxHeap(maxHeap) << endl;
    cout << "   {10,15,20,7,12,2} isMaxHeap: " << isMaxHeap(notMaxHeap) << endl;
    cout << "   BFS version: " << isMaxHeapBFS(maxHeap) << endl;

    // Тесты isMaxHeapFLAG
    cout << "\n2. Тесты isMaxHeapFLAG:" << endl;
    TreeNode* maxHeapTree = createMaxHeapTree();
    TreeNode* bst = createBST();
    
    cout << "   MaxHeap tree: " << isMaxHeapFLAG(maxHeapTree) << endl;
    cout << "   BST (not max heap): " << isMaxHeapFLAG(bst) << endl;

    // Тесты isCompleteTree
    cout << "\n3. Тесты isCompleteTree:" << endl;
    TreeNode* completeTree = createCompleteTree();
    TreeNode* incompleteTree = createIncompleteTree();
    
    cout << "   Complete tree: " << isCompleteTree(completeTree) << endl;
    cout << "   Incomplete tree: " << isCompleteTree(incompleteTree) << endl;

    // Тесты mergeKSortedArrays
    cout << "\n4. Тесты mergeKSortedArrays:" << endl;
    vector<vector<int>> arrays = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    vector<int> merged = mergeKSortedArrays(arrays);
    
    cout << "   Merged arrays: ";
    for (int num : merged) cout << num << " ";
    cout << endl;

    // Тесты k-th smallest
    cout << "\n5. Тесты k-th smallest:" << endl;
    cout << "   3rd smallest (iterative): " << inorderMinIterative(bst, 3) << endl;
    cout << "   3rd smallest (recursive): " << inorderMin(bst, 3) << endl;
    cout << "   5th smallest: " << inorderMin(bst, 5) << endl;

    // Тесты balance factor
    cout << "\n6. Тесты calculateHeightsAndBalance:" << endl;
    int height = calculateHeightsAndBalance(bst);
    cout << "   Tree height: " << height << endl;
    cout << "   Root balance: " << bst->balanceFactor << endl;

    // Тесты mirror tree
    cout << "\n7. Тесты mirrorTree:" << endl;
    TreeNode* original = createBST();
    TreeNode* mirrored = mirrorTree(original);
    
    cout << "   Original 3rd smallest: " << inorderMinIterative(original, 3) << endl;
    cout << "   Mirrored 3rd smallest: " << inorderMinIterative(mirrored, 3) << endl;

    // Освобождение памяти
    deleteTree(maxHeapTree);
    deleteTree(bst);
    deleteTree(completeTree);
    deleteTree(incompleteTree);
    deleteTree(mirrored);
}

int main() {
    runTests();
    cout << "\n=== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ ===" << endl;
    return 0;
}