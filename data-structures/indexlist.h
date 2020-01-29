#ifndef INDEXLIST_H
#define INDEXLIST_H

#include <stdexcept>
#include <list>

template <typename T>
class IndexList : public std::list<T>
{
    typename std::list<T>::iterator iterateToPosition(size_t index) {
        auto nodesSize = this->size();

        if (index >= nodesSize) {
            throw std::out_of_range("route node index is larger than route size");
        }

        if (index == 0) {
            return this->begin();
        } else if (index == nodesSize - 1) {
            return std::prev(this->end());
        }

        typename std::list<T>::iterator currentIterator;
        int distance;
        auto indexIsInLeftHalf = index < nodesSize/2;

        if (indexIsInLeftHalf) {
            currentIterator = ++this->begin();
            distance = static_cast<int>(index - 1);
        } else {
            currentIterator = this->end();
            distance = static_cast<int>(-nodesSize + index);
        }

        std::advance(currentIterator, distance);

        return currentIterator;
    }

public:
    IndexList() : std::list<T>() {}

    typename std::list<T>::iterator operator[](size_t index) {
        return iterateToPosition(index);
    }


};

#endif // INDEXLIST_H
