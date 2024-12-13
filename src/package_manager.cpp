#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/package_manager.hpp"


void PackageManager::saveToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    for (const auto& package : installed_packages) {
        outFile << package.name << " "
                << package.version.major << " "
                << package.version.minor << " "
                << package.version.patch;

        if (package.dependencies.getSize()) {
            for (const auto& dep : package.dependencies) {
                outFile << " " << dep;
            }
        }
        outFile << "\n";
    }
    outFile.close();
}

void PackageManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "Could not open file for reading: " + filename << "\n";
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string packageName;
        int major, minor, patch;

        if (!(ss >> packageName >> major >> minor >> patch)) {
            std::cerr << "Error: Invalid data format in file.\n";
            continue;
        }

        if (!PackageManager::is_valid_name(packageName)){
            std::cerr << "Error: Invalid package name format. Expected: a string consisting only of letters and numbers, with the first character being a letter.\n";
            continue;
        }

        if (major <= 0 || minor < 0 || patch < 0) {
            std::cerr << "Error: Invalid version in file. Version must be positive.\n";
            continue;
        }

        Package package(packageName, Version(major, minor, patch));

        std::string dep;
        while (ss >> dep) {
            if (!PackageManager::is_valid_name(dep)){
                std::cerr << "Error: Invalid dependency name format. Expected: a string consisting only of letters and numbers, with the first character being a letter.\n";
                continue;
            }
            package.dependencies.add(dep);
        }
        try {
            install(package);
        } catch (const std::runtime_error& e) {
            if (std::string(e.what()) != "Dependencies not satisfied" && std::string(e.what()).find("Package '") != 0){
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    }

    inFile.close();
}

void PackageManager::printPackageInfo(const Package& pkg) {
    std::cout << "Package: " << pkg.name
              << " (v" << pkg.version.major
              << "." << pkg.version.minor
              << "." << pkg.version.patch << ")\n";

    if (pkg.dependencies.getSize() > 0) {
        std::cout << "Dependencies: ";
        for (const auto& dep : pkg.dependencies) {
            std::cout << dep << " ";
        }
        std::cout << "\n";
    }
}

void PackageManager::printInstalledPackages(const PackageManager& pm) {
    std::cout << "\nInstalled packages:\n";
    for (const auto& pac : pm.getInstalledPackages()) {
        printPackageInfo(pac);
    }
    std::cout << "------------------------\n";
}

bool PackageManager::is_valid_name(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    if (!isalpha(name[0])) {
        return false;
    }
    for (size_t i = 1; i < name.size(); ++i) {
        if (!isalnum(name[i]) && name[i] != '_') {
            return false;
        }
    }
    return true;
}