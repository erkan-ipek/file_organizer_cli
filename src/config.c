#include "config.h"
#include <string.h>

int parse_config(const char *config_path, struct Rule *rules) {
    int rule_count = 0;

    // open txt file
    FILE *fp = fopen(config_path, "r");
    if (fp == NULL) {
        printf("Fehler: config.txt nicht gefunden\n");
        return 0;
    }

    char line [512]; // temp cache (512 Bytes), fgets writes the lines into it, printf outputs it
    while (fgets(line, sizeof(line), fp) != NULL) {
        //printf("%s", line);
        if (strncmp(line, "[rule]", strlen("[rule]")) == 0) rule_count++;

        if (strncmp(line, "pattern", strlen("pattern")) == 0) {
            char *field_value = strchr(line, '=') + 2; //+2 to skip '='
            strncpy(rules[rule_count - 1].pattern, field_value, 255);
            rules[rule_count - 1].pattern[strcspn(rules[rule_count - 1].pattern, "\n")] = '\0';
        }
            

        if (strncmp(line, "destination", strlen("destination")) == 0) {
            char *field_value = strchr(line, '=') + 2; //+2 to skip '='
            strncpy(rules[rule_count - 1].dest_dir, field_value, 255);
            rules[rule_count - 1].dest_dir[strcspn(rules[rule_count - 1].dest_dir, "\n")] = '\0';
        }
    }

     //close txt file
    fclose(fp);

    return rule_count;
}

