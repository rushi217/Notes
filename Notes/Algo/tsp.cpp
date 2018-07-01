#include <iostream>
#include <stack>
#define INT_MAX 90090

using namespace std;

int findmin(int cost[], bool visited[]){
	int minindex = 0, min = INT_MAX;
	for(int i = 0; i < 9; i++){
		if(cost[i] < min && !visited[i]){
			min = cost[i];
			minindex = i;
		}
	}
	return minindex;
}

void prims(int adjmat[][9]){
	bool visited[9];
	int cost[9];
	int parent[9];
	stack<int> s;
	for(int i = 0; i < 9; i++){
		cost[i] = INT_MAX;
		parent[i] = 0;
		visited[i] = false;
	}
	cost[0] = 0;
	for(int i = 0; i < 8; i++){
		int min = findmin(cost, visited);
		visited[min] = true;
		for(int j = 0; j < 9; j++){
			if(adjmat[min][j] && !visited[j] && adjmat[min][j] < cost[j]){
				cost[j] = adjmat[min][j];
				parent[j] = min;
			}
		}
	}
	//for(int i = 0; i < 9; i++){
		//cout<<i<<" "<<parent[i]<<endl;
	//}
	int premat[9][9];
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(parent[j] == i){
				premat[i][j] = adjmat[i][j];
				//cout<<i<<" "<<j<<endl;
			}
			else{
				premat[i][j] = 0;
			}
		}
	}
	int start = 0;
	int n = 0;
	s.push(0);
	while(!s.empty()){
		n = s.top();
		cout<<n<<endl;
		s.pop();
		for(int i = 0; i < 9; i++){
			if(premat[n][i] != 0){
				s.push(i);
			}
		}
	}
}

int main(){
	int adjmat[9][9] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 14, 10, 0, 2, 0, 0},
                      {0, 0, 0, 0, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };
    prims(adjmat);
    
	return 0;
}
