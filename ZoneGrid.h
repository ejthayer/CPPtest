#pragma once

#include "PolyZone.h"
#include "GameModel.h"

class ZoneGrid {
protected:
  long gridx,gridz;
  float zonesize;

  PolyZone *zones;

public:
  ZoneGrid(void);
  ~ZoneGrid(void);
  void SetupGrid(GameModel *gmodel);
  void SetGridSize(long x,long z);
  void SetZoneSize(float zs);
  float GetZoneSize(void);
  void AddPoly(mod_vertice *vert1, mod_vertice *vert2, mod_vertice *vert3, long ind);
  PolyZone* GetZone(long xx,long zz);
  void Save(char *fname);
  void Load(char *fname);
  void Dump(void);
};
