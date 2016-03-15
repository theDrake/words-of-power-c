/******************************************************************************
   Filename: characters.c

     Author: David C. Drake (http://davidcdrake.com)

Description: Functions governing the creation, initialization, and basic
             analysis of game characters for the text-based fantasy RPG "Words
             of Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: InitializeCharacter

Description: Initializes a given game character struct to its default starting
             values.

     Inputs: p_gc     - Pointer to the game characer struct to be initialized.
             type     - Integer representing desired game character type.
             location - The game character's starting location.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int InitializeCharacter(game_character_t *p_gc, int type,
                        location_t *location) {
  int i;
  bool repeat_options;

  // Default stats, representative of an average adult human:
  p_gc->type = type;
  strcpy(p_gc->name, "");
  strcpy(p_gc->descriptor, "");
  p_gc->unique = false;
  p_gc->max_hp = DEFAULT_HP;
  p_gc->hp = DEFAULT_HP;
  p_gc->physical_power = DEFAULT_PHYSICAL_POWER;
  p_gc->physical_defense = DEFAULT_PHYSICAL_DEFENSE;
  p_gc->mental_power = DEFAULT_MENTAL_POWER;
  p_gc->mental_defense = DEFAULT_MENTAL_DEFENSE;
  p_gc->speed = DEFAULT_SPEED;
  p_gc->soul = NEUTRAL;
  p_gc->level = 1;
  p_gc->experience = DEFAULT_EXP;
  p_gc->knows_player = false;
  p_gc->known_to_player = false;
  p_gc->relationship = INDIFFERENT;
  p_gc->conversations = 0;
  for (i = 0; i < NUM_STATUS_TYPES; i++) {
    p_gc->status[i] = false;
  }
  p_gc->gold = 0;
  for (i = 0; i < NUM_ITEM_TYPES; i++) {
    p_gc->inventory[i] = 0;
    p_gc->equipped_items[i] = 0;
  }
  for (i = 0; i < NUM_LANGUAGE_TYPES; i++) {
    p_gc->languages[i] = UNKNOWN;
  }
  for (i = 0; i < NUM_WORD_TYPES; i++) {
    p_gc->words[i] = UNKNOWN;
  }
  p_gc->location = location->id;
  p_gc->summoned_creature = NULL;
  p_gc->next = NULL;

  // Character-specific stats:
  switch (p_gc->type) {
    case PLAYER:
      p_gc->unique = true;
      p_gc->experience = 0;
      p_gc->mental_power *= 2;
      p_gc->mental_defense *= 2;
      p_gc->knows_player = true;
      p_gc->known_to_player = true;
      p_gc->relationship = GREAT_FRIEND;
      p_gc->gold = 10;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->inventory[HEALING_POTION] = 3;
      p_gc->location = ILLARUM_SCHOOL;
      PrintString("You are a wizard who has studied at the city of Illarum's "
                  "School of the Elements for the past five years.\0");
      FlushInput();
      do {
        printf("Choose your name: ");
        GetStrInput(p_gc->name, SHORT_STR_LEN + 1);
        repeat_options = strlen(p_gc->name) < 1;
      }while (repeat_options);
      break;
    case ARCHWIZARD_OF_ELEMENTS:
      strcpy(p_gc->name, "Archememnon");
      strcpy(p_gc->descriptor, "archwizard");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->mental_power *= 10;
      p_gc->mental_defense *= 10;
      p_gc->soul = EVIL;
      p_gc->relationship = GOOD_FRIEND;
      p_gc->knows_player = true;
      p_gc->known_to_player = true;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(100, 200);
      break;
    case WIZARD_OF_ELEMENTS:
      strcpy(p_gc->name, "Wizard of the Elements");
      strcpy(p_gc->descriptor, "wizard");
      p_gc->mental_power *= 2;
      p_gc->mental_defense *= 2;
      p_gc->relationship = GOOD_FRIEND;
      p_gc->knows_player = true;
      p_gc->known_to_player = true;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->level = 2;
      p_gc->experience *= 3;
      p_gc->gold = RandomInt(10, 20);
      break;
    case ILLARUM_PRIEST:
      strcpy(p_gc->name, "Priest");
      strcpy(p_gc->descriptor, "priest");
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 2.5;
      p_gc->soul = EXTREMELY_GOOD;
      p_gc->relationship = FRIEND;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[GESH] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->level = 2;
      p_gc->experience *= 3;
      break;
    case ILLARUM_HIGH_PRIEST:
      strcpy(p_gc->name, "Yemmul");
      strcpy(p_gc->descriptor, "high priest");
      p_gc->unique = true;
      p_gc->max_hp *= 2.5;
      p_gc->hp *= 2.5;
      p_gc->mental_power *= 5;
      p_gc->mental_defense *= 15;
      p_gc->soul = EXTREMELY_GOOD;
      p_gc->relationship = FRIEND;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[GESH] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      break;
    case DUMMY:
      strcpy(p_gc->name, "Dummy");
      strcpy(p_gc->descriptor, "stuffed dummy");
      p_gc->max_hp = 1;
      p_gc->hp = 1;
      p_gc->physical_power = 0;
      p_gc->physical_defense = 1;
      p_gc->mental_power = 0;
      p_gc->mental_defense = 0;
      p_gc->experience = 1;
      p_gc->status[INANIMATE] = true;
      break;
    case HUMAN:
      strcpy(p_gc->name, "Peasant");
      strcpy(p_gc->descriptor, "peasant");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->gold = RandomInt(0, 5);
      break;
    case THIEF:
      strcpy(p_gc->name, "Thief");
      strcpy(p_gc->descriptor, "thief");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->gold = RandomInt(5, 10);
      break;
    case SOLDIER:
      strcpy(p_gc->name, "Soldier");
      strcpy(p_gc->descriptor, "soldier");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->gold = RandomInt(1, 5);
      break;
    case MERCHANT:
      strcpy(p_gc->name, "Merchant");
      strcpy(p_gc->descriptor, "merchant");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->gold = RandomInt(25, 50);
      break;
    case INNKEEPER:
      strcpy(p_gc->name, "Innkeeper");
      strcpy(p_gc->descriptor, "innkeeper");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->gold = RandomInt(10, 30);
      break;
    case ILLARUM_KING:
      strcpy(p_gc->name, "King of Illarum");
      strcpy(p_gc->descriptor, "king");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 2;
      p_gc->mental_defense *= 2;
      p_gc->soul = GOOD;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(100, 500);
      break;
    case COURT_WIZARD:
      strcpy(p_gc->name, "Court Wizard");
      strcpy(p_gc->descriptor, "wizard");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->mental_power *= 3;
      p_gc->mental_defense *= 3;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      for (i = 0; i < NUM_WORD_TYPES; i++) {
        p_gc->words[i] = KNOWN;
      }
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(50, 100);
      break;
    case NOBLEMAN:
      strcpy(p_gc->name, "Nobleman");
      strcpy(p_gc->descriptor, "nobleman");
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->gold = RandomInt(50, 100);
      break;
    case KNIGHT:
      strcpy(p_gc->name, "Knight");
      strcpy(p_gc->descriptor, "knight");
      p_gc->max_hp *= 3;
      p_gc->hp *= 3;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 3;
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->level = 10;
      p_gc->experience *= 5;
      p_gc->gold = RandomInt(10, 30);
      break;
    case SERVANT:
      strcpy(p_gc->name, "Servant");
      strcpy(p_gc->descriptor, "servant");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      break;
    case PRISONER:
      strcpy(p_gc->name, "Prisoner");
      strcpy(p_gc->descriptor, "prisoner");
      p_gc->max_hp /= 2;
      p_gc->hp /= 2;
      p_gc->physical_power /= 2;
      p_gc->physical_defense /= 2;
      p_gc->mental_power /= 2;
      p_gc->mental_defense /= 2;
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->experience /= 2;
      break;
    case SLAVE:
      strcpy(p_gc->name, "Slave");
      strcpy(p_gc->descriptor, "slave");
      p_gc->max_hp /= 1.5;
      p_gc->hp /= 1.5;
      p_gc->physical_power /= 1.5;
      p_gc->physical_defense /= 1.5;
      p_gc->mental_power /= 1.5;
      p_gc->mental_defense /= 1.5;
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->experience /= 1.5;
      break;
    case SAILOR:
      strcpy(p_gc->name, "Sailor");
      strcpy(p_gc->descriptor, "sailor");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      break;
    case ARCHWIZARD_OF_MIND:
      strcpy(p_gc->name, "Kaeloss");
      strcpy(p_gc->descriptor, "archwizard");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->mental_power *= 10;
      p_gc->mental_defense *= 10;
      p_gc->soul = VERY_EVIL;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(200, 300);
      break;
    case WIZARD_OF_MIND:
      strcpy(p_gc->name, "Wizard of Mind");
      strcpy(p_gc->descriptor, "wizard");
      p_gc->mental_power *= 2;
      p_gc->mental_defense *= 2;
      p_gc->soul = EVIL;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->level = 2;
      p_gc->experience *= 3;
      p_gc->gold = RandomInt(20, 30);
      break;
    case VENTARRIS_PRIEST:
      strcpy(p_gc->name, "Priest");
      strcpy(p_gc->descriptor, "priest");
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 2.5;
      p_gc->soul = GOOD;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->level = 2;
      p_gc->experience *= 3;
      break;
    case VENTARRIS_HIGH_PRIEST:
      strcpy(p_gc->name, "Graelmach");
      strcpy(p_gc->descriptor, "high priest");
      p_gc->unique = true;
      p_gc->max_hp *= 2.5;
      p_gc->hp *= 2.5;
      p_gc->mental_power *= 5;
      p_gc->mental_defense *= 15;
      p_gc->soul = VERY_GOOD;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->words[WORD_OF_EVIL] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      break;
    case VENTARRIS_KING:
      strcpy(p_gc->name, "King Estvann");
      strcpy(p_gc->descriptor, "king");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 2;
      p_gc->mental_defense *= 2;
      p_gc->soul = VERY_EVIL;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(250, 500);
      break;
    case FARMER:
      strcpy(p_gc->name, "Farmer");
      strcpy(p_gc->descriptor, "farmer");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->soul = GOOD;
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->gold = RandomInt(0, 5);
      break;
    case FISHERMAN:
      strcpy(p_gc->name, "Fisherman");
      strcpy(p_gc->descriptor, "fisherman");
      if (InVentarrisTerritory(location)) {
        p_gc->languages[VENTARRI] = KNOWN;
      } else {
        p_gc->languages[IMPERIAL] = KNOWN;
      }
      p_gc->gold = RandomInt(0, 5);
      break;
    case DRUID:
      strcpy(p_gc->name, "Druid");
      strcpy(p_gc->descriptor, "druid");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->mental_power *= 2;
      p_gc->mental_defense *= 2.5;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[GESH] = KNOWN;
      p_gc->languages[ELVISH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->level = 10;
      p_gc->experience *= 3;
      break;
    case ARCHDRUID:
      strcpy(p_gc->name, "Pann");
      strcpy(p_gc->descriptor, "archdruid");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->mental_power *= 10;
      p_gc->mental_defense *= 10;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[GESH] = KNOWN;
      p_gc->languages[ELVISH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      break;
    case ELF:
      strcpy(p_gc->name, "Elf");
      strcpy(p_gc->descriptor, "elf");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 3;
      p_gc->mental_defense *= 3;
      p_gc->soul = GOOD;
      p_gc->languages[ELVISH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->experience *= 3.5;
      break;
    case ELF_LOREMASTER:
      strcpy(p_gc->name, "Elven Loremaster");
      strcpy(p_gc->descriptor, "elven loremaster");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 5;
      p_gc->mental_defense *= 5;
      p_gc->soul = GOOD;
      p_gc->languages[ELVISH] = KNOWN;
      p_gc->languages[ANCIENT_ELVISH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->words[WORD_OF_BALANCE] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      break;
    case BARBARIAN:
      strcpy(p_gc->name, "Babarian");
      strcpy(p_gc->descriptor, "barbarian");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->languages[GESH] = KNOWN;
      p_gc->experience *= 1.2;
      break;
    case BARBARIAN_WARRIOR:
      strcpy(p_gc->name, "Barbarian Warrior");
      strcpy(p_gc->descriptor, "barbarian warrior");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 3;
      p_gc->languages[GESH] = KNOWN;
      p_gc->level = 8;
      p_gc->experience *= 2.5;
      break;
    case BARBARIAN_SHAMAN:
      strcpy(p_gc->name, "Barbarian Shaman");
      strcpy(p_gc->descriptor, "barbarian shaman");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 2;
      p_gc->mental_defense *= 2;
      p_gc->languages[GESH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->level = 10;
      p_gc->experience *= 3;
      break;
    case BARBARIAN_CHIEFTAIN:
      strcpy(p_gc->name, "Telth");
      strcpy(p_gc->descriptor, "barbarian chieftain");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 5;
      p_gc->physical_defense *= 5;
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 1.5;
      p_gc->languages[GESH] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      break;
    case DWARF:
      strcpy(p_gc->name, "Dwarf");
      strcpy(p_gc->descriptor, "dwarf");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->experience *= 1.2;
      p_gc->gold = RandomInt(5, 10);
      break;
    case DWARF_GUARDIAN:
      strcpy(p_gc->name, "Dwarven Guardian");
      strcpy(p_gc->descriptor, "dwarven guardian");
      p_gc->max_hp *= 3;
      p_gc->hp *= 3;
      p_gc->physical_power *= 4;
      p_gc->physical_defense *= 4;
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 1.5;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->level = 10;
      p_gc->experience *= 5;
      p_gc->gold = RandomInt(10, 30);
      break;
    case DWARF_MERCHANT:
      strcpy(p_gc->name, "Dwarven Merchant");
      strcpy(p_gc->descriptor, "dwarven merchant");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->experience *= 1.2;
      p_gc->gold = RandomInt(50, 100);
      break;
    case DWARF_LOREMASTER:
      strcpy(p_gc->name, "Dwarven Loremaster");
      strcpy(p_gc->descriptor, "dwarven loremaster");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 5;
      p_gc->mental_defense *= 5;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->languages[ANCIENT_DWARVISH] = KNOWN;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->words[WORD_OF_FOCUS] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(10, 20);
      break;
    case DWARF_PRIEST:
      strcpy(p_gc->name, "Dwarven Priest");
      strcpy(p_gc->descriptor, "dwarven priest");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 3;
      p_gc->mental_defense *= 3;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->languages[ANCIENT_DWARVISH] = KNOWN;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->words[WORD_OF_FOCUS] = KNOWN;
      p_gc->level = 10;
      p_gc->experience *= 3;
      p_gc->gold = RandomInt(10, 20);
      break;
    case DWARF_HIGH_PRIEST:
      strcpy(p_gc->name, "Dwarven High Priest");
      strcpy(p_gc->descriptor, "dwarven high priest");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 5;
      p_gc->mental_defense *= 5;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->languages[ANCIENT_DWARVISH] = KNOWN;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->words[WORD_OF_FOCUS] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(10, 20);
      break;
    case DWARF_KING:
      strcpy(p_gc->name, "King Beoklast");
      strcpy(p_gc->descriptor, "dwarven king");
      p_gc->max_hp *= 4;
      p_gc->hp *= 4;
      p_gc->physical_power *= 5;
      p_gc->physical_defense *= 5;
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 2;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->languages[ANCIENT_DWARVISH] = KNOWN;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 12;
      p_gc->gold = RandomInt(500, 1000);
      break;
    case DWARF_MINER:
      strcpy(p_gc->name, "Dwarven Miner");
      strcpy(p_gc->descriptor, "dwarven miner");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 1.5;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->experience *= 1.5;
      p_gc->gold = RandomInt(10, 20);
      break;
    case DRAGON:
      strcpy(p_gc->name, "Dragon");
      strcpy(p_gc->descriptor, "dragon");
      p_gc->max_hp *= 50;
      p_gc->hp *= 50;
      p_gc->physical_power *= 50;
      p_gc->physical_defense *= 50;
      p_gc->mental_power *= 10;
      p_gc->mental_defense *= 5;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->languages[ANCIENT_DWARVISH] = KNOWN;
      p_gc->languages[ANCIENT_GNOMISH] = KNOWN;
      p_gc->languages[ANCIENT_ELVISH] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->level = 30;
      p_gc->experience *= 100;
      break;
    case GNOME:
      strcpy(p_gc->name, "Gnome");
      strcpy(p_gc->descriptor, "gnome");
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 1.5;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->gold = RandomInt(10, 20);
      break;
    case GNOME_MINER:
      strcpy(p_gc->name, "Gnomish Miner");
      strcpy(p_gc->descriptor, "gnomish miner");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 1.5;
      p_gc->mental_defense *= 1.5;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->experience *= 1.2;
      p_gc->gold = RandomInt(10, 20);
      break;
    case NECROMANCER:
      strcpy(p_gc->name, "Necromancer");
      strcpy(p_gc->descriptor, "necromancer");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->mental_power *= 3;
      p_gc->mental_defense *= 2;
      p_gc->relationship = ENEMY;
      p_gc->soul = EXTREMELY_EVIL;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_EVIL] = KNOWN;
      p_gc->level = 10;
      p_gc->experience *= 3.5;
      p_gc->gold = RandomInt(25, 50);
      break;
    case ARCHNECROMANCER:
      strcpy(p_gc->name, "Kraathmot");
      strcpy(p_gc->descriptor, "archnecromancer");
      p_gc->max_hp *= 3;
      p_gc->hp *= 3;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 5;
      p_gc->mental_defense *= 4;
      p_gc->relationship = ENEMY;
      p_gc->soul = EXTREMELY_EVIL;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_EVIL] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      p_gc->gold = RandomInt(50, 100);
      break;
    case LICH:
      strcpy(p_gc->name, "Velroth");
      strcpy(p_gc->descriptor, "lich");
      p_gc->unique = true;
      p_gc->max_hp *= 5;
      p_gc->hp *= 5;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 3;
      p_gc->mental_power *= 15;
      p_gc->mental_defense *= 15;
      p_gc->soul = EXTREMELY_EVIL;
      p_gc->relationship = ENEMY;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_EVIL] = KNOWN;
      p_gc->level = 30;
      p_gc->experience *= 30;
      p_gc->gold = RandomInt(1000, 2000);
      break;
    case ZOMBIE:
      strcpy(p_gc->name, "Zombie");
      strcpy(p_gc->descriptor, "zombie");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 2;
      p_gc->mental_power = 0;
      p_gc->mental_defense = 0;
      p_gc->soul = EVIL;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->experience *= 2;
      break;
    case SKELETAL_KNIGHT:
      strcpy(p_gc->name, "Skeletal Knight");
      strcpy(p_gc->descriptor, "skeletal knight");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power = 0;
      p_gc->mental_defense = 0;
      p_gc->soul = EVIL;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->level = 10;
      p_gc->experience *= 5;
      break;
    case RAT:
      strcpy(p_gc->name, "Rat");
      strcpy(p_gc->descriptor, "large rat");
      p_gc->max_hp /= 2;
      p_gc->hp /= 2;
      p_gc->physical_power /= 5;
      p_gc->physical_defense /= 5;
      p_gc->mental_power /= 10;
      p_gc->mental_defense /= 10;
      p_gc->relationship = ENEMY;
      p_gc->experience /= 10;
      break;
    case SHARK:
      strcpy(p_gc->name, "Shark");
      strcpy(p_gc->descriptor, "shark");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power /= 10;
      p_gc->mental_defense /= 10;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->experience *= 2.5;
      break;
    case WOLF:
      strcpy(p_gc->name, "Wolf");
      strcpy(p_gc->descriptor, "wolf");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power /= 10;
      p_gc->mental_defense /= 10;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->experience *= 2.5;
      break;
    case BEAR:
      strcpy(p_gc->name, "Bear");
      strcpy(p_gc->descriptor, "bear");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power /= 10;
      p_gc->mental_defense /= 10;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->experience *= 2.5;
      break;
    case GOBLIN:
      strcpy(p_gc->name, "Goblin");
      strcpy(p_gc->descriptor, "goblin");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power /= 10;
      p_gc->mental_defense /= 10;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->experience *= 2.5;
      break;
    case ORC:
      strcpy(p_gc->name, "Orc");
      strcpy(p_gc->descriptor, "orc");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power /= 10;
      p_gc->mental_defense /= 10;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->experience *= 2.5;
      break;
    case GIANT_SQUID:
      strcpy(p_gc->name, "Giant Squid");
      strcpy(p_gc->descriptor, "giant squid");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 2;
      p_gc->mental_power /= 10;
      p_gc->mental_defense /= 10;
      p_gc->relationship = HOSTILE_ENEMY;
      p_gc->experience *= 2.5;
      break;
    case MERFOLK:
      strcpy(p_gc->name, "Merfolk");
      strcpy(p_gc->descriptor, "merfolk");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_defense *= 2;
      p_gc->relationship = ENEMY;
      p_gc->languages[MER] = KNOWN;
      p_gc->experience *= 1.2;
      break;
    case MERFOLK_SOLDIER:
      strcpy(p_gc->name, "Merman Soldier");
      strcpy(p_gc->descriptor, "merman soldier");
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 3;
      p_gc->mental_defense *= 3;
      p_gc->level = 2;
      p_gc->relationship = ENEMY;
      p_gc->languages[MER] = KNOWN;
      p_gc->experience *= 2;
      break;
    case MERFOLK_HIGH_PRIESTESS:
      strcpy(p_gc->name, "Quaelos");
      strcpy(p_gc->descriptor, "mermaid high priestess");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 12;
      p_gc->mental_defense *= 12;
      p_gc->relationship = ENEMY;
      p_gc->languages[MER] = KNOWN;
      p_gc->languages[ANCIENT_MER] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_WAVES] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      break;
    case MERFOLK_PRIESTESS:
      strcpy(p_gc->name, "Mermaid Priestess");
      strcpy(p_gc->descriptor, "mermaid priestess");
      p_gc->max_hp *= 1.5;
      p_gc->hp *= 1.5;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 3;
      p_gc->mental_defense *= 3;
      p_gc->relationship = ENEMY;
      p_gc->languages[MER] = KNOWN;
      p_gc->languages[ANCIENT_MER] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_WAVES] = KNOWN;
      p_gc->level = 10;
      p_gc->experience *= 3;
      break;
    case MERFOLK_QUEEN:
      strcpy(p_gc->name, "Queen Serashnul");
      strcpy(p_gc->descriptor, "mermaid queen");
      p_gc->unique = true;
      p_gc->max_hp *= 2;
      p_gc->hp *= 2;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 3;
      p_gc->mental_defense *= 3;
      p_gc->relationship = ENEMY;
      p_gc->languages[MER] = KNOWN;
      p_gc->languages[ANCIENT_MER] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->level = 20;
      p_gc->experience *= 10;
      break;
    case THE_DARK_RECLUSE:
      strcpy(p_gc->name, "The Dark Recluse");
      strcpy(p_gc->descriptor, "black-robed wizard");
      p_gc->unique = true;
      p_gc->max_hp *= 4;
      p_gc->hp *= 4;
      p_gc->physical_power *= 1.5;
      p_gc->physical_defense *= 1.5;
      p_gc->mental_power *= 15;
      p_gc->mental_defense *= 15;
      p_gc->soul = VERY_EVIL;
      p_gc->relationship = ENEMY;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_EVIL] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->level = 40;
      p_gc->experience *= 40;
      break;
    case THE_HERMIT:
      strcpy(p_gc->name, "The Hermit");
      strcpy(p_gc->descriptor, "old, green-robed man");
      p_gc->unique = true;
      p_gc->max_hp *= 4;
      p_gc->hp *= 4;
      p_gc->physical_power *= 2;
      p_gc->physical_defense *= 2;
      p_gc->mental_power *= 15;
      p_gc->mental_defense *= 15;
      p_gc->relationship = ENEMY;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ELVISH] = KNOWN;
      p_gc->languages[ANCIENT_ELVISH] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_BALANCE] = KNOWN;
      p_gc->words[WORD_OF_TIME] = KNOWN;
      p_gc->level = 40;
      p_gc->experience *= 40;
      break;
    case THE_ANGLER:
      strcpy(p_gc->name, "The Angler");
      strcpy(p_gc->descriptor, "old, blue-robed fisherman");
      p_gc->unique = true;
      p_gc->max_hp *= 3;
      p_gc->hp *= 3;
      p_gc->mental_power *= 15;
      p_gc->mental_defense *= 15;
      p_gc->soul = GOOD;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->languages[MER] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->level = 40;
      p_gc->experience *= 40;
      p_gc->gold = RandomInt(1, 10);
      break;
    case THE_WANDERING_MONK:
      strcpy(p_gc->name, "The Wandering Monk");
      strcpy(p_gc->descriptor, "red-robed monk");
      p_gc->unique = true;
      p_gc->max_hp *= 4;
      p_gc->hp *= 4;
      p_gc->physical_power *= 3;
      p_gc->physical_defense *= 3;
      p_gc->mental_power *= 15;
      p_gc->mental_defense *= 15;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->languages[GESH] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->words[WORD_OF_EVIL] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_VOID] = KNOWN;
      p_gc->level = 40;
      p_gc->experience *= 40;
      p_gc->gold = RandomInt(0, 5);
      break;
    case THE_SILENT_SAGE:
      strcpy(p_gc->name, "The Silent Sage");
      strcpy(p_gc->descriptor, "old, white-robed man");
      p_gc->unique = true;
      p_gc->max_hp *= 3;
      p_gc->hp *= 3;
      p_gc->mental_power *= 20;
      p_gc->mental_defense *= 20;
      p_gc->soul = VERY_GOOD;
      p_gc->languages[IMPERIAL] = KNOWN;
      p_gc->languages[ANCIENT_IMPERIAL] = KNOWN;
      p_gc->languages[VENTARRI] = KNOWN;
      p_gc->languages[ANCIENT_VENTARRI] = KNOWN;
      p_gc->languages[ELVISH] = KNOWN;
      p_gc->languages[ANCIENT_ELVISH] = KNOWN;
      p_gc->languages[DWARVISH] = KNOWN;
      p_gc->languages[ANCIENT_DWARVISH] = KNOWN;
      p_gc->languages[GNOMISH] = KNOWN;
      p_gc->languages[ANCIENT_GNOMISH] = KNOWN;
      p_gc->words[WORD_OF_FIRE] = KNOWN;
      p_gc->words[WORD_OF_EARTH] = KNOWN;
      p_gc->words[WORD_OF_WATER] = KNOWN;
      p_gc->words[WORD_OF_AIR] = KNOWN;
      p_gc->words[WORD_OF_BODY] = KNOWN;
      p_gc->words[WORD_OF_MIND] = KNOWN;
      p_gc->words[WORD_OF_FLORA] = KNOWN;
      p_gc->words[WORD_OF_FAUNA] = KNOWN;
      p_gc->words[WORD_OF_LIGHT] = KNOWN;
      p_gc->words[WORD_OF_DARKNESS] = KNOWN;
      p_gc->words[WORD_OF_HEALTH] = KNOWN;
      p_gc->words[WORD_OF_SICKNESS] = KNOWN;
      p_gc->words[WORD_OF_LIFE] = KNOWN;
      p_gc->words[WORD_OF_DEATH] = KNOWN;
      p_gc->words[WORD_OF_GIVING] = KNOWN;
      p_gc->words[WORD_OF_TAKING] = KNOWN;
      p_gc->words[WORD_OF_INCREASE] = KNOWN;
      p_gc->words[WORD_OF_DECREASE] = KNOWN;
      p_gc->words[WORD_OF_HOLINESS] = KNOWN;
      p_gc->words[WORD_OF_EVIL] = KNOWN;
      p_gc->words[WORD_OF_SHIELDING] = KNOWN;
      p_gc->words[WORD_OF_TIME] = KNOWN;
      p_gc->level = 50;
      p_gc->experience *= 50;
      p_gc->gold = RandomInt(1, 10);
      break;
    default:
      PRINT_ERROR_MESSAGE;
      return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: AddCompanion

Description: Removes a game character from the current location's list of
             inhabitants and adds that character to the player's list of
             companions.

     Inputs: companion - Pointer to the player's new companion.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int AddCompanion(game_character_t *companion) {
  game_character_t *p_gc1, *p_gc2 = NULL;

  if (companion == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  // Add "companion" to player's list of companions:
  if (g_player.next == NULL) {
    g_player.next = companion;
  } else {
    for (p_gc1 = g_player.next;
         p_gc1->next != NULL;
         p_gc1 = p_gc1->next)
      ;
    p_gc1->next = companion;
  }

  // Remove "companion" from current location's list of inhabitants:
  for (p_gc1 = g_world[g_player.location]->inhabitants;
       p_gc1 != NULL;
       p_gc2 = p_gc1, p_gc1 = p_gc1->next) {
    if (p_gc1 == companion && p_gc2 != NULL) {
      if (p_gc1->next == NULL) {
        p_gc2->next = NULL;
      } else {
        p_gc2->next = p_gc1->next;
      }
      break;
    }
  }

  companion->next = NULL;

  if (p_gc1 == NULL) {  // If true, "companion" wasn't at current location.
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: RemoveCompanion

Description: Removes a game character from the player's list of companions and
             adds that character to the current location's list of inhabitants.

     Inputs: companion - Pointer to the companion to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int RemoveCompanion(game_character_t *companion) {
  game_character_t *p_gc1, *p_gc2 = NULL;

  if (companion == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  // Add "companion" to current location's list of inhabitants:
  if (g_world[g_player.location]->inhabitants == NULL) {
    g_world[g_player.location]->inhabitants = companion;
  } else {
    for (p_gc1 = g_world[g_player.location]->inhabitants;
         p_gc1->next != NULL;
         p_gc1 = p_gc1->next)
      ;
    p_gc1->next = companion;
  }

  // Remove "companion" from player's list of companions:
  for (p_gc1 = g_player.next;
       p_gc1 != NULL;
       p_gc2 = p_gc1, p_gc1 = p_gc1->next) {
    if (p_gc1 == companion && p_gc2 != NULL) {
      if (p_gc1->next == NULL) {
        p_gc2->next = NULL;
      } else {
        p_gc2->next = p_gc1->next;
      }
      break;
    }
  }

  companion->next = NULL;

  if (p_gc1 == NULL) {  // If true, "companion" wasn't player's companion.
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: DeleteCompanion

Description: Removes a game character from the player's list of companions and
             deallocates its associated memory.

     Inputs: companion - Pointer to the companion to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int DeleteCompanion(game_character_t *companion) {
  game_character_t *p_gc1, *p_gc2 = NULL;

  if (companion == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  // Remove "companion" from player's list of companions:
  for (p_gc1 = g_player.next;
       p_gc1 != NULL;
       p_gc2 = p_gc1, p_gc1 = p_gc1->next) {
    if (p_gc1 == companion && p_gc2 != NULL) {
      if (p_gc1->next == NULL) {
        p_gc2->next = NULL;
      } else {
        p_gc2->next = p_gc1->next;
      }
      break;
    }
  }
  if (p_gc1 == NULL) {  // If true, "companion" wasn't player's companion.
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  // Deallocate associated memory:
  if (companion->summoned_creature != NULL) {
    DeleteCreatureSummonedBy(companion);
  }
  free(companion);

  return SUCCESS;
}

/******************************************************************************
   Function: AddSummonedCreature

Description: Creates a new, summoned game character and associates it with its
             summoner. (If the summoner already had a summoned creature, that
             creature is deleted.)

     Inputs: summoner - Pointer to the character that summoned the creature.
             type     - Integer representing the summoned creature's type.

    Outputs: Pointer to the summoned creature.
******************************************************************************/
game_character_t *AddSummonedCreature(game_character_t *summoner, int type) {
  game_character_t *newGC = NULL;

  if (summoner == NULL) {
    PRINT_ERROR_MESSAGE;
  } else {
    if (summoner->summoned_creature != NULL) {
      DeleteCreatureSummonedBy(summoner);
    }
    newGC = malloc(sizeof(game_character_t));
    if (newGC != NULL) {
      InitializeCharacter(newGC, type, g_world[summoner->location]);
    } else {
      PRINT_ERROR_MESSAGE;
      exit(1);
    }
  }

  return newGC;
}

/******************************************************************************
   Function: DeleteCreatureSummonedBy

Description: Removes a summoned creature from its summoner's struct and
             deallocates its associated memory.

     Inputs: summoner - Pointer to the character who summoned the creature to
                        be deleted.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int DeleteCreatureSummonedBy(game_character_t *summoner) {
  game_character_t *creature;

  if (summoner == NULL || summoner->summoned_creature == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  creature = summoner->summoned_creature;
  summoner->summoned_creature = NULL;
  free(creature);

  return SUCCESS;
}

/******************************************************************************
   Function: DisplayCharacterData

Description: Displays detailed information about a given game character (and
             the game character's summoned creature and/or companions, if any).

     Inputs: p_gc - Game character of interest.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int DisplayCharacterData(game_character_t *p_gc) {
  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  printf("Name: %s\n", p_gc->name);
  printf("Level: %d\n", p_gc->level);
  printf("Experience: %d\n", p_gc->experience);
  printf("HP: %d/%d\n", p_gc->hp, p_gc->max_hp);
  printf("Physical power: %d\n", p_gc->physical_power);
  printf("Physical defense: %d\n", p_gc->physical_defense);
  printf("Speed: %d\n", p_gc->speed);
  printf("Mental power: %d\n", p_gc->mental_power);
  printf("Mental defense: %d\n", p_gc->mental_defense);
  printf("Soul: ");
  PrintSoulDescription(p_gc);
  printf("\n");
  printf("Languages learned: %d\n", NumberOfLanguagesKnown(p_gc));
  printf("Words of Power acquired: %d\n", NumberOfWordsKnown(p_gc));
  printf("Gold: %d\n", p_gc->gold);
  PrintInventory(p_gc);
  //PrintStatus(p_gc);
  if (p_gc->summoned_creature != NULL) {
    printf("Summoned creature: %s (%d/%d, ",
           p_gc->summoned_creature->name,
           p_gc->summoned_creature->hp,
           p_gc->summoned_creature->max_hp);
    //PrintStatus(p_gc->summoned_creature);
  }
  FlushInput();

  return SUCCESS;
}

/******************************************************************************
   Function: PrintSoulDescription

Description: Prints one or two words describing the general state of a given
             game character's soul (e.g., "good", "evil", etc.).

     Inputs: p_gc - Game character of interest.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int PrintSoulDescription(game_character_t *p_gc) {
  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  } else if (p_gc->soul <= EXTREMELY_EVIL) {
    printf("Extremely Evil");
  } else if (p_gc->soul <= VERY_EVIL) {
    printf("Very Evil");
  } else if (p_gc->soul <= EVIL) {
    printf("Evil");
  } else if (p_gc->soul >= EXTREMELY_GOOD) {
    printf("Extremely Good");
  } else if (p_gc->soul >= VERY_GOOD) {
    printf("Very Good");
  } else if (p_gc->soul >= GOOD) {
    printf("Good");
  } else {
    printf("Neutral");
  }

  return SUCCESS;
}

/******************************************************************************
   Function: IsGood

Description: Returns true if a given game character has a good soul.

     Inputs: p_gc - Game character of interest.

    Outputs: true or false.
******************************************************************************/
bool IsGood(game_character_t *p_gc) {
  return p_gc != NULL && p_gc->soul >= GOOD;
}

/******************************************************************************
   Function: IsEvil

Description: Returns true if a given game character has an evil soul.

     Inputs: p_gc - Game character of interest.

    Outputs: true or false.
******************************************************************************/
bool IsEvil(game_character_t *p_gc) {
  return p_gc != NULL && p_gc->soul <= EVIL;
}

/******************************************************************************
   Function: IsNeutral

Description: Returns true if a given game character has a neutral soul (neither
             good nor evil).

     Inputs: p_gc - Game character of interest.

    Outputs: true or false.
******************************************************************************/
bool IsNeutral(game_character_t *p_gc) {
  return p_gc != NULL && p_gc->soul > EVIL && p_gc->soul < GOOD;
}

/******************************************************************************
   Function: NumberOfLanguagesKnown

Description: Returns the number of languages a given game character knows.

     Inputs: p_gc - Game character of interest.

    Outputs: Number of languages the game character knows (or -1 if an error is
             encountered).
******************************************************************************/
int NumberOfLanguagesKnown(game_character_t *p_gc) {
  int i, numLanguages = 0;

  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return -1;
  }

  for (i = 0; i < NUM_LANGUAGE_TYPES; i++) {
    if (p_gc->languages[i] == KNOWN) {
      numLanguages++;
    }
  }

  return numLanguages;
}

/******************************************************************************
   Function: NumberOfWordsKnown

Description: Returns the number of Words of Power a given game character knows.

     Inputs: p_gc - Game character of interest.

    Outputs: Number of Words the game character knows (or -1 if an error is
             encountered).
******************************************************************************/
int NumberOfWordsKnown(game_character_t *p_gc) {
  int i, numWords = 0;

  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return -1;
  }

  for (i = 0; i < NUM_WORD_TYPES; i++) {
    if (p_gc->words[i] == KNOWN) {
      numWords++;
    }
  }

  return numWords;
}

/******************************************************************************
   Function: GetNameDefinite

Description: Returns either a name or a generic descriptor preceded by "the"
             for a given game character.

     Inputs: p_gc - Pointer to the game character of interest.

    Outputs: The game character's definite name/descriptor as a pointer to an
             array of characters.
******************************************************************************/
char *GetNameDefinite(game_character_t *p_gc) {
  static char name[SHORT_STR_LEN + 1];

  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return NULL;
  }

  if (p_gc->unique && p_gc->known_to_player) {
    return p_gc->name;
  }
  strcpy(name, "the ");
  strcat(name, p_gc->descriptor);

  return name;
}

/******************************************************************************
   Function: GetNameIndefinite

Description: Returns either a name or a generic descriptor preceded by "a" or
             "an" for a given game character.

     Inputs: p_gc - Pointer to the game character of interest.

    Outputs: The game character's indefinite name/descriptor as a pointer to an
             array of characters.
******************************************************************************/
char *GetNameIndefinite(game_character_t *p_gc) {
  static char name[SHORT_STR_LEN + 1];

  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return NULL;
  }

  if (p_gc->unique && p_gc->known_to_player) {
    return p_gc->name;
  } else if (p_gc->descriptor[0] == 'a' ||
             p_gc->descriptor[0] == 'e' ||
             p_gc->descriptor[0] == 'i' ||
             p_gc->descriptor[0] == 'o' ||
             p_gc->descriptor[0] == 'u' ||
             p_gc->descriptor[0] == 'A' ||
             p_gc->descriptor[0] == 'E' ||
             p_gc->descriptor[0] == 'I' ||
             p_gc->descriptor[0] == 'O' ||
             p_gc->descriptor[0] == 'U') {
    strcpy(name, "an ");
  } else {
    strcpy(name, "a ");
  }
  strcat(name, p_gc->descriptor);

  return name;
}

/******************************************************************************
   Function: GetNamePlural

Description: Returns the plural form of a given game character's generic
             descriptor.

     Inputs: p_gc - Pointer to the game character whose name/description is to
                    be made plural.

    Outputs: The game character's plural name/descriptor as a pointer to an
             array of characters.
******************************************************************************/
char *GetNamePlural(game_character_t *p_gc) {
  int name_length;
  static char name[SHORT_STR_LEN + 1];

  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  switch (p_gc->type) {
    case HUMAN:
      strcpy(name, "common folk");
      break;
    case ELF:
      strcpy(name, "elves");
      break;
    case DWARF:
      strcpy(name, "dwarves");
      break;
    case THIEF:
      strcpy(name, "thieves");
      break;
    case FISHERMAN:
      strcpy(name, "fishermen");
      break;
    case NOBLEMAN:
      strcpy(name, "noblemen");
      break;
    case MERFOLK:
      strcpy(name, "common merfolk");
      break;
    case MERFOLK_PRIESTESS:
      strcpy(name, "mermaid priestesses");
      break;
    case DUMMY:
      strcpy(name, "stuffed dummies");
      break;
    default:  // Add 's' to the end of the descriptor.
      strcpy(name, p_gc->descriptor);
      name_length = strlen(name);
      if (name_length >= SHORT_STR_LEN - 1) {  // Ensure there's room for 's'.
        PRINT_ERROR_MESSAGE;
        return NULL;
      }
      name[name_length] = 's';
      name[name_length + 1] = '\0';
      break;
  }

  return name;
}

/******************************************************************************
   Function: CheckStatus

Description: Checks player's HP and status to see if anything needs to be
             adjusted or reported.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void CheckStatus(void) {
  int i;
  char output[LONG_STR_LEN + 1] = "";

  if (g_player.status[IN_COMBAT] == true) {
    for (i = 0; i < NumberOfEnemies(); i++) {
      if (g_enemies[i]->hp <= 0) {
        strcat(output, Capitalize(GetNameDefinite(g_enemies[i])));
        if (g_enemies[i]->status[INANIMATE]) {
          strcat(output, " has been destroyed.\n");
        } else {
          strcat(output, " is dead.\n");
        }
        g_num_kills[g_enemies[i]->type]++;
        DeleteEnemy(g_enemies[i]);
        i--;  // Because the "g_enemies" array has now been left-shifted.
      }
    }
    PrintString(output);
    FlushInput();
  }
  if (g_player.hp <= 0) {
    if (g_enemies[0] != NULL && g_enemies[0]->type == DUMMY) {  // In tutorial.
      sprintf(output,
              "%s: \"You have fallen due to severe backlash from your spell! "
              "This is often caused by speaking the same elemental Word more "
              "than once, or by combining three or more elemental Words in a "
              "single spell. We will bring you back to full health for now, "
              "but you must be more cautious in the future.\"",
              FindInhabitant(ARCHWIZARD_OF_ELEMENTS)->name);
      g_player.hp = g_player.max_hp;
    } else {  // Not in tutorial mode: death is permanent.
      sprintf(output, "Alas, %s has perished!\n", g_player.name);
      //HandleMainMenuInput();
    }
  }
  if (strlen(output) > 0) {
    PrintString(output);
    FlushInput();
  }
}

/******************************************************************************
   Function: UpdateVisibleGameCharCounter

Description: Updates the game character counter to accurately reflect the
             number of each GC type currently visible to the player. If in
             combat mode, only enemies will be counted. Summoned creatures are
             included in the count.

     Inputs: None.

    Outputs: None. (Modifies the global "g_num_visible_of_type" array.)
******************************************************************************/
void UpdateVisibleGameCharCounter(void) {
  int i;
  game_character_t *p_gc;

  for (i = 0; i < NUM_GC_TYPES; i++) {  // Clear the visible GC counter.
    g_num_visible_of_type[i] = 0;
  }
  if (g_player.status[IN_COMBAT]) {  // Combat mode: only count enemies.
    for (i = 0; i < NumberOfEnemies(); i++) {
      g_num_visible_of_type[g_enemies[i]->type]++;
      if (g_enemies[i]->summoned_creature != NULL) {
        g_num_visible_of_type[g_enemies[i]->summoned_creature->type]++;
      }
    }
  } else {  // Not in combat mode: count all local inhabitants.
    for (p_gc = g_world[g_player.location]->inhabitants;
         p_gc != NULL;
         p_gc = p_gc->next) {
      if (p_gc->status[INVISIBLE] == false) {
        g_num_visible_of_type[p_gc->type]++;
        if (p_gc->summoned_creature != NULL) {
          g_num_visible_of_type[p_gc->summoned_creature->type]++;
        }
      }
    }
  }
}

/******************************************************************************
   Function: GetTarget

Description: Takes the player through the process of selecting a target.

     Inputs: None.

    Outputs: Pointer to the targeted game character.
******************************************************************************/
game_character_t *GetTarget(void) {
  game_character_t *target = NULL;

  return target;
}

/******************************************************************************
   Function: IsTargeted

Description: Determines whether a given game character is currently being
             targeted (i.e., being pointed to by an array of pointers to
             targets).

     Inputs: p_gc    - Pointer to the game character of interest.
             targets - Array of pointers to targeted game characters.

    Outputs: true if "p_gc" is being targeted, otherwise false.
******************************************************************************/
bool IsTargeted(game_character_t *p_gc, game_character_t *targets[]) {
  int i;

  for (i = 0; i < MAX_TARGETS && targets[i] != NULL; i++) {
    if (targets[i] == p_gc) {
      return true;
    }
  }

  return false;
}

/******************************************************************************
   Function: HealGameCharacter

Description: Causes a given game character to regain a certain number of hit
             points (always at least 1). Will not allow current HP to exceed
             maximum HP.

     Inputs: p_gc   - Pointer to the game character to be healed.
             amount - Number of hit points to be recovered. If zero or
                      negative, it will be converted to 1.

    Outputs: Number of hit points regained (or -1 if an error is encountered).
******************************************************************************/
int HealGameCharacter(game_character_t *p_gc, int amount) {
  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return -1;
  }

  if (amount <= 0) {
    amount = 1;  // At least 1 HP should be restored.
  }
  p_gc->hp += amount;
  if (p_gc->hp > p_gc->max_hp) {
    p_gc->hp = p_gc->max_hp;
  }

  return amount;
}

/******************************************************************************
   Function: DamageGameCharacter

Description: Causes a given game character to lose a certain number of hit
             points.

     Inputs: p_gc   - Pointer to the game character to be damaged.
             amount - Number of hit points to be lost. If zero or negative, it
                      will be converted to 1.

    Outputs: Number of hit points lost (or -1 if an error is encountered).
******************************************************************************/
int DamageGameCharacter(game_character_t *p_gc, int amount) {
  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return -1;
  }

  if (amount <= 0) {
    amount = 1;  // At least 1 HP should be lost.
  }
  p_gc->hp -= amount;
  if (p_gc->hp < 0) {
    p_gc->hp = 0;  // Game characters may not have negative HP.
  }

  return amount;
}

/******************************************************************************
   Function: GainExperience

Description: Increases the player's experience by a specified amount and checks
             for a level-up.

     Inputs: amount - Number of experience points to be gained.

    Outputs: Number of level-ups.
******************************************************************************/
int GainExperience(int amount) {
  int i, level_up_counter = 0;

  printf("%d experience points earned!\n", amount);
  FlushInput();
  for (i = 0; i < amount; i++) {
    g_player.experience++;
    if (g_player.experience % EXP_PER_LEVEL == 0) {
      LevelUp();
      level_up_counter++;
    }
  }

  return level_up_counter;
}

/******************************************************************************
   Function: LevelUp

Description: Increases the player's level and relevant stats.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void LevelUp(void) {
  int temp;

  g_player.level++;
  printf("%s has reached Level %d!\n", g_player.name, g_player.level);
  FlushInput();
  temp = HP_LEVEL_UP_VALUE;
  if (temp > 0) {
    g_player.max_hp += temp;
    HealGameCharacter(&g_player, temp);
    printf("Maximum hit points increased by %d.\n", temp);
  }
  temp = PHYSICAL_LEVEL_UP_VALUE;
  if (temp > 0) {
    g_player.physical_power += temp;
    printf("Physical power increased by %d.\n", temp);
  }
  temp = PHYSICAL_LEVEL_UP_VALUE;
  if (temp > 0) {
    g_player.physical_defense += temp;
    printf("Physical defense increased by %d.\n", temp);
  }
  temp = PHYSICAL_LEVEL_UP_VALUE;
  if (temp > 0) {
    g_player.speed += temp;
    printf("Speed increased by %d.\n", temp);
  }
  temp = MENTAL_LEVEL_UP_VALUE;
  if (temp > 0) {
    g_player.mental_power += temp;
    printf("Mental power increased by %d.\n", temp);
  }
  temp = MENTAL_LEVEL_UP_VALUE;
  if (temp > 0) {
    g_player.mental_defense += temp;
    printf("Mental defense increased by %d.\n", temp);
  }
  FlushInput();
}

/******************************************************************************
   Function: LearnLanguage

Description: Sets one of the player's languages to KNOWN.

     Inputs: language - Integer representing the language learned.

    Outputs: None.
******************************************************************************/
void LearnLanguage(int language) {
  g_player.languages[language] = KNOWN;
  printf("%s has learned the %s  language!\n", g_player.name,
         LanguageName(language));
  FlushInput();
}

/******************************************************************************
   Function: LearnWord

Description: Sets one of the player's Words of Power to KNOWN.

     Inputs: word - Integer representing the Word learned.

    Outputs: None.
******************************************************************************/
void LearnWord(int word) {
  g_player.words[word] = KNOWN;
  printf("%s has learned %s, the Word of %s!\n", g_player.name, GetWord(word),
         GetWordName(word));
  FlushInput();
}
