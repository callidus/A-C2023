#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum {
    FIVE_O_K,
    FOUR_O_K,
    FULL_HOUSE,
    THREE_O_K,
    TWO_PAIR,
    ONE_PAIR,
    HIGH_CARD
} HandType;

const char* name[] = {
 "Five of a kind",
 "Four of a kind",
 "Full house",
 "Three of a kind",
 "Two pair",
 "One pair",
 "High card"
};

typedef struct { char hand[6]; char ordr[6]; int bid; HandType type; } Play;

char lut[] = "AKQJT98765432";

Play play[1024];
int num = 0;

int cardToIdx(char c) {
    int x = 0;
    while(lut[x++] != c);
    return x-1;
}

int cardCmp(const void* a, const void* b) {
    int x = cardToIdx(*(const char*)a);
    int y = cardToIdx(*(const char*)b);
    return x - y;
}

HandType handType(char* hand) {
    int count[13];
    memset(count, 0, 13 * sizeof(int));
    for(int i=0; i<5; ++i) {
        count[cardToIdx(hand[i])]++;
    }

    HandType ht = HIGH_CARD;
    for(int i=0; i<13; ++i) {
        if(count[i] == 2) {
            if (ht == HIGH_CARD) ht = ONE_PAIR; 
            else if (ht == ONE_PAIR) ht = TWO_PAIR;
            else if (ht == THREE_O_K) ht = FULL_HOUSE;
        }

        if(count[i] == 3) {
            ht = (ht == ONE_PAIR) ? FULL_HOUSE : THREE_O_K;
        }

        if(count[i] == 4) {
            ht = FOUR_O_K;
            break;
        }

        if(count[i] == 5) {
            ht = FIVE_O_K;
            break;
        }
    }
    return ht;
}

int cmp(const void* a, const void* b) {
    const Play* pa = a;
    const Play* pb = b;
    if(pa->type == pb->type) {
        for(int i=0; i<5; ++i) {
            int va = cardToIdx(pa->hand[i]);
            int vb = cardToIdx(pb->hand[i]);
            if(va != vb) {
                return vb - va; 
            }
        }
    }
    return pb->type - pa->type;
}

int main(int argc, char** argv) {
    memset(play, 0, 1024 * sizeof(Play));
    FILE* fp = fopen("data.txt", "r");
    while(fscanf(fp, "%s %i\n", play[num].hand, &play[num].bid) == 2)  {
        // /printf("%s %i\n", play[num].hand, play[num].bid);
        memcpy(play[num].ordr, play[num].hand, 6);
        qsort(play[num].ordr, 5, 1, cardCmp);
        play[num].type = handType(play[num].ordr);
        num++;
    }

    qsort(play, num, sizeof(Play), cmp);

    int got = 0;
    for(int i=0; i<num; ++i) {
        printf("play: %s %i (%s)\n", play[i].hand, play[i].bid, name[play[i].type]);
        got += (i+1) * play[i].bid;
    }
    
    printf("got %i\n", got);
    return 0;
}
