#include<bits/stdc++.h>
using namespace std;

string awa(string s){
	string r;
	for (auto i : s){
		if (i != '-'){
			if (('0'<=i) && ('9'>=i)) r+=i;
			else if (('A'<=i) && ('C'>=i)) r+='2';
			else if (('D'<=i) && ('F'>=i)) r+='3';
			else if (('G'<=i) && ('I'>=i)) r+='4';
			else if (('J'<=i) && ('L'>=i)) r+='5';
			else if (('M'<=i) && ('O'>=i)) r+='6';
			else if (('P'<=i) && ('S'>=i)) r+='7';
			else if (('T'<=i) && ('V'>=i)) r+='8';
			else if (('W'<=i) && ('Y'>=i)) r+='9';
		}
	}
	return r;
}

void print(string r,int num){
	cout<<r[0]<<r[1]<<r[2]<<'-'<<r[3]<<r[4]<<r[5]<<r[6]<<' '<<num<<endl;
}

int main(){
	map<string, int> dict;
	int c;cin>>c;
	while(c--){
		string r0;cin >> r0;
		string r = awa (r0);
		dict[r] += 1;
	}
	int o = 0;
	for (auto i : dict){
		if (i.second>1){
			print(i.first,i.second);
			o=1;
		}
	}
	if (!o) {
		cout << "No duplicates.";
	}
}

