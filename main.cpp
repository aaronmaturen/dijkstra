/****************************************************************************************/
/* Programmer Name: Aaron Maturen  The awesomest!                                                     */
/* Course Title: CS316  Section: 1                                                      */
/* Assignment No.: MP #5   Due Date: 12-05-09                                           */
/* Instructor: Dr. Tai-Chi Lee                                                          */
/*                                                                                      */
/* ==================================================================================== */
/* Program Definition                                                                   */
/*   Makes a multimap from flight data, and uses dijkstra's algorithm to find shortest  */
/*   path                                                                               */
/*                                                                                      */
/* ==================================================================================== */
/* Development History                                                                  */
/*                                                                                      */
/* 18.11.2009                                                                           */
/*    Started                                                                           */
/*    Created flightSystem.cpp / flightSystem.h                                         */
/*    Created fileManage.cpp / fileManage.h                                             */
/*                                                                                      */
/****************************************************************************************/


#include <iostream>
#include "flightSystem.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
ifstream infile;
ofstream outfile;

int main () {

    infile.open("f09mp5.dat1");
    outfile.open("out.data");
    flightMatrix theseFlights;
    int from;
    int to;
    char pref;

    char arrival_city[25];
    char departure_city[25];
    char flight_id1[4];
    char flight_id2[4];
    char departure_time1[4];
    char departure_time2[4];
    char arrival_time1[4];
    char arrival_time2[4];
    char cost[4];
    char capacity[4];

    while(infile){
        infile >> departure_city >> arrival_city >> flight_id1 >> departure_time1 >> arrival_time1 >> flight_id2 >> departure_time2 >> arrival_time2 >> cost >> capacity;
        theseFlights.addFlight(flight_id1,departure_city,arrival_city,atoi(departure_time1),atoi(arrival_time1),atoi(cost),atoi(capacity));
        theseFlights.addFlight(flight_id2,departure_city,arrival_city,atoi(departure_time2),atoi(arrival_time2),atoi(cost),atoi(capacity));
    }

    infile.close();
    infile.open("f09mp5.dat2");
    infile.clear();
    //debugging stuffs
    //theseFlights.printCities();
    cout << endl << endl;
    theseFlights.printFlights();
    cout << endl << endl << "*** Customer Inquiry Results *** " << endl << endl;

    while(infile){
        infile >> from >> to >> pref;
        theseFlights.dijkstra(theseFlights.lookupCity(from), theseFlights.lookupCity(to), pref);
    }

    infile.close();
    return 0;
}
