#include <bits/stdc++.h>
using namespace std;

//#define pair <int,int> PR;

vector<vector<char>> v;																				//Storage of Board		
unordered_set <int> mines;																			//Set of mines where (n*X + Y) is used as key		
unordered_map <int,int> mp;																			//To keep in check cell that has been revealed
int X,Y;																							//Coordinates given by user each time
int n;																								//n is total no. of row/column on board;
int m;																								//No. of mines = m				

void initialise_board(){
	for(int i=0;i<n;i++){															
		vector<char> a;
		for(int j=0;j<n;j++){
			a.push_back('_');
		}
		v.push_back(a);
	}
}

void initialise_mines(){
	srand(time(0));																			//srand(time(0) ensures each time different random nos. are generated	
	while(mines.size()<m){
		int x,y;
		x = rand() % n;
		y = rand() % n;
		if(x!=X || y!=Y){
			mines.insert(n*x + y);	
		}
	}
}

void get_points(){
	loop:
	cout<<"Coordinates for X:";
	cin>>X;
	cout<<"Coordinates for Y:";
	cin>>Y;
	cout<<endl;

	if(X<0 || X>=n || Y<0 || Y>=n){
		cout<<"Enter correct Coordinates";
		goto loop;
	}
}

int check_mines(int x,int y){																			//Count of mines around all 8 blocks of given coordinates is checked and then count is returned 
	int count=0;
	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			if(i>=0 && i<n && j>=0 && j<n && !(i==x && j==y)){
				if(mines.find(n*i + j)!=mines.end())	count++;
			}
		}
	}
	return count;
}

void show_board(){																			//Status of Board after every move is shown
	cout<<"Current Status of Board:"<<endl;
	cout<<"     ";
	for(int i=0;i<n;i++)	cout<<i<<" ";
	cout<<"\n\n";
	for(int i=0;i<n;i++){
		cout<<i<<"    ";
		for(int j=0;j<n;j++){
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}


void reveal(int x,int y){																	//using dfs on matrix for finding revealing blocks
	if(x<0 || x>=n || y<0 || y>=n)	return;
	if(mines.find(n*x + y)!=mines.end())	return;
	if(mp[n*x + y]==1)	return;

	char count = '0' + check_mines(x,y);														
	v[x][y] = count;
	mp[n*x + y] = 1;

	if(count!='0')	return;

	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			reveal(i,j);
		}
	}
}


int main(int argc, char const *argv[])
{	
	n=9;
	m=10;
	
	initialise_board();		
	show_board();																			//Board is initialised		
	
	bool flag = true;
	int i=0;

	while(mp.size()<(n*n)-m){
		get_points();
		//i++;
		if(mp.empty()){																			//After first move mines are initialised so user doesn't encounter a mine on first try 	
			initialise_mines();
		}
		else{
			if(mp[n*X + Y]==1){
				cout<<"Already Selected"<<endl;
				continue;
			}
			if(mines.find(n*X + Y)!=mines.end()){											//Checking if a mine is encoutered or not
				flag = false;
				v[X][Y] = '*';
				show_board();
				break;
			}
			//mp[n*X + Y] = 1;
		}

		reveal(X,Y);
		//char count = '0' + check_mines(X,Y);														
		//v[X][Y] = count;
		//mp[n*X + Y] = 1;
		show_board();
	}

	if(flag)	cout<<"YOU WIN";
	else	cout<<"YOU LOSE";

	return 0;
}
