#include "../includes/person.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct person{

    char name[15];
    int num;
    int year;
    int gender; // 1 for male 0 for female
} Person;


Person * create_person(char* line){

    Person *p = malloc(sizeof(Person)); 

    char* token;
    int i = 0;

    while((token = strsep(&line, ";"))!=NULL){
        
        switch(i++){

            case 0:
                strcpy(p->name, token);
                //printf("%s\n", p->name);
                break;
            
            case 1:
                p->num = atoi(token);
                //printf("%d\n", p->num);
                break;
            
            case 2: 
                p->year = atoi(token);
                //printf("%d\n", p->year);
                break;
            
            case 3:
                p->gender = atoi(token);
                //printf("%d\n", p->gender);
                break;
        }
    } 

    return p;
}



void insert_person(Person *p, GHashTable *hash){

    g_hash_table_insert(hash, p->name, p);
}


char* get_name(GHashTable *hash, char* name){

    Person *p = g_hash_table_lookup(hash, name);
    printf("%s\n", p->name);
    return p->name;
}

/*
int get_num(GHashTable *hash, char* name){

    Person *p = g_hash_table_lookup(hash, name);
    return p->num;
}

int get_year(GHashTable *hash, char* name){

    Person *p = g_hash_table_lookup(hash, name);
    return p->year;
}

int get_gender(GHashTable *hash, char* name){

    Person *p = g_hash_table_lookup(hash, name);
    return p->gender;
}
*/


void fill_hash(GHashTable *hash){

    FILE *f;
    char open[50];

    getcwd(open, sizeof(open));
    f = fopen(strcat(open, "/lei.csv"), "r");
    if(!f){
        perror("Error!");
        return;
    }

    char* line = NULL;
    size_t len = 0;

    while(getline(&line, &len, f)>0){
        
        line[strcspn(line, "\n")] = 0;
        Person *p = create_person(line);
        if(p != NULL) insert_person(p, hash); 
    }   

    fclose(f);
}

int compare_person(char* name, GHashTable *hash, char *answer_key){

    Person *guess = g_hash_table_lookup(hash, name);
    Person *answer = g_hash_table_lookup(hash, answer_key);

    //printf("%s", name);
    //printf("%s\n", get_name(hash, answer_key));

    if(!strcmp(guess->name, answer->name)){
        printf("Congrats no skill issue found!\n");
        return 1;
    }

    else{

        printf("%s: ", guess->name);

        if(guess->num < answer->num) printf("Number: %d (+) ", guess->num);
        else if(guess->num > answer->num) printf("Number: %d (-) ", guess->num);
        else printf("Number: %d (!) ", guess->num);

        if(guess->year < answer->year) printf("Year: %d (+) ", guess->year);
        else if(guess->year > answer->year) printf("Year: %d (-) ", guess->year);
        else printf("Year: %d (!) ", guess->year);

        if(guess->gender != answer->gender) printf("Gender: (X)\n");
        else printf("Gender: (!)\n");

        return 0;
    }
}