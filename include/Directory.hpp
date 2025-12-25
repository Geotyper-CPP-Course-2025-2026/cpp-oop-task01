#pragma once
#include "Node.hpp"
#include <vector>
#include <memory>

class Directory : public Node {
private:
    // Храним умные указатели, чтобы не было утечек (уровень 5/10)
    std::vector<std::shared_ptr<Node>> children;
public:
    Directory(std::string name);
    
    void add(std::shared_ptr<Node> node); // Добавление файла или подпапки
    size_t getSize() const override;      // Рекурсивный подсчет
};
