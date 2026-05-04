/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HashMap.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:19:29 by lekix             #+#    #+#             */
/*   Updated: 2026/05/04 16:41:25 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <optional>
#include <string>
#include <iostream>

#define HASH_OFFSET 2166136261
#define FNV_PRIME 16777619

template <typename T>
struct Entry 
{
    std::string                     key;
    T                               value;
    std::unique_ptr<Entry<T>>       next;

    Entry(std::string key, T value) : key(key), value(value), next(nullptr) {}
}; 

template <typename T>
class HashMap
{
    private:
        std::unique_ptr<std::unique_ptr<Entry<T>>[]>    _buckets;
        uint32_t                                        _size;
        int                                             _stored = 0;
        
        uint32_t                                        hash(std::string key);
        void                                            rehash(void);
        bool                                            need_rehash(void);
        
        T &                                             store(std::string key);
        void                                            move_in_bucket(std::unique_ptr<Entry<T>>* node, std::unique_ptr<Entry<T>>* bucket);
        Entry<T>*                                       search(std::string key);
        
        public:
        HashMap(void);
        ~HashMap(void) {};
        
        T &operator[](const std::string key);  // map["friend"]
        
        HashMap(int size);
        
        void                                            erase(std::string key);
        void                                            print(void);
        
    class KeyAlreadyExists : public std::exception
    {
        public:
            const char *what(void) const throw();
    };
};

template <typename T>
HashMap<T>::HashMap()
{
    this->_size = 16;
    this->_buckets = std::make_unique<std::unique_ptr<Entry<T>>[]>(16);
}

template <typename T>
HashMap<T>::HashMap(int size)
{
    this->_size = size;
    this->_buckets = std::make_unique<std::unique_ptr<Entry<T>>[]>(size);
}

template <typename T>
uint32_t HashMap<T>::hash(std::string key)
{
    uint32_t hash = HASH_OFFSET;
    for (auto c : key)
    {
        hash ^= c;
        hash *= FNV_PRIME;
    }
    return hash;
}

template <typename T>
Entry<T> *HashMap<T>::search(std::string key)
{
    uint32_t                        index = this->hash(key) % this->_size;
    std::unique_ptr<Entry<T>>*      current = &_buckets[index];

    while (*current)
    {
        if ((*current)->key == key)
           return ((*current).get());
        current = &(*current)->next;
    }
    return nullptr;
}

template <typename T>
T &HashMap<T>::store(std::string key)
{
    this->_stored += 1;
    uint32_t index = this->hash(key) % this->_size;
    std::unique_ptr<Entry<T>>* lst_begin = &_buckets[index];
    Entry<T>* curr = lst_begin->get();
    if (!curr)
    {
        *lst_begin = std::make_unique<Entry<T>>(key, T{});
        return (*lst_begin)->value;
    }
    while (curr && curr->next && curr->next.get())
        curr = curr->next.get();
    curr->next = std::make_unique<Entry<T>>(key, T{});
    return curr->next->value;
}

template <typename T>
void HashMap<T>::move_in_bucket(std::unique_ptr<Entry<T>>* node, std::unique_ptr<Entry<T>>* bucket)
{
    Entry<T>* curr = bucket->get();
    if (!curr)
    {
        *bucket = std::move(*node);
        return ;
    }
    while (curr && curr->next && curr->next.get())
        curr = curr->next.get();
    curr->next = std::move(*node);
}

template <typename T>
void HashMap<T>::print(void)
{
    for (uint32_t i = 0; i < this->_size; i++)
    {
        std::unique_ptr<Entry<T>>* current = &_buckets[i];
        while (*current)
        {
            std::cout << "key = " << (*current)->key << " val = " << (*current)->value << " at idx " << i << std::endl;
            current = &(*current)->next;
        }
        std::cout << "empty\n"; 
    }
    std::cout << "==========================\n" << std::endl;
}

template <typename T>
void HashMap<T>::erase(std::string key)
{
    uint32_t                        index = this->hash(key) % this->_size;
    std::unique_ptr<Entry<T>>*      current = &this->_buckets[index];
    std::unique_ptr<Entry<T>>*      prev;

    if (*current && (*current)->key == key)
    {
        this->_buckets[index] = std::move((*current)->next);
        return ;
    }
    while (*current)
    {
        if ((*current)->key == key)
        {
            (*prev)->next = std::move((*current)->next);
            return ;
        }
        prev = current;
        current = &(*current)->next;
    }
}

template <typename T>
bool HashMap<T>::need_rehash(void)
{
    if ((float)this->_stored / (float)this->_size >= 0.75)
        return true;
    return false;
}

template <typename T>
T &HashMap<T>::operator[](const std::string key)
{
    Entry<T>* found = this->search(key);
    
    if (found)
        return found->value;
    if (this->need_rehash())
        this->rehash();
    return this->store(key);
}

template <typename T>
void HashMap<T>::rehash()
{
    int old_size = this->_size;
    this->_size *= 2;

    std::unique_ptr<std::unique_ptr<Entry<T>>[]> new_tab;
    new_tab = std::make_unique<std::unique_ptr<Entry<T>>[]>(this->_size);
    
    for (int i = 0; i < old_size; i++)
    {
        if (this->_buckets[i])
        {
            std::unique_ptr<Entry<T>>* current = &this->_buckets[i];
            while (*current)
            {
                std::unique_ptr<Entry<T>> next = std::move((*current)->next);
                (*current)->next = nullptr;
                int new_hash = this->hash(current->get()->key) % this->_size;
                this->move_in_bucket(current, &new_tab[new_hash]);
                *current = std::move(next);
            }
        }
    }
    this->_buckets = std::move(new_tab);
}

template <typename T>
const char * HashMap<T>::KeyAlreadyExists::what(void) const throw()
{
    return ("Unique key already found\n");
}