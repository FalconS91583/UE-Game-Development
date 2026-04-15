# UE-Game-Development

## Falcon Spike - Personal Big Project
### Falcon Spike (Work in Progress)

Fast-paced single-player looter shooter with RPG progression systems, focused on responsive movement, modular combat, and scalable gameplay architecture.

### Core Features

#### Movement System
Implemented a modular locomotion system enabling smooth transitions between multiple movement states, including:
- walking, running, sliding, and wall jumping  
- advanced wall jump mechanics allowing directional rebounds  
- grappling hook system for dynamic traversal and vertical gameplay  

The system is designed around a shared momentum pipeline to ensure fluid and responsive player control.

#### Combat System
Developed a modular, data-driven weapon system inspired by modern FPS games:
- multiple weapon types  
- procedural recoil and spread systems  
- ADS (aim-down-sights) mechanics  
- extensible architecture for adding new weapon behaviors  

#### RPG & Progression Systems
Designed and implemented layered RPG mechanics:
- expanded stat system inspired by Souls-like games  
- elemental damage types: fire, ice, lightning, acid, radiation, and magnetism  
- status effects integrated into the combat pipeline  
- skill tree system for upgrading abilities and enhancing playstyles  

### Additional progression includes:
- item-based stat modifiers  
- special effects that influence survivability and combat outcomes  
- crafting system to give purpose to looting and resource management  

#### AI & Enemies
Created multiple enemy archetypes with increasing gameplay complexity:
- melee, ranged, and boss enemies  
- multiple variants per enemy type (e.g. aggressive melee, fast attacker, hybrid ranged units)  
- bosses featuring multi-phase encounters with evolving abilities  

#### UI System
Implemented a responsive, real-time UI system providing:
- combat feedback  
- player stats and status effects  
- inventory and progression interfaces  

#### Technical Highlights
- Built in Unreal Engine 5 using C++ and Blueprints  
- Strong focus on modular and scalable system design  
- Heavy use of 3D math for movement and gameplay mechanics  

#### Status
Project is currently in active development with additional features and systems planned.


## Enemy Learning System
Implemented an adaptive AI system that records gameplay situations and adjusts enemy behavior based on past outcomes.

Enemies can learn from player interactions (e.g. detecting attacks from behind cover) and modify future responses using stored experience data.

## Dragons League
MOBA-style gameplay prototype featuring hero evolution system with dynamic form switching (Human → Dragon), modular abilities, and combat targeting.

## GAS Top-Down RPG Game
GAS Top-Down RPG — Self-developed UE5 top-down RPG built independently, with occasional reference to Stephen Ulibarri's GAS course when facing architectural challenges. Implements full RPG systems using Gameplay Ability System: primary/secondary attributes, offensive and passive spells, enemy AI with Behavior Trees, XP and leveling system, and multiplayer-ready architecture. Written with SOLID principles and ~50% C++ / ~50% Blueprints split — mirroring the approach used in shipped AAA titles.

## Item_Inventory_System
Implemented an complex item and inventory system that allows you to change your armor and weapons with visual feedback also boosting character stats with responsive UI

## Basic Projects 
Four complete games built while following the Epic Games-collaborated course by GameDev.tv. Covers C++ fundamentals, OOP, AI behaviour, Enhanced Input System, UI, and animation in Unreal Engine 5. Projects: Obstacle Assault, Dungeon Escape, Battle Blaster, Shooter Sam.
