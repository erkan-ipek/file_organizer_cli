#include <stdio.h>
#include <string.h>

#define MAX_RULES 64

struct Rules{
    char pattern [256];
    char dest_dir [256];
};

int main(){
    struct Rules rules[MAX_RULES];
    int rule_count = 0;
    // open txt file
    FILE *fp = fopen("config.txt", "r");
    
    // read line for line
    char buffer [512]; // temp cache (512 Bytes), fgets writes the lines into it, printf outputs it
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        //printf("%s", buffer);
        if (strncmp(buffer, "[rule]", strlen("[rule]")) == 0) rule_count++;

        if (strncmp(buffer, "pattern", strlen("pattern")) == 0) {
            char *value = strchr(buffer, '=') + 2; //+2 to skip '='
            strncpy(rules[rule_count - 1].pattern, value, 255);
        }
            

        if (strncmp(buffer, "destination", strlen("destination")) == 0) {
            char *value = strchr(buffer, '=') + 2; //+2 to skip '='
            strncpy(rules[rule_count - 1].dest_dir, value, 255);
        }
    }

    //close txt file
    fclose(fp);

    for (int i = 0; i < rule_count; i++) {
        printf("Regel %d: pattern=%s dest=%s\n", i+1, rules[i].pattern, rules[i].dest_dir);
    }

    return 0;
}