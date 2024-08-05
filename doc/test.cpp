// 单链表
// 1 -  3 - 2 - 3 - 3 -4 -5- 5 -6-8-7

#include <iostream>
using namespace std;
typedef struct Node {
    int val;
    struct Node *next;
    Node(int v) {val = v;}
} Node;

void print(Node *node)
{
    // 打印
    Node *iter = node;
    while (iter) {
        cout << iter->val << endl;
        iter = iter->next;
    }
}

Node *solve(Node *node)
{
    // 避免头部链表重复风复杂处理直接空的头指针
    Node *empty_head = new Node(-999999);
    empty_head->next = node;
    Node *prev_p = empty_head, *prev = empty_head->next, *next = empty_head->next->next;

    while (next) {
        int should_move_index = 0;
        // 有重复清理重复直到不重复，前后指针向后移
        cout << "p_prev : " << prev_p->val << ":" << prev->val << "," << next->val << endl;
        while (prev && next && prev->val == next->val) {
            should_move_index = 1;
            next = next->next;
        }
        if (should_move_index) {
            // 清理无用节点内存
            while (prev != next) {
                Node *tmp = prev;
                prev = prev->next;
                free(tmp);
            }
            cout << "next->val : " << next->val << endl;
            prev_p->next = next;
            should_move_index = 0;
        }
        // 无重复，只偏移指针
        if (prev_p)
            prev_p = prev_p->next;
        if (prev)
            prev = prev->next;
        if (next)
            next = next->next;
    }
    return empty_head->next;
}

int main()
{
    // 初始化
    Node *node = new Node(1);
    Node *iter = node;
    Node *tmp_node = new Node(3);
    iter->next = tmp_node;
    iter = tmp_node;
    tmp_node = new Node(2);
    iter->next = tmp_node;
    iter = tmp_node;
    tmp_node = new Node(2);
    iter->next = tmp_node;
    iter = tmp_node;
    tmp_node = new Node(4);
    iter->next = tmp_node;
    iter = tmp_node;
    
    print(node);
    cout << "res : =============>" << endl;

    // 测试 1 3 2 2 4
    Node *res = solve(node);
    print(res);
    
}

