#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float delta) override;

private:

	void drawLines();
	void drawPattern(float radius1, float radius2, float radius3, const cocos2d::Color3B &color);
	void onTouchBegining(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event);
	void onTouchMoving(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event);
	void onTouchEnding(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event);

private:

	cocos2d::RenderTexture *_renderTex;
	cocos2d::DrawNode *_drawNode;
	float _theta;

	cocos2d::Node *_circle;
	cocos2d::Node *_mark;
};

#endif // __HELLOWORLD_SCENE_H__
