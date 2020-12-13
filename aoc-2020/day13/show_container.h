/**
 * @file show_container.h
 * @author your name (you@domain.com)
 * @brief Show content of any container
 * @version 0.1
 * @date 2020-12-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __SHOW_CONTAINER_H__
#define __SHOW_CONTAINER_H__

#include <iostream>

template <class Container>
void show_container(Container&& container, const char* abschluss = "\n", const char* trenn = " ") {
    for (decltype(auto) element : container) {
        std::cout << element << trenn;
    }
    std::cout << abschluss;
}

#endif