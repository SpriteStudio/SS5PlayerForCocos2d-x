#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SSPlayer/SS5Player.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	//�A�b�v�f�[�g
	virtual void update(float delta);

	//���[�U�[�f�[�^�R�[���o�b�N
	void userDataCallback(ss::Player* player, const ss::UserData* data);

	//�A�j���[�V�����I���R�[���o�b�N
	void playEndCallback(ss::Player* player);

private:
	//SS5�v���C���[
	ss::Player *ssplayer;

	//���\���p���x��
	cocos2d::Label *label;
};

#endif // __HELLOWORLD_SCENE_H__
