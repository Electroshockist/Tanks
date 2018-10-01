#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"
#include "Vector.h"
#include "Body.h"

class Scene {
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(SDL_Event& event) = 0;
};

#endif
