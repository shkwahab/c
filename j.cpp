#include <iostream>
#include <string>

using namespace std;

struct AVLNode {
    int key;
    string line;
    int height;
    AVLNode* left;
    AVLNode* right;
};

class TextEditor:public AVLNode{
private:
    // AVLNode* root;
    // int height(AVLNode* node);
    // int getBalance(AVLNode* node);
    // AVLNode* newNode(int key, string line);
    // AVLNode* rightRotate(AVLNode* node);
    // AVLNode* leftRotate(AVLNode* node);
    // AVLNode* insert(AVLNode* node, int key, string line);
    // AVLNode* minValueNode(AVLNode* node);
    // AVLNode* deleteNode(AVLNode* node, int key);
    // void preOrder(AVLNode* node);

public:
    TextEditor();
    void insertLine(int lineNumber, string line);
    void deleteLine(int lineNumber);
    void updateLine(int lineNumber, string newLine);
    string getLine(int lineNumber);
    void display();
};

TextEditor::TextEditor() {
    root = nullptr;
}

// some helper functions

void TextEditor::insertLine(int lineNumber, string line) {
    root = insert(root, lineNumber, line);
}

void TextEditor::deleteLine(int lineNumber) {
    root = deleteNode(root, lineNumber);
}

void TextEditor::updateLine(int lineNumber, string newLine) {
    AVLNode* node = root;
    while (node != nullptr) {
        if (node->key == lineNumber) {
            node->line = newLine;
            break;
        } else if (node->key > lineNumber) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

string TextEditor::getLine(int lineNumber) {
    AVLNode* node = root;
    while (node != nullptr) {
        if (node->key == lineNumber) {
            return node->line;
        } else if (node->key > lineNumber) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return "Line not found";
}

void TextEditor::display() {
    preOrder(root);
}

int main() {
    TextEditor editor;
    editor.insertLine(1, "This is the first line");
    editor.insertLine(2, "This is the second line");
    editor.insertLine(3, "This is the third line");
    editor.display();
    cout << endl;
    editor.deleteLine(2);
    editor.display();
    cout << endl;
    editor.updateLine(3, "This is the updated third line");
    editor.display();
    cout<<endl;
}
