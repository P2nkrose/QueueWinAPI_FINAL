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


#define DT qTimeMgr::GetInst()->GetDeltaTime()
#define DC qEngine::GetInst()->GetSubDC()

