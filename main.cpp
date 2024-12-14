#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "include/package_manager.hpp"

#include "tests/func/func_sequences.hpp"
#include "tests/func/func_hash_table.hpp"
#include "tests/func/func_iset.hpp"
#include "tests/func/func_package_manager.hpp"

#include "tests/chrono/chrono_sequences.hpp"
#include "tests/chrono/chrono_hash_table.hpp"
#include "tests/chrono/chrono_iset.hpp"

#include "graphics/plot.hpp"


void clearConsole() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/MacOS
#endif
}


void processCommand(PackageManager &pm) {
    Sequence<DataSeries> plot_data;
    std::string command;
    std::getline(std::cin, command);
    std::stringstream ss(command);
    ss >> command;

    if (command == "install") {
        std::string packageName;
        int major, minor, patch;
        std::vector<std::string> dependencies;

        if (!(ss >> packageName >> major >> minor >> patch)) {
            std::cerr << "Error: Insufficient data. Package name and version are required.\n";
            return;
        }

        if (major <= 0 || minor < 0 || patch < 0) {
            std::cerr << "Error: Invalid data format or version. Version must be positive.\n";
            return;
        }

        std::string dep;
        while (ss >> dep) {
            dependencies.push_back(dep);
        }

        Package pkg(packageName, Version(major, minor, patch));
        for (const auto &c_dep: dependencies) {
            pkg.dependencies.add(c_dep);
        }

        try {
            pm.install(pkg);
            std::cout << "Package '" << packageName << "' installed successfully.\n";
        } catch (const std::runtime_error &e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    } else if (command == "remove") {
        std::string packageName;
        int major, minor, patch;

        if (!(ss >> packageName >> major >> minor >> patch)) {
            std::cerr << "Error: Insufficient data. Package name and version are required.\n";
            return;
        }

        if (major <= 0 || minor < 0 || patch < 0) {
            std::cerr << "Error: Invalid data format or version. Version must be positive.\n";
            return;
        }

        Package pkg(packageName, Version(major, minor, patch));
        try {
            pm.remove(pkg);
            std::cout << "Package '" << packageName << "' removed successfully.\n";
        } catch (const std::runtime_error &e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    } else if (command == "list") {
        PackageManager::printInstalledPackages(pm);
    } else if (command == "show") {
        std::string packageName;
        if (!(ss >> packageName)) {
            std::cerr << "Error: Package name is required.\n";
            return;
        }

        Package *pkg = pm.findPackage(packageName);
        if (pkg) {
            PackageManager::printPackageInfo(*pkg);
        } else {
            std::cout << "Package '" << packageName << "' not found.\n";
        }
    } else if (command == "clear") {
        clearConsole();
        std::cout << "Package Manager started. Type 'help' for commands.\n";
    } else if (command == "fseq") {
        testSequence();
    } else if (command == "flistseq") {
        testListSequence();
    } else if (command == "farrseq") {
        testArraySequence();
    } else if (command == "fhasht") {
        testHashTable();
    } else if (command == "fiset") {
        testISet();
    } else if (command == "fpkgmn") {
        testPackageManager();
    } else if (command == "chseq") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        chronoSequence(values, 100);
    } else if (command == "chlistseq") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        chronoListSequence(values, 100);
    } else if (command == "charrseq") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        chronoArraySequence(values, 100);
    } else if (command == "chhasht") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        chronoHashTable(values);
    } else if (command == "chiset") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        chronoISet(values);
    } else if (command == "pseq") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        plot_data.add(DataSeries("Sequence", Color::Red));
        plot_data.add(DataSeries("std::vector", Color::Blue));
        plotInit<Sequence<int>, std::vector<int>>(values, plot_data);
    } else if (command == "plistseq") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        plot_data.add(DataSeries("ListSequence", Color::Red));
        plot_data.add(DataSeries("std::list", Color::Blue));
        plotInit<ListSequence<int>, std::list<int>>(values, plot_data);
    } else if (command == "parrseq") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        plot_data.add(DataSeries("ArraySequence", Color::Red));
        plot_data.add(DataSeries("std::vector", Color::Blue));
        plotInit<ArraySequence<int>, std::vector<int>>(values, plot_data);
    } else if (command == "phasht") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        plot_data.add(DataSeries("HashTable", Color::Red));
        plot_data.add(DataSeries("std::unordered_map", Color::Blue));
        plotInit<HashTable<int, int>, std::unordered_map<int, int>>(values, plot_data);
    } else if (command == "piset") {
        int values;
        if (!(ss >> values)) {
            std::cerr << "Error: Number of values is required.\n";
            return;
        }
        plot_data.add(DataSeries("ISet", Color::Red));
        plot_data.add(DataSeries("std::set", Color::Blue));
        plotInit<ISet<int>, std::set<int>>(values, plot_data);
    } else if (command == "func") {
        std::cout << "Available function tests:\n"
                  << "  Sequence        >fseq\n"
                  << "  ListSequence    >flistseq\n"
                  << "  ArraySequence   >farrseq\n"
                  << "  HashTable       >fhasht\n"
                  << "  ISet            >fiset\n"
                  << "  Package Manager >fpkgmn\n";
    } else if (command == "chrono") {
        std::cout << "Available chrono tests:\n"
                  << "  Sequence vs std::vector      >chseq\n"
                  << "  ListSequence std::list       >chlistseq\n"
                  << "  ArraySequence vs std::vector >charrseq\n"
                  << "  HashTable vs std::unordmap   >chhasht\n"
                  << "  ISet vs std::set             >chiset\n";
    } else if (command == "plots") {
        std::cout << "Available comparative plots:\n"
                  << "  Sequence vs std::vector      >pseq\n"
                  << "  ListSequence vs std::list    >plistseq\n"
                  << "  ArraySequence vs std::vector >parrseq\n"
                  << "  HashTable vs std::unordmap   >phasht\n"
                  << "  ISet vs std::set             >piset\n";
    } else if (command == "admin") {
        std::cout << "Available commands:\n"
                  << "  func\n"
                  << "  chrono\n"
                  << "  plots\n";
    } else if (command == "exit") {
        pm.saveToFile("../data/pgk.txt"); // Save to file on exit
        throw std::runtime_error("exit");
    } else if (command == "help") {
        std::cout << "Available commands:\n"
                  << "  install <package_name> <major> <minor> <patch> [dependencies...]\n"
                  << "  remove <package_name> <major> <minor> <patch>\n"
                  << "  list\n"
                  << "  show <package_name>\n"
                  << "  clear\n"
                  << "  help\n"
                  << "  admin\n"
                  << "  exit\n";
    } else {
        std::cerr << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

int main() {
    PackageManager pm;
    pm.loadFromFile("../data/pgk.txt"); // Load from file on startup
    std::cout << "Package Manager started. Type 'help' for commands.\n";
    while (true) {
        std::cout << "> ";
        try {
            processCommand(pm);
        } catch (const std::runtime_error &e) {
            if (std::string(e.what()) == "exit" || std::string(e.what()) == "EOF") {
                break;
            } else {
                std::cerr << "An unexpected error occurred: " << e.what() << "\n";
            }
        } catch (const std::exception &e) {
            std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        }
    }
    return 0;
}