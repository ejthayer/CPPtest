#include "dxstdafx.h"
#include "Frustum.h"

Frustum::Frustum(void) {
}

Frustum::~Frustum(void) {
}

// NOTE: The far plane has been commented out because I am not testing things
//       that are outside the far plane anyway so those are wasted clacs. So the
//       loops go to < 5, accept of course the functions that only use 3 planes. 

//--------------------------------------------------------------------------------------------
void Frustum::BuildFrustumPlanes(D3DXMATRIXA16 &ViewProj) {
  static D3DXVECTOR4 col0,col1,col2,col3;

  col0.Set(ViewProj._11, ViewProj._21, ViewProj._31, ViewProj._41);
  col1.Set(ViewProj._12, ViewProj._22, ViewProj._32, ViewProj._42);
  col2.Set(ViewProj._13, ViewProj._23, ViewProj._33, ViewProj._43);
  col3.Set(ViewProj._14, ViewProj._24, ViewProj._34, ViewProj._44);

	// Planes face inward.
	FrustumPlanes[0] = (D3DXPLANE)(col2);        // near
	FrustumPlanes[1] = (D3DXPLANE)(col3 + col0); // left
	FrustumPlanes[2] = (D3DXPLANE)(col3 - col0); // right
	FrustumPlanes[3] = (D3DXPLANE)(col3 - col1); // top
	FrustumPlanes[4] = (D3DXPLANE)(col3 + col1); // bottom
	//FrustumPlanes[5] = (D3DXPLANE)(col3 - col2); // far

	for(int i = 0; i < MAXPLANES; i++) 
    D3DXPlaneNormalize(&FrustumPlanes[i], &FrustumPlanes[i]);
}
 
//--------------------------------------------------------------------------------------------
// Builds only 3 planes, near, left, and right
//--------------------------------------------------------------------------------------------
void Frustum::BuildFrustumPlanes3(D3DXMATRIXA16 &ViewProj) {
  static D3DXVECTOR4 col0,col1,col2,col3;

  col0.Set(ViewProj._11, ViewProj._21, ViewProj._31, ViewProj._41);
  //col1.Set(ViewProj._12, ViewProj._22, ViewProj._32, ViewProj._42);
  col2.Set(ViewProj._13, ViewProj._23, ViewProj._33, ViewProj._43);
  col3.Set(ViewProj._14, ViewProj._24, ViewProj._34, ViewProj._44);

	// Planes face inward.
	FrustumPlanes[0] = (D3DXPLANE)(col2);        // near
	FrustumPlanes[1] = (D3DXPLANE)(col3 + col0); // left
	FrustumPlanes[2] = (D3DXPLANE)(col3 - col0); // right
	//FrustumPlanes[3] = (D3DXPLANE)(col3 - col1); // top
	//FrustumPlanes[4] = (D3DXPLANE)(col3 + col1); // bottom
	//FrustumPlanes[5] = (D3DXPLANE)(col3 - col2); // far

	for(int i = 0; i < 3; i++) 
    D3DXPlaneNormalize(&FrustumPlanes[i], &FrustumPlanes[i]);
}
 
//--------------------------------------------------------------------------------------------
bool Frustum::IsVisible(AABB &box) {
  static D3DXVECTOR3 Q;
  static long i;

  for ( i = 0 ; i < MAXPLANES ; ++i ) {

    if ( FrustumPlanes[i][0] >= 0.0f ) { Q[0] = box.maxPt[0];	} else { Q[0] = box.minPt[0];	}
    if ( FrustumPlanes[i][1] >= 0.0f ) { Q[1] = box.maxPt[1];	} else { Q[1] = box.minPt[1];	}
    if ( FrustumPlanes[i][2] >= 0.0f ) { Q[2] = box.maxPt[2];	} else { Q[2] = box.minPt[2];	}

    if( D3DXPlaneDotCoord(&FrustumPlanes[i], &Q) < 0.0f  ) return false;
  }
  return true;
}

//--------------------------------------------------------------------------------------------
bool Frustum::IsVisible3(AABB &box) {
  static D3DXVECTOR3 Q;
  static long i;

  for ( i = 0 ; i < 3 ; ++i ) {

    if ( FrustumPlanes[i][0] >= 0.0f ) { Q[0] = box.maxPt[0];	} else { Q[0] = box.minPt[0];	}
    if ( FrustumPlanes[i][1] >= 0.0f ) { Q[1] = box.maxPt[1];	} else { Q[1] = box.minPt[1];	}
    if ( FrustumPlanes[i][2] >= 0.0f ) { Q[2] = box.maxPt[2];	} else { Q[2] = box.minPt[2];	}

    if( D3DXPlaneDotCoord(&FrustumPlanes[i], &Q) < 0.0f  ) return false;
  }
  return true;
}

//--------------------------------------------------------------------------------------------
bool Frustum::IsVisible(float x,float y,float z,float rad) {
  static D3DXVECTOR3 Q;
  static long i;

  for ( i = 0 ; i < MAXPLANES ; ++i ) {

    if ( FrustumPlanes[i][0] >= 0.0f ) { Q.x = x+rad; } else { Q.x = x-rad; }
    if ( FrustumPlanes[i][1] >= 0.0f ) { Q.y = y+rad; } else { Q.y = y-rad;	}
    if ( FrustumPlanes[i][2] >= 0.0f ) { Q.z = z+rad; } else { Q.z = z-rad; }

    if( D3DXPlaneDotCoord(&FrustumPlanes[i], &Q) < 0.0f  ) return false;
  }
  return true;
}

//--------------------------------------------------------------------------------------------
bool Frustum::IsVisible3(float x,float y,float z,float rad) {
  static D3DXVECTOR3 Q;
  static long i;

  for ( i = 0 ; i < 3 ; ++i ) {

    if ( FrustumPlanes[i][0] >= 0.0f ) { Q.x = x+rad; } else { Q.x = x-rad; }
    if ( FrustumPlanes[i][1] >= 0.0f ) { Q.y = y+rad; } else { Q.y = y-rad;	}
    if ( FrustumPlanes[i][2] >= 0.0f ) { Q.z = z+rad; } else { Q.z = z-rad; }

    if( D3DXPlaneDotCoord(&FrustumPlanes[i], &Q) < 0.0f  ) return false;
  }
  return true;
}

//--------------------------------------------------------------------------------------------
bool Frustum::IsVisible(D3DXVECTOR3 &vec,float rad) {
  static D3DXVECTOR3 Q;
  static long i;

  for ( i = 0 ; i < MAXPLANES ; ++i ) {

    if ( FrustumPlanes[i][0] >= 0.0f ) { Q.x = vec.x+rad; } else { Q.x = vec.x-rad; }
    if ( FrustumPlanes[i][1] >= 0.0f ) { Q.y = vec.y+rad; } else { Q.y = vec.y-rad;	}
    if ( FrustumPlanes[i][2] >= 0.0f ) { Q.z = vec.z+rad; } else { Q.z = vec.z-rad; }

    if( D3DXPlaneDotCoord(&FrustumPlanes[i], &Q) < 0.0f  ) return false;
  }
  return true;
}

//--------------------------------------------------------------------------------------------
bool Frustum::IsVisible(D3DXVECTOR3 &vec) {
  static long i;

  for ( i = 0 ; i < MAXPLANES ; ++i ) {
    if( D3DXPlaneDotCoord(&FrustumPlanes[i], &vec) < 0.0f  ) return false;
  }
  return true;
}
