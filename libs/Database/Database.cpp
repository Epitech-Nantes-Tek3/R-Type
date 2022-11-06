/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Database
*/

#include "Database.hpp"
#include <iostream>

namespace database
{
    Database::Database(const std::filesystem::path &fileName) : _db(nullptr), _fileName(fileName) { _open(_fileName); }

    Database::~Database() { sqlite3_close(_db); }

    bool Database::_open(const std::filesystem::path &fileName)
    {
        if (sqlite3_open(fileName.string().c_str(), &_db) != SQLITE_OK) {
            throw std::logic_error(sqlite3_errmsg(_db));
        }
        std::cerr << "Opened database successfully" << std::endl;
        return true;
    }

    bool Database::createUserTable()
    {
        std::string creationQuery = "CREATE TABLE Users("
                                    "UserID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "CreationDate DATETIME NOT NULL,"
                                    "UserName CHAR(50) NOT NULL,"
                                    "Password CHAR(64) NOT NULL,"
                                    "Moderator BIT NOT NULL,"
                                    "Banned BIT NOT NULL,"
                                    "Muted BIT NOT NULL,"
                                    "HighestScore INTEGER UNSIGNED NOT NULL,"
                                    "Deaths INTEGER UNSIGNED NOT NULL,"
                                    "KilledEnemies INTEGER UNSIGNED NOT NULL,"
                                    "GamesPlayed INTEGER UNSIGNED NOT NULL);";
        int reply = sqlite3_exec(_db, creationQuery.c_str(), 0, 0, 0);
        if (reply != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(_db) << std::endl;
        } else {
            std::cerr << "Records created successfully" << std::endl;
        }
        return reply == SQLITE_OK;
    }

    bool Database::addUser(const std::string &userName, const std::string &password, bool moderator, bool banned,
        bool muted, unsigned int highestScore, unsigned int deaths, unsigned int killedEnemies, unsigned int gamePlayed)
    {
        std::string query;
        query
            .append("INSERT INTO Users (CreationDate, UserName, Password, Moderator, Banned, Muted, HighestScore, "
                    "Deaths, KilledEnemies, GamesPlayed) VALUES (DATE(), '")
            .append(userName)
            .append("', '")
            .append(password)
            .append("', ")
            .append(moderator ? "1, " : "0, ")
            .append(banned ? "1, " : "0, ")
            .append(muted ? "1, " : "0, ")
            .append(std::to_string(highestScore).append(", "))
            .append(std::to_string(deaths).append(", "))
            .append(std::to_string(killedEnemies).append(", "))
            .append(std::to_string(gamePlayed))
            .append(");");
        int reply = sqlite3_exec(_db, query.c_str(), 0, 0, 0);
        if (reply != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(_db) << std::endl;
        } else {
            std::cerr << "User succesfully created !" << std::endl;
        }
        return reply == SQLITE_OK;
    }

    /// @brief It takes a pointer to a vector of Row objects, and it fills that vector with
    /// the results of the query
    /// @param data This is a pointer to the data that will be passed to the callback function.
    /// @param argc The number of columns in the result set.
    /// @param argv an array of strings representing fields in the result
    /// @param azColName An array of strings representing column names
    /// @return A vector of rows.
    static int selectUsersCallback(void *data, int argc, char **argv, char **azColName)
    {
        std::vector<Row> *results = static_cast<std::vector<Row> *>(data);
        if (results) {
            Row row;
            for (int i = 0; i < argc; i++) {
                row[std::string(azColName[i])] = (argv[i] ? std::string(argv[i]) : "NULL");
            }
            results->push_back(row);
        }
        return 0;
    }

    std::vector<Row> Database::selectUsers(const std::string specifiedResearch)
    {
        std::vector<Row> results = {};
        std::string query = "SELECT * FROM Users";

        if (specifiedResearch != "") {
            query.append(" WHERE ").append(specifiedResearch);
        }
        query.append(";");
        int reply = sqlite3_exec(_db, query.c_str(), selectUsersCallback, static_cast<void *>(&results), 0);
        if (reply != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(_db) << std::endl;
        }
        return results;
    };

    bool Database::_updateDatabase()
    {
        if (sqlite3_close(_db) != SQLITE_OK) {
            throw std::logic_error(sqlite3_errmsg(_db));
        }
        return _open(_fileName);
    }

    bool Database::updateUsers(const std::string &setValues, const std::string &condition)
    {
        std::string query = "UPDATE Users set ";
        query.append(setValues).append(" WHERE ").append(condition).append(";").append("SELECT * FROM Users;");
        int reply = sqlite3_exec(_db, query.c_str(), 0, 0, 0);
        if (reply != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(_db) << std::endl;
        } else {
            _updateDatabase();
        }
        return reply == SQLITE_OK;
    }
} // namespace database
