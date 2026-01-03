#include <stdint.h>
#include <stdio.h> 
#include <time.h>
#include <unistd.h>

#define MAP_H	10
#define MAP_W	20

#define AIR	0
#define WALL	1
#define PACMAN	2
#define GHOST	3

#define RESET		"\033[0m"
#define CLEAR		"\033[2J\033[H"

#define C_AIR		"\033[48;2;0;0;0m"
#define C_WALL		"\033[48;2;0;46;255m"
#define C_PACMAN	"\033[38;2;255;255;0m"C_AIR
#define C_GHOST		""

#define CH_AIR		"  "
#define CH_WALL		"  "
#define CH_PACMAN	"C "
#define CH_GHOST	"m "

#define UP	0
#define RIGHT	1
#define DOWN	2
#define LEFT	3	

#define PX	st.px
#define PY	st.py

#define POS_PACMAN map[PY][PX]

#define RUNNING st.running

#define INIT_PX 1
#define INIT_PY 1

#define OP	st.op

union cel {
	uint8_t d;

	struct {
		uint8_t type     : 2;
		uint8_t bean     : 1;
		uint8_t reserved : 5;
	};
};

struct {
	uint8_t running;
	uint8_t op;
	int8_t px;
	int8_t py;
} st;

union cel map[MAP_H][MAP_W];


const char *ch[] = {
	C_AIR    CH_AIR,
	C_WALL   CH_WALL,
	C_PACMAN CH_PACMAN,
	C_GHOST  CH_GHOST,
};

void prtch(int t)
{
	printf("%s" RESET, ch[t]);
}

void change(void)
{
	printf("\n");
}

void init(void)
{
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			map[i][j].d = AIR;
		}
	}

	map[INIT_PY][INIT_PX].type = PACMAN;
	map[9][19].type = WALL;
	map[INIT_PY][INIT_PX + 5].type = WALL;	
	RUNNING = 1;
	PX = INIT_PX;
	PY = INIT_PY;
	OP = RIGHT;
}


#define DEBUG 1
void render(void)
{
	printf(CLEAR);
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			prtch(map[i][j].type);
		}
		change();
	}

	if (DEBUG) {
		printf("PX:%d, PY:%d\n", PX, PY);
	}
}


#define FINE 0
#define DEAD 1
int move(void)
{
	int8_t tx = PX;
	int8_t ty = PY;
	if (OP == UP) {
		ty--;
	} else if (OP == RIGHT) {
		tx++;
	} else if (OP == DOWN) {
		ty++;
	} else if (OP == LEFT) {
		tx--;
	}
	if (tx > 0 && tx < MAP_W - 1) {
		if (map[ty][tx].type == WALL)	
			return FINE;
	}

	POS_PACMAN.type = AIR;	
	PX = tx;
	PY = ty;

	if (PX < 0)
		PX = MAP_W - 1;
	else if (PX > MAP_W - 1)
		PX = 0;

	if (POS_PACMAN.type == GHOST)
		return DEAD;
	
	POS_PACMAN.type = PACMAN;
	return FINE;
}

void run(void)
{
	if (move() == DEAD) {
		RUNNING = 0;
	}
		
}

int main(void)
{
	init();
	
	while (RUNNING) {
		run();
		render();
		sleep(1);
	}


	return 0;
}
