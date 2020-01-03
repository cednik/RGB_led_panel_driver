/*
 * mutex.hpp
 *
 *  Created on: 3. 1. 2020
 *      Author: Jakub Streit <xstrei03@stud.feec.vutbr.cz>
 */

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <mutex>

#include "FreeRTOS.h"
#include "semphr.h"

namespace std {

class mutex
{
public:
    typedef SemaphoreHandle_t __native_type;

    mutex(const mutex&) = delete;
    mutex& operator=(const mutex&) = delete;

    mutex() noexcept;
    ~mutex();

    void init();

    void lock();
    bool try_lock() noexcept;
    void unlock();

    __native_type native_handle() noexcept;
private:
    __native_type __handle;
};

} // namespace std


#endif /* MUTEX_HPP_ */
