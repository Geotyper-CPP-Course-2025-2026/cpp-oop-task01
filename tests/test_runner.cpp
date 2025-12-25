#include "Node.hpp"
#include "File.hpp"
#include "Directory.hpp"
#include <iostream>
#include <cassert>
#include <memory>
#include <cstdlib>

// Вспомогательная функция для проверки с информативными сообщениями
void check(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "❌ FAILED: " << message << std::endl;
        std::exit(1); // Завершаем с ошибкой для автопроверки
    }
}

void testFileSystem() {
    // Создаем структуру:
    // Root (Folder)
    // ├── doc.txt (100 bytes)
    // └── Images (Folder)
    //     ├── photo.png (500 bytes)
    //     └── icon.png (50 bytes)
    
    auto root = std::make_shared<Directory>("root");
    auto file1 = std::make_shared<File>("doc.txt", 100);
    
    auto imgDir = std::make_shared<Directory>("images");
    auto img1 = std::make_shared<File>("photo.png", 500);
    auto img2 = std::make_shared<File>("icon.png", 50);
    
    imgDir->add(img1);
    imgDir->add(img2);
    
    root->add(file1);
    root->add(imgDir);

    // Главная проверка: размер root должен быть 650 (100 + 500 + 50)
    check(root->getSize() == 650, "Root size should be 650, got " + std::to_string(root->getSize()));
    std::cout << "✓ Root size test passed: " << root->getSize() << " bytes" << std::endl;
    
    // Проверка вложенной папки отдельно
    check(imgDir->getSize() == 550, "Images folder size should be 550, got " + std::to_string(imgDir->getSize()));
    std::cout << "✓ Images folder size test passed: " << imgDir->getSize() << " bytes" << std::endl;
    
    // Проверка отдельных файлов
    check(file1->getSize() == 100, "doc.txt size should be 100");
    check(img1->getSize() == 500, "photo.png size should be 500");
    check(img2->getSize() == 50, "icon.png size should be 50");
    std::cout << "✓ Individual file size tests passed" << std::endl;
}

void testEmptyDirectory() {
    auto emptyDir = std::make_shared<Directory>("empty");
    check(emptyDir->getSize() == 0, "Empty directory size should be 0");
    std::cout << "✓ Empty directory test passed" << std::endl;
}

void testDeepNesting() {
    // Тест глубокой вложенности
    // root -> level1 -> level2 -> level3 -> file.txt (42 bytes)
    
    auto level3 = std::make_shared<Directory>("level3");
    level3->add(std::make_shared<File>("file.txt", 42));
    
    auto level2 = std::make_shared<Directory>("level2");
    level2->add(level3);
    
    auto level1 = std::make_shared<Directory>("level1");
    level1->add(level2);
    
    auto root = std::make_shared<Directory>("root");
    root->add(level1);
    
    check(root->getSize() == 42, "Deep nesting size should be 42, got " + std::to_string(root->getSize()));
    std::cout << "✓ Deep nesting test passed" << std::endl;
}

void testMultipleFiles() {
    auto dir = std::make_shared<Directory>("documents");
    dir->add(std::make_shared<File>("a.txt", 10));
    dir->add(std::make_shared<File>("b.txt", 20));
    dir->add(std::make_shared<File>("c.txt", 30));
    
    check(dir->getSize() == 60, "Multiple files size should be 60, got " + std::to_string(dir->getSize()));
    std::cout << "✓ Multiple files test passed" << std::endl;
}

void testMixedContent() {
    auto root = std::make_shared<Directory>("root");
    
    // Добавляем файлы
    root->add(std::make_shared<File>("file1.txt", 100));
    
    // Добавляем подпапку с файлами
    auto subDir1 = std::make_shared<Directory>("sub1");
    subDir1->add(std::make_shared<File>("file2.txt", 200));
    root->add(subDir1);
    
    // Добавляем еще один файл
    root->add(std::make_shared<File>("file3.txt", 50));
    
    // Добавляем пустую папку
    auto emptyDir = std::make_shared<Directory>("empty");
    root->add(emptyDir);
    
    // Общий размер: 100 + 200 + 50 + 0 = 350
    check(root->getSize() == 350, "Mixed content size should be 350, got " + std::to_string(root->getSize()));
    std::cout << "✓ Mixed content test passed" << std::endl;
}

void testZeroSizeFile() {
    // Тест на файлы нулевого размера
    // Иногда ученики пишут логику так, что она игнорирует файлы с нулевым размером
    auto dir = std::make_shared<Directory>("logs");
    dir->add(std::make_shared<File>("empty.log", 0));
    dir->add(std::make_shared<File>("data.txt", 100));
    
    check(dir->getSize() == 100, "Directory with 0-byte file should work correctly, got " + std::to_string(dir->getSize()));
    
    // Проверяем, что 0-байтный файл тоже считается
    auto zeroDir = std::make_shared<Directory>("zeros");
    zeroDir->add(std::make_shared<File>("a", 0));
    zeroDir->add(std::make_shared<File>("b", 0));
    zeroDir->add(std::make_shared<File>("c", 0));
    
    check(zeroDir->getSize() == 0, "Directory with only 0-byte files should have size 0");
    std::cout << "✓ Zero size file test passed" << std::endl;
}

void testNullptrHandling() {
    // "Коварный" тест: проверка на nullptr (Уровень 6/10)
    // Проверяет защитное программирование - ученик должен обработать nullptr
    auto dir = std::make_shared<Directory>("test");
    dir->add(std::make_shared<File>("file.txt", 100));
    
    // Пытаемся добавить nullptr - это должно либо игнорироваться, либо вызывать исключение
    // Но не должно вызывать segfault
    try {
        dir->add(nullptr);
        // Если не вызвало исключение, проверяем, что размер не изменился
        check(dir->getSize() == 100, "Adding nullptr should not affect directory size");
        std::cout << "✓ Nullptr handling test passed (nullptr ignored)" << std::endl;
    } catch (...) {
        // Если вызвано исключение - это тоже корректное поведение
        std::cout << "✓ Nullptr handling test passed (exception thrown)" << std::endl;
    }
}

int main() {
    std::cout << "=== Running File System Tests ===" << std::endl;
    
    testFileSystem();
    testEmptyDirectory();
    testDeepNesting();
    testMultipleFiles();
    testMixedContent();
    testZeroSizeFile();
    testNullptrHandling();
    
    std::cout << "\n=== All tests passed! ===" << std::endl;
    return 0;
}
