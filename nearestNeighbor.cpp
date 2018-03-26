/***********************************************************
 * Author: Patrick Mullaney
 * Date: 6/1/2017
 * CS325, Spring 2017
 * Description: Implementation file for nearest Neighbor 
 * algorithm for TSP (modeled after wikipedia description).
 ***********************************************************/

#include "nearestNeighbor.hpp"

using std::cout;
using std::endl;

/* Psuedocode description based on wikipedia:
 Start at a random city, find the nearest city (shortest edge between current
 and any unvisited city).  Set current city to closest neighbor, mark visited, repeat
 until all cities are visited.  Sequence of visited cities represents the path.
 */
struct tour nearestNeighbor(vector<struct city> cities){
    
    vector<struct city> path;
    
      /* Start at random city */
    int index = rand()%cities.size();
    struct city current = cities[index];
    current.visited = true;
    cities[index].visited = true;
    path.push_back(current);
    
    int distance = 0;
   
    while(path.size() < cities.size())
    {
        /* Initialize distance to arbitrarily large number.*/
        int nearest = 9999999;
        struct city next;
        
        for(int i = 0; i < cities.size(); i++)
        {
            /* If city is unvsited, calculate disance */
            if((cities[i].visited == false) && (current.cityNum != cities[i].cityNum))
            {
                /* Calculate distance. */
                int d = nearestInt(current, cities[i]);
                /* If distance to next is the nearest city, update next */
                if(d < nearest)
                {
                    nearest = d;
                    next = cities[i];
                }
            }
        }
        /* After iterating through unvisited cities, assign current city to next and push to path.*/
        current = cities[next.cityNum];
        cities[next.cityNum].visited = true;
        distance += nearest;
        path.push_back(current);
    }
    
    /* After path run, add distance from last city back to first. */
    distance += nearestInt(current, cities[index]);
    
    struct tour t;
    t.distance = distance;
    t.path = path;
    return t;
};

/* Psuedocode description based on wikipedia:
  Start at a random city, find the nearest city (shortest edge between current
 and any unvisited city).  Set current city to closest neighbor, mark visited, repeat
 until all cities are visited.  Sequence of visited cities represents the path.
*/
int nearestInt(struct city a, struct city b){
    
    int near;
    
    /* Amended distance calculation */
    double n = 0.0;
    double x1 = a.x;
    double x2 = b.x;
    double y1 = a.y;
    double y2 = b.y;
    
    // Calculate distance.
    n = sqrt(pow((x1 - x2),2.0) + pow((y1 - y2),2.0));
    
    // Round up if rem >= .5 else round down.
    int temp = floor(n);
    double rem = n - temp;
    
    if(rem >= 0.5)
    {
        near = ceil(n);
    }
    else
        near = floor(n);
    
    return near;
}
/* Create DP table of all distances */
int** bruteInit(vector <struct city> cities)
{
    int size = cities.size();
    
    int **table = new int*[size];
    for(int i = 0; i < size; i++)
    {
        table[i] = new int[size];
    }
    /* Initialize to arbitrarily large # */
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            table[i][j] = 999999;
        }
    }
    // Calculate distance to from all cities.
    struct city curr;
    for(int i = 0; i < size; i++)
    {
        curr = cities[i];
        for(int j = 0; j < size; j++)
        {
            table[curr.cityNum][cities[j].cityNum] = bruteDist(curr, cities[j], table);
        }
    }
    
    return table;
}
/* Calculate distances and update accordingly */
int bruteDist(struct city a, struct city b, int** table){
    
    int current, next;
    current = a.cityNum;
    next = b.cityNum;
    int near;
    
    if(table[current][next] == 999999)
    {
        double n = 0.0;
        double x1 = a.x;
        double x2 = b.x;
        double y1 = a.y;
        double y2 = b.y;
        
        // Calculate distance.
        n = sqrt(pow((x1 - x2),2.0) + pow((y1 - y2),2.0));
        
        // Round up if rem >= .5 else round down.
        int temp = floor(n);
        double rem = n - temp;
        
        if(rem >= 0.5)
        {
            near = ceil(n);
        }
        else
            near = floor(n);
        
        table[current][next] = near;
    }
    else
        near = table[current][next];
    
    return near;
}

struct tour brute(vector<struct city> cities)
{
    struct tour t;
    vector<struct tour> cityTours;
    vector<vector<struct tour>> allTours;
    
    /* Initialize DP table */
    int** table = bruteInit(cities);
    
    for(int i = 0; i < cities.size(); i++)
    {
        cityTours = bruteHelper(cities, i, table);
        allTours.push_back(cityTours);
    }
    
    
    
    /* Take the shortest path as optimal path */
    int shortest = 99999999;
    struct tour cityStart;
    
    for(int i = 0; i < allTours.size(); i++)
    {
        cityStart = cityTours[i];
        for(int j = 0; j < cityTours.size(); j++)
        {
            if(cityTours[i].distance < shortest)
            {
                shortest = cityTours[i].distance;
                t = cityTours[i];
            }
        }
    }
    return t;
}

vector<struct tour> bruteHelper(vector<struct city> cities, int index, int** table)
{
    struct tour t;
    vector<struct city> path;
    vector<struct tour> tours;
    
    /* Start at input city */
    struct city current = cities[index];
    cities[index].visited = true;
    path.push_back(current);
    
    int distance = 0;
    /* Push start city for all tours */
    for(int i = 0; i < cities.size()-1; i++)
    {
        tours[i].path.push_back(current);
    }
    /* Push remaining cities */
    for(int i = 0; i < cities.size()-1; i++)
    {
        for(int j = 0; j < cities.size(); j++)
        {
            if(tours[i].path[j].visited == false)
            {
                tours[i].path[j].visited == true;
                tours[i].distance += bruteDist(current, tours[i].path[j], table);
                tours[i].path.push_back(tours[i].path[j]);
            }
        }
    }
    
    // Calculate distance to each city
    for(int i = 0; i < cities.size(); i++)
    {
        distance = bruteDist(cities[index], cities[i], table);
    }
    distance = 0;
    // Calculate path.
    while(path.size() < cities.size())
    {
        /* Initialize distance to arbitrarily large number.*/
        struct city next;
        int d = 0;
        
        for(int i = 0; i < cities.size(); i++)
        {
            /* If city is unvsited, calculate disance */
            if((cities[i].visited == false) && (current.cityNum != cities[i].cityNum))
            {
                /* Calculate distance. */
                d = bruteDist(cities[index], cities[i], table);
                current = cities[i];
                path.push_back(current);
                cities[current.cityNum].visited = true;
                distance+= d;
            }
        }
    }
    /* After path run, add distance from last city back to first. */
    distance += bruteDist(current, cities[index],table);
    t.distance = distance;
    t.path = path;
    tours.push_back(t);
    resetBrute(cities);
   
    
    int shortest = 9999999;
    for(int i = 0; i < tours.size(); i++)
    {
        if(tours[i].distance < shortest)
        {
            t = tours[i];
            shortest = tours[i].distance;
        }
    }
    return tours;
}
void resetBrute(vector<struct city> cities)
{
    for(int i = 0; i < cities.size(); i++)
    {
        cities[i].visited = false;
    }
}
