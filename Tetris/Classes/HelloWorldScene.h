#pragma once

#include "stdafx.h"

class HelloWorld : public Layer
{
private:

	cTetris* tetris;

	bool speedUp;

public:
    //!< �� ������ ���� �̱���
    static Scene* createScene();

    //!< �ʱ�ȭ �ϴ� ����
	//!< bool ������ ���� ������ true �� �������� ��ȯ
	//!< false �� ���������� �ȵǾ��� ������ ���� �޽����� ��ȯ�ϱ� ����
    virtual bool init();  
    
	void update(float dt);
	void update2(float dt);

	EventListenerKeyboard* listener;

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    //!< ���� ��� ��Ŵ
    CREATE_FUNC(HelloWorld);
};