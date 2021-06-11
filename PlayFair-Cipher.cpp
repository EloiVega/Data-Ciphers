#include<bits/stdc++.h>
using namespace std;

int FixedMod(int a, int b){
  return ((a%b)+b)%b;
}

class PlayFair{
public:
 
	//CONSTRUCTOR
	PlayFair(string plain){
		for(int i = 0 ; i < 5 ; ++i)
			for(int j = 0 ; j < 5 ; ++j)
				letterPosition[key[i][j] - 'a'] = {i,j};
 
		for(int i = 0; i < plain.size() ; ++i)
			if(isalpha(plain[i]))
				this->plain += tolower(plain[i]);
	}
 
	void outputEncryption(){
		encrypt();
		cout << "Cipher text after using PlayFair encryption: " << cipher << endl;
	}
 
	void outputDecryption(){
		decrypt();
		cout << "Plain text after using PlayFair decryption: " << plain << endl;
	}
 
private:
	char key[5][5] = {
		{'l', 'o', 'v', 'e', 'i'},
		{'s', 'a', 'm', 'n', 'y'}, 
		{'p', 'd', 'r', 't', 'h'}, 
		{'g', 'b', 'c', 'f', 'k'}, 
		{'q', 'u', 'w', 'x', 'z'}
	};
	pair<int,int> letterPosition[26];
	string fragments[1000];
	int sz;
	string plain;
	string cipher;
 
	//createFragments: SPLITS STRING INTO A COUPLE (example: abcd -> {'ab', 'cd'})
	void createFragments(string str){
		// cout << str << " ";
		//Preventing double characters (example: aabc -> axabc)
		string temp = "";
		temp += str[0];
		for(int i = 1 ; i < str.length() ; ++i){
			// cout << temp << " " << str << endl;
			if(temp[temp.length()-1] == str[i] && temp.length()%2 == 1) temp += 'x';
			temp += str[i];
 
		}
		str = temp;
		// cout << str << endl;
		//Adds an 'x' to the end of the string in case the length of it is odd.
		if(str.length()%2 == 1) str += 'x';
 
		//adds each to the array and increase (sz) the size of the fragments
		sz = 0;
		for(int i = 1 ; i < str.length() ; i+=2){
			fragments[sz] = "";
			fragments[sz] += str[i-1];
			fragments[sz] += str[i];
			sz++;
		}
 
		// for(int i = 0 ; i < sz ; ++i)
		// 	cout << fragments[i][0] << fragments[i][1] << " ";
		// puts("");
	}
 
	//Removes the Added (X)s after decryption.
	void removeX(string str){
		string temp = "";
		for(int i = 0 ; i < str.length() ; ++i){
			if(str[i] != 'x') temp += str[i];
		}
		this->plain = temp;
	}
 
	//ENCRYPTION
	void encrypt(){
		createFragments(this->plain);
 
		pair<int, int> pos1, pos2;
		string temp = "";
		for(int i = 0 ; i < sz ; ++i){
			pos1 = letterPosition[fragments[i][0]-'a'];
			pos2 = letterPosition[fragments[i][1]-'a'];
 
 
			//checking if both letters lay in the same column
			if(pos1.first == pos2.first){
				pos1.second = FixedMod((pos1.second+1),5);
				pos2.second = FixedMod((pos2.second+1),5);
 
				temp += key[pos1.first][pos1.second];
				temp += key[pos2.first][pos2.second];
				// printf("1. pos1: %d %d , pos2: %d %d ", pos1.first, pos1.second, pos2.first, pos2.second);
			}
			//checking if both letters lay in the same row
			else if(pos1.second == pos2.second){
				pos1.first = FixedMod((pos1.first+1),5);
				pos2.first = FixedMod((pos2.first+1),5);
 
				temp += key[pos1.first][pos1.second];
				temp += key[pos2.first][pos2.second];
				// printf("2. pos1: %d %d , pos2: %d %d ", pos1.first, pos1.second, pos2.first, pos2.second);
			}
			//checking if both points are on different rows and different columns
			else{
				temp += key[pos1.first][pos2.second];
				temp += key[pos2.first][pos1.second];
			}
			// cout << "temp: " << temp << endl;
 
			this->cipher = temp;
		}
	}
 
	//DECRYPTION
	void decrypt(){
		createFragments(this->cipher);
 
		pair<int, int> pos1, pos2;
		string temp = "";
		for(int i = 0 ; i < sz ; ++i){
			pos1 = letterPosition[fragments[i][0]-'a'];
			pos2 = letterPosition[fragments[i][1]-'a'];
 
 
			//checking if both letters lay in the same column
			if(pos1.first == pos2.first){
				pos1.second = FixedMod((pos1.second-1),5);
				pos2.second = FixedMod((pos2.second-1),5);
 
				temp += key[pos1.first][pos1.second];
				temp += key[pos2.first][pos2.second];
				// printf("1. pos1: %d %d , pos2: %d %d ", pos1.first, pos1.second, pos2.first, pos2.second);
			}
			//checking if both letters lay in the same row
			else if(pos1.second == pos2.second){
				pos1.first = FixedMod((pos1.first-1),5);
				pos2.first = FixedMod((pos2.first-1),5);
 
				temp += key[pos1.first][pos1.second];
				temp += key[pos2.first][pos2.second];
				// printf("2. pos1: %d %d , pos2: %d %d ", pos1.first, pos1.second, pos2.first, pos2.second);
			}
			//checking if both points are on different rows and different columns
			else{
				temp += key[pos1.first][pos2.second];
				temp += key[pos2.first][pos1.second];
			}
			this -> plain = temp;
		}
		removeX(plain);
	}
} ;

int main(){
  PlayFair *pf = new PlayFair("AMBASSADOR SHOT");
  pf -> outputEncryption();
  pf -> outputDecryption();
  
  return 0;
}
