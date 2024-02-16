#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H

/*!
 * \file gridmanager.h
 * \brief Fonctions for grid/map management
 * \author Adam De Angeli
 * \version 1.0
 * \date 05/01/2023
*/


#include <string>

#include "type.h"
#include "mingl/mingl.h"

/**
 * @brief Clear the current terminal
 * @fn void ClearScreen ();
 */
void ClearScreen ();

/**
 * @brief Set the color of the future input in the terminal
 * @param[in] Col : Next color to be used
 * @fn void Color (const std::string & Col);
 */
void Color (const std::string & Col);


/**
 * @brief Display the grid according to the parameters
 * @param[in] Mat : Game grid
 * @param[in] Params : : List of usefull parameters
 * @fn void DisplayGrid (const CMat & Mat, const CMyParam & Params, bool ShowLineNumber = true, bool ShowColor = true);
 */
void DisplayGrid (const CMat & Mat, const CMyParam Param);

/**
 * @brief Initialize the grid from an extern file
 * @param[in, out] Mat the matrix
 * @param[in] The path to the file FileName
 */

void LoadMatrice (CMat & Mat, std::string & FileName);

/*!
 * \brief Initialization of the Matrix from scratch
 * \param[out] Mat the matrix to be initialized
 * \param[in] Parms Set of game's parameters
 * \param[out] PosPlayer1 position of the first player's token in Mat
 * \param[out] PosBOT position of the bot token in Mat
 * \param[out] STV score to victory (number of point in mat)
 * @fn void InitGrid (CMat & Mat, const CMyParam & Params, CPosition & PosPlayer1, CPosition & PosPlayer2);
 */
void InitGrid (CMat & Mat, const CMyParam & Param, CPosition & PosPlayer1, CPosition & PosBOT1, CPosition & PosBOT2, size_t & STV);

/*!
 * \brief Display the game in the mingl window
 * \param[out] window the mingl window that u want to use
 * \param[out] Mat the matrix representing the game
 * \param[out] ScoreToVictory
 * \param[out] Score
 * @fn void displaying_mingl(MinGL & window, CMat & Mat, size_t & ScoreToVictory, size_t & Score);
 */
void displaying_mingl(MinGL & window, CMat & Mat);



#endif // GRIDMANAGER_H
