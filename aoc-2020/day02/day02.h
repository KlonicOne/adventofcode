/**
 * @file day01.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _DAY02_H_
#define _DAY02_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;


class day02
{
private:
    /* data */
    std::vector<std::tuple<int, int, char, std::string>> format_code_list;
    int number_valid_policies;

public:
    day02(/* args */);
    ~day02();

    void solver_part1(std::vector<std::string> inTable);
    void solver_part2(std::vector<std::string> inTable);

    // part 1
    void format_code(std::vector<std::string> inTable);
    bool check_single_policy(std::tuple<int, int, char, std::string> password_element);
    int count_valid_policies(void);
};

#endif // _DAY02_H_