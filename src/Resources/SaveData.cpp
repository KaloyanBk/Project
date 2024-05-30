/**
 * @file SaveData.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the SaveData functions, which are used to save and load game data.
 * @version 0.1
 * @date 2024-05-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../../include/Resources/SaveData.hpp"
#include <fstream>
#include <iostream>

/**
 * @brief Saves game data to a JSON file.
 *
 * @param numberOfPlayers The number of players.
 * @param player1Level Player 1's level.
 * @param player1Hp Player 1's health points.
 * @param player1HpMax Player 1's maximum health points.
 * @param player1Exp Player 1's experience.
 * @param player1ExpNext Player 1's experience required for next level.
 * @param player1Score Player 1's score.
 * @param player2Level Player 2's level.
 * @param player2Hp Player 2's health points.
 * @param player2HpMax Player 2's maximum health points.
 * @param player2Exp Player 2's experience.
 * @param player2ExpNext Player 2's experience required for next level.
 * @param player2Score Player 2's score.
 * @param upperWeapon Whether the upper weapon is enabled.
 * @param upperWeaponLevel The level of the upper weapon.
 * @param lowerWeapon Whether the lower weapon is enabled.
 * @param lowerWeaponLevel The level of the lower weapon.
 * @param typeOfBullet The type of bullet.
 */
void saveData(
    int numberOfPlayers,
    int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
    int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
    bool upperWeapon, int upperWeaponLevel,
    bool lowerWeapon, int lowerWeaponLevel,
    int typeOfBullet)
{
    json savedData;

    savedData["numberOfPlayers"] = numberOfPlayers;

    savedData["player1"]["level"] = player1Level;
    savedData["player1"]["hp"] = player1Hp;
    savedData["player1"]["hpMax"] = player1HpMax;
    savedData["player1"]["exp"] = player1Exp;
    savedData["player1"]["expNext"] = player1ExpNext;
    savedData["player1"]["score"] = player1Score;

    savedData["player2"]["level"] = player2Level;
    savedData["player2"]["hp"] = player2Hp;
    savedData["player2"]["hpMax"] = player2HpMax;
    savedData["player2"]["exp"] = player2Exp;
    savedData["player2"]["expNext"] = player2ExpNext;
    savedData["player2"]["score"] = player2Score;

    savedData["upperWeapon"]["enabled"] = upperWeapon;
    savedData["upperWeapon"]["level"] = upperWeaponLevel;

    savedData["lowerWeapon"]["enabled"] = lowerWeapon;
    savedData["lowerWeapon"]["level"] = lowerWeaponLevel;

    savedData["typeOfBullet"] = typeOfBullet;

    savedData["continueGame"] = true;

    std::ofstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to save data!" << std::endl;
        return;
    }

    file << savedData.dump(4);
}

/**
 * @brief Loads game data from a JSON file.
 *
 * @param numberOfPlayers The number of players.
 * @param player1Level Player 1's level.
 * @param player1Hp Player 1's health points.
 * @param player1HpMax Player 1's maximum health points.
 * @param player1Exp Player 1's experience.
 * @param player1ExpNext Player 1's experience required for next level.
 * @param player1Score Player 1's score.
 * @param player2Level Player 2's level.
 * @param player2Hp Player 2's health points.
 * @param player2HpMax Player 2's maximum health points.
 * @param player2Exp Player 2's experience.
 * @param player2ExpNext Player 2's experience required for next level.
 * @param player2Score Player 2's score.
 * @param upperWeapon Whether the upper weapon is enabled.
 * @param upperWeaponLevel The level of the upper weapon.
 * @param lowerWeapon Whether the lower weapon is enabled.
 * @param lowerWeaponLevel The level of the lower weapon.
 * @param typeOfBullet The type of bullet.
 */
void loadSavedData(
    int &numberOfPlayers,
    int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
    int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
    bool &upperWeapon, int &upperWeaponLevel,
    bool &lowerWeapon, int &lowerWeaponLevel,
    int &typeOfBullet)
{
    /// Open file to load data
    std::ifstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to load data!" << std::endl;
        return;
    }

    /// Read data from file
    json savedData;
    file >> savedData;

    /// Extract game data
    numberOfPlayers = savedData["numberOfPlayers"];

    player1Level = savedData["player1"]["level"];
    player1Hp = savedData["player1"]["hp"];
    player1HpMax = savedData["player1"]["hpMax"];
    player1Exp = savedData["player1"]["exp"];
    player1ExpNext = savedData["player1"]["expNext"];
    player1Score = savedData["player1"]["score"];

    player2Level = savedData["player2"]["level"];
    player2Hp = savedData["player2"]["hp"];
    player2HpMax = savedData["player2"]["hpMax"];
    player2Exp = savedData["player2"]["exp"];
    player2ExpNext = savedData["player2"]["expNext"];
    player2Score = savedData["player2"]["score"];

    upperWeapon = savedData["upperWeapon"]["enabled"];
    upperWeaponLevel = savedData["upperWeapon"]["level"];

    lowerWeapon = savedData["lowerWeapon"]["enabled"];
    lowerWeaponLevel = savedData["lowerWeapon"]["level"];

    typeOfBullet = savedData["typeOfBullet"];
}
/**
 * @brief Saves default game data to a JSON file.
 */
void saveDefaultData()
{
    /// Open file to load data
    std::ifstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to load data!" << std::endl;
        return;
    }

    /// Read data from file
    json savedData;
    file >> savedData;
    file.close();

    /// Update default data
    savedData["player1"]["level"] = 0;
    savedData["player1"]["hp"] = 10;
    savedData["player1"]["hpMax"] = 0;
    savedData["player1"]["exp"] = 0.0;
    savedData["player1"]["expNext"] = 0.0;
    savedData["player1"]["score"] = 0;

    savedData["player2"]["level"] = 0;
    savedData["player2"]["hp"] = 10;
    savedData["player2"]["hpMax"] = 0;
    savedData["player2"]["exp"] = 0.0;
    savedData["player2"]["expNext"] = 0.0;
    savedData["player2"]["score"] = 0;

    savedData["continueGame"] = true;

    /// Save default data
    std::ofstream outFile("data/savedData.json");
    if (!outFile.is_open())
    {
        std::cerr << "Could not open the file to save data!" << std::endl;
        return;
    }

    outFile << savedData.dump(4);
    std::cout << "Default data saved!" << std::endl;
}

/**
 * @brief Erases saved game data by replacing it with default data.
 */
void eraceSavedData()
{
    /// Create default data
    json defaultData = {
        {"numberOfPlayers", 1},
        {"player1", {{"level", 0}, {"hp", 10}, {"hpMax", 0}, {"exp", 0.0}, {"expNext", 0.0}, {"score", 0}}},
        {"player2", {{"level", 0}, {"hp", 10}, {"hpMax", 0}, {"exp", 0.0}, {"expNext", 0.0}, {"score", 0}}},
        {"upperWeapon", {{"enabled", false}, {"level", 0}}},
        {"lowerWeapon", {{"enabled", false}, {"level", 0}}},
        {"continueGame", false},
        {"typeOfBullet", 0}};

    /// Open file to save default data
    std::ofstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to save default data!" << std::endl;
        return;
    }

    /// Write default data to file
    file << defaultData.dump(4);
}

/**
 * @brief Helper function to read JSON data from a file.
 *
 * @param fileName The name of the file.
 * @return json The JSON data.
 */
json readJsonFromFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to read data!" << std::endl;
        return json();
    }
    json savedData;
    file >> savedData;
    return savedData;
}

/**
 * @brief Helper function to write JSON data to a file.
 *
 * @param fileName The name of the file.
 * @param savedData The JSON data to write.
 */
void writeJsonToFile(const std::string &fileName, const json &savedData)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to save data!" << std::endl;
        return;
    }
    file << savedData.dump(4);
}

/**
 * @brief Sets the number of players in the saved game data.
 *
 * @param numberOfPlayers The number of players.
 */
void setNumberOfPlayers(int numberOfPlayers)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["numberOfPlayers"] = numberOfPlayers;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the level of player 1 in the saved game data.
 *
 * @param player1Level The level of player 1.
 */
void setPlayer1Level(int player1Level)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["level"] = player1Level;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the HP of player 1 in the saved game data.
 *
 * @param player1Hp The HP of player 1.
 */
void setPlayer1Hp(int player1Hp)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["hp"] = player1Hp;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the maximum HP of player 1 in the saved game data.
 *
 * @param player1HpMax The maximum HP of player 1.
 */
void setPlayer1HpMax(int player1HpMax)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["hpMax"] = player1HpMax;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the experience points of player 1 in the saved game data.
 *
 * @param player1Exp The experience points of player 1.
 */
void setPlayer1Exp(float player1Exp)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["exp"] = player1Exp;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the next level experience points of player 1 in the saved game data.
 *
 * @param player1ExpNext The next level experience points of player 1.
 */
void setPlayer1ExpNext(float player1ExpNext)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["expNext"] = player1ExpNext;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the score of player 1 in the saved game data.
 *
 * @param player1Score The score of player 1.
 */
void setPlayer1Score(int player1Score)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["score"] = player1Score;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the level of player 2 in the saved game data.
 *
 * @param player2Level The level of player 2.
 */
void setPlayer2Level(int player2Level)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["level"] = player2Level;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the HP of player 2 in the saved game data.
 *
 * @param player2Hp The HP of player 2.
 */
void setPlayer2Hp(int player2Hp)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["hp"] = player2Hp;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the maximum HP of player 2 in the saved game data.
 *
 * @param player2HpMax The maximum HP of player 2.
 */
void setPlayer2HpMax(int player2HpMax)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["hpMax"] = player2HpMax;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the experience points of player 2 in the saved game data.
 *
 * @param player2Exp The experience points of player 2.
 */
void setPlayer2Exp(float player2Exp)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["exp"] = player2Exp;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the next level experience points of player 2 in the saved game data.
 *
 * @param player2ExpNext The next level experience points of player 2.
 */
void setPlayer2ExpNext(float player2ExpNext)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["expNext"] = player2ExpNext;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the score of player 2 in the saved game data.
 *
 * @param player2Score The score of player 2.
 */
void setPlayer2Score(int player2Score)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["score"] = player2Score;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets whether the upper weapon is enabled in the saved game data.
 *
 * @param upperWeapon Whether the upper weapon is enabled.
 */
void setUpperWeapon(bool upperWeapon)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["upperWeapon"]["enabled"] = upperWeapon;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the level of the upper weapon in the saved game data.
 *
 * @param upperWeaponLevel The level of the upper weapon.
 */
void setUpperWeaponLevel(int upperWeaponLevel)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["upperWeapon"]["level"] = upperWeaponLevel;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets whether the lower weapon is enabled in the saved game data.
 *
 * @param lowerWeapon Whether the lower weapon is enabled.
 */
void setLowerWeapon(bool lowerWeapon)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["lowerWeapon"]["enabled"] = lowerWeapon;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the level of the lower weapon in the saved game data.
 *
 * @param lowerWeaponLevel The level of the lower weapon.
 */
void setLowerWeaponLevel(int lowerWeaponLevel)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["lowerWeapon"]["level"] = lowerWeaponLevel;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets the type of bullet in the saved game data.
 *
 * @param typeOfBullet The type of bullet.
 */
void setTypeOfBullet(int typeOfBullet)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["typeOfBullet"] = typeOfBullet;
    writeJsonToFile("data/savedData.json", savedData);
}

/**
 * @brief Sets whether the game continues from the saved state in the saved game data.
 *
 * @param continueGame Whether the game continues.
 */
void setContinueGame(bool continueGame)
{
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["continueGame"] = continueGame;
    writeJsonToFile("data/savedData.json", savedData);
}