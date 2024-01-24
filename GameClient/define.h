#pragma once


#define SINGLE(type) public:\
						static type* GetInit()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							type(const type& _other) = delete;\
						public:\
							~type();