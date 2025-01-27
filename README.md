﻿![Pour Decisions Banner](https://raw.githubusercontent.com/Harry-Skerritt/test/refs/heads/main/pd_github_banner.png)

![Static Badge](https://img.shields.io/badge/in_development-green)
![SFML Badge](https://img.shields.io/badge/Built_with-SFML-%238CC445?style=flat&logo=SFML&logoColor=%238CC445)
![C++ Version](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)
![GitHub Release](https://img.shields.io/badge/version-pre_1.0.1-yellow)
![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/Harry-Skerritt/PourDecisions/total)

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Harry-Skerritt/PourDecisions/ci-windows.yml?label=Windows)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Harry-Skerritt/PourDecisions/ci-linux.yml?label=Linux)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Harry-Skerritt/PourDecisions/ci-macos.yml?label=MacOS)


# A Spinwheel based drinking game!
***Spin, Sip and See what happens!***
**Full Version Coming 2025**

--- 

### **🔞 Please Note 🔞** 

**By downloading and playing this game you are acknowledging that you are over the legal drinking age in your territory, and understand this is game is not for minors**

**This game does not encourage excessive drinking, and you should drink responsibly**

**This game also does not *require* the consumption of alcohol to play**

Contact Email: contact.pourdecisions.game@gmail.com

---

## About Pour Decisions
Pour Decisions is a spinwheel based drinking game for 3-8 players. The idea of the game is players take it in turns to spin a wheel which will give them a card from a set of predefined categories, if they do the card they will be awarded points! If they cant, they must spin the forfeit wheel!

***Note:*** This game is best played in 1920x1080 at fullscreen!

[Game Credits](https://harry-skerritt.github.io/PourDecisions/)

### Features
- Available for Windows. (MacOS and Linux coming later)
- Support for 3-8 Players
- Has 56 default cards across 7 categories and 15 default forfeits!
	- Categories Include:
		- Truth
		- Dare
		- Memory
		- Challenges
		- Group
		- NSFW (Toggleable)
		- Handicap
- Supports the ability to import your own custom cards and forfeits (coming soon) please read [here](https://github.com/Harry-Skerritt/PourDecisions/tree/dev?tab=readme-ov-file#adding-custom-cardsforfeits) for how to do this
- The amount of points needed to win is customisable within the settings page

### Rules
- The order you input players is the order of play
- Everyone needs something to drink
- Cards are worth 2 points, Group cards are worth 1. If you forfeit a card you get 1 point, unless its a group card then you get 0
- First to X points wins
- Regardless of how many people reach the winning point value, the first one to get it will be declared the winner

### Game Play Information
- The game is for 3 - 8 people
- Player names are inputted on the  player setup screen, you can click a name to remove them
- Spin the wheel to get a card, if you 
do the card, you click pass and are awarded points.  If you don’t, you click forfeit and spin for a forfeit card
- If a card requires something to be done within 
a time limit, you will need to use a stopwatch to keep time. - If you fail to complete within the time, its an automatic forfeit

⚠️***Currently in Pre-Release***⚠️


## Screenshots of the Game
![Home Screen](https://raw.githubusercontent.com/Harry-Skerritt/PourDecisions/refs/heads/dev/screenshots/pd-home-screenshot.png)
This is the main screen of the game, which provides an options menu allowing for the adjustment of audio levels, aswell as game and video settings.

![Player Setup](https://raw.githubusercontent.com/Harry-Skerritt/PourDecisions/refs/heads/dev/screenshots/pd-playerselect-screenshot.png)
This is the player setup screen where all player information can be entered prior to the start of the game

![Main Game](https://raw.githubusercontent.com/Harry-Skerritt/PourDecisions/refs/heads/dev/screenshots/pd-maingame-screenshot.png)
This is the main game, featuring the spinwheel front and centre as well as a list of the players, their points and who's turn it currently is.

![Card](https://raw.githubusercontent.com/Harry-Skerritt/PourDecisions/refs/heads/dev/screenshots/pd-card-screenshot.png)
This is an example of what the cards look like!

![Forfeit Spinner](https://raw.githubusercontent.com/Harry-Skerritt/PourDecisions/refs/heads/dev/screenshots/pd-forfeitscreenshot.png)
And finally the forfeit spinwheel!


## How to download
**Currently In Pre-Release. Full Release: 2025**

The game can either be directly downloaded [here](https://harry-skerritt.itch.io/pour-decisions) on Itch.io,
or can be compiled into an installer from GitHub

The game comes packaged with an installer so should install like any other window application

## Update Roadmap
### Before leaving pre-release 
- All the cards and forfeits will be updated as the current ones are mostly placeholders
- Bug Fixes

### After Pre-Release
- Custom card functionality
- More platform releases


## Adding custom cards/forfeits
**This functionality is coming soon**

To add your own cards/forfeits you need to create a **.json** file, it can be store anywhere but its content must follow the following format:

![Custom JSON Format](https://raw.githubusercontent.com/Harry-Skerritt/PourDecisions/refs/heads/dev/screenshots/customjson.png)

Some things to note:
- The "content-name" **must** remain as "custom"
- Whilst the "card-color" can be changed, for best visuals it is recommened that it is not
- "card-info" **must not** be changed
- On the "card-count" line "your card count" will need to be replaced with however many custom cards you have added
- "cards" **must** remain as "cards", but everything within the [] (the array) can be changed, and is where the text for your cards can be added
- "forfeit-info" **must not** be changed
- On the "forfeit-count" line "your forfeit count" will need to be replaced with however many custom forfeits you have added
- Similar to "cards", "forefeits" **must** remain as "forfeits", but everything within the [] (the array) can be changed, and is where your custom forfeits can be added

### If you are unfamilliar with JSON then you can read about JSON arrays here: 
[Json Arrays](https://www.microfocus.com/documentation/silk-performer/205/en/silkperformer-205-webhelp-en/GUID-0847DE13-2A2F-44F2-A6E7-214CD703BF84.html)

### Alternativly a sample file is located here: [custom.json](https://github.com/Harry-Skerritt/PourDecisions/blob/dev/custom.json)
 


