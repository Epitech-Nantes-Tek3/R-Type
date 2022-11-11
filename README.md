# **R-Type**

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
 ![GitHub Actions](https://img.shields.io/badge/github%20actions-%232671E5.svg?style=for-the-badge&logo=githubactions&logoColor=white) ![CodeCov](https://img.shields.io/badge/codecov-%23ff0077.svg?style=for-the-badge&logo=codecov&logoColor=white)

***

## **Table of Contents**

- [**Table of Contents**](#table-of-contents)
- [**Introduction**](#introduction)
  - [**Supported Platforms**](#supported-platforms)
- [**The Game**](#the-game)
  - [**Story**](#story)
- [**How to play ?**](#how-to-play-)
  - [**Prerequisites**](#prerequisites)
  - [**Launch the game**](#launch-the-game)
- [**For developers**](#for-developers)
  - [**Build the program**](#build-the-program)
  - [**Testing program**](#testing-program)
  - [**Documentation**](#documentation)
- [**Thank for reading**](#thank-for-reading)
- [**Authors**](#authors)

***

## **Introduction**

The goal of the Epitech R-Type project is to implement a multithreaded server and a graphical client for a game called R-Type, using an engine of our own design.

The project is composed of two parts: the server and the client, both in C++.

It uses three libraries:

- SFML: The library used to display.
- Boost: The library used to manage communication, threads and processes.
- SQLite3: The library used to manage the storage.

### **Supported Platforms**

The R-Type project is supported on Windows AND Linux !!

***

## **The Game**

### **Story**

...And that’s why we are there.

This story begins in 2442, at a time when humans successfully survived the 4th world war. But the consequences were terrible, every place on Earth was radioactive. To save humanity, geniuses from all over the world started to think together, to conclude at the same point: they need to move.

After several studies about various places in space, every tiny bit of ground was hostile to earthlings. When the light of hope started to decline, five geniuses came out of nowhere to bring a new future for humanity. We called them by their team's name: “On est que 4 ;)”.

First, we have Lucas, a genius of networking, followed by Quentin master of ECS (Engine for Cruise Ship). Thomas is the team protector and Tom is the team’s pathfinder. Last one but not least, Nathan the... the one who is telling this story for you, dear reader.

Together they found a new planet, a new home, a place to live for humanity, the only one who was welcoming for weakened humans: Zelta. After spending weeks building the best ships for the team, they were ready to go. But none of them were expecting what was about to happen.

<br>

While making their way to Zelta, our teams started to cross a new specie, like an alien who is shooting at a regular frequency but moving randomly. Beating them was not the hard part, learning that there are potentially others form of intelligence in the space was.

All the members of the team gather to be prepared for the aliens. Each one of them started to feel fear, but they managed to stay focused until a new alien appeared. A huge form, blazing into space was rushing to them. Tom spaceship successfully takes the first damage but could not take all the others. Every member started crying in their ships with the first loss of the mission.

But they did not have time to cry, another wave was coming. Two groups of four mobs, shooting ice spikes through the space were aiming for the team. The only way of beating them was to shoot back but a shield was necessary. Thanks to Thomas, the other members could rest for a bit. Even if the team eliminated every alien, they could not celebrate because only three of them were left.

The following minutes were horribly calm, until the ECS master could not control his ship anymore. He was falling into void for no reason. Suddenly, huge flashes were coming from everywhere, with electrics alien attacking and rushing the team. We were hiding behind our falling mate to take down every piece of the worst species we have found.

From 5 strong men, they were reduced to 2 survivors, who were hoping to find a land somewhere. Making their way through space, hoping that every dangerous species has been killed.

And that is why we are there. In front of our survivors, the despair, a boss appears. You need to help them, tell them how to move and when to shoot. You need to beat this boss for the sake of humanity! Good luck! 

***

## **How to play ?**

### **Prerequisites**

To build our R-Type project, you will need CMake 3.17.0 Compiler, C++ 20 and Conan.

### **Launch the game**

***

## **For developers**

### **Build the program**

On Linux :

- You may execute the script `build.sh` or the following commands :

```bash
    cmake -B ./build -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build
```

On Windows :

- You may execute the script `build.bat` or the following commands :

```bash
    mkdir build
    cd build
    conan install .. --build=missing  -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
    cd ..
    cmake -B ./build -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build
    copy ".\Debug\r-type_server.exe" .
    copy ".\Debug\r-type_client.exe" .
    copy ".\Debug\r-type_room.exe" .
    copy ".\Debug\r-type_admin_panel.exe" .
```

### **Testing program**

The tests are available on Linux.
You may can test the code executing the script `build_tests.sh` or using with the following commands.

```bash
    rm -rf ./build
    cmake -B ./build -DCMAKE_BUILD_TYPE=Debug -DTESTING=ON
    cmake --build ./build
    cd ./build
    ctest --ouput-on-failure
```

### **Documentation**

The code documentation is available [here](). <br>
Additional documentation such as the protocols used or the database can be found [here](https://amazing-partridge-567.notion.site/R-Type-Documentations-On-est-que-4-de59851ea5e64808a3c3d9f145a960a9).

***

## **Thank for reading**

Feel free to read the `CONTRIBUTING.md`.

Do not hesitate to contact any member for any questions or remarks. You can click on each following name.

## **Authors**

<table>
    <tbody>
        <tr>
            <td align="center"><a href="https://github.com/TomDUVAL-MAHE"><img src="https://avatars.githubusercontent.com/u/72017980?v=4" width="100px;" alt="Tom Duval-Mahe"/><br/><sub><b>Tom Duval-Mahe</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/ZQUEMA/"><img src="https://avatars.githubusercontent.com/u/56249749?s=96&v=4" width="100px;" alt="ZQUEMA"/><br/><sub><b>Quentin Camilleri</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/osvegn/"><img src="https://avatars.githubusercontent.com/u/72011124?v=4" width="100px;" alt="osvegn"/><br/><sub><b>Thomas Prud'homme</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/31Nathan/"><img src="https://avatars.githubusercontent.com/u/72010794?v=4" width="100px;" alt="31Nathan"/><br/><sub><b>Nathan Rousseau</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/LucasTesnier/"><img src="https://avatars.githubusercontent.com/u/72015360?v=4" width="100px;" alt="LucasTesnier"/><br/><sub><b>Lucas Tesnier</b></sub></a><br/></td>
        </tr>
    </tbody>
</table>
