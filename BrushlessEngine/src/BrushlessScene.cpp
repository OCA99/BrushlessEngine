#include "BrushlessScene.h"
#include "GameObject.h"

BrushlessScene::BrushlessScene()
{
}

BrushlessScene::~BrushlessScene()
{
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}
