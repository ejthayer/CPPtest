#pragma once

#include <string.h>
#include "StrUtil.h"

struct Base_Sounds {
  long slot;
  char name[40];
};
extern Base_Sounds BaseSounds[];

long GetBaseSoundCount(void);
long FindBaseSound(char *name);
