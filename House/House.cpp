#include "House.hpp"
#include<iostream>
#include <fstream>
#include <stdexcept>


House::House(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::string line;
    int y = 0;
    while (getline(file, line)) {
        // Possibly ignore lines that start with certain characters if configurations are mixed in the same file
        if (line.front() == '#') continue;
        if (line.front() == 'M') break;
        std::vector<char> row(line.begin(), line.end());
        for (size_t x = 0; x < line.length(); ++x) {
            if (line[x] == 'D') {
                dockingStation = std::make_pair(x, y);
            }
        }
        grid.push_back(row);
        ++y;
    }
    file.close();
}


void House::checkBounds(int x, int y) const {
    if (x < 0 || y < 0 || x > grid.size() || y > grid[x].size()) {
        throw HouseOutOfBoundsException("Position out of bounds, illegal to access coordinates");
    }
}

int House::getDirtLevel(int x, int y) const {
    checkBounds(x,y);
    char cell = grid[y][x]; // verigy that it is y x and not x y
    if (cell >= '1' && cell <= '9') {
        return cell - '0';
    }
    return 0;
}

bool House::isWall(int x, int y) const {
    checkBounds(x, y);
    //std::cout << grid[y][x] << std::endl;
    return grid[y][x] == 'W';
}

void House::decrementDirt(int x, int y) {
    checkBounds(x, y);
    if (grid[y][x] > '0' && grid[y][x] <= '9') {
        grid[y][x]--;
    }
}

std::pair<int, int> House::getDockingStation()  {
    std::pair<int, int> copyDockingStation;
    copyDockingStation = std::pair<int, int>(dockingStation.first,dockingStation.second);
    return copyDockingStation;
}

void House::printCoordinate(int x, int y) const {
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size()) {
        std::cout << "Coordinate (" << x << ", " << y << ") is out of bounds." << std::endl;
        return;
    }
    char cell = grid[x][y];
    std::cout << "Coordinate (" << x << ", " << y << ") contains: '" << cell << "'" << std::endl;
    if (cell == 'D') {
        std::cout << "This is the docking station." << std::endl;
    } else if (cell == 'W') {
        std::cout << "This is a wall." << std::endl;
    } else if (cell >= '1' && cell <= '9') {
        std::cout << "Dirt level is " << (cell - '0') << "." << std::endl;
    } else if (cell == ' ') {
        std::cout << "This space is clean." << std::endl;
    }
}

void House::printAllCoordinates() const {
    std::cout << "Printing all coordinates of the house grid:" << std::endl;
    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            char cell = grid[y][x];
            std::cout << "Coordinate (" << x << ", " << y << "): ";
            if (cell == 'D') {
                std::cout << "Docking Station";
            } else if (cell == 'W') {
                std::cout << "Wall";
            } else if (cell >= '1' && cell <= '9') {
                std::cout << "Dirt level " << (cell - '0');
            } else if (cell == '0') {
                std::cout << "Clean space";
            }
            std::cout << std::endl;
        }
    }
}

void House::print(bool printDimensions) const {
    for (const auto &row: grid) {
        for (char cell: row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    if (printDimensions) {
        std::cout << "Length: " << grid.size() << " rows" << std::endl;
        std::cout << "Width: " << (grid.empty() ? 0 : grid[0].size()) << " columns" << std::endl;
    }
    std::cout << "\n" << std::endl;
}

bool House::isHouseClean() const {
    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            char cell = grid[y][x];
            // Check only the cells that are supposed to hold dirt
            if (cell != 'W' && cell != 'D') {
                if (cell != '0') {
                    return false;  // Found a cell that is not clean
                }
            }
        }
    }
    return true;  // All cleanable cells are clean
}

int House::calculateTotalDirt() const {
    int totalDirt = 0;
    for (const auto &row: grid) {
        for (char cell: row) {
            if (std::isdigit(cell) && cell != '0') { // Check if the cell contains dirt
                totalDirt += cell - '0'; // Convert character to integer and add to total
            }
        }
    }
    return totalDirt;
}