# Smart-Traffic-Evacuation-System-
1. Smart Traffic Evacuation System (Graph + Greedy) Problem: Jab koi Emergency (Ambulance ya Fire Brigade) aati hai, toh heavy traffic ki wajah se wo fans jati hai.  
# 🚦 Smart Traffic Simulation System

An AI-powered emergency routing and smart traffic management system designed for urban grid networks (Mumbai). This project features a **C++ backend** utilizing pathfinding algorithms (A* Search) paired with an **interactive HTML/JavaScript frontend** using Leaflet.js maps for real-time visualization of green corridors.

## 🚀 Live Interactive Demo
Experience the live simulation directly in your web browser:
👉 **[CLICK HERE TO VIEW THE LIVE TRAFFIC SIMULATION](https://YOUR-GITHUB-USERNAME.github.io/Smart-Traffic-Simulation-System/)** *(Note: Replace with your actual GitHub Pages link after enabling it)*

---

## 🛠️ Tech Stack & Architecture
* **Backend Engine:** C++ (Graph Data Structure, Priority Queues, A* Pathfinding Algorithm)
* **Frontend Dashboard:** HTML5, CSS3, JavaScript, Leaflet.js (Map Rendering), Leaflet Routing Machine
* **Core Concept:** Optimizing emergency vehicle (Ambulance) routes by calculating live distances and traffic weights between critical city nodes and major trauma centers.

---

## 💻 How to Run the Project Locally

### 1. Running the C++ Backend Simulator
1. Open your terminal/command prompt inside the project folder.
2. Compile the source file using a C++ compiler:
   ```bash
   g++ dsaproject.cpp -o traffic_simulator
