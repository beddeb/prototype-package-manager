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

template<typename T>
bool readValue(std::stringstream &ss, T &value, const std::string &error_message) {
    if (!(ss >> value)) {
        std::cerr << error_message << "\n";
        return false;
    }
    return true;
}

bool readAndValidatePackageData(std::stringstream &ss, std::string &packageName, int &major, int &minor, int &patch) {
    if (!(ss >> packageName >> major >> minor >> patch)) {
        std::cerr << "Error: Insufficient data. Package name and version are required.\n";
        return false;
    }

    if (major <= 0 || minor < 0 || patch < 0) {
        std::cerr << "Error: Invalid data format or version. Version must be positive.\n";
        return false;
    }
    return true;
}

void processCommand(PackageManager &pm) {
    Sequence<DataSeries> plot_data;
    int values;
    std::string command;
    std::getline(std::cin, command);
    std::stringstream ss(command);
    ss >> command;

    if (command == "install") {
        std::string packageName;
        int major, minor, patch;
        std::vector<std::string> dependencies;

        if (!readAndValidatePackageData(ss, packageName, major, minor, patch)) { return; }

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

        if (!readAndValidatePackageData(ss, packageName, major, minor, patch)) { return; }

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
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }
        chronoSequence(values, 100);
    } else if (command == "chlistseq") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }
        chronoListSequence(values, 100);
    } else if (command == "charrseq") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }
        chronoArraySequence(values, 100);
    } else if (command == "chhasht") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }
        chronoHashTable(values);
    } else if (command == "chiset") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }
        chronoISet(values);
    } else if (command == "pseq") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }

        plot_data.add(DataSeries("Sequence", Color::Red));
        plot_data.add(DataSeries("std::vector", Color::Blue));

        plotInit<Sequence<int>, std::vector<int>>(values, plot_data);
    } else if (command == "plistseq") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }

        plot_data.add(DataSeries("ListSequence", Color::Red));
        plot_data.add(DataSeries("std::list", Color::Blue));

        plotInit<ListSequence<int>, std::list<int>>(values, plot_data);
    } else if (command == "parrseq") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }

        plot_data.add(DataSeries("ArraySequence", Color::Red));
        plot_data.add(DataSeries("std::vector", Color::Blue));

        plotInit<ArraySequence<int>, std::vector<int>>(values, plot_data);
    } else if (command == "phasht") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }

        plot_data.add(DataSeries("HashTable", Color::Red));
        plot_data.add(DataSeries("std::unordered_map", Color::Blue));

        plotInit<HashTable<int, int>, std::unordered_map<int, int>>(values, plot_data);
    } else if (command == "piset") {
        if (!readValue(ss, values, "Error: Number of values is required.")) { return; }

        plot_data.add(DataSeries("ISet", Color::Red));
        plot_data.add(DataSeries("std::set", Color::Blue));

        plotInit<ISet<int>, std::set<int>>(values, plot_data);
    } else if (command == "func") {
        std::cout << "Available function tests:\n"
                  << "  fseq       ~ Sequence\n"
                  << "  flistseq   ~ ListSequence\n"
                  << "  farrseq    ~ ArraySequence\n"
                  << "  fhasht     ~ HashTable\n"
                  << "  fiset      ~ ISet\n"
                  << "  fpkgmn     ~ Package Manager\n";
    } else if (command == "chrono") {
        std::cout << "Available chrono tests:\n"
                  << "  chseq <value>       ~ Sequence vs std::vector\n"
                  << "  chlistseq <value>   ~ ListSequence std::list\n"
                  << "  charrseq <value>    ~ ArraySequence vs std::vector\n"
                  << "  chhasht <value>     ~ HashTable vs std::unordmap\n"
                  << "  chiset <value>      ~ ISet vs std::set\n";
    } else if (command == "plots") {
        std::cout << "Available comparative plots:\n"
                  << "  pseq <value>        ~ Sequence vs std::vector\n"
                  << "  plistseq <value>    ~ ListSequence vs std::list\n"
                  << "  parrseq <value>     ~ ArraySequence vs std::vector\n"
                  << "  phasht <value>      ~ HashTable vs std::unordmap\n"
                  << "  piset <value>       ~ ISet vs std::set\n";
    } else if (command == "admin") {
        std::cout << "Available commands:\n"
                  << "  func       ~ Functional tests\n"
                  << "  chrono     ~ Load chrono tests\n"
                  << "  plots      ~ Plotting load tests\n";
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