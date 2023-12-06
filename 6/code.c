
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//int time[3] = {7, 15, 30};
//int dist[3] = {9, 40, 200};
//int mine[3] = {0,0,0};
//int num = 3;

//int time[4] = {53, 71, 78, 80};
//int dist[4] = {275, 1181, 1215, 1524};
//int mine[4] = {0,0,0, 0};
//int num = 4;

//int time[1] = {71530};
//int dist[1] = {940200};
//int mine[1] = {0};
//int num = 1;


long long int time[1] = {53717880};
long long int dist[1] = {275118112151524};
long long int mine[1] = {0};
int num = 1;

int main() {
    
    for(int i=0; i<num; ++i) {
        int hold = 0;
        while(hold < time[i]) {
            long long int derp = (time[i] - hold) * hold;
            //printf("got %lli\n", derp );
            hold++;
            if(derp > dist[i]) {
                mine[i]++;
            }
        }
        printf("DERP %lli\n\n", mine[i]);
    }
    
    long long int got = 1;
    for(int i=0; i<num; ++i) {
        got *= mine[i];
    }
    printf(".... and %lli\n", got);
    return 0;
}