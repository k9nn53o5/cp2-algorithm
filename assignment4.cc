//count the maximum point on a straight line
//need to avoid precision problems
//  or maybe can use <string, int>, using string as the key instead of double(slope)
//  above will more easier to write than <pair<int, int>, int>
#include <iostream>
#include <unordered_map>
using namespace std;

struct point{
    int x, y;
};

//get this from
//https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
struct hash_pair{
    template<class T1, class T2>
    size_t operator()(const pair<T1, T2>& p)const{
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);
        return h1 ^ h2;
    }
};

int gcd(int a, int b){
    if(b==0){
        return a;
    }
    return gcd(b, a%b);
}

int max_of_three(int v, int h, int t){
    if((v>=h)&&(v>=t)){
        return v;
    }else if((h>=v)&&(h>=t)){
        return h;
    }else if((t>=v)&&(t>=h)){
        return t;
    }
    return 0;
}

int main(){
    int n, max=0, cur_max, total, vertical, horizontal, X, Y, _gcd, count=0;
    scanf("%d", &n);
    struct point p[n];
    unordered_map<pair<int, int>, int, hash_pair> hash_map;
    for(int i=0; i<n; i++){
        scanf("%d %d", &p[i].x, &p[i].y);
    }
    for(int i=0; i<n-1; i++){
        cur_max=0, vertical=1, horizontal=1, total=1, hash_map.clear();
        for(int j=i+1; j<n; j++){
            if(p[i].x==p[j].x){
                vertical++;
            }else if(p[i].y==p[j].y){
                horizontal++;
            }else{
                X = p[i].x-p[j].x;
                Y = p[i].y-p[j].y;
                _gcd = gcd(X, Y);
                //cout  << "before: " << _gcd << " " << X << " " << Y << endl;
                if(_gcd!=0){
                    X /= _gcd;
                    Y /= _gcd;
                }
                //cout  << "after: " << _gcd << " " << X << " " << Y << endl;
                pair<int, int> slope = make_pair(X, Y);
                if(hash_map.find(slope)==hash_map.end()){
                    hash_map[slope] = 1;
                }else{
                    hash_map[slope]+=1;
                    cout << "###slope = " << slope.first << " " << slope.second << endl;
                }
                if(hash_map[slope] > total){
                    total = hash_map[slope];
                }
                //cout << "hash_map = " << hash_map[slope] << endl;
            }
        }
        /*
        for(auto i = hash_map.begin(); i!=hash_map.end(); i++){
            if(i->second+1 > total){
                total = (i->second)+1;
            }
        }
        */
        //cout << vertical << " " << horizontal << " " << total+1 << endl ;
        cur_max = max_of_three(vertical, horizontal, total+1);
        if(cur_max > max){
            max = cur_max;
        }
    }
    cout << max;
    return 0;
}