/*
 * print.hpp
 *
 *  Created on: 3. 1. 2020
 *      Author: Jakub Streit <xstrei03@stud.feec.vutbr.cz>
 */

#ifndef PRINT_HPP_
#define PRINT_HPP_

#include "fsl_debug_console.h"
#include "fmt/format.h"
#include "mutex.hpp"

extern std::mutex __print_mutex;

template <typename S, typename... Args>
int print(const S& format_str, Args&&... args) {
	std::lock_guard<std::mutex> guard(__print_mutex);
	fmt::memory_buffer buf;
	fmt::format_to(buf, format_str, args...);
	return DbgConsole_SendDataReliable(reinterpret_cast<uint8_t*>(buf.data()), buf.size());
}


#endif /* PRINT_HPP_ */
