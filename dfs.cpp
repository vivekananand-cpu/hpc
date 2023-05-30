#include <iostream>
#include <vector>
#include <stack>
#include<omp.h>

using namespace std;

struct Node {
    int data;
    vector<Node*> child;
};

void parallelBFS(Node* root){
    stack<Node*> s ;
    s.push(root);
    while(!s.empty()){
        int levelSize = s.size();
        #pragma omp parallel for 
        for(int i = 0;i<levelSize ; i++){
            Node* current = s.top();
            s.pop();
            cout<<current->data<<" ";
             for (Node* child : current->child){
            #pragma omp critical
            s.push(child);
        }
        }
       
    }
    
    }
    
    
    int main(){
        Node* root =new Node{1};
        Node* node2 =new Node{2};
        Node* node3 =new Node{3};
        Node* node4 =new Node{4};
        Node* node5 =new Node{5};
        Node* node6 =new Node{6};
        
        root->child.push_back(node2);
        root->child.push_back(node3);
        node2->child.push_back(node4);
        node2->child.push_back(node5);
        node3->child.push_back(node6);
        
        parallelBFS(root);
        return 0;
    }
