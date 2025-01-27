#pragma once

#include "logger.hpp"
#include <iostream>

struct Stack {
    int stack[16]; 
    int top = -1;
    int cap = 16;

    Stack() {
        for (int i = 0; i < cap; i++) {
            stack[i] = 0;
        }
    }

    void push(int data) {
        if (top < cap) {
            top++;
            stack[top] = data;
        } else {
            Logger::log("CRITICAL", "Failed to push data to stack. Stack is full.");
        }
    }

    void pop() {
        if (top < 0) {
            Logger::log("CRITICAL", "Failed to pop data from stack. Stack is empty.");
        } else {
            top--;
        }
    }

    int get_top() {
        if (top < 0) {
            Logger::log("CRITICAL", "Failed to get top of stack. Stack is empty.");
            return -1;
        } else {
            return stack[top];
        }
    }
};
