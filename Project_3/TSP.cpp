#include "TSP.hpp"

/**
 * Displays the edges and total distance of the tour.
 * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
 */
void TSP::Tour::display() const {
  for (size_t i = 1; i < path.size(); i++) {
    std::cout << "EDGE " << path[i-1].id << " -> " << path[i].id << " | WEIGHT : " << weights[i] << std::endl;
  }
  std::cout << "TOTAL DISTANCE: " << total_distance << std::endl;
}

/**
 * Reads a .tsp file and constructs a list of cities as nodes.
 * The file should have a section labeled "NODE_COORD_SECTION" followed by lines with the format: ID x-coordinate y-coordinate.
 * 
 * @param filename The path to the TSP file.
 * @return A list of `Node` objects representing cities and their coordinates.
 * @throws std::runtime_error If the file cannot be read or parsed.
 * 
 * @pre The file specified by `filename` exists and follows the TSP format.
 */
std::list<Node> TSP::constructCities(const std::string& filename) {
  // Read past metadata
  std::ifstream fin(filename);
  if (fin.fail()) {
    std::cerr << "ERROR: Could not read file: " << filename << std::endl;
    throw std::runtime_error("Failed to read file. Terminating.");
  }

  std::string line;
  do { std::getline(fin, line); }
  while (line.find("NODE_COORD_SECTION"));

  // Read data from file into Node list "cities"
  std::list<Node> cities;
  size_t ID;
  double x, y;
  while (!fin.eof()){
    if (!(fin >> ID >> x >> y)) break;
    cities.push_back(Node(ID, x, y));
  }
  return cities;
}

double distance(const Node& a, const Node& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

TSP::Tour TSP::nearestNeighbor(std::list<Node> cities, const size_t& start_id) {
    Tour tour;
    
    // Locating starting node
    auto it = std::find_if(cities.begin(), cities.end(), [start_id](const Node& node) {
        return node.id == start_id;
    });

    if (it == cities.end()) {
        throw std::runtime_error("Starting node not found.");
    }

    Node start = *it; // Saving starting node
    Node current = start;
    tour.path.push_back(current);
    tour.weights.push_back(0); // No distance for starting point
    cities.erase(it); // Remove from the list

    while (!cities.empty()) {
        auto nearest_it = std::min_element(
            cities.begin(), cities.end(),
            [&current](const Node& a, const Node& b) {
                return distance(current, a) < distance(current, b);
            });

        if (nearest_it == cities.end()) break; 

        double min_distance = distance(current, *nearest_it);
        current = *nearest_it;

        tour.path.push_back(current);
        tour.weights.push_back(static_cast<size_t>(std::round(min_distance)));
        tour.total_distance += static_cast<size_t>(std::round(min_distance));
        cities.erase(nearest_it);
    }

    // Return to the starting node to complete the circuit
    double return_distance = distance(tour.path.back(), start);
    tour.path.push_back(start); //cycle to start
    tour.weights.push_back(static_cast<size_t>(std::round(return_distance)));
    tour.total_distance += static_cast<size_t>(std::round(return_distance));

    return tour;
}

// int main() {
//     // Test case 1
//     {
//         std::list<Node> cities1 = {
//             Node(1, 0, 0),
//             Node(2, 0, 1),
//             Node(3, 1, 1),
//             Node(4, 1, 0)
//         };
//         TSP::Tour tour1 = TSP::nearestNeighbor(cities1, 1);
//         assert(tour1.path.front().id == 1);
//         assert(tour1.path.back().id == 1);
//         assert(tour1.total_distance == 4);
//     }

//     // Test case 2
//     {
//         std::list<Node> cities3 = {
//             Node(1, 0, 0)
//         };
//         TSP::Tour tour3 = TSP::nearestNeighbor(cities3, 1);
//         assert(tour3.path.front().id == 1);
//         assert(tour3.path.back().id == 1);
//         assert(tour3.total_distance == 0);
//     }

//     return 0;
// }