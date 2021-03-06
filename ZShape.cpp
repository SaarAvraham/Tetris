#include "ZShape.h"

zShape::zShape(ShapeDir shapeDir, char material)
{
	this->shapeDir = shapeDir;
	this->c = material;
	body[0] = { STARTX, STARTY + 1 };

	body[1] = body[0].right();
	body[2] = body[0].up();
	body[3] = body[2].left();
}

void zShape::draw()
{
	if (shapeDir == ORIGINAL)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].right();
		body[2] = body[0].up();
		body[3] = body[2].left();
	}
	else if (shapeDir == CW90)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].down();
		body[2] = body[0].right();
		body[3] = body[2].up();
	}
	else if (shapeDir == CW180)
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].right();
		body[2] = body[0].down();
		body[3] = body[2].left();
	}
	else//CW270
	{
		body[0] = { this->body[0].getX(),this->body[0].getY() };
		body[1] = body[0].up();
		body[2] = body[0].left();
		body[3] = body[2].down();
	}
	for (size_t i = 0; i <this->getLen(); i++)
	{
		body[i].draw(this->c);
	}
}

bool zShape::move(ARROWS key, GameBoard & gameBoard, Menu & menu)
{
	Point p[MAXLEN] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } }, lastPos[MAXLEN]{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
	int size;

	lastPos[0] = this->body[0];
	lastPos[1] = this->body[1];
	lastPos[2] = this->body[2];
	lastPos[3] = this->body[3];
	switch (key)
	{
	case ARROWS::LEFT:
	{
		p[0].setY(body[0].getY());
		p[1].setY(body[1].getY());
		p[2].setY(body[2].getY());
		p[3].setY(body[3].getY());

		p[0].setX(body[0].getX() - 1);
		p[1].setX(body[1].getX() - 1);
		p[2].setX(body[2].getX() - 1);
		p[3].setX(body[3].getX() - 1);

		size = this->getLen();//this is for isLegitMove "1" CAN NOT replaced with a constant

		if (gameBoard.isLegitMove(p, size, lastPos))
		{
			if (this->body[0].getX() != FIRST_COL_GAME && this->body[3].getX() != FIRST_COL_GAME)
			{
				gotoxy(body[3].getX(), body[3].getY());
				body[3].draw(' ');
				gotoxy(body[2].getX(), body[2].getY());
				body[2].draw(' ');

				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');

				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');

				body[0].setX(body[0].getX() - 1);
			}
		}
		else
			return false;
		break;
	}
	case ARROWS::RIGHT:
	{


		p[0].setY(body[0].getY());
		p[1].setY(body[1].getY());
		p[2].setY(body[2].getY());
		p[3].setY(body[3].getY());

		p[0].setX(body[0].getX() + 1);
		p[1].setX(body[1].getX() + 1);
		p[2].setX(body[2].getX() + 1);
		p[3].setX(body[3].getX() + 1);
		size = this->getLen();//this is for isLegitMove "1" CAN NOT replaced with a constant

		if (gameBoard.isLegitMove(p, size, lastPos))
		{
			if (this->body[0].getX() != LAST_COL_GAME && this->body[3].getX() != LAST_COL_GAME)
			{
				gotoxy(body[3].getX(), body[3].getY());
				body[3].draw(' ');
				gotoxy(body[2].getX(), body[2].getY());
				body[2].draw(' ');

				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');

				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');

				body[0].setX(body[0].getX() + 1);
			}
		}
		else
			return false;
		break;

	}
	case ARROWS::DOWN:
	{
		p[0].setY(body[0].getY() + 1);
		p[1].setY(body[1].getY() + 1);
		p[2].setY(body[2].getY() + 1);
		p[3].setY(body[3].getY() + 1);

		p[0].setX(body[0].getX());
		p[1].setX(body[1].getX());
		p[2].setX(body[2].getX());
		p[3].setX(body[3].getX());
		size = this->getLen();
		if (gameBoard.isLegitMove(p, size, lastPos))
		{
			if (this->body[0].getY() != LAST_ROW_GAME && this->body[3].getY() != LAST_ROW_GAME)
			{
				gotoxy(body[0].getX(), body[0].getY());
				body[0].draw(' ');
				gotoxy(body[1].getX(), body[1].getY());
				body[1].draw(' ');
				gotoxy(body[2].getX(), body[2].getY());
				body[2].draw(' ');
				gotoxy(body[3].getX(), body[3].getY());
				body[3].draw(' ');

				body[0].setY(body[0].getY() + 1);
				body[1].setY(body[1].getY() + 1);
				body[2].setY(body[2].getY() + 1);
				body[3].setY(body[3].getY() + 1);
			}
		}
		else
			return false;
		break;
	}
	}
	this->draw();
	this->updateBoard(key, gameBoard, menu, lastPos);
	return true;
}

Shape::ShapeDir zShape::getShapeDir() const
{
	return shapeDir;
}

void zShape::rotateRight(GameBoard & gameBoard, Menu& menu)
{
	Point lastPos[ZSHAPE_LEN];
	Point pCheck[ZSHAPE_LEN];
	for (size_t i = 0; i < ZSHAPE_LEN; i++)
		lastPos[i] = body[i];
	for (size_t i = 0; i < ZSHAPE_LEN; i++)
		pCheck[i] = body[i];

	for (int i = 0; i < this->getLen(); i++)
	{
		//pCheck[i].draw(' ');
		pCheck[i].rotateRight90Point((float)pCheck[0].getX(), (float)pCheck[0].getY());
	}

	if (gameBoard.GameBoard::isLegitMove(pCheck, this->getLen(), lastPos))
	{
		for (int i = 0; i < this->getLen(); i++)
		{
			body[i].draw(' ');
			body[i].rotateRight90Point((float)body[0].getX(), (float)body[0].getY());
		}
		shapeDir = (Shape::ShapeDir) (((int)shapeDir + 1) % NUM_OF_ROTATIONS);
		this->draw();
		this->updateBoard(Shape::CHANGER, gameBoard,menu, lastPos);
	}
}

void zShape::immidiateDown(GameBoard & gameBoard, Menu & menu)
{
	bool resume = true;

	while (resume == true)
	{
		resume = this->move(Shape::DOWN, gameBoard, menu);
		this->updateBoard(Shape::DOWN, gameBoard, menu);
	}
}

void zShape::updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN]) const
{
	int i;
	if (lastPos != NULL)
	{
		for (i = 0; i < this->getLen(); i++)
			gameBoard.setCell(lastPos[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), lastPos[i].getX() - FIRST_COL_GAME, 0);
	}

	for (i = 0; i < this->getLen(); i++)
		gameBoard.setCell(this->body[i].getY() + ((BOARD_HEIGHT - 1) - LAST_ROW_GAME), this->body[i].getX() - FIRST_COL_GAME, this->getChar());
}

bool zShape::hasReachedBottom(GameBoard &gameBoard, Menu& menu) 
{
	if (this->getShapeDir() == Shape::ORIGINAL)
		return (body[0].getY() == LAST_ROW_GAME);
	else if (this->getShapeDir() == Shape::CW90)
		return (body[0].getY() == LAST_ROW_GAME - 1);
	else if (this->getShapeDir() == Shape::CW180)
		return (body[0].getY() == LAST_ROW_GAME - 1);
	else if (this->getShapeDir() == Shape::CW270)
		return (body[0].getY() == LAST_ROW_GAME - 1);
}

bool zShape::isGameOver() const
{
	int y, dummyX;
	this->getBodyCellXY(0, dummyX, y);
	if (y == this->getStartY())
		return true;
	else return false;
}