#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct coord{
	int x;
	int y;
}coord;

void show(char field[10][10]){
	printf(" ");
	for(int i = 0; i < 10; i++) printf("\033[1;33m%d\033[0m", i);
	printf("\n");
	for(int i = 0; i < 10; i++){
		printf("\033[1;33m%d\033[0m", i);
		for(int j = 0; j < 10; j++){
			if(field[i][j] == 'O') printf("\033[0;30;46m-\033[0m");// printf("\033[1;30;42mO\033[0m");
			else if(field[i][j] == '-')  printf("\033[0;30;46m-\033[0m");
			else if(field[i][j] == 'x') printf("\033[1;30;41mx\033[0m");
			else printf("\033[0;30;43m+\033[0m");
		}
		printf("\n");
	}
}

void generate(char field[10][10], coord coords[40]){
	int x0, y0, direction, dx, dy;
	int fl = 1;
	int s = 0;
	int k = 0;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			field[i][j] = '-';
		}
	}
	for(int i = 3; i > -1; i--){
		for(int j = 0; j < 4 - i; j++){
			fl = 1;
			while(fl){
				s = 0;
				x0 = rand()%10;
				y0 = rand()%10;
				direction = rand()%4;
				dx = (direction%2) * ((direction/2) * (1) + (!(direction/2)) * (-1));
				dy = (!(direction%2)) * ((direction/2) * (1) + (!(direction/2)) * (-1));
				if(x0 + i*dx >= 0 && x0 + i*dx < 10 && y0 + i*dy >= 0 && y0 + i*dy < 10){
					for(int k = 0; k < i+1; k++){
						if(field[x0+k*dx-1][y0+k*dy-1] == '-' && field[x0+k*dx-1][y0+k*dy] == '-' && field[x0+k*dx-1][y0+k*dy+1] == '-' 
							&& field[x0+k*dx][y0+k*dy-1] == '-' && field[x0+k*dx][y0+k*dy] == '-' && field[x0+k*dx][y0+k*dy+1] == '-'
							&& field[x0+k*dx+1][y0+k*dy-1] == '-' && field[x0+k*dx+1][y0+k*dy] == '-' && field[x0+k*dx+1][y0+k*dy+1] == '-')
								s+=1;
					}
				}
				if(s == i+1) fl = 0;
				
			}
			field[x0][y0] = 'O'; coords[k].x = x0; coords[k++].y = y0;
			if((i+1)/2){field[x0+dx][y0+dy] = 'O'; coords[k].x = x0+dx; coords[k++].y = y0+dy;}
			if((i+1)/3){field[x0+2*dx][y0+2*dy] = 'O'; coords[k].x = x0+2*dx; coords[k++].y = y0+2*dy;}
			if((i+1)/4){field[x0+3*dx][y0+3*dy] = 'O'; coords[k].x = x0+3*dx; coords[k++].y = y0+3*dy;}
		}
	}
}

int checker(coord coords[20]){
	if(coords[0].x + coords[1].x + coords[2].x + coords[3].x != -4 && (coords[0].x == -1 || coords[1].x == -1 || coords[2].x == -1 || coords[3].x == -1))
		return 1;

	if(coords[4].x + coords[5].x + coords[6].x != -3 && (coords[4].x == -1 || coords[5].x == -1 || coords[6].x == -1))
		return 1;
	if(coords[7].x + coords[8].x + coords[9].x != -3 && (coords[7].x == -1 || coords[8].x == -1 || coords[9].x == -1))
		return 1;

	if(coords[10].x + coords[11].x != -2 && (coords[10].x == -1 || coords[11].x == -1))
		return 1;
	if(coords[12].x + coords[13].x != -2 && (coords[12].x == -1 || coords[13].x == -1))
		return 1;
	if(coords[14].x + coords[15].x != -2 && (coords[14].x == -1 || coords[15].x == -1))
		return 1;
	return 0;
}

int step(int* tru, int* trudx, int* trudy, int* damage, int* game_over, int* first_damage, int* m, coord* damage_coords, coord* first_damage_coords, coord ship[4], char field2[10][10], coord coords2[20]){
	int x0, y0;
	int direction,dx,dy;

		do{
			if(*damage){
				if(*tru){
					dx = *trudx;
					dy = *trudy;
				}else{
					direction = rand()%4;
					dx = (direction%2) * ((direction/2) * (1) + (!(direction/2)) * (-1));
					dy = (!(direction%2)) * ((direction/2) * (1) + (!(direction/2)) * (-1));
				}
				x0 = damage_coords->x + dx;
				y0 = damage_coords->y + dy;
			}
			else{
				x0 = rand()%10;
				y0 = rand()%10; 
			}
		}while(x0 < 0 || x0 > 9 || y0 < 0 || y0 > 9 || (field2[x0][y0] == 'x' || field2[x0][y0] == '+'));
		if(field2[x0][y0] == 'O'){
			field2[x0][y0] = 'x';
			ship[*m].x = x0; ship[(*m)++].y = y0;
			(*game_over)++;
			*damage = 1;
			damage_coords->x = x0;
			damage_coords->y = y0;
			if(*first_damage){
				*first_damage = 0;
				first_damage_coords->x = x0;
				first_damage_coords->y = y0;
			}else if(!*tru){
				*tru = 1;
				*trudx = dx;
				*trudy = dy;
			}
			for(int i = 0; i < 20; i++){
				if(coords2[i].x == x0 && coords2[i].y == y0){
					coords2[i].x = -1;
					break;
				}
			}
			*damage = checker(coords2);
			if(*tru && *damage && (x0 + dx < 0 || x0 +dx  > 9 || y0 + dy < 0 || y0 + dy > 9 || field2[x0+dx][y0+dy] == '+' || field2[x0+dx][y0+dy] == 'x')){
				*trudx = -*trudx;
				*trudy = -*trudy;
				damage_coords->x = first_damage_coords->x;
				damage_coords->y = first_damage_coords->y;
			}
			if(!*damage){
				*first_damage = 1;
				*tru = 0;
				for(int i = 0; i < 4; i++){
					if(ship[i].x == -1) break;
					if(ship[i].x-1 >= 0 && ship[i].x-1 < 10 && ship[i].y-1 >= 0 && ship[i].y-1 < 10) field2[ship[i].x-1][ship[i].y-1] = '+';
					if(ship[i].x-1 >= 0 && ship[i].x-1 < 10 && ship[i].y >= 0 && ship[i].y < 10) field2[ship[i].x-1][ship[i].y] = '+';
					if(ship[i].x-1 >= 0 && ship[i].x-1 < 10 && ship[i].y+1 >= 0 && ship[i].y+1 < 10) field2[ship[i].x-1][ship[i].y+1] = '+';
					if(ship[i].x >= 0 && ship[i].x < 10 && ship[i].y-1 >= 0 && ship[i].y-1 < 10) field2[ship[i].x][ship[i].y-1] = '+';
					if(ship[i].x >= 0 && ship[i].x < 10 && ship[i].y+1 >= 0 && ship[i].y+1 < 10) field2[ship[i].x][ship[i].y+1] = '+';
					if(ship[i].x+1 >= 0 && ship[i].x+1 < 10 && ship[i].y-1 >= 0 && ship[i].y-1 < 10) field2[ship[i].x+1][ship[i].y-1] = '+';
					if(ship[i].x+1 >= 0 && ship[i].x+1 < 10 && ship[i].y >= 0 && ship[i].y < 10) field2[ship[i].x+1][ship[i].y] = '+';
					if(ship[i].x+1 >= 0 && ship[i].x+1 < 10 && ship[i].y+1 >= 0 && ship[i].y+1 < 10) field2[ship[i].x+1][ship[i].y+1] = '+';
				}
				for(int i = 0; i < 4; i++){
					if(ship[i].x == -1) break;
					field2[ship[i].x][ship[i].y] = 'x';
				}
				for(int i = 0; i < 4; i++){
					if(ship[i].x == -1) break;
					ship[i].x = -1;
					ship[i].y = -1;
				}
				*m = 0;
			}
			return 1;
		}
		else {
			field2[x0][y0] = '+';
			if(*tru && *damage){
				*trudx = -*trudx;
				*trudy = -*trudy;
				damage_coords->x = first_damage_coords->x;
				damage_coords->y = first_damage_coords->y;
			}
			return 0;
		}
}

void battle(char field1[10][10], char field2[10][10], coord coords1[20], coord coords2[20]){

	//first init
	int tru1 = 0, trudx1, trudy1, damage1 = 0, game_over1 = 0, first_damage1 = 1, m1 = 0;
	coord damage_coords1, first_damage_coords1, ship1[4];
	for(int i = 0; i < 4; i++){
		ship1[i].x = -1;
		ship1[i].y = -1;
	}

	//second init
	int tru2 = 0, trudx2, trudy2, damage2 = 0, game_over2 = 0, first_damage2 = 1, m2 = 0;
	coord damage_coords2, first_damage_coords2, ship2[4];
	for(int i = 0; i < 4; i++){
		ship2[i].x = -1;
		ship2[i].y = -1;
	}

	int next1 = 1;
	char number = 'y';
	int fl = 1;
	while(fl && game_over1 < 20 && game_over2 < 20){
		if(next1) next1 = step(&tru1,&trudx1,&trudy1,&damage1,&game_over1,&first_damage1,&m1,&damage_coords1,&first_damage_coords1,ship1,field1,coords1);
		else 	  next1 = !(step(&tru2,&trudx2,&trudy2,&damage2,&game_over2,&first_damage2,&m2,&damage_coords2,&first_damage_coords2,ship2,field2,coords2));

		show(field1);show(field2);
		printf("Next? (Y/n) ");
		scanf("%c",&number);
		while(number != '\n' && number != 'y' && number != 'n'){
			do scanf("%c",&number); while(number == '\n');
		}
		if (number == 'n') fl = 0;
	}
}

void writing(char field1[10][10], char field2[10][10], clock_t* t, FILE* output){
	output = fopen("output.bin", "wb");
	fwrite(t, sizeof(clock_t), 1, output);
	fwrite(field1, sizeof(char), 100, output);
	fwrite(field2, sizeof(char), 100, output);
	fclose(output);
}

void reading(clock_t* t, FILE* output){
	output = fopen("output.bin", "rb");
    if (output == NULL) {
		printf("Error opening file");
		return;
    }
    fread(t, sizeof(clock_t), 1, output);
    fclose(output);
}

int main(int argc, char const *argv[]){
	int fl = 1;
	char answer;
	char field1[10][10];char field2[10][10];
	coord coords1[20];coord coords2[20];
	FILE* output = NULL;
    clock_t t;
	while(fl){
		printf("1)Play game without writing\n2)Play game with writing\n3)Reproduce game\n4)Exit\n");
		do scanf("%c", &answer); while(answer == '\n');
		switch(answer){
			case '1':
				t = time(NULL);
				srand(t);
				generate(field1,coords1);generate(field2,coords2);
				battle(field1,field2,coords1,coords2);
			break;
			case '2':
				t = time(NULL);
				printf("%ld\n", t);
				srand(t);
				generate(field1,coords1);generate(field2,coords2);
				writing(field1, field2, &t, output);
				battle(field1,field2,coords1,coords2);
				system("hexdump -C output.bin");
			break;
			case '3':
				reading(&t, output);
				printf("%ld\n", t);
				srand(t);
				generate(field1,coords1);generate(field2,coords2);
				battle(field1,field2,coords1,coords2);
			break;
			case '4':
				fl = 0;
			break;
		}
	}	
	return 0;
}