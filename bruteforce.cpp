#include <iostream>
#include <ctime>
#include <random>
#include <list>
#include <tuple>
using namespace std;


struct lineStruct{
    int x1;
    int y1;
    int x2;
    int y2;

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
 
    double x = ((lineOne.x1 * oneSlope) - (lineTwo.x1 * twoSlope) + (lineTwo.y2 - lineOne.y1)) / (oneSlope - twoSlope);
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
    for(int i = 0; i < numLines - 1; i++){
        for(int j = i + 1; j < numLines; j++){
            tie(a, b) = findIntersections(linesList[i], linesList[j], safe_number);
            cout << a << " " << b << endl;
            if(a != safe_number && b != safe_number){
                intersections.push_back({a, b});
                numIntersections++;
            }
            
        }
    }
    for(auto x : intersections){
        tuple <double,double> tp = x;
        cout << get<0>(tp) << endl;
    }
    
    return numIntersections;

}
int main() {
    int dimensions = 10; // Dimensions of the square
    int numLines = 7; // Number of lines
    lineStruct linesList[numLines];
    srand(1);
    for(int i = 0; i < numLines; i++){
        linesList[i].x1 = rand() % dimensions;
        linesList[i].y1 = rand() % dimensions;
        linesList[i].x2 = rand() % dimensions;
        linesList[i].y2 = rand() % dimensions;
        cout << linesList[i].x1 << " " << linesList[i].y1 << " " << linesList[i].x2 << " " << linesList[i].y2 << endl;
    }
    cout << "There are a total of " << countIntersections(linesList, numLines, dimensions + 1) << " intersections" << endl;   
    return 0;
}
