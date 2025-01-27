#pragma once

#include <iostream>
#include "logger.hpp"

struct PriorityQueue {
    struct Node {
        int value = 0;
        int priority = 0;
        Node() = default;
        Node(int value, int priority) : value(value), priority(priority) { }
    };

    Node** heap;
    int size;

    PriorityQueue() {
        heap = new Node*[9];
        size = -1;
    }

    // Create a constructor that deep copies the priority queue
    PriorityQueue(const PriorityQueue& other) {
        heap = new Node*[9];
        size = other.size;
        for (int i = 0; i <= size; i++) {
            heap[i] = new Node(other.heap[i]->value, other.heap[i]->priority);
        }
    }

    int enqueue(int value, int priority) {
        // Check if the value is already in the priority queue
        for (int i = 0; i <= size; i++) {
            if (heap[i]->value == value) {
                return -1;
            }
        }
        size++;
        heap[size] = new Node(value, priority);

        int current = size;

        // Move the current node up the tree until it is in the right place
        while (current > 0 && heap[current]->priority < heap[parent(current)]->priority) {
            Node* tmp = heap[current];
            heap[current] = heap[parent(current)];
            heap[parent(current)] = tmp;
            current = parent(current);
        }
        return 0;
    }

    void dequeue() {
        if (size < 0) {
            Logger::log("WARN", "Failed to dequeue from priority queue. Queue is empty.");
            return;
        }
        Node* tmp = heap[size];
        delete heap[0];
        heap[0] = tmp;
        heap[size] = nullptr;
        size--;

        rearrange(0);
    }

    void rearrange(int index) {
        if (size <= 0) {
            return;
        }

        // Get the left and right child of the current index
        int left = left_child(index);
        int right = right_child(index);

        // Set the smallest to the current index
        int smallest = index;

        // If the left child is smaller than the parent, set the smallest to the left child
        if (left < size + 1 && heap[left]->priority < heap[index]->priority) {
            smallest = left;
        }

        // If the right child is smaller than the left child, set the smallest to the right child
        if (right < size + 1 && heap[right]->priority < heap[smallest]->priority) {
            smallest = right;
        }

        // If the smallest is not the current index, swap the smallest with the current index
        if (smallest != index) {

            // Swap the smallest with the current index
            Node* temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;

            // Recursively heapify the affected sub-tree
            rearrange(smallest);
        }
    }

    // Get the most prioritized node in the priority queue
    Node* get_min() {
        if (size < 0) {
            return nullptr;
        }
        return heap[0];
    }
    bool is_empty() {
        return (heap[0] == nullptr);
    }

    // For calculating where the parent, left child, and right child of a node are
    int parent(int i) { return (i - 1) / 2; }
    int left_child(int i) { return 2*i + 1; }
    int right_child(int i) { return 2*i + 2; }

};
