#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure representing a file or folder
struct FileNode {
    string name;
    bool isFile;              // true if file, false if folder
    vector<FileNode*> children;

    FileNode(string n, bool file = false) {
        name = n;
        isFile = file;
    }
};

// Create a new file or folder node
FileNode* createItem(string name, bool isFile) {
    return new FileNode(name, isFile);
}

// Add a file or folder under a parent folder
void addItem(FileNode* parent, string name, bool isFile) {
    FileNode* item = createItem(name, isFile);
    parent->children.push_back(item);
}

// Recursive function to display the file system
void displayFileSystem(FileNode* root, string indent = "") {
    cout << indent << (root->isFile ? "[FILE] " : "[DIR]  ") << root->name << endl;
    for (auto child : root->children) {
        displayFileSystem(child, indent + "  |-- ");
    }
}

// Search for a file or folder by name
FileNode* searchItem(FileNode* root, string name) {
    if (root->name == name) return root;
    for (auto child : root->children) {
        FileNode* res = searchItem(child, name);
        if (res) return res;
    }
    return nullptr;
}

// Count total files in the file system
int countFiles(FileNode* root) {
    int count = root->isFile ? 1 : 0;
    for (auto child : root->children)
        count += countFiles(child);
    return count;
}

// Count total folders in the file system
int countFolders(FileNode* root) {
    int count = root->isFile ? 0 : 1;
    for (auto child : root->children)
        count += countFolders(child);
    return count;
}

int main() {
    // Create root folder
    FileNode* root = createItem("MyDrive");

    // Add folders and files
    addItem(root, "Projects", false);
    addItem(root, "Documents", false);
    addItem(root, "todo.txt", true);

    // Add subfolders and files inside "Projects"
    FileNode* projects = searchItem(root, "Projects");
    if (projects) {
        addItem(projects, "SudokuSolver.cpp", true);
        addItem(projects, "FileSystem.cpp", true);
    }

    // Add subfolders and files inside "Documents"
    FileNode* documents = searchItem(root, "Documents");
    if (documents) {
        addItem(documents, "MLNotes.txt", true);
        addItem(documents, "Assignments", false);
        FileNode* assignments = searchItem(documents, "Assignments");
        if (assignments)
            addItem(assignments, "DSA_HW.pdf", true);
    }

    // Display the full file system
    cout << "My File System:\n";
    displayFileSystem(root);

    // Count files and folders
    cout << "\nTotal Files: " << countFiles(root) << endl;
    cout << "Total Folders: " << countFolders(root) << endl;

    return 0;
}
