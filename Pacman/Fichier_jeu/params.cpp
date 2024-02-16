#include <string>
#include "params.h"
#include "game.h"
#include <map>
#include "type.h"
#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;



void LoadParams (CMyParam & Param){
            ifstream ifs ("../Pacman/Nos_fichiers/config.yaml");
            if (!ifs.is_open()) {cerr << "OH MON DIEU il trouve pas le fichier "; return;}
            char Valchar; unsigned ValUnsigned; string Valstring;
            for (string Cle; ifs >> Cle;)
            {
                ifs >> Valchar; //pour purger le ':'
                if (KAuthorizedKey.VParamString.end() != find(KAuthorizedKey.VParamString.begin(), KAuthorizedKey.VParamString.end(), Cle))
                {
                    ifs >> Valstring;
                    Param.MapParamString[Cle] = Valstring;
                }
                else if (KAuthorizedKey.VParamChar.end() != find(KAuthorizedKey.VParamChar.begin(), KAuthorizedKey.VParamChar.end(), Cle))
                {
                    ifs >> Valchar;
                    Param.MapParamChar[Cle] = Valchar;
                }
                else if (KAuthorizedKey.VParamUnsigned.end() != find(KAuthorizedKey.VParamUnsigned.begin(), KAuthorizedKey.VParamUnsigned.end(), Cle))
                {
                    ifs >> ValUnsigned;
                    Param.MapParamUnsigned[Cle] = ValUnsigned;
                }
            }
        }
