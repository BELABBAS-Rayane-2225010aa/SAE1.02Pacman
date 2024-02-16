
#define FPS_LIMIT 15

#include "mingl/gui/sprite.h"
#include "mingl/gui/text.h"
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/audio/audioengine.h"
#include "params.h"
#include "type.h"
#include "game.h"
#include "gridmanager.h"
#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

using namespace std;

bool IfCollision(CMat & Mat, CPosition & Pos){
    if (Mat[Pos.first][Pos.second]== kBorder){
        return true;
    }
    else return false;
}

bool IfPoitnPickedUp(CMat & Mat, CPosition & Pos){
    if (Mat[Pos.first][Pos.second]== kPoint){
        return true;
    }
    else return false;
}

void MoveToken (CMat & Mat, const char & Move, CPosition & Pos, CMyParam & Param, size_t & Score, bool & pickup)
{
    CPosition NextPos (Pos);
    if (Move == toupper(Param.MapParamChar.find("KeyUp")->second))
        --NextPos.first;
    else if (Move == toupper(Param.MapParamChar.find("KeyLeft")->second))
        --NextPos.second;
    else if (Move == toupper(Param.MapParamChar.find("KeyRight")->second))
        ++NextPos.second;
    else if (Move == toupper(Param.MapParamChar.find("KeyDown")->second))
        ++NextPos.first;
    if (!(IfCollision(Mat,NextPos))){
        if (IfPoitnPickedUp(Mat,NextPos)){
            ++Score;
            pickup=true;
        }
        char car = Mat [Pos.first][Pos.second];
        Mat [Pos.first][Pos.second] = KEmpty;
        Pos = NextPos;
        Mat[NextPos.first][NextPos.second] = car;
    }
} //MoveToken ()

void MoveBOTIdiot (CMat & Mat, CPosition & Pos,CMyParam &Param, char & BotOnCar ){
    char Ligne = Pos.first;
    char col = Pos.second;
    srand(time(NULL));
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;

    int way = rand()%4;
    while (true) {
        if (way == 0)
        {
            if (Mat [Ligne-1][col] !=Param.MapParamChar.find("BorderChar")->second && Mat [Ligne-1][col] !=Param.MapParamChar.find("TokenBOT")->second ){
                Pos.first-=1;
                break;
            }
            else{
            ++way;
            }
        }
        if (way == 1)
        {
            if (Mat [Ligne][col+1] != Param.MapParamChar.find("BorderChar")->second && Mat [Ligne][col+1] != Param.MapParamChar.find("TokenBOT")->second){
                Pos.second+=1;
                break;
            }
            else{
            ++way;
            }
        }
        if (way == 2)
        {
            if (Mat [Ligne+1][col] != Param.MapParamChar.find("BorderChar")->second && Mat [Ligne+1][col] != Param.MapParamChar.find("TokenBOT")->second){
                Pos.first+=1;
                break;
            }
            else {
            ++way;
            }
        }
        if (way == 3)
        {
            if (Mat [Ligne][col-1] != Param.MapParamChar.find("BorderChar")->second && Mat [Ligne][col-1] != Param.MapParamChar.find("TokenBOT")->second){
                Pos.second-=1;
                break;
            }
            else{
            way=0;
            }
        }
    }
    Mat [Ligne][col] = BotOnCar;
    BotOnCar = Mat[Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = car;

}

void MoveBOT_trackP (CMat & Mat, CPosition & PosG, CPosition & PosP, CMyParam & Param, char & BotOnCar)
{
    char LigneG = PosG.first;
    char colG = PosG.second;
    char carG = Mat [PosG.first][PosG.second];


    if (PosG.second<PosP.second ) // on voit d'abord si le joueur est a droite du fantome si oui on continue
    {
        if (Mat [LigneG][colG+1] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.second+=1;
        }
        else if (PosG.first>=PosP.first) // on voit si Pacman est audessus
        {
            if (Mat [LigneG-1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first-=1;
            }
            else if (Mat [LigneG][colG-1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second-=1;
            }
            else if (Mat [LigneG+1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first+=1;
            }
        }
        else if (PosG.first<PosP.first)//si pac est endessous
        {
            if (Mat [LigneG+1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first+=1;
            }
            else if (Mat [LigneG][colG-1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second-=1;
            }
            else if (Mat [LigneG-1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first-=1;
            }
        }
        else if(Mat [LigneG][colG-1] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.second-=1;
        }
    }
    //
    else if (PosG.second>PosP.second ) // on cÃ©rifie si le joueur est a gauche
    {
        if (Mat [LigneG][colG-1] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.second-=1;
        }
        else if (PosG.first>=PosP.first) // on voit si Pacman est audessus
        {
            if (Mat [LigneG-1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first-=1;
            }
            else if (Mat [LigneG][colG+1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second+=1;
            }
            else if (Mat [LigneG+1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first+=1;
            }
        }
        else if (PosG.first<PosP.first)//si pac est endessous
        {
            if (Mat [LigneG+1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first+=1;
            }
            else if (Mat [LigneG][colG+1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second+=1;
            }
            else if (Mat [LigneG-1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first-=1;
            }
        }
        else if(Mat [LigneG][colG+1] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.second+=1;
        }
    }
    //
    else if (PosG.first<PosP.first ) // on voit d'abord si le joueur est sur un fantome
    {
        if (Mat [LigneG+1][colG] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.first+=1;
        }
        else if (PosG.second>=PosP.second) // on voit si Pacman est a gauche
        {
            if (Mat [LigneG][colG-1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second-=1;

            }
            else if (Mat [LigneG-1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first-=1;
            }
            else if (Mat [LigneG][colG+1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second+=1;
            }
        }
        else if (PosG.second<PosP.second)//si pac est a droite
        {
            if (Mat [LigneG][colG+1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second+=1;
            }
            else if (Mat [LigneG-1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first-=1;
            }
            else if (Mat [LigneG][colG-1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second-=1;
            }
        }
        else if (Mat [LigneG-1][colG] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.first-=1;
        }
    }
    //
    else if (PosG.first>PosP.first )
    {
        if (Mat [LigneG-1][colG] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG-1][colG] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.first-=1;
        }
        else if (PosG.second>=PosP.second) // on voit si Pacman est a gauche
        {
            if (Mat [LigneG][colG-1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second-=1;
            }
            else if (Mat [LigneG+1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first+=1;
            }
            else if (Mat [LigneG][colG+1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second+=1;
            }
        }
        else if (PosG.second<PosP.second)//si pac est a droite
        {
            if (Mat [LigneG][colG+1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG+1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second+=1;
            }
            else if (Mat [LigneG+1][colG] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.first+=1;
            }
            else if (Mat [LigneG][colG-1] !=Param.MapParamChar.find("BorderChar")->second && Mat [LigneG][colG-1] !=Param.MapParamChar.find("TokenBOT")->second)
            {
                PosG.second-=1;
            }
        }
        else if (Mat [LigneG+1][colG] != Param.MapParamChar.find("BorderChar")->second && Mat [LigneG+1][colG] != Param.MapParamChar.find("TokenBOT")->second)
        {
            PosG.first+=1;
        }
    }
    Mat [LigneG][colG] = BotOnCar;
    BotOnCar = Mat[PosG.first][PosG.second];
    Mat [PosG.first][PosG.second] = carG;
}

void playermovement(MinGL & window,string & Move)
{
    // On vérifie si ZQSD est pressé, et met a jour la position
    if (window.isPressed({'z', false})){
        Move="z";
    }
    else if (window.isPressed({'s', false})){
        Move="s";
    }
    else if (window.isPressed({'q', false})){
        Move="q";
    }
    else if (window.isPressed({'d', false})){
        Move="d";
    }
}

int ppal (void)
{   
    bool Victory (false);
    bool GameOver (false);
    size_t ScoreToVictory (1), Score (0); //STV initialiser avec 1 pour compter le point en dessous du BOT
    CMat Mat;
    CMyParam Param;
    CPosition PosP1, PosBOT1, PosBOTIdiot;
    char Bot1OnCar (kPoint), BotIdiotOnCar (kPoint); //Caractère sur lequel se trouve le bot
    LoadParams(Param);
    string FileName (kMaps.find(Param.MapParamUnsigned["NbMap"])->second);
    LoadMatrice(Mat, FileName);
    InitGrid(Mat, Param, PosP1 ,PosBOT1, PosBOTIdiot, ScoreToVictory);
    DisplayGrid(Mat,Param);

    bool play_music=true;
    MinGL window("Pacumanu", nsGraphics::Vec2D(Mat[0].size()*50, Mat.size()*50), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    nsAudio::AudioEngine audioEngine;

    audioEngine.setMusic("res/sound/pacman_chomp.wav");

    audioEngine.loadSound("res/sound/pacman_chomp1.wav");
    audioEngine.loadSound("res/sound/pacman_beginning.wav");

    chrono::microseconds frameTime = chrono::microseconds::zero();
    while (!Victory && !GameOver && window.isOpen())
    {
        string Move;
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
        window.clearScreen();

        if(play_music){
            audioEngine.playSoundFromBuffer("res/sound/pacman_beginning.wav");
            play_music=false;
        }
        playermovement(window,Move);
        displaying_mingl(window,Mat);

        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

        /*cout << " score: "<< Score << "/" << ScoreToVoctory << ", entrez un déplacement : ";
        string Move;
        cin >> Move;*/

        Move = toupper (Move[0]);
        bool pickup=false;
        MoveToken (Mat, Move[0], PosP1, Param, Score, pickup);

        window.clearScreen();

        displaying_mingl(window,Mat);
        if(pickup){
            audioEngine.playSoundFromBuffer("res/sound/pacman_chomp1.wav");
        }

        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

        //GameOver test
        if (PosP1 == PosBOT1){
            Mat[PosBOT1.first][PosBOT1.second] = Param.MapParamChar.find("TokenBOT")->second;
            GameOver = true;
            ClearScreen();
            DisplayGrid(Mat, Param);
            continue;
        }
        MoveBOTIdiot(Mat,PosBOTIdiot, Param, BotIdiotOnCar);
        //GameOver test
        if (PosP1 == PosBOTIdiot){
            Mat[PosP1.first][PosP1.second] = Param.MapParamChar.find("TokenBOT")->second;
            GameOver = true;
            ClearScreen();
            DisplayGrid(Mat, Param);
            continue;
        }
        MoveBOT_trackP(Mat, PosBOT1, PosP1, Param, Bot1OnCar);
        //GameOver test
        if (PosP1 == PosBOT1){
            Mat[PosP1.first][PosP1.second] = Param.MapParamChar.find("TokenBOT")->second;
            GameOver = true;
            ClearScreen();
            DisplayGrid(Mat, Param);
            continue;
        }

        ClearScreen();
        DisplayGrid(Mat, Param);

        window.clearScreen();

        displaying_mingl(window,Mat);

        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

        //Victory test
        if (Score == ScoreToVictory) Victory = true;

    }//while (no victory)
    if (GameOver)
    {
        Color (KColor.find("KRed")->second);
        cout << "GAME OVER" << endl;

        audioEngine.loadSound("res/sound/pacman_death.wav");

        chrono::microseconds frameTime = chrono::microseconds::zero();
        play_music=true;
        while (window.isOpen())
        {
            chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
            window.clearScreen();

            window << nsShape::Rectangle (nsGraphics::Vec2D(0,0), nsGraphics::Vec2D(Mat[0].size()*50, Mat.size()*50), nsGraphics::KRed)
                   << nsGui::Text(nsGraphics::Vec2D((Mat[0].size()*50)/2, (Mat.size()*50)/2), "Vous avez perdu :'(", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15,
                                                    nsGui::Text::HorizontalAlignment::ALIGNH_CENTER);
            if(play_music)
            {
                audioEngine.playSoundFromBuffer("res/sound/pacman_death.wav");
                play_music=false;
            }
            window.finishFrame();
            window.getEventManager().clearEvents();
            this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
            frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
        }
        return 1;
    }
    audioEngine.loadSound("res/sound/pacman_win.wav");
    play_music=true;
    Color (KColor.find("KGreen")->second);
    cout << "Félicitations Joueur vous avez gagné :)" << endl;
    Color (KColor.find("KReset")->second);
    while (window.isOpen())
    {
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
        window.clearScreen();

        window << nsShape::Rectangle (nsGraphics::Vec2D(0,0), nsGraphics::Vec2D(Mat[0].size()*50, Mat.size()*50), nsGraphics::KGreen)
               << nsGui::Text(nsGraphics::Vec2D((Mat[0].size()*50)/2, (Mat.size()*50)/2), "Vous avez win !", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15,
                                                nsGui::Text::HorizontalAlignment::ALIGNH_CENTER);;
        if(play_music){
            audioEngine.playSoundFromBuffer("res/sound/pacman_win.wav");
            play_music=false;
        }

        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
} //ppal ()
