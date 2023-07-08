#include "search.h"

template<typename T>
template<typename Callback>
vector<T> Search<T>::fuzzy(const vector<T>& items, Callback callback, const string& searchQuery) {
    vector<T> results;
    
    for (const auto& item : items) {
        string fieldValue = callback(item);
        if (isFuzzyMatch(fieldValue, searchQuery)) {
            results.push_back(item);
        }
    }
    
    return results;
}

template<typename T>
bool Search<T>::isFuzzyMatch(const string& fieldValue, const string& searchQuery) {
    string lowerField = fieldValue;
    string lowerQuery = searchQuery;
    
    transform(lowerField.begin(), lowerField.end(), lowerField.begin(), ::tolower);
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    
    return lowerField.find(lowerQuery) != string::npos;
}
