#pragma once

#include "Board.h"

class BoardControl
{
private:
	Board* board;
public:
	BoardControl( Board* b);
	~BoardControl();

	bool mouse_events(player& player);
	bool CheckControlEvents(player& player, bool& NeedUpdate);


};
