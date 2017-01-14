#include "stdafx.h"
#include "GameBoard.h"
#include <afx.h>
#define SPEED 7.5

KGameBoard::KGameBoard():m_score(0), m_count(1), m_offset(0), m_moved(false), m_lastcall(false), m_okay(true), m_oldrand(0) 
{
    m_xstart[0] = 40;
    m_xstart[1] = 130;
    m_xstart[2] = 220;
    m_xstart[3] = 310;
    m_xend[0] = 120;
    m_xend[1] = 210;
    m_xend[2] = 300;
    m_xend[3] = 390;
    m_ystart[0] = 60;
    m_ystart[1] = 195;
    m_ystart[2] = 330;
    m_ystart[3] = 330+135; 
    m_yend[0] = 185;
    m_yend[1] = 320;
    m_yend[2] = 455;
    m_yend[3] = 590;
    m_red[0] = 0xEE;
    m_green[0] = 0xE4;
    m_blue[0] = 0xDA;
    m_red[1] = 0xED;
    m_green[1] = 0xE0;
    m_blue[1] = 0xC8;
    m_red[3] = 0xF5;
    m_green[3] = 0x95;
    m_blue[3] = 0x63;
    m_red[2] = 0xF2;
    m_green[2] = 0xB1;
    m_blue[2] = 0x79;
    m_red[4] = 0xF6;
    m_green[4] = 0x7C;
    m_blue[4] = 0x5F;
    m_red[5] = 0xF6;
    m_green[5] = 0x5E;
    m_blue[5] = 0x3B;
    m_red[6] = 255;
    m_green[6] = 255;
    m_blue[6] = 0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            m_oldpos[i][j] = 0;
            m_newpos[i][j] = 0;
            m_oldboard[i][j] = 0;
        }
    }
}
void KGameBoard::addTile(){
    srand(time(NULL));
    int r = rand();
    int iSecret = r % 16;
    int newval;
    int i =0;
    if(m_oldrand%10<9) newval = 2;
    else newval=4;
    m_oldrand = r;
    while(i<16){
        iSecret = (iSecret+i)%16;
        if(m_board[iSecret/4][iSecret%4].val==0)
        {
            m_board[iSecret/4][iSecret%4].val=newval;
            m_oldboard[iSecret/4][iSecret%4]=newval;
            break;
        }
        i++;
    }
}
void KGameBoard::makeMove(int dir) {
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            m_oldboard[i][j] = m_board[i][j].val;
        }
    }
    switch( dir )
    {
    case 2:
        for( int x = 0; x < 4; x++ )
        {
            int y = 1;
            while( y < 4 )
            { if( m_board[x][y].val ) {m_oldpos[x][y] = m_count;  m_hov=2; moveVert( x, y, -1 ); m_count++;} y++;}
        }
        break;
    case 4:
        for( int x = 0; x < 4; x++ )
        {
            int y = 2;
            while( y >= 0 )
            { if( m_board[x][y].val ) {m_oldpos[x][y] = m_count;  m_hov=4; moveVert( x, y, 1 ); m_count++;} y--;}
        }
        break;
    case 1:
        for( int y = 0; y < 4; y++ )
        {
            int x = 1;
            while( x < 4 )
            { if( m_board[x][y].val ) {m_oldpos[x][y] = m_count;  m_hov=1; moveHori( x, y, -1 ); m_count++;} x++;}
        }
        break;
    case 3:
        for( int y = 0; y < 4; y++ )
        {
            int x = 2;
            while( x >= 0 )
            { if( m_board[x][y].val ) {m_oldpos[x][y] = m_count; m_hov = 3; moveHori( x, y, 1 ); m_count++;} x--;}
        }
        break;
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            m_board[i][j].blocked=false;

            m_count=1;
        }
    }
    /*if(m_moved)
    {
    addTile();
    //m_moved = false;
    }*/
}

void KGameBoard::moveVert( int x, int y, int d )
{
    bool yes = false;
    if( m_board[x][y + d].val && m_board[x][y + d].val == m_board[x][y].val && !m_board[x][y].blocked && !m_board[x][y + d].blocked  )
    {
        m_board[x][y].val = 0;
        m_board[x][y + d].val *= 2;
        m_score += m_board[x][y + d].val;
        m_board[x][y + d].blocked = true;
        m_moved = true;
        yes = true;
    }
    else if( !m_board[x][y + d].val && m_board[x][y].val )
    {
        m_board[x][y + d].val = m_board[x][y].val;
        m_board[x][y].val = 0;
        m_moved = true;
        yes = true;
    }
    if( d > 0 ) { if( y + d < 3 &&yes ) moveVert( x, y + d,  1 );
    else if(yes) m_newpos[x][y+1] = m_count;
    else m_newpos[x][y] = m_count;
    }
    else        { if( y + d > 0 &&yes) moveVert( x, y + d, -1 ); 
    else if(yes) m_newpos[x][y-1] = m_count;
    else m_newpos[x][y] = m_count;
    }


}
void KGameBoard::moveHori( int x, int y, int d )
{
    bool yes = false;
    if( m_board[x + d][y].val && m_board[x + d][y].val == m_board[x][y].val && !m_board[x][y].blocked && !m_board[x + d][y].blocked  )
    {
        m_board[x][y].val = 0;
        m_board[x + d][y].val *= 2;
        m_score += m_board[x + d][y].val;
        m_board[x + d][y].blocked = true;
        m_moved = true;
        yes = true;
    }
    else if( !m_board[x + d][y].val && m_board[x][y].val )
    {
        m_board[x + d][y].val = m_board[x][y].val;
        m_board[x][y].val = 0;
        m_moved = true;
        yes = true;
    }
    if( d > 0 ) { if( x + d < 3 &&yes) moveHori( x + d, y,  1 );
    else if(yes)  m_newpos[x+1][y] = m_count; 
    else m_newpos[x][y] = m_count;
    }
    else        { if( x + d > 0 &&yes) moveHori( x + d, y, -1 ); 
    else if(yes) m_newpos[x-1][y] = m_count;
    else m_newpos[x][y] = m_count;
    }


    //newy.push_back(y)
}

//maintain another 2d array that stores which spots had tiles that were overwritten

void KGameBoard::drawRect(HDC hdc, RECT *temp,int x,int y,bool sw)
{
    int val;

    if(sw)  val = m_oldboard[x][y];
    else val = m_board[x][y].val;
    if(val==0)  //save old board values and print all of them here!!!
    {
        FillRect(hdc, temp, (HBRUSH)GetStockObject(GRAY_BRUSH));
    }
    //improve by checking the width of characters
    if(val!=0) 
    {

        HBRUSH bru;
        switch(val)
        {    case 2:
        bru = CreateSolidBrush(RGB(m_red[0],m_green[0],m_blue[0]));
        break;
        case 4:
            bru = CreateSolidBrush(RGB(m_red[1],m_green[1],m_blue[1]));
            break;
        case 8:
            bru = CreateSolidBrush(RGB(m_red[2],m_green[2],m_blue[2]));
            break;
        case 16:
            bru = CreateSolidBrush(RGB(m_red[3],m_green[3],m_blue[3]));
            break;
        case 32:
            bru = CreateSolidBrush(RGB(m_red[4],m_green[4],m_blue[4]));
            break;
        case 64:
            bru = CreateSolidBrush(RGB(m_red[5],m_green[5],m_blue[5]));
            break;
        default:
            bru = CreateSolidBrush(RGB(m_red[6],m_green[6],m_blue[6]));
            break;
        }
        FillRect(hdc, temp, bru);

        ::DeleteObject(bru);
    }
}
void KGameBoard::drawBoard(HDC hdc){
    //after every move and after init
    //addTile();

    // Rectangle(hdc,30,0,400,600);
    for(int x=0;x<4;x++)
    {    for(int y=0;y<4;y++)
    {  RECT temp;
    temp.left = m_xstart[x]+1;
    temp.right = m_xend[x]-1;
    temp.top = m_ystart[y]+1;
    temp.bottom = m_yend[y]-1;
    if(m_newpos[x][y]==0||m_newpos[x][y]==m_oldpos[x][y])
    {


        //if((m_oldpos[x][y]==0||m_oldpos[x][y]==m_newpos[x][y]))

        drawRect(hdc,&temp,x,y,false);
        if(m_board[x][y].val!=0){
            CString pointsInStr;
            pointsInStr.Format(TEXT("%d"),m_board[x][y].val);
            TextOut(hdc,m_xstart[x]+37,m_ystart[y]+60,pointsInStr, pointsInStr.GetLength());
        }
    }
    else if(m_oldpos[x][y]==0)  FillRect(hdc, &temp, (HBRUSH)GetStockObject(GRAY_BRUSH));
    }
    }
    //::SetTimer(hWnd, 1, 100, TimerProc);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(!(m_newpos[i][j]==0||m_oldpos[i][j]==m_newpos[i][j]))
            {
                RECT temp;
                int disp=0;

                switch (m_hov)
                {   case 1:
                if(i<=2&&m_oldpos[i+1][j]==m_newpos[i][j])    disp=1;
                if(i<=1&&m_oldpos[i+2][j]==m_newpos[i][j])    disp=2;
                if(i<=0&&m_oldpos[i+3][j]==m_newpos[i][j])    disp=3;
                temp.left = m_xstart[i+disp]+1-m_offset*SPEED*(disp);
                temp.right = m_xend[i+disp]-1-m_offset*SPEED*(disp);
                temp.top=m_ystart[j]+1;
                temp.bottom=m_yend[j]-1;
                if(m_oldboard[i+disp][j]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
                else if(!m_lastcall) drawRect(hdc,&temp,i+disp,j,true);
                else drawRect(hdc,&temp,i,j,false);
                break;
                case 2:
                    if(j<=2&&m_oldpos[i][j+1]==m_newpos[i][j])    disp=1;
                    if(j<=1&&m_oldpos[i][j+2]==m_newpos[i][j])    disp=2;
                    if(j<=0&&m_oldpos[i][j+3]==m_newpos[i][j])    disp=3;
                    temp.left = m_xstart[i]+1;
                    temp.right = m_xend[i]-1;
                    temp.top = m_ystart[j+disp]+1-m_offset*SPEED*(disp);
                    temp.bottom = m_yend[j+disp]-1-m_offset*SPEED*(disp);
                    if(m_oldboard[i][j+disp]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
                    else if(!m_lastcall) drawRect(hdc,&temp,i,j+disp,true);
                    else drawRect(hdc,&temp,i,j,false);
                    break;
                case 3:
                    if(i>=1&&m_oldpos[i-1][j]==m_newpos[i][j])    disp=1;
                    if(i>=2&&m_oldpos[i-2][j]==m_newpos[i][j])    disp=2;
                    if(i>=3&&m_oldpos[i-3][j]==m_newpos[i][j])    disp=3;
                    temp.left = m_xstart[i-disp]+1+m_offset*SPEED*(disp);
                    temp.right = m_xend[i-disp]-1+m_offset*SPEED*(disp);
                    temp.top=m_ystart[j]+1;
                    temp.bottom=m_yend[j]-1;
                    if(m_oldboard[i-disp][j]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
                    else if(!m_lastcall) drawRect(hdc,&temp,i-disp,j,true);
                    else drawRect(hdc,&temp,i,j,false);
                    break;
                case 4:
                    if(j>=1&&m_oldpos[i][j-1]==m_newpos[i][j])    disp=1;
                    if(j>=2&&m_oldpos[i][j-2]==m_newpos[i][j])    disp=2;
                    if(j>=3&&m_oldpos[i][j-3]==m_newpos[i][j])    disp=3;
                    temp.left = m_xstart[i]+1;
                    temp.right = m_xend[i]-1;
                    temp.top = m_ystart[j-disp]+1+m_offset*SPEED*(disp);
                    temp.bottom = m_yend[j-disp]-1+m_offset*SPEED*(disp);
                    if(m_oldboard[i][j-disp]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
                    else if(!m_lastcall) drawRect(hdc,&temp,i,j-disp,true);
                    else drawRect(hdc,&temp,i,j,false);
                    break;
                }    
            }
        }
    }
    // KillTimer(hWnd, 1);*/
}
bool KGameBoard::_testAdd( int x, int y, int v )
{
    if( x < 0 || x > 3 || y < 0 || y > 3 ) return false;
    return m_board[x][y].val == v;
}

bool KGameBoard::canMove()
{
    for( int y = 0; y < 4; y++ )
        for( int x = 0; x < 4; x++ )
            if( !m_board[x][y].val ) return true;

    for( int y = 0; y < 4; y++ )
        for( int x = 0; x < 4; x++ )
        {
            if( _testAdd( x + 1, y, m_board[x][y].val ) ) return true;
            if( _testAdd( x - 1, y, m_board[x][y].val ) ) return true;
            if( _testAdd( x, y + 1, m_board[x][y].val ) ) return true;
            if( _testAdd( x, y - 1, m_board[x][y].val ) ) return true;
        }
        return false;
}
void KGameBoard::gameOver(HDC hdc,HWND hWnd){
    SetBkMode(hdc,OPAQUE);
    RECT clientRect;
    GetClientRect(hWnd,&clientRect);
    FillRect(hdc,&clientRect,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
    TextOut(hdc,clientRect.right/2,clientRect.bottom/2,TEXT("Game Over"),9);
}





