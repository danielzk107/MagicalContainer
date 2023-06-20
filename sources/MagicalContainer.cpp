#include "MagicalContainer.hpp"
#include <ostream>
#include <iostream>
using namespace std;
using namespace ariel;

bool Node::isPrime(int num)
{
    for (int i = 2; i < num / 2; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool Node::operator==(Node other)
{
    return this == &other;
}

bool Node::operator<(Node other)
{
    return num < other.num;
}
bool Node::operator>(Node other)
{
    return num > other.num;
}

void Node::print()
{
    cout << "Value = " << num << ", isPrime = " << isprime << ", nextCross = " << nextCross  << ", CrossIndex = " << crossIndex << endl;
}

Node::Node(int num)
{
    this->num = num;
    isprime = isPrime(num);
    nextAsc = NULL;
    nextCross = NULL;
    nextPrime = NULL;
    prevCross = NULL;
    prevAsc = NULL;
    prevPrime = NULL;
}

Node::Node(int num, Node *prevAsc, Node *asc, Node *prevCross, Node *cross, Node *prevPrime, Node *prime)
{
    this->num = num;
    isprime = isPrime(num);
    nextAsc = asc;
    nextCross = cross;
    nextPrime = prime;
    this->prevCross = prevCross;
    this->prevAsc = prevAsc;
    this->prevPrime = prevPrime;
}

Node::~Node()
{
}

MagicalContainer::MagicalContainer()
{
    num_of_elements = 0;
    firstAsc = NULL;
    lastAsc = NULL;
    firstCross = NULL;
    firstCross = NULL;
    firstPrime = NULL;
    firstPrime = NULL;
}

MagicalContainer::~MagicalContainer()
{
    while (firstAsc != NULL)
    {
        Node *temp = firstAsc;
        firstAsc = firstAsc->nextAsc; // No need to go through the other pointers as they are all of nodes in this order
        // free(temp);
    }
}

Node *MagicalContainer::getFirstAsc()
{
    return firstAsc;
}

Node *MagicalContainer::getLastAsc()
{
    return lastAsc;
}

Node *MagicalContainer::getfirstPrime()
{
    return firstPrime;
}

Node *MagicalContainer::getLastPrime()
{
    return lastPrime;
}

Node *MagicalContainer::getfirstCross()
{
    return firstCross;
}

Node *MagicalContainer::getLastCross()
{
    return lastCross;
}

int MagicalContainer::size()
{
    return num_of_elements;
}

// ADDITION AND REMOVAL OF ELEMENTS:

void MagicalContainer::addElement(int num)
{
    // First, we must check if the number already exists within our container:
    Node *temp = firstAsc;
    while (firstAsc != NULL)
    {
        if (firstAsc->num == num)
        {
            firstAsc = temp;
            cout << num << " already exists within this container" << endl;
            throw this;
        }
        if (firstAsc->num > num)
        { // The new number is not in our list
            break;
        }
        firstAsc = firstAsc->nextAsc;
    }
    firstAsc = temp;
    // Case of first insert:
    Node *newNum = new Node(num, NULL, NULL, NULL, NULL, NULL, NULL);
    if (num_of_elements == 0)
    {
        newNum->crossIndex = 1;
        firstAsc = newNum;
        lastAsc = new Node(-1, firstAsc, NULL, NULL, NULL, NULL, NULL);
        firstCross = newNum;
        lastCross = new Node(-1, NULL, NULL, firstCross, NULL, NULL, NULL);
        if (newNum->isprime)
        {
            firstPrime = newNum;
            lastPrime = new Node(-1, NULL, NULL, NULL, NULL, firstPrime, NULL);
        }
    }
    else
    {
        // Insert newNum in an arbitrary position that will be fixed in our helper functions.
        // The new node will be in the second position in the ascending order, so we first correct our prime and cross storages and only then the ascending order.
        // We do this in order to keep the new node in storage but not transfer it as a paramater to each helper function (This also avoids a lot of mess in our helper functions).
        newNum->nextAsc = firstAsc->nextAsc;
        firstAsc->nextAsc = newNum;
        if (newNum->isprime)
        {
            UpdatePrime();
        }
        UpdateCross();
        UpdateAsc();
    }
    num_of_elements++;
}

bool MagicalContainer::removeElement(int num)
{
    // We remove the element from the list (and from everything that may point to it), add a temporary node with -1 value as the second ascending node, and call UpdateCross() to update our cross order.
    // We will use the temporary node to signal to our UpdateCross() function whether an element is being added or removed.
    bool found = false;
    Node *toRemove;
    // Check for the case of removing the first number:
    if (firstAsc->num == num)
    {
        toRemove = firstAsc;
        if (toRemove->nextCross != NULL)
        {
            toRemove->nextCross->prevCross = NULL;
        }
        firstAsc = firstAsc->nextAsc;
        UpdateCross();
        found = true;
    }
    Node *temp = firstAsc;
    while (firstAsc != NULL && !found)
    {
        if (firstAsc->num > num) // The element cannot be in our container
        {
            firstAsc = temp;
            throw this;
        }
        if (firstAsc->nextAsc != NULL && firstAsc->nextAsc->num == num)
        { // We have found our element. Now we need to handle it.
            toRemove = firstAsc->nextAsc;
            firstAsc->nextAsc = toRemove->nextAsc;
            found = true;
            if (toRemove->nextAsc != NULL)
            {
                toRemove->nextAsc->prevAsc = firstAsc;
            }
            if (toRemove->nextCross != NULL)
            {
                toRemove->nextCross->prevCross = NULL;
            }
            if (toRemove->prevCross != NULL)
            {
                toRemove->prevCross->nextCross = NULL;
            }
            firstAsc = temp;
            firstAsc->nextAsc = new Node(-1, firstAsc, firstAsc->nextAsc, NULL, NULL, NULL, NULL); // This node signals the updateCross function to work in removal "mode", where it takes out the second node but does not insert it back.
            UpdateCross();
        }
        firstAsc = firstAsc->nextAsc;
    }
    firstAsc = temp;
    if (!found)
    {
        throw this;
    }
    // Deleting the temporary node
    Node* tempForCross = firstAsc->nextAsc;
    firstAsc->nextAsc = tempForCross->nextAsc;
    free(tempForCross);
    // Fix prime pointers if the removed element was prime:
    if (toRemove->isprime)
    {
        if (firstPrime == toRemove)
        {
            firstPrime = firstPrime->nextPrime;
        }
        else
        {
            temp = firstPrime;
            while (firstPrime != NULL)
            {
                if (firstPrime->nextPrime != NULL && firstPrime->nextPrime == toRemove)
                {
                    firstPrime->nextPrime = toRemove->nextPrime;
                    break;
                }
            }
            firstPrime = temp;
        }
    }
    free(toRemove);
    num_of_elements--;
    return true;
}

// HELPER FUNCTIONS FOR PREVIOUS TWO FUNCTIONS:

void MagicalContainer::UpdatePrime()
{
    if (firstPrime == NULL)
    {
        firstPrime = firstAsc->nextAsc;
        lastPrime = new Node(-1, NULL, NULL, NULL, NULL, firstPrime, NULL);
        return;
    }
    free(lastPrime); // Freeing the node as we assign it again in this function.
    bool found = false;
    Node *newNum = firstAsc->nextAsc;
    if (*newNum < *firstPrime)
    {
        newNum->nextPrime = firstPrime;
        firstPrime->prevPrime = newNum;
        firstPrime = newNum;
        found = true;
    }
    Node *temp = firstPrime;
    while (firstPrime != NULL && firstPrime->num != -1)
    {
        if (*firstPrime > *newNum && !found)
        {
            newNum->nextPrime = firstPrime;
            newNum->prevPrime = firstPrime->prevPrime;
            firstPrime->prevPrime->nextPrime = newNum; // We know firstPrime->prevAsc != NULL
            firstPrime->prevPrime = newNum;
            firstPrime = newNum;
            found = true;
        }
        if (*firstPrime < *newNum && (firstPrime->nextPrime == NULL || firstPrime->nextPrime > newNum) && !found)
        {
            newNum->nextPrime = firstPrime->nextPrime;
            firstPrime->nextPrime = newNum;
            newNum->prevPrime = firstPrime;
            found = true;
        }
        if (firstPrime->nextPrime == NULL)
        {
            lastPrime = new Node(-1, NULL, NULL, NULL, NULL, firstPrime, NULL);
            firstPrime->nextPrime = lastPrime;
            firstPrime = temp;
            break;
        }
        firstPrime = firstPrime->nextPrime;
    }
    firstPrime = temp;
}

void MagicalContainer::UpdateCross()
{
    // In this function, we split our 'list' to two and fix the cross order (according to order of entry and not ascending).
    Node *firstHalf = NULL;
    Node *secondHalf = NULL;
    Node *newNum = firstAsc->nextAsc;
    if (firstCross->nextCross == NULL)
    { // There are only two elements including our newest entry, so we put it next
        firstCross->nextCross = newNum;
        newNum->prevCross = firstCross;
        lastCross = newNum;
        return;
    }

    // Notice that our newest entry would always be at the second place, as it is the last in the 'list' according to entry order
    // This means that we simply construct our two lists, add our newest entry at the top of our second list, and reconstruct our cross order.
    int index = 0; // We use this index to determine which list we should put the current element into.
    Node *temp = firstCross;
    firstCross = firstCross->nextCross; // We skip the first element as it will always be first in the list (as it is chronological)
    while (firstCross != NULL)
    {
        if (index % 2 == 1)
        { // Element should go to first list
            if (firstHalf == NULL)
            {
                firstHalf = firstCross;
            }
            else
            {
                firstHalf->nextCross = firstCross;
                firstHalf = firstHalf->nextCross;
            }
        }
        else
        {
            if (secondHalf == NULL)
            {
                secondHalf = firstCross;
            }
            else
            {
                // secondHalf->nextCross = firstCross;
                firstCross->prevCross = secondHalf;
                secondHalf = firstCross;
            }
        }
        firstCross = firstCross->nextCross;
        index++;
    }
    firstCross = temp;
    firstHalf = firstCross;
    if (newNum->num != -1)
    {
        newNum->prevCross = secondHalf;
        secondHalf = newNum;
    }
    Node *secondTemp = secondHalf;
    for (int i = 0; i < index + 1; i++)
    {
        if (i % 2 == 0)
        {
            if (firstHalf != NULL)
            {
                firstCross->nextCross = firstHalf;
                firstHalf->prevCross = firstCross;
                firstCross = firstCross->nextCross;
                firstHalf = firstHalf->nextCross;
            }
        }
        else
        {
            if (secondHalf != NULL)
            {
                firstCross->nextCross = secondHalf;
                secondHalf->prevCross = firstCross;
                secondHalf = secondHalf->nextCross;
            }
        }
        firstCross->crossIndex = i;
        if (firstCross->nextCross == NULL)
        {
            lastCross = firstCross;
            firstCross = temp;
            return;
        }
        firstCross = firstCross->nextCross;
    }
    firstCross = temp;
}

void MagicalContainer::UpdateAsc()
{
    // We 'extract' the new element from our list and find its appropriate place in the order.
    Node *newNum = firstAsc->nextAsc;
    firstAsc->nextAsc = newNum->nextAsc;
    bool found = false;
    // Checking if the new entry is smaller than the current smallest number:
    if (*newNum < *firstAsc)
    {
        newNum->nextAsc = firstAsc;
        firstAsc->prevAsc = newNum;
        firstAsc = newNum;
        found = true;
    }
    Node *temp = firstAsc;
    while (firstAsc != NULL)
    {
        if (*firstAsc > *newNum && !found)
        {
            newNum->nextAsc = firstAsc;
            newNum->prevAsc = firstAsc->prevAsc;
            firstAsc->prevAsc->nextAsc = newNum; // We know firstAsc->prevAsc != NULL
            firstAsc->prevAsc = newNum;
            firstAsc = newNum;
            found = true;
        }
        if (*firstAsc < *newNum && (firstAsc->nextAsc == NULL || firstAsc->nextAsc > newNum) && !found)
        {
            newNum->nextAsc = firstAsc->nextAsc;
            firstAsc->nextAsc = newNum;
            found = true;
        }
        if (firstAsc->nextAsc == NULL)
        {
            lastAsc = firstAsc;
        }
        firstAsc = firstAsc->nextAsc;
    }
    firstAsc = temp;
}

// Print functions:

void MagicalContainer::PrintAsc()
{
    Node *temp = firstAsc;
    cout << "Ascending order:" << endl;
    while (firstAsc)
    {
        firstAsc->print();
        firstAsc = firstAsc->nextAsc;
    }
    firstAsc = temp;
    cout << firstAsc->num << endl;
}

void MagicalContainer::PrintPrime()
{
    Node *temp = firstPrime;
    cout << "Prime order:" << endl;
    while (firstPrime && firstPrime->num != -1)
    {
        firstPrime->print();
        firstPrime = firstPrime->nextPrime;
    }
    firstPrime = temp;
}

void MagicalContainer::PrintCross()
{
    Node *temp = firstCross;
    cout << "Cross order:" << endl;
    while (firstCross)
    {
        firstCross->print();
        firstCross = firstCross->nextCross;
    }
    firstCross = temp;
}