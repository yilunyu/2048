#include "Tile.h"
#include "Resource.h"

#ifndef KGAMEBOARD_H
#define KGAMEBOARD_H

class KGameBoard 
{
public:
       int m_offset;      //by how much tiles have moved since keydown
       int m_hov;         //horizontal or vertical direction
       bool m_moved;
       int m_red[7];
       int m_green[7];
       int m_blue[7];
       int m_oldboard[4][4];
      /* std::vector<int> oldx;
       std::vector<int> oldy;
       std::vector<int> newx;
       std::vector<int> newy;*/
       int m_oldpos[4][4];
       int m_newpos[4][4];
       int m_count;
       bool m_lastcall;    //if true, then we are drawing the last frame of the tile moving animation
       KTile m_board[4][4];   
       
       int m_xstart [4]; 
       int m_xend[4];
       int m_ystart[4];
       int m_yend[4];
        //these four arrays define the x and y coordinates of the top-left and bottom right corners of
       //all 16 tiles on the gameboard

       int m_okay;
       int m_score;
       int m_oldrand;

public:
       void gameOver(HDC hdc,HWND hWnd);
       bool canMove();
       void drawBoard(HDC hdc);
       void drawRect(HDC hdc, RECT *temp,int x,int y,bool sw);
       void moveHori( int x, int y, int d );
       void moveVert( int x, int y, int d );
       void makeMove(int dir);
       void addTile();
       KGameBoard();
private:
       bool _testAdd(int x,int y,int v);
    
};

#endif
