#pragma once


#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							type(const type& _other) = delete;\
						public:\
							~type();


#define USE_PEN(DC, TYPE) qSelectObj SelectPen(DC, qEngine::GetInst()->GetPen(PEN_TYPE::TYPE))
#define USE_BRUSH(DC, TYPE) qSelectObj SelectBrush(DC, qEngine::GetInst()->GetBrush(BRUSH_TYPE::TYPE))

#define DT qTimeMgr::GetInst()->GetDeltaTime()
#define DC qEngine::GetInst()->GetSubDC()


#define KEY_CHECK(Key, State) qKeyMgr::GetInst()->GetKeyState(Key) == State

#define KEY_TAP(Key)		KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_PRESSED(Key)	KEY_CHECK(Key, KEY_STATE::PRESSED)
#define KEY_RELEASED(Key)	KEY_CHECK(Key, KEY_STATE::RELEASED)
#define KEY_NONE(Key)		KEY_CHECK(Key, KEY_STATE::NONE)

#define CLONE(Type) virtual Type* Clone() override {return new Type(*this); };
#define CLONE_DISABLE(Type) virtual Type* Clone() override {return nullptr; };

#define PI 3.1415926535f