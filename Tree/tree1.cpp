#include <iostream>
#include <list>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left, *right;
    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

void DeleteTree(TreeNode *node) {
    if (node != nullptr) {
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }
}

TreeNode* AddChild(TreeNode *parent, int value, const char *path) {
    if (parent == 0) {
        parent = new TreeNode(0);
    }
    switch (*path) {
        case ')':
            parent->value = (parent->value == 0 && value != 0) ? value : -1;
            break;
        case 'L':
            parent->left = AddChild(parent->left, value, path + 1);
            break;
        case 'R':
            parent->right = AddChild(parent->right, value, path + 1);
            break;
    }
    return parent;
}

int main() {
    TreeNode *root = nullptr;
    string token;
    while (cin >> token) {
        const char *path = token.c_str();
        int nLen = token.length(), value = 0;
        if (path[1] != ')') {
            for (; isdigit(*++path); value = value * 10 + *path - '0');
            if (*path != ',') while(true);
            root = AddChild(root, value, ++path);
            continue;
        }

        list<TreeNode*> levelOrder;
        stringstream resultStream;
        levelOrder.push_back(root);

        while (!levelOrder.empty()) {
            TreeNode *current = levelOrder.front();
            levelOrder.pop_front();
            if (current == 0) {
                continue;
            }
            if (current->value <= 0) {
                levelOrder.clear();
                resultStream.str("");
                break;
            }

            resultStream << current->value << ' ';
            levelOrder.push_back(current->left);
            levelOrder.push_back(current->right);
        }
        DeleteTree(root);
        root = nullptr;

        string result = resultStream.str();
        if (result.empty()) {
            result = "not complete";
        } else {
            result.erase(result.end() - 1);      
        }
        cout << result << endl;
    }
    return 0;
}