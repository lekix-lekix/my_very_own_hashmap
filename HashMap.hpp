/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HashMap.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:19:29 by lekix             #+#    #+#             */
/*   Updated: 2026/04/07 22:34:46 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <string>
#include <iostream>

#define HASH_OFFSET 2166136261
#define FNV_PRIME 16777619

template <typename T>
struct Entry 
{
    std::string         key;
    T                   value;
    struct Entry<T>     *next;
};

template <typename T>
class HashMap
{
    private:
        std::unique_ptr<Entry<T>*[]> buckets;
        uint32_t hash(int value);

    public:
        HashMap(void) {};
        // HashMap(const HashMap &rhs);
        ~HashMap(void) {};

        // HashMap& operator=(HashMap const &rhs);
        HashMap& operator[](HashMap const &rhs);  // map["friend"]        
        HashMap(int size);
};

// template <typename T>
// HashMap<T>::HashMap(void) {}
// 
// template <typename T>
// HashMap<T>::~HashMap(void) {}

template <typename T>
HashMap<T>::HashMap(int size)
{
    this->buckets = std::make_unique<Entry<T>*[]>(size);
}

