#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "config.h"

int match_and_move(struct Rule *rules, int rule_count, int dry_run_flag);

#endif