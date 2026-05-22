#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

#define MAX_RULES 64


struct Rule{
    char pattern [256];
    char dest_dir [256];
};

int parse_config(const char *config_path, struct Rule *rules);

#endif