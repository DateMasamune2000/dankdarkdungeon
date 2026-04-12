#ifndef _UTIL_H
#define _UTIL_H

struct level {
	char data[24][80];
	bool seen[24][80];
};

void generate(struct level *l);
void display(const struct level *l);

#endif
