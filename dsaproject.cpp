#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include <algorithm>

// Windows specific header for Emoji/UTF-8 support
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Node Structure (HTML locations ke coordinates ke hisaab se)
struct Node {
    string name;
    double lat, lng; 
};

struct Edge {
    int to;
    int weight; // Traffic/Time in minutes
};

struct State {
    int nodeID;
    int g; // Actual cost
    int f; // Total cost (g + heuristic)
    bool operator>(const State& other) const { return f > other.f; }
};

class MumbaiTrafficControl {
private:
    unordered_map<int, vector<Edge>> network;
    unordered_map<int, Node> cityNodes;
    
    // Heuristic function: Distance formula (A* Algorithm)
    int calculateHeuristic(int u, int v) {
        return sqrt(pow(cityNodes[u].lat - cityNodes[v].lat, 2) + pow(cityNodes[u].lng - cityNodes[v].lng, 2)) * 100;
    }

public:
    void addLocation(int id, string name, double lat, double lng) {
        cityNodes[id] = {name, lat, lng};
    }

    void addRoad(int u, int v, int trafficWeight) {
        network[u].push_back({v, trafficWeight});
        network[v].push_back({u, trafficWeight});
    }

    void findEmergencyPath(int start, int end) {
        priority_queue<State, vector<State>, greater<State>> pq;
        unordered_map<int, int> minCost;
        unordered_map<int, int> parent;
        
        for (auto const& n : cityNodes) minCost[n.first] = 1e9;

        minCost[start] = 0;
        pq.push({start, 0, calculateHeuristic(start, end)});

        cout << "\n[🛰️  GPS] Analyzing Mumbai Grid..." << endl;
        cout << "[📡  SCAN] Detecting best path to " << cityNodes[end].name << "..." << endl;

        while (!pq.empty()) {
            int u = pq.top().nodeID;
            pq.pop();

            if (u == end) break;

            for (auto& edge : network[u]) {
                if (minCost[u] + edge.weight < minCost[edge.to]) {
                    minCost[edge.to] = minCost[u] + edge.weight;
                    parent[edge.to] = u;
                    pq.push({edge.to, minCost[edge.to], minCost[edge.to] + calculateHeuristic(edge.to, end)});
                }
            }
        }
        displayPath(parent, start, end, minCost[end]);
    }

    void displayPath(unordered_map<int, int>& parent, int start, int end, int totalTime) {
        if (parent.find(end) == parent.end() && start != end) {
            cout << "❌ Path blocked by severe traffic or road closure!" << endl;
            return;
        }

        vector<int> path;
        int curr = end;
        while (curr != start) {
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        cout << "\n" << string(60, '=') << endl;
        cout << " 🚑  MUMBAI GREEN CORRIDOR: " << cityNodes[start].name << " -> " << cityNodes[end].name << endl;
        cout << string(60, '=') << endl;

        for (size_t i = 0; i < path.size(); ++i) {
            cout << "📍 " << cityNodes[path[i]].name;
            if (i < path.size() - 1) {
                cout << "\n  ║  [🚦 SIGNAL: GREEN]" << endl;
            }
        }

        cout << "\n\n🏁 Destination: " << cityNodes[end].name << " Reached!" << endl;
        cout << "⏱️  Estimated Time: " << totalTime << " minutes" << endl;
        cout << string(60, '=') << endl;
    }
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    MumbaiTrafficControl mumbai;

    // --- HTML WALI LOCATIONS (Exact Same) ---
    // Hospitals
    mumbai.addLocation(101, "Lilavati Hospital, Bandra", 19.0514, 72.8295);
    mumbai.addLocation(102, "Nanavati Max, Vile Parle", 19.1015, 72.8425);
    mumbai.addLocation(103, "JJ Hospital, Byculla", 18.9630, 72.8330);

    // Accident Sites
    mumbai.addLocation(0, "Marine Drive", 18.9430, 72.8230);
    mumbai.addLocation(1, "Dadar TT Circle", 19.0178, 72.8478);
    mumbai.addLocation(2, "BKC Junction", 19.0633, 72.8633);
    mumbai.addLocation(3, "Juhu Circle", 19.1075, 72.8263);
    mumbai.addLocation(4, "Powai Hiranandani", 19.1170, 72.9110);

    // --- CONNECTING ROADS (Based on Mumbai Geography) ---
    mumbai.addRoad(0, 1, 15);  // Marine Drive to Dadar
    mumbai.addRoad(1, 103, 10); // Dadar to JJ Hospital
    mumbai.addRoad(1, 101, 12); // Dadar to Lilavati
    mumbai.addRoad(2, 101, 5);  // BKC to Lilavati (Fastest)
    mumbai.addRoad(3, 102, 4);  // Juhu to Nanavati
    mumbai.addRoad(4, 102, 20); // Powai to Nanavati
    mumbai.addRoad(2, 4, 15);   // BKC to Powai

    cout << " 🚦 WELCOME TO SMART CITY TRAFFIC DASHBOARD 🚦" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Locations Loaded: Marine Drive(0), Dadar(1), BKC(2), Juhu(3), Powai(4)" << endl;
    
    int startIdx, hospIdx;
    cout << "\n👉 Select Accident Location ID (0-4): ";
    cin >> startIdx;
    cout << "👉 Select Hospital ID (101-103): ";
    cin >> hospIdx;

    if (startIdx >= 0 && startIdx <= 4 && hospIdx >= 101 && hospIdx <= 103) {
        mumbai.findEmergencyPath(startIdx, hospIdx);
    } else {
        cout << "❌ Invalid IDs entered." << endl;
    }

    return 0;
}
