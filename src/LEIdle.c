#include "../includes/person.h"

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(){

    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);

    fill_hash(hash);

    gpointer *keys = g_hash_table_get_keys_as_array(hash, NULL);
    guint size = g_hash_table_size(hash);
    guint random_index = g_random_int_range(0, size);
    char *answer_key = keys[random_index];

    char guess[15];
    int i = 0;

    for(i; i<6; i++){

        printf("Guess: ");
        scanf("%s", guess);

        if(!g_hash_table_lookup(hash, guess)){
            printf("Could'nt find name, try again.\n");
            i--;
            continue;
        }

        int r = compare_person(guess, hash, answer_key);

        if(r) break;
    }

    if(i==6) printf("\nThe answer was: %s\nGet good Bozo!\n", answer_key);
    
    g_free(keys);
    g_hash_table_unref(hash);

    return 0;
}