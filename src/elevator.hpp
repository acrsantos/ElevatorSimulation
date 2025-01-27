#pragma once

#include "array.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "priority_queue.hpp"
#include <string>


std::string get_direction();

int get_floor();

class Elevator {
public:
    Elevator(int current_floor, std::string direction);
    void run(int user_floor);
    void add_floor(int floor);
    void move_elevator();
    void move_elevator(int user_floor);
    void print_status();
    void print_recent_floors();
    void failure();

private:
    int current_floor;
    std::string direction;
    int next_floor;

    PriorityQueue floor_queue;
    Queue queue;
    Stack recently_visited;
    Array states;
};
