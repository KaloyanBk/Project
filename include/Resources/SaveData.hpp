#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void saveData(
    int numberOfPlayers,
    int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
    int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
    bool upperWeapon, int upperWeaponLevel,
    bool lowerWeapon, int lowerWeaponLevel,
    int typeOfBullet);

void loadSavedData(
    int &numberOfPlayers,
    int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
    int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
    bool &upperWeapon, int &upperWeaponLevel,
    bool &lowerWeapon, int &lowerWeaponLevel,
    int &typeOfBullet);

void saveDefaultData();

void eraceSavedData();

void setNumberOfPlayers(int numberOfPlayers);
void setPlayer1Level(int player1Level);
void setPlayer1Hp(int player1Hp);
void setPlayer1HpMax(int player1HpMax);
void setPlayer1Exp(float player1Exp);
void setPlayer1ExpNext(float player1ExpNext);
void setPlayer1Score(int player1Score);
void setPlayer2Level(int player2Level);
void setPlayer2Hp(int player2Hp);
void setPlayer2HpMax(int player2HpMax);
void setPlayer2Exp(float player2Exp);
void setPlayer2ExpNext(float player2ExpNext);
void setPlayer2Score(int player2Score);
void setUpperWeapon(bool upperWeapon);
void setUpperWeaponLevel(int upperWeaponLevel);
void setLowerWeapon(bool lowerWeapon);
void setLowerWeaponLevel(int lowerWeaponLevel);
void setTypeOfBullet(int typeOfBullet);
void setContinueGame(bool continueGame);

