#include "MagicalContainer.hpp"
#include <ostream>
#include <iostream>
using namespace std;
using namespace ariel;

// OPERATOR OVERLOADING:

bool MagicalContainer::Iterator::operator==(Iterator other)
{
    if(this->container != other.container){
        throw this;
    }
    if(curr == NULL){
        if(other.curr == NULL){
            return true;
        }
        return false;
    }
    return other.curr == curr;
}

bool MagicalContainer::Iterator::operator!=(Iterator other)
{
    
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(Iterator other)
{
    return curr->num > other.curr->num;
}

bool MagicalContainer::AscendingIterator::operator<(Iterator other)
{
    return curr->num < other.curr->num;
}

bool MagicalContainer::AscendingIterator::operator>=(Iterator other)
{
    return !(*this < other);
}

bool MagicalContainer::AscendingIterator::operator<=(Iterator other)
{
    return !(*this > other);
}

bool MagicalContainer::PrimeIterator::operator>(Iterator other)
{
    return curr->num > other.curr->num;
}

bool MagicalContainer::PrimeIterator::operator<(Iterator other)
{
    return curr->num < other.curr->num;
}

bool MagicalContainer::PrimeIterator::operator>=(Iterator other)
{
    return !(*this < other);
}

bool MagicalContainer::PrimeIterator::operator<=(Iterator other)
{
    return !(*this > other);
}

bool MagicalContainer::SideCrossIterator::operator>(Iterator other)
{
    return curr->crossIndex > other.curr->crossIndex;
}

bool MagicalContainer::SideCrossIterator::operator<(Iterator other)
{
    return curr->crossIndex < other.curr->crossIndex;
}

bool MagicalContainer::SideCrossIterator::operator>=(Iterator other)
{
    return !(*this < other);
}

bool MagicalContainer::SideCrossIterator::operator<=(Iterator other)
{
    return !(*this > other);
}

MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(Iterator &other)
{
    return other;
}

int MagicalContainer::Iterator::operator*()
{
    return curr->num;
}

MagicalContainer::Iterator &MagicalContainer::AscendingIterator::operator++()
{
    if (curr == NULL)
    {
        cout << "Iterator has reached its end" << endl;
        throw this;
    }
    curr = curr->nextAsc;
    return *this;
}

MagicalContainer::Iterator &MagicalContainer::AscendingIterator::operator--()
{
    if (curr == NULL)
    {
        cout << "Iterator has reached its beginning" << endl;
        throw this;
    }
    curr = curr->prevAsc;
    return *this;
}

MagicalContainer::Iterator &MagicalContainer::PrimeIterator::operator++()
{
    if (curr == NULL)
    {
        cout << "Iterator has reached its end" << endl;
        throw this;
    }
    curr = curr->nextPrime;
    return *this;
}

MagicalContainer::Iterator &MagicalContainer::PrimeIterator::operator--()
{
    if (curr == NULL)
    {
        cout << "Iterator has reached its beginning" << endl;
        throw this;
    }
    curr = curr->prevPrime;
    return *this;
}

MagicalContainer::Iterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (curr == NULL)
    {
        cout << "Iterator has reached its end" << endl;
        throw this;
    }
    curr = curr->nextCross;
    return *this;
}

MagicalContainer::Iterator &MagicalContainer::SideCrossIterator::operator--()
{
    if (curr == NULL)
    {
        cout << "Iterator has reached its beginning" << endl;
        throw this;
    }
    curr = curr->prevCross;
    return *this;
}
namespace ariel // This operator is wrapped inside the namespace directly so the compiler will not think it is different from the function definition in MagicalContainer.hpp.
{
    std::ostream &operator<<(std::ostream &stream, MagicalContainer::Iterator Itr)
    {
        stream << Itr.curr->num;
        return stream;
    }
}
// CONSTRUCTORS:

MagicalContainer::AscendingIterator::AscendingIterator()
{
    this->container = new MagicalContainer();
    curr = NULL;
}

MagicalContainer::PrimeIterator::PrimeIterator()
{
    this->container = new MagicalContainer();
    curr = NULL;
}

MagicalContainer::SideCrossIterator::SideCrossIterator()
{
    this->container = new MagicalContainer();
    curr = NULL;
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
{
    this->container = &container;
    curr = container.firstAsc;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
{
    this->container = &container;
    curr = container.firstPrime;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
{
    this->container = &container;
    curr = container.firstCross;
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer::AscendingIterator &other)
{
    this->container = other.container;
    curr = other.container->firstAsc;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer::PrimeIterator &other)
{
    this->container = other.container;
    curr = other.container->firstPrime;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer::SideCrossIterator &other)
{
    this->container = other.container;
    curr = other.container->firstCross;
}

// DESTRUCTORS:

MagicalContainer::AscendingIterator::~AscendingIterator()
{
    // delete container;
}
MagicalContainer::PrimeIterator::~PrimeIterator()
{
    // delete container;
}
MagicalContainer::SideCrossIterator::~SideCrossIterator()
{
    // delete container;
}

// BIGIN AND END FUNCTIONS:

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    this->curr = this->container->firstAsc;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    this->curr = this->container->firstPrime;
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    this->curr = this->container->firstCross;
    return *this;
}


MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator itr = AscendingIterator(*(this->container));
    itr.curr = this->container->lastAsc->nextAsc;
    return itr;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator itr = PrimeIterator(*(this->container));
    itr.curr = this->container->lastPrime;
    return itr;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator itr = SideCrossIterator(*(this->container));
    itr.curr = this->container->lastCross->nextCross;
    return itr;
}