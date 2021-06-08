#pragma once
#include <queue>
#include <stack>
#include <ostream>
#include <iostream>
using namespace std;

namespace ariel
{
    template <typename T>
    class BinaryTree
    {
    private:
        struct Node
        {
            T _value;
            Node *_left;
            Node *_right;
            Node(T value, Node *left = nullptr, Node *right = nullptr)
                : _value(value), _left(left), _right(right){};
            Node(Node &other) : _value(other._value)
            {
                if (other._left != nullptr)
                {
                    _left = new Node(other._left->_value);
                }
                if (other._right != nullptr)
                {
                    _right = new Node(other._right->_value);
                }
            }
            Node(Node &&other) noexcept : _value(other._value)
            {
                if (other._left != nullptr)
                {
                    _left = new Node(other._left->_value);
                }
                if (other._right != nullptr)
                {
                    _right = new Node(other._right->_value);
                }
                other.left = nullptr;
                other._right = nullptr;
            }
            Node &operator=(const Node other)
            {
                _value = other._value;
                if (other._left != nullptr)
                {
                    _left = new Node(_left->_value);
                }
                if (other._right != nullptr)
                {
                    _right = new Node(_left->_right);
                }
                return *this;
            }
            Node &operator=(Node &&other) noexcept
            {
                _value = other._value;
                if (other._left != nullptr)
                {
                    _left = new Node(_left->_value);
                }
                if (other._right != nullptr)
                {
                    _right = new Node(_left->_right);
                }
                other.left = nullptr;
                other._right = nullptr;
                return *this;
            }
            ~Node()
            {
                if (_left != nullptr)
                {
                    delete _left;
                }
                if (_right != nullptr)
                {
                    delete _right;
                }
            }
        };

    public:
        Node *_root; /// change to private
        BinaryTree() : _root(nullptr){};
        BinaryTree(BinaryTree &other)
        {
            queue<Node *> temp;
            _root = new Node(other._root->_value);
            temp.push(other._root);
            while (!temp.empty())
            {
                Node *curr = temp.front();
                temp.pop();
                if (curr->_left != nullptr)
                {
                    this->add_left(curr->_value, curr->_left->_value);
                    temp.push(curr->_left);
                }
                if (curr->_right != nullptr)
                {
                    this->add_right(curr->_value, curr->_right->_value);
                    temp.push(curr->_right);
                }
            }
        };
        BinaryTree(BinaryTree &&other) noexcept
        {
            _root = other._root;
            other._root = nullptr;
        }

        ~BinaryTree()
        {
            if (_root != nullptr)
            {
                delete _root;
            }
        };

        BinaryTree &add_root(T value)
        {
            if (_root == nullptr)
            {
                _root = new Node(value);
            }
            else
            {
                _root->_value = value;
            }
            return *this;
        }
        BinaryTree &add_left(T parent, T left)
        {
            if (_root == nullptr)
            {
                throw("Empty Tree");
            }
            queue<Node *> q;
            q.push(_root);
            Node *curr = nullptr;
            bool flag = false;
            while (!q.empty())
            {
                curr = q.front();
                q.pop();
                if (curr->_value == parent)
                {
                    flag = true;
                    break;
                }
                if (curr->_left != nullptr)
                {
                    q.push(curr->_left);
                }
                if (curr->_right != nullptr)
                {
                    q.push(curr->_right);
                }
            }
            if (!flag)
            {
                throw("Parent value doesn't exsists");
            }
            if (curr->_left == nullptr)
            {
                curr->_left = new Node(left);
            }
            else
            {
                curr->_left->_value = left;
            }
            return *this;
        }
        BinaryTree &add_right(T parent, T right)
        {
            if (_root == nullptr)
            {
                throw("Empty Tree");
            }
            queue<Node *> q;
            q.push(_root);
            Node *curr = nullptr;
            bool flag = false;
            while (!q.empty())
            {
                curr = q.front();
                q.pop();
                if (curr->_value == parent)
                {
                    flag = true;
                    break;
                }
                if (curr->_left != nullptr)
                {
                    q.push(curr->_left);
                }
                if (curr->_right != nullptr)
                {
                    q.push(curr->_right);
                }
            }
            if (!flag)
            {
                throw("Parent value doesn't exsists");
            }
            if (curr->_right == nullptr)
            {
                curr->_right = new Node(right);
            }
            else
            {
                curr->_right->_value = right;
            }
            return *this;
        }
        BinaryTree &operator=(BinaryTree other)
        {
            queue<Node *> temp;
            _root = new Node(other._root->_value);
            temp.push(other._root);
            while (!temp.empty())
            {
                Node *curr = temp.front();
                temp.pop();
                if (curr->_left != nullptr)
                {
                    this->add_left(curr->_value, curr->_left->_value);
                    temp.push(curr->_left);
                }
                if (curr->_right != nullptr)
                {
                    this->add_right(curr->_value, curr->_right->_value);
                    temp.push(curr->_right);
                }
            }
            return *this;
        }
        BinaryTree &operator=(BinaryTree &&other) noexcept
        {
            _root = other._root;
            other._root = nullptr;
            return *this;
        }
        friend ostream &operator<<(ostream &os, const BinaryTree &t)
        {
            return os;
        }

        class iterator
        {
        public:
            Node *node_ptr;
            Node *root;
            iterator(Node *ptr) : root(ptr), node_ptr(nullptr){};
            iterator(iterator &&other)noexcept:node_ptr(nullptr)
            {
                node_ptr = other.node_ptr;
                root = other.root;
                other.node_ptr = nullptr;
                other.root = nullptr;
            }
            iterator(const iterator &other) : root(other.root), node_ptr(other.node_ptr){};
            ~iterator() {}
            bool operator!=(const iterator &other) const
            {
                return (this->node_ptr != other.node_ptr);
            }
            bool operator==(const iterator &other) const
            {
                return (this->node_ptr == other.node_ptr);
            }
            T *operator->() const
            {
                return &(node_ptr->_value);
            }
            T &operator*() const
            {
                return node_ptr->_value;
            }
            iterator &operator=(iterator other)
            {
                if(this==&other){
                    return *this;
                }
                root = other.root;
                node_ptr = other.node_ptr;

                return *this;
            }
            iterator &operator=(iterator &&other) noexcept
            {
                node_ptr = other.node_ptr;
                root = other.root;
                other.node_ptr = nullptr;
                other.root = nullptr;
                return *this;
            }
        };
        class inOrder_iterator : public iterator
        {
        private:
            void find_node(int &i, Node *curr, bool &flag)
            {
                ////cout<<"Here, curr is nullptr =="<<boolalpha<<(curr == nullptr)<<endl;
                ////cout<<"Here for"<<curr->_value<<", i= "<<i<<", flag= "<<boolalpha<<flag <<endl;
                if (flag)
                {
                    //cout<<"Inside flag"<<endl;
                    return;
                }
                if (curr->_left != nullptr)
                {
                    //cout<<"In Left, for: "<<curr->_value<<endl;
                    find_node(i, curr->_left, flag);
                }
                if (i == 0 && !flag)
                {

                    //cout << "Returning -->" << curr->_value << endl;
                    flag = true;
                    //cout<<"Puting "<<curr<<" In "<<iterator::node_ptr<<" root=="<<iterator::root<<endl;
                    iterator::node_ptr = curr;
                    return;
                }
                i--;
                if (curr->_right != nullptr)
                {
                    //cout<<"In Right, for: "<<curr->_value<<endl;
                    find_node(i, curr->_right, flag);
                }
            }

        public:
            int count;
            inOrder_iterator(Node *ptr) : iterator(ptr)
            {
                //cout<<this<<" : In Iterator Cont  "<<boolalpha<<(ptr == nullptr)<<endl;
                if (ptr != nullptr)
                {
                    count = 0;
                    int j = count;
                    bool flag = false;
                    //cout<<" Root is:"<<iterator::root<<endl;
                    find_node(j, iterator::root, flag);
                    //cout<<this<<" : Here after cont find_node(), j="<<j<<"and root is null = "<<(iterator::root==nullptr)<<endl;
                }
            };
            inOrder_iterator operator++(int)
            {
                inOrder_iterator prev_it = *this;
                Node *prev = iterator::node_ptr;
                ////cout << "Inside" << endl;
                count++;
                bool flag = false;
                int j = count;
                find_node(j, iterator::root, flag);
                if (prev == iterator::node_ptr)
                {
                    ////cout << "Returning Null" << endl;
                    iterator::node_ptr = nullptr;
                }
                return prev_it;
            }
            inOrder_iterator operator++()
            {
                Node *prev = iterator::node_ptr;
                //cout<<"prev: "<<prev<<endl;
                ////cout << "Inside" << endl;
                count++;
                bool flag = false;
                int j = count;
                //cout<<this<<" : Everthing Ok1  "<<boolalpha<<(iterator::root == nullptr) << boolalpha<<(iterator::node_ptr == nullptr)<<endl;
                find_node(j, iterator::root, flag);
                if (prev == iterator::node_ptr)
                {
                    //cout << "Returning Null" << endl;
                    iterator::node_ptr = nullptr;
                }
                //cout<<"Everthing Ok1 End"<<endl;
                return *this;
            }
        };
        class preOrder_itertator : public iterator
        {
        private:
            void find_node(int &i, Node *curr, bool &flag)
            {
                if (flag)
                {
                    return;
                }
                if (i == 0 && !flag)
                {
                    flag = true;
                    iterator::node_ptr = curr;
                    return;
                }
                i--;
                if (curr->_left != NULL)
                {
                    find_node(i, curr->_left, flag);
                }
                if (curr->_right != NULL)
                {
                    find_node(i, curr->_right, flag);
                }
            }

        public:
            int i;
            preOrder_itertator(Node *ptr) : iterator(ptr)
            {
                if (ptr != nullptr)
                {
                    i = 0;
                    int j = i;
                    bool flag = false;
                    find_node(j, iterator::root, flag);
                    if (i != 0)
                    {
                        iterator::node_ptr = nullptr;
                    }
                }
            };
            preOrder_itertator operator++(int)
            {
                preOrder_itertator prev_it = *this;
                Node *prev = iterator::node_ptr;
                ////cout << "Inside" << endl;
                i++;
                bool flag = false;
                int j = i;
                find_node(j, iterator::root, flag);
                if (prev == iterator::node_ptr)
                {
                    ////cout << "Returning Null" << endl;
                    iterator::node_ptr = nullptr;
                }
                return prev_it;
            }
            preOrder_itertator operator++()
            {
                Node *prev = iterator::node_ptr;
                ////cout << "Inside" << endl;
                i++;
                bool flag = false;
                int j = i;
                find_node(j, iterator::root, flag);
                if (prev == iterator::node_ptr)
                {
                    ////cout << "Returning Null" << endl;
                    iterator::node_ptr = nullptr;
                }
                return *this;
            }
        };

        class postOrder_iterator : public iterator
        {
        private:
            void find_node(int &i, Node *curr, bool &flag)
            {
                if (flag)
                {
                    return;
                }
                if (curr->_left != NULL)
                {
                    find_node(i, curr->_left, flag);
                }
                if (curr->_right != NULL)
                {
                    find_node(i, curr->_right, flag);
                }
                if (i == 0 && !flag)
                {
                    ////cout << "Returning -->" << curr->_value << endl;
                    flag = true;
                    iterator::node_ptr = curr;
                    return;
                }
                i--;
            }
        public:
            int i;
            postOrder_iterator(Node *ptr) : iterator(ptr)
            {
                if (ptr != nullptr)
                {
                    i = 0;
                    int j = i;
                    bool flag = false;
                    find_node(j, iterator::root, flag);
                    if (i != 0)
                    {
                        iterator::node_ptr = nullptr;
                    }
                }
            };
            postOrder_iterator operator++(int)
            {
                postOrder_iterator prev_it = *this;
                Node *prev = iterator::node_ptr;
                ////cout << "Inside" << endl;
                i++;
                bool flag = false;
                int j = i;
                find_node(j, iterator::root, flag);
                if (prev == iterator::node_ptr)
                {
                    ////cout << "Returning Null" << endl;
                    iterator::node_ptr = nullptr;
                }
                return prev_it;
            }
            postOrder_iterator operator++()
            {
                Node *prev = iterator::node_ptr;
                ////cout << "Inside" << endl;
                i++;
                bool flag = false;
                int j = i;
                find_node(j, iterator::root, flag);
                if (prev == iterator::node_ptr)
                {
                    ////cout << "Returning Null" << endl;
                    iterator::node_ptr = nullptr;
                }
                return *this;
            }
        };
        inOrder_iterator begin()
        {
            return inOrder_iterator(_root);
        }
        inOrder_iterator end()
        {
            return inOrder_iterator(nullptr);
        }
        preOrder_itertator begin_preorder()
        {
            return preOrder_itertator(_root);
        }
        preOrder_itertator end_preorder()
        {
            return preOrder_itertator(nullptr);
        }
        inOrder_iterator begin_inorder()
        {
            return inOrder_iterator(_root);
        }
        inOrder_iterator end_inorder()
        {
            return inOrder_iterator(nullptr);
        }
        postOrder_iterator begin_postorder()
        {
            return postOrder_iterator(_root);
        }
        postOrder_iterator end_postorder()
        {
            return postOrder_iterator(nullptr);
        }
    };
}