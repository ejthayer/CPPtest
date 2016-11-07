
#include "BaseSounds.h"

Base_Sounds BaseSounds[] = {
  { 0 , "button"       }, // 
  { 1 , "cast"         }, // 
  { 2 , "clang"        }, // 
  { 3 , "ffft"         }, // 
  { 4 , "step"         }, // 
  { 5 , "guitar"       }, // 
  { 6 , "swish"        }, // 
  { 7 , "hitf"         }, // 
  { 8 , "growl1"       }, // 
  { 9 , "bow"          }, // 
  { 10 , "spell4"       }, // 
  { 11 , "SpExp"        }, // 
  { 12 , "droplet"      }, // 
  { 13 , "angel"        }, // 
  { 14 , "scream"       }, // 
  { 15 , "mgicwind"     }, // 
  { 16 , "chantspll"    }, // 
  { 17 , "tranquil"     }, // 
  { 18 , "grunt"        }, // 
  { 19 , "Uwater"       }, // 
  //{ 20, "action2"    }, // music sound -- DONT LOAD HERE!
  { 21 , "suprspell"    }, // 
  { 22 , "twinkle"      }, // 
  { 23 , "bugdie"       }, // 
  { 24 , "bugatt"       }, // 
  { 25 , "fem1hit"      }, // 
  { 26 , "fem1att1"     }, // 
  { 27 , "fem1att2"     }, // 
  { 28 , "fem1die1"     }, // 
  { 29 , "fem1die2"     }, // 
  { 30 , "fem2hit1"     }, // 
  { 31 , "fem2hit2"     }, // 
  { 32 , "fem2att1"     }, // 
  { 33 , "fem2att2"     }, // 
  { 34 , "fem2die1"     }, // 
  { 35 , "mal1att1"     }, // 
  { 36 , "mal1hit1"     }, // 
  { 37 , "mal1hit2"     }, // 
  { 38 , "mal1die1"     }, // 
  { 39 , "mal1die2"     }, // 
  { 40 , "night"        }, // 
  { 41 , "hoots"        }, // 
  { 42 , "evilspl"      }, // 
  { 43 , "skatt1"       }, // 
  { 44 , "skatt2"       }, // 
  { 45 , "skdie"        }, // 
  { 46 , "door1"        }, // 
  { 47 , "door2"        }, // 
  { 48 , "attwind"      }, // 
  { 49 , "spiderd"      }, // 
  { 50 , "ogrea"        }, // 
  { 51 , "ogreh"        }, // 
  { 52 , "ogred"        }, // 
  { 53 , "gurgle"       }, // 
  { 54 , "cvwind"       }, // 
  { 55 , "spell3"       }, // 
  { 56 , "wolfa"        }, // 
  { 57 , "wolfd"        }, // 
  { 58 , "glass"        }, // 
  { 59 , "flap"         }, // 
  { 60 , "dragdie"      }, // 
  { 61 , "draghit"      }, // 
  { 62 , "shortzap"     }, // 
  { 63 , "summon"       }, // 
  { 64 , "mind"         }, // 
  { 65 , "chickcluk"    }, // 
  { 66 , "chicken"      }, // 
  { 67 , "bigheal"      }, // 
  { 68 , "DivTueri"     }, // 
  { 69 , "cycwind"      }, // 
  { 70 , "golstep"      }, // 
  { 71 , "golswing"     }, // 
  { 72 , "beam"         }, // 
  { 73 , "redtail"      }, // 
  { 74 , "rot"          }, // 
  { 75 , "switch"       }, // 
  { 76 , "sclang"       }, // 
  { 77 , "hitwood"      }, // 
  { 78 , "bomb"         }, // 
  { 79 , "cast2"        }, // 
  { 80 , "wfw"          }, // 
  { 81 , "electric"     }, // 
  { 82 , "dstar"        }, // 
  { 83 , "impgrr"       }, // 
  { 84 , "impdie"       }, // 
  { 85 , "imphit"       }, // 
  { 86 , "volgrunt"     }, // 
  { 87 , "volgrunt2"    }, // 
  { 88 , "voldie"       }, // 
  { 89 , "demongnt"     }, // 
  { 90 , "demonhit"     }, // 
  { 91 , "demondie"     }, // 
  { 92 , "thunder"      }, // 
  { 93 , "rain"         }, // 
  { 94 , "shrine"       }, // 
  { 95 , "flameup"      }, // 
  { 96 , "orcat"        }, // 
  { 97 , "orcat2"       }, // 
  { 98 , "orcdie"       }, // 
  { 99 , "beam2"        }, // 
  { 100 , "beam3"        }, // 
  { 101 , "exp6"         }, // 
  { 102 , "tap"          }, // 
  { 103 , "powerup3"     }, // 
  { 999 , ""             }, // need a blank terminator
};

long GetBaseSoundCount(void) {
  static long bscount = 0;
  if ( bscount ) return bscount;
  int a = 0;
  while(true) {
    if ( strlen(BaseSounds[a].name) == 0 ) break;
    a++;
  }
  bscount = a + 1;
  return bscount;
}

long FindBaseSound(char *name) {
  static char findname[40], soundname[40];

  strlcpy(findname,name,40);
  strupr(findname);

  long c = GetBaseSoundCount();
  for ( long a = 0 ; a < c ; a++ ) {
    strcpy(soundname,BaseSounds[a].name);
    strupr(soundname);
    if ( strcmp(findname,soundname) == 0 ) return a;
  }
  return -1;
}
