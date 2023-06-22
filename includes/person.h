#ifndef PERSON_H
#define PERSON_H

#include <glib.h>

typedef struct person Person;

/*
char* get_name(GHashTable *hash, char* name);

int get_num(GHashTable *hash, int num);

char* get_year(GHashTable *hash, char* year);

int get_gender(GHashTable *hash, int gender);
*/

void fill_hash(GHashTable *hash);

int compare_person(char* name, GHashTable *hash, char *answer_key);


#endif 