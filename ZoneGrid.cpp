#include "dxstdafx.h"
#include "ZoneGrid.h"

#define dbline(val) {FILE *outfile; outfile = fopen("mydebug.txt","a+b"); fputs(val,outfile); fclose(outfile); }

ZoneGrid::ZoneGrid(void) {
  zones = 0;
  zonesize = 500;
}

ZoneGrid::~ZoneGrid(void) {
}

void ZoneGrid::SetupGrid(GameModel *gmodel) {
  static long pgcc,pgc,a,v1,v2,v3;
  static float maxx,maxz;

  // find the models max x and z
  a = 0;
  maxx = 0;
  maxz = 0;

  for ( pgcc = 0 ; pgcc < gmodel->pgcountscount ; pgcc++ ) {
    for ( pgc = 0 ; pgc < gmodel->pgcounts[pgcc] ; pgc++ ) {

      v1 = gmodel->dipvi[gmodel->mpolys[a].v1].originalvert;
      if ( gmodel->mverts[v1].x > maxx ) maxx = gmodel->mverts[v1].x;
      if ( gmodel->mverts[v1].z > maxz ) maxz = gmodel->mverts[v1].z;

      v2 = gmodel->dipvi[gmodel->mpolys[a].v2].originalvert;
      if ( gmodel->mverts[v2].x > maxx ) maxx = gmodel->mverts[v2].x;
      if ( gmodel->mverts[v2].z > maxz ) maxz = gmodel->mverts[v2].z;

      v3 = gmodel->dipvi[gmodel->mpolys[a].v3].originalvert;
      if ( gmodel->mverts[v3].x > maxx ) maxx = gmodel->mverts[v3].x;
      if ( gmodel->mverts[v3].z > maxz ) maxz = gmodel->mverts[v3].z;

      a++;
    }
  }

  //debugline("Max XZ %f %f \n",maxx,maxz);

  // set the grid size based on the maxx and maxz (+1 on each for partial section)
  SetGridSize(maxx / zonesize + 1 , maxz / zonesize + 1);

  // create the grid
  a = 0;
  for ( pgcc = 0 ; pgcc < gmodel->pgcountscount ; pgcc++ ) {
    for ( pgc = 0 ; pgc < gmodel->pgcounts[pgcc] ; pgc++ ) {

      v1 = gmodel->dipvi[gmodel->mpolys[a].v1].originalvert;
      v2 = gmodel->dipvi[gmodel->mpolys[a].v2].originalvert;
      v3 = gmodel->dipvi[gmodel->mpolys[a].v3].originalvert;

      AddPoly( &gmodel->mverts[v1] , &gmodel->mverts[v2] , &gmodel->mverts[v3] , a );

      a++;
    }
  }

}

void ZoneGrid::SetGridSize( long x , long z ) {
  if ( zones ) delete [] zones;
  gridx = x;
  gridz = z;
  zones = new PolyZone[gridx * gridz];
  //debugline("ZoneGrid %d x %d == %d \n",gridx,gridz,gridx*gridz);
}

void ZoneGrid::SetZoneSize(float zs) {
  zonesize = zs;
}

float ZoneGrid::GetZoneSize() {
  return zonesize;
}

void ZoneGrid::AddPoly(mod_vertice *vert1, mod_vertice *vert2, mod_vertice *vert3, long ind) {
  static long x1,z1,x2,z2;
  static long xx,zz;
  static float minx,maxx,minz,maxz;

  minx = 9999999;
  minz = 9999999;
  maxx = -9999999;
  maxz = -9999999;

  if ( vert1->x > maxx ) maxx = vert1->x;
  if ( vert2->x > maxx ) maxx = vert2->x;
  if ( vert3->x > maxx ) maxx = vert3->x;

  if ( vert1->x < minx ) minx = vert1->x;
  if ( vert2->x < minx ) minx = vert2->x;
  if ( vert3->x < minx ) minx = vert3->x;

  if ( vert1->z > maxz ) maxz = vert1->z;
  if ( vert2->z > maxz ) maxz = vert2->z;
  if ( vert3->z > maxz ) maxz = vert3->z;

  if ( vert1->z < minz ) minz = vert1->z;
  if ( vert2->z < minz ) minz = vert2->z;
  if ( vert3->z < minz ) minz = vert3->z;

  x1 = minx / zonesize;
  z1 = minz / zonesize;
  x2 = maxx / zonesize;
  z2 = maxz / zonesize;

  for ( xx = x1 ; xx <= x2 ; xx++ ) {
    for ( zz = z1 ; zz <= z2 ; zz++ ) {
      if ( xx < 0 || xx >= gridx || zz < 0 || zz >= gridz ) continue;
      zones[xx + zz*gridx].Add(ind);
    }
  }

}

PolyZone* ZoneGrid::GetZone(long xx, long zz) {
  if ( xx < 0 || xx >= gridx || zz < 0 || zz >= gridz ) return &zones[0];
  return &zones[xx + zz*gridx];
}

void ZoneGrid::Save(char *fname) {
  FILE *stream;
  long x,y;

  stream = fopen(fname,"wb");

  if ( !stream ) {
    dbline("Could not create file ");
    dbline(fname);
    dbline("\n");
    return;
  }

  fwrite(&gridx,sizeof(long),1,stream);
  fwrite(&gridz,sizeof(long),1,stream);
  fwrite(&zonesize,sizeof(float),1,stream);

  for ( x = 0 ; x < gridx ; x++ ) {
    for ( y = 0 ; y < gridz ; y++ ) {
      GetZone(x,y)->Save(stream);
    }
  }

  fclose(stream);
}

void ZoneGrid::Load(char *fname) {
  FILE *stream;
  long x,y;

  stream = fopen(fname,"rb");

  if ( !stream ) {
    dbline("Could not open file ");
    dbline(fname);
    dbline("\n");
    return;
  }
  
  fread(&gridx,sizeof(long),1,stream);
  fread(&gridz,sizeof(long),1,stream);
  fread(&zonesize,sizeof(float),1,stream);

  SetGridSize(gridx,gridz);

  for ( x = 0 ; x < gridx ; x++ ) {
    for ( y = 0 ; y < gridz ; y++ ) {
      GetZone(x,y)->Load(stream);
    }
  }

  fclose(stream);
}

void ZoneGrid::Dump() {
  long a,b,totalindexedpolys;
  char text[80];

  dbline("\n***** Zone Grid Dump *****\n");
  sprintf(text,"Zone Grid Size %d x %d ZoneSize %f \n",gridx,gridz,zonesize);
  dbline(text);

  totalindexedpolys = 0;
  for ( a = 0 ; a < gridx ; a++ ) {
    for ( b = 0 ; b < gridz ; b++ ) {
      sprintf(text,"Zone %d %d count %d \n",a,b,GetZone(a,b)->count); dbline(text);
      totalindexedpolys += GetZone(a,b)->count;
      //GetZone(a,b)->Dump();
    }
  }

  sprintf(text,"Total indexed polys %d \n",totalindexedpolys);
  dbline(text);

  dbline("\n***** END Zone Grid Dump *****\n");
}