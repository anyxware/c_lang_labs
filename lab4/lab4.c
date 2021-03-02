#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct student{
	char* surname;
	char* group;
	float mark;
}student;

char* get_str(){
	char buf[80] = {0};
	char* res = NULL;
	int len = 0;
	int n = 0;
	do{
		n = scanf("%80[^\n]",buf);
		if(n < 0){
			if(!res) return NULL;	
		} else if(n > 0){
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res,str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		} else{
			scanf("%*c");
		}
	}while(n > 0);

	if(len > 0) res[len] = '\0';
	else res = calloc(1,sizeof(char));
	return res;
}

char read_number(){
	char number;
	scanf("%c",&number);
	while(number != '1' && number != '2' && number != '3' && number != '4' && number != '5' && number != '6' && number != '7'){
		do scanf("%c",&number); while(number == '\n');
	}
	return number;
}

int checkSurname(student* man){
	int fl = 0;
	if(man->surname[0] < 65 || man->surname[0] > 90){
		fl = 1;
		return fl;
	}
	for(int j = 1; j < strlen(man->surname); j++){
		if(man->surname[j] < 97 || man->surname[j] > 122){
			fl = 1;
			return fl;
		}
	}
	return fl;
}

int checkGroup(student* man){
	int fl = 0;
	if(strlen(man->group) > 7){
		fl = 1;
		return fl;
	}
	if(man->group[0] != 'B' && man->group[0] != 'S'){
		fl = 1;
		return fl;
	}
	if(man->group[1] < 48 || man->group[1] > 57 || man->group[2] < 48 || man->group[2] > 57){
		fl = 1;
		return fl;
	}
	if(man->group[3] != '-'){
		fl = 1;
		return fl;
	}
	if(man->group[4] < 49 || man->group[4] > 57 || man->group[5] < 48 || man->group[5] > 57 || man->group[6] < 48 || man->group[6] > 57){
		fl = 1;
		return fl;
	}
	
	return 0;
}

int checkScore(char** score){
	int fl = 0;
	int dot = 0;
	for(int i = 0; i < strlen(*score); i++){
		if((*score)[i] == '.'){
			dot++;
			if(dot > 1){
				fl = 1;
				return fl;
			}
		}else if((*score)[i] < 48 || (*score)[i] > 57){
			fl = 1;
			return fl;
		}
		if((*score)[strlen(*score)-1] == '.'){
			fl = 1;
			return fl;
		}
	}
	return fl;
}

float string_to_float(char** score, student* man){
	int kdot = 0;
	float remainder = 1;
	for(int i = 0; i < strlen(*score); i++){
		if(kdot)
			remainder *= 10;
		if((*score)[i] != '.'){
			man->mark *= 10;
			man->mark += (int)(*score)[i] - 48;
		}else if((*score)[i] == '.')
			kdot = 1;
	}
	man->mark /= remainder;
}

int reading(student* students){
	char answer2;
	int n = 0;
	int fl = 0;
	do{
		student man;
		man.surname = NULL;
		man.group = NULL;
		man.mark = 0;
		char* score = NULL;
		char* s = NULL;
		//Read surname
		printf("\033[1;36mInput surname['Ivanov'](please use only ASCII symbols): \033[0m\n");
		s = get_str();
		do{
			fl = 0;
			man.surname = get_str();
			fl = checkSurname(&man);
			if(fl) printf("\033[1;31mInvalid surname\033[0m\n");
		}while(fl);

		//Read group
		printf("\033[1;36mInput group['B20-513'](please use only ASCII symbols): \033[0m\n");
		printf("\033[1;36mUse B**-*** if undergraduate and S**-*** if specialty\033[0m\n");
		do{
			fl = 0;
			man.group = get_str();
			fl = checkGroup(&man);
			if(fl) printf("\033[1;31mInvalid group\033[0m\n");
		}while(fl);

		//Read score
		printf("\033[1;36mInput mark['17.56'](please use only ASCII symbols): \033[0m\n");
		do{
			fl = 0;
			score = get_str();
			fl = checkScore(&score);
			if(fl) printf("\033[1;31mInvalid mark\033[0m\n");
		}while(fl);
		string_to_float(&score, &man);

		//Writing
		char answer1;

		printf("\33[1;34mYour date is:\033[0m\033[1;33m\n%s %s %s?(y/n)\033[0m\n", man.surname, man.group, score);
		do scanf("%c",&answer1); while(answer1 != 'y' && answer1 != 'n');
		if(answer1 == 'y')
			students[n++] = man;

		printf("\033[1;34mAdd any other students?(y/n)\033[0m\n");
		do scanf("%c",&answer2); while(answer2 != 'y' && answer2 != 'n');

		free(score);
	}while(answer2 != 'n');
	return n;
}

int check_flow(char* flow, student* man, char** score){
	int i = 0;
	int nsur = 0;
	int ngro = 0;
	int nsco = 0;
	int len = strlen(flow);
	while(flow[i] == ' '){
		i++;
		if(i > len) return 0;
	}
	nsur = i;
	while(flow[i] != ' '){
		i++;
		if(i > len) return 0;
	}
	flow[i++] = '\0';
	man->surname = realloc(man->surname,i - nsur);
	memcpy(man->surname, &flow[nsur],i - nsur);
	if(i > len) return 0;
	while(flow[i] == ' '){
		i++;
		if(i > len) return 0;
	}
	ngro = i;
	while(flow[i] != ' '){
		i++;
		if(i > len) return 0;
	}
	flow[i++] = '\0';
	man->group = realloc(man->group,i - ngro);
	memcpy(man->group, &flow[ngro], i - ngro);
	if(i > len) return 0;
	while(flow[i] == ' '){
		i++;
		if(i > len) return 0;
	}
	nsco = i;
	while(i < len && flow[i] != ' '){
		i++;
		if(i > len) return 0;
	}
	flow[i++] = '\0';
	*score = realloc(*score,i - nsco);
	memcpy(*score, &flow[nsco], i - nsco);
	while(i < len){
		i++;
		if(i != ' ') return 0;
	}
	return 1;
}

int read_file(student* students){
	int n = 0;
	int k = 0;
	FILE* date;
	char* flow = (char*)malloc(100);
	char name[] = "data.txt";
	if((date = fopen(name,"r")) == NULL){
		printf("\033[1;31mCan't open file\033[0m\n");
		return 0;
	}
	//Reading
	int fl = 0;
	while(fscanf(date, "%100[^\n]\n", flow) > 0){
		student man;
		man.surname = NULL;
		man.group = NULL;
		man.mark = 0;
		char* score = NULL;
		k++;
		fl = check_flow(flow, &man, &score);

		if(!fl){
			printf("\033[1;31m%d student incorrect\033[0m\n", k);
			free(man.surname);
			free(man.group);
		}else if(checkSurname(&man) || checkGroup(&man) || checkScore(&score)){
			printf("\033[1;31m%d student incorrect\033[0m\n", k);
			free(man.surname);
			free(man.group);
		}else{
			string_to_float(&score,&man);
			students[n++] = man;
		}
		free(score);
	}
	free(flow);
	fclose(date);
	return n;
}

int randomer(student* students){
	int n = 0;
	int remainder = 0;
	int num_sur = 0;
	int fl = 0;
	char surnames[216][20] = {"Ivanov","Smirnov","Kuznetsov","Popov","Vasilev","Petrov","Sokolov","Mikhailov","Novikov","Fedorov","Morozov","Volkov","Alekseev","Lebedev","Semenov","Egorov","Pavlov","Kozlov","Stepanov","Nikolaev","Orlov","Andreev","Makarov","Nikitin","Zakharov","Zaitsev","Solovev","Borisov","IAkovlev","Grigorev","Romanov","Vorobev","Sergeev","Kuzmin","Frolov","Aleksandrov","Dmitriev","Korolev","Gusev","Kiselev","Maksimov","Poliakov","Sorokin","Vinogradov","Kovalev","Belov","Medvedev","Antonov","Tarasov","ZHukov","Baranov","Filippov","Komarov","Davydov","Beliaev","Gerasimov","Bogdanov","Osipov","Sidorov","Matveev","Titov","Markov","Mironov","Krylov","Kulikov","Karpov","Vlasov","Melnikov","Denisov","Gavrilov","Tikhonov","Kazakov","Afanasev","Danilov","Savelev","Timofeev","Fomin","CHernov","Abramov","Martynov","Efimov","Fedotov","SHCHerbakov","Nazarov","Kalinin","Isaev","CHernyshev","Bykov","Maslov","Rodionov","Konovalov","Lazarev","Voronin","Klimov","Filatov","Ponomarev","Golubev","Kudriavtsev","Prokhorov","Naumov","Potapov","ZHuravlev","Ovchinnikov","Trofimov","Leonov","Sobolev","Ermakov","Kolesnikov","Goncharov","Emelianov","Nikiforov","Grachev","Kotov","Grishin","Efremov","Arkhipov","Gromov","Kirillov","Malyshev","Panov","Moiseev","Rumiantsev","Akimov","Kondratev","Biriukov","Gorbunov","Anisimov","Eremin","Tikhomirov","Galkin","Lukianov","Mikheev","Skvortsov","IUdin","Belousov","Nesterov","Simonov","Prokofev","KHaritonov","Kniazev","TSvetkov","Levin","Mitrofanov","Voronov","Aksenov","Sofronov","Maltsev","Loginov","Gorshkov","Savin","Krasnov","Maiorov","Demidov","Eliseev","Rybakov","Safonov","Plotnikov","Demin","Fadeev","Molchanov","Ignatov","Litvinov","Ershov","Ushakov","Dementev","Riabov","Mukhin","Kalashnikov","Leontev","Lobanov","Kuzin","Korneev","Evdokimov","Borodin","Platonov","Nekrasov","Balashov","Bobrov","ZHdanov","Blinov","Ignatev","Korotkov","Muravev","Kriukov","Beliakov","Bogomolov","Drozdov","Lavrov","Petukhov","Larin","Nikulin","Serov","Terentev","Zotov","Ustinov","Fokin","Samoilov","Konstantinov","Sakharov","SHishkin","Samsonov","CHerkasov","CHistiakov","Nosov","Spiridonov","Karasev","Avdeev","Vorontsov","Zverev","Vladimirov","Seleznev","Nechaev","Kudriashov","Sedov","Firsov","Andrianov"};
	char groups[2] = {'B','S'};
	srand(time(NULL));
	n = 1 + rand()%10;
	remainder = rand()%2;
	for(int i = 0; i < n; i++){
		student man;
		man.surname = (char*)malloc(20);
		man.group = (char*)malloc(11);
		man.mark = 0;
		if(remainder)
			man.mark = 1 + rand()%900/100.0;
		else
			man.mark = 10 + rand()%900/10.0;
		num_sur = rand()%216;
		memcpy(man.surname,surnames[num_sur],20);
		man.group[0] = groups[rand()%2]; man.group[1] = (char)(48 + rand()%10); man.group[2] = (char)(48 + rand()%10); man.group[3] = '-'; man.group[4] = (char)(49 + rand()%10); man.group[5] = (char)(48 + rand()%10); man.group[6] = (char)(48 + rand()%10); man.group[7] = '\0';
		students[i] = man;
	}
	return n;
}

int comprasion1(student* students, int j){
	int k = 0;
	int fl = 0;
	if(strcmp(students[j].surname, students[j+1].surname) > 0){
		student tmp = students[j];
 		students[j] = students[j+1] ;
		students[j+1] = tmp; 
		return 1;
	}
	return 0;
	/*
	while(students[j].surname[k] == students[j+1].surname[k]){
		if(k = strlen(students[j].surname) - 1){
			fl = 1;
			break;
		}else if(k = strlen(students[j + 1].surname) - 1){
			fl = 2;
			break;
		}
		k++;
	}
	if(fl == 1){
		student tmp = students[j];
 		students[j] = students[j+1] ;
		students[j+1] = tmp;
		return 1;
	}else if(fl == 2){
		return 0;
	}
	if((int)students[j].surname[k] > (int)students[j+1].surname[k]) {
		student tmp = students[j];
 		students[j] = students[j+1] ;
		students[j+1] = tmp; 
		return 1;
	}*/
}

void sort_by_Bubble(student* students, int n){
	for(int i = 0 ; i < n - 1; i++){
		for(int j = 0 ; j < n - i - 1 ; j++){
			comprasion1(students, j);
        }
    }
}

void sort_by_Shaker(student* students, int n){
	int left = 0, right = n - 1;
	int flag = 1;
	while((left < right) && flag > 0){
		flag = 0;
		for(int j = left; j < right; j++){
			flag = comprasion1(students,j);
		}
		right--;
		for(int j = right; j >= left; j--){
			flag = comprasion1(students,j);
		}
		left++;
	}
}

void choose_date(student* students, int n){
	float min = 0;
	float max = 0;
	printf("\033[1;36mInput min mark: \033[0m");
	scanf("%f", &min);
	printf("\033[1;36mInput max mark: \033[0m");
	scanf("%f", &max);
	for(int i = 0; i < n; i++){
		if(students[i].mark >= min && students[i].mark <= max) 
			printf("%s %s %f\n", students[i].surname, students[i].group, students[i].mark);
	}

}

void writing(int write, FILE* list, char* name, student* students, int n){
	if(write){
		list = fopen(name,"w");
		for (int i = 0; i < n; ++i){
			fprintf(list, "%s %s %f\n", students[i].surname, students[i].group, students[i].mark);
		}
		fclose(list);
	}
}

void cleaning(student* students, int n){
	for (int i = 0; i < n; i++){
		free(students[i].surname);
		free(students[i].group);
	}
}

void invisible_for_reading(student* students, int n, int* write, int* sorted){
	if(n) cleaning(students,n);
	*write = 1;
	*sorted = 0;
}

void invisible_for_sorting(student* students, int n, int* write, int* sorted, int type){
	if(!n){
		printf("\033[1;31mNo date\033[0m\n");
		*write = 0;
	}else if(*sorted){
		printf("\033[1;31mThe file is already sorted\033[0m\n");
		*write = 0;
	}else{
		clock_t t = clock();
		if(type){
			sort_by_Bubble(students, n);
			printf("\033[1;32mSorting time by Bubble\033[0m %.3fs\n", (clock() - t)/1000.0);
		}else{
			sort_by_Shaker(students, n);
			printf("\033[1;32mSorting time by Shaker\033[0m %.3fs\n", (clock() - t)/1000.0);
		}
		*write = 1;
		*sorted = 1;
	}
}

void invisible_for_choosing(student* students, int n, int* write){
	if(!n) printf("\033[1;31mNo date\033[0m\n");
	else choose_date(students, n);
	*write = 0;
}

int main(int argc, char const *argv[]){
	int n = 0;
	int fl = 1;
	int write = 0;
	int sorted = 0;
	student students[100] = {NULL};
	FILE* list;
	char name[] = "students.txt";
	while(fl){
		//Number of menu
		printf("\n\033[1;33mCHOOSE OPTION:\033[0m\n");
		printf("\033[1;35m1) Reading data for processing from the input stream (from the keyboard).\n2) Reading data for processing from a text file.\n3) Random generation of data for processing.\n4) Sort by Bubble\n5) Sort by Shaker \n6) Choose date\n7) Exit\033[0m\n");
		char number = read_number();

		//MY MENU
		switch(number){

			//1) Reading data for processing from the input stream (from the keyboard).
			case '1':
				invisible_for_reading(students,n,&write,&sorted);
				n = reading(students);
			break;

			//2) Reading data for processing from a text file.
			case '2':
				invisible_for_reading(students,n,&write,&sorted);
				n = read_file(students);
			break;

			//3) Random generation of data for processing.
			case '3':
				invisible_for_reading(students,n,&write,&sorted);
				n = randomer(students);
			break;

			//4) Sort by Bubble
			case '4':
				invisible_for_sorting(students,n,&write,&sorted,1);
			break;

			//5) Sort by Shaker
			case '5':
				invisible_for_sorting(students,n,&write,&sorted,0);
			break;

			//6) Choose date
			case '6':
				invisible_for_choosing(students,n,&write);
			break;

			//7) Exit
			case '7':
				fl = 0;
			break;
		}

		writing(write, list, name, students, n);
	
	}

	cleaning(students, n);
	
	return 0;
}
