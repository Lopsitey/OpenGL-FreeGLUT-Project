#include "LinkedLists.h"

LinkedLists::LinkedLists()
{
}

LinkedLists::~LinkedLists()
{
}

LinkedLists::ListNode* LinkedLists::MakeNode(ListNode** head, SceneObject* data)
{
    // Create a new node
    auto newNode = new ListNode;
    ListNode* last = *head;

    //Pass in the data
    newNode->data = data;
    newNode->next = nullptr;

    if (*head == nullptr)
    {
        *head = newNode;
        return newNode;
    }
    // Traverse to the end of the list
    while (last->next != nullptr)
    {
        last = last->next;
    }
    last->next = newNode;
    return newNode;
}

LinkedLists::ListNode* LinkedLists::InsertFirst(ListNode** head, SceneObject* data)
{
    // Insert a new node at the beginning of the list
    auto newNode = new ListNode;

    newNode->data = data; //data is passed in
    newNode->next = *head; //assigns the head to the next node
    *head = newNode; //moves the head to the front

    return newNode;
}

void LinkedLists::InsertAfter(ListNode* lastNode, SceneObject* data)
{
    // Insert a new node after the given node
    if (lastNode == nullptr)
    {
        std::cout << "The given previous node cannot be NULL" << std::endl;
        return;
    }
    auto newNode = new ListNode;
    newNode->data = data;
    newNode->next = lastNode->next; //sets the node after the new node to the node after the last node
    lastNode->next = newNode; //sets the new node to the last node (node after old last node)
}

void LinkedLists::DeleteList(ListNode** node)
{
    //Deletes the entire list
    ListNode* prev = *node;
    ListNode* next;

    while (prev != nullptr)
    {
        next = prev->next; //sets next to the next node
        delete prev; //deletes the previous node
        prev = next; //moves to the next node
    }
    *node = nullptr; //sets the head to null
}

void LinkedLists::DeleteAfter(ListNode* node)
{
    // Delete the node after the given node
    ListNode* nexTemp;
    if (node != nullptr && node->next != nullptr)
    {
        nexTemp = node->next; //stores the next node
        node->next = nexTemp->next; //sets the current node's next node 1 space ahead
        delete nexTemp; //deletes the old next node
    }
}

LinkedLists::ListNode* LinkedLists::GetNode(ListNode* node, int pos)
{
    // Get the node at the specified position
    int count = 0;
    while (node != nullptr)
    {
        if (count == pos) //if the position has been reached
        {
            std::cout << "Data stored at position " << pos << "is: " << node->data << '\n';
            return node;
        }
        ++count;
        node = node->next; //iterates through the list
    }
    std::cout << "Position not found" << '\n';
    return nullptr;
}

LinkedLists::ListNode* LinkedLists::Find(ListNode* node, SceneObject* val)
{
    //The list is searched in a linear fashion until the specified value is reached
    while (node != nullptr)
    {
        if (node->data == val)
        {
            std::cout << "Data found: " << node->data << '\n';
            return node;
        }
        node = node->next;
    }
    return nullptr;
}

void LinkedLists::PrintList(ListNode* node)
{
    // Print the entire list
    while (node != nullptr)
    {
        //setw ensures that the width of the string is of a minimum of 5 chars
        std::cout << std::setw(5) << "|" << node->data << "|-->";
        node = node->next; //iterates throught the list, printing every node 
    }
    if (node == nullptr) //null validation
    {
        std::cout << "| NULL |" << '\n';
    }
    std::cout << '\n';
}

void LinkedLists::DeleteNode(ListNode* node, SceneObject* val)
{
    //The list is searched in a linear fashion until the specified value is reached
    while (node != nullptr)
    {
        if (node->data == val)
            delete node;
        node = node->next;
    }
}

void LinkedLists::PrintListBackwards(ListNode* node)
{
    //Print the entire list backwards
    if (node != nullptr)
    {
        PrintListBackwards(node->next);
        std::cout << std::setw(5) << "|" << node->data << "|-->";
    }
}

void LinkedLists::PrintLastElement(ListNode* node)
{
    if (node == nullptr) //stops if the node is null
    {
        std::cout << "No last element found" << '\n';
        return;
    }
    if (node->next == nullptr) //checks if your at the end of the list
    {
        std::cout << "Last element is: " << node->data << '\n';
        return;
    }
    PrintLastElement(node->next); //iterates if not at the end of the list
}
