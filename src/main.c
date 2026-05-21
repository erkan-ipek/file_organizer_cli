#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <fnmatch.h>

#define MAX_RULES 64

struct Rules{
    char pattern [256];
    char dest_dir [256];
};

int main(){
    int dry_run_flag = 1; // 1 = just display, 0 = move file

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
            rules[rule_count - 1].pattern[strcspn(rules[rule_count - 1].pattern, "\n")] = '\0';
        }
            

        if (strncmp(buffer, "destination", strlen("destination")) == 0) {
            char *value = strchr(buffer, '=') + 2; //+2 to skip '='
            strncpy(rules[rule_count - 1].dest_dir, value, 255);
            rules[rule_count - 1].dest_dir[strcspn(rules[rule_count - 1].dest_dir, "\n")] = '\0';
        }
    }

    //close txt file
    fclose(fp);

    for (int i = 0; i < rule_count; i++) {
        printf("Regel %d: pattern=%s dest=%s\n", i+1, rules[i].pattern, rules[i].dest_dir);
    }

    char *home_dir = getenv("HOME");

    char downloads_path [512];

    snprintf(downloads_path, sizeof(downloads_path), "%s/Downloads", home_dir);

    DIR *dir = opendir(downloads_path);

    if (dir == NULL) {
        printf("Error opening directory...");
        return 1;
    }

    struct dirent *entry;

    while((entry = readdir(dir)) != NULL){
        //printf("%s\n", entry->d_name);

        for (int i = 0; i < rule_count; i++) {
            if (fnmatch(rules[i].pattern, entry->d_name, 0) == 0) {
                //printf("Match: %s -> %s\n", entry->d_name, rules[i].dest_dir);
                if(dry_run_flag) {
                    printf("[DRY-RUN] Würde verschieben %s -> %s\n", entry->d_name, rules[i].dest_dir);
                } else {

                }
            }
        }
    }

    closedir(dir);

    return 0;
}