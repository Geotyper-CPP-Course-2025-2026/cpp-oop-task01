#pragma once
#include <string>

class Node {
protected:
    std::string name;
public:
    Node(std::string n) : name(n) {}
    virtual ~Node() {}
    
    virtual size_t getSize() const = 0; // "Изюминка": метод один, а логика разная
    std::string getName() const { return name; }
};
