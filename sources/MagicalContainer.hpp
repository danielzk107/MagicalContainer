#include <vector>
#include <ostream>
using namespace std;
namespace ariel
{
    class Node{
        private:
            bool isPrime(int num); // This function is never used outside of this class
        public:
            bool isprime;
            int crossIndex; // Used in comparing cross iterators
            int num;
            Node* prevAsc;
            Node* nextAsc;
            Node* prevCross;
            Node* nextCross;
            Node* prevPrime;
            Node* nextPrime;
            Node(int num, Node* prevAsc, Node* asc, Node* prevCross, Node* cross, Node* prevPrime, Node* prime);
            Node(int num);
            ~Node();
            bool operator==(Node other);
            bool operator<(Node other);
            bool operator>(Node other);
            void print();
    };
    class MagicalContainer
    {
    private:
        int num_of_elements; // Not called size since the function is called size and would therefor try and return a reference to itself instead of this integer
        Node* firstAsc;
        Node* lastAsc;
        Node* firstPrime;
        Node* lastPrime;
        Node* firstCross;
        Node* lastCross;
    public:
        MagicalContainer();
        ~MagicalContainer();
        Node* getFirstAsc();
        Node* getLastAsc();
        Node* getfirstPrime();
        Node* getLastPrime();
        Node* getfirstCross();
        Node* getLastCross();
        void UpdateAsc();
        void UpdateCross();
        void UpdatePrime();
        // Print functions used for debugging:
        void PrintAsc();
        void PrintPrime();
        void PrintCross();
        int size();
        void addElement(int num);
        bool removeElement(int num); // Returns true/false according to the success of the operation.
        class Iterator
        {       
        private:
            friend std::ostream &operator<<(std::ostream &stream, Iterator Itr);
        public:
            MagicalContainer* container;
            Node* curr;
            bool operator==(Iterator other);
            bool operator!=(Iterator other);
            Iterator &operator=(Iterator &other);
            int operator*();
        };
        class AscendingIterator : public Iterator
        {
        public:
            AscendingIterator();
            AscendingIterator(MagicalContainer& container);
            AscendingIterator(AscendingIterator &other);
            ~AscendingIterator();
            AscendingIterator begin();
            AscendingIterator end();
            Iterator& operator++();
            Iterator& operator--();
            bool operator>(Iterator other);
            bool operator<(Iterator other);
            bool operator>=(Iterator other);
            bool operator<=(Iterator other);
        };
        class SideCrossIterator : public Iterator
        {
        public:
            SideCrossIterator();
            SideCrossIterator(MagicalContainer& container);
            SideCrossIterator(SideCrossIterator &other);
            ~SideCrossIterator();
            SideCrossIterator begin();
            SideCrossIterator end();
            Iterator& operator++();
            Iterator& operator--();
            bool operator>(Iterator other);
            bool operator<(Iterator other);
            bool operator>=(Iterator other);
            bool operator<=(Iterator other);
        };
        class PrimeIterator : public Iterator
        {
        public:
            PrimeIterator();
            PrimeIterator(MagicalContainer& container);
            PrimeIterator(PrimeIterator &other);
            ~PrimeIterator();
            PrimeIterator begin();
            PrimeIterator end();
            Iterator& operator++();
            Iterator& operator--();
            bool operator>(Iterator other);
            bool operator<(Iterator other);
            bool operator>=(Iterator other);
            bool operator<=(Iterator other);
        };
    };
}