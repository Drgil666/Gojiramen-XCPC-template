#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>
#include <ctime>
#include <cassert>
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;
typedef long long ll;
const int MAX_N = 250;
int T, cases = 0, p;
char s[MAX_N];
int main()
{
    scanf("%d", &T);
    while(T--){
        scanf("%s%d", &s, &p);
        printf("Case %d: ", ++cases);
        int len = strlen(s);
        if(s[0] == '0' && len == 1){
            printf("divisible\n");
            continue;
        }
        if(p < 0) p = -p;
        int ans = 0, st = 0;
        if(s[0] == '-') st = 1;
        for(int i = st; i < len; i++){
            ans = (int)(((ll) ans * 10 + s[i] - '0') % p);
        }
        if(ans == 0) printf("divisible\n");
        else printf("not divisible\n");
    }
    return 0;
}