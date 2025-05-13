#pragma once
#include "Structures.h"
#include <iostream>
#include "iomanip"
#include "SceneObject.h"

class LinkedLists
{
public:
    struct ListNode
    {
        SceneObject* data;
        ListNode* next;
    };

    LinkedLists();
    ~LinkedLists();

    //It needs to e a pointer to a pointer because of the dynamic memory allocation
    ListNode* MakeNode(ListNode** head, SceneObject* data);
    //It being a pointer to a pointer makes it easeier to access the list
    ListNode* InsertFirst(ListNode** head, SceneObject* data);
    void InsertAfter(ListNode* lastNode, SceneObject* data);

    void DeleteList(ListNode** node);
    void DeleteAfter(ListNode* node);
    void DeleteNode(ListNode* node, SceneObject* val);

    ListNode* GetNode(ListNode* node, int pos);
    ListNode* Find(ListNode* node, SceneObject* val);

    void PrintList(ListNode* node);
    void PrintListBackwards(ListNode* node);
    void PrintLastElement(ListNode* node);

private:
    ListNode* head = nullptr;
};
