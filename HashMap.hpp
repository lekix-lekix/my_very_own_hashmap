/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HashMap.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:19:29 by lekix             #+#    #+#             */
/*   Updated: 2026/04/14 17:18:45 by kipouliq         ###   ########.fr       */
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

    Entry(std::string key, T value) : key(key), value(value) {}
};

template <typename T>
class HashMap
{
    private:
        std::unique_ptr<std::unique_ptr<Entry<T>>[]>    buckets;
        uint32_t                                        size;
        
        uint32_t                                        hash(std::string key);
        T &                                             store(std::string key, T value);
        T &                                             search(std::string key);
        
    public:
        HashMap(void) {};
        ~HashMap(void) {};
        
        T &operator[](const std::string key);  // map["friend"]
        
        HashMap(int size);
        
        void                            print(void);
        
    class KeyAlreadyExists : public std::exception
    {
        public:
            const char *what(void) const throw();
    };
};

template <typename T>
HashMap<T>::HashMap(int size)
{
    this->size = size;
    this->buckets = std::make_unique<std::unique_ptr<Entry<T>>[]>(size);
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
    return (hash);
}

template <typename T>
T &HashMap<T>::store(std::string key, T value)
{
    uint32_t                        index = this->hash(key) % this->size;
    std::unique_ptr<Entry<T>>       new_node = std::make_unique<Entry<T>>(key, value);
    std::unique_ptr<Entry<T>>*      current = &buckets[index];

    while (*current)
    {
        if ((*current)->key == key)
        {
            (*current)->value = value;
            return ((*current)->value);
        }
        current = &(*current)->next;
    }
    *current = std::move(new_node);
    return ((*current)->value);
}

// template <typename T>
// T &HashMap<T>::search(std::string key)
// {
//     for (uint32_t i = 0; i < this->size; i++)
//     {
//         std::unique_ptr<Entry<T>>* current = &buckets[i];
//         while (*current)
//         {
//             if ((*current)->key == key)
//                 return ((*current)->value);
//             current = &(*current)->next;
//         }
//     }
//     return (nullptr);
// }

template <typename T>
void HashMap<T>::print(void)
{
    for (uint32_t i = 0; i < this->size; i++)
    {
        std::unique_ptr<Entry<T>>* current = &buckets[i];
        while (*current)
        {
            std::cout << "key = " << (*current)->key << " val = " << (*current)->value << " at idx " << i << std::endl;
            current = &(*current)->next;
        }
        std::cout << "empty\n"; 
    }
}

template <typename T>
T &HashMap<T>::operator[](const std::string key)
{
    return (this->store(key));
}

template <typename T>
const char * HashMap<T>::KeyAlreadyExists::what(void) const throw()
{
    return ("Unique key already found\n");
}