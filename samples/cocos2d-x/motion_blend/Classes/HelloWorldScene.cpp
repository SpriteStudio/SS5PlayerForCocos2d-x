#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    

	/**********************************************************************************

	SS�A�j���\���̃T���v���R�[�h
	Visual Studio Express 2013 for Windows Desktop�œ�����m�F���Ă��܂��B
	ssbp��png������΍Đ����鎖���ł��܂����AResources�t�H���_��sspj���܂܂�Ă��܂��B

	**********************************************************************************/
	//--------------------------------------------------------------------------------
	//SS5.5���瓋�ڂ��ꂽ�G�t�F�N�g�@�\�̍œK�����s��SS5Manager�N���X���ǉ�����܂����B
	//�v���C���[�����L����G�t�F�N�g�o�b�t�@���쐬���܂��B
	//�o�b�t�@�͏풓����܂��̂ŃQ�[���N��������1�x�s���Ă��������B
	auto ss5man = ss::SS5Manager::getInstance();
	ss5man->createEffectBuffer(1024);			//�G�t�F�N�g�p�o�b�t�@�̍쐬
	//--------------------------------------------------------------------------------

	//���\�[�X�}�l�[�W���̍쐬
	auto resman = ss::ResourceManager::getInstance();
	//�v���C���[�̍쐬
	ssplayer = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	resman->addData("character_template_comipo/character_template1.ssbp");
	//�v���C���[�Ƀ��\�[�X�����蓖��
	ssplayer->setData("character_template1");						// ssbp�t�@�C�����i�g���q�s�v�j
	//�A�j���[�V�����̍Đ�
	ssplayer->play("character_template_3head/stance");				// �A�j���[�V�����̎w��(ssae��/�A�j���[�V������)

	//�A�j���[�V�����̕\���ʒu��ݒ�
	ssplayer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//�X�P�[���̐ݒ�
	ssplayer->setScale(0.5f, 0.5f);


	//���[�U�[�f�[�^�R�[���o�b�N��ݒ�
	ssplayer->setUserDataCallback(CC_CALLBACK_2(HelloWorld::userDataCallback, this));

	//�A�j���[�V�����I���R�[���o�b�N��ݒ�
	ssplayer->setPlayEndCallback(CC_CALLBACK_1(HelloWorld::playEndCallback, this));

	//�v���C���[���Q�[���V�[���ɒǉ�
	this->addChild(ssplayer, 10);


	//updete�̍쐬
	this->scheduleUpdate();


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



//���C�����[�v
int cnt = 0;
bool type = false;
void HelloWorld::update(float delta)
{
	int max_frame = ssplayer->getMaxFrame();
	int now_frame = ssplayer->getFrameNo();
	{
		cnt++;
		if ( (cnt % 180) == 0 )
		{
			//���[�V�����u�����h�t���A�j���[�V�����Đ�
			//���[�V�����u�����h���s�����߂ɂ͏���������܂��B
			//SS5Player.h��motionBlendPlay�֐��̃R�����g���Q�Ƃ��Ă��������B
			if (type == false)
			{
				type = true;
				ssplayer->motionBlendPlay("character_template_3head/dead1", 1);				 // �A�j���[�V�����̎w��(ssae��/�A�j���[�V������)
			}
			else
			{
				type = false;
				ssplayer->motionBlendPlay("character_template_3head/run", 0);				 // �A�j���[�V�����̎w��(ssae��/�A�j���[�V������)
			}
		}
	}
	{
		auto str = String::createWithFormat("max:%d, fream:%d", max_frame, now_frame);
		label->setString(str->getCString());
	}
}

//���[�U�[�f�[�^�R�[���o�b�N
void HelloWorld::userDataCallback(ss::Player* player, const ss::UserData* data)
{
	//�Đ������t���[���Ƀ��[�U�[�f�[�^���ݒ肳��Ă���ꍇ�Ăяo����܂��B
	//�v���C���[�𔻒肷��ꍇ�A�Q�[�����ŊǗ����Ă���ss::Player�̃A�h���X�Ɣ�r���Ĕ��肵�Ă��������B
/*
	//�R�[���o�b�N���Ńp�[�c�̃X�e�[�^�X���擾�������ꍇ�́A���̎��_�ł̓A�j�����X�V����Ă��Ȃ����߁A
	//getPartState�@�Ɂ@data->frameNo�@�Ńt���[�������w�肵�Ď擾���Ă��������B
	ss::ResluteState result;
	//�Đ����Ă��郂�[�V�����Ɋ܂܂��p�[�c���ucollision�v�̃X�e�[�^�X���擾���܂��B
	ssplayer->getPartState(result, "collision", data->frameNo);
*/	

}

//�A�j���[�V�����I���R�[���o�b�N
void HelloWorld::playEndCallback(ss::Player* player)
{
	//�Đ������A�j���[�V�������I�������i�K�ŌĂяo����܂��B
	//�v���C���[�𔻒肷��ꍇ�A�Q�[�����ŊǗ����Ă���ss::Player�̃A�h���X�Ɣ�r���Ĕ��肵�Ă��������B
	//player->getPlayAnimeName();
	//���g�p���鎖�ōĐ����Ă���A�j���[�V���������擾���鎖���ł��܂��B
	
	//���[�v�񐔕��Đ�������ɌĂяo�����_�ɒ��ӂ��Ă��������B
	//�������[�v�ōĐ����Ă���ꍇ�̓R�[���o�b�N���������܂���B

}

