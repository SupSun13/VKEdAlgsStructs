#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;


struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val = 0) : data(val), left(nullptr), right(nullptr) {}
};

// Восстановление бинарного дерева из массива 
TreeNode* buildTree(const vector<int>& arr, size_t i = 0) {
    if (i >= arr.size() || arr[i] == -1) {
        return nullptr;
    }
    
    TreeNode* root = new TreeNode(arr[i]);
    root->left = buildTree(arr, 2*i + 1);
    root->right = buildTree(arr, 2*i + 2);
    return root;
}

bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);
    
    while (!q.empty()) {
        TreeNode* leftNode = q.front(); q.pop();
        TreeNode* rightNode = q.front(); q.pop();
        // Оба null - продолжаем
        if (leftNode == nullptr && rightNode == nullptr) {
            continue;
        }
        // Один null, другой нет - не симметрично
        if (leftNode == nullptr || rightNode == nullptr) {
            return false;
        }
        // Значения не равны - не симметрично
        if (leftNode->data != rightNode->data) {
            return false;
        }
        // Добавляем пары для сравнения в правильном порядке
        q.push(leftNode->left);
        q.push(rightNode->right);
        
        q.push(leftNode->right);
        q.push(rightNode->left);
    }
    
    return true;
}

void deptSearch(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
        return;
    }
    deptSearch(root->left, res);
    res.push_back(root->data);
    deptSearch(root->right, res);
}

bool isSymmetricDFS(TreeNode* root) {
    if (root == nullptr) return true;
    
    vector<int> data;
    deptSearch(root, data);
    
    int j = data.size() - 1;
    for (int i = 0; i < data.size() / 2; i++) {
        if (data[i] != data[j]) {
            return false;
        }
        j--;
    }
    return true;
}

int minDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    // Лист (нет потомков)
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    // Оба потомка существуют
    if (root->left != nullptr && root->right != nullptr) {
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
    // Только левый потомок
    if (root->left != nullptr) {
        return 1 + minDepth(root->left);
    }
    // Только правый потомок
    if (root->right != nullptr) {
        return 1 + minDepth(root->right);
    }
    return 1; // На всякий случай)
}

int maxMinMultiplication(vector<int>& data) {
    if (data.size() < 3) {
        return -1;
    }
    // Самый левый элемент (минимальный индекс в пути левых потомков)
    int min_index = 0;
    while (2 * min_index + 1 < data.size()) {
        min_index = 2 * min_index + 1;
    }
    // Самый правый элемент (максимальный индекс в пути правых потомков)
    int max_index = 0;
    while (2 * max_index + 2 < data.size()) {
        max_index = 2 * max_index + 2;
    }
    return data[min_index] * data[max_index];
}

bool isSameTree(TreeNode* a, TreeNode* b) {
    // Оба узла null - одинаковые
    if (a == nullptr && b == nullptr) {
        return true;
    }
    // Один из узлов null, другой нет - разные
    if (a == nullptr || b == nullptr) {
        return false;
    }
    // Значения узлов не совпадают - разные
    if (a->data != b->data) {
        return false;
    }
    // Рекурсивно проверяем левые и правые поддеревья
    return isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
}

int main() {
    cout << "=== ТЕСТИРОВАНИЕ ФУНКЦИЙ ДЛЯ БИНАРНЫХ ДЕРЕВЬЕВ ===\n" << endl;

    // Тест buildTree
    cout << "1. Тест buildTree:" << endl;
    vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* tree1 = buildTree(arr1);
    cout << "   Дерево построено из массива: {1, 2, 3, 4, 5, 6, 7}" << endl;
    
    vector<int> arr2 = {1, 2, 2, 3, 4, 4, 3};
    TreeNode* symmetricTree = buildTree(arr2);
    cout << "   Симметричное дерево построено" << endl << endl;

    // Тест isSymmetric
    cout << "2. Тест isSymmetric:" << endl;
    cout << "   Симметричное дерево {1,2,2,3,4,4,3}: " << (isSymmetric(symmetricTree) ? "true" : "false") << endl;
    
    vector<int> arr3 = {1, 2, 2, -1, 3, -1, 3};
    TreeNode* nonSymmetricTree = buildTree(arr3);
    cout << "   Несимметричное дерево {1,2,2,-1,3,-1,3}: " << (isSymmetric(nonSymmetricTree) ? "true" : "false") << endl << endl;

    // Тест deptSearch (in-order обход)
    cout << "3. Тест deptSearch (in-order):" << endl;
    vector<int> traversal;
    deptSearch(tree1, traversal);
    cout << "   In-order обход дерева {1,2,3,4,5,6,7}: ";
    for (int val : traversal) cout << val << " ";
    cout << endl << endl;

    // Тест isSymmetricDFS (ДЕМОНСТРАЦИЯ ОШИБКИ)
    cout << "4. Тест isSymmetricDFS (НЕПРАВИЛЬНЫЙ метод):" << endl;
    cout << "   Симметричное дерево: " << (isSymmetricDFS(symmetricTree) ? "true" : "false") << endl;
    cout << "   Несимметричное дерево: " << (isSymmetricDFS(nonSymmetricTree) ? "true" : "false") << endl;
    cout << "   ВНИМАНИЕ: Этот метод может давать неверные результаты!" << endl << endl;

    // Тест minDepth
    cout << "5. Тест minDepth:" << endl;
    cout << "   Минимальная глубина полного дерева: " << minDepth(tree1) << endl;
    
    TreeNode* unbalancedTree = buildTree(vector<int>{1, 2, -1, 3, -1, -1, -1, 4});
    cout << "   Минимальная глубина несбалансированного дерева: " << minDepth(unbalancedTree) << endl << endl;

    // Тест maxMinMultiplication
    cout << "6. Тест maxMinMultiplication:" << endl;
    vector<int> treeArray = {10, 5, 15, 3, 7, 12, 20, 1, 4, 6, 8};
    cout << "   Произведение крайних элементов в массиве-дереве: " << maxMinMultiplication(treeArray) << endl;
    
    vector<int> smallArray = {1, 2};
    cout << "   Массив слишком мал: " << maxMinMultiplication(smallArray) << endl << endl;

    // Тест isSameTree
    cout << "7. Тест isSameTree:" << endl;
    TreeNode* treeA = buildTree(vector<int>{1, 2, 3});
    TreeNode* treeB = buildTree(vector<int>{1, 2, 3});
    TreeNode* treeC = buildTree(vector<int>{1, 2, 4});
    
    cout << "   Два одинаковых дерева: " << (isSameTree(treeA, treeB) ? "true" : "false") << endl;
    cout << "   Два разных дерева: " << (isSameTree(treeA, treeC) ? "true" : "false") << endl;
    cout << "   Оба nullptr: " << (isSameTree(nullptr, nullptr) ? "true" : "false") << endl;
    
    return 0;
}