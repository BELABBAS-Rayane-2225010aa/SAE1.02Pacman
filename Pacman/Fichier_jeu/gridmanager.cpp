

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

#include "gridmanager.h"
#include "mingl/gui/sprite.h"
#include "mingl/gui/text.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"


#include "type.h"


using namespace std;


void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()


void DisplayGrid (const CMat & Mat, const CMyParam Param)
{
    const unsigned KNbLine = Mat.size ();
    for (unsigned i (0); i < KNbLine; ++i)
    {
        for (char c : Mat[i])
        {
            if (c == KEmpty || c == kBorder || c == kPoint)
            {
                cout << c;
            }
            else if (c == Param.MapParamChar.find("TokenP1")->second)
            {
                Color (KColor.find(Param.MapParamString.find("ColorP1")->second)->second);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
            else if (c == Param.MapParamChar.find("TokenBOT")->second)
            {
                Color (KColor.find(Param.MapParamString.find("ColorBOT")->second)->second);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
        }
        cout << endl;
    }
}// ShowMatrix ()






void LoadMatrice(CMat & Mat, string & FileName){
    ifstream ifs (FileName);
    if (!ifs.is_open()) {cerr << "OH MON DIEU il trouve pas le fichier "; return;}
    size_t NbLine (0), NbRow (0);
    char car;
    ifs.get(car);
    while(!ifs.eof()){
        while (car != '\n'){
            Mat.resize(NbLine+1);
            Mat[NbLine].resize(NbRow+1);
            Mat[NbLine][NbRow] = car;
            ifs.get(car);
            ++NbRow;
        }
        ifs.get(car);
        ++NbLine;
        NbRow = 0;
    }

}

void InitGrid (CMat & Mat, const CMyParam & Param, CPosition & PosPlayer1, CPosition & PosBOT1, CPosition & PosBOT2, size_t & STV /*Score To Victory*/)
{
    PosBOT1.first = Mat.size() - 2;
    PosBOT1.second = 1;
    Mat[PosBOT1.first][PosBOT1.second] = Param.MapParamChar.find("TokenBOT")->second;
    PosBOT2.first = 1;
    PosBOT2.second = 1;
    Mat[PosBOT2.first][PosBOT2.second] = Param.MapParamChar.find("TokenBOT")->second;
    PosPlayer1.first = 1;
    PosPlayer1.second = Mat[PosPlayer1.first].size() - 2;
    Mat[PosPlayer1.first][PosPlayer1.second] = Param.MapParamChar.find("TokenP1")->second;
    for (CVLine & Line : Mat){
        for (CVLine::iterator iter (Line.begin()); iter != Line.end(); ++iter){
            if (*iter == KEmpty){
                *iter = kPoint;
                ++STV;
            }
        }
    }
}

void displaying_mingl(MinGL & window, CMat & Mat){
    for(size_t i=0;i<Mat.size();++i){
        for(size_t j=0;j<Mat[i].size();++j){
            if(Mat[i][j]=='#'){
                window<<nsShape::Rectangle (nsGraphics::Vec2D(j*50,i*50), nsGraphics::Vec2D(j*50+50,i*50+50), nsGraphics::KBlue);
            }
            //gestion des sprites pac man
            else if(Mat[i][j]=='O' && window.isPressed({'z', false}))
                window<<nsGui::Sprite ("res/sprites/pacman/pacmant/pacmant1.si2", nsGraphics::Vec2D(j*50, i*50));

            else if(Mat[i][j]=='O' && window.isPressed({'s', false}))
                window<<nsGui::Sprite ("res/sprites/pacman/pacmanb/pacmanb1.si2", nsGraphics::Vec2D(j*50, i*50));

            else if(Mat[i][j]=='O' && window.isPressed({'q', false}))
                window<<nsGui::Sprite ("res/sprites/pacman/pacmanl/pacmanl1.si2", nsGraphics::Vec2D(j*50, i*50));

            else if(Mat[i][j]=='O' && window.isPressed({'d', false}))
                window<<nsGui::Sprite ("res/sprites/pacman/pacmanr/pacmanr1.si2", nsGraphics::Vec2D(j*50, i*50));

            else if(Mat[i][j]=='O'){
                window<<nsGui::Sprite ("res/sprites/pacman/pacman0.si2", nsGraphics::Vec2D(j*50, i*50));
            }
            //fantome
            else if(Mat[i][j]=='H'){
                //window<<nsShape::Rectangle (nsGraphics::Vec2D(j*50,i*50), nsGraphics::Vec2D(j*50+50,i*50+50), nsGraphics::KGreen);
                window<<nsGui::Sprite ("res/sprites/redghost/redghostl/redghostl1.si2", nsGraphics::Vec2D(j*50, i*50));
            }
            //points
            else if(Mat[i][j]=='.'){
                window << nsShape::Circle(nsGraphics::Vec2D(j*50+25, i*50+25), 5, nsGraphics::RGBAcolor(255, 200, 0));
            }
            //gestion texte
            window << nsGui::Text(nsGraphics::Vec2D(20, 20), "1up", nsGraphics::KWhite);
            window << nsGui::Text(nsGraphics::Vec2D(20, 35), "Score : ", nsGraphics::KWhite);
        }
    }
}





