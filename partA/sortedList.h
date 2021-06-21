#ifndef HW2_SORTEDLIST_H
#define HW2_SORTEDLIST_H

#include <iostream>
#include <string>
#include "stdlib.h"
#include <stdexcept>

/**
* Generic List Container
*
* Implements a list container type.
* The list has an internal iterator for external use.
*
* The following functions are available:
*   insert		- Adds an element to the list, by order.
*   remove		- Deletes an existing element from the list.
*   length		- Returning the list's size.
*   filter		- Creates a new list and puts into it only the
*                 elements of the list which are accepted by the predicate given.
*   apply	    - Creates a new list which contains the result for every element of the first list,
*                 when applied to the function given as a parameter.
*   begin		- returns a const iterator to the first element.
*   end  	    - returns a const iterator to the end of the list.
*/


namespace mtm
{
    const std::string OUT_OF_RANGE_ERROR = "End of list";

    template <class T>
    class SortedList
    {
        typedef class node_t
        {
        public:
            T data;
            class node_t *next;

            node_t(T data);

        } *Node;

    public:
        Node head;
        int size;

        class const_iterator
        {
            friend class SortedList<T>;

        private:
            Node current_node;
            const_iterator();
            const_iterator(const SortedList<T>::Node node_to_be_head);

        public:
            ~const_iterator() = default;
            const_iterator(const SortedList<T>::const_iterator &iterator_to_copy);
            const_iterator& operator= (const const_iterator &iterator_to_assign);
            const_iterator operator++();
            bool operator==(const const_iterator &iterator1) const;
            const T operator*();
        };

        SortedList();
        ~SortedList();
        SortedList(const SortedList<T> &list);
        SortedList<T>& operator= (const SortedList<T> &list);

        /**
        * insert: Adds an element to the list, by order.
        *
        * @param new_data - data to be added to the list.
        */
        void insert(const T& new_data);

        /**
        * remove: Deletes an existing element from the list.
        *
        * @param iterator - iterator to the element to remove.
        */
        void remove(typename SortedList<T>::const_iterator iterator);

        /**
        * remove: Deletes an existing element from the list.
        *
        * @return
        * 	the size of the list.
        */
        int length();

        /**
        * filter: Creates a new list and puts into it only the
        *         elements of the list which are accepted by the predicate given.
        * @return
        * 	a new list with the filtered elements.
        */
        template <class Condition>
        SortedList<T> filter(Condition condition) const;

        /**
        * apply: Creates a new list which contains the result for every element of the first list,
        *        when applied to the function given as a parameter.
        * @return
        * 	a new list with the elements after being applied to the give function.
        */
        template <class Function>
        SortedList<T> apply(Function function) const;

        /**
        * apply: returns a const iterator to the first element.
        *
        * @return
        * 	an iterator to the first element of the list.
        */
        const_iterator begin();

        /**
        * apply: returns a const iterator to the end of the list.
        *
        * @return
        * 	an iterator to the end of the list.
        */
        const_iterator end();
    };

    template<class T>
    SortedList<T>::node_t::node_t(T data) : data(data), next(nullptr)
    {
    }

    template<class T>
    SortedList<T>::const_iterator::const_iterator() : current_node(head)
    {
    }

    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T>::Node node_to_be_head)
                : current_node(node_to_be_head)
    {
    }

    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T>::const_iterator &iterator_to_copy) :
        current_node(iterator_to_copy.current_node)
    {
    }

    template<class T>
    typename SortedList<T>::const_iterator&
                    SortedList<T>::const_iterator::operator= (const const_iterator &iterator_to_assign)
    {
        current_node = iterator_to_assign.current_node;
        return *this;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++()
    {
        if (current_node == nullptr)
        {
            throw std::out_of_range(OUT_OF_RANGE_ERROR);
        }

        current_node = current_node->next;

        return *this;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator &iterator1) const
    {
        return current_node == iterator1.current_node;
    }

    template<class T>
    const T SortedList<T>::const_iterator::operator*()
    {
        if(current_node == nullptr)
        {
            throw std::out_of_range(OUT_OF_RANGE_ERROR);
        }
        return current_node->data;
    }

    template<class T>
    SortedList<T>::SortedList() : head(nullptr), size(0)
    {
    }

    template<class T>
    SortedList<T>::~SortedList()
    {
        if(size == 0)
        {
            return;
        }

        if(size == 1)
        {
            delete(head);
            return;
        }

        Node current_node = head->next;
        Node node_before = head;
        while(current_node != nullptr)
        {
            delete(node_before);
            node_before = current_node;
            current_node = current_node->next;
        }

        delete(node_before);
    }

    template<class T>
    SortedList<T>::SortedList(const SortedList<T>& list)
    {
        size = 0;
        if(list.size == 0)
        {
            head = nullptr;
            return;
        }

        Node current_node = list.head;
        while(current_node != nullptr)
        {
            insert(current_node->data);
            current_node = current_node->next;
        }
    }

    template<class T>
    SortedList<T>& SortedList<T>::operator= (const SortedList<T> &list)
    {
        if(this == &list)
        {
            return *this;
        }
        if(size > 1)
        {
            Node to_delete = head;
            Node current_node = head->next;
            while (current_node != nullptr)
            {
                delete (to_delete);
                to_delete = current_node;
                current_node = current_node->next;
            }
            delete(to_delete);
            head = nullptr;
        }
        else if(size == 1)
        {
            delete(head);
            head = nullptr;
        }

        size = 0;
        if(list.size == 0)
        {
            head = nullptr;
            return *this;
        }

        Node current_node = list.head;
        while(current_node != nullptr)
        {
            insert(current_node->data);
            current_node = current_node->next;
        }

        return *this;
    }

    template<class T>
    void SortedList<T>::insert(const T& new_data)
    {
        Node new_node = new node_t(new_data);
        if(size == 0)
        {
            head = new_node;
        }
        else if (size == 1)
        {
            if(head->data < new_data)
            {
                head->next = new_node;
            }
            else
            {
                new_node->next = head;
                head = new_node;
            }
        }
        else
        {
            if(!(head->data < new_data))
            {
                new_node->next = head;
                head = new_node;
                size = size + 1;
                return;
            }

            Node current_node = head->next;
            Node node_before = head;
            while(current_node && current_node->data < new_data)
            {
                current_node = current_node->next;
                node_before = node_before->next;
            }

            if(current_node == nullptr)
            {
                node_before->next = new_node;
                new_node->next = nullptr;
                size = size + 1;
                return;
            }

            node_before->next = new_node;
            new_node->next = current_node;
        }

        size = size + 1;
    }

    template<class T>
    void SortedList<T>::remove(typename SortedList<T>::const_iterator iterator)
    {
        if(size == 0)
        {
            return;
        }
        else if(size == 1)
        {
            delete(head);
            head = nullptr;
            size = size - 1;
            return;
        }
        else
        {
            Node current_node = head->next;
            Node node_before = head;

            if(iterator.current_node == head)
            {
                Node to_delete = head;
                head = head->next;
                delete(to_delete);
                size = size - 1;
                return;
            }

            while(current_node->next && !(current_node == iterator.current_node))
            {
                current_node = current_node->next;
                node_before = node_before->next;
            }

            if(current_node->next == nullptr)
            {
                if(!(current_node == iterator.current_node))
                {
                    return;
                }
                else
                {
                    delete(current_node);
                    node_before->next = nullptr;
                    size = size - 1;
                    return;
                }
            }

            Node to_delete = current_node;

            node_before->next = current_node->next;

            delete(to_delete);
            size = size - 1;
        }
    }

    template<class T>
    int SortedList<T>::length()
    {
        return size;
    }

    template <class T>
    template <class Condition>
    SortedList<T> SortedList<T>::filter(Condition condition) const
    {
        Node current_node = head;
        SortedList<T> new_list = SortedList<T>();
        if(size == 0)
        {
            return new_list;
        }

        while(current_node != nullptr)
        {
            if(condition(current_node->data))
            {
                new_list.insert(current_node->data);
            }
            current_node = current_node->next;
        }

        return new_list;
    }

    template<class T>
    template <class Function>
    SortedList<T> SortedList<T>::apply(Function function) const
    {
        Node current_node = head;
        SortedList<T> new_list;
        new_list.size = 0;
        if(size == 0)
        {
            return new_list;
        }

        while(current_node != nullptr)
        {
            new_list.insert(function(current_node->data));
            current_node = current_node->next;
        }

        return new_list;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin()
    {
        return const_iterator(head);
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end()
    {
        const_iterator iterator = begin();
        while(iterator.current_node != nullptr)
        {
            iterator.current_node = iterator.current_node->next;
        }
        return iterator;
    }
}

#endif //HW2_SORTEDLIST_H
