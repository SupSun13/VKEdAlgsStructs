#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

int binarySearchSqrt(float target){
    if (target < 0) return -1;
    if (target < 1.0f) return 0;

    int left = 0;
    int right = trunc(target) / 2; //тут мб и round бы подошёл
    while (left <= right) {
        int middle = left + (right - left) / 2;
        double sq = (double)middle * (double)middle;

        if (sq > target) {
            right = middle - 1;
        } else if (sq < target) {
            left = middle + 1;
        } else { return middle; }
    }

    return right;
}

long long copyTime(int n, int x, int y) {
    long long left = 0;
    long long right = (long long)(n - 1) * max(x, y);

    while (left + 1 < right) {
        long long mid = left + (right - left) / 2;
        long long copies = mid / x + mid / y;

        if (copies < n - 1) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return right + min(x, y);
}

int feedAnimals(const vector<int>& animals, const vector<int>& food) {
    if (animals.empty() || food.empty()) {
        return 0;
    }

    vector<int> sorted_animals = animals;
    vector<int> sorted_food = food;
    sort(sorted_animals.begin(), sorted_animals.end());
    sort(sorted_food.begin(), sorted_food.end());

    int count = 0;

    for (int f : sorted_food) {
        if (f >= sorted_animals[count]) {
            count++;
            if (count == static_cast<int>(sorted_animals.size())) {
                break;
            }
        }
    }
    return count;
}

char extraLetter(const string& a, const string& b) {
    unordered_map<char, int> hashMapA;

    for (char c : a) {
        hashMapA[c]++;
    }

    for (char c : b) {
        if (hashMapA.count(c)) {
            hashMapA[c]--;
            if (hashMapA[c] == 0) {
                hashMapA.erase(c); 
            }
        } else {
            return c;
        }
    }
    return '\0';
}

vector<int> twoSum(const vector<int>& data, int target) {
    unordered_map<int, int> cache;

    for (int i = 0; i < static_cast<int>(data.size()); ++i) {
        int num = data[i];
        int diff = target - num;
        if (cache.count(diff)) {
            return {cache[diff], i};
        }
        cache[num] = i;
    }
    return {};
}

#include <vector>

vector<int> shell_sort(vector<int> arr) {
    int n = static_cast<int>(arr.size());
    int gap = n / 2;

    while (gap > 0) {
        for (int current_position = gap; current_position < n; ++current_position) {
            int temp = arr[current_position];
            int m_gap = current_position;
            while (m_gap >= gap && arr[m_gap - gap] > temp) {
                arr[m_gap] = arr[m_gap - gap];
                m_gap -= gap;
            }
            arr[m_gap] = temp;
        }
        gap /= 2;
    }
    return arr;
}

vector<vector<string>> groupAnagrams(vector<string> strs) {
    unordered_map<string, vector<string>> groups;

    for (const string& word : strs) {
        string sorted_word = word;
        sort(sorted_word.begin(), sorted_word.end());
        groups[sorted_word].push_back(word);
    }
    vector<vector<string>> result;
    for (const auto& pair : groups) {
        result.push_back(pair.second);
    }
    return result;
}

int main() {
    cout << "binarySearchSqrt(569.1): " << binarySearchSqrt(569.1f) << endl;  // 23
    cout << "binarySearchSqrt(16): " << binarySearchSqrt(16.0f) << endl;      // 4
    cout << "binarySearchSqrt(0.25): " << binarySearchSqrt(0.25f) << endl;    // 0
    cout << "binarySearchSqrt(-1): " << binarySearchSqrt(-1.0f) << endl;      // -1

    cout << "\ncopyTime(3, 1, 2): " << copyTime(3, 1, 2) << endl;  // 3
    cout << "copyTime(4, 1, 2): " << copyTime(4, 1, 2) << endl;   // 4

    vector<int> animals = {1, 2, 3};
    vector<int> food = {1, 1, 1, 4};
    cout << "\nfeedAnimals: " << feedAnimals(animals, food) << endl;  // 2

    cout << "\nextraLetter: " << extraLetter("abcd", "abcde") << endl;  // e

    vector<int> nums = {2, 7, 11, 15};
    auto result = twoSum(nums, 9);
    cout << "twoSum: [" << result[0] << ", " << result[1] << "]" << endl;  // [0, 1]

    vector<int> arr = {64, 88, 15, 2, 7, 33, 46, 55, 1};
    arr = shell_sort(arr);
    cout << "\nshell_sort: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    vector<string> anagrams = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto groups = groupAnagrams(anagrams);
    cout << "\ngroupAnagrams:" << endl;
    for (const auto& group : groups) {
        for (const string& s : group) {
            cout << s << " ";
        }
        cout << endl;
    }

    return 0;
}