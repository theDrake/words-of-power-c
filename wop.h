/******************************************************************************
   Filename: wop.h

     Author: David C. Drake (www.davidcdrake.com)

Description: Header file for the text-based fantasy RPG "Words of Power."
******************************************************************************/

#ifndef WOP_H
#define WOP_H

#include <stdio.h>  /* printf, scanf                                         */
#include <stdlib.h> /* srand, rand                                           */
#include <time.h>   /* time                                                  */
#include <ctype.h>  /* toupper, isalnum                                      */
#include <string.h> /* strlen, strcpy, strcmp                                */

#define DEBUG 1
#define ERROR_MESSAGE printf("Error: line %d\n", __LINE__); FlushInput();

#define BOOL  int
#define FALSE 0
#define TRUE  1

#define FAILURE 0
#define SUCCESS 1

#define STR_LEN 100

  /* Maximum number of enemies per battle.                                   */
#define MAX_ENEMIES 100

  /* Maximum number of targets per spell.                                    */
#define MAX_TARGETS (MAX_ENEMIES * 2)

  /* To evaluate the player's progress with regard to game secrets.          */
#define TOTAL_SECRETS 200

  /* Maximum number of menu options.                                         */
#define MAX_OPTIONS 100

  /* Maximum number of travel options.                                       */
#define MAX_DESTINATIONS 20

  /* Default stats, representative of an average adult human.                */
#define DEFAULT_HP               30
#define DEFAULT_PHYSICAL_POWER   10
#define DEFAULT_PHYSICAL_DEFENSE 10
#define DEFAULT_MENTAL_POWER     10
#define DEFAULT_MENTAL_DEFENSE   10
#define DEFAULT_SPEED            5
#define DEFAULT_EXP              10

  /* Standard prices and price modifiers for goods and services.             */
#define STD_LANG_FEE    50
#define STD_WORD_FEE    100
#define FRIEND_MODIFIER 0.8
#define ENEMY_MODIFIER  1.5

  /* The amount of experience earned for completing the easiest missions.    */
#define STD_MISSION_EXP 25

  /* The amount of experience needed to level-up.                            */
#define EXP_PER_LEVEL           100
#define HP_LEVEL_UP_VALUE       RandomInt(5, 10)
#define PHYSICAL_LEVEL_UP_VALUE RandomInt(0, 2)
#define MENTAL_LEVEL_UP_VALUE   RandomInt(0, 2)

  /* Values for different kinds of "souls."                                  */
#define EXTREMELY_EVIL -30
#define VERY_EVIL      -15
#define EVIL           -5
#define NEUTRAL        0
#define GOOD           5
#define VERY_GOOD      15
#define EXTREMELY_GOOD 30

  /* Values for important relationship thresholds.                           */
#define HOSTILE_ENEMY -10
#define BAD_ENEMY     -5
#define ENEMY         -1
#define INDIFFERENT   0
#define FRIEND        1
#define GOOD_FRIEND   5
#define GREAT_FRIEND  10

  /* Maximum number of Words allowed in a single spell.                      */
#define MAX_SPELL_LEN 8

enum WordID {WORD_OF_AIR, WORD_OF_WATER, WORD_OF_EARTH, WORD_OF_FIRE,
  WORD_OF_BODY, WORD_OF_MIND, WORD_OF_FLORA, WORD_OF_FAUNA, WORD_OF_LIGHT,
  WORD_OF_DARKNESS, WORD_OF_HEALTH, WORD_OF_SICKNESS, WORD_OF_LIFE,
  WORD_OF_DEATH, WORD_OF_HOLINESS, WORD_OF_EVIL, WORD_OF_GIVING,
  WORD_OF_TAKING, WORD_OF_INCREASE, WORD_OF_DECREASE, WORD_OF_BALANCE,
  WORD_OF_SHIELDING, WORD_OF_WAVES, WORD_OF_FOCUS, WORD_OF_TIME, WORD_OF_VOID,
  TOTAL_WORD_IDS};
enum LanguageID {IMPERIAL, ANCIENT_IMPERIAL, ELVISH, ANCIENT_ELVISH, DWARVISH,
  ANCIENT_DWARVISH, GNOMISH, ANCIENT_GNOMISH, MER, ANCIENT_MER, GESH, VENTARRI,
  ANCIENT_VENTARRI, TOTAL_LANGUAGE_IDS};
enum LocationID {ILLARUM_ENTRANCE, ILLARUM_MARKET, ILLARUM_INN, ILLARUM_SCHOOL,
  ILLARUM_TEMPLE, ILLARUM_PALACE, ILLARUM_PRISON, VENTARRIS_ENTRANCE,
  VENTARRIS_MARKET, VENTARRIS_INN, VENTARRIS_SCHOOL, VENTARRIS_TEMPLE,
  VENTARRIS_PALACE, VENTARRIS_PRISON, VENTARRIS_DOCKS, PLAINS_NORTH,
  NORTHERN_FARMS, BRILL_OUTSKIRTS, BRILL_MARKET, BRILL_INN, BRILL_DOCKS,
  PLAINS_SOUTH, SOUTHERN_FARMS, SILENT_SAGE_HOME, FOREST, DRUIDS_GROVE,
  HERMIT_HUT, WYNNFAER_ENTRANCE, WYNNFAER_PLAZA, WYNNFAER_PALACE,
  MOUNTAINS, GESHTAL, TORR_ENTRANCE, TORR_MARKET, TORR_SCHOOL, TORR_TEMPLE,
  TORR_THRONE_ROOM, TORR_MINE, TORR_VAULT, TORR_PRISON, GUGGENHOLM_ENTRANCE,
  GUGGENHOLM_MAIN, GUGGENHOLM_MINE, SWAMP, NECROMANCERS_CIRCLE,
  ISHTARR_ENTRANCE, ISHTARR_EAST_WING, ISHTARR_WEST_WING,
  ISHTARR_CENTRAL_TOWER, ISHTARR_DUNGEON, SHORE_NE, SHORE_EAST, SHORE_SE,
  OCEAN_SURFACE, OCEAN_SHALLOW, OCEAN_DEEP, OCEAN_TRENCH, QUELACENTUS_ENTRANCE,
  QUELACENTUS_PLAZA, QUELACENTUS_TEMPLE, QUELACENTUS_PALACE,
  TOTAL_LOCATION_IDS};
enum GameCharID {PLAYER, HUMAN, SOLDIER, KNIGHT, WIZARD, MERCHANT, INNKEEPER,
  NOBLEMAN, FISHERMAN, SAILOR, SERVANT, SLAVE, THIEF, PRISONER, FARMER,
  ILLARUM_PRIEST, ILLARUM_HIGH_PRIEST, ILLARUM_KING, COURT_WIZARD,
  WIZARD_OF_ELEMENTS, ARCHWIZARD_OF_ELEMENTS, DUMMY, WIZARD_OF_MIND,
  ARCHWIZARD_OF_MIND, VENTARRIS_PRIEST, VENTARRIS_HIGH_PRIEST, VENTARRIS_KING,
  BARBARIAN, BARBARIAN_WARRIOR, BARBARIAN_SHAMAN, BARBARIAN_CHIEFTAIN, ELF,
  ELF_LOREMASTER, DWARF, DWARF_MERCHANT, DWARF_MINER, DWARF_GUARDIAN,
  DWARF_LOREMASTER, DWARF_PRIEST, DWARF_HIGH_PRIEST, DWARF_KING, GNOME,
  GNOME_MINER, DRUID, ARCHDRUID, RAT, BAT, GIANT_SPIDER, WOLF, BEAR, BIRD,
  TREANT, CENTAUR, FISH, SHARK, WHALE, GIANT_SQUID, MERFOLK,
  MERFOLK_SOLDIER, MERFOLK_PRIESTESS, MERFOLK_HIGH_PRIESTESS, MERFOLK_QUEEN,
  NECROMANCER, ARCHNECROMANCER, LICH, ZOMBIE, SKELETAL_KNIGHT, GOBLIN, ORC,
  OGRE, TROLL, GIANT, DRAGON, FIRE_ELEMENTAL, WATER_ELEMENTAL,
  EARTH_ELEMENTAL, AIR_ELEMENTAL, THE_DARK_RECLUSE, THE_HERMIT, THE_ANGLER,
  THE_WANDERING_MONK, THE_SILENT_SAGE, TOTAL_GC_IDS};
enum GameCharStatusID {INVISIBLE, FLYING, WATER_BREATHING, FIRE_FORM,
  EARTH_FORM, WIND_FORM, WATER_FORM, ASLEEP, PARALYZED, POISONED, SILENCED,
  IN_COMBAT, SUMMONED, INANIMATE, TOTAL_STATUS_IDS};
enum ItemID {FOOD, HEALING_POTION, GLOWING_MUSHROOM, TOTAL_ITEM_IDS};
enum MissionID {ELEMENTS1, ELEMENTS2, ELEMENTS3, ELEMENTS4, ELEMENTS5, MIND1,
  MIND2, MIND3, MIND4, MIND5, DRUID1, DRUID2, DRUID3, DRUID4, DRUID5, ELF1,
  ELF2, ELF3, ELF4, ELF5, DWARF1, DWARF2, DWARF3, DWARF4, DWARF5, GNOME1,
  GNOME2, GNOME3, GNOME4, GNOME5, NECROMANCER1, NECROMANCER2, NECROMANCER3,
  NECROMANCER4, NECROMANCER5, LICH1, LICH2, LICH3, LICH4, LICH5,
  ILLARUM_PRIEST1, ILLARUM_PRIEST2, ILLARUM_PRIEST3, ILLARUM_PRIEST4,
  ILLARUM_PRIEST5, VENTARRIS_PRIEST1, VENTARRIS_PRIEST2, VENTARRIS_PRIEST3,
  VENTARRIS_PRIEST4, VENTARRIS_PRIEST5, GESH1, GESH2, GESH3, GESH4, GESH5,
  MERFOLK1, MERFOLK2, MERFOLK3, MERFOLK4, MERFOLK5, FARMER1, FARMER2, FARMER3,
  FARMER4, FARMER5, BRILL1, BRILL2, BRILL3, BRILL4, BRILL5, ILLARUM_KING1,
  ILLARUM_KING2, ILLARUM_KING3, ILLARUM_KING4, ILLARUM_KING5, VENTARRIS_KING1,
  VENTARRIS_KING2, VENTARRIS_KING3, VENTARRIS_KING4, VENTARRIS_KING5,
  TOTAL_MISSION_IDS};
enum MissionStatus {CLOSED, OPEN, COMPLETED, TERMINATED, FAILED};
enum GroupID {ELEMENTS_GUILD, MIND_GUILD, THE_DRUIDS, THE_ELVES, THE_DWARVES,
  THE_GNOMES, THE_MERFOLK, THE_BARBARIANS, PRIESTS_OF_ILLARUM,
  PRIESTS_OF_VENTARRIS, PRIESTS_OF_TORR, THE_NECROMANCERS, THE_FARMERS,
  TOTAL_GROUP_IDS};
enum Knowledge {UNKNOWN, PARTIALLY_KNOWN, KNOWN};
enum Capitalization {LOWERCASE, UPPERCASE};

typedef struct GAME_CHARACTER
{
  int ID;
  BOOL unique;                  /* FALSE for generic humans, goblins, etc.   */
  char name[STR_LEN + 1];       /* Capitalized, even for generic characters. */
  char descriptor[STR_LEN + 1]; /* Brief and generic description.            */
  int level;
  int experience;    /* "Total exp." for player; "exp. obtainable" for NPCs. */
  int maxHP;
  int currentHP;
  int physicalPower;
  int physicalDefense;
  int speed;
  int mentalPower;
  int mentalDefense;
  int soul;          /* May range from EXTREMELY_EVIL to EXTREMELY_GOOD.     */
  enum Knowledge words[TOTAL_WORD_IDS];  /* Records known Words of Power.    */
  enum Knowledge languages[TOTAL_LANGUAGE_IDS];
  int conversations; /* Number of conversations held with player.            */
  BOOL knowsPlayer;
  BOOL knownToPlayer;
  int relationship;  /* Relative to player: FRIEND, ENEMY, INDIFFERENT, etc. */
  int status[TOTAL_STATUS_IDS];
  int gold;
  int inventory[TOTAL_ITEM_IDS]; /* Includes equipped items.                 */
  int equippedItems[TOTAL_ITEM_IDS];
  int locationID;
  struct GAME_CHARACTER *summonedCreature;  /* Only one allowed at a time.   */
  struct GAME_CHARACTER *next;   /* For forming linked lists.                */
}GameCharacter;

typedef struct LOCATION
{
  int ID;
  char name[STR_LEN + 1];
  BOOL hidden;  /* If TRUE, special effort is required to find the location. */
  int visits;   /* Number of times player has visited the location.          */
  int searches; /* Number of times player has searched the location.         */
  struct GAME_CHARACTER *inhabitants;  /* Linked list of local NPCs.         */
}Location;

  /* Function prototypes.                                                    */
void MainMenu(void);
void PrintStandardOptions(void);
int CreateWorld(void);
int DestroyWorld(void);
void QuitMenu(void);
void HelpMenu(void);
int RandomInt(int low, int high);
int RandomBool(void);
char GetCharInput(char *c);
int GetIntInput(int *i, int low, int high);
char *GetStrInput(char *string, int n);
BOOL StrContains(char string[], char c);
void FlushInput(void);
int InitializeLocation(Location *location, int idNum);
BOOL InVentarrisTerritory(Location *location);
GameCharacter *AddInhabitant(Location *location, int idNum);
int AddInhabitants(Location *location, int idNum, int amount);
GameCharacter *FindInhabitant(int idNum);
int MoveInhabitant(GameCharacter *inhabitant, int destinationID);
int RemoveInhabitant(Location *location, GameCharacter *inhabitant);
int DeleteInhabitant(Location *location, GameCharacter *inhabitant);
int VisibleInhabitants(Location *location);
int MovementMenu(void);
int MovePlayer(int destinationID);
int SearchLocation(Location *location);
void DescribeSituation(void);
int InitializeCharacter(GameCharacter *pGC, int idNum, Location *location);
int AddCompanion(GameCharacter *companion);
int RemoveCompanion(GameCharacter *companion);
int DeleteCompanion(GameCharacter *companion);
GameCharacter *AddSummonedCreature(GameCharacter *summoner, int idNum);
int DeleteCreatureSummonedBy(GameCharacter *summoner);
int DisplayCharacterData(GameCharacter *pGC);
int PrintSoulDescription(GameCharacter *pGC);
BOOL IsGood(GameCharacter *pGC);
BOOL IsEvil(GameCharacter *pGC);
BOOL IsNeutral(GameCharacter *pGC);
int NumberOfLanguagesKnown(GameCharacter *pGC);
int NumberOfWordsKnown(GameCharacter *pGC);
int PrintNameDefinite(GameCharacter *pGC, Capitalization cap);
int PrintNameIndefinite(GameCharacter *pGC, Capitalization cap);
int PrintNamePlural(GameCharacter *pGC, Capitalization cap);
void StatusCheck(void);
void UpdateVisibleGameCharCounter(void);
GameCharacter *GetTarget(void);
BOOL IsTargeted(GameCharacter *pGC, GameCharacter *targets[]);
int HealGameCharacter(GameCharacter *pGC, int amount);
int DamageGameCharacter(GameCharacter *pGC, int amount);
int GainExperience(int amount);
void LevelUp(void);
void LearnLanguage(int langID);
void LearnWord(int wordID);
int AddEnemy(GameCharacter *pGC);
int AddRandomEnemy(Location *location);
int RemoveEnemy(GameCharacter *pGC);
int DeleteEnemy(GameCharacter *pGC);
int NumberOfEnemies(void);
int VisibleEnemies(void);
int Combat(void);
void PrintCombatStatus(GameCharacter *pGC);
int EnemyAI(int index);
int AttackMenu(void);
int Attack(GameCharacter *attacker, GameCharacter *defender);
BOOL WillingToFight(GameCharacter *pGC);
BOOL WillingToFlee(GameCharacter *pGC);
BOOL WillingToHelp(GameCharacter *pGC);
int TalkMenu(void);
int Dialogue(GameCharacter *pGC);
int LanguageLearningDialogue(GameCharacter *pGC);
int WordLearningDialogue(GameCharacter *pGC);
int Transaction(GameCharacter *merchant, int price);
char *LanguageName(int idNum);
int SpellMenu(void);
int CastSpell(GameCharacter *spellcaster,
              char *spell,
              GameCharacter *gcTargets[]);
BOOL CanCastBeneficialSpells(GameCharacter *pGC);
int PrintKnownWords(void);
char *Word(int idNum);
char *WordStartingWith(char firstLetter);
char *WordName(int idNum);
int WordID(char firstLetter);
BOOL IsSpellcaster(GameCharacter *pGC);
int ItemMenu(void);
int UseItem(GameCharacter *pGC, int idNum);
int PrintInventory(GameCharacter *pGC);
int PrintItemName(int idNum);
int PrintItemNamePlural(int idNum);
int GiveGold(GameCharacter *giver, GameCharacter *receiver, int amount);
int GiveItem(GameCharacter *giver, GameCharacter *receiver, int itemID);
int GiveItems(GameCharacter *giver,
              GameCharacter *receiver,
              int itemID,
              int amount);

  /* Global variables.                                                       */
Location *world[TOTAL_LOCATION_IDS];      /* Pointers to all game locations. */
BOOL worldExists;   /* Indicates whether a game world exists in memory.      */
BOOL quit;          /* Indicates a player's desire to quit the game.         */
int secretsFound;   /* Number of "secrets" discovered by the player.         */
GameCharacter player;                     /* Player character.               */
GameCharacter *enemyNPCs[MAX_ENEMIES];    /* For linked lists of enemies.    */
int missions[TOTAL_MISSION_IDS];          /* To track the player's progress. */
int allegiances[TOTAL_GROUP_IDS];         /* Player relationships w/groups.  */
int kills[TOTAL_GC_IDS];                  /* Number of each GC type killed.  */
int visibleGameCharCounter[TOTAL_GC_IDS]; /* Number of each GC type visible. */
BOOL gcDescribed[TOTAL_GC_IDS]; /* To prevent duplicate descriptions of GCs. */

#endif
