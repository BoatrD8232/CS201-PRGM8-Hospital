#include "Queue.h"

Queue::Queue() {
    head = NULL;
    tail = NULL;
    num_items = 0;
}

bool Queue::empty() {
    if (num_items == 0) {
        return true;
    }
    return false;
}

const Node* Queue::front() {
    return head;
}

const Node* Queue::back() {
    return tail;
}

void Queue::push_front(const Patient& data) {
    Node* newHead = new Node(data);
    // If list is not empty
    if (!empty()) {
        newHead->next = head;
        head = newHead;
    }
    else {
        head = newHead;
        tail = newHead;
    }
    ++num_items;
}

void Queue::push_back(const Patient& data) {
    Node* newTail = new Node(data);
    // If list is not empty
    if (!empty()) {
        tail->next = newTail;
        tail = newTail;
    }
    else {
        head = newTail;
        tail = newTail;
    }
    ++num_items;
}

void Queue::pop_front() {
    if (empty()) {
        cout << "Queue is empty, cannot remove." << endl;
        return;
    }
    Node* nodeToDelete = head;
    // If the head is the only member in the list.
    if (head->next == NULL) {
        head = NULL;
        tail = NULL;
    }
    else {
        head = head->next;
    }
    delete nodeToDelete;
    --num_items;
}

void Queue::pop_back() {
    if (empty()) {
        cout << "Queue is empty, cannot remove." << endl;
        return;
    }
    Node* nodeToDelete = tail;
    // If the tail is the only member in the list.
    if (num_items == 1) {
        head = NULL;
        tail = NULL;
    }
    else {
        Node* currNode = head;
        // Loops to the new end of the list to change its next pointer to null.
        for (int i = 0; i < num_items - 2; ++i) {
            currNode = currNode->next;
        }
        currNode->next = NULL;
        tail = currNode;
    }
    delete nodeToDelete;
    --num_items;
}

bool Queue::insert(const Patient& data) {
    //If queue is full.
    if (num_items >= 10) {
        return false;
    }
    //If the patient is critical, must add them in the right spot.
    if (data.isCrit) {
        //If there are no other crititcal patients, add to the front.
        if (empty() || !head->data.isCrit) {
            push_front(data);
        }
        else {
            Node* currNode = head;
            //Find the spot that the patient should be added
            while (currNode->next != NULL && currNode->next->data.isCrit) {
                currNode = currNode->next;
            }
            currNode->next = new Node(data, currNode->next);
            num_items++;
        }
    }
    //If patient is not critical, can just be added to end of queue.
    else {
        push_back(data);
    }
    return true;
}

pair<bool, string> Queue::remove(int num) {
    pair<bool, string> result;
    string name;
    // If the target is the head.
    if (head->data.SSN == num) {
        name = head->data.fName + " " + head->data.lName;
        pop_front();
        result.first = true;
        result.second = name;
    }
    // If the target is the tail.
    else if (tail->data.SSN == num) {
        name = tail->data.fName + " " + tail->data.lName;
        pop_back();
        result.first = true;
        result.second = name;
    }
    else {
        Node* currNode = head;
        // Loops to find the node before the target, so that its next member can be reassigned to the node formerly 2 in front of it.
        while (currNode->next != NULL && currNode->next->data.SSN != num) {
            currNode = currNode->next;
        }
        //If the patient is found.
        if (currNode->next != NULL) {
            Node* nodeToBeDeleted = currNode->next;
            currNode->next = currNode->next->next;
            name = nodeToBeDeleted->data.fName + " " + nodeToBeDeleted->data.lName;
            delete nodeToBeDeleted;
            result.first = true;
            result.second = name;
            --num_items;
        }
        else {
            result.first = false;
            result.second = "";
            return result;
        }
    }
    return result;
}

void Queue::print() {
    cout << setw(10) << setfill('-') << "" << "Patient List" << setw(10) << "" << endl;
    Node* currentNode = head;
    cout << setfill(' ') << left;
    for (int i = 0; i < num_items; i++) {
        cout << setw(10) << currentNode->data.fName << setw(15) << currentNode->data.lName << setw(10) << currentNode->data.SSN;
        if (currentNode->data.isCrit) {
            cout << setw(5) << 'C';
        }
        else {
            cout << setw(5) << 'R';
        }
        cout << endl;
        currentNode = currentNode->next;
    }
    cout << setw(33) << "" << endl;
}