#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"
#include <vector>


inline void collect_all_Files_inRange(Node* node, size_t min, size_t max, std::vector<File*>& result) {
    //If the node is null, stop the recursion.
    if (node == nullptr) return;
    //Left
    //Traverse Recursively the left subtree if it exists
    //values less than the current node's size are processed first.
    collect_all_Files_inRange(node->left_, min, max, result);

    // Check each file stored in the current node.
    for (auto file : node->files_) {
        // If the file size is within the specified range, add it to the result vector.
        if (file->getSize() >= min && file->getSize() <= max) {
            result.push_back(file);
        }
    }
    //Right
    //Traverse Recursively the right subtree if it exists.
    //values greater than the current node's size are processed next.
    collect_all_Files_inRange(node->right_, min, max, result);
}

//Collect all files from the nodes
inline void collect_Files_From_Nodes(FileTrieNode* node, std::unordered_set<File*>& results) {
    if (node == nullptr) return;

    // Add all matching file pointers from the current node to the results set.
    results.insert(node->matching.begin(), node->matching.end());

    // Recursively process all child nodes.
    for (const auto& [key, childNode] : node->next) {
        collect_Files_From_Nodes(childNode, results);
    }
}


// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */

std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> result;

    // Check if range is valid by swapping min and max if needed
    if (min >= max) std::swap(min, max);

    // Collect all the files within the range
    collect_all_Files_inRange(root_, min, max, result);

    return result;
}

// Your code here.
//search entire file system (efficient range search) 
//(dont recurse on a child above the range)
//(range search is O(logn + k) where k is the number of files/elements in the range)
// Normalize the range

//tri is searching for a tree with a prefix
//(tree where each child is a character and you read full the string in and follow the the path character by character/ tells if its
//in the set)
//we are gona use a modification of that where we arent gonnna story the elements just at the leaves bu store on each node that represents
//a prefix of that file name


//FileTrie addfile
void FileTrie::addFile(File* f) {
    std::string filename = f->getName();
    FileTrieNode* current = head;

    // Traverse the trie structure for the file's name
    for (char ch : filename) {
        char lowerCh = std::tolower(ch);  // Convert "tolower" character to lowercase

        // Create a new node if it doesn't exist for the current character
        if (current->next.find(lowerCh) == current->next.end()) {
            current->next[lowerCh] = new FileTrieNode(lowerCh);
        }
        // Move to the next node in the trie
        current = current->next[lowerCh];

        // Add the file to the matching set at the current node
        current->matching.insert(f);
    }
}

// FileTrie getFilesWithPrefix
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const {
    std::unordered_set<File*> results;  // Set to store the matching files
    FileTrieNode* current = head;       // Start at the root of the trie

    // Traverse the trie to find the node corresponding to the prefix
    for (char ch : prefix) {
        char lowerCh = std::tolower(ch);  // Convert the character to lowercase

        // If the current character is not in the trie, return an empty set
        if (current->next.find(lowerCh) == current->next.end()) {
            return results;
        }

        // Move to the next node in the trie
        current = current->next[lowerCh];
    }

    // Collect all files from the current node and its descendants
    collect_Files_From_Nodes(current, results);
    return results;
}

// //Testing Functions
// int main() {


//     //testing helper functions 
//     // Example files
//     File* file1 = new File("file1.txt", "File 1 contents", nullptr, 10); // Size: 10
//     File* file2 = new File("file2.txt", "File 2 contents", nullptr, 25); // Size: 25
//     File* file3 = new File("file3.txt", "File 3 contents", nullptr, 50); // Size: 50
//     File* file4 = new File("file4.txt", "File 4 contents", nullptr, 75); // Size: 75
//     File* file5 = new File("file5.txt", "File 5 contents", nullptr, 100); // Size: 100

//     // Creating an example AVL tree for testing `collect_all_Files_inRange`
//     Node* root = new Node(file3);
//     root->left_ = new Node(file1);
//     root->right_ = new Node(file5);
//     root->left_->right_ = new Node(file2);
//     root->right_->left_ = new Node(file4);

//     // Test `collect_all_Files_inRange`
//     std::cout << "Testing collect_all_Files_inRange:" << std::endl;
//     std::vector<File*> rangeResults;
//     collect_all_Files_inRange(root, 20, 80, rangeResults);
//     for (const auto& file : rangeResults) {
//         std::cout << "File in range: " << file->getName() << " (Size: " << file->getSize() << ")" << std::endl;
//     }
//     std::cout << std::endl;

//     // Creating a FileTrie for testing `collect_Files_From_Nodes`
//     FileTrieNode* trieRoot = new FileTrieNode('\0'); // Root node
//     trieRoot->matching = {file1, file3};
//     trieRoot->next['a'] = new FileTrieNode('a');
//     trieRoot->next['b'] = new FileTrieNode('b');
//     trieRoot->next['a']->matching = {file2};
//     trieRoot->next['b']->matching = {file4, file5};

//     // Test `collect_Files_From_Nodes`
//     std::cout << "Testing collect_Files_From_Nodes:" << std::endl;
//     std::unordered_set<File*> nodeResults;
//     collect_Files_From_Nodes(trieRoot, nodeResults);
//     for (const auto& file : nodeResults) {
//         std::cout << "File collected: " << file->getName() << std::endl;
//     }
//     std::cout << std::endl;

//     // Test `deleting_Nodes`
//     std::cout << "Testing deleting_Nodes:" << std::endl;
//     deleting_Nodes(trieRoot); // Deletes all nodes in the trie
//     std::cout << "Trie nodes deleted successfully." << std::endl;



//     // Initializing FileTrie and files
//     FileTrie fileTrie;

//     File* f1 = new File("apple.txt", "Contents of apple.txt", nullptr);
//     File* f2 = new File("banana.txt", "Contents of banana.txt", nullptr);
//     File* f3 = new File("apricot.txt", "Contents of apricot.txt", nullptr);

//     std::cout << "Testing for FileTrie implementation" << std::endl;

//     // Adding files to the trie
//     fileTrie.addFile(f1);
//     fileTrie.addFile(f2);
//     fileTrie.addFile(f3);

//     std::cout << "Added files to FileTrie." << std::endl;

//     // Searching for prefixes
//     auto searchAndPrint = [&](const std::string& prefix) {
//         std::cout << "Looking for prefix: \"" << prefix << "\"" << std::endl;
//         auto results = fileTrie.getFilesWithPrefix(prefix);
//         if (results.empty()) {
//             std::cout << "No files found for prefix \"" << prefix << "\"." << std::endl;
//         } else {
//             for (auto file : results) {
//                 std::cout << "Found file: " << file->getName() << std::endl;
//             }
//         }
//         std::cout << std::endl;
//     };

//     searchAndPrint("ap");
//     searchAndPrint("b");
//     searchAndPrint("c");
//     searchAndPrint("blue");
//     searchAndPrint("x");

//     // Adding additional files dynamically
//     File* f6 = new File("blackberry.txt", "Contents of blackberry.txt", nullptr);
//     File* f7 = new File("carrot.txt", "Contents of carrot.txt", nullptr);

//     std::cout << "Adding more files dynamically..." << std::endl;
//     fileTrie.addFile(f6);
//     fileTrie.addFile(f7);

//     searchAndPrint("bl");
//     searchAndPrint("car");

//     // Edge cases: Empty prefix and long prefix
//     searchAndPrint("");
//     searchAndPrint("Something_tasty");

//     std::cout << "All tests completed successfully!" << std::endl;

//     return 0;
// }