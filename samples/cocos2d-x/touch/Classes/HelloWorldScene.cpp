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
    label = LabelTTF::create("Hello World", "Arial", 24);
    
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
	Visual Studio Express 2013 for Windows Desktop�Acocos2d-x Ver3.2�œ�����m�F���Ă��܂��B
	ssbp��png������΍Đ����鎖���ł��܂����AResources�t�H���_��sspj���܂܂�Ă��܂��B

	**********************************************************************************/
		
	//���\�[�X�}�l�[�W���̍쐬
	auto resman = ss::ResourceManager::getInstance();
	//�v���C���[�̍쐬
	ssplayer = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	//���ꂼ��̃v���b�g�t�H�[���ɍ��킹���p�X�֕ύX���Ă��������B
	resman->addData("character_template_comipo\\character_template1.ssbp");
	//�v���C���[�Ƀ��\�[�X�����蓖��
	ssplayer->setData("character_template1");        // ssbp�t�@�C�����i�g���q�s�v�j
	//�Đ����郂�[�V������ݒ�
	ssplayer->play("character_template_3head/stance");				 // �A�j���[�V���������w��(ssae��/�A�j���[�V���������\�A�ڂ����͌�q)

	//�A�j���̈ʒu��ݒ�
	ssplayer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//�X�P�[���̕ύX
	ssplayer->setScale(0.5f, 0.5f);

	//���[�U�[�f�[�^�R�[���o�b�N��ݒ�
	ssplayer->setUserDataCallback(CC_CALLBACK_2(HelloWorld::userDataCallback, this));

	//�A�j���[�V�����I���R�[���o�b�N��ݒ�
	ssplayer->setPlayEndCallback(CC_CALLBACK_1(HelloWorld::playEndCallback, this));

	//�v���C���[���Q�[���V�[���ɒǉ�
	this->addChild(ssplayer, 10);


	//updete�̍쐬
	this->scheduleUpdate();



	//�A�j���[�V�����Ɋ܂܂�p�[�c���^�b�`���ꂽ�����擾����T���v���R�[�h�ł��B
	//�T���v���ł́A�p�[�c��""collision"�͈̔͂��^�b�`���肵�܂��B

	//�C�x���g���X�i�[���쐬
	auto listener = EventListenerTouchOneByOne::create();

	//�^�b�`�J�n
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		//�C�x���g�𔭐�������SSPlayer���擾���܂��B
		auto target = (ss::Player*)event->getCurrentTarget();

		//�p�[�c�����������ă^�b�`����p�̋�`���擾
		ss::ResluteState result;
		if ( true == target->getPartState(result, "collision") )
		{
			//Node�̔z�u���W�ƃ^�b�`�Ŏ擾�������W��Y�������t�̗l�Ȃ̂ŏ㉺�𔽓]���܂��B
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Rect targetBox(result.x, visibleSize.height - result.y, result.scaledsize_X, result.scaledsize_Y);

			//�^�b�`���ꂽ���W�̎擾
			Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);

			//touchPoint��targetBox�̒��Ɋ܂܂�Ă��邩����
			if (targetBox.containsPoint(touchPoint))
			{
				//�p�[�c���^�b�`����܂����B
				CCLOG("touch parts");
				return true;
			}
		}


		return false;
	};

	//�C�x���g���X�i�[��o�^
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, ssplayer);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//���C�����[�v
void HelloWorld::update(float delta)
{
	// �����ɏ������L�q
	
	//�p�[�c��������W���擾���܂��B
	//�Q�[���̓��e�ɉ����ĕK�v�ȏ����擾�ł���悤�Ƀv���C���[���������Ă��������B
	ss::ResluteState result;
	//�Đ����Ă��郂�[�V�����Ɋ܂܂��p�[�c���ucollision�v�̃X�e�[�^�X���擾���܂��B
	ssplayer->getPartState(result, "collision");
		
	//�擾�������W��\��
	auto str = String::createWithFormat("x:%f, y:%f", result.x, result.y);
	label->setString(str->getCString());

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
