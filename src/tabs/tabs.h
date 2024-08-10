#ifndef TABS_H
#define TABS_H

// TODO: Alloc dynamically or at least move to a settings file
#define MAX_TABS 1

void tabs_init(void);
void tabs_show(void);
void tabs_hide(void);
void tabs_free(void);

#endif // TABS_H
