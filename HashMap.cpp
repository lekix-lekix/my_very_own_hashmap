/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HashMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 21:33:39 by lekix             #+#    #+#             */
/*   Updated: 2026/04/17 16:08:11 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HashMap.hpp"
#include <vector>
#include <unordered_map>
#include <cassert>

void test_insert_and_access()
{
    HashMap<int> map;
    map["age"] = 25;
    map["score"] = 100;
    assert(map["age"] == 25);
    assert(map["score"] == 100);
    std::cout << "✅ insert and access\n";
}

void test_overwrite()
{
    HashMap<int> map;
    map["age"] = 25;
    map["age"] = 30;
    assert(map["age"] == 30);
    std::cout << "✅ overwrite\n";
}

void test_default_value()
{
    HashMap<int> map;
    assert(map["nonexistent"] == 0);  // int par défaut = 0
    std::cout << "✅ default value\n";
}

void test_erase()
{
    HashMap<int> map;
    map["age"] = 25;
    map.erase("age");
    assert(map["age"] == 0);  // après erase, doit retourner valeur par défaut
    std::cout << "✅ erase\n";
}

void test_erase_nonexistent()
{
    HashMap<int> map;
    map.erase("ghost");  // ne doit pas crasher
    std::cout << "✅ erase nonexistent\n";
}

void test_collision()
{
    HashMap<int> map(200);
    // insère beaucoup de clés pour forcer des collisions
    for (int i = 0; i < 150; i++)
        map[std::to_string(i)] = i;
    std::cout << "coucou\n";
    // for (int i = 0; i < 100; i++)
        // std::cout << map[std::to_string(i)] << std::endl;
    std::cout << "===========\n";
    map.print();
    map["coucou"] = 156;
    map.print();
    std::cout << map["coucou"] << std::endl;
    std::cout << map["48"] << std::endl;
    // std::cout << "index 0 = " << map[std::to_string(0)] << std::endl;
    for (int i = 0; i < 300; i++)
        std::cout << map[std::to_string(i)] << std::endl;
    std::cout << "✅ collisions\n";
}

void test_string_values()
{
    HashMap<std::string> map(10);
    map["name"] = "alice";
    map["city"] = "paris";
    assert(map["name"] == "alice");
    assert(map["city"] == "paris");
    std::cout << "✅ string values\n";
}

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

int main()
{
    test_insert_and_access();
    test_overwrite();
    test_default_value();
    test_erase();
    test_erase_nonexistent();
    test_collision();
    test_string_values();
    std::cout << "\n🎉 tous les tests passent\n";
}

// int main ()
// {
//     // int size = 1000;
    
//     HashMap<int> map;
//     std::vector<std::string> keys;


//     // std::cout << map[10001] << std::endl;
//     for (int i = 0; i < 20; i++)
//     {
//         std::string key = gen_random(10);
//         keys.push_back(key);
//         map[key] = i;
//     }
//     map.print();
//     for (int i = 0; i < 20; i++)
//     {
//         std::string key = gen_random(10);
//         keys.push_back(key);
//     map[key] = i;
//     }

//     // std::unordered_map<std::string, int> unmap;

//     // std::cout << unmap["hey"] << std::endl;
    
//     // std::optional<int> found;

//     // found = map.search(keys[0]);
//     // if (found.has_value())
//     //     std::cout << "value found = " << map.search(keys[0]).value() << " for key " << keys[0] << std::endl;
    
//     // found = map.search("coucou");
//     // if (found.has_value())
//     //     std::cout << "value found = " << map.search("hey coucou").value() << " for key " << "hey coucou" << std::endl;
//     // else
//     //     std::cout << "key not found !\n";

//     // try {
//     //     map.store(keys[0], 2);
//     // } catch (std::exception &excpt) {
//     //     std::cerr << excpt.what();
//     // // }
//     map["coucou"] = 32;
//     std::cout << map["coucou"] << std::endl;
//     std::cout << "========\n";
//     // std::cout << keys[99998] << std::endl;
//     std::cout << map[keys[999]] << std::endl;
//     map.erase(keys[5]);
//     // std::cout << map["coucou"] << std::endl;
// }