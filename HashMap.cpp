/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HashMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 21:33:39 by lekix             #+#    #+#             */
/*   Updated: 2026/04/14 16:59:00 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HashMap.hpp"
#include <vector>

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

int main ()
{
    HashMap<int> map(20);
    std::vector<std::string> keys;

    for (int i = 0; i < 100; i++)
    {
        std::string key = gen_random(10);
        keys.push_back(key);
        map[key] = 1;
    }
    map.print();
    // std::optional<int> found;

    // found = map.search(keys[0]);
    // if (found.has_value())
    //     std::cout << "value found = " << map.search(keys[0]).value() << " for key " << keys[0] << std::endl;
    
    // found = map.search("coucou");
    // if (found.has_value())
    //     std::cout << "value found = " << map.search("hey coucou").value() << " for key " << "hey coucou" << std::endl;
    // else
    //     std::cout << "key not found !\n";

    // try {
    //     map.store(keys[0], 2);
    // } catch (std::exception &excpt) {
    //     std::cerr << excpt.what();
    // }
    map["coucou"] = 32;
}