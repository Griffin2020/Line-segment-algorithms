#include <iostream>
#include <ctime>
#include <random>
#include <list>
#include <tuple>
#include <queue>
using namespace std;


struct lineStruct{
    double x1;
    double y1;
    double x2;
    double y2;

} ;

bool colinear(lineStruct lineOne, int x, int y){
    if(x <= max(lineOne.x1, lineOne.x2) && x <= min(lineOne.x1, lineOne.x2) && 
    y <= max(lineOne.y1, lineOne.y2) && y <= min(lineOne.y1, lineOne.y2)){
        return true;
    }
    return false;
}

int orientation(int x1, int x2, int x3, int y1, int y2, int y3){

    int value = (y2-y1)*(x3-x2) - (x2-x1)*(y3-y2);
    if(value == 0){
        return 0;
    } else if(value < 0){
        return 2;
    }
    return 1;
}
tuple <double, double> findIntersections(lineStruct lineOne, lineStruct lineTwo, double safe_number){
 

    double oneSlope = (lineOne.y1 - lineOne.y2) / (lineOne.x1 - lineOne.x2);
    double twoSlope = (lineTwo.y1 - lineTwo.y2) / (lineTwo.x1 - lineTwo.x2);
    if(oneSlope == twoSlope){
        return {safe_number, safe_number};
    }
    double x = ((lineOne.x1 * oneSlope) - (lineTwo.x1 * twoSlope) + (lineTwo.y1 - lineOne.y1)) / (oneSlope - twoSlope);
    if(!(lineOne.x1 < x && lineOne.x2 > x)){

        return {safe_number, safe_number};
    }
    if(!(lineTwo.x1 < x && lineTwo.x2 > x)){
        return {safe_number, safe_number};
    }
    //cout << oneSlope << endl;
    double y = oneSlope * ((x - lineOne.x1) + lineOne.y1) ;
    return {x, y};
}
int countIntersections(lineStruct linesList[], int numLines, double safe_number){
    int numIntersections = 0;
    list<tuple<double, double>> intersections;
    double a, b;
    
    


    cout << "Intersections found: " << endl;
    for(auto x : intersections){
        tuple <double,double> tp = x;
        cout << get<0>(tp) << ", " << get<1>(tp) << endl;
    }
    
    return numIntersections;

}
bool operator<(lineStruct lineOne, lineStruct lineTwo){
    return lineOne.x1 > lineTwo.x1;
}
int main() {
    int dimensions = 10; // Dimensions of the square
    int numLines = 100; // Number of lines
    lineStruct linesList[numLines];
    srand(1);
    list<lineStruct> usedLines;
    for(int i = 0; i < numLines; i++){

        linesList[i].x1 = rand()/ static_cast<float>(RAND_MAX);
        linesList[i].y1 = rand()/ static_cast<float>(RAND_MAX);
        linesList[i].x2 = rand()/ static_cast<float>(RAND_MAX);
        linesList[i].y2 = rand()/ static_cast<float>(RAND_MAX);
      
    } 
/*     linesList[0].x1 = 2;
    linesList[0].x2 = 5;
    linesList[0].y1 = 2;
    linesList[0].y2 = 6;
    
    linesList[1].x1 = 1;
    linesList[1].x2 = 5;
    linesList[1].y1 = 8;
    linesList[1].y2 = 1; */
    priority_queue<lineStruct> boQueue;
    // Swap points one and two if one comes before the other
    for(int i = 0; i < numLines; i++){
        if(linesList[i].x1 < linesList[i].x2){
            swap(linesList[i].x1, linesList[i].x2);
            swap(linesList[i].y1, linesList[i].y2);
        }
        boQueue.push(linesList[i]);
    }
    // Sort the values by x1 
    cout << boQueue.top().x1 << endl;


    int numIntersect = countIntersections(linesList, numLines, dimensions + 1);
    cout << numIntersect << " intersections were found" << endl;
    return 0;
}
