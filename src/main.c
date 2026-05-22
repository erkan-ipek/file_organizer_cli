#include "config.h"
#include "organizer.h"

int main(){

    int dry_run_flag = 0; // 0 -> move, 1 -> only display what would change

    struct Rule rules[MAX_RULES];

    int rule_count = parse_config("config.txt", rules);
    match_and_move(rules, rule_count, dry_run_flag);

    return 0;
}