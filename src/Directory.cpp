#include "Directory.hpp"

Directory::Directory(std::string name) : Node(name) {
    // Инициализация: имя уже передано в базовый класс Node
}

void Directory::add(std::shared_ptr<Node> node) {
    // TODO: Реализовать добавление в вектор children
}

size_t Directory::getSize() const {
    // TODO: Реализовать рекурсивный подсчет размера всех вложенных узлов
    return 0; 
}
