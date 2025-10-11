#include <iostream>
#include <vector>
using namespace std;

//интересное замечание: можно писать не функцию, которая возвращает вектор,
//а просто войд, т.к. везде принимаем ссылку на вектор
//впрочем, тогда не будет работать printVector

void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}


// первая задача с нахождением индексов двух чисел в сортед массиве,
// которые дают сумму target
vector<int> twoSum(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int sum = 0;
    while (left < right) {
         sum = nums[left] + nums[right];
         if (sum == target) {
            vector<int> result(2);
            result[0] = left;
            result[1] = right;
            return result;
         }
         else if (sum < target) {
            ++left;
         }
         else {
            --right;
         }
    };

    vector<int> result(2, -1);
    return result;
}

// вторая задача с разворотом массива
vector<int> reverse(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
        swap(nums[left], nums[right]);
        ++left;
        --right;
    };
    return nums;
}

//третья задача с разворотом части массива
//перегрузим ревёрс, чтобы была возможность задавать левый и правый индексы
vector<int> reverse(vector<int>& nums, int left, int right) {
    while (left < right) {
        swap(nums[left], nums[right]);
        ++left;
        --right;
    }
    return nums;
}

vector<int> cicle_move(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> arr = reverse(nums);
    arr = reverse(arr, 0, k % n - 1);
    arr = reverse(arr, k % n, n - 1);
    return arr;
}

//четвёртая задача со слияние двух отсортированных массивов
vector<int> merge_sorted_arrays(vector<int>& arr1, vector<int>& arr2) {
    vector<int> merged_array;
    int i = 0, j = 0;
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] < arr2[j]) {
            merged_array.push_back(arr1[i]);
            ++i;
        } else {
            merged_array.push_back(arr2[j]);
            ++j;
        }
    }
    merged_array.insert(merged_array.end(), arr1.begin() + i, arr1.end());
    merged_array.insert(merged_array.end(), arr2.begin() + j, arr2.end());
    return merged_array;
    }


//списки отсортированы, в конце первого нули
vector<int> merge(vector <int>& arr1, vector<int>& arr2) {
    int i = arr1.size() - arr2.size() - 1;
    int j = arr2.size() - 1;
    int k = arr1.size() - 1;
    while (j >= 0){
        if (i >= 0 && arr1[i] > arr2[j]) { //зачему условие i >= 0? уходим куда-то аутофренж, там мб быть приколы
            arr1[k] = arr1[i];
            --i;
        } else {
            arr1[k] = arr2[j];
            --j;
        }
        --k;
    }
    return arr1;
}

//пятая задача, с нулями и единицами
vector<int> sort_binary_array(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    while (left < right){
        if (arr[left] == 1) {
            swap(arr[left], arr[right]);
            --right;
        } else {
            ++left;
        }
    }
    return arr;
}

//шестая задача, флага Нидерландов
vector<int> flag_problem(vector<int>& arr) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;
    while (mid <= high){
        if (arr[mid] == 0){
            swap(arr[low], arr[mid]);
            ++low;
            ++mid;
        } else if (arr[mid] == 1){
            ++mid;
        } else if (arr[mid] == 2){
            swap(arr[mid], arr[high]);
            --high;
        }
    }
    return arr;
}

//задача седьмая с переносом чётных в начало с сохранением очерёдности
vector<int> evenFirst(vector<int>& arr) {
    int evenIndex = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] % 2 == 0) {
            swap(arr[i], arr[evenIndex]);
            ++evenIndex;
        }
    }
    return arr;
}

//задача восьмая с переносом нулей в конец
vector<int> zerosToEnd(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    while (left < right){
        if (arr[left] == 0) {
            swap(arr[left], arr[right]);
            --right;
        } else {
            ++left;
        }
    }
    return arr;
}

int main(){
    vector<int> nums = {3, 8, 9, 11, 16, 18, 19, 21};
    vector<int> nums_2 = {1, 2, 8, 15};
    vector<int> nums_3 = {3, 8, 9, 11, 16, 18, 19, 21, 0, 0, 0, 0};
    vector<int> binary = {0, 1, 1, 0, 1, 0, 1, 0};
    vector<int> zeros = {0, 0, 0, 18, 16, 0, 0, 77, 99};
    // printVector(nums);
    // printVector(twoSum(nums, 25));
    // printVector(reverse(nums));
    // printVector(cicle_move(nums, 3));
    // printVector(merge(nums_3, nums_2));
    // printVector(sort_binary_array(binary));
    // printVector(evenFirst(nums));
    printVector(zerosToEnd(zeros));
}
