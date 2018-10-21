#include "SceneBase.h"

bool SceneBase::isFinished() const
{
	return nextScene != nullptr || returnScene;
}

bool SceneBase::getReturnScene() const
{
	return returnScene;
}

bool SceneBase::getSaveScene() const
{
	return saveScene;
}

std::unique_ptr<SceneBase> SceneBase::getNextScene() {
	return std::move(nextScene);
}