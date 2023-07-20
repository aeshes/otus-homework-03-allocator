#pragma once

template<typename T, typename Alloc>
class list
{
    struct node
    {
        node* next;
        T value;
    };

public:
    void push_front(const T& value)
    {
        typename Alloc::template rebind<node>::other alloc;
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

    typename Alloc::template rebind<node>::other alloc;
    node* n = alloc.allocate(1);

private:
    node* head;
    node* tail;
    Alloc allocator;
};
