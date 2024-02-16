#ifndef GAME_H
#define GAME_H

/*!
 * \file game.h
 * \brief Fonctions for game management
 * \author Adam De Angeli
 * \version 1.0
 * \date 05/01/2023
 */

#include "type.h"
#include "string"
#include "mingl/mingl.h"

/**
 * @brief Test if there is a collison
 * @param[in] Mat the game matrix
 * @param[in] Pos the target position
 */

bool IfCollision(CMat & Mat, CPosition & Pos);

/**
 * @brief Test if a point is on the next position
 * @param[in] Mat the game matrix
 * @param[in] Pos the target position
 */

bool IfPoitnPickedUp(CMat & Mat, CPosition & Pos);


/*!
 * \brief Move the current token according to the character in the 2nd parameter
 * \param[in, out] Mat the matrix before and after the move
 * \param[in] Move the key pressed by the user
 * \param[in, out] Pos the player's position before and after the move
 * \param[in] Param the game's parameter
 * \param[in, out] Score the player's score
 */

void MoveToken (CMat & Mat, const char & Move, CPosition & Pos, CMyParam & Param, size_t & Score, bool & pickup);

/*!
 * \brief Move the BOT dumbly
 * \param[in, out] Mat the matrix before and after the move
 * \param[in, out] Pos the BOT's position before and after the move
 * \param[in] Param the game's parameter
 * \param[in, out] BotOnCar the char under the bot
 */
void MoveBOTIdiot (CMat & Mat, CPosition & Pos, CMyParam &Param, char & BotOnCar );

/*!
 * \brief Move the BOT following Player pos
 * \param[in, out] Mat the matrix before and after the move
 * \param[in, out] PosG the BOT's position before and after the move
 * \param[in, out] PosG the Player's position
 * \param[in] Param the game's parameter
 * \param[in, out] BotOnCar the char under the bot
 */
void MoveBOT_trackP (CMat & Mat, CPosition & PosG, CPosition & PosP, CMyParam & Param, char & BotOnCar);

/*!
 * \brief fetch the playermovement
 * \param[in, out] window the matrix before and after the move
 * \param[in, out] Move the BOT's position before and after the move
 */
void playermovement(MinGL & window,std::string & Move);

/**
 * @brief new main
 * @return 0 if everything is OK
 * @fn int ppal ();
 */
int ppal ();

#endif // GAME_H
