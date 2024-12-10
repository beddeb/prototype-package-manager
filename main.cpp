#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "include/package_manager.hpp" // Или правильный путь к package_manager.hpp


// Функция для обработки пользовательского ввода
void processCommand(PackageManager& pm) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string command;
    ss >> command;

    if (command == "install") {
        std::string packageName;
        int major, minor, patch;
        ss >> packageName >> major >> minor >> patch;
        std::vector<std::string> dependencies;
        std::string dep;
        while (ss >> dep) {
            dependencies.push_back(dep);
        }

        Package pkg(packageName, Version(major, minor, patch));
        for (const auto& i : dependencies){
            pkg.dependencies.add(i);
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
        exit(0);
        return;
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
    std::cout << "Package Manager started. Type 'help' for commands.\n";

    while (true) {
        std::cout << "> ";
        try {
            processCommand(pm);
            if (std::cin.eof()){
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        }

    }
    std::cout << "Package Manager stopped.\n";
    return 0;
}