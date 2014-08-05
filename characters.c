/******************************************************************************
   Filename: characters.c

     Author: David C. Drake (www.davidcdrake.com)

Description: Functions governing the creation, initialization, and basic
             analysis of game characters for the text-based fantasy RPG "Words
             of Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: InitializeCharacter

Description: Initializes a given GameCharacter struct to its default starting
             values.

     Inputs: pGC      - Pointer to the GameCharacer struct to be initialized.
             idNum    - ID number of the desired game character.
             location - The game character's starting location.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int InitializeCharacter(GameCharacter *pGC, int idNum, Location *location)
{
  int i; /* for loop variable */
  char cInput;
  BOOL repeatOptions;

    /* Default stats, representative of an average adult human.              */
  pGC->ID = idNum;
  strcpy(pGC->name, "");
  strcpy(pGC->descriptor, "");
  pGC->unique = FALSE;
  pGC->maxHP = DEFAULT_HP;
  pGC->currentHP = DEFAULT_HP;
  pGC->physicalPower = DEFAULT_PHYSICAL_POWER;
  pGC->physicalDefense = DEFAULT_PHYSICAL_DEFENSE;
  pGC->mentalPower = DEFAULT_MENTAL_POWER;
  pGC->mentalDefense = DEFAULT_MENTAL_DEFENSE;
  pGC->speed = DEFAULT_SPEED;
  pGC->soul = NEUTRAL;
  pGC->level = 1;
  pGC->experience = DEFAULT_EXP;
  pGC->knowsPlayer = FALSE;
  pGC->knownToPlayer = FALSE;
  pGC->relationship = INDIFFERENT;
  pGC->conversations = 0;
  for (i = 0; i < TOTAL_STATUS_IDS; i++)
  {
    pGC->status[i] = FALSE;
  }
  pGC->gold = 0;
  for (i = 0; i < TOTAL_ITEM_IDS; i++)
  {
    pGC->inventory[i] = 0;
    pGC->equippedItems[i] = 0;
  }
  for (i = 0; i < TOTAL_LANGUAGE_IDS; i++)
  {
    pGC->languages[i] = UNKNOWN;
  }
  for (i = 0; i < TOTAL_WORD_IDS; i++)
  {
    pGC->words[i] = UNKNOWN;
  }
  pGC->locationID = location->ID;
  pGC->summonedCreature = NULL;
  pGC->next = NULL;

    /* Character-specific stats.                                             */
  switch (pGC->ID)
  {
    case PLAYER:
      pGC->unique = TRUE;
      pGC->experience = 0;
      pGC->mentalPower *= 2;
      pGC->mentalDefense *= 2;
      pGC->knowsPlayer = TRUE;
      pGC->knownToPlayer = TRUE;
      pGC->relationship = GREAT_FRIEND;
      pGC->gold = 10;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->inventory[HEALING_POTION] = 3;
      pGC->locationID = ILLARUM_SCHOOL;
      PrintString("You are a human wizard from a distant land who has traveled"
                  " to the city of Illarum in order to study at the "
                  "prestigious School of the Elements.\0");
      FlushInput();
      do
      {
        printf("What is thy name? ");
        GetStrInput(pGC->name, SHORT_STR_LEN + 1);
        repeatOptions = strlen(pGC->name) < 1;
      }while (repeatOptions);
      break;
    case ARCHWIZARD_OF_ELEMENTS:
      strcpy(pGC->name, "Archememnon");
      strcpy(pGC->descriptor, "archwizard");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->mentalPower *= 10;
      pGC->mentalDefense *= 10;
      pGC->soul = EVIL;
      pGC->relationship = GOOD_FRIEND;
      pGC->knowsPlayer = TRUE;
      pGC->knownToPlayer = TRUE;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(100, 200);
      break;
    case WIZARD_OF_ELEMENTS:
      strcpy(pGC->name, "Wizard of the Elements");
      strcpy(pGC->descriptor, "wizard");
      pGC->mentalPower *= 2;
      pGC->mentalDefense *= 2;
      pGC->relationship = GOOD_FRIEND;
      pGC->knowsPlayer = TRUE;
      pGC->knownToPlayer = TRUE;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->level = 2;
      pGC->experience *= 3;
      pGC->gold = RandomInt(10, 20);
      break;
    case ILLARUM_PRIEST:
      strcpy(pGC->name, "Priest");
      strcpy(pGC->descriptor, "priest");
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 2.5;
      pGC->soul = EXTREMELY_GOOD;
      pGC->relationship = FRIEND;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[GESH] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->level = 2;
      pGC->experience *= 3;
      break;
    case ILLARUM_HIGH_PRIEST:
      strcpy(pGC->name, "Yemmul");
      strcpy(pGC->descriptor, "high priest");
      pGC->unique = TRUE;
      pGC->maxHP *= 2.5;
      pGC->currentHP *= 2.5;
      pGC->mentalPower *= 5;
      pGC->mentalDefense *= 15;
      pGC->soul = EXTREMELY_GOOD;
      pGC->relationship = FRIEND;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[GESH] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      break;
    case DUMMY:
      strcpy(pGC->name, "Dummy");
      strcpy(pGC->descriptor, "stuffed dummy");
      pGC->maxHP = 1;
      pGC->currentHP = 1;
      pGC->physicalPower = 0;
      pGC->physicalDefense = 1;
      pGC->mentalPower = 0;
      pGC->mentalDefense = 0;
      pGC->experience = 1;
      pGC->status[INANIMATE] = TRUE;
      break;
    case HUMAN:
      strcpy(pGC->name, "Peasant");
      strcpy(pGC->descriptor, "peasant");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->gold = RandomInt(0, 5);
      break;
    case THIEF:
      strcpy(pGC->name, "Thief");
      strcpy(pGC->descriptor, "thief");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->gold = RandomInt(5, 10);
      break;
    case SOLDIER:
      strcpy(pGC->name, "Soldier");
      strcpy(pGC->descriptor, "soldier");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->gold = RandomInt(1, 5);
      break;
    case MERCHANT:
      strcpy(pGC->name, "Merchant");
      strcpy(pGC->descriptor, "merchant");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->gold = RandomInt(25, 50);
      break;
    case INNKEEPER:
      strcpy(pGC->name, "Innkeeper");
      strcpy(pGC->descriptor, "innkeeper");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->gold = RandomInt(10, 30);
      break;
    case ILLARUM_KING:
      strcpy(pGC->name, "King of Illarum");
      strcpy(pGC->descriptor, "king");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 2;
      pGC->mentalDefense *= 2;
      pGC->soul = GOOD;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(100, 500);
      break;
    case COURT_WIZARD:
      strcpy(pGC->name, "Court Wizard");
      strcpy(pGC->descriptor, "wizard");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->mentalPower *= 3;
      pGC->mentalDefense *= 3;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      for (i = 0; i < TOTAL_WORD_IDS; i++)
      {
        pGC->words[i] = KNOWN;
      }
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(50, 100);
      break;
    case NOBLEMAN:
      strcpy(pGC->name, "Nobleman");
      strcpy(pGC->descriptor, "nobleman");
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->gold = RandomInt(50, 100);
      break;
    case KNIGHT:
      strcpy(pGC->name, "Knight");
      strcpy(pGC->descriptor, "knight");
      pGC->maxHP *= 3;
      pGC->currentHP *= 3;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 3;
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->level = 10;
      pGC->experience *= 5;
      pGC->gold = RandomInt(10, 30);
      break;
    case SERVANT:
      strcpy(pGC->name, "Servant");
      strcpy(pGC->descriptor, "servant");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      break;
    case PRISONER:
      strcpy(pGC->name, "Prisoner");
      strcpy(pGC->descriptor, "prisoner");
      pGC->maxHP /= 2;
      pGC->currentHP /= 2;
      pGC->physicalPower /= 2;
      pGC->physicalDefense /= 2;
      pGC->mentalPower /= 2;
      pGC->mentalDefense /= 2;
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->experience /= 2;
      break;
    case SLAVE:
      strcpy(pGC->name, "Slave");
      strcpy(pGC->descriptor, "slave");
      pGC->maxHP /= 1.5;
      pGC->currentHP /= 1.5;
      pGC->physicalPower /= 1.5;
      pGC->physicalDefense /= 1.5;
      pGC->mentalPower /= 1.5;
      pGC->mentalDefense /= 1.5;
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->experience /= 1.5;
      break;
    case SAILOR:
      strcpy(pGC->name, "Sailor");
      strcpy(pGC->descriptor, "sailor");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      break;
    case ARCHWIZARD_OF_MIND:
      strcpy(pGC->name, "Kaeloss");
      strcpy(pGC->descriptor, "archwizard");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->mentalPower *= 10;
      pGC->mentalDefense *= 10;
      pGC->soul = VERY_EVIL;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(200, 300);
      break;
    case WIZARD_OF_MIND:
      strcpy(pGC->name, "Wizard of Mind");
      strcpy(pGC->descriptor, "wizard");
      pGC->mentalPower *= 2;
      pGC->mentalDefense *= 2;
      pGC->soul = EVIL;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->level = 2;
      pGC->experience *= 3;
      pGC->gold = RandomInt(20, 30);
      break;
    case VENTARRIS_PRIEST:
      strcpy(pGC->name, "Priest");
      strcpy(pGC->descriptor, "priest");
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 2.5;
      pGC->soul = GOOD;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->level = 2;
      pGC->experience *= 3;
      break;
    case VENTARRIS_HIGH_PRIEST:
      strcpy(pGC->name, "Graelmach");
      strcpy(pGC->descriptor, "high priest");
      pGC->unique = TRUE;
      pGC->maxHP *= 2.5;
      pGC->currentHP *= 2.5;
      pGC->mentalPower *= 5;
      pGC->mentalDefense *= 15;
      pGC->soul = VERY_GOOD;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->words[WORD_OF_EVIL] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      break;
    case VENTARRIS_KING:
      strcpy(pGC->name, "King Estvann");
      strcpy(pGC->descriptor, "king");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 2;
      pGC->mentalDefense *= 2;
      pGC->soul = VERY_EVIL;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(250, 500);
      break;
    case FARMER:
      strcpy(pGC->name, "Farmer");
      strcpy(pGC->descriptor, "farmer");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->soul = GOOD;
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->gold = RandomInt(0, 5);
      break;
    case FISHERMAN:
      strcpy(pGC->name, "Fisherman");
      strcpy(pGC->descriptor, "fisherman");
      if (InVentarrisTerritory(location))
      {
        pGC->languages[VENTARRI] = KNOWN;
      }
      else
      {
        pGC->languages[IMPERIAL] = KNOWN;
      }
      pGC->gold = RandomInt(0, 5);
      break;
    case DRUID:
      strcpy(pGC->name, "Druid");
      strcpy(pGC->descriptor, "druid");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->mentalPower *= 2;
      pGC->mentalDefense *= 2.5;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[GESH] = KNOWN;
      pGC->languages[ELVISH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->level = 10;
      pGC->experience *= 3;
      break;
    case ARCHDRUID:
      strcpy(pGC->name, "Pann");
      strcpy(pGC->descriptor, "archdruid");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->mentalPower *= 10;
      pGC->mentalDefense *= 10;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[GESH] = KNOWN;
      pGC->languages[ELVISH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      break;
    case ELF:
      strcpy(pGC->name, "Elf");
      strcpy(pGC->descriptor, "elf");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 3;
      pGC->mentalDefense *= 3;
      pGC->soul = GOOD;
      pGC->languages[ELVISH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->experience *= 3.5;
      break;
    case ELF_LOREMASTER:
      strcpy(pGC->name, "Elven Loremaster");
      strcpy(pGC->descriptor, "elven loremaster");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 5;
      pGC->mentalDefense *= 5;
      pGC->soul = GOOD;
      pGC->languages[ELVISH] = KNOWN;
      pGC->languages[ANCIENT_ELVISH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->words[WORD_OF_BALANCE] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      break;
    case BARBARIAN:
      strcpy(pGC->name, "Babarian");
      strcpy(pGC->descriptor, "barbarian");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->languages[GESH] = KNOWN;
      pGC->experience *= 1.2;
      break;
    case BARBARIAN_WARRIOR:
      strcpy(pGC->name, "Barbarian Warrior");
      strcpy(pGC->descriptor, "barbarian warrior");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 3;
      pGC->languages[GESH] = KNOWN;
      pGC->level = 8;
      pGC->experience *= 2.5;
      break;
    case BARBARIAN_SHAMAN:
      strcpy(pGC->name, "Barbarian Shaman");
      strcpy(pGC->descriptor, "barbarian shaman");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 2;
      pGC->mentalDefense *= 2;
      pGC->languages[GESH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->level = 10;
      pGC->experience *= 3;
      break;
    case BARBARIAN_CHIEFTAIN:
      strcpy(pGC->name, "Telth");
      strcpy(pGC->descriptor, "barbarian chieftain");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 5;
      pGC->physicalDefense *= 5;
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 1.5;
      pGC->languages[GESH] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      break;
    case DWARF:
      strcpy(pGC->name, "Dwarf");
      strcpy(pGC->descriptor, "dwarf");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->experience *= 1.2;
      pGC->gold = RandomInt(5, 10);
      break;
    case DWARF_GUARDIAN:
      strcpy(pGC->name, "Dwarven Guardian");
      strcpy(pGC->descriptor, "dwarven guardian");
      pGC->maxHP *= 3;
      pGC->currentHP *= 3;
      pGC->physicalPower *= 4;
      pGC->physicalDefense *= 4;
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 1.5;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->level = 10;
      pGC->experience *= 5;
      pGC->gold = RandomInt(10, 30);
      break;
    case DWARF_MERCHANT:
      strcpy(pGC->name, "Dwarven Merchant");
      strcpy(pGC->descriptor, "dwarven merchant");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->experience *= 1.2;
      pGC->gold = RandomInt(50, 100);
      break;
    case DWARF_LOREMASTER:
      strcpy(pGC->name, "Dwarven Loremaster");
      strcpy(pGC->descriptor, "dwarven loremaster");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 5;
      pGC->mentalDefense *= 5;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->languages[ANCIENT_DWARVISH] = KNOWN;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->words[WORD_OF_FOCUS] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(10, 20);
      break;
    case DWARF_PRIEST:
      strcpy(pGC->name, "Dwarven Priest");
      strcpy(pGC->descriptor, "dwarven priest");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 3;
      pGC->mentalDefense *= 3;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->languages[ANCIENT_DWARVISH] = KNOWN;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->words[WORD_OF_FOCUS] = KNOWN;
      pGC->level = 10;
      pGC->experience *= 3;
      pGC->gold = RandomInt(10, 20);
      break;
    case DWARF_HIGH_PRIEST:
      strcpy(pGC->name, "Dwarven High Priest");
      strcpy(pGC->descriptor, "dwarven high priest");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 5;
      pGC->mentalDefense *= 5;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->languages[ANCIENT_DWARVISH] = KNOWN;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->words[WORD_OF_FOCUS] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(10, 20);
      break;
    case DWARF_KING:
      strcpy(pGC->name, "King Beoklast");
      strcpy(pGC->descriptor, "dwarven king");
      pGC->maxHP *= 4;
      pGC->currentHP *= 4;
      pGC->physicalPower *= 5;
      pGC->physicalDefense *= 5;
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 2;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->languages[ANCIENT_DWARVISH] = KNOWN;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 12;
      pGC->gold = RandomInt(500, 1000);
      break;
    case DWARF_MINER:
      strcpy(pGC->name, "Dwarven Miner");
      strcpy(pGC->descriptor, "dwarven miner");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 1.5;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->experience *= 1.5;
      pGC->gold = RandomInt(10, 20);
      break;
    case DRAGON:
      strcpy(pGC->name, "Dragon");
      strcpy(pGC->descriptor, "dragon");
      pGC->maxHP *= 50;
      pGC->currentHP *= 50;
      pGC->physicalPower *= 50;
      pGC->physicalDefense *= 50;
      pGC->mentalPower *= 10;
      pGC->mentalDefense *= 5;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->languages[ANCIENT_DWARVISH] = KNOWN;
      pGC->languages[ANCIENT_GNOMISH] = KNOWN;
      pGC->languages[ANCIENT_ELVISH] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->level = 30;
      pGC->experience *= 100;
      break;
    case GNOME:
      strcpy(pGC->name, "Gnome");
      strcpy(pGC->descriptor, "gnome");
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 1.5;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->gold = RandomInt(10, 20);
      break;
    case GNOME_MINER:
      strcpy(pGC->name, "Gnomish Miner");
      strcpy(pGC->descriptor, "gnomish miner");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 1.5;
      pGC->mentalDefense *= 1.5;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->experience *= 1.2;
      pGC->gold = RandomInt(10, 20);
      break;
    case NECROMANCER:
      strcpy(pGC->name, "Necromancer");
      strcpy(pGC->descriptor, "necromancer");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->mentalPower *= 3;
      pGC->mentalDefense *= 2;
      pGC->relationship = ENEMY;
      pGC->soul = EXTREMELY_EVIL;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_EVIL] = KNOWN;
      pGC->level = 10;
      pGC->experience *= 3.5;
      pGC->gold = RandomInt(25, 50);
      break;
    case ARCHNECROMANCER:
      strcpy(pGC->name, "Kraathmot");
      strcpy(pGC->descriptor, "archnecromancer");
      pGC->maxHP *= 3;
      pGC->currentHP *= 3;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 5;
      pGC->mentalDefense *= 4;
      pGC->relationship = ENEMY;
      pGC->soul = EXTREMELY_EVIL;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_EVIL] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      pGC->gold = RandomInt(50, 100);
      break;
    case LICH:
      strcpy(pGC->name, "Velroth");
      strcpy(pGC->descriptor, "lich");
      pGC->unique = TRUE;
      pGC->maxHP *= 5;
      pGC->currentHP *= 5;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 3;
      pGC->mentalPower *= 15;
      pGC->mentalDefense *= 15;
      pGC->soul = EXTREMELY_EVIL;
      pGC->relationship = ENEMY;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_EVIL] = KNOWN;
      pGC->level = 30;
      pGC->experience *= 30;
      pGC->gold = RandomInt(1000, 2000);
      break;
    case ZOMBIE:
      strcpy(pGC->name, "Zombie");
      strcpy(pGC->descriptor, "zombie");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 2;
      pGC->mentalPower = 0;
      pGC->mentalDefense = 0;
      pGC->soul = EVIL;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->experience *= 2;
      break;
    case SKELETAL_KNIGHT:
      strcpy(pGC->name, "Skeletal Knight");
      strcpy(pGC->descriptor, "skeletal knight");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower = 0;
      pGC->mentalDefense = 0;
      pGC->soul = EVIL;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->level = 10;
      pGC->experience *= 5;
      break;
    case RAT:
      strcpy(pGC->name, "Rat");
      strcpy(pGC->descriptor, "large rat");
      pGC->maxHP /= 2;
      pGC->currentHP /= 2;
      pGC->physicalPower /= 5;
      pGC->physicalDefense /= 5;
      pGC->mentalPower /= 10;
      pGC->mentalDefense /= 10;
      pGC->relationship = ENEMY;
      pGC->experience /= 10;
      break;
    case SHARK:
      strcpy(pGC->name, "Shark");
      strcpy(pGC->descriptor, "shark");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower /= 10;
      pGC->mentalDefense /= 10;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->experience *= 2.5;
      break;
    case WOLF:
      strcpy(pGC->name, "Wolf");
      strcpy(pGC->descriptor, "wolf");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower /= 10;
      pGC->mentalDefense /= 10;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->experience *= 2.5;
      break;
    case BEAR:
      strcpy(pGC->name, "Bear");
      strcpy(pGC->descriptor, "bear");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower /= 10;
      pGC->mentalDefense /= 10;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->experience *= 2.5;
      break;
    case GOBLIN:
      strcpy(pGC->name, "Goblin");
      strcpy(pGC->descriptor, "goblin");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower /= 10;
      pGC->mentalDefense /= 10;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->experience *= 2.5;
      break;
    case ORC:
      strcpy(pGC->name, "Orc");
      strcpy(pGC->descriptor, "orc");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower /= 10;
      pGC->mentalDefense /= 10;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->experience *= 2.5;
      break;
    case GIANT_SQUID:
      strcpy(pGC->name, "Giant Squid");
      strcpy(pGC->descriptor, "giant squid");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 2;
      pGC->mentalPower /= 10;
      pGC->mentalDefense /= 10;
      pGC->relationship = HOSTILE_ENEMY;
      pGC->experience *= 2.5;
      break;
    case MERFOLK:
      strcpy(pGC->name, "Merfolk");
      strcpy(pGC->descriptor, "merfolk");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalDefense *= 2;
      pGC->relationship = ENEMY;
      pGC->languages[MER] = KNOWN;
      pGC->experience *= 1.2;
      break;
    case MERFOLK_SOLDIER:
      strcpy(pGC->name, "Merman Soldier");
      strcpy(pGC->descriptor, "merman soldier");
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 3;
      pGC->mentalDefense *= 3;
      pGC->level = 2;
      pGC->relationship = ENEMY;
      pGC->languages[MER] = KNOWN;
      pGC->experience *= 2;
      break;
    case MERFOLK_HIGH_PRIESTESS:
      strcpy(pGC->name, "Quaelos");
      strcpy(pGC->descriptor, "mermaid high priestess");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 12;
      pGC->mentalDefense *= 12;
      pGC->relationship = ENEMY;
      pGC->languages[MER] = KNOWN;
      pGC->languages[ANCIENT_MER] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_WAVES] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      break;
    case MERFOLK_PRIESTESS:
      strcpy(pGC->name, "Mermaid Priestess");
      strcpy(pGC->descriptor, "mermaid priestess");
      pGC->maxHP *= 1.5;
      pGC->currentHP *= 1.5;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 3;
      pGC->mentalDefense *= 3;
      pGC->relationship = ENEMY;
      pGC->languages[MER] = KNOWN;
      pGC->languages[ANCIENT_MER] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_WAVES] = KNOWN;
      pGC->level = 10;
      pGC->experience *= 3;
      break;
    case MERFOLK_QUEEN:
      strcpy(pGC->name, "Queen Serashnul");
      strcpy(pGC->descriptor, "mermaid queen");
      pGC->unique = TRUE;
      pGC->maxHP *= 2;
      pGC->currentHP *= 2;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 3;
      pGC->mentalDefense *= 3;
      pGC->relationship = ENEMY;
      pGC->languages[MER] = KNOWN;
      pGC->languages[ANCIENT_MER] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->level = 20;
      pGC->experience *= 10;
      break;
    case THE_DARK_RECLUSE:
      strcpy(pGC->name, "The Dark Recluse");
      strcpy(pGC->descriptor, "black-robed wizard");
      pGC->unique = TRUE;
      pGC->maxHP *= 4;
      pGC->currentHP *= 4;
      pGC->physicalPower *= 1.5;
      pGC->physicalDefense *= 1.5;
      pGC->mentalPower *= 15;
      pGC->mentalDefense *= 15;
      pGC->soul = VERY_EVIL;
      pGC->relationship = ENEMY;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_EVIL] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->level = 40;
      pGC->experience *= 40;
      break;
    case THE_HERMIT:
      strcpy(pGC->name, "The Hermit");
      strcpy(pGC->descriptor, "old, green-robed man");
      pGC->unique = TRUE;
      pGC->maxHP *= 4;
      pGC->currentHP *= 4;
      pGC->physicalPower *= 2;
      pGC->physicalDefense *= 2;
      pGC->mentalPower *= 15;
      pGC->mentalDefense *= 15;
      pGC->relationship = ENEMY;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ELVISH] = KNOWN;
      pGC->languages[ANCIENT_ELVISH] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_BALANCE] = KNOWN;
      pGC->words[WORD_OF_TIME] = KNOWN;
      pGC->level = 40;
      pGC->experience *= 40;
      break;
    case THE_ANGLER:
      strcpy(pGC->name, "The Angler");
      strcpy(pGC->descriptor, "old, blue-robed fisherman");
      pGC->unique = TRUE;
      pGC->maxHP *= 3;
      pGC->currentHP *= 3;
      pGC->mentalPower *= 15;
      pGC->mentalDefense *= 15;
      pGC->soul = GOOD;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->languages[MER] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->level = 40;
      pGC->experience *= 40;
      pGC->gold = RandomInt(1, 10);
      break;
    case THE_WANDERING_MONK:
      strcpy(pGC->name, "The Wandering Monk");
      strcpy(pGC->descriptor, "red-robed monk");
      pGC->unique = TRUE;
      pGC->maxHP *= 4;
      pGC->currentHP *= 4;
      pGC->physicalPower *= 3;
      pGC->physicalDefense *= 3;
      pGC->mentalPower *= 15;
      pGC->mentalDefense *= 15;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->languages[GESH] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->words[WORD_OF_EVIL] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_VOID] = KNOWN;
      pGC->level = 40;
      pGC->experience *= 40;
      pGC->gold = RandomInt(0, 5);
      break;
    case THE_SILENT_SAGE:
      strcpy(pGC->name, "The Silent Sage");
      strcpy(pGC->descriptor, "old, white-robed man");
      pGC->unique = TRUE;
      pGC->maxHP *= 3;
      pGC->currentHP *= 3;
      pGC->mentalPower *= 20;
      pGC->mentalDefense *= 20;
      pGC->soul = VERY_GOOD;
      pGC->languages[IMPERIAL] = KNOWN;
      pGC->languages[ANCIENT_IMPERIAL] = KNOWN;
      pGC->languages[VENTARRI] = KNOWN;
      pGC->languages[ANCIENT_VENTARRI] = KNOWN;
      pGC->languages[ELVISH] = KNOWN;
      pGC->languages[ANCIENT_ELVISH] = KNOWN;
      pGC->languages[DWARVISH] = KNOWN;
      pGC->languages[ANCIENT_DWARVISH] = KNOWN;
      pGC->languages[GNOMISH] = KNOWN;
      pGC->languages[ANCIENT_GNOMISH] = KNOWN;
      pGC->words[WORD_OF_FIRE] = KNOWN;
      pGC->words[WORD_OF_EARTH] = KNOWN;
      pGC->words[WORD_OF_WATER] = KNOWN;
      pGC->words[WORD_OF_AIR] = KNOWN;
      pGC->words[WORD_OF_BODY] = KNOWN;
      pGC->words[WORD_OF_MIND] = KNOWN;
      pGC->words[WORD_OF_FLORA] = KNOWN;
      pGC->words[WORD_OF_FAUNA] = KNOWN;
      pGC->words[WORD_OF_LIGHT] = KNOWN;
      pGC->words[WORD_OF_DARKNESS] = KNOWN;
      pGC->words[WORD_OF_HEALTH] = KNOWN;
      pGC->words[WORD_OF_SICKNESS] = KNOWN;
      pGC->words[WORD_OF_LIFE] = KNOWN;
      pGC->words[WORD_OF_DEATH] = KNOWN;
      pGC->words[WORD_OF_GIVING] = KNOWN;
      pGC->words[WORD_OF_TAKING] = KNOWN;
      pGC->words[WORD_OF_INCREASE] = KNOWN;
      pGC->words[WORD_OF_DECREASE] = KNOWN;
      pGC->words[WORD_OF_HOLINESS] = KNOWN;
      pGC->words[WORD_OF_EVIL] = KNOWN;
      pGC->words[WORD_OF_SHIELDING] = KNOWN;
      pGC->words[WORD_OF_TIME] = KNOWN;
      pGC->level = 50;
      pGC->experience *= 50;
      pGC->gold = RandomInt(1, 10);
      break;
    default:
#if DEBUG
      ERROR_MESSAGE
#endif
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
int AddCompanion(GameCharacter *companion)
{
  GameCharacter *pGC1, *pGC2;  /* For scanning linked lists.                 */

  if (companion == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

    /* Add "companion" to the player's list of companions.                   */
  if (player.next == NULL)
  {
    player.next = companion;
  }
  else
  {
    for (pGC1 = player.next;
         pGC1->next != NULL;
         pGC1 = pGC1->next)
      ;
    pGC1->next = companion;
  }

    /* Remove "companion" from the current location's list of inhabitants.   */
  for (pGC1 = world[player.locationID]->inhabitants;
       pGC1 != NULL;
       pGC2 = pGC1, pGC1 = pGC1->next)
  {
    if (pGC1 == companion)
    {
      if (pGC1->next == NULL)
      {
        pGC2->next = NULL;
      }
      else
      {
        pGC2->next = pGC1->next;
      }
      break;
    }
  }

  companion->next = NULL;

  if (pGC1 == NULL) /* If true, "companion" was not at the current location. */
  {
#if DEBUG
    ERROR_MESSAGE
#endif
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
int RemoveCompanion(GameCharacter *companion)
{
  GameCharacter *pGC1, *pGC2;  /* For scanning linked lists.                 */

  if (companion == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

    /* Add "companion" to the current location's list of inhabitants.        */
  if (world[player.locationID]->inhabitants == NULL)
  {
    world[player.locationID]->inhabitants = companion;
  }
  else
  {
    for (pGC1 = world[player.locationID]->inhabitants;
         pGC1->next != NULL;
         pGC1 = pGC1->next)
      ;
    pGC1->next = companion;
  }

    /* Remove "companion" from the player's list of companions.              */
  for (pGC1 = player.next;
       pGC1 != NULL;
       pGC2 = pGC1, pGC1 = pGC1->next)
  {
    if (pGC1 == companion)
    {
      if (pGC1->next == NULL)
      {
        pGC2->next = NULL;
      }
      else
      {
        pGC2->next = pGC1->next;
      }
      break;
    }
  }

  companion->next = NULL;

  if (pGC1 == NULL) /* If true, "companion" was not the player's companion.  */
  {
#if DEBUG
    ERROR_MESSAGE
#endif
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
int DeleteCompanion(GameCharacter *companion)
{
  GameCharacter *pGC1, *pGC2;  /* For scanning linked lists.                 */

  if (companion == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

    /* Remove "companion" from the player's list of companions.              */
  for (pGC1 = player.next;
       pGC1 != NULL;
       pGC2 = pGC1, pGC1 = pGC1->next)
  {
    if (pGC1 == companion)
    {
      if (pGC1->next == NULL)
      {
        pGC2->next = NULL;
      }
      else
      {
        pGC2->next = pGC1->next;
      }
      break;
    }
  }
  if (pGC1 == NULL) /* If true, "companion" was not the player's companion.  */
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

    /* Deallocate associated memory.                                         */
  if (companion->summonedCreature != NULL)
  {
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
             idNum    - ID of the summoned creature.

    Outputs: Pointer to the summoned creature.
******************************************************************************/
GameCharacter *AddSummonedCreature(GameCharacter *summoner, int idNum)
{
  GameCharacter *newGC = NULL;  /* To point to the new character.            */
  GameCharacter *temp;          /* To scan the location's inhabitant list.   */

  if (summoner == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
  }
  else
  {
    if (summoner->summonedCreature != NULL)
    {
      DeleteCreatureSummonedBy(summoner);
    }
    newGC = malloc(sizeof(GameCharacter));
    if (newGC != NULL)
    {
      InitializeCharacter(newGC, idNum, world[summoner->locationID]);
    }
    else
    {
#if DEBUG
      ERROR_MESSAGE
#endif
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
int DeleteCreatureSummonedBy(GameCharacter *summoner)
{
  GameCharacter *creature;

  if (summoner == NULL || summoner->summonedCreature == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  creature = summoner->summonedCreature;
  summoner->summonedCreature = NULL;
  free(creature);

  return SUCCESS;
}

/******************************************************************************
   Function: DisplayCharacterData

Description: Displays detailed information about a given game character (and
             the game character's summoned creature and/or companions, if any).

     Inputs: pGC - Game character of interest.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int DisplayCharacterData(GameCharacter *pGC)
{
  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  printf("Name: %s\n", pGC->name);
  printf("Level: %d\n", pGC->level);
  printf("Experience: %d\n", pGC->experience);
  printf("HP: %d/%d\n", pGC->currentHP, pGC->maxHP);
  printf("Physical power: %d\n", pGC->physicalPower);
  printf("Physical defense: %d\n", pGC->physicalDefense);
  printf("Speed: %d\n", pGC->speed);
  printf("Mental power: %d\n", pGC->mentalPower);
  printf("Mental defense: %d\n", pGC->mentalDefense);
  printf("Soul: ");
  PrintSoulDescription(pGC);
  printf("\n");
  printf("Languages learned: %d\n", NumberOfLanguagesKnown(pGC));
  printf("Words of Power acquired: %d\n", NumberOfWordsKnown(pGC));
  printf("Gold: %d\n", pGC->gold);
  PrintInventory(pGC);
  printf("\n");
  /* PrintStatus(pGC); */
  printf("\n");
  if (pGC->summonedCreature != NULL)
  {
    printf("Summoned creature: %s (%d/%d, ",
           pGC->summonedCreature->name,
           pGC->summonedCreature->currentHP,
           pGC->summonedCreature->maxHP);
    /* PrintStatus(pGC->summonedCreature); */
    printf(")\n");
  }
  FlushInput();

  return SUCCESS;
}

/******************************************************************************
   Function: PrintSoulDescription

Description: Prints one or two words describing the general state of a given
             game character's soul (e.g., "good", "evil", etc.).

     Inputs: pGC - Game character of interest.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int PrintSoulDescription(GameCharacter *pGC)
{
  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }
  else if (pGC->soul <= EXTREMELY_EVIL)
  {
    printf("Extremely Evil");
  }
  else if (pGC->soul <= VERY_EVIL)
  {
    printf("Very Evil");
  }
  else if (pGC->soul <= EVIL)
  {
    printf("Evil");
  }
  else if (pGC->soul >= EXTREMELY_GOOD)
  {
    printf("Extremely Good");
  }
  else if (pGC->soul >= VERY_GOOD)
  {
    printf("Very Good");
  }
  else if (pGC->soul >= GOOD)
  {
    printf("Good");
  }
  else
  {
    printf("Neutral");
  }

  return SUCCESS;
}

/******************************************************************************
   Function: IsGood

Description: Returns TRUE if a given game character has a good soul.

     Inputs: pGC - Game character of interest.

    Outputs: TRUE or FALSE.
******************************************************************************/
BOOL IsGood(GameCharacter *pGC)
{
  return (pGC != NULL && pGC->soul >= GOOD);
}

/******************************************************************************
   Function: IsEvil

Description: Returns TRUE if a given game character has an evil soul.

     Inputs: pGC - Game character of interest.

    Outputs: TRUE or FALSE.
******************************************************************************/
BOOL IsEvil(GameCharacter *pGC)
{
  return (pGC != NULL && pGC->soul <= EVIL);
}

/******************************************************************************
   Function: IsNeutral

Description: Returns TRUE if a given game character has a neutral soul (neither
             good nor evil).

     Inputs: pGC - Game character of interest.

    Outputs: TRUE or FALSE.
******************************************************************************/
BOOL IsNeutral(GameCharacter *pGC)
{
  return (pGC != NULL && (pGC->soul > EVIL && pGC->soul < GOOD));
}

/******************************************************************************
   Function: NumberOfLanguagesKnown

Description: Returns the number of languages a given game character knows.

     Inputs: pGC - Game character of interest.

    Outputs: Number of languages the game character knows (or -1 if an error is
             encountered).
******************************************************************************/
int NumberOfLanguagesKnown(GameCharacter *pGC)
{
  int i;  /* for loop variable */
  int numLanguages = 0;

  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return -1;
  }

  for (i = 0; i < TOTAL_LANGUAGE_IDS; i++)
  {
    if (pGC->languages[i] == KNOWN)
    {
      numLanguages++;
    }
  }

  return numLanguages;
}

/******************************************************************************
   Function: NumberOfWordsKnown

Description: Returns the number of Words of Power a given game character knows.

     Inputs: pGC - Game character of interest.

    Outputs: Number of Words the game character knows (or -1 if an error is
             encountered).
******************************************************************************/
int NumberOfWordsKnown(GameCharacter *pGC)
{
  int i;  /* for loop variable */
  int numWords = 0;

  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return -1;
  }

  for (i = 0; i < TOTAL_WORD_IDS; i++)
  {
    if (pGC->words[i] == KNOWN)
    {
      numWords++;
    }
  }

  return numWords;
}

/******************************************************************************
   Function: GetNameDefinite

Description: Returns either a name or a generic descriptor preceded by "the"
             for a given game character.

     Inputs: pGC        - The game character whose named/descriptor is desired.
             capitalize - Indicates whether or not to capitalize (e.g., "The").

    Outputs: The game character's definite name/descriptor as a pointer to an
             array of characters.
******************************************************************************/
char *GetNameDefinite(GameCharacter *pGC, BOOL capitalize)
{
  static char gcName[SHORT_STR_LEN + 1];

  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return NULL;
  }

  if (pGC->unique && pGC->knownToPlayer)
  {
    return pGC->name;
  }
  else
  {
    if (capitalize)
    {
      strcpy(gcName, "The ");
    }
    else
    {
      strcpy(gcName, "the ");
    }
  }
  strcat(gcName, pGC->descriptor);

  return gcName;
}

/******************************************************************************
   Function: GetNameIndefinite

Description: Returns either a name or a generic descriptor preceded by "a" or
             "an" for a given game character.

     Inputs: pGC        - The game character whose name/descriptor is desired.
             capitalize - Indicates whether or not to capitalize (e.g., "An").

    Outputs: The game character's indefinite name/descriptor as a pointer to an
             array of characters.
******************************************************************************/
char *GetNameIndefinite(GameCharacter *pGC, BOOL capitalize)
{
  static char gcName[SHORT_STR_LEN + 1];

  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return NULL;
  }

  if (pGC->unique && pGC->knownToPlayer)
  {
    return pGC->name;
  }
  else if (pGC->descriptor[0] == 'a' ||
           pGC->descriptor[0] == 'e' ||
           pGC->descriptor[0] == 'i' ||
           pGC->descriptor[0] == 'o' ||
           pGC->descriptor[0] == 'u' ||
           pGC->descriptor[0] == 'A' ||
           pGC->descriptor[0] == 'E' ||
           pGC->descriptor[0] == 'I' ||
           pGC->descriptor[0] == 'O' ||
           pGC->descriptor[0] == 'U')
  {
    if (capitalize)
    {
      strcpy(gcName, "An ");
    }
    else
    {
      strcpy(gcName, "an ");
    }
  }
  else
  {
    if (capitalize)
    {
      strcpy(gcName, "A ");
    }
    else
    {
      strcpy(gcName, "a ");
    }
  }
  strcat(gcName, pGC->descriptor);

  return gcName;
}

/******************************************************************************
   Function: GetNamePlural

Description: Returns the plural form of a given game character's generic
             descriptor.

     Inputs: pGC        - Game character whose name/description is to be made
                          plural.
             capitalize - If TRUE, capitalize.

    Outputs: The game character's plural name/descriptor as a pointer to an
             array of characters.
******************************************************************************/
char *GetNamePlural(GameCharacter *pGC, BOOL capitalize)
{
  int nameLength;
  static char gcName[SHORT_STR_LEN + 1];

  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  switch (pGC->ID)
  {
    case HUMAN:
      strcpy(gcName, "common folk");
      break;
    case ELF:
      strcpy(gcName, "elves");
      break;
    case DWARF:
      strcpy(gcName, "dwarves");
      break;
    case THIEF:
      strcpy(gcName, "thieves");
      break;
    case FISHERMAN:
      strcpy(gcName, "fishermen");
      break;
    case NOBLEMAN:
      strcpy(gcName, "noblemen");
      break;
    case MERFOLK:
      strcpy(gcName, "common merfolk");
      break;
    case MERFOLK_PRIESTESS:
      strcpy(gcName, "mermaid priestesses");
      break;
    case DUMMY:
      strcpy(gcName, "stuffed dummies");
      break;
    default: /* Simply adds "s" to the end of a game character's descriptor. */
      strcpy(gcName, pGC->descriptor);
      nameLength = strlen(gcName);
      if (nameLength >= SHORT_STR_LEN - 1) /* Must have room for 's'.        */
      {
#if DEBUG
        ERROR_MESSAGE
#endif
        return NULL;
      }
      gcName[nameLength] = 's';
      gcName[nameLength + 1] = '\0';
      break;
  }
  if (capitalize)
  {
    gcName[0] = toupper(gcName[0]);
  }

  return gcName;
}

/******************************************************************************
   Function: CheckStatus

Description: Checks player's HP and status to see if anything needs to be
             adjusted or reported.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void CheckStatus(void)
{
  int i;
  char output[LONG_STR_LEN + 1] = "";

  if (player.status[IN_COMBAT] == TRUE)
  {
    for (i = 0; i < NumberOfEnemies(); i++)
    {
      if (enemyNPCs[i]->currentHP <= 0)
      {
        strcat(output, GetNameDefinite(enemyNPCs[i], TRUE));
        if (enemyNPCs[i]->status[INANIMATE])
        {
          strcat(output, " has been destroyed.\n");
        }
        else
        {
          strcat(output, " is dead.\n");
        }
        kills[enemyNPCs[i]->ID]++;
        DeleteEnemy(enemyNPCs[i]);
        i--;  /* Because the "enemyNPCs" array has now been left-shifted.    */
      }
    }
    PrintString(output);
    FlushInput();
  }
  if (player.currentHP <= 0)
  {
    if (enemyNPCs[0] != NULL && enemyNPCs[0]->ID == DUMMY) /* Tutorial mode. */
    {
      sprintf(output,
              "%s: \"You have fallen due to severe backlash from your spell! "
              "This is often caused by speaking the same elemental Word more "
              "than once, or by combining three or more elemental Words in a "
              "single spell. We will bring you back to full health for now, "
              "but you must be more cautious in the future.\"",
              FindInhabitant(ARCHWIZARD_OF_ELEMENTS)->name);
      player.currentHP = player.maxHP;
    }
    else /* Not in tutorial mode: death is permanent.                        */
    {
      sprintf(output, "Alas, %s has perished!\n", player.name);
      //MainMenu();
    }
  }
  if (strlen(output) > 0)
  {
    PrintString(output);
    FlushInput();
  }
}

/******************************************************************************
   Function: UpdateVisibleGameCharCounter

Description: Updates the GameCharacter counter to accurately reflect the number
             number of each GC type currently visible to the player. If in
             combat mode, only enemies will be counted. Summoned creatures are
             included in the count.

     Inputs: None.

    Outputs: None. (Modifies the global "visibleGameCharCounter" array.)
******************************************************************************/
void UpdateVisibleGameCharCounter(void)
{
  int i;              /* for loop variable                  */
  GameCharacter *pGC; /* To scan the local inhabitant list. */

  for (i = 0; i < TOTAL_GC_IDS; i++)  /* Clear the visible GC counter.       */
  {
    visibleGameCharCounter[i] = 0;
  }
  if (player.status[IN_COMBAT]) /* Combat mode: only count enemies.          */
  {
    for (i = 0; i < NumberOfEnemies(); i++)
    {
      visibleGameCharCounter[enemyNPCs[i]->ID]++;
      if (enemyNPCs[i]->summonedCreature != NULL)
      {
        visibleGameCharCounter[enemyNPCs[i]->summonedCreature->ID]++;
      }
    }
  }
  else  /* Not in combat mode: count all local inhabitants.                  */
  {
    for (pGC = world[player.locationID]->inhabitants;
         pGC != NULL;
         pGC = pGC->next)
    {
      if (pGC->status[INVISIBLE] == FALSE)
      {
        visibleGameCharCounter[pGC->ID]++;
        if (pGC->summonedCreature != NULL)
        {
          visibleGameCharCounter[pGC->summonedCreature->ID]++;
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
GameCharacter *GetTarget(void)
{
  GameCharacter *target = NULL;

  return target;
}

/******************************************************************************
   Function: IsTargeted

Description: Determines whether a given game character is currently being
             targeted (i.e., being pointed to by an array of pointers to
             targets).

     Inputs: pGC     - Pointer to the game character of interest.
             targets - Array of pointers to targeted game characters.

    Outputs: TRUE if "pGC" is being targeted, otherwise FALSE.
******************************************************************************/
BOOL IsTargeted(GameCharacter *pGC, GameCharacter *targets[])
{
  int i; /* for loop variable */

  for (i = 0; i < MAX_TARGETS; i++)
  {
    if (targets[i] == pGC)
    {
      return TRUE;
    }
  }

  return FALSE;
}

/******************************************************************************
   Function: HealGameCharacter

Description: Causes a given game character to regain a certain number of hit
             points (always at least 1). Will not allow current HP to exceed
             maximum HP.

     Inputs: pGC    - Pointer to the game character to be healed.
             amount - Number of hit points to be recovered. If zero or
                      negative, it will be converted to 1.

    Outputs: Number of hit points regained (or -1 if an error is encountered).
******************************************************************************/
int HealGameCharacter(GameCharacter *pGC, int amount)
{
  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return -1;
  }

  if (amount <= 0)
  {
    amount = 1;                    /* At least 1 HP should be regained.      */
  }
  pGC->currentHP += amount;
  if (pGC->currentHP > pGC->maxHP) /* Current HP may not exceed maximum HP.  */
  {
    pGC->currentHP = pGC->maxHP;
  }

  return amount;
}

/******************************************************************************
   Function: DamageGameCharacter

Description: Causes a given game character to lose a certain number of hit
             points.

     Inputs: pGC    - Pointer to the game character to be damaged.
             amount - Number of hit points to be lost. If zero or negative, it
                      will be converted to 1.

    Outputs: Number of hit points lost (or -1 if an error is encountered).
******************************************************************************/
int DamageGameCharacter(GameCharacter *pGC, int amount)
{
  if (pGC == NULL)
  {
#if DEBUG
    ERROR_MESSAGE
#endif
    return -1;
  }

  if (amount <= 0)
  {
    amount = 1;         /* At least 1 HP should be lost.                     */
  }
  pGC->currentHP -= amount;
  if (pGC->currentHP < 0)
  {
    pGC->currentHP = 0; /* Game characters may not have negative HP.         */
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
int GainExperience(int amount)
{
  int i; /* for loop variable */
  int levelUpCounter = 0;

  printf("%d experience points earned!\n", amount);
  FlushInput();
  for (i = 0; i < amount; i++)
  {
    player.experience++;
    if (player.experience % EXP_PER_LEVEL == 0)
    {
      LevelUp();
      levelUpCounter++;
    }
  }

  return levelUpCounter;
}

/******************************************************************************
   Function: LevelUp

Description: Increases the player's level and relevant stats.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void LevelUp(void)
{
  int temp;

  player.level++;
  printf("%s has reached Level %d!\n", player.name, player.level);
  FlushInput();
  temp = HP_LEVEL_UP_VALUE;
  if (temp > 0)
  {
    player.maxHP += temp;
    HealGameCharacter(&player, temp);
    printf("Maximum hit points increased by %d.\n", temp);
  }
  temp = PHYSICAL_LEVEL_UP_VALUE;
  if (temp > 0)
  {
    player.physicalPower += temp;
    printf("Physical power increased by %d.\n", temp);
  }
  temp = PHYSICAL_LEVEL_UP_VALUE;
  if (temp > 0)
  {
    player.physicalDefense += temp;
    printf("Physical defense increased by %d.\n", temp);
  }
  temp = PHYSICAL_LEVEL_UP_VALUE;
  if (temp > 0)
  {
    player.speed += temp;
    printf("Speed increased by %d.\n", temp);
  }
  temp = MENTAL_LEVEL_UP_VALUE;
  if (temp > 0)
  {
    player.mentalPower += temp;
    printf("Mental power increased by %d.\n", temp);
  }
  temp = MENTAL_LEVEL_UP_VALUE;
  if (temp > 0)
  {
    player.mentalDefense += temp;
    printf("Mental defense increased by %d.\n", temp);
  }
  FlushInput();
}

/******************************************************************************
   Function: LearnLanguage

Description: Sets one of the player's languages to KNOWN.

     Inputs: langID - ID number of the language learned.

    Outputs: None.
******************************************************************************/
void LearnLanguage(int langID)
{
  player.languages[langID] = KNOWN;
  printf("%s has learned the %s  language!\n",
         player.name,
         LanguageName(langID));
  FlushInput();
}

/******************************************************************************
   Function: LearnWord

Description: Sets one of the player's Words of Power to KNOWN.

     Inputs: wordID - ID number of the language learned.

    Outputs: None.
******************************************************************************/
void LearnWord(int wordID)
{
  player.words[wordID] = KNOWN;
  printf("%s has learned %s, the Word of %s!\n",
         player.name,
         Word(wordID),
         WordName(wordID));
  FlushInput();
}
