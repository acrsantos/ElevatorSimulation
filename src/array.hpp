#pragma once

#include <string>

struct Array {
    struct State {
        State() = default;
        State(int current_floor, std::string direction, int next_floor)
            : current_floor(current_floor), direction(std::move(direction)),
            next_floor(next_floor) {}
        int current_floor;
        std::string direction;
        int next_floor;
    };

    State* data;
    size_t size;
    size_t capacity;

    Array() : data(new State[12]), size(0), capacity(12) { }
    Array(int capacity) : data(new State[capacity]), size(0), capacity(12) { }
    State& operator[](size_t index) const {
        if (size < index) {
            throw -1;
        }
        return data[index];
    }
    void resize(size_t new_size) {
        State* new_array = new State[new_size];
        size = (new_size < size) ? new_size : size;
        for (size_t i = 0; i < size; i++) {
            new_array[i] = data[i];
        }
        delete[] data;
        data = new_array;
    }
    void add(State state) {
        if (size > capacity) {
            resize(capacity * 2);
        }
    }
};
