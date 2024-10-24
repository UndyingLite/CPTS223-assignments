#include <iostream>
#include <map>
#include <vector>
#include "generateUsers.hpp"  // Include the header for generating users

using namespace std;

// Function declarations
map<string, User> buildMapByUserName(vector<User> users);
map<string, User> buildMapByEmail(vector<User> users);
void printMap(const map<string, User>& aMap);
bool isMapSorted(const map<string, User>& aMap);
bool testSearchByKey(const map<string, User>& aMap, const string& keyToSearch);
bool testDeleteByKey(map<string, User>& aMap, const string& keyToDelete);
void printActiveUsers(const map<string, User>& aMap);
void printMostPopularCategory(const map<string, User>& aMap);

// Builds a map using userName as the key.
map<string, User> buildMapByUserName(vector<User> users) {
    map<string, User> usersMap;
    for (const auto& user : users) {
        usersMap[user.userName] = user;  // Insert user into map with userName as the key.
    }
    return usersMap;
}

// Builds a map using email as the key.
map<string, User> buildMapByEmail(vector<User> users) {
    map<string, User> usersMap;
    for (const auto& user : users) {
        usersMap[user.email] = user;  // Insert user into map with email as the key.
    }
    return usersMap;
}

// Prints all elements of the map.
void printMap(const map<string, User>& aMap) {
    for (const auto& entry : aMap) {
        cout << "Key: " << entry.first << ", "
             << "UserName: " << entry.second.userName << ", "
             << "First Name: " << entry.second.firstName << ", "
             << "Last Name: " << entry.second.lastName << ", "
             << "Email: " << entry.second.email << ", "
             << "# of Posts: " << entry.second.numPosts << ", "
             << "Most Viewed Category: " << entry.second.mostViewedCategory << endl;
    }
}

// Checks if the map is sorted by its keys (it always is for std::map).
bool isMapSorted(const map<string, User>& aMap) {
    return true; // std::map is always sorted by key.
}

// Searches the map for a specific key.
bool testSearchByKey(const map<string, User>& aMap, const string& keyToSearch) {
    auto it = aMap.find(keyToSearch);
    return it != aMap.end();
}

// Deletes an element by key from the map.
bool testDeleteByKey(map<string, User>& aMap, const string& keyToDelete) {
    auto it = aMap.find(keyToDelete);
    if (it != aMap.end()) {
        aMap.erase(it);
        return true;
    }
    return false;
}

// Prints users with more than 800 posts.
void printActiveUsers(const map<string, User>& aMap) {
    int activeThreshold = 800;
    for (const auto& entry : aMap) {
        if (entry.second.numPosts > activeThreshold) {
            cout << entry.first << endl;
        }
    }
}

// Prints the most popular category based on the number of users viewing it.
void printMostPopularCategory(const map<string, User>& aMap) {
    map<string, int> categoryCount;
    for (const auto& entry : aMap) {
        categoryCount[entry.second.mostViewedCategory]++;
    }

    string mostPopularCategory;
    int maxCount = 0;
    for (const auto& category : categoryCount) {
        if (category.second > maxCount) {
            maxCount = category.second;
            mostPopularCategory = category.first;
        }
    }
    cout << "Most Popular Category: " << mostPopularCategory << endl;
}

int main() {
    int numUsers = 10;
    vector<User> users = generateUsers(numUsers); // Generate users

    // Building and operating on maps
    cout << "Build map with username as key" << endl;
    map<string, User> mapByUserName = buildMapByUserName(users);
    if (mapByUserName.size() == numUsers) {
        cout << " Built successfully." << endl << endl;
    } else {
        cout << " Built unsuccessfully." << endl << endl;
    }

    cout << "Print \"mapByUserName\" map:" << endl;
    printMap(mapByUserName);
    cout << endl;

    string keyToSearch = "smith55";
    cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
    if (testSearchByKey(mapByUserName, keyToSearch)) {
        cout << " Search successfully." << endl << endl;
    } else {
        cout << " Search unsuccessfully." << endl << endl;
    }

    string keyToDelete = "smith55";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if (testDeleteByKey(mapByUserName, keyToDelete)) {
        cout << " Delete successfully." << endl << endl;
    } else {
        cout << " Delete unsuccessfully." << endl << endl;
    }

    cout << "Test if map's key is sorted" << endl;
    if (isMapSorted(mapByUserName)) {
        cout << " Order test passed!" << endl << endl;
    } else {
        cout << " Order test failed!" << endl << endl;
    }

    cout << "Print usernames with more than 800 tweets:" << endl;
    printActiveUsers(mapByUserName);
    cout << endl;

    cout << "Print the most popular category" << endl;
    printMostPopularCategory(mapByUserName);
    cout << endl;

    cout << "============================================================================== " << endl << endl;

    cout << "Build map with email as key" << endl;
    map<string, User> mapByEmail = buildMapByEmail(users);
    if (mapByEmail.size() == numUsers) {
        cout << " Built successfully." << endl << endl;
    } else {
        cout << " Built unsuccessfully." << endl << endl;
    }

    keyToSearch = "kat@gmail.com";
    cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
    if (testSearchByKey(mapByEmail, keyToSearch)) {
        cout << " Search successfully." << endl << endl;
    } else {
        cout << " Search unsuccessfully." << endl << endl;
    }

    keyToDelete = "kat@gmail.com";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if (testDeleteByKey(mapByEmail, keyToDelete)) {
        cout << " Delete successfully." << endl << endl;
    } else {
        cout << " Delete unsuccessfully." << endl << endl;
    }

    return 0;
}
