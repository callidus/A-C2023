#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct  {
	int id,r,g,b;
} Game;


Game game;
int main(int argc, char** argv) {
	int val, pos, t;
	char buf[32];

	val = pos = t = 0;
	FILE* fp = fopen("data.txt", "r");
	while(fscanf(fp, "Game %i:", &game.id) == 1) {
		printf("Game %i: ", game.id);
		pos = 1;
		while(true) {
			fscanf(fp, " %i %s", &t, buf);
			switch(buf[0]) {
				case 'r': game.r = t; break;
				case 'g': game.g = t; break;
				case 'b': game.b = t; break;
				default: {
					printf("huh %c\n", buf[0]);
					assert(false);
				}
			}
			t = strlen(buf)-1;
			if( buf[t] != ',') {
				printf("%i %i %i : ", game.r, game.g, game.b);
				pos = pos && !(game.r > 12 || game.g > 13 || game.b > 14);
				game.r = game.g = game.b = 0;
				if(buf[t] != ';') break;
			}
		}
		if(pos) val += game.id;
		printf(" pos %i\n", pos);
		fgetc(fp);
	}
	printf("got %i\n", val);
}
