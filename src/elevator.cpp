#include "array.hpp"
#include "queue.hpp"
#include "logger.hpp"
#include "priority_queue.hpp"
#include "elevator.hpp"
#include "util.hpp"

#include <ios>
#include <iostream>
#include <limits>
#include <string_view>
#include <thread>
#include <optional>

int get_floor(std::string_view prompt);

Elevator::Elevator(int current_floor, std::string direction)
: current_floor(current_floor), direction(std::move(direction)) {
    add_floor(current_floor);
    next_floor = 0;
}

// Start the elevator
void Elevator::run(int user_floor) {
    add_floor(user_floor);
    move_elevator(user_floor);
    print_status();

    int target_floor = get_floor("Target floor");
    add_floor(target_floor);
    move_elevator(target_floor);

    print_status();
    recently_visited.push(current_floor);
    print_recent_floors();
}

void Elevator::print_status() {
    std::cout << "Current Floor: " << current_floor << "   Next Floor: " << next_floor << "   Direction: " << direction << '\n';
    states.add(Array::State(current_floor, direction, next_floor));
}

void Elevator::print_recent_floors() {
    std::cout << "Recent floor trace stack: ";
    // While the stack is not empty, print the top element and pop it
    while (recently_visited.top != -1) {
        std::cout << recently_visited.get_top() << " ";
        recently_visited.pop();
    }
    std::cout << std::endl;
}

void Elevator::move_elevator(int user_floor) {
    // While the target floor is not reached, move the elevator
    while (user_floor != current_floor) {
        print_status();

        // Random chance to simulate failure
        failure();
        recently_visited.push(current_floor);
        Logger::log("INFO", "Reached floor " + std::to_string(current_floor));
        // Set the current floor to the highest priority floor and dequeue it
        current_floor = floor_queue.get_min()->value;
        floor_queue.dequeue();

        // If there is still floors to visit in queue, set the next floor and direction
        if (!floor_queue.is_empty()) {
            next_floor = floor_queue.get_min()->value;
            direction = (next_floor > current_floor) ? "up" : "down";
            Logger::log("INFO", "Moving to floor " + std::to_string(next_floor));
        }
    }
}

void Elevator::add_floor(int floor) {
    if (floor == current_floor) return;

    // Calculate the priority of the floor
    // lower value = higher priority
    int priority = abs(floor - current_floor);

    // If the elevator's direction is opposite from user specified direction,
    // lower the priority of the floor being enqueued.
    if (!(this->direction == "up" && current_floor < floor) &&
        !(this->direction == "down" && current_floor > floor)) {
        priority += 9;
    }

    int status = floor_queue.enqueue(floor, priority);
    if (status == -1) {
        return;
    }
    Logger::log("INFO", "Added floor " + std::to_string(floor) + " to destination queue");
}

void Elevator::failure() {
    int chance = Util::generate_rand(1, 100);
    if (chance <= 2 ) {
        std::cout << "\nThe elevator is stuck. Requesting for help\n";
        Logger::log("CRITICAL", "Elevator is stuck. Sending help request");
        std::exit(1);
    } else if (chance <= 4) {
        std::cout << "\nThere is a power outage. Requesting for help\n";
        Logger::log("CRITICAL", "Power outage. Sending help request");
        std::exit(1);
    }
}
