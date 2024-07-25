#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>      // Include chrono header
#include <sstream>     // Include sstream header
#include "body.h"

class BarnesHutSimulation {
public:
    BarnesHutSimulation(int numBodies) : numBodies(numBodies), theta(0.5), dt(0.01), steps(1000), root(nullptr) {
        srand(time(0));
        for (int i = 0; i < numBodies; ++i) {
            bodies.push_back({
                static_cast<double>(rand() % 100),
                static_cast<double>(rand() % 100),
                static_cast<double>(rand() % 10 - 5),
                static_cast<double>(rand() % 10 - 5),
                static_cast<double>(rand() % 10 + 1)
            });
        }
    }

    void runSimulation() {
        auto start = std::chrono::high_resolution_clock::now();

        std::string filename = "serial_output_" + getCurrentTime() + ".txt";
        std::ofstream outfile(filename);

        auto setup_end = std::chrono::high_resolution_clock::now();

        outfile << "Initial Positions and Velocities:\n";
        for (const auto& body : bodies) {
            outfile << "Body: Position(" << body.x << ", " << body.y << "), Velocity(" 
                    << body.vx << ", " << body.vy << ")\n";
        }

        for (int step = 0; step < steps; ++step) {
            root = nullptr;

            for (auto& body : bodies) {
                insertBody(body);
            }

            for (auto& body : bodies) {
                computeForce(body);
                updateBody(body);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::chrono::duration<double> setup_time = setup_end - start;

        outfile << "\nFinal Positions and Velocities:\n";
        for (const auto& body : bodies) {
            outfile << "Body: Position(" << body.x << ", " << body.y << "), Velocity(" 
                    << body.vx << ", " << body.vy << ")\n";
        }

        outfile << "\nSimulation Time (excluding setup): " << (elapsed - setup_time).count() << " seconds\n";
        outfile << "Total Time (including setup): " << elapsed.count() << " seconds\n";
        outfile.close();
    }

private:
    struct Node {
        double x, y, mass;
        Body* body;
        Node* NW;
        Node* NE;
        Node* SW;
        Node* SE;

        Node(double x, double y, double mass) : x(x), y(y), mass(mass), body(nullptr), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}
    };

    int numBodies;
    double theta;
    double dt;
    int steps;
    std::vector<Body> bodies;
    Node* root;

    void insertBody(Body& body) {
        if (root == nullptr) {
            root = new Node(body.x, body.y, body.mass);
            root->body = &body;
        } else {
            insert(root, body);
        }
    }

    void insert(Node* node, Body& body) {
        if (node->body == nullptr) {
            node->body = &body;
        } else {
            if (node->NW == nullptr) {
                node->NW = new Node(node->x - 50, node->y + 50, 0);
                node->NE = new Node(node->x + 50, node->y + 50, 0);
                node->SW = new Node(node->x - 50, node->y - 50, 0);
                node->SE = new Node(node->x + 50, node->y - 50, 0);
            }

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

    void computeForce(Body& body) {
        if (root != nullptr) {
            computeForce(root, body);
        }
    }

    void computeForce(Node* node, Body& body) {
        if (node == nullptr || node->body == &body) return;

        double dx = node->x - body.x;
        double dy = node->y - body.y;
        double dist = sqrt(dx * dx + dy * dy);

        if (dist > 0) {
            double F = (body.mass * node->mass) / (dist * dist);
            body.vx += F * dx / dist;
            body.vy += F * dy / dist;
        }

        if (node->NW != nullptr) {
            computeForce(node->NW, body);
            computeForce(node->NE, body);
            computeForce(node->SW, body);
            computeForce(node->SE, body);
        }
    }

    void updateBody(Body& body) {
        body.x += body.vx * dt;
        body.y += body.vy * dt;
    }

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d%H%M%S");
        return ss.str();
    }
};

int main() {
    int numBodies;
    std::cout << "Enter the number of bodies: ";
    std::cin >> numBodies;

    BarnesHutSimulation simulation(numBodies);
    simulation.runSimulation();

    return 0;
}

