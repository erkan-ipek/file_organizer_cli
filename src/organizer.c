#include "organizer.h"
#include "config.h"
#include <dirent.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <string.h>
#include <stdio.h>

int match_and_move(struct Rule *rules, int rule_count, int dry_run_flag){
    char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        printf("Fehler: HOME-Umgebungsvariable nicht gesetzt\n");
        return 1;
    }

    char downloads_path [512];

    snprintf(downloads_path, sizeof(downloads_path), "%s/Downloads", home_dir);

    DIR *dir = opendir(downloads_path);

    if (dir == NULL) {
        printf("Fehler: Verzeichnis konnte nicht geöffnet werden\n");
        return 0;
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
                    char old_path[512];
                    snprintf(old_path, sizeof(old_path), "%s/%s", downloads_path, entry->d_name);

                    char new_path[512];
                    snprintf(new_path, sizeof(new_path), "%s%s/%s", home_dir, rules[i].dest_dir + 1, entry->d_name);

                    if (rename(old_path, new_path) == 0) {
                        printf("Verschoben: %s -> %s\n", entry->d_name, rules[i].dest_dir);
                    } else {
                        perror("Fehler beim verschieben");
                        return 1;
                    }
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
