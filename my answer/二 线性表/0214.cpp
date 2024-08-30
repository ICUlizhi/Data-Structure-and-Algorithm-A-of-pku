#include <bits/stdc++.h>
using namespace std;

bool search(const vector<string> &d, const string &s){
    return find(d.begin(), d.end(), s) != d.end();
}

int main(){
    vector<string> d,a;
    string s;
    while(cin >> s){
        if(s == "#")break;
        d.push_back(s);
    }
    while(cin >> s){
    	if(s == "#")break;
    	a.push_back(s);
	}
	for(string c : a){
		if(search(d,c)){
			cout<< c <<" is correct"<<endl;continue;
		}
		cout<<c<<":";
		int l = c.length(),m =26;
		vector<string> e;
		for (int i=0;i<l;i++){
			string c0 = c.erase();
			e.push_back(c0);
			for(char j='a';j<='z';j++){
				c0 = c.replace(i,1,1,j);
				e.push_back(c0);
				c0 = c.insert(i,1,j);
				e.push_back(c0);
			}
		}
		for (string f : e){
			if(search(d,f)){
				cout<<' '<<f;
			}
		}
		cout<<endl;
	}
    

}