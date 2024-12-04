#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;
#pragma once

/*
    PRE- Takes in a first name, last name, SSN and critical status.
    POST- Uses the information to makes a patient.
*/
struct Patient {
    string fName;
    string lName;
    int SSN;
    bool isCrit;
    Patient(string infN = "", string inlN = "", int inSSN = -1, bool inCrit = false) : fName(infN), lName(inlN), SSN(inSSN), isCrit(inCrit) {}
};

/*
    PRE- Takes in a patient and a next pointer.
    POST- Makes a node of a singly linked list with the data.
*/
struct Node {
    Patient data;
    Node* next;
    Node(const Patient& data_item, Node* next_ptr = NULL) :data(data_item), next(next_ptr) {}
};

/*
    Defines the queue used by the clinic to stores patients.
*/
class Queue {
private:
    Node* head;
    Node* tail;
    int num_items;
public:
    Queue();
    /*
        PRE- Checks if the queue is empty.
        POST- returns true if empty, false otherwise.
    */
    bool empty();
    /*
        PRE- Gets the current head node.
        POST- Returns a pointer to the current head node.
    */
    const Node* front();
    /*
        PRE- Gets the current tail node.
        POST- Returns a pointer to the current tail node.
    */
    const Node* back();
    /*
        PRE- Takes in a patient to be added.
        POST- Adds the patient to the front of the queue.
    */
    void push_front(const Patient& data);
    /*
        PRE- Takes in a patient to be added
        POST- Adds a patient to the end of the queue.
    */
    void push_back(const Patient& data);
    /*
        PRE- Takes in no arguments, checks if the list is empty.
        POST- Removes the node at the front of the list.
    */
    void pop_front();
    /*
        PRE- Takes no arguments.
        POST- Removes the node at the end of the list.
    */
    void pop_back();
    /*
        PRE- Takes in a patient to insert.
        POST- Adds the patient at the appropriate place in the queue based on priority. Returns true if insertion was successful.
    */
    bool insert(const Patient& data);
    /*
        PRE- Takes in the SSN of the patient to remove
        POST- Removes the patient, if found. Returns a pair that stores true if removal is successful and the full name of the removed patient.
    */
    pair<bool, string> remove(int num);
    /*
        PRE- No arguments, merely prints the queue.
        POST- Prints the contents of the queue.
    */
    void print();
};