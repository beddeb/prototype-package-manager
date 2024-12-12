#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "include/package_manager.hpp"


void processCommand(PackageManager& pm) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string command;
    ss >> command;

    if (command == "install") {
        if (ss.eof()) {
            std::cerr << "Error: Insufficient data. Package name and version are required.\n";
            return;
        }

        std::string packageName;
        int major, minor, patch;
        ss >> packageName >> major >> minor >> patch;

        if (ss.fail() || major <= 0 || minor < 0 || patch < 0) {
            std::cerr << "Error: Invalid data format or version. Version must be positive.\n";
            return;
        }

        std::vector<std::string> dependencies;
        std::string dep;
        while (ss >> dep) {
            dependencies.push_back(dep);
        }

        Package pkg(packageName, Version(major, minor, patch));
        for (const auto& dep : dependencies) {
            pkg.dependencies.add(dep);
        }

        try {
            pm.install(pkg);
            std::cout << "Package '" << packageName << "' installed successfully.\n";
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    } else if (command == "remove") {
        std::string packageName;
        int major, minor, patch;
        ss >> packageName >> major >> minor >> patch;

        if (ss.fail() || major <= 0 || minor < 0 || patch < 0) {
            std::cerr << "Error: Invalid data format or version. Version must be positive.\n";
            return;
        }

        Package pkg(packageName, Version(major, minor, patch));
        try {
            pm.remove(pkg);
            std::cout << "Package '" << packageName << "' removed successfully.\n";
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    } else if (command == "list") {
        PackageManager::printInstalledPackages(pm);
    } else if (command == "show") {
        std::string packageName;
        ss >> packageName;
        Package* pkg = pm.findPackage(packageName);
        if (pkg) {
            PackageManager::printPackageInfo(*pkg);
        } else {
            std::cout << "Package '" << packageName << "' not found.\n";
        }
    } else if (command == "exit") {
        pm.saveToFile("../data/pgk.txt"); // Сохранение в файл при выходе
        exit(0);
    } else if (command == "help") {
        std::cout << "Available commands:\n"
                  << "  install <package_name> <major> <minor> <patch> [dependencies...]\n"
                  << "  remove <package_name> <major> <minor> <patch>\n"
                  << "  list\n"
                  << "  show <package_name>\n"
                  << "  help\n"
                  << "  exit\n";
    } else {
        std::cerr << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

int main() {
    PackageManager pm;
    pm.loadFromFile("../data/pgk.txt"); // Загрузка из файла при старте
    std::cout << "Package Manager started. Type 'help' for commands.\n";

    while (true) {
        std::cout << "> ";
        try {
            processCommand(pm);
        } catch (const std::runtime_error& e) {
            if (std::string(e.what()) == "exit" || std::string(e.what()) == "EOF") {
                break;
            } else {
                std::cerr << "An unexpected error occurred: " << e.what() << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        }
    }
    return 0;
}