/****************************************************************************************/
/* Programmer Name: Aaron Maturen                                                       */
/* File: flightSystem.cpp                                                               */
/* Assignment No.: MP #5                                                                */
/* ==================================================================================== */
/* File Definition                                                                      */
/*     Handles the flightMatrix operations for flight management system                 */
/*                                                                                      */
/*                                                                                      */
/* ==================================================================================== */
/* Development History                                                                  */
/*                                                                                      */
/* 18.11.2009                                                                           */
/*      Started                                                                         */
/*      Created searchCity, addCity, printCities, searchFlights,                        */
/*          addFlights, printFlights                                                    */
/*                                                                                      */
/* 02.12.2009                                                                           */
/*      Created searchRoute                                                             */
/*                                                                                      */
/* 05.12.2011                                                                           */
/*      Fixed some booboo                                                               */
/****************************************************************************************/

#include "flightSystem.h"

int flightMatrix::addCity(string cityName){

    if (searchCity(cityName) == -1){

        city newCity;
        newCity.uid = cities.size();
        newCity.name = cityName;

        cities.push_back(newCity);

        return newCity.uid;

    } else {
        return -1;
    }

};

int flightMatrix::searchCity(string cityName){

    vector<city>::iterator it;

    for (it = cities.begin(); it < cities.end(); it++){
        if ( it->name == cityName ){
            return it->uid;
        }
    }

    return -1;
};

string flightMatrix::lookupCity(int city_id){

    vector<city>::iterator it;

    for (it = cities.begin(); it < cities.end(); it++){
        if ( it->uid == city_id ){
            return it->name;
        }
    }

    return "";
};

bool flightMatrix::printCities(void){

    vector<city>::iterator it;

    for (it = cities.begin(); it < cities.end(); it++){
            cout << it->uid << "    " << it->name << endl;
    }

    return 1;
};

//apparently I don't use this anyway... how, useful...
flight flightMatrix::searchFlight(string flight_id){

    flight emptyFlight = {"","","",0,0,0,0};

    for( it = flights.begin(); it!= flights.end(); it++){
        if((*it).second.flight_id == flight_id){
            return (*it).second;
        }
    }
    return emptyFlight;
};

//nor do I use this one...
vector<flight> flightMatrix::searchRoute(string departure_city, string destination_city){

    vector<flight> results;
    for( it = flights.begin(); it!= flights.end(); it++){
        if((*it).second.departure_city == departure_city && (*it).second.destination_city == destination_city){
            results.push_back((*it).second);
            cout << (*it).second.flight_id << endl;
        }
    }

    return results;
}

//nor this one...
void flightMatrix::printFlights(void){

    for( it = flights.begin(); it!= flights.end(); it++){
            cout << setw(4) << (*it).second.flight_id << "  " << setw(14) << (*it).second.departure_city << "  " << setw(14) << (*it).second.destination_city << "  " << setw(4) << (*it).second.departure_time << "  " << setw(4) << (*it).second.arrival_time << "  " << setw(4) << (*it).second.cost << "  " << setw(4) << (*it).second.capacity << endl;
    }

};

bool flightMatrix::addFlight(string flight_id, string departure_city, string destination_city, int departure_time, int arrival_time, int cost, int capacity){

    flight newFlight = {flight_id, departure_city, destination_city, arrival_time, departure_time, cost, capacity}; // prep a new flight for entry
    int departure_city_id = searchCity(departure_city); //check to see if the city already exists, if it doesnt returns -1
    int destination_city_id = searchCity(destination_city);

    if (departure_city_id == -1){ //if the city didnt exist

        departure_city_id = addCity(departure_city); //add it to the cities key

    }

    if (destination_city_id == -1){ //if the city didnt exist

        destination_city_id = addCity(destination_city); //add it to the cities key

    }

    flight query = searchFlight(flight_id);

    if(query.flight_id == ""){

        flights.insert(pair<int, flight>(departure_city_id, newFlight)); //insert flight into multimap

    }else{

        //cout << "Duplicate flight id " << flight_id << endl;

    }
    //cout << "Number of flights from " << departure_city << " " << flights.count(departure_city_id) << endl; //counts the number of flights leaving from each city

    return 1;
}

vector<flight> flightMatrix::cityInfo(int city_id){

    vector<flight> results;

    for( it = flights.begin(); it!= flights.end(); it++){

        if((*it).first == city_id ){

            results.push_back((*it).second);
            //cout << (*it).second.flight_id << endl;

        }

    }

    return results;

}

vector<flight> flightMatrix::dijkstra(string departure_city, string destination_city, char time_preference){

    int arrival_time;

    vector<vertex> vertices;
    vector<flight> outboundFlights;
    vector<flight> shortestFlight;

    vertex newVertex;

    //iterators
    vector<vertex>::iterator iter;
    vector<vertex>::iterator iter2;
    vector<flight>::iterator vFlightIt;

    newVertex.cost = 0;
    newVertex.id = searchCity(departure_city);
    vertices.push_back(newVertex);

    //insert -1 for distance for all paths except from root to root
    for(int i = 0; i!=cities.size();i++){

        newVertex.id = i;
        newVertex.cost = -1;

        if(i==searchCity(departure_city)){newVertex.cost = 0;}

        vertices.push_back(newVertex);

    }

    //go through all the vertices and find distance
    for (iter = vertices.begin(); iter != vertices.end(); iter++){

        outboundFlights = cityInfo((*iter).id);

        for( vFlightIt = outboundFlights.begin(); vFlightIt!= outboundFlights.end(); vFlightIt++){

            for(iter2 = vertices.begin(); iter2 != vertices.end(); iter2++){

                if((*iter2).id == searchCity((*vFlightIt).destination_city)){

                    if(!(*iter).path.empty()){
                        arrival_time = (*iter).path.back().arrival_time;
                    }else{
                        if (time_preference == 'A'){
                            arrival_time=0;
                        }else if(time_preference == 'P'){
                            arrival_time=1200;
                        } else {
                            arrival_time=0;
                        }
                    }
                    if((((*iter2).cost > ((*vFlightIt).cost + (*iter).cost) && (arrival_time <= (*vFlightIt).departure_time)) || ((*iter2).cost == -1)) && (arrival_time <= (*vFlightIt).departure_time)){

                     cout << endl << arrival_time << endl;
                        if((*iter2).cost == -1){(*iter2).cost=0;}

                        int routeCost = ((*iter).cost==-1)?0:(*iter).cost;
                        (*iter2).cost = (*vFlightIt).cost + routeCost;

                        (*iter2).path = (*iter).path;
                        (*iter2).path.push_back(*vFlightIt);
                    }
                }
            }
        }
    }

    //print out all the vertices after dijkstra!
    for(iter2 = vertices.begin(); iter2 < vertices.end(); iter2++){
        if(lookupCity((*iter2).id) == destination_city){

                cout << "Departure City :   " << departure_city << endl;
                cout << "Destination City:  " << destination_city << endl;
                cout << "Time Preference:   " << time_preference;
                if (time_preference == 'A'){
                    cout << " - Morning Flight" << endl;
                }else if(time_preference == 'P'){
                    cout << " - Evening Flight" << endl;
                }else {
                    cout << " - No Time Preference" << endl;
                }
                cout << "Lowest Fare:       " << (*iter2).cost << endl;
                cout << ">>> Flight information and Options <<<" << endl << endl;
                cout << "Departing From " << "Arriving At " << "Flight No. " << "Departure Time " << "Arrival Time " << "Air Fare " << "Capacity" << endl;
                cout << "============== " << "=========== " << "========== " << "============== " << "============ " << "======== " << "========" << endl;
                for( vFlightIt = (*iter2).path.begin(); vFlightIt!= (*iter2).path.end(); vFlightIt++){
                    cout << setw(14) << (*vFlightIt).departure_city << setw(12) << (*vFlightIt).destination_city << setw(11) << (*vFlightIt).flight_id << setw(15)<< (*vFlightIt).departure_time << setw(13) << (*vFlightIt).arrival_time << setw(9) << (*vFlightIt).cost << setw(9) << (*vFlightIt).capacity << endl;
                }
                cout << endl << endl;
        }
    }

    return shortestFlight;

}
