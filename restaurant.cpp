#include "main.h"

class Restaurant {
	public:
		string restaurantname;
		int MAXSIZE;
		int NUM;
		virtual void LAPSE();
		public:
		class customer {
			string customername;
		};
};

void simulate(string filename)
{
	cout << "Good Luck";
	return;
}
//SORT FREQUENCY
int check(vector<pair<int,int>> ys,int x){
    for(size_t i=0;i<ys.size();i++){
        if(ys[i].first==x)
            return i;
    }
    return -1;
}
void insertsort(vector<pair<int,int>> &ys){
    for(size_t i=1;i<ys.size();i++){
        int tmp=ys[i].second;
        int tmp1=ys[i].first;
        int j;
        for(j=i;j>0 && ys[j-1].second<tmp;j--){
            ys[j].second=ys[j-1].second;
            ys[j].first=ys[j-1].first;
        }
        ys[j].second=tmp;
        ys[j].first=tmp1;
    }
}

void sortByFrequency(int arr[], int n){
    vector<pair<int,int>> ys;
    ys.emplace_back(arr[0],1);
    
    for(int i=1;i<n;i++){
        int h=check(ys,arr[i]);
        if(h==-1){
           ys.emplace_back(arr[i],1);
        }
        else {
            ys[h].second++;
        }
    }
    insertsort(ys);
    int j=0;
    for(size_t i=0;i<ys.size();i++){
        while(ys[i].second>0){
            arr[j++]=ys[i].first;
            ys[i].second--;
        }
    }
}
//END SORT FREQUENCY
void LAPSE(string name){

}

void KOKUSEN(){

}

void KEITEIKEN(int NUM){

}

void HAND(){

}

void LIMITLESS(int NUM){

}

void CLEAVE(int NUM){

}