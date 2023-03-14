#include <iostream>
#include <ctime>
#include <random>
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
bool checkIntersect(lineStruct lineOne, lineStruct lineTwo){
    int directions [4];
    directions[0] = orientation(lineOne.x1, lineOne.x2, lineTwo.x1, lineOne.y1, lineOne.y2, lineTwo.y1);
    directions[1] = orientation(lineOne.x1, lineOne.x2, lineTwo.x2, lineOne.y1, lineOne.y2, lineTwo.y2);
    directions[2] = orientation(lineTwo.x1, lineTwo.x2, lineOne.x1, lineTwo.y1, lineTwo.y2, lineOne.y1);
    directions[3] = orientation(lineTwo.x1, lineTwo.x2, lineOne.x2, lineTwo.y1, lineTwo.y2, lineOne.y2);  
    if(directions[0] != directions[1] && directions[2] != directions[3]){
        return true;
    }
    if(directions[0] == 0 && colinear(lineOne, lineTwo.x1, lineTwo.y1))
        return true;
    if(directions[1] == 0 && colinear(lineOne, lineTwo.x2, lineTwo.y2))
        return true;
    if(directions[2] == 0 && colinear(lineTwo, lineOne.x1, lineOne.y1))
        return true;
    if(directions[3] == 0 && colinear(lineTwo, lineOne.x2, lineOne.y2))
        return true;
    return false;

}
int countIntersections(lineStruct linesList[], int numLines){
    int numIntersections = 0;
    for(int i = 0; i < numLines - 1; i++){
        for(int j = 1; j < numLines; j++){
            if(checkIntersect(linesList[i], linesList[j])){
                numIntersections++;
            }
        }
    }
    return numIntersections;

}
int main() {
    int dimensions = 100; // Dimensions of the square
    int numLines = 10; // Number of lines
    lineStruct linesList[numLines];
    srand(2);
    for(int i = 0; i < numLines; i++){
        linesList[i].x1 = rand() % dimensions;
        linesList[i].y1 = rand() % dimensions;
        linesList[i].x2 = rand() % dimensions;
        linesList[i].y2 = rand() % dimensions;
        cout << linesList[i].x1 << " " << linesList[i].y1 << " " << linesList[i].x2 << " " << linesList[i].y2 << endl;
    }
    cout << "There are a total of " << countIntersections(linesList, numLines) << " intersections" << endl;   
    return 0;
}
