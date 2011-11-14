/*
 *  flightSystem.h
 *  prog5
 *
 *  Created by Aaron Maturen on 11/18/09.
 *
 */

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

struct city{
    int uid;
    string name;
};

struct flight{
    string flight_id;
    string departure_city;
    string destination_city;
    int arrival_time;
    int departure_time;
    int cost;
    int capacity; 
};

class vertex{
    public:    
        int cost;
        int id;
        vector<flight> route;
        vector<flight> path;
};

class flightMatrix{
    public:
        bool addFlight(string, string, string, int, int, int, int);
        int searchCity(string);
        int addCity(string);
        string lookupCity(int);
        bool addPath(void);
        flight searchFlight(string);
        vector<flight> dijkstra(string, string, char);
        vector<flight> cityInfo(int);
        vector<flight> searchRoute(string, string);
        bool pathExists(void);
        bool printCities(void);
        void printFlights(void);
        
        
    private:
        multimap<int,flight> flights;
        vector<city> cities;
        multimap<int, flight>::iterator it;
            
};