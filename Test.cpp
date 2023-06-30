#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <iostream>
using namespace ariel;

TEST_CASE("Node operators")
{
    Node n1 = Node(4);
    Node n2 = Node(7);
    CHECK(n2.isprime);
    CHECK(n2 > n1);
    CHECK(n1 < n2);
    CHECK_FALSE(n1 == n2);
    Node n3 = Node(4);
    CHECK_FALSE(n1 == n3); // False as they have different addresses
}

TEST_CASE("Container Addition and Removal")
{
    ariel::MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(3);
    CHECK(container.size() == 3);
    bool removed = container.removeElement(10);
    CHECK(removed);
    CHECK(container.size() == 2);
}

TEST_CASE("Container pointers")
{
    ariel::MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(3);

    CHECK(container.getFirstAsc()->num == 3);
    CHECK(container.getLastAsc()->num == 10);
    CHECK(container.getfirstPrime()->num == 3);
    CHECK(container.getLastPrime()->prevPrime->num == 5);
    CHECK(container.getfirstCross()->num == 5);
}

TEST_CASE("Iterator operators")
{
    MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(3);
    MagicalContainer::AscendingIterator ascItr = MagicalContainer::AscendingIterator(container);
    MagicalContainer::PrimeIterator primeItr = MagicalContainer::PrimeIterator(container);
    MagicalContainer::SideCrossIterator crossItr = MagicalContainer::SideCrossIterator(container);

    MagicalContainer::AscendingIterator ascItr1 = ascItr.begin();
    MagicalContainer::AscendingIterator ascItr2 = ascItr.begin();
    CHECK(ascItr1 == ascItr2);
    ++ascItr2;
    CHECK(ascItr1 != ascItr2);
    CHECK(ascItr1 < ascItr2);
    CHECK(ascItr2 > ascItr1);
    CHECK(ascItr1 <= ascItr2);
    CHECK(ascItr2 >= ascItr1);

    MagicalContainer::PrimeIterator primeItr1 = primeItr.begin();
    MagicalContainer::PrimeIterator primeItr2 = primeItr.end();
    --primeItr2;
    CHECK(primeItr1 != primeItr2);
    CHECK(primeItr1 < primeItr2);
    CHECK(primeItr2 > primeItr1);
    CHECK(primeItr1 <= primeItr2);
    CHECK(primeItr2 >= primeItr1);
    --primeItr2;
    CHECK(primeItr1 == primeItr2);

    MagicalContainer::SideCrossIterator crossItr1 = crossItr.begin();
    MagicalContainer::SideCrossIterator crossItr2 = crossItr.begin();
    CHECK(crossItr1 == crossItr2);
    CHECK(crossItr2 >= crossItr1);
    ++crossItr2;
    CHECK(crossItr1 != crossItr2);
}

TEST_CASE("Iterating over containers")
{
    MagicalContainer container1;
    container1.addElement(5);
    container1.addElement(10);
    container1.addElement(3);
    MagicalContainer::AscendingIterator ascItr1 = MagicalContainer::AscendingIterator(container1);
    MagicalContainer::PrimeIterator primeItr1 = MagicalContainer::PrimeIterator(container1);
    MagicalContainer::SideCrossIterator crossItr1 = MagicalContainer::SideCrossIterator(container1);

    ariel::MagicalContainer container2;
    container2.addElement(5);
    container2.addElement(10);
    container2.addElement(3);
    MagicalContainer::AscendingIterator ascItr2 = MagicalContainer::AscendingIterator(container2);
    MagicalContainer::PrimeIterator primeItr2 = MagicalContainer::PrimeIterator(container2);
    MagicalContainer::SideCrossIterator crossItr2 = MagicalContainer::SideCrossIterator(container2);

    // Test AscendingIterator
    ariel::MagicalContainer::AscendingIterator itr1 = ascItr1.begin();
    CHECK(*itr1 == 3);
    ++itr1;
    CHECK(*itr1 == 5);
    ++itr1;
    CHECK(*itr1 == 10);
    ++itr1;
    CHECK(itr1 == ascItr1.end());
    ariel::MagicalContainer::AscendingIterator itr2 = ascItr2.end();

    
    // Test PrimeIterator
    ariel::MagicalContainer::PrimeIterator primeItr = primeItr1.begin();
    CHECK(*primeItr == 3);
    ++primeItr;
    CHECK(primeItr == --primeItr1.end());

    // Comparing different containers:
    CHECK_THROWS(ascItr1 == ascItr2);
    CHECK_THROWS(ascItr1 == primeItr2);
}
