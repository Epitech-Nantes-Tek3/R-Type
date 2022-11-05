/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Database
*/

#pragma once

extern "C"
{
#include <sqlite3.h>
}
#include <filesystem>
#include <vector>
#include <unordered_map>

/// @brief An unordered map to store a row of the result of a query
/// The key is the name of the column and the value is the field returned by the query
typedef std::unordered_map<std::string, std::string> Row;

/// @brief A Database objet used to manage a SQLITE database
class Database {
  public:
    /// @brief It creates a Database object and it opens a database file and stores the database handle in the _db
    /// member variable
    /// @param fileName The path to the database file.
    Database(const std::filesystem::path &fileName);

    ///@brief The destructor for the Database class closes the database connection
    ~Database();

    /// @brief It creates the user table in the database if it doesn't exist
    /// @return A boolean value.
    bool createUserTable();

    /// @brief It creates a new user in the database
    /// @param userName The user's name
    /// @param password The password of the user.
    /// @param moderator if the user is a moderator
    /// @param banned if the user is banned or not
    /// @param muted if the user is muted or not
    /// @param highestScore The highest score the user has ever achieved.
    /// @param deaths number of times the player died
    /// @param killedEnemies number of enemies killed by the user
    /// @param gamePlayed number of games played by the user
    /// @return A boolean value.
    bool addUser(const std::string &userName, const std::string &password, bool moderator, bool banned, bool muted,
        unsigned int highestScore = 0, unsigned int deaths = 0, unsigned int killedEnemies = 0,
        unsigned int gamePlayed = 0);

    /// @brief The function in order to search users in the database
    /// @param specifiedResearch The WHERE clause of the SQL query.
    /// @return A vector of rows.
    std::vector<Row> selectUsers(const std::string specifiedResearch = "");

    /// @brief It takes a string of values to set and a string of conditions to update the database with, and returns
    /// true if the update was successful
    /// @param setValues The values you want to change.
    /// @param condition The condition to be met for the update to occur.
    /// @return The return value is a boolean value.
    bool updateUsers(const std::string &setValue, const std::string &condition);

  private:
  protected:
  private:
    /// @brief the database
    sqlite3 *_db;

    /// @brief The path to the database file
    std::filesystem::path _fileName;

    /// @brief It opens a database file and returns true if it succeeds
    /// @param fileName The name of the file to open.
    /// @return A boolean value.
    bool _open(const std::filesystem::path &fileName);

    /// @biref It closes the database, then reopens it
    /// @return A boolean value.
    bool _updateDatabase();
};
