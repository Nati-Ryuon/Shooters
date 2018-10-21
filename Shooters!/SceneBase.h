#pragma once
#include<memory>

class SceneBase {
protected:
	bool returnScene;
	bool saveScene;
	std::unique_ptr<SceneBase> nextScene;
public:
	SceneBase() : returnScene(false), nextScene(nullptr), saveScene(false) {}
	bool IsFinished() const;
	bool getReturnScene() const;
	bool getSaveScene() const;
	bool nextSceneNullCheck() const { return nextScene != nullptr; }
	std::unique_ptr<SceneBase> getNextScene();
	virtual void draw() = 0;
	virtual void update() = 0;
};
