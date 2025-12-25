#include "File.hpp"

// TODO: Реализовать конструктор. 
// Не забудьте передать имя в базовый класс Node
File::File(std::string name, size_t size) : Node(name) {
    // Подсказка: инициализируйте fileSize
}

size_t File::getSize() const {
    // TODO: Вернуть размер файла
    return 0;
}
