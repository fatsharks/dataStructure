#include <iostream>
#include <global.hpp>

namespace myDataStructure
{
    template <typename Key, typename Value>
    struct hashNode
    {
        Key key_;
        Value value_;
        struct hashNode<Key, Value> *nextNode;
    };
    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    class hashMap
    {
    private:
        HashFunc hash;
        EqualKey equal;
        hashNode<Key, Value> **table;
        size_t size_;
        Value valueNULL;

    public:
        hashMap(size_t size);
        ~hashMap();

        void insert(const Key &key, const Value &value);
        bool remove(const Key &key, const Value &value);
        Value &find(const Key &key);
        Value &operator[](const Key &key);
    };

    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    hashMap<Key, Value, HashFunc, EqualKey>::hashMap(size_t size) : size_(size)
    {
        hash = HashFunc();
        equal = EqualKey();
        table = new hashNode<Key, Value> *[size];
        for (size_t i = 0; i < size; i++)
        {
            table[i] = NULL;
        }
    }

    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    hashMap<Key, Value, HashFunc, EqualKey>::~hashMap()
    {
        for (size_t i = 0; i < table; i++)
        {
            hashNode<Key, Value> *current = table[i];
            while (current)
            {
                hashNode<Key, Value> *temp = current->nextNode;
                current = current->nextNode;
                delete temp;
            }
        }
        delete table;
    }
    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    void hashMap<Key, Value, HashFunc, EqualKey>::insert(const Key &key, const Value &value)
    {
        size_t index = hash(key);
        hashNode<Key, Value> *newNode = new hashNode<Key, Value> *(key, value, NULL);
        hashNode<Key, Value> *temp;
        temp = table[index];
        while (temp->nextNode)
        {
            if (temp->value_ < newNode->value_)
            {
                temp = temp->nextNode;
            }
            else
            {
                break;
            }
        }
        newNode->nextNode = temp->nextNode;
        temp->nextNode = newNode;
    }
    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    bool hashMap<Key, Value, HashFunc, EqualKey>::remove(const Key &key, const Value &value)
    {
        size_t index = hash(key);
        if (table[index] == NULL)
        {
            return false;
        }
        else
        {
            hashNode<Key, Value> *temp = table[index];
            hashNode<Key, Value> *parent = NULL;
            while (temp)
            {
                if (temp->key_ == key)
                {
                    if (parent == NULL)
                    {
                        table[index] = temp->nextNode;
                    }
                    else
                    {
                        parent->nextNode = temp->nextNode;
                    }
                    delete temp;
                    return true;
                }
                parent = temp
                    temp = temp->nextNode;
            }
            return false;
        }
    }
    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    Value &hashMap<Key, Value, HashFunc, EqualKey>::find(const Key &key)
    {
        size_t index = hash(key);
        if (table[index] == NULL)
        {
            return valueNULL;
        }
        else
        {
            hashNode<Key, Value> *temp = table[index];
            while (temp)
            {
                if (temp->key_ == key)
                {
                    return temp->value_;
                }
                temp = temp->nextNode;
            }
            return valueNULL;
        }
    }
    template <typename Key, typename Value, typename HashFunc, typename EqualKey>
    Value &hashMap<Key, Value, HashFunc, EqualKey>::operator[](const Key &key)
    {
        return find(key);
    }

    template <typename Key>
    class fibonacciHash
    {
    public:
        int operator()(Key key)
        {
            size_t index = 0;
            switch (sizeof(Key))
            {
            case 2:
                index = (key * 40503) >> 28;
                break;
            case 4:
                index = (key * 2654435769) >> 28;
                break;
            case 8:
                index = (key * 11400714819323198485) >> 28;
                break;
            default:
                break;
            }
            return index;
        }
    };

    template <typename Key>
    class EqualKey
    {
    public:
        bool operator()(Key key_1, Key key_2)
        {
            return key_1 == key_2 ? true : false;
        }
    };

} // namespace myDataStructure
