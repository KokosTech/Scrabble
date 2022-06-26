#include <iostream>
#include <string>
#include <algorithm>

class Map
{
private:
    Map *iterator(int key)
    {
        Map *temp = root;

        while (temp != nullptr &&
               temp->key != key)
        {

            if (key < temp->key)
            {
                temp = temp->left;
            }

            else
            {
                temp = temp->right;
            }
        }
        return temp;
    }

    const Map *iterator(int key) const
    {
        Map *temp = root;
        while (temp != nullptr && temp->key != key)
        {
            if (key < temp->key)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return temp;
    }

    const std::string search(int key) const
    {
        const Map *temp = iterator(key);
        if (temp != nullptr)
        {
            return temp->value;
        }
        return 0;
    }

    Map *create(int key)
    {
        Map *newnode = (Map *)malloc(sizeof(Map));
        newnode->key = key;
        newnode->value = "";
        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->par = nullptr;

        newnode->depth = 1;
        return newnode;
    }

    void right_rotation(Map *x)
    {
        Map *y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
        {
            y->right->par = x;
        }
        if (x->par != nullptr && x->par->right == x)
        {
            x->par->right = y;
        }
        else if (x->par != nullptr && x->par->left == x)
        {
            x->par->left = y;
        }
        y->par = x->par;
        y->right = x;
        x->par = y;
    }

    void left_rotation(Map *x)
    {
        Map *y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
        {
            y->left->par = x;
        }
        if (x->par != nullptr && x->par->left == x)
        {
            x->par->left = y;
        }
        else if (x->par != nullptr && x->par->right == x)
        {
            x->par->right = y;
        }
        y->par = x->par;
        y->left = x;
        x->par = y;
    }

    void helper(Map *node)
    {
        if (depthf(node->left) - depthf(node->right) > 1)
        {

            if (depthf(node->left->left) > depthf(node->left->right))
            {
                node->depth = std::max(depthf(node->right) + 1,
                                       depthf(node->left->right) + 1);
                node->left->depth = std::max(depthf(node->left->left) + 1,
                                             depthf(node) + 1);
                right_rotation(node);
            }

            else
            {
                node->left->depth = std::max(
                    depthf(node->left->left) + 1,
                    depthf(node->left->right->left) + 1);
                node->depth = std::max(depthf(node->right) + 1,
                                       depthf(node->left->right->right) + 1);
                node->left->right->depth = std::max(depthf(node) + 1,
                                                    depthf(node->left) + 1);
                left_rotation(node->left);
                right_rotation(node);
            }
        }

        else if (depthf(node->left) - depthf(node->right) < -1)
        {

            if (depthf(node->right->right) > depthf(node->right->left))
            {
                node->depth = std::max(depthf(node->left) + 1,
                                       depthf(node->right->left) + 1);
                node->right->depth = std::max(depthf(node->right->right) + 1,
                                              depthf(node) + 1);
                left_rotation(node);
            }

            else
            {
                node->right->depth = std::max(
                    depthf(node->right->right) + 1,
                    depthf(node->right->left->right) + 1);
                node->depth = std::max(
                    depthf(node->left) + 1,
                    depthf(node->right->left->left) + 1);
                node->right->left->depth = std::max(depthf(node) + 1,
                                                    depthf(node->right) + 1);
                right_rotation(node->right);
                left_rotation(node);
            }
        }
    }

    void balance(Map *node)
    {
        while (node != root)
        {
            int d = node->depth;
            node = node->par;
            if (node->depth < d + 1)
            {
                node->depth = d + 1;
            }
            if (node == root && depthf(node->left) - depthf(node->right) > 1)
            {
                if (depthf(node->left->left) > depthf(node->left->right))
                {
                    root = node->left;
                }
                else
                {
                    root = node->left->right;
                }
                helper(node);
                break;
            }
            else if (node == root && depthf(node->left) - depthf(node->right) < -1)
            {
                if (depthf(node->right->right) > depthf(node->right->left))
                {
                    root = node->right;
                }
                else
                {
                    root = node->right->left;
                }
                helper(node);
                break;
            }
            helper(node);
        }
    }

    int depthf(Map *node)
    {
        if (node == nullptr)

            return 0;
        return node->depth;
    }

    Map *insert(int key)
    {
        cnt++;
        Map *newnode = create(key);
        if (root == nullptr)
        {
            root = newnode;
            return root;
        }
        Map *temp = root, *prev = nullptr;
        while (temp != nullptr)
        {
            prev = temp;
            if (key < temp->key)
            {
                temp = temp->left;
            }
            else if (key > temp->key)
            {
                temp = temp->right;
            }
            else
            {
                free(newnode);
                cnt--;
                return temp;
            }
        }
        if (key < prev->key)
        {
            prev->left = newnode;
        }
        else
        {
            prev->right = newnode;
        }
        newnode->par = prev;
        balance(newnode);
        return newnode;
    }

    Map *inorderPredecessor(Map *head)
    {
        if (head == nullptr)
            return head;
        while (head->right != nullptr)
        {
            head = head->right;
        }
        return head;
    }

    Map *inorderSuccessor(Map *head)
    {
        if (head == nullptr)
            return head;
        while (head->left != nullptr)
        {
            head = head->left;
        }
        return head;
    }

public:
    static class Map *root;
    static int cnt;

    Map *left, *right, *par;
    int key, depth;
    std::string value;

    std::string operator[](int key)
    {
        return insert(key)->value;
    }

    const std::string operator[](int key) const
    {
        return search(key);
    }

    int count(int key)
    {
        Map *temp = iterator(key);
        if (temp != nullptr)
        {
            return 1;
        }
        return 0;
    }

    int size(void)
    {
        return cnt;
    }

    void erase(int key, Map *temp = root)
    {
        Map *prev = nullptr;
        cnt--;
        while (temp != nullptr &&
               temp->key != key)
        {
            prev = temp;
            if (key < temp->key)
            {
                temp = temp->left;
            }
            else if (key > temp->key)
            {
                temp = temp->right;
            }
        }
        if (temp == nullptr)
        {
            cnt++;
            return;
        }
        if (cnt == 0 && temp == root)
        {
            free(temp);
            root = nullptr;
            return;
        }
        Map *l = inorderPredecessor(temp->left);
        Map *r = inorderSuccessor(temp->right);
        if (l == nullptr && r == nullptr)
        {
            if (prev == nullptr)
            {
                root = nullptr;
            }
            else
            {
                if (prev->left == temp)
                {
                    prev->left = nullptr;
                }
                else
                {
                    prev->right = nullptr;
                }
                free(temp);
                balance(prev);
            }
            return;
        }
        Map *start;
        if (l != nullptr)
        {
            if (l == temp->left)
            {
                l->right = temp->right;
                if (l->right != nullptr)
                {
                    l->right->par = l;
                }
                start = l;
            }
            else
            {
                if (l->left != nullptr)
                {
                    l->left->par = l->par;
                }
                start = l->par;
                l->par->right = l->left;
                l->right = temp->right;
                l->par = nullptr;
                if (l->right != nullptr)
                {
                    l->right->par = l;
                }
                l->left = temp->left;
                temp->left->par = l;
            }
            if (prev == nullptr)
            {
                root = l;
            }
            else
            {
                if (prev->left == temp)
                {
                    prev->left = l;
                    l->par = prev;
                }
                else
                {
                    prev->right = l;
                    l->par = prev;
                }
                free(temp);
            }
            balance(start);
            return;
        }
        else
        {
            if (r == temp->right)
            {
                r->left = temp->left;
                if (r->left != nullptr)
                {
                    r->left->par = r;
                }
                start = r;
            }
            else
            {
                if (r->right != nullptr)
                {
                    r->right->par = r->par;
                }
                start = r->par;
                r->par->left = r->right;
                r->left = temp->left;
                r->par = nullptr;
                if (r->left != nullptr)
                {
                    r->left->par = r;
                }
                r->right = temp->right;
                temp->right->par = r;
            }
            if (prev == nullptr)
            {
                root = r;
            }
            else
            {
                if (prev->right == temp)
                {
                    prev->right = r;
                    r->par = prev;
                }
                else
                {
                    prev->left = r;
                    r->par = prev;
                }
                free(temp);
            }
            balance(start);
            return;
        }
    }

    bool empty(void)
    {
        if (root == nullptr)
            return true;
        return false;
    }

    void update(int key, int value)
    {
        Map *temp = iterator(key);
        if (temp != nullptr)
        {
            temp->value = value;
        }
    }

    void clear(void)
    {
        while (root != nullptr)
        {
            erase(root->key);
        }
    }

    void iterate(Map *head = root)
    {
        if (root == nullptr)
            return;
        if (head->left != nullptr)
        {
            iterate(head->left);
        }
        if (head->right != nullptr)
        {
            iterate(head->right);
        }
    }

    Map *find(int key)
    {
        return iterator(key);
    }

    void insert(int key, int value)
    {
        Map *temp = iterator(key);
        if (temp == nullptr)
        {
            insert(key)->value = value;
        }
        else
        {
            temp->value = value;
        }
    }
};

Map *Map::root = nullptr;
int Map::cnt = 0;
