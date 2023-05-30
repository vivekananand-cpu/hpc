#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;
struct Node {
    int data;
    std::vector<Node*> children;
};

void parallelBFS(Node* root) {
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        #pragma omp parallel for
        for (int i = 0; i < levelSize; i++) {
            Node* current = q.front();
            q.pop();
            std::cout << current->data << " "; // Process the node here

            // Enqueue children of the current node
            for (Node* child : current->children) {
                #pragma omp critical
                q.push(child);
            }
        }
    }
}

int main() {
    // Create a sample tree
    Node* root = new Node{1};
    Node* node2 = new Node{2};
    Node* node3 = new Node{3};
    Node* node4 = new Node{4};
    Node* node5 = new Node{5};
    Node* node6 = new Node{6};

    root->children.push_back(node2);
    root->children.push_back(node3);
    node2->children.push_back(node4);
    node2->children.push_back(node5);
    node3->children.push_back(node6);

    parallelBFS(root);

    // Clean up allocated memory
    delete node6;
    delete node5;
    delete node4;
    delete node3;
    delete node2;
    delete root;

    return 0;
}
