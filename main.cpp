#include "List.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <fstream>

using namespace std;
const int SIZE = 100;

int findPath(int from, int to, List<int> array[SIZE]){
    Node<int> *itemSearch = array[from].head;
    while (itemSearch != nullptr){
        if (itemSearch->field == to) return itemSearch->weight;
        itemSearch = itemSearch->nextNode;
    }
    return 0;
}

int Dijkstra(int st, int fin, List<int> array[SIZE], string cities[SIZE], int countCities)
{
    int distance[countCities];
    bool visited[countCities];
    string road[countCities];
    int current, index;

    for (int i = 0; i < countCities; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        road[i] = "";
    }
    distance[st] = 0;
    road[st] += cities[st];

    for (int i = 0; i < countCities-1; i++)
    {
        int min = INT_MAX;
        for (int j = 0; j < countCities; j++)
            if (!visited[j] && distance[j] <= min)
            {
                min = distance[j];
                index = j;
            }
        current = index;
        visited[current] = true;

        for (int j = 0; j < countCities; j++){
            int rez = findPath(current, j, array);

            if (!visited[j] && rez && distance[current] != INT_MAX &&
                distance[current] + rez < distance[j]){
               // cout << "from "<< u << " to" << i << " as " <<  distance[u]<< " plus " << rez << endl;
                distance[j] = distance[current] + rez;
                road[j] = road[current] + "->" + cities[j];
            }
        }
    }

    cout<<"The path from start to finish:\t\n";
    cout << cities[st] << " > " << cities[fin] << " = " << distance[fin] << endl;
    cout << "Road: " << road[fin];
    return distance[fin];
}


int main(int argc, char* argv[]){

    List<int> array[SIZE]; // array of lists of adjacent vertices
    string cities[SIZE]; // array of city names
    int countCities = 0; // current number of cities
    string parse[SIZE][4]; // array for input from the file
    int countStr = 0; // the number of lines in the file

    string line;
    ifstream in("input.txt");

    if(in.is_open()){
        while (getline(in, line)) {

            // counted one line, divided into different cells.
            int field = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ';') {
                    field++;
                } else {
                    parse[countStr][field] += line[i];
                }
            }

            // if there is no such city in the array, add it
            bool flag = false;
            for (int i = 0; i < countCities; i++){
                if (parse[countStr][0] == cities[i]) flag = true;
            }
            if (!flag) {
                cities[countCities] = parse[countStr][0];
                countCities++;
            }
            countStr++;
        }

        int start;
        int finish;
        for (int i = 0; i < countStr; i++){
            // if there is no such city in the array, add it
            bool flag = false;

            for (int j = 0; j < countCities; j++){
                if (parse[i][0] == cities[j]) start = j;
                if (parse[i][1] == cities[j]) { finish = j; flag = true;}
            }

            if (!flag) {
                cities[countCities] = parse[i][1];
                finish = countCities;
                countCities++;
            }

            if(parse[i][2] != "N/A") array[start].push_back(finish, atoi(parse[i][2].c_str()));
            if(parse[i][3] != "N/A") array[finish].push_back(start, atoi(parse[i][3].c_str()));
        }
    }

    int start = 0;
    int finish = 0;
    string userFrom = "Saint-Petersburg";
    string userTo = "Moscow";
   // cout<<"Start point >> "; cin>>user;

    for (int i = 0; i < countCities; i++){
        if (userFrom == cities[i]) start = i;
        if (userTo == cities[i]) finish = i;
    }

    Dijkstra(start, finish, array, cities, countCities);

    testing::InitGoogleTest(&argc, argv);
    int b = RUN_ALL_TESTS();
    return 0;
}
