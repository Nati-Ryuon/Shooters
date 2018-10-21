#pragma once
#include <memory>
/*
class SceneBase {
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	bool isFinished() {
		return false;
	}
	std::unique_ptr<SceneBase> getNextScene() {
		return next.get;
	}
	std::unique_ptr<SceneBase> getReturnScene() {
		return prev.get;
	}
	std::unique_ptr<SceneBase> next;
	std::unique_ptr<SceneBase> prev;
};
*/

class SceneBase {
protected:
	bool returnScene;
	bool saveScene;
	std::unique_ptr<SceneBase> nextScene;
public:
	SceneBase() : returnScene(false), nextScene(nullptr), saveScene(false) {}
	bool isFinished() const;
	bool getReturnScene() const;
	bool getSaveScene() const;
	bool nextSceneNullCheck() const { return nextScene != nullptr; }
	std::unique_ptr<SceneBase> getNextScene();
	virtual void draw() = 0;
	virtual void update() = 0;
};