//
// Created by Lokotochek on 08.05.16.
//

#include "Futex.h"

void Futex::lock() {
    auto me = std::this_thread::get_id();
    auto expected = thread::id();
    while (!ownerId.compare_exchange_weak(expected, me, memory_order_acquire)) {
        this_thread::yield();
        expected = thread::id();
    }
}

bool Futex::try_lock() {
    auto me = std::this_thread::get_id();
    auto expected = thread::id();
    return ownerId.compare_exchange_strong(expected, me, memory_order_acquire);
}

void Futex::unlock() {
    try {
        auto me = std::this_thread::get_id();
        auto expected = thread::id();
        if (!ownerId.compare_exchange_strong(me, expected, memory_order_release)) {
            throw new futexException("Unlock of foreign futex");
        }
    } catch (futexException &fex) {
        cerr << fex.getMessage() << endl;
    }
}