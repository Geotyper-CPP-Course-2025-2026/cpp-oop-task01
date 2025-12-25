#pragma once
#include "Node.hpp"

class File : public Node {
private:
    size_t fileSize;
public:
    File(std::string name, size_t size); // Ученик реализует сам
    size_t getSize() const override; 
};
