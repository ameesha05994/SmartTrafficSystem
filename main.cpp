// SMART CITY TRAFFIC NAVIGATION SYSTEM
// HARD LEVEL C++ PROJECT
// Concepts Used:
// - Graphs
// - Dijkstra Algorithm
// - File Handling
// - OOP
// - Priority Queue
// - STL

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

class Road
{
public:
    int destination;
    int distance;
    int traffic;
    int accidentRisk;
    int toll;

    Road(int d, int dist, int t, int a, int tl)
    {
        destination = d;
        distance = dist;
        traffic = t;
        accidentRisk = a;
        toll = tl;
    }
};

class City
{
public:
    int id;
    string name;

    City(int i = 0, string n = "")
    {
        id = i;
        name = n;
    }
};

class TrafficSystem
{
private:
    vector<City> cities;
    vector<vector<Road>> graph;

public:

    // ADD CITY
    void addCity(int id, string name)
    {
        cities.push_back(City(id, name));

        if(graph.size() <= id)
        {
            graph.resize(id + 1);
        }
    }

    // ADD ROAD
    void addRoad(int source, int destination,
                 int distance, int traffic,
                 int accidentRisk, int toll)
    {
        graph[source].push_back(
            Road(destination, distance,
                 traffic, accidentRisk, toll));

        graph[destination].push_back(
            Road(source, distance,
                 traffic, accidentRisk, toll));
    }

    // DISPLAY CITIES
    void displayCities()
    {
        cout << "\n------ CITIES ------\n";

        for(auto city : cities)
        {
            cout << city.id << " -> " << city.name << endl;
        }
    }

    // DISPLAY GRAPH
    void displayMap()
    {
        cout << "\n------ ROAD MAP ------\n";

        for(int i = 0; i < graph.size(); i++)
        {
            cout << "\nCity " << i << ":\n";

            for(auto road : graph[i])
            {
                cout << " -> "
                     << road.destination
                     << " Distance: " << road.distance
                     << " Traffic: " << road.traffic
                     << " AccidentRisk: " << road.accidentRisk
                     << " Toll: " << road.toll
                     << endl;
            }
        }
    }

    // DIJKSTRA SHORTEST PATH
    void shortestPath(int source, int destination)
    {
        int n = graph.size();

        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        dist[source] = 0;

        pq.push({0, source});

        while(!pq.empty())
        {
            int current = pq.top().second;
            pq.pop();

            for(auto road : graph[current])
            {
                int next = road.destination;

                int cost =
                    road.distance +
                    road.traffic * 5 +
                    road.accidentRisk * 20 +
                    road.toll;

                if(dist[current] + cost < dist[next])
                {
                    dist[next] = dist[current] + cost;

                    parent[next] = current;

                    pq.push({dist[next], next});
                }
            }
        }

        // PRINT PATH
        if(dist[destination] == INT_MAX)
        {
            cout << "\nNo Route Found!\n";
            return;
        }

        vector<int> path;

        int temp = destination;

        while(temp != -1)
        {
            path.push_back(temp);
            temp = parent[temp];
        }

        cout << "\n------ BEST ROUTE ------\n";

        for(int i = path.size()-1; i >= 0; i--)
        {
            cout << path[i];

            if(i != 0)
            {
                cout << " -> ";
            }
        }

        cout << "\nTotal Cost: " << dist[destination] << endl;
    }

    // SAVE TO FILE
    void saveData()
    {
        ofstream cityFile("cities.txt");

        for(auto city : cities)
        {
            cityFile << city.id << " "
                     << city.name << endl;
        }

        cityFile.close();

        ofstream roadFile("roads.txt");

        for(int i = 0; i < graph.size(); i++)
        {
            for(auto road : graph[i])
            {
                roadFile
                    << i << " "
                    << road.destination << " "
                    << road.distance << " "
                    << road.traffic << " "
                    << road.accidentRisk << " "
                    << road.toll << endl;
            }
        }

        roadFile.close();

        cout << "\nData Saved Successfully!\n";
    }

    // LOAD FROM FILE
    void loadData()
    {
        ifstream cityFile("cities.txt");

        string line;

        while(getline(cityFile, line))
        {
            stringstream ss(line);

            int id;
            string name;

            ss >> id >> name;

            addCity(id, name);
        }

        cityFile.close();

        ifstream roadFile("roads.txt");

        while(getline(roadFile, line))
        {
            stringstream ss(line);

            int s, d, dist, t, a, tl;

            ss >> s >> d >> dist >> t >> a >> tl;

            addRoad(s, d, dist, t, a, tl);
        }

        roadFile.close();

        cout << "\nData Loaded Successfully!\n";
    }
};

int main()
{
    TrafficSystem system;

    int choice;

    while(true)
    {
        cout << "\n====== SMART CITY TRAFFIC SYSTEM ======\n";

        cout << "1. Add City\n";
        cout << "2. Add Road\n";
        cout << "3. Display Cities\n";
        cout << "4. Display Map\n";
        cout << "5. Find Best Route\n";
        cout << "6. Save Data\n";
        cout << "7. Load Data\n";
        cout << "8. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        if(choice == 1)
        {
            int id;
            string name;

            cout << "Enter City ID: ";
            cin >> id;

            cout << "Enter City Name: ";
            cin >> name;

            system.addCity(id, name);
        }

        else if(choice == 2)
        {
            int s, d, dist, t, a, tl;

            cout << "Source City ID: ";
            cin >> s;

            cout << "Destination City ID: ";
            cin >> d;

            cout << "Distance: ";
            cin >> dist;

            cout << "Traffic Level: ";
            cin >> t;

            cout << "Accident Risk: ";
            cin >> a;

            cout << "Toll Cost: ";
            cin >> tl;

            system.addRoad(s, d, dist, t, a, tl);
        }

        else if(choice == 3)
        {
            system.displayCities();
        }

        else if(choice == 4)
        {
            system.displayMap();
        }

        else if(choice == 5)
        {
            int source, destination;

            cout << "Enter Source City ID: ";
            cin >> source;

            cout << "Enter Destination City ID: ";
            cin >> destination;

            system.shortestPath(source, destination);
        }

        else if(choice == 6)
        {
            system.saveData();
        }

        else if(choice == 7)
        {
            system.loadData();
        }

        else if(choice == 8)
        {
            cout << "\nExiting Program...\n";
            break;
        }

        else
        {
            cout << "\nInvalid Choice!\n";
        }
    }

    return 0;
}