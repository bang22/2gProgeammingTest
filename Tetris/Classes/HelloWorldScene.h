#pragma once

#include "stdafx.h"

class HelloWorld : public Layer
{
private:

	cTetris* tetris;

	bool speedUp;

public:
    //!< 씬 생성에 대한 싱글톤
    static Scene* createScene();

    //!< 초기화 하는 구문
	//!< bool 형으로 만든 이유는 true 면 정상적인 반환
	//!< false 면 정상적으로 안되었기 때문에 오류 메시지를 반환하기 위함
    virtual bool init();  
    
	void update(float dt);
	void update2(float dt);

	EventListenerKeyboard* listener;

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    //!< 씬을 등록 시킴
    CREATE_FUNC(HelloWorld);
};