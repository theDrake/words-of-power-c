/******************************************************************************
   Filename: wop.h

     Author: David C. Drake (http://davidcdrake.com)

Description: Header file for the text-based fantasy RPG "Words of Power."
******************************************************************************/

#ifndef WOP_H_
#define WOP_H_

#include <stdio.h>  // printf, scanf
#include <stdlib.h>  // srand, rand
#include <time.h>  // time
#include <ctype.h>  // toupper, isalnum
#include <string.h>  // strlen, strcpy, strcmp
#include <stdbool.h>  // bool, true, false

/******************************************************************************
  Constants
******************************************************************************/

// Error checking:
#define DEBUG   false
#define FAILURE false
#define SUCCESS true
#define PRINT_ERROR_MESSAGE printf("ERROR: %s, line %d\n", __FILE__, __LINE__); FlushInput()

// String lengths and other max. values:
#define SHORT_STR_LEN    50
#define LONG_STR_LEN     500
#define MAX_LINE_LENGTH  80  // including new line character
#define MAX_ENEMIES      100  // per battle
#define MAX_TARGETS      (MAX_ENEMIES * 2)  // per spell
#define TOTAL_SECRETS    200  // to evaluate player progress
#define MAX_MENU_OPTIONS 100
#define MAX_DESTINATIONS 20

// Default stats, representative of an average adult human:
#define DEFAULT_HP               30
#define DEFAULT_PHYSICAL_POWER   10
#define DEFAULT_PHYSICAL_DEFENSE 10
#define DEFAULT_MENTAL_POWER     10
#define DEFAULT_MENTAL_DEFENSE   10
#define DEFAULT_SPEED            5
#define DEFAULT_EXP              10

// Standard prices and price modifiers for goods and services:
#define STD_LANG_FEE    50
#define STD_WORD_FEE    100
#define FRIEND_MODIFIER 0.8
#define ENEMY_MODIFIER  1.5

// Amount of experience earned for completing the easiest missions:
#define STD_MISSION_EXP 25

// Amount of experience needed to level-up:
#define EXP_PER_LEVEL           100
#define HP_LEVEL_UP_VALUE       RandomInt(5, 10)
#define PHYSICAL_LEVEL_UP_VALUE RandomInt(0, 2)
#define MENTAL_LEVEL_UP_VALUE   RandomInt(0, 2)

// Values for different kinds of "souls":
#define EXTREMELY_EVIL -30
#define VERY_EVIL      -15
#define EVIL           -5
#define NEUTRAL        0
#define GOOD           5
#define VERY_GOOD      15
#define EXTREMELY_GOOD 30

// Values for important relationship thresholds:
#define HOSTILE_ENEMY -10
#define BAD_ENEMY     -5
#define ENEMY         -1
#define INDIFFERENT   0
#define FRIEND        1
#define GOOD_FRIEND   5
#define GREAT_FRIEND  10

// Maximum number of Words allowed in a single spell:
#define MAX_SPELL_LEN 8

/******************************************************************************
  Enumerations
******************************************************************************/

enum WordID {
  WORD_OF_AIR,
  WORD_OF_WATER,
  WORD_OF_EARTH,
  WORD_OF_FIRE,
  WORD_OF_BODY,
  WORD_OF_MIND,
  WORD_OF_FLORA,
  WORD_OF_FAUNA,
  WORD_OF_LIGHT,
  WORD_OF_DARKNESS,
  WORD_OF_HEALTH,
  WORD_OF_SICKNESS,
  WORD_OF_LIFE,
  WORD_OF_DEATH,
  WORD_OF_HOLINESS,
  WORD_OF_EVIL,
  WORD_OF_GIVING,
  WORD_OF_TAKING,
  WORD_OF_INCREASE,
  WORD_OF_DECREASE,
  WORD_OF_BALANCE,
  WORD_OF_SHIELDING,
  WORD_OF_WAVES,
  WORD_OF_FOCUS,
  WORD_OF_TIME,
  WORD_OF_VOID,
  NUM_WORD_IDS
};

enum LanguageID {
  IMPERIAL,
  ANCIENT_IMPERIAL,
  ELVISH,
  ANCIENT_ELVISH,
  DWARVISH,
  ANCIENT_DWARVISH,
  GNOMISH,
  ANCIENT_GNOMISH,
  MER,
  ANCIENT_MER,
  GESH,
  VENTARRI,
  ANCIENT_VENTARRI,
  NUM_LANGUAGE_IDS
};

enum LocationID {
  ILLARUM_ENTRANCE,
  ILLARUM_MARKET,
  ILLARUM_INN,
  ILLARUM_SCHOOL,
  ILLARUM_TEMPLE,
  ILLARUM_PALACE,
  ILLARUM_PRISON,
  VENTARRIS_ENTRANCE,
  VENTARRIS_MARKET,
  VENTARRIS_INN,
  VENTARRIS_SCHOOL,
  VENTARRIS_TEMPLE,
  VENTARRIS_PALACE,
  VENTARRIS_PRISON,
  VENTARRIS_DOCKS,
  PLAINS_NORTH,
  NORTHERN_FARMS,
  BRILL_OUTSKIRTS,
  BRILL_MARKET,
  BRILL_INN,
  BRILL_DOCKS,
  PLAINS_SOUTH,
  SOUTHERN_FARMS,
  SILENT_SAGE_HOME,
  FOREST,
  DRUIDS_GROVE,
  HERMIT_HUT,
  WYNNFAER_ENTRANCE,
  WYNNFAER_PLAZA,
  WYNNFAER_PALACE,
  MOUNTAINS, GESHTAL,
  TORR_ENTRANCE,
  TORR_MARKET,
  TORR_SCHOOL,
  TORR_TEMPLE,
  TORR_THRONE_ROOM,
  TORR_MINE,
  TORR_VAULT,
  TORR_PRISON,
  GUGGENHOLM_ENTRANCE,
  GUGGENHOLM_MAIN,
  GUGGENHOLM_MINE,
  SWAMP,
  NECROMANCERS_CIRCLE,
  ISHTARR_ENTRANCE,
  ISHTARR_EAST_WING,
  ISHTARR_WEST_WING,
  ISHTARR_CENTRAL_TOWER,
  ISHTARR_DUNGEON,
  SHORE_NE,
  SHORE_EAST,
  SHORE_SE,
  OCEAN_SURFACE,
  OCEAN_SHALLOW,
  OCEAN_DEEP,
  OCEAN_TRENCH,
  QUELACENTUS_ENTRANCE,
  QUELACENTUS_PLAZA,
  QUELACENTUS_TEMPLE,
  QUELACENTUS_PALACE,
  NUM_LOCATION_IDS
};

enum GameCharID {
  PLAYER,
  HUMAN,
  SOLDIER,
  KNIGHT,
  WIZARD,
  PEASANT,
  MERCHANT,
  INNKEEPER,
  NOBLEMAN,
  FISHERMAN,
  SAILOR,
  SERVANT,
  SLAVE,
  THIEF,
  PRISONER,
  FARMER,
  ILLARUM_PRIEST,
  ILLARUM_HIGH_PRIEST,
  ILLARUM_KING,
  COURT_WIZARD,
  WIZARD_OF_ELEMENTS,
  ARCHWIZARD_OF_ELEMENTS,
  DUMMY,
  WIZARD_OF_MIND,
  ARCHWIZARD_OF_MIND,
  VENTARRIS_PRIEST,
  VENTARRIS_HIGH_PRIEST,
  VENTARRIS_KING,
  BARBARIAN,
  BARBARIAN_WARRIOR,
  BARBARIAN_SHAMAN,
  BARBARIAN_CHIEFTAIN,
  ELF,
  ELF_LOREMASTER,
  DWARF,
  DWARF_MERCHANT,
  DWARF_MINER,
  DWARF_GUARDIAN,
  DWARF_LOREMASTER,
  DWARF_PRIEST,
  DWARF_HIGH_PRIEST,
  DWARF_KING,
  GNOME,
  GNOME_MINER,
  DRUID,
  ARCHDRUID,
  RAT,
  BAT,
  GIANT_SPIDER,
  WOLF,
  BEAR,
  BIRD,
  TREANT,
  CENTAUR,
  FISH,
  SHARK,
  WHALE,
  GIANT_SQUID,
  MERFOLK,
  MERFOLK_SOLDIER,
  MERFOLK_PRIESTESS,
  MERFOLK_HIGH_PRIESTESS,
  MERFOLK_QUEEN,
  NECROMANCER,
  ARCHNECROMANCER,
  LICH,
  ZOMBIE,
  SKELETAL_KNIGHT,
  GOBLIN,
  ORC,
  OGRE,
  TROLL,
  GIANT,
  DRAGON,
  FIRE_ELEMENTAL,
  WATER_ELEMENTAL,
  EARTH_ELEMENTAL,
  AIR_ELEMENTAL,
  THE_DARK_RECLUSE,
  THE_HERMIT,
  THE_ANGLER,
  THE_WANDERING_MONK,
  THE_SILENT_SAGE,
  NUM_GC_IDS
};

enum GameCharStatusID {
  INVISIBLE,
  FLYING,
  WATER_BREATHING,
  FIRE_FORM,
  EARTH_FORM,
  WIND_FORM,
  WATER_FORM,
  ASLEEP,
  PARALYZED,
  POISONED,
  SILENCED,
  IN_COMBAT,
  SUMMONED,
  INANIMATE,
  NUM_STATUS_IDS
};

enum ItemID {
  FOOD,
  HEALING_POTION,
  GLOWING_MUSHROOM,
  NUM_ITEM_IDS
};

enum MissionID {
  ELEMENTS1,
  ELEMENTS2,
  ELEMENTS3,
  ELEMENTS4,
  ELEMENTS5,
  MIND1,
  MIND2,
  MIND3,
  MIND4,
  MIND5,
  DRUID1,
  DRUID2,
  DRUID3,
  DRUID4,
  DRUID5,
  ELF1,
  ELF2,
  ELF3,
  ELF4,
  ELF5,
  DWARF1,
  DWARF2,
  DWARF3,
  DWARF4,
  DWARF5,
  GNOME1,
  GNOME2,
  GNOME3,
  GNOME4,
  GNOME5,
  NECROMANCER1,
  NECROMANCER2,
  NECROMANCER3,
  NECROMANCER4,
  NECROMANCER5,
  LICH1,
  LICH2,
  LICH3,
  LICH4,
  LICH5,
  ILLARUM_PRIEST1,
  ILLARUM_PRIEST2,
  ILLARUM_PRIEST3,
  ILLARUM_PRIEST4,
  ILLARUM_PRIEST5,
  VENTARRIS_PRIEST1,
  VENTARRIS_PRIEST2,
  VENTARRIS_PRIEST3,
  VENTARRIS_PRIEST4,
  VENTARRIS_PRIEST5,
  GESH1,
  GESH2,
  GESH3,
  GESH4,
  GESH5,
  MERFOLK1,
  MERFOLK2,
  MERFOLK3,
  MERFOLK4,
  MERFOLK5,
  FARMER1,
  FARMER2,
  FARMER3,
  FARMER4,
  FARMER5,
  BRILL1,
  BRILL2,
  BRILL3,
  BRILL4,
  BRILL5,
  ILLARUM_KING1,
  ILLARUM_KING2,
  ILLARUM_KING3,
  ILLARUM_KING4,
  ILLARUM_KING5,
  VENTARRIS_KING1,
  VENTARRIS_KING2,
  VENTARRIS_KING3,
  VENTARRIS_KING4,
  VENTARRIS_KING5,
  NUM_MISSION_IDS
};

enum MissionStatus {
  CLOSED,
  OPEN,
  COMPLETED,
  TERMINATED,
  FAILED
};

enum GroupID {
  ELEMENTS_GUILD,
  MIND_GUILD,
  THE_DRUIDS,
  THE_ELVES,
  THE_DWARVES,
  THE_GNOMES,
  THE_MERFOLK,
  THE_BARBARIANS,
  PRIESTS_OF_ILLARUM,
  PRIESTS_OF_VENTARRIS,
  PRIESTS_OF_TORR,
  THE_NECROMANCERS,
  THE_FARMERS,
  NUM_GROUP_IDS
};

enum Knowledge {
  UNKNOWN,
  PARTIALLY_KNOWN,
  KNOWN
};

/******************************************************************************
  Structures
******************************************************************************/

typedef struct GameCharacter {
  int ID;
  bool unique;  // False for generic NPCs.
  char name[SHORT_STR_LEN + 1];  // Capitalized, even for generic NPCs.
  char descriptor[SHORT_STR_LEN + 1];  // Brief generic description.
  int level;
  int experience;  // "Total exp." for player, "exp. obtainable" for NPCs.
  int maxHP;
  int currentHP;
  int physicalPower;
  int physicalDefense;
  int speed;
  int mentalPower;
  int mentalDefense;
  int soul;  // Ranges from EXTREMELY_EVIL to EXTREMELY_GOOD.
  enum Knowledge words[NUM_WORD_IDS];  // Records known Words of Power.
  enum Knowledge languages[NUM_LANGUAGE_IDS];
  int conversations;  // Number of conversations held with player.
  bool knowsPlayer;
  bool knownToPlayer;
  int relationship;  // Relative to player: FRIEND, ENEMY, INDIFFERENT, etc.
  int status[NUM_STATUS_IDS];
  int gold;
  int inventory[NUM_ITEM_IDS];  // Includes equipped items.
  int equippedItems[NUM_ITEM_IDS];
  int locationID;
  struct GAME_CHARACTER *summonedCreature;  // Only one allowed at a time.
  struct GAME_CHARACTER *next;  // For forming linked lists.
} game_character_t;

typedef struct Location {
  int ID;
  char name[SHORT_STR_LEN + 1];
  bool hidden;  // If true, special effort is required to find the location.
  int visits;  // Number of times player has visited the location.
  int searches;  // Number of times player has searched the location.
  struct GAME_CHARACTER *inhabitants;  // Linked list of local NPCs.
} location_t;

/******************************************************************************
  Global Variables
******************************************************************************/

location_t *world[NUM_LOCATION_IDS];  // Pointers to all game locations.
bool worldExists;  // Indicates whether game world exists in memory.
bool quit;  // Indicates player's desire to quit the game.
int secretsFound;  // Number of "secrets" discovered by the player.
game_character_t player;
game_character_t *enemyNPCs[MAX_ENEMIES];
int missions[NUM_MISSION_IDS];  // To track player progress.
int allegiances[NUM_GROUP_IDS];  // Player's relationships with groups.
int kills[NUM_GC_IDS];  // Number of each GC type killed.
int visibleGameCharCounter[NUM_GC_IDS];  // Number of each GC type visible.
bool gcDescribed[NUM_GC_IDS];  // To prevent duplicate descriptions of GCs.

/******************************************************************************
  Function Prototypes
******************************************************************************/

// Function prototypes for "main.c":
int main(void);
void MainMenu(void);
void PrintStandardOptions(void);
int CreateWorld(void);
int DestroyWorld(void);
bool GetExitConfirmation(void);
void HelpMenu(void);
int RandomInt(int low, int high);
int RandomBool(void);
char GetCharInput(char *c);
int GetIntInput(int *i, int low, int high);
char *GetStrInput(char *str, int n);
void PrintString(char *str);
char *Capitalize(char *str);
char *AllCaps(char *str);
bool StrContains(char *str, char c);
void FlushInput(void);

// Function prototypes for "locations.c":
int InitializeLocation(location_t *location, int idNum);
bool InVentarrisTerritory(location_t *location);
game_character_t *AddInhabitant(location_t *location, int idNum);
int AddInhabitants(location_t *location, int idNum, int amount);
game_character_t *FindInhabitant(int idNum);
int MoveInhabitant(game_character_t *inhabitant, int destinationID);
int RemoveInhabitant(location_t *location, game_character_t *inhabitant);
int DeleteInhabitant(location_t *location, game_character_t *inhabitant);
int VisibleInhabitants(location_t *location);
int MovementMenu(void);
int MovePlayer(int destinationID);
int SearchLocation(location_t *location);
void DescribeSituation(void);

// Function prototypes for "characters.c":
int InitializeCharacter(game_character_t *pGC, int idNum,
                        location_t *location);
int AddCompanion(game_character_t *companion);
int RemoveCompanion(game_character_t *companion);
int DeleteCompanion(game_character_t *companion);
game_character_t *AddSummonedCreature(game_character_t *summoner, int idNum);
int DeleteCreatureSummonedBy(game_character_t *summoner);
int DisplayCharacterData(game_character_t *pGC);
int PrintSoulDescription(game_character_t *pGC);
bool IsGood(game_character_t *pGC);
bool IsEvil(game_character_t *pGC);
bool IsNeutral(game_character_t *pGC);
int NumberOfLanguagesKnown(game_character_t *pGC);
int NumberOfWordsKnown(game_character_t *pGC);
char *GetNameDefinite(game_character_t *pGC);
char *GetNameIndefinite(game_character_t *pGC);
char *GetNamePlural(game_character_t *pGC);
void CheckStatus(void);
void UpdateVisibleGameCharCounter(void);
game_character_t *GetTarget(void);
bool IsTargeted(game_character_t *pGC, game_character_t *targets[]);
int HealGameCharacter(game_character_t *pGC, int amount);
int DamageGameCharacter(game_character_t *pGC, int amount);
int GainExperience(int amount);
void LevelUp(void);
void LearnLanguage(int langID);
void LearnWord(int wordID);

// Function prototypes for "combat.c":
int AddEnemy(game_character_t *pGC);
int AddRandomEnemy(location_t *location);
int RemoveEnemy(game_character_t *pGC);
int DeleteEnemy(game_character_t *pGC);
int NumberOfEnemies(void);
int VisibleEnemies(void);
int Combat(void);
void PrintCombatStatus(game_character_t *pGC);
int EnemyAI(int index);
int AttackMenu(void);
int Attack(game_character_t *attacker, game_character_t *defender);
bool WillingToFight(game_character_t *pGC);
bool WillingToFlee(game_character_t *pGC);
bool WillingToHelp(game_character_t *pGC);

// Function prototypes for "dialogue.c":
int TalkMenu(void);
int Dialogue(game_character_t *pGC);
int LanguageLearningDialogue(game_character_t *pGC);
int WordLearningDialogue(game_character_t *pGC);
double GetPriceModifier(game_character_t *merchant);
int Transaction(game_character_t *merchant, int price);
char *LanguageName(int idNum);

// Function prototypes for "magic.c":
int SpellMenu(void);
int CastSpell(game_character_t *spellcaster, char *spell,
              game_character_t *gcTargets[]);
int Targeted(game_character_t *pGC, game_character_t *gcTargets[]);
bool CanCastBeneficialSpells(game_character_t *pGC);
int PrintKnownWords(void);
char *Word(int idNum);
char *WordStartingWith(char firstLetter);
char *WordName(int idNum);
int WordID(char firstLetter);
bool IsSpellcaster(game_character_t *pGC);

// Function prototypes for "item.c":
int ItemMenu(void);
int UseItem(game_character_t *pGC, int idNum);
int PrintInventory(game_character_t *pGC);
char *GetItemName(int idNum);
char *GetItemNamePlural(int idNum);
int GiveGold(game_character_t *giver, game_character_t *receiver, int amount);
int GiveItem(game_character_t *giver, game_character_t *receiver, int itemID);
int GiveItems(game_character_t *giver, game_character_t *receiver, int itemID,
              int amount);
int ItemValue(int idNum);

#endif  // WOP_H_
