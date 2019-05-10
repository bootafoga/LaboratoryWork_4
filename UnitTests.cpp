#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "List.h"
#include "map.h"

using testing::Eq;
const int SIZE = 10;

int Dijkstra(int st, int fin, List<int> array[SIZE], Map<string,int> citiesMap, int countCities);
int findPath(int from, int to, List<int> array[SIZE]);
namespace {
    class ClassDeclaration: public testing::Test{
    public:
        ClassDeclaration(){
        }
    };
}

TEST_F(ClassDeclaration, dijkstra_check){
    List<int> array[3];
    Map<string,int> citiesMap;
    citiesMap.insert("Spb", 0);
    citiesMap.insert("Msk", 1);
    citiesMap.insert("Rnd", 2);

    array[0].push_back(1, 50);
    array[0].push_back(2, 10);
    array[2].push_back(1, 10);

    ASSERT_EQ(Dijkstra(0, 1, array, citiesMap, 3), 20);
}

TEST_F(ClassDeclaration, findPath_check){
    List<int> array[3];
    array[0].push_back(1, 50);
    array[0].push_back(2, 10);
    array[2].push_back(1, 10);

    ASSERT_EQ(findPath(0,2, array), 10);
}

TEST_F(ClassDeclaration, findPathWhichDoesntExist_check){
    List<int> array[3];
    array[0].push_back(1, 50);
    array[0].push_back(2, 10);
    array[2].push_back(1, 10);

    ASSERT_EQ(findPath(2,0, array), 0);
}

TEST_F(ClassDeclaration, dijkstraDoesntExist_check){
    List<int> array[3];
    Map<string,int> citiesMap;
    citiesMap.insert("Spb", 0);
    citiesMap.insert("Msk", 1);
    citiesMap.insert("Rnd", 2);

    array[0].push_back(1, 50);

    ASSERT_EQ(Dijkstra(0, 2, array, citiesMap, 3), INT_MAX);
}