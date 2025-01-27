#include "logger.hpp"
#include "elevator.hpp"
#include "stack.hpp"
#include <limits>
#include <sstream>
#include <string>

std::string get_direction(std::string_view prompt);

int get_floor(std::string_view prompt);

int main() {
    Logger log;
    int current_floor = get_floor("Elevator's current floor (1-9)");
    std::string current_direction = get_direction("Elevator's current direction (up/down)");
    int floor = get_floor("Enter your current floor (1-9)");
    std::string direction = std::move(get_direction("Enter your direction (up/down)"));

    Elevator elevator(current_floor, current_direction);

    Queue queue;

    bool is_valid_floor = false;
    std::string elev_floors;
    std::string num;

    // Prompt the user for the floors they would like to visit
    while (!is_valid_floor) {
        try {
            std::cout << "Floors: ";
            std::getline(std::cin >> std::ws, elev_floors);

            // Use istringstream to split the string by spaces
            std::istringstream iss(elev_floors);
            is_valid_floor = true;

            // While there are still numbers in the string, add them to the queue
            while (iss >> num) {
                int value = std::stoi(num);
                if (value < 1 || value > 9) {
                    is_valid_floor = false;
                    queue.clear();
                    break;
                }
                queue.enqueue(value);
            }
        } catch (std::invalid_argument) {
            is_valid_floor = false;
            queue.clear();
        }
    }
    while (!queue.is_empty()) {
        elevator.add_floor(queue.front());
        queue.dequeue();
    }
    elevator.run(floor);

    return 0;
}

int get_floor(std::string_view prompt) {
    int floor = 0;
    // Continue to prompt the user until they enter a valid floor
    while (true) {
        std::cout << prompt << ": ";
        std::cin >> floor;
        if (!std::cin.fail() && floor >= 1 && floor <= 9) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return floor;
}

std::string get_direction(std::string_view prompt) {
    std::string floor = "";
    // Continue to prompt the user until they enter a valid direction
    while (true) {
        std::cout << prompt << ": ";
        std::cin >> floor;
        if (!std::cin.fail() && (floor == "up" || floor == "down")) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return floor;
}
