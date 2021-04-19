/**
 * @file day14.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day14.h"

#include <time.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <vector>

#include "show_container.h"

using namespace std;

#define DEBUG_OUT false

/**
 * @brief constructor
 *
 */
day14::day14(/* args */) { this->m_sum_mem = 0; }

/**
 * @brief Destroy the day14::day14
 *
 */
day14::~day14() {}

/**
 * @brief Solve part 1
 *
 */
void day14::solver_part1(void) {
  unsigned long long answer = 0;

  std::cout << "Part 1" << std::endl;

  // Loop through format input and apply the masks to store value
  for (auto iter : this->m_format_input) {
    // Take input value from mem input
    for (auto iter_mem : iter.mem_entry) {
      unsigned long address = iter_mem.first;
      unsigned long value = iter_mem.second;
      // Apply set mask
      value = value | iter.set_mask;
      // Apply reset mask
      value = value & iter.reset_mask;
      // Saturate to 36 bit
      value = value & SAT_MASK;
      // Store in mem
      this->m_mem[address] = value;
    }
  }

  answer = this->calc_sum_mem();

  if (DEBUG_OUT) {
    std::cout << "Memory content: " << std::endl;
    for (auto iter : this->m_mem) {
      std::cout << "[" << std::dec << iter.first << "]: " << iter.second
                << std::endl;
    }
  }

  // Out result
  std::cout << "Result Part1: " << std::dec << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day14::solver_part2(void) {
  long answer = 0;

  std::cout << "Part 2" << std::endl;

  // Clear result used in part 1
  this->m_mem.clear();

  // Loop through format input and apply the masks to store value
  for (auto iter : this->m_format_input) {
    // Take input value from mem input
    for (auto iter_mem : iter.mem_entry) {
      std::vector<unsigned long> address_vector;
      unsigned long address = iter_mem.first;
      unsigned long value = iter_mem.second;

      // Apply unchange mask on address
      address = this->apply_unchange(address, iter.unchange_mask);
      // Apply overwrite mask on address
      address = this->apply_overwrite(address, iter.overwrite_one_mask);
      // Apply floating mask on address
      address_vector = this->apply_floating(address, iter.floating_mask);
      // Saturate to 36 bit the value
      value = value & SAT_MASK;

      // Loop through all addresses calculated with the
      for (auto iter_add : address_vector) {
        // Store value in memory
        this->m_mem[iter_add] = value;
      }
    }
  }

  answer = this->calc_sum_mem();

  if (DEBUG_OUT) {
    std::cout << "Memory content: " << std::endl;
    for (auto iter : this->m_mem) {
      std::cout << "[" << std::dec << iter.first << "]: " << iter.second
                << std::endl;
    }
  }

  // Out result
  std::cout << "Result Part2: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day14::format_input(std::vector<std::string> inTable) {
  int line_num = 0;
  bool first_found = false;
  std::string string_line = "";
  t_input_element temp_input_element;

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i, ++line_num) {
    std::size_t found;
    std::size_t found_enclosing;

    // Get single line as string_line
    string_line = (*i);

    // Skip empty line
    if (string_line == "") {
      continue;
    }

    // Check if new input element is found starting with mask
    found = string_line.find("mask");
    if (found != std::string::npos) {
      // Add last content if not very first element
      if (first_found) {
        // Add element because we found first one
        this->m_format_input.push_back(temp_input_element);
      }

      // Clear last content
      temp_input_element.set_mask = 0;
      temp_input_element.reset_mask = 1;
      temp_input_element.unchange_mask = 0;
      temp_input_element.overwrite_one_mask = 0;
      temp_input_element.floating_mask = 0;
      temp_input_element.mem_entry.clear();

      // Get the masks mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
      std::string mask = string_line.substr(found + 7, 36);

      // Store masks in temp element
      temp_input_element.set_mask = get_set_mask(mask);
      temp_input_element.reset_mask = get_reset_mask(mask);

      // For part 2 we have further maks to store
      temp_input_element.unchange_mask = get_unchage_mask(mask);
      temp_input_element.overwrite_one_mask = get_overwriteone_mask(mask);
      temp_input_element.floating_mask = get_floating_mask(mask);

      // We found first one
      first_found = true;
    } else {
      // Memory to be added on the input element
      found = string_line.find("mem[");
      found_enclosing = string_line.find("]");

      // Extract address mem[7] = 101
      unsigned long adr =
          stoi(string_line.substr(found + 4, found_enclosing - (found + 4)));
      found = string_line.find("=");
      // Extract value for address
      unsigned long val =
          stoi(string_line.substr(found + 1, std::string::npos - (found + 1)));
      // Now add to mem
      temp_input_element.mem_entry.push_back(make_pair(adr, val));
    }
  }

  // Add last element to format input
  this->m_format_input.push_back(temp_input_element);

  // Debug out the formatted input
  if (DEBUG_OUT) {
    std::cout << "Format input: " << std::endl;
    for (auto iter_input : this->m_format_input) {
      std::cout << "set: " << std::hex << iter_input.set_mask;
      std::cout << ", reset: " << std::hex << iter_input.reset_mask;
      std::cout << ", unchange: " << std::hex << iter_input.unchange_mask;
      std::cout << ", overwrite: " << std::hex << iter_input.overwrite_one_mask;
      std::cout << ", floating: " << std::hex << iter_input.floating_mask
                << std::endl;
      for (auto iter : iter_input.mem_entry) {
        std::cout << "[" << std::dec << iter.first << "]: " << iter.second
                  << std::endl;
      }
    }
  }
}

/**
 * @brief Get the mask as integer value from string
 *
 * @param str input as string
 * @return unsigned long mask to set bits
 */
unsigned long day14::get_set_mask(std::string str) {
  unsigned long ret_val = 0;

  if (str != "") {
    for (int i = 0; i < str.size(); ++i) {
      if (str.at(str.size() - 1 - i) == '1') {
        ret_val = ret_val | (1ULL << i);
      }
    }
  }

  return (ret_val);
}

/**
 * @brief Get the mask as integer from string value
 *
 * @param str input as string
 * @return unsigned long reset mask
 */
unsigned long day14::get_reset_mask(std::string str) {
  unsigned long ret_val = SAT_MASK;  // Set all lower 36 bit

  if (str != "") {
    for (int i = 0; i < str.size(); ++i) {
      if (str.at(str.size() - 1 - i) == '0') {
        ret_val = ret_val & ~(1ULL << i);
      }
    }
  }

  return (ret_val);
}

/**
 * @brief Return unchange mask containing a '1' on position not to be changed
 * and '0' are ignored, so only take over the value on which this mask is '1'
 *
 * @param str input string with 0, X, and 1
 * @return unsigned long return value as int mask
 */
unsigned long day14::get_unchage_mask(std::string str) {
  unsigned long ret_val = 0;

  if (str != "") {
    for (int i = 0; i < str.size(); ++i) {
      if (str.at(str.size() - 1 - i) == '0') {
        ret_val = ret_val | (1ULL << i);
      }
    }
  }

  return (ret_val);
}

/**
 * @brief Return the bit positions with '1' on which the value is overwritten
 * with '1'. Only the bit position in value are overwritten with one having this
 * mask with one
 *
 * @param str input string with 0, X, and 1
 * @return unsigned long maks for overwriting with one
 */
unsigned long day14::get_overwriteone_mask(std::string str) {
  unsigned long ret_val = 0;

  if (str != "") {
    for (int i = 0; i < str.size(); ++i) {
      if (str.at(str.size() - 1 - i) == '1') {
        ret_val = ret_val | (1ULL << i);
      }
    }
  }

  return (ret_val);
}

/**
 * @brief Return the mask with the bit position having a floating bit. In case
 * the returned int has a '1' on the postiont the bit is a flaoting bit and all
 * combinations have to be applied
 *
 * @param str input string with 0, X, and 1
 * @return unsigned long
 */
unsigned long day14::get_floating_mask(std::string str) {
  unsigned long ret_val = 0;

  if (str != "") {
    for (int i = 0; i < str.size(); ++i) {
      if (str.at(str.size() - 1 - i) == 'X') {
        ret_val = ret_val | (1ULL << i);
      }
    }
  }

  return (ret_val);
}

/**
 * @brief Calculate the sum over the memory and return it
 *
 * @return unsigned long
 */
unsigned long long day14::calc_sum_mem(void) {
  unsigned long long ret_val = 0;

  for (auto iter : this->m_mem) {
    ret_val += iter.second;
  }

  this->m_sum_mem = ret_val;
  return (ret_val);
}

/**
 * @brief Apply the unchange mask on putting the bits where the mask is '1' into
 * the new address as return value
 *
 * @param address Input address on which the mask is applied
 * @param mask The mask with the '1' on position where to take over the value of
 * the address into the return
 * @return unsigned long New address with the bits taken over unchanged
 */
unsigned long day14::apply_unchange(unsigned long address, unsigned long mask) {
  std::bitset<NUM_BITS_ADDRESS> bit_mask_temp = mask;
  std::bitset<NUM_BITS_ADDRESS> bit_address_temp = address;
  std::bitset<NUM_BITS_ADDRESS> ret_val;

  for (int current_bit_pos = 0; current_bit_pos < NUM_BITS_ADDRESS;
       current_bit_pos++) {
    if (bit_mask_temp[current_bit_pos] == true) {
      // In case the flag is set just take over the address bit
      ret_val[current_bit_pos] = bit_address_temp[current_bit_pos];
    }
  }

  return (ret_val.to_ulong());
}

unsigned long day14::apply_overwrite(unsigned long address,
                                     unsigned long mask) {
  std::bitset<NUM_BITS_ADDRESS> bit_mask_temp = mask;
  std::bitset<NUM_BITS_ADDRESS> bit_address_temp = address;
  std::bitset<NUM_BITS_ADDRESS> ret_val = address;

  for (int current_bit_pos = 0; current_bit_pos < NUM_BITS_ADDRESS;
       current_bit_pos++) {
    if (bit_mask_temp[current_bit_pos] == true) {
      // In case the flag is set overwrite with one
      ret_val.set(current_bit_pos, true);
    }
  }

  return (ret_val.to_ulong());
}

std::vector<unsigned long> day14::apply_floating(unsigned long address,
                                                 unsigned long mask) {
  unsigned long number_floating_bits = 0;
  unsigned long counter_comb = 0;
  unsigned long current_address = 0;
  unsigned long number_of_combintations = 0;
  std::vector<unsigned long> ret_val;
  std::bitset<NUM_BITS_ADDRESS> bit_mask_temp = mask;
  std::bitset<NUM_BITS_ADDRESS> bit_address_temp = address;
  std::bitset<NUM_BITS_ADDRESS> bit_address_calc;

  // Get number of floating bits
  for (int i = 0; i < bit_mask_temp.size(); ++i) {
    if (bit_mask_temp[i] == true) {
      ++number_floating_bits;
    }
  }

  // Two in power of number of bits are all possible combinations
  number_of_combintations = pow(2, number_floating_bits);

  // Calc all combinations
  for (int i = 0; i < number_of_combintations; ++i) {
    bit_address_calc =
        counter_comb;  // bitset used to access the single position of a bit

    // Current position of the bit to be take over on position of floating bit
    unsigned long pos_in_comb_mask = 0;

    // Check in the address for the floating bits and copy over the bit in the
    // current combination on the floating position. The number of bits in
    // combination must fit with the number of floating bits in the address
    for (int current_bit_pos = 0; current_bit_pos < NUM_BITS_ADDRESS;
         current_bit_pos++) {
      if (bit_mask_temp[current_bit_pos] == true) {
        bit_address_temp[current_bit_pos] = bit_address_calc[pos_in_comb_mask];
        ++pos_in_comb_mask;
      }
    }
    // Add address to the return vector
    ret_val.push_back(bit_address_temp.to_ulong());
    // count up for next address combination
    ++counter_comb;
  }

  return (ret_val);
}
