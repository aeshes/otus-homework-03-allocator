#pragma once

#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class list
{
    struct node
    {
        node* next;
        T value;
    };

public:
    using allocator_type = Alloc;

    list()
        : head(nullptr), tail(nullptr)
    {

    }

    list(const allocator_type &a)
        : head(nullptr), tail(nullptr), allocator(a)
    {

    }

    void push_front(const T& value)
    {
        typename Alloc::template rebind<node>::other alloc{allocator};
        node* n = alloc.allocate(1);
        n->value = value;
        n->next = nullptr;

        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            tail->next = n;
            tail = tail->next;
        }
    }

    T& front() const
    {
        return head->value;
    }

    T& back()
    {
        return tail->value;
    }

    class iterator
    {
    public:
        iterator() noexcept
            : current(nullptr)
        {

        }

        iterator(const node* ptr) noexcept
            : current(ptr)
        {

        }

        iterator& operator=(node* ptr)
        {
            current = ptr;
            return *this;
        }

        iterator& operator++()
        {
            if (current)
                current = current->next;
            return *this;
        }

        bool operator==(const iterator& it)
        {
            return current == it.current;
        }

        bool operator!=(const iterator& it)
        {
            return current != it.current;
        }

        T operator*() const
        {
            return current->value;
        }

    private:
        const node* current;
    };

    iterator begin()
    {
        return iterator(head);
    }

    iterator begin() const
    {
        return iterator(head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    iterator end() const
    {
        return iterator(nullptr);
    }

private:
    node* head;
    node* tail;
    Alloc allocator;
};
