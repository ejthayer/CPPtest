#pragma once

#define MAXPLANES 5

struct AABB {
  D3DXVECTOR3 minPt;
  D3DXVECTOR3 maxPt;

  void Clear() {
    minPt.x = 0;
    minPt.y = 0;
    minPt.z = 0;
    maxPt.x = 0;
    maxPt.y = 0;
    maxPt.z = 0;
  }
};

class Frustum {
public:

  D3DXPLANE FrustumPlanes[MAXPLANES];

  Frustum(void);
  ~Frustum(void);
  void BuildFrustumPlanes(D3DXMATRIXA16 &ViewProj);
  void BuildFrustumPlanes3(D3DXMATRIXA16 &ViewProj);
  bool IsVisible(AABB &box);
  bool IsVisible3(AABB &box);
  bool IsVisible(float x,float y,float z,float rad);
  bool IsVisible3(float x,float y,float z,float rad);
  bool IsVisible(D3DXVECTOR3 &vec,float rad);
  bool IsVisible(D3DXVECTOR3 &vec);
};
