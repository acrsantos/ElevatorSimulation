#pragma once

#include "logger.hpp"

struct Queue {
    struct Node {
        Node* next;
        int value;
        Node() = default;
        Node(int value) {
            this->value = value;
        }
    };
    Node* head;
    Node* tail;

    Queue() {
        head = nullptr;
        tail = nullptr;
    }

    void enqueue(int data) {
        Node* node = new Node(data);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    void dequeue() {
        if (head == nullptr) {
            Logger::log("WARN", "Failed to dequeue from queue. Queue is empty.");
            return;
        } else {
            Node* temp_node = head;
            head = head->next;
            delete temp_node;
        }
    }

    void clear() {
        while (head != nullptr) {
            dequeue();
        }
    }

    int front() {
        if (head == nullptr) {
            Logger::log("WARN", "Failed to get front of queue. Queue is empty.");
            return -1;
        }

        return head->value;
    }

    void print() {
        Node* tmp = head;
        std::cout << "Queue: ";
        while (tmp != nullptr) {
            std::cout << tmp->value << ' ';
            tmp = tmp->next;
        }
    }

    bool is_empty() {
        return (head == nullptr);
    }
};

