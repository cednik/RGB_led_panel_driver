/*
 * mutex.cpp
 *
 *  Created on: 3. 1. 2020
 *      Author: Jakub Streit <xstrei03@stud.feec.vutbr.cz>
 */

#include "mutex.hpp"

#include <cassert>

namespace std {

mutex::mutex()
	: __handle(xSemaphoreCreateMutex())
{
	assert(__handle);
}

mutex::~mutex() {
	assert(__handle);
	vSemaphoreDelete(__handle);
	__handle = NULL;
}

void mutex::lock() {
	assert(__handle);
	xSemaphoreTake(__handle, portMAX_DELAY);
}

bool mutex::try_lock() {
	assert(__handle);
	return xSemaphoreTake(__handle, 0) == pdTRUE;
}

void mutex::unlock() {
	assert(__handle);
	xSemaphoreGive(__handle);
}

mutex::__native_type mutex::native_handle() {
	return __handle;
}

} // namespace std
