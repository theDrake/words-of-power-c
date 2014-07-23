/******************************************************************************
   Filename: combat.c

     Author: David C. Drake (www.davidcdrake.com)

Description: Functions governing enemies and combat for the text-based fantasy
             RPG "Words of Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: AddEnemy

Description: Given an already existing game character, adds a pointer to it in
             the global "enemyNPCs" array.

     Inputs: pGC - Pointer to the game character to be added.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int AddEnemy(GameCharacter *pGC)
{
  int i; /* for loop variable */

  if (pGC == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  for (i = 0; i < MAX_ENEMIES; i++)
  {
    if (enemyNPCs[i] == NULL)
    {
      enemyNPCs[i] = pGC;
      pGC->status[IN_COMBAT] = TRUE;
      return SUCCESS;
    }
  }

    /* If we reach this point, "enemyNPCs" was full and the add failed.      */
#ifdef DEBUG
  ERROR_MESSAGE
#endif
  return FAILURE;
}

/******************************************************************************
   Function: AddRandomEnemy

Description: Creates a new game character and adds a pointer to it in the local
             "inhabitants" array as well as the the global "enemyNPCs" array,
             unless no random enemy is associated with the given location, in
             which case nothing happens.

     Inputs: location - Pointer to the location in which to add a random enemy.

    Outputs: SUCCESS if an enemy is added, otherwise FAILURE.
******************************************************************************/
int AddRandomEnemy(Location *location)
{
  GameCharacter *newEnemy = NULL;

  if (location == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  switch (location->ID)
  {
    case ILLARUM_ENTRANCE:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case ILLARUM_MARKET:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case ILLARUM_INN:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case ILLARUM_SCHOOL:
      break;
    case ILLARUM_TEMPLE:
      break;
    case ILLARUM_PALACE:
      break;
    case ILLARUM_PRISON:
      break;
    case VENTARRIS_ENTRANCE:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case VENTARRIS_MARKET:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case VENTARRIS_INN:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case VENTARRIS_SCHOOL:
      break;
    case VENTARRIS_TEMPLE:
      break;
    case VENTARRIS_PALACE:
      break;
    case VENTARRIS_PRISON:
      break;
    case VENTARRIS_DOCKS:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case PLAINS_NORTH:
      newEnemy = AddInhabitant(location, WOLF);
      break;
    case NORTHERN_FARMS:
      break;
    case BRILL_OUTSKIRTS:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case BRILL_MARKET:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case BRILL_INN:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case BRILL_DOCKS:
      newEnemy = AddInhabitant(location, THIEF);
      break;
    case PLAINS_SOUTH:
      newEnemy = AddInhabitant(location, WOLF);
      break;
    case SOUTHERN_FARMS:
      break;
    case SILENT_SAGE_HOME:
      break;
    case FOREST:
      if (player.soul <= EVIL)
      {
        newEnemy = AddInhabitant(location, ELF);
      }
      else
      {
        newEnemy = AddInhabitant(location, BEAR);
      }
      break;
    case DRUIDS_GROVE:
      break;
    case HERMIT_HUT:
      break;
    case WYNNFAER_ENTRANCE:
      if (player.soul <= EVIL)
      {
        newEnemy = AddInhabitant(location, ELF);
      }
      break;
    case WYNNFAER_PLAZA:
      if (player.soul <= EVIL)
      {
        newEnemy = AddInhabitant(location, ELF);
      }
      break;
    case WYNNFAER_PALACE:
      if (player.soul <= EVIL)
      {
        newEnemy = AddInhabitant(location, ELF);
      }
      break;
    case MOUNTAINS:
      newEnemy = AddInhabitant(location, GOBLIN);
      break;
    case GESHTAL:
      if (player.soul <= EVIL)
      {
        newEnemy = AddInhabitant(location, BARBARIAN);
      }
      break;
    case TORR_ENTRANCE:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_MARKET:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_SCHOOL:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_TEMPLE:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_THRONE_ROOM:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_MINE:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_VAULT:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_PRISON:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case GUGGENHOLM_ENTRANCE:
      newEnemy = AddInhabitant(location, GOBLIN);
      break;
    case GUGGENHOLM_MAIN:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, GNOME);
      }
      break;
    case GUGGENHOLM_MINE:
      if (player.soul <= VERY_EVIL)
      {
        newEnemy = AddInhabitant(location, GNOME);
      }
      break;
    case SWAMP:
      newEnemy = AddInhabitant(location, ZOMBIE);
      break;
    case NECROMANCERS_CIRCLE:
      newEnemy = AddInhabitant(location, ZOMBIE);
      break;
    case ISHTARR_ENTRANCE:
      newEnemy = AddInhabitant(location, ZOMBIE);
      break;
    case ISHTARR_EAST_WING:
      newEnemy = AddInhabitant(location, ZOMBIE);
      break;
    case ISHTARR_WEST_WING:
      newEnemy = AddInhabitant(location, ZOMBIE);
      break;
    case ISHTARR_CENTRAL_TOWER:
      newEnemy = AddInhabitant(location, ZOMBIE);
      break;
    case ISHTARR_DUNGEON:
      newEnemy = AddInhabitant(location, ZOMBIE);
      break;
    case SHORE_NE:
      break;
    case SHORE_EAST:
      break;
    case SHORE_SE:
      break;
    case OCEAN_SURFACE:
      break;
    case OCEAN_SHALLOW:
      newEnemy = AddInhabitant(location, SHARK);
      break;
    case OCEAN_DEEP:
      newEnemy = AddInhabitant(location, GIANT_SQUID);
      break;
    case OCEAN_TRENCH:
      newEnemy = AddInhabitant(location, GIANT_SQUID);
      break;
    case QUELACENTUS_ENTRANCE:
      newEnemy = AddInhabitant(location, MERFOLK_SOLDIER);
      break;
    case QUELACENTUS_PLAZA:
      newEnemy = AddInhabitant(location, MERFOLK_SOLDIER);
      break;
    case QUELACENTUS_TEMPLE:
      newEnemy = AddInhabitant(location, MERFOLK_SOLDIER);
      break;
    case QUELACENTUS_PALACE:
      newEnemy = AddInhabitant(location, MERFOLK_SOLDIER);
      break;
    default:
#ifdef DEBUG
      ERROR_MESSAGE
#endif
      break;
  }
  if (newEnemy != NULL)
  {
    AddEnemy(newEnemy);
    return SUCCESS;
  }

  return FAILURE;
}

/******************************************************************************
   Function: RemoveEnemy

Description: Removes a pointer to a given enemy from the global "enemyNPCs"
             array (does NOT remove the enemy from the "world" or deallocate
             its associated memory).

     Inputs: pGC - Pointer to the game character to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int RemoveEnemy(GameCharacter *pGC)
{
  int i, j; /* for loop variables */

  if (pGC == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  pGC->status[IN_COMBAT] = FALSE;
  for (i = 0; i < MAX_ENEMIES; i++)
  {
    if (enemyNPCs[i] == pGC)
    {
        /* Remove the pointer to "pGC".                                      */
      enemyNPCs[i] = NULL;
        /* If any active pointers existed past "pGC", shift them left.       */
      for (j = i + 1;
           j < MAX_ENEMIES && enemyNPCs[j] != NULL;
           j++, i++)
      {
        enemyNPCs[i] = enemyNPCs[j];
        enemyNPCs[j] = NULL;
      }
      return SUCCESS;
    }
  }

    /* If we reach this point, "pGC" was not found.                          */
#ifdef DEBUG
  ERROR_MESSAGE
#endif
  return FAILURE;
}

/******************************************************************************
   Function: DeleteEnemy

Description: Removes a pointer to a given enemy from the global "enemyNPCs"
             array, then removes the enemy from the "world" and deallocates its
             associated memory.

     Inputs: pGC - Pointer to the game character to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int DeleteEnemy(GameCharacter *pGC)
{
  if (RemoveEnemy(pGC) == SUCCESS)
  {
    DeleteInhabitant(world[pGC->locationID], pGC);
  }
  else
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: NumberOfEnemies

Description: Returns the number of enemies pointed to by the global array
             "enemyNPCs".

     Inputs: None.

    Outputs: The number of active pointers in "enemyNPCs".
******************************************************************************/
int NumberOfEnemies(void)
{
  int i;
  for (i = 0; i < MAX_ENEMIES && enemyNPCs[i] != NULL; i++)
    ;
  return i;
}

/******************************************************************************
   Function: VisibleEnemies

Description: Returns the number of visible enemies.

     Inputs: None.

    Outputs: The number of visible enemies.
******************************************************************************/
int VisibleEnemies(void)
{
  int i;         /* for loop counter           */
  int count = 0; /* Number of visible enemies. */

  if (player.status[IN_COMBAT] == FALSE)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return count;
  }
  else
  {
    for (i = 0; i < MAX_ENEMIES && enemyNPCs[i] != NULL; i++)
    {
      if (enemyNPCs[i]->status[INVISIBLE] == FALSE)
      {
        count++;
      }
    }
  }

  return count;
}

/******************************************************************************
   Function: Combat

Description: Handles combat situations between the player and NPCs by
             displaying relevant information, presenting options, etc.

     Inputs: None.

    Outputs: Returns the number of enemies remaining (usually 0).
******************************************************************************/
int Combat(void)
{
  int i;              /* for loop variable                                   */
  int round = 1;
  char cInput;
  BOOL repeatOptions;
  BOOL playerFirst;   /* TRUE if the player has the initiative.              */
  GameCharacter *pGC; /* For searching through linked lists of GCs.          */

  if (NumberOfEnemies() == 0)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return 0;
  }

  player.status[IN_COMBAT] = TRUE;
  playerFirst = RandomBool();     /* Determine who gets the first round.     */

  do
  {
    printf(
"  ____________\n"
"_/ENEMY STATS \\___________________________________________________________\n"
    );
    for (i = 0; i < MAX_ENEMIES; i++)
    {
      if (enemyNPCs[i] == NULL)
      {
        break;
      }
      PrintCombatStatus(enemyNPCs[i]);
      if (enemyNPCs[i]->summonedCreature != NULL)
      {
        printf("%s's summoned creature: ", enemyNPCs[i]->name);
        PrintCombatStatus(enemyNPCs[i]->summonedCreature);
      }
    }
    printf(
"  ____________\n"
"_/PLAYER STATS\\___________________________________________________________\n"
    );
    for (pGC = &player; pGC != NULL; pGC = pGC->next)
    {
      PrintCombatStatus(pGC);
    }
    if (player.summonedCreature != NULL)
    {
      PrintCombatStatus(player.summonedCreature);
    }
    printf("\n");

    if (round > 1 || playerFirst) /* Check initiative only on the 1st round. */
    {
        /* --PLAYER'S TURN-- */
      do
      {
        repeatOptions = FALSE;
        printf("Choose an action:\n"
               "[A]ttack\n"
               "[C]ast a Spell\n"
               "[U]se an Item\n"
               "[F]lee\n"
               "[Q]uit (Return to Main Menu)\n");
        GetCharInput(&cInput);
        switch (cInput)
        {
          case 'A': /* Attack */
            if (AttackMenu() == FAILURE)
            {
              repeatOptions = TRUE;
            }
            break;
          case 'C': /* Cast a Spell */
            if (SpellMenu() == FAILURE)
            {
              repeatOptions = TRUE;
            }
            break;
          case 'U': /* Use an Item */
            if (ItemMenu() == FAILURE)
            {
              repeatOptions = TRUE;
            }
            break;
          case 'F': /* Flee */
            if (enemyNPCs[0]->ID == DUMMY)  /*Indicates tutorial mode.       */
            {
              printf("%s: \"Um...why are you backing away? Just destroy the "
                     "dummy already!\"\n",
                     FindInhabitant(ARCHWIZARD_OF_ELEMENTS)->name);
              FlushInput();
              repeatOptions = TRUE;
            }
            else if (RandomInt(1, 3) == 1)
            {
              printf("You have successfully fled.\n");
              FlushInput();
              while (NumberOfEnemies() > 0)
              {
                RemoveEnemy(enemyNPCs[0]);
              }
              player.status[IN_COMBAT] = FALSE;
              MovementMenu();
            }
            else
            {
              printf("Your attempt to escape has failed.\n");
              FlushInput();
            }
            break;
          case 'Q': /* Quit */
            if (GetExitConfirmation())
            {
              return 0;
            }
            else
            {
              repeatOptions = TRUE;
            }
            break;
          default:
            printf("Invalid response.\n\n");
            repeatOptions = TRUE;
            break;
        }
      }while (repeatOptions);
      CheckStatus();

        /* Increment "round" here if the NPCs had the initiative.            */
      if (!playerFirst)
      {
        round++;
      }
    }

      /* --THE ENEMY'S TURN-- */
    for (i = 0; i < NumberOfEnemies(); i++)
    {
      EnemyAI(i);
    }
    printf("\n");
    CheckStatus();

      /* Increment "round" here if the player had the initiative.            */
    if (playerFirst)
    {
      round++;
    }
  }while (player.currentHP > 0 && NumberOfEnemies() > 0);
  player.status[IN_COMBAT] = FALSE;

  return NumberOfEnemies();
}

/******************************************************************************
   Function: PrintCombatStatus

Description: Prints some basic, combat-relevant information about a given game
             character.

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: None.
******************************************************************************/
void PrintCombatStatus(GameCharacter *pGC)
{
  if (pGC == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return;
  }

  printf("%s (%d/%d", pGC->name, pGC->currentHP, pGC->maxHP);
  /* Code for printing status will go here... */
  printf(")\n");
}

/******************************************************************************
   Function: EnemyAI

Description: Handles enemy NPC decision-making during combat.

     Inputs: index - The index value of the active enemy in the "enemyNPCs"
                     array.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int EnemyAI(int index)
{
  int i;  /* for loop variable */
  BOOL actionPerformed = FALSE;
  GameCharacter *gcTargets[MAX_TARGETS] = {NULL};

  if (enemyNPCs[index] == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  if (enemyNPCs[index]->status[INANIMATE] == TRUE)
  {
    return SUCCESS;
  }
  else if (IsSpellcaster(enemyNPCs[index]))
  {
    if (RandomInt(1, 10) > 1)  /* 90% chance of casting a spell.             */
    {
      for (i = 0; i < NumberOfEnemies(); i++)
      {
        if (enemyNPCs[i]->currentHP <= (enemyNPCs[i]->maxHP / 4) &&
            enemyNPCs[i]->words[WORD_OF_HEALTH] == KNOWN)
        {
          gcTargets[0] = enemyNPCs[i];
          CastSpell(enemyNPCs[index], "Y", gcTargets);  /* Healing spell.    */
          actionPerformed = TRUE;
        }
      }
      while (actionPerformed == FALSE)
      {
        if (enemyNPCs[i]->words[WORD_OF_FIRE] == KNOWN ||
            enemyNPCs[i]->words[WORD_OF_AIR] == KNOWN ||
            enemyNPCs[i]->words[WORD_OF_WATER] == KNOWN ||
            enemyNPCs[i]->words[WORD_OF_EARTH] == KNOWN)
        switch (RandomInt(1, 4))
        {
          case 1:
            if (enemyNPCs[i]->words[WORD_OF_AIR] == KNOWN)
            {
              gcTargets[0] = &player;
              CastSpell(enemyNPCs[index], "E", gcTargets);   /* Wind spell.  */
              actionPerformed = TRUE;
            }
            break;
          case 2:
            if (enemyNPCs[i]->words[WORD_OF_WATER] == KNOWN)
            {
              gcTargets[0] = &player;
              CastSpell(enemyNPCs[index], "S", gcTargets);   /* Water spell. */
              actionPerformed = TRUE;
            }
            break;
          case 3:
            if (enemyNPCs[i]->words[WORD_OF_EARTH] == KNOWN)
            {
              gcTargets[0] = &player;
              CastSpell(enemyNPCs[index], "P", gcTargets);   /* Earth spell. */
              actionPerformed = TRUE;
            }
            break;
          default:
            if (enemyNPCs[i]->words[WORD_OF_FIRE] == KNOWN)
            {
              gcTargets[0] = &player;
              CastSpell(enemyNPCs[index], "B", gcTargets);   /* Fire spell.  */
              actionPerformed = TRUE;
            }
            break;
        }
      }
    }
    else
    {
      Attack(enemyNPCs[index], &player);
    }
  }
  else /* The active NPC is not a spellcaster. */
  {
    Attack(enemyNPCs[index], &player);
  }

  return SUCCESS;
}

/******************************************************************************
   Function: AttackMenu

Description: Takes the player through the process of selecting a game character
             to attack.

     Inputs: None.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int AttackMenu(void)
{
  int i;                 /* for loop variable                                */
  int iInput;
  BOOL repeatOptions;
  int temp;
  GameCharacter *target; /* To select a target from a list of inhabitants.   */

  if (enemyNPCs[0] != NULL && enemyNPCs[0]->ID == DUMMY)
  {
    printf("%s: \"This isn't a training camp for soldiers, %s, and you're a "
           "wizard, not a warrior. Why rely on physical attacks when you can "
           "cast spells?\"\n", FindInhabitant(ARCHWIZARD_OF_ELEMENTS)->name,
           player.name);
    FlushInput();
    return FAILURE;
  }

  UpdateVisibleGameCharCounter();
  temp = 0;
  for (i = 0; i < TOTAL_GC_IDS; i++)
  {
    gcDescribed[i] = FALSE;
  }

    /* Potential targets are displayed (unless only one is available).       */
  if (player.status[IN_COMBAT])
  {
    if (VisibleEnemies() == 1)
    {
      Attack(&player, enemyNPCs[0]);
      return SUCCESS;
    }
    else
    {
      printf("Select a target:\n");
      for (i = 0; i < NumberOfEnemies(); i++)
      {
        if (enemyNPCs[i]->status[INVISIBLE] == FALSE &&
            gcDescribed[enemyNPCs[i]->ID] == FALSE)
        {
          temp++;
          printf("[%d] %s", temp, enemyNPCs[i]->name);
          if (visibleGameCharCounter[enemyNPCs[i]->ID] > 1)
          {
            printf(" (%d available)",
                   visibleGameCharCounter[enemyNPCs[i]->ID]);
          }
          printf("\n");
          gcDescribed[enemyNPCs[i]->ID] = TRUE;
        }
      }
    }
  }
  else  /* Not in combat mode: player attacks a local inhabitant.            */
  {
    if (VisibleInhabitants(world[player.locationID]) == 0)
    {
      printf("There is nobody here to attack.\n");
      FlushInput();
      return FAILURE;
    }
    if (VisibleInhabitants(world[player.locationID]) == 1)
    {
      for (target = world[player.locationID]->inhabitants;
           target != NULL;
           target = target->next)
      {
        if (target->status[INVISIBLE] == FALSE)
        {
          Attack(&player, target);
          return SUCCESS;
        }
      }
    }
    else  /* Multiple visible inhabitants to choose from.                    */
    {
      printf("Select a target:\n");
      for (target = world[player.locationID]->inhabitants;
           target != NULL;
           target = target->next)
      {
        if (target->status[INVISIBLE] == FALSE &&
            gcDescribed[target->ID] == FALSE)
        {
          temp++;
          printf("[%d] %s", temp, target->name);
          if (visibleGameCharCounter[target->ID] > 1)
          {
            printf(" (%d available)", visibleGameCharCounter[target->ID]);
          }
          printf("\n");
          gcDescribed[target->ID] = TRUE;
        }
      }
    }
  }

    /* Player chooses a target by number.                                    */
  GetIntInput(&iInput, 1, temp);

    /* The target is now found, and attacked, by matching it with the input. */
  temp = 0;
  for (i = 0; i < TOTAL_GC_IDS; i++)
  {
    gcDescribed[i] = FALSE;
  }
  if (player.status[IN_COMBAT])
  {
    for (i = 0; i < NumberOfEnemies(); i++)
    {
      if (enemyNPCs[i]->status[INVISIBLE] == FALSE &&
          gcDescribed[enemyNPCs[i]->ID] == FALSE)
      {
        temp++;
        if (temp == iInput)
        {
          Attack(&player, enemyNPCs[i]);
          return SUCCESS;
        }
        gcDescribed[enemyNPCs[i]->ID] = TRUE;
      }
    }
  }
  else  /* Not in combat mode: player attacks a local inhabitant.            */
  {
    for (target = world[player.locationID]->inhabitants;
         target != NULL;
         target = target->next)
    {
      if (target->status[INVISIBLE] == FALSE &&
          gcDescribed[target->ID] == FALSE)
      {
        temp++;
        if (temp == iInput)
        {
          Attack(&player, target);
          if (player.status[IN_COMBAT] == FALSE)
          {
            if (target->currentHP > 0)
            {
              target->relationship = HOSTILE_ENEMY;
              AddEnemy(target);
            }
            else
            {
              PrintNameDefinite(target, TRUE);
              printf(" is dead.\n");
              FlushInput();
            }
            for (target = world[player.locationID]->inhabitants;
                 target != NULL;
                 target = target->next)
            {
              if (WillingToFight(target) && target->status[IN_COMBAT] == FALSE)
              {
                target->relationship = HOSTILE_ENEMY;
                AddEnemy(target);
              }
            }
          }
          if (player.status[IN_COMBAT] == FALSE && NumberOfEnemies() > 0)
          {
            printf("Prepare for battle!\n");
            FlushInput();
            Combat();
          }
          return SUCCESS;
        }
        gcDescribed[target->ID] = TRUE;
      }
    }
  }

#ifdef DEBUG
  ERROR_MESSAGE
#endif
  return FAILURE;
}

/******************************************************************************
   Function: Attack

Description: Handles a physical attack between two game characters.

     Inputs: attacker - The GC performing the attack.
             defender - The GC being attacked.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int Attack(GameCharacter *attacker, GameCharacter *defender)
{
  int damage;

  if (attacker == NULL || defender == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  printf("%s attacks %s", attacker->name, defender->name);
  if (RandomInt(1, 10) > 2)  /* 80% chance of a successful hit.              */
  {
    damage = RandomInt(1, attacker->physicalPower);
    damage -= RandomInt(0, defender->physicalDefense);
    if (damage <= 0)
    {
      damage = 1;
    }
    defender->currentHP -= damage;
    printf(" for %d damage.", damage);
  }
  else
  {
    printf(", but misses.");
  }
  FlushInput();

  return SUCCESS;
}

/******************************************************************************
   Function: WillingToFight

Description: Determines whether a given NPC will fight the player if the player
             is openly hostile to another NPC in the area.

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: TRUE or FALSE.
******************************************************************************/
BOOL WillingToFight(GameCharacter *pGC)
{
  if (pGC->ID == SOLDIER || pGC->ID == KNIGHT || pGC->ID == WIZARD ||
      pGC->ID == INNKEEPER || pGC->ID == FISHERMAN || pGC->ID == SAILOR ||
      pGC->ID == FARMER || pGC->ID == ILLARUM_PRIEST ||
      pGC->ID == ILLARUM_HIGH_PRIEST || pGC->ID == ARCHWIZARD_OF_ELEMENTS ||
      pGC->ID == COURT_WIZARD || pGC->ID == WIZARD_OF_ELEMENTS ||
      pGC->ID == WIZARD_OF_MIND || pGC->ID == ARCHWIZARD_OF_MIND ||
      pGC->ID == VENTARRIS_PRIEST || pGC->ID == BARBARIAN_WARRIOR ||
      pGC->ID == VENTARRIS_HIGH_PRIEST || pGC->ID == BARBARIAN ||
      pGC->ID == BARBARIAN_SHAMAN || pGC->ID == BARBARIAN_CHIEFTAIN ||
      pGC->ID == ELF || pGC->ID == DWARF_MERCHANT || pGC->ID == DWARF_PRIEST ||
      pGC->ID == ELF_LOREMASTER || pGC->ID == DWARF || pGC->ID == DWARF_KING ||
      pGC->ID == DWARF_MINER || pGC->ID == DWARF_GUARDIAN ||
      pGC->ID == DWARF_LOREMASTER || pGC->ID == DWARF_HIGH_PRIEST ||
      pGC->ID == GNOME || pGC->ID == GNOME_MINER || pGC->ID == DRUID ||
      pGC->ID == ARCHDRUID || pGC->ID == MERFOLK_SOLDIER ||
      pGC->ID == MERFOLK_PRIESTESS || pGC->ID == MERFOLK_HIGH_PRIESTESS ||
      pGC->ID == MERFOLK_QUEEN || pGC->ID == VENTARRIS_KING ||
      pGC->ID == ILLARUM_KING || pGC->ID == LICH || pGC->ID == NECROMANCER ||
      pGC->ID == ARCHNECROMANCER || pGC->ID == SKELETAL_KNIGHT)
  {
    return TRUE;
  }

  return FALSE;
}

/******************************************************************************
   Function: WillingToFlee

Description: Determines whether a given NPC will flee when losing a fight.

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: TRUE or FALSE.
******************************************************************************/
BOOL WillingToFlee(GameCharacter *pGC)
{
  return pGC->ID == PEASANT ||
         pGC->ID == SOLDIER ||
         pGC->ID == WIZARD ||
         pGC->ID == INNKEEPER ||
         pGC->ID == FISHERMAN ||
         pGC->ID == SAILOR ||
         pGC->ID == FARMER ||
         pGC->ID == ILLARUM_PRIEST ||
         pGC->ID == ILLARUM_HIGH_PRIEST ||
         pGC->ID == ARCHWIZARD_OF_ELEMENTS ||
         pGC->ID == COURT_WIZARD ||
         pGC->ID == WIZARD_OF_ELEMENTS ||
         pGC->ID == WIZARD_OF_MIND ||
         pGC->ID == ARCHWIZARD_OF_MIND ||
         pGC->ID == VENTARRIS_PRIEST ||
         pGC->ID == VENTARRIS_HIGH_PRIEST ||
         pGC->ID == ELF ||
         pGC->ID == DWARF_MERCHANT ||
         pGC->ID == DWARF_PRIEST ||
         pGC->ID == ELF_LOREMASTER ||
         pGC->ID == GNOME ||
         pGC->ID == GNOME_MINER ||
         pGC->ID == DRUID ||
         pGC->ID == ARCHDRUID ||
         pGC->ID == VENTARRIS_KING ||
         pGC->ID == NECROMANCER ||
         pGC->ID == ARCHNECROMANCER;
}

/******************************************************************************
   Function: WillingToHelp

Description: Determines whether a given NPC will assist allies during combat
             (by healing them, for example).

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: TRUE or FALSE.
******************************************************************************/
BOOL WillingToHelp(GameCharacter *pGC)
{
  if (pGC->ID == SOLDIER || pGC->ID == KNIGHT || pGC->ID == WIZARD ||
      pGC->ID == INNKEEPER || pGC->ID == FISHERMAN || pGC->ID == SAILOR ||
      pGC->ID == FARMER || pGC->ID == ILLARUM_PRIEST ||
      pGC->ID == ILLARUM_HIGH_PRIEST || pGC->ID == ARCHWIZARD_OF_ELEMENTS ||
      pGC->ID == COURT_WIZARD || pGC->ID == WIZARD_OF_ELEMENTS ||
      pGC->ID == WIZARD_OF_MIND || pGC->ID == ARCHWIZARD_OF_MIND ||
      pGC->ID == VENTARRIS_PRIEST || pGC->ID == BARBARIAN_WARRIOR ||
      pGC->ID == VENTARRIS_HIGH_PRIEST || pGC->ID == BARBARIAN ||
      pGC->ID == BARBARIAN_SHAMAN || pGC->ID == BARBARIAN_CHIEFTAIN ||
      pGC->ID == ELF || pGC->ID == DWARF_MERCHANT || pGC->ID == DWARF_PRIEST ||
      pGC->ID == ELF_LOREMASTER || pGC->ID == DWARF || pGC->ID == DWARF_KING ||
      pGC->ID == DWARF_MINER || pGC->ID == DWARF_GUARDIAN ||
      pGC->ID == DWARF_LOREMASTER || pGC->ID == DWARF_HIGH_PRIEST ||
      pGC->ID == GNOME || pGC->ID == GNOME_MINER || pGC->ID == DRUID ||
      pGC->ID == ARCHDRUID || pGC->ID == MERFOLK_SOLDIER ||
      pGC->ID == MERFOLK_PRIESTESS || pGC->ID == MERFOLK_HIGH_PRIESTESS ||
      pGC->ID == MERFOLK_QUEEN || pGC->ID == VENTARRIS_KING ||
      pGC->ID == ILLARUM_KING)
  {
    return TRUE;
  }

  return FALSE;
}
