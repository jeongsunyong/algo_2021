#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    float b=brown, y=yellow;
    
    //2*(w-2) + 2*h  = brown && (w-2)*(h-2) = yellow
    
    int w = +((2+b/2) + sqrt(pow((2+b/2),2)-4*(b+y)))/2;  
    int h = +((2+b/2) - sqrt(pow((2+b/2),2)-4*(b+y)))/2;
    
    answer.push_back(w);
    answer.push_back(h);
    
    return answer;
}
