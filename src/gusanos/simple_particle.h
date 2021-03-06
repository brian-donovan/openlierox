#ifndef VERMES_BLOOD_H
#define VERMES_BLOOD_H

#include "game/CGameObject.h"
#include "CVec.h"

class SimpleParticle : public CGameObject
{
public:
		
	SimpleParticle(Vec pos_ = Vec(0.f, 0.f), Vec spd_ = Vec(0.f, 0.f), CWormInputHandler* owner = NULL, int timeout_ = 0, float gravity_ = 0.f, int colour_ = 0, bool wupixel_ = false)
	: CGameObject(owner, pos_, spd_), timeout(timeout_), colour(colour_)
	, gravity(gravity_)
	, wupixel(wupixel_)	  
	//, gravity(int(gravity_ * 256.f))
	/*, posx(int(pos_.x * 256.f)), posy(int(pos_.y * 256.f))
	, spdx(int(spd_.x * 256.f)), spdy(int(spd_.y * 256.f))*/
	{}

	void draw(CViewport* viewport);
	void think();
		
	void* operator new(size_t count);
	
	void operator delete(void* block);
	
protected:
	
	int timeout;
	uint32_t colour;
	//int gravity;
	float gravity;
	bool wupixel;
/*
	int posx;
	int posy;
	int spdx;
	int spdy;*/
};


#endif  // VERMES_BLOOD_H
