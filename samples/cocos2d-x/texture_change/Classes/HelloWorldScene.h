#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SSPlayer/SS5Player.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	//アップデート
	virtual void update(float delta);
	
	//ユーザーデータコールバック
	void userDataCallback(ss::Player* player, const ss::UserData* data);

	//アニメーション終了コールバック
	void playEndCallback(ss::Player* player);


    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	//SS5プレイヤー
	ss::Player *ssplayer;

	//情報表示用ラベル
	cocos2d::Label *label;

	//テクスチャ差し替え用ポインタ
	cocos2d::Texture2D* tex1;
	cocos2d::Texture2D* tex2;
};

#endif // __HELLOWORLD_SCENE_H__
