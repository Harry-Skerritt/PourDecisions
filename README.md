![Pour Decisions Banner](https://raw.githubusercontent.com/Harry-Skerritt/test/refs/heads/main/pd_github_banner.png)

![Static Badge](https://img.shields.io/badge/in_development-green)
![Static Badge](https://img.shields.io/badge/Built_With-SFML-orange)
![GitHub Release](https://img.shields.io/github/v/release/Harry-Skerritt/PourDecisions)
![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/Harry-Skerritt/PourDecisions/total)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Harry-Skerritt/PourDecisions/ci-windows.yml?label=Windows)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Harry-Skerritt/PourDecisions/ci-macos.yml?label=MacOS)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Harry-Skerritt/PourDecisions/ci-linux.yml?label=Linux)


# A Spinwheel based drinking game!
***Spin, Sip and See what happens!***
**Coming 2025**

--- 

### **🔞 Please Note 🔞** 

**By downloading and playing this game you are acknowledging that you are over the legal drinking age in your territory, and understand this is game is not for minors**

**This game does not encourage excessive drinking, and you should drink responsibly**

**This game also does not *require* the consumption of alcohol to play**

Contact Email: example@example.com

---

## About Pour Decisions
Pour Decisions is a spinwheel based drinking game for 3-8 players. The idea of the game is players take it in turns to spin a wheel which will give them a card from a set of predefined categories, if they do the card they will be awarded points! If they cant, they must spin the forfeit wheel!

***Note:*** This game is best played in 1920x1080 at fullscreen!

## More Info To Come Soon!

### Features
- Soon Avaiable for Windows. (MacOS and Linux coming later)
- Support for 3-8 Players
- Has 56 default cards and 15 default forfeits!
- Supports the ability to import your own custom cards and forfeits (coming soon) please read [here]() for how to do this
- The amount of points needed to win is customisable within the settings page

## Screenshots of the Game
Coming Soon

## How to download
**Not Available Yet. Planned Release: 2025**

The game can either be directly downloaded [here]() on GitHub, or [here](https://harry-skerritt.itch.io/pour-decisions) on Itch.io.

The game comes packaged with an installer so should install like any other window application



## Adding custom cards/forfeits
**This functionality is coming soon**

To add your own cards/forfeits you need to create a **.json** file, it can be store anywhere but its content must follow the following format:

![Custom JSON Format](https://raw.githubusercontent.com/Harry-Skerritt/test/refs/heads/main/image.png)

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

### Alternativly a sample file is located here: [custom.json]()
 


