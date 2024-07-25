#include <iostream> // For standard input/output
#include <vector> // For using the vector container
#include <cstdlib> // For standard library functions like rand() and srand()
#include <ctime> // For time() function to seed random number generator
#include <cmath> // For mathematical functions like sqrt()
#include <fstream> // For file operations
#include <iomanip> // For manipulating output formatting
#include <chrono> // For timing the code
#include <sstream> // For string stream operations
#include "body.h" // Include the body structure definition

class BarnesHutSimulation {
public:
    // Constructor to initialize the simulation with a given number of bodies
    BarnesHutSimulation(int numBodies) : numBodies(numBodies), theta(0.5), dt(0.01), steps(1000), root(nullptr) {
        srand(time(0)); // Seed the random number generator with current time
        // Initialize the bodies with random positions, velocities, and masses
        for (int i = 0; i < numBodies; ++i) {
            bodies.push_back({
                static_cast<double>(rand() % 100), // Random x position
                static_cast<double>(rand() % 100), // Random y position
                static_cast<double>(rand() % 10 - 5), // Random x velocity
                static_cast<double>(rand() % 10 - 5), // Random y velocity
                static_cast<double>(rand() % 10 + 1) // Random mass
            });
        }
    }

    // Function to run the simulation
    void runSimulation() {
        auto start = std::chrono::high_resolution_clock::now(); // Start timing the simulation

        std::string filename = "serial_output_" + getCurrentTime() + ".txt"; // Generate a filename with current time
        std::ofstream outfile(filename); // Open the output file

        auto setup_end = std::chrono::high_resolution_clock::now(); // End timing the setup

        // Output the initial positions and velocities of the bodies
        outfile << "Initial Positions and Velocities:\n";
        for (const auto& body : bodies) {
            outfile << "Body: Position(" << body.x << ", " << body.y << "), Velocity(" 
                    << body.vx << ", " << body.vy << ")\n";
        }

        // Main simulation loop
        for (int step = 0; step < steps; ++step) {
            root = nullptr; // Clear the quadtree

            // Insert bodies into the quadtree
            for (auto& body : bodies) {
                insertBody(body);
            }

            // Compute forces and update bodies
            for (auto& body : bodies) {
                computeForce(body);
                updateBody(body);
            }
        }

        auto end = std::chrono::high_resolution_clock::now(); // End timing the simulation
        std::chrono::duration<double> elapsed = end - start; // Calculate total elapsed time
        std::chrono::duration<double> setup_time = setup_end - start; // Calculate setup time

        // Output the final positions and velocities of the bodies
        outfile << "\nFinal Positions and Velocities:\n";
        for (const auto& body : bodies) {
            outfile << "Body: Position(" << body.x << ", " << body.y << "), Velocity(" 
                    << body.vx << ", " << body.vy << ")\n";
        }

        // Output the timing information
        outfile << "\nSimulation Time (excluding setup): " << (elapsed - setup_time).count() << " seconds\n";
        outfile << "Total Time (including setup): " << elapsed.count() << " seconds\n";
        outfile.close(); // Close the output file
    }

private:
    // Structure to represent a node in the quadtree
    struct Node {
        double x, y, mass; // Position and mass of the center of mass
        Body* body; // Pointer to the body, if this is a leaf node
        Node* NW; // Northwest child
        Node* NE; // Northeast child
        Node* SW; // Southwest child
        Node* SE; // Southeast child

        // Constructor to initialize a node
        Node(double x, double y, double mass) : x(x), y(y), mass(mass), body(nullptr), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}
    };

    int numBodies; // Number of bodies in the simulation
    double theta; // Threshold for Barnes-Hut approximation
    double dt; // Time step for the simulation
    int steps; // Number of simulation steps
    std::vector<Body> bodies; // Vector to store the bodies
    Node* root; // Pointer to the root of the quadtree

    // Function to insert a body into the quadtree
    void insertBody(Body& body) {
        if (root == nullptr) {
            root = new Node(body.x, body.y, body.mass); // Create a new root node
            root->body = &body; // Set the body pointer
        } else {
            insert(root, body); // Insert the body into the existing quadtree
        }
    }

    // Recursive function to insert a body into a node
    void insert(Node* node, Body& body) {
        if (node->body == nullptr) {
            node->body = &body; // Set the body pointer if this is a leaf node
        } else {
            // Subdivide the node if necessary
            if (node->NW == nullptr) {
                node->NW = new Node(node->x - 50, node->y + 50, 0);
                node->NE = new Node(node->x + 50, node->y + 50, 0);
                node->SW = new Node(node->x - 50, node->y - 50, 0);
                node->SE = new Node(node->x + 50, node->y - 50, 0);
            }

            // Insert the body into the appropriate quadrant
            if (body.x < node->x && body.y > node->y) {
                insert(node->NW, body);
            } else if (body.x > node->x && body.y > node->y) {
                insert(node->NE, body);
            } else if (body.x < node->x && body.y < node->y) {
                insert(node->SW, body);
            } else {
                insert(node->SE, body);
            }
        }
    }

    // Function to compute the force on a body
    void computeForce(Body& body) {
        if (root != nullptr) {
            computeForce(root, body); // Start the force computation from the root
        }
    }

    // Recursive function to compute the force on a body from a node
    void computeForce(Node* node, Body& body) {
        if (node == nullptr || node->body == &body) return; // Skip if the node is null or if it is the same body

        double dx = node->x - body.x; // Calculate the x distance
        double dy = node->y - body.y; // Calculate the y distance
        double dist = sqrt(dx * dx + dy * dy); // Calculate the distance

        if (dist > 0) {
            double F = (body.mass * node->mass) / (dist * dist); // Calculate the force
            body.vx += F * dx / dist; // Update the x velocity
            body.vy += F * dy / dist; // Update the y velocity
        }

        // Recursively compute the force from the child nodes
        if (node->NW != nullptr) {
            computeForce(node->NW, body);
            computeForce(node->NE, body);
            computeForce(node->SW, body);
            computeForce(node->SE, body);
        }
    }

    // Function to update the position of a body
    void updateBody(Body& body) {
        body.x += body.vx * dt; // Update the x position
        body.y += body.vy * dt; // Update the y position
    }

    // Function to get the current time as a string
    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now(); // Get the current time
        auto in_time_t = std::chrono::system_clock::to_time_t(now); // Convert to time_t
        std::stringstream ss; // Create a string stream
        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d%H%M%S"); // Format the time
        return ss.str(); // Return the formatted time as a string
    }
};

int main() {
    int numBodies; // Variable to store the number of bodies
    std::cout << "Enter the number of bodies: ";
    std::cin >> numBodies; // Get the number of bodies from the user

    BarnesHutSimulation simulation(numBodies); // Create a simulation with the specified number of bodies
    simulation.runSimulation(); // Run the simulation

    return 0; // Return 0 to indicate successful execution
}
