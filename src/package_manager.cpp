#include <iostream>
#include "../include/package_manager.hpp"


// Вспомогательная функция для вывода информации о пакете
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

// Вспомогательная функция для вывода всех установленных пакетов
void PackageManager::printInstalledPackages(const PackageManager& pm) {
    std::cout << "\nInstalled packages:\n";
    for (const auto& pkg_pair : pm.getInstalledPackages()) {
        printPackageInfo(pkg_pair.first);
    }
    std::cout << "------------------------\n";
}