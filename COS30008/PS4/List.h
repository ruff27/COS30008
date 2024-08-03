
// COS30008, Problem Set 4, 2024

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <cassert>

template<typename T>
class List
{
private:
    using Node = typename DoublyLinkedList<T>::Node;

    Node fHead;		// first element
    Node fTail;		// last element
    size_t fSize;	// number of elements

public:

    using Iterator = DoublyLinkedListIterator<T>;

    List() noexcept :								// default constructor	(2)
        fHead(nullptr), fTail(nullptr), fSize(0)
    {}

    // copy semantics
    List(const List& aOther) : fSize(aOther.fSize)					// copy constructor		(10)
    {
        for (Node lCurrent = aOther.fHead; lCurrent != nullptr; lCurrent = lCurrent->fNext)
        {
            push_back(lCurrent->fData);
        }
    }

    List& operator=(const List& aOther)		// copy assignment		(14)
    {
        if (this != &aOther)
        {
            List lTemp(aOther);
            swap(lTemp);
        }
        return *this;
    }

    // move semantics
    List(List&& aOther) noexcept :				// move constructor		(4)
        fHead(std::move(aOther.fHead)), fTail(std::move(aOther.fTail)), fSize(aOther.fSize)
    {
        aOther.fSize = 0;
    }

    List& operator=(List&& aOther) noexcept	// move assignment		(8)
    {
        if (this != &aOther)
        {
            fHead = std::move(aOther.fHead);
            fTail = std::move(aOther.fTail);
            fSize = aOther.fSize;
            aOther.fSize = 0;
        }
        return *this;
    }

    void swap(List& aOther) noexcept			// swap elements		(9)
    {
        std::swap(fHead, aOther.fHead);
        std::swap(fTail, aOther.fTail);
        std::swap(fSize, aOther.fSize);
    }

    // basic operations
    size_t size() const noexcept					// list size			(2)
    {
        return fSize;
    }

    template<typename U>
    void push_front(U&& aData)					// add element at front	(24)
    {
        Node lNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));
        if (!fHead)
        {
            fHead = lNode;
            fTail = lNode;
        }
        else
        {
            lNode->fNext = fHead;
            fHead->fPrevious = lNode;
            fHead = lNode;
        }
        ++fSize;
    }

    template<typename U>
    void push_back(U&& aData)					// add element at back	(24)
    {
        Node lNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));
        if (!fHead)
        {
            fHead = lNode;
            fTail = lNode;
        }
        else
        {
            fTail->fNext = lNode;
            lNode->fPrevious = fTail;
            fTail = lNode;
        }
        ++fSize;
    }

    void remove(const T& aElement) noexcept	// remove element		(36)
    {
        Node lCurrent = fHead;
        while (lCurrent)
        {
            if (lCurrent->fData == aElement)
            {
                if (lCurrent == fHead)
                {
                    fHead = lCurrent->fNext;
                    if (fHead)
                    {
                        fHead->fPrevious.reset();
                    }
                    else
                    {
                        fTail.reset();
                    }
                }
                else if (lCurrent == fTail)
                {
                    fTail = lCurrent->fPrevious.lock();
                    if (fTail)
                    {
                        fTail->fNext.reset();
                    }
                    else
                    {
                        fHead.reset();
                    }
                }
                else
                {
                    lCurrent->isolate();
                }
                --fSize;
                break;
            }
            lCurrent = lCurrent->fNext;
        }
    }

    const T& operator[](size_t aIndex) const	// list indexer			(14)
    {
        assert(aIndex < fSize);
        Node lCurrent = fHead;
        for (size_t i = 0; i < aIndex; ++i) {
            lCurrent = lCurrent->fNext;
        }
        return lCurrent->fData;
    }

    // iterator interface
    Iterator begin() const noexcept				//						(4)
    {
        return Iterator(fHead, fTail).begin();
    }

    Iterator end() const noexcept				//						(4)
    {
        return Iterator(fHead, fTail).end();
    }

    Iterator rbegin() const noexcept				//						(4)
    {
        return Iterator(fHead, fTail).rbegin();
    }

    Iterator rend() const noexcept				//						(4)
    {
        return Iterator(fHead, fTail).rend();
    }

};
