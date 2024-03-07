#pragma once
#include "qObj.h"
class qTile : public qObj
{
public:
	CLONE(qTile);

public:
	qTile();
	~qTile();

private:
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;
};

