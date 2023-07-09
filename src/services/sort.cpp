#include "sort.h"

template<typename T>
void Sort<T>::bubble(vector<T>& items, bool (*compare)(const T&, const T&)) {
    int n = items.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(items[j], items[j + 1])) {
                swap(items[j], items[j + 1]);
            }
        }
    }
}
