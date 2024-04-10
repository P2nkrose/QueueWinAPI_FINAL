#pragma once
class qUIMgr
{
	SINGLE(qUIMgr);

public:
	void tick();
	
	void SetOwner(qObj* _Owner) { m_Owner = _Owner; }

private:

	qObj*		m_Owner;

};

