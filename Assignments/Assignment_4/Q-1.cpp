#include<bits/stdc++.h>
using namespace std;

class BSTNode
{
    public:
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent;

    BSTNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BinarySearchTree
{
    protected:
        BSTNode* root;
    private:

    void InorderHelper(BSTNode* node, vector<int>& res)
    {
        if(node)
        {
            InorderHelper(node->left,res);
            res.push_back(node->key);
            InorderHelper(node->right,res);
        }
    }

    BSTNode* searchHelper(BSTNode* node,int key)
    {
        if(node==nullptr || node->key == key)
        {
            return node;
        }
        if(key<node->key)
        {
            return searchHelper(node->left,key);
        }
        return searchHelper(node->right,key);
    }

    BSTNode* findMin(BSTNode* node) 
    {
        while (node && node->left) 
        {
            node = node->left;
        }
        return node;
    }

    BSTNode* findMax(BSTNode* node) 
    {
        while (node && node->right) 
        {
            node = node->right;
        }
        return node;
    }

    BSTNode* selectHelper(BSTNode* node, int k,int& count)
    {
        if(node==nullptr)
        {
            return nullptr;
        }
        BSTNode* left = selectHelper(node->left , k, count);

        if(left)
        {
            return left;
        }
        count++;

        if(count==k)
        {
            return node;
        }
        return selectHelper(node->right,k,count);
    }

    int rankHelper(BSTNode* node , int key , int& rank)
    {
        if (node == nullptr) 
        {
            return rank;
        }

        if (key < node->key) 
        {
            return rankHelper(node->left, key, rank);
        } 
        else 
        {
            rank += size(node->left) + 1;
            if (key == node->key) 
            {
                return rank;
            }
            return rankHelper(node->right, key, rank);
        }
    }

    void transplant(BSTNode* u,BSTNode* v)
    {
        if(u->parent == nullptr)
        {
            root = v;
        }
        else if(u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        if(v != nullptr)
        {
            v->parent = u->parent;
        }
    }

    void delNode(BSTNode* z)
    {
        if(z->left == nullptr)
        {
            transplant(z,z->right);
        }
        else if(z->right == nullptr)
        {
            transplant(z,z->left);
        }
        else
        {
            BSTNode* y = findMin(z->right);
            if(y->parent != z)
            {
                transplant(y,y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z,y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

    int size(BSTNode* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        return 1 + size(node->left) + size(node->right);
    }


    public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key)
    {
        BSTNode* node = new BSTNode(key);
        BSTNode* y = nullptr;
        BSTNode* x = root;

        while(x != nullptr)
        {
            y = x;
            if(node->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;
        if(y == nullptr)
        {
            root = node;
        }
        else if(node->key < y->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
    }

    bool search(int key)
    {
        return searchHelper(root , key) != nullptr;
    }

    void remove(int key)
    {
        BSTNode* node = searchHelper(root,key);
        if(node)
        {
            delNode(node);
        }
    }

    vector<int> inorderTraversal()
    {
        vector<int> res;
        InorderHelper(root,res);
        return res;
    }
    
    int findMinimum()
    {
        BSTNode* minNode = findMin(root);
        return minNode ? minNode->key : -1;
    }
    int findMaximum()
    {
        BSTNode* maxNode = findMax(root);
        return maxNode ? maxNode->key : -1;
    }

    int select(int k)
    {
        int count = 0;
        BSTNode* result = selectHelper(root,k,count);
        return result ? result->key : -1;
    }

    int rank(int key)
    {
        int rank = 0;
        return rankHelper(root,key,rank);
    }

    int findPred(int key)
    {
        BSTNode* node = searchHelper(root,key);
        if(node == nullptr)
        {
            return -1;
        }
        if(node->left)
        {
            return findMax(node->left)->key;
        }

        BSTNode* y = node->parent;
        while(y != nullptr && node == y->left)
        {
            node = y;
            y = y->parent;
        }
        return y ? y->key : -1;
    }

    int findSuc(int key)
    {
        BSTNode* node = searchHelper(root,key);
        if(node == nullptr)
        {
            return -1;
        }
        if(node->right)
        {
            return findMin(node->right)->key;
        }

        BSTNode* y = node->parent;
        while(y != nullptr && node == y->right)
        {
            node = y;
            y = y->parent;
        }
        return y ? y->key : -1;
    }
};

enum Color { RED, BLACK };

class RBTNode : public BSTNode 
{
public:
    Color color;

    RBTNode(int k) : BSTNode(k), color(RED) {}
};

class RedBlackTree : public BinarySearchTree 
{
    private:
        void leftRotate(RBTNode* x) 
        {
            RBTNode* y = static_cast<RBTNode*>(x->right);
            x->right = y->left;
            if (y->left != nullptr) 
            {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) 
            {
                root = y;
            } 
            else if (x == x->parent->left) 
            {
                x->parent->left = y;
            } 
            else 
            {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }

        void rightRotate(RBTNode* y) 
        {
            RBTNode* x = static_cast<RBTNode*>(y->left);
            y->left = x->right;
            if (x->right != nullptr) 
            {
                x->right->parent = y;
            }
            x->parent = y->parent;
            if (y->parent == nullptr) 
            {
                root = x;
            } 
            else if (y == y->parent->right) 
            {
                y->parent->right = x;
            } 
            else 
            {
                y->parent->left = x;
            }
            x->right = y;
            y->parent = x;
        }

        void fixInsert(RBTNode* z) 
        {
            while (z->parent && static_cast<RBTNode*>(z->parent)->color == RED) 
            {
                if (z->parent == z->parent->parent->left)
                {
                    RBTNode* y = static_cast<RBTNode*>(z->parent->parent->right);
                    if (y && y->color == RED) 
                    {
                        static_cast<RBTNode*>(z->parent)->color = BLACK;
                        y->color = BLACK;
                        static_cast<RBTNode*>(z->parent->parent)->color = RED;
                        z = static_cast<RBTNode*>(z->parent->parent);
                    } 
                    else 
                    {
                        if (z == z->parent->right) 
                        {
                            z = static_cast<RBTNode*>(z->parent);
                            leftRotate(z);
                        }
                        static_cast<RBTNode*>(z->parent)->color = BLACK;
                        static_cast<RBTNode*>(z->parent->parent)->color = RED;
                        rightRotate(static_cast<RBTNode*>(z->parent->parent));
                    }
                } 
                else 
                {
                    RBTNode* y = static_cast<RBTNode*>(z->parent->parent->left);
                    if (y && y->color == RED) 
                    {
                        static_cast<RBTNode*>(z->parent)->color = BLACK;
                        y->color = BLACK;
                        static_cast<RBTNode*>(z->parent->parent)->color = RED;
                        z = static_cast<RBTNode*>(z->parent->parent);
                    } 
                    else 
                    {
                        if (z == z->parent->left) 
                        {
                            z = static_cast<RBTNode*>(z->parent);
                            rightRotate(z);
                        }
                        static_cast<RBTNode*>(z->parent)->color = BLACK;
                        static_cast<RBTNode*>(z->parent->parent)->color = RED;
                        leftRotate(static_cast<RBTNode*>(z->parent->parent));
                    }
                }
            }
            static_cast<RBTNode*>(root)->color = BLACK;
        }

    public:
        void insert(int key) 
        {
            RBTNode* z = new RBTNode(key);
            BinarySearchTree::insert(z->key);  
            fixInsert(z);  
        }

};

int main() 
{
    BinarySearchTree bst;
    
    bst.insert(20);
    bst.insert(15);
    bst.insert(25);
    bst.insert(10);
    bst.insert(18);
    bst.insert(30);

    vector<int> inorderBST = bst.inorderTraversal();
    cout << "Inorder Traversal of BST: ";
    for (int val : inorderBST) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Search 25 in BST: " << (bst.search(25) ? "Found" : "Not Found") << endl;
    cout << "Search 150 in BST: " << (bst.search(150) ? "Found" : "Not Found") << endl;

    cout << "Minimum in BST: " << bst.findMinimum() << endl;
    cout << "Maximum in BST: " << bst.findMaximum() << endl;

    cout << "Rank of 18 in BST: " << bst.rank(18) << endl;

    cout << "3rd smallest element in BST: " << bst.select(3) << endl;

    cout << "Predecessor of 20 in BST: " << bst.findPred(20) << endl;
    cout << "Successor of 20 in BST: " << bst.findSuc(20) << endl;

    bst.remove(18);
    inorderBST = bst.inorderTraversal();
    cout << "Inorder Traversal of BST after deleting 18: ";
    for (int val : inorderBST) 
    {
        cout << val << " ";
    }
    cout << endl;

    RedBlackTree rbt;

    rbt.insert(20);
    rbt.insert(29);
    rbt.insert(27);
    rbt.insert(15);
    rbt.insert(42);
    rbt.insert(30);

    vector<int> inorderRBT = rbt.inorderTraversal();
    cout << "Inorder Traversal of Red-Black Tree: ";
    for (int val : inorderRBT) 
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}


