#include "../../include/Resources/SaveData.hpp"
#include <fstream>
#include <iostream>

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

void loadSavedData(
    int &numberOfPlayers,
    int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
    int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
    bool &upperWeapon, int &upperWeaponLevel,
    bool &lowerWeapon, int &lowerWeaponLevel,
    int &typeOfBullet)
{
    std::ifstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to load data!" << std::endl;
        return;
    }

    json savedData;
    file >> savedData;

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

void saveDefaultData()
{
    std::ifstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to load data!" << std::endl;
        return;
    }

    json savedData;
    file >> savedData;
    file.close();

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

    std::ofstream outFile("data/savedData.json");
    if (!outFile.is_open())
    {
        std::cerr << "Could not open the file to save data!" << std::endl;
        return;
    }

    outFile << savedData.dump(4);
    std::cout << "Default data saved!" << std::endl;
}

void eraceSavedData()
{

    json defaultData = {
        {"numberOfPlayers", 1},
        {"player1", {{"level", 0}, {"hp", 10}, {"hpMax", 0}, {"exp", 0.0}, {"expNext", 0.0}, {"score", 0}}},
        {"player2", {{"level", 0}, {"hp", 10}, {"hpMax", 0}, {"exp", 0.0}, {"expNext", 0.0}, {"score", 0}}},
        {"upperWeapon", {{"enabled", false}, {"level", 0}}},
        {"lowerWeapon", {{"enabled", false}, {"level", 0}}},
        {"continueGame", false},
        {"typeOfBullet", 0}};

    std::ofstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file to save default data!" << std::endl;
        return;
    }

    file << defaultData.dump(4);
}

// Helper function to read the JSON data from the file
json readJsonFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open the file to read data!" << std::endl;
        return json();
    }
    json savedData;
    file >> savedData;
    return savedData;
}

// Helper function to write the JSON data to the file
void writeJsonToFile(const std::string& fileName, const json& savedData) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open the file to save data!" << std::endl;
        return;
    }
    file << savedData.dump(4);
}

void setNumberOfPlayers(int numberOfPlayers) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["numberOfPlayers"] = numberOfPlayers;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer1Level(int player1Level) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["level"] = player1Level;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer1Hp(int player1Hp) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["hp"] = player1Hp;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer1HpMax(int player1HpMax) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["hpMax"] = player1HpMax;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer1Exp(float player1Exp) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["exp"] = player1Exp;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer1ExpNext(float player1ExpNext) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["expNext"] = player1ExpNext;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer1Score(int player1Score) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player1"]["score"] = player1Score;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer2Level(int player2Level) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["level"] = player2Level;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer2Hp(int player2Hp) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["hp"] = player2Hp;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer2HpMax(int player2HpMax) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["hpMax"] = player2HpMax;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer2Exp(float player2Exp) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["exp"] = player2Exp;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer2ExpNext(float player2ExpNext) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["expNext"] = player2ExpNext;
    writeJsonToFile("data/savedData.json", savedData);
}

void setPlayer2Score(int player2Score) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["player2"]["score"] = player2Score;
    writeJsonToFile("data/savedData.json", savedData);
}

void setUpperWeapon(bool upperWeapon) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["upperWeapon"]["enabled"] = upperWeapon;
    writeJsonToFile("data/savedData.json", savedData);
}

void setUpperWeaponLevel(int upperWeaponLevel) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["upperWeapon"]["level"] = upperWeaponLevel;
    writeJsonToFile("data/savedData.json", savedData);
}

void setLowerWeapon(bool lowerWeapon) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["lowerWeapon"]["enabled"] = lowerWeapon;
    writeJsonToFile("data/savedData.json", savedData);
}

void setLowerWeaponLevel(int lowerWeaponLevel) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["lowerWeapon"]["level"] = lowerWeaponLevel;
    writeJsonToFile("data/savedData.json", savedData);
}

void setTypeOfBullet(int typeOfBullet) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["typeOfBullet"] = typeOfBullet;
    writeJsonToFile("data/savedData.json", savedData);
}

void setContinueGame(bool continueGame) {
    json savedData = readJsonFromFile("data/savedData.json");
    savedData["continueGame"] = continueGame;
    writeJsonToFile("data/savedData.json", savedData);
}