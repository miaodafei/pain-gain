#include<stdio.h>
//#include<stdlib.h>
// 1 - 2 - 2 - 3 - 4 -5
typedef struct Node
{
    int val;
    struct Node *next;
} node;

void myprint(node *head)
{
    node *iter = head;
    while (iter) {
        printf(" %d ", iter->val);
        iter = iter->next;
    }
    printf("\n");
}

node *solve(node *head)
{
    // empty head
    node res;
    res.next = head;

    node *p_prev = &res, *prev = head, *next = head->next;
    while (next) {
        int should_erase = 0;
        // 查重并且偏移next指针
        while (prev && next && prev->val == next->val) {
            should_erase = 1;
            next = next->next;
        }
        printf("%d\n", next->val);
        // 删除并且偏移到不重复地址
        if (should_erase) {
            p_prev->next = next;
            should_erase = 0;
        }
        if (p_prev)
            p_prev = p_prev->next;
        if (next)
            prev = prev->next;
        if (next)
            next = next->next;
    }
    return res.next; 
}

int main(void) {
    // init 1 - 2 - 2 - 3
    node *head = malloc(sizeof(node));
    node *iter = head;
    iter->val = 1;
    node *tmp_node = malloc(sizeof(node));
    tmp_node->val = 2;
    iter->next = tmp_node;
    iter = iter->next;
    tmp_node = malloc(sizeof(node));
    tmp_node->val = 2;
    iter->next = tmp_node;
    iter = iter->next;
    tmp_node = malloc(sizeof(node));
    tmp_node->val = 3;
    iter->next = tmp_node;

    myprint(head);

    // solve
    //node *res = solve(head);
    printf("after =======>\n");
    // res
    myprint(head);
    
    return 0;
}