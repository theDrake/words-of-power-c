/******************************************************************************
   Filename: combat.c

     Author: David C. Drake (http://davidcdrake.com)

Description: Functions governing enemies and combat for the text-based fantasy
             RPG "Words of Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: AddEnemy

Description: Given an already existing game character, adds a pointer to it in
             the global "g_enemies" array.

     Inputs: pGC - Pointer to the game character to be added.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int AddEnemy(game_character_t *pGC) {
  int i;

  if (pGC == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  for (i = 0; i < MAX_ENEMIES; i++) {
    if (g_enemies[i] == NULL) {
      g_enemies[i] = pGC;
      pGC->status[IN_COMBAT] = true;

      return SUCCESS;
    }
  }

  // If we reach this point, "g_enemies" was full and the add failed.
#if DEBUG
  PRINT_ERROR_MESSAGE;
#endif
  return FAILURE;
}

/******************************************************************************
   Function: AddRandomEnemy

Description: Creates a new game character and adds a pointer to it in the local
             "inhabitants" array as well as the the global "g_enemies" array,
             unless no random enemy is associated with the given location, in
             which case nothing happens.

     Inputs: location - Pointer to the location in which to add a random enemy.

    Outputs: SUCCESS if an enemy is added, otherwise FAILURE.
******************************************************************************/
int AddRandomEnemy(location_t *location) {
  game_character_t *newEnemy = NULL;

  if (location == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  switch (location->ID) {
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
      if (g_player.soul <= EVIL) {
        newEnemy = AddInhabitant(location, ELF);
      } else {
        newEnemy = AddInhabitant(location, BEAR);
      }
      break;
    case DRUIDS_GROVE:
      break;
    case HERMIT_HUT:
      break;
    case WYNNFAER_ENTRANCE:
      if (g_player.soul <= EVIL) {
        newEnemy = AddInhabitant(location, ELF);
      }
      break;
    case WYNNFAER_PLAZA:
      if (g_player.soul <= EVIL) {
        newEnemy = AddInhabitant(location, ELF);
      }
      break;
    case WYNNFAER_PALACE:
      if (g_player.soul <= EVIL) {
        newEnemy = AddInhabitant(location, ELF);
      }
      break;
    case MOUNTAINS:
      newEnemy = AddInhabitant(location, GOBLIN);
      break;
    case GESHTAL:
      if (g_player.soul <= EVIL) {
        newEnemy = AddInhabitant(location, BARBARIAN);
      }
      break;
    case TORR_ENTRANCE:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_MARKET:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_SCHOOL:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_TEMPLE:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_THRONE_ROOM:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_MINE:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_VAULT:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case TORR_PRISON:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, DWARF);
      }
      break;
    case GUGGENHOLM_ENTRANCE:
      newEnemy = AddInhabitant(location, GOBLIN);
      break;
    case GUGGENHOLM_MAIN:
      if (g_player.soul <= VERY_EVIL) {
        newEnemy = AddInhabitant(location, GNOME);
      }
      break;
    case GUGGENHOLM_MINE:
      if (g_player.soul <= VERY_EVIL) {
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
#if DEBUG
      PRINT_ERROR_MESSAGE;
#endif
      break;
  }
  if (newEnemy != NULL) {
    AddEnemy(newEnemy);
    return SUCCESS;
  }

  return FAILURE;
}

/******************************************************************************
   Function: RemoveEnemy

Description: Removes a pointer to a given enemy from the global "g_enemies"
             array (does NOT remove the enemy from the "world" or deallocate
             its associated memory).

     Inputs: pGC - Pointer to the game character to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int RemoveEnemy(game_character_t *pGC) {
  int i, j;

  if (pGC == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  pGC->status[IN_COMBAT] = false;
  for (i = 0; i < MAX_ENEMIES; i++) {
    if (g_enemies[i] == pGC) {
      g_enemies[i] = NULL;
      // If any active pointers existed past "pGC", shift them left:
      for (j = i + 1;
           j < MAX_ENEMIES && g_enemies[j] != NULL;
           j++, i++) {
        g_enemies[i] = g_enemies[j];
        g_enemies[j] = NULL;
      }
      return SUCCESS;
    }
  }

  // If we reach this point, "pGC" was not found.
#if DEBUG
  PRINT_ERROR_MESSAGE;
#endif
  return FAILURE;
}

/******************************************************************************
   Function: DeleteEnemy

Description: Removes a pointer to a given enemy from the global "g_enemies"
             array, then removes the enemy from the "world" and deallocates its
             associated memory.

     Inputs: pGC - Pointer to the game character to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int DeleteEnemy(game_character_t *pGC) {
  if (RemoveEnemy(pGC) == SUCCESS) {
    DeleteInhabitant(g_world[pGC->locationID], pGC);
  } else {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: NumberOfEnemies

Description: Returns the number of enemies pointed to by the global array
             "g_enemies".

     Inputs: None.

    Outputs: The number of active pointers in "g_enemies".
******************************************************************************/
int NumberOfEnemies(void) {
  int i;

  for (i = 0; i < MAX_ENEMIES && g_enemies[i] != NULL; i++)
    ;

  return i;
}

/******************************************************************************
   Function: VisibleEnemies

Description: Returns the number of visible enemies.

     Inputs: None.

    Outputs: The number of visible enemies.
******************************************************************************/
int VisibleEnemies(void) {
  int i, count = 0;

  if (g_player.status[IN_COMBAT] == false) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return count;
  } else {
    for (i = 0; i < MAX_ENEMIES && g_enemies[i] != NULL; i++) {
      if (g_enemies[i]->status[INVISIBLE] == false) {
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
int Combat(void) {
  int i, round = 1;
  char cInput;
  bool repeatOptions, playerFirst;
  game_character_t *pGC;

  if (NumberOfEnemies() == 0) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return 0;
  }

  g_player.status[IN_COMBAT] = true;
  playerFirst = RandomBool();  // Determine who gets the first round.

  do {
    printf("  ____________\n"
           "_/ENEMY STATS \\__________________________________________________"
           "______________\n");
    for (i = 0; i < MAX_ENEMIES; i++) {
      if (g_enemies[i] == NULL) {
        break;
      }
      PrintCombatStatus(g_enemies[i]);
      if (g_enemies[i]->summonedCreature != NULL) {
        printf("%s's summoned creature: ", g_enemies[i]->name);
        PrintCombatStatus(g_enemies[i]->summonedCreature);
      }
    }
    printf("  ____________\n"
           "_/PLAYER STATS\\__________________________________________________"
           "______________\n");
    for (pGC = &g_player; pGC != NULL; pGC = pGC->next) {
      PrintCombatStatus(pGC);
    }
    if (g_player.summonedCreature != NULL) {
      PrintCombatStatus(g_player.summonedCreature);
    }
    printf("\n");

    if (round > 1 || playerFirst) {  // Check initiative only on 1st round.
        /* --PLAYER'S TURN-- */
      do {
        repeatOptions = false;
        printf("Choose an action:\n"
               "[A]ttack\n"
               "[C]ast a Spell\n"
               "[U]se an Item\n"
               "[F]lee\n"
               "[Q]uit (Return to Main Menu)\n");
        GetCharInput(&cInput);
        switch (cInput) {
          case 'A':  // Attack
            if (AttackMenu() == FAILURE) {
              repeatOptions = true;
            }
            break;
          case 'C':  // Cast a Spell
            if (SpellMenu() == FAILURE) {
              repeatOptions = true;
            }
            break;
          case 'U':  // Use an Item
            if (ItemMenu() == FAILURE) {
              repeatOptions = true;
            }
            break;
          case 'F':  // Flee
            if (g_enemies[0]->ID == DUMMY) {  // Indicates tutorial mode.
              printf("%s: \"Come on, destroy the dummy already!\"\n",
                     FindInhabitant(ARCHWIZARD_OF_ELEMENTS)->name);
              FlushInput();
              repeatOptions = true;
            } else if (RandomInt(1, 3) == 1) {
              printf("You have successfully fled.\n");
              FlushInput();
              while (NumberOfEnemies() > 0) {
                RemoveEnemy(g_enemies[0]);
              }
              g_player.status[IN_COMBAT] = false;
              MovementMenu();
            } else {
              printf("Your attempt to escape has failed.\n");
              FlushInput();
            }
            break;
          case 'Q':  // Quit
            if (GetExitConfirmation()) {
              return 0;
            } else {
              repeatOptions = true;
            }
            break;
          default:
            printf("Invalid response.\n\n");
            repeatOptions = true;
            break;
        }
      }while (repeatOptions);
      CheckStatus();

      // Increment "round" here if the NPCs had the initiative:
      if (!playerFirst) {
        round++;
      }
    }

      /* -- ENEMY'S TURN-- */
    for (i = 0; i < NumberOfEnemies(); i++) {
      EnemyAI(i);
    }
    printf("\n");
    CheckStatus();

    // Increment "round" here if the player had the initiative:
    if (playerFirst) {
      round++;
    }
  }while (g_player.currentHP > 0 && NumberOfEnemies() > 0);
  g_player.status[IN_COMBAT] = false;

  return NumberOfEnemies();
}

/******************************************************************************
   Function: PrintCombatStatus

Description: Prints some basic, combat-relevant information about a given game
             character.

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: None.
******************************************************************************/
void PrintCombatStatus(game_character_t *pGC) {
  if (pGC == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return;
  }

  printf("%s (%d/%d", pGC->name, pGC->currentHP, pGC->maxHP);
  // Code for printing status will go here.
  printf(")\n");
}

/******************************************************************************
   Function: EnemyAI

Description: Handles enemy NPC decision-making during combat.

     Inputs: index - The index value of the active enemy in the "g_enemies"
                     array.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int EnemyAI(int index) {
  int i;
  bool actionPerformed = false;
  game_character_t *gcTargets[MAX_TARGETS] = {NULL};

  if (g_enemies[index] == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  if (g_enemies[index]->status[INANIMATE] == true) {
    return SUCCESS;
  } else if (IsSpellcaster(g_enemies[index])) {
    if (RandomInt(1, 10) > 1) {  // 90% chance of casting a spell.
      for (i = 0; i < NumberOfEnemies(); i++) {
        if (g_enemies[i]->currentHP <= (g_enemies[i]->maxHP / 4) &&
            g_enemies[i]->words[WORD_OF_HEALTH] == KNOWN) {
          gcTargets[0] = g_enemies[i];
          CastSpell(g_enemies[index], "Y", gcTargets);  // Healing spell.
          actionPerformed = true;
        }
      }
      while (actionPerformed == false) {
        if (g_enemies[i]->words[WORD_OF_FIRE] == KNOWN ||
            g_enemies[i]->words[WORD_OF_AIR] == KNOWN ||
            g_enemies[i]->words[WORD_OF_WATER] == KNOWN ||
            g_enemies[i]->words[WORD_OF_EARTH] == KNOWN)
        switch (RandomInt(1, 4)) {
          case 1:
            if (g_enemies[i]->words[WORD_OF_AIR] == KNOWN) {
              gcTargets[0] = &g_player;
              CastSpell(g_enemies[index], "E", gcTargets);  // Wind spell.
              actionPerformed = true;
            }
            break;
          case 2:
            if (g_enemies[i]->words[WORD_OF_WATER] == KNOWN) {
              gcTargets[0] = &g_player;
              CastSpell(g_enemies[index], "S", gcTargets);  // Water spell.
              actionPerformed = true;
            }
            break;
          case 3:
            if (g_enemies[i]->words[WORD_OF_EARTH] == KNOWN) {
              gcTargets[0] = &g_player;
              CastSpell(g_enemies[index], "P", gcTargets);  // Earth spell.
              actionPerformed = true;
            }
            break;
          default:
            if (g_enemies[i]->words[WORD_OF_FIRE] == KNOWN) {
              gcTargets[0] = &g_player;
              CastSpell(g_enemies[index], "B", gcTargets);  // Fire spell.
              actionPerformed = true;
            }
            break;
        }
      }
    } else {
      Attack(g_enemies[index], &g_player);
    }
  } else {  // The active NPC is not a spellcaster.
    Attack(g_enemies[index], &g_player);
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
int AttackMenu(void) {
  int i, iInput, temp;
  bool repeatOptions;
  game_character_t *target;

  if (g_enemies[0] != NULL && g_enemies[0]->ID == DUMMY) {
    printf("%s: \"You're a wizard, not a warrior. Cast a spell!\"\n",
           FindInhabitant(ARCHWIZARD_OF_ELEMENTS)->name);
    FlushInput();
    return FAILURE;
  }

  UpdateVisibleGameCharCounter();
  temp = 0;
  for (i = 0; i < NUM_GC_IDS; i++) {
    g_character_type_described[i] = false;
  }

  // Display potential targets (unless only one is available):
  if (g_player.status[IN_COMBAT]) {
    if (VisibleEnemies() == 1) {
      Attack(&g_player, g_enemies[0]);
      return SUCCESS;
    } else {
      printf("Select a target:\n");
      for (i = 0; i < NumberOfEnemies(); i++) {
        if (g_enemies[i]->status[INVISIBLE] == false &&
            g_character_type_described[g_enemies[i]->ID] == false) {
          temp++;
          printf("[%d] %s", temp, g_enemies[i]->name);
          if (g_num_visible_of_type[g_enemies[i]->ID] > 1) {
            printf(" (%d available)",
                   g_num_visible_of_type[g_enemies[i]->ID]);
          }
          printf("\n");
          g_character_type_described[g_enemies[i]->ID] = true;
        }
      }
    }
  } else {  // Not in combat mode: player attacks a local inhabitant.
    if (VisibleInhabitants(g_world[g_player.locationID]) == 0) {
      printf("There is nobody here to attack.\n");
      FlushInput();
      return FAILURE;
    }
    if (VisibleInhabitants(g_world[g_player.locationID]) == 1) {
      for (target = g_world[g_player.locationID]->inhabitants;
           target != NULL;
           target = target->next) {
        if (target->status[INVISIBLE] == false) {
          Attack(&g_player, target);
          return SUCCESS;
        }
      }
    } else {  // Multiple visible inhabitants to choose from.
      printf("Select a target:\n");
      for (target = g_world[g_player.locationID]->inhabitants;
           target != NULL;
           target = target->next) {
        if (target->status[INVISIBLE] == false &&
            g_character_type_described[target->ID] == false) {
          temp++;
          printf("[%d] %s", temp, target->name);
          if (g_num_visible_of_type[target->ID] > 1) {
            printf(" (%d available)", g_num_visible_of_type[target->ID]);
          }
          printf("\n");
          g_character_type_described[target->ID] = true;
        }
      }
    }
  }

  // Player chooses a target by number:
  GetIntInput(&iInput, 1, temp);

  // Target is now found, and attacked, by matching it with the input:
  temp = 0;
  for (i = 0; i < NUM_GC_IDS; i++) {
    g_character_type_described[i] = false;
  }
  if (g_player.status[IN_COMBAT]) {
    for (i = 0; i < NumberOfEnemies(); i++) {
      if (g_enemies[i]->status[INVISIBLE] == false &&
          g_character_type_described[g_enemies[i]->ID] == false) {
        temp++;
        if (temp == iInput) {
          Attack(&g_player, g_enemies[i]);
          return SUCCESS;
        }
        g_character_type_described[g_enemies[i]->ID] = true;
      }
    }
  } else {  // Not in combat mode: player attacks a local inhabitant.
    for (target = g_world[g_player.locationID]->inhabitants;
         target != NULL;
         target = target->next) {
      if (target->status[INVISIBLE] == false &&
          g_character_type_described[target->ID] == false) {
        temp++;
        if (temp == iInput) {
          Attack(&g_player, target);
          if (g_player.status[IN_COMBAT] == false) {
            if (target->currentHP > 0) {
              target->relationship = HOSTILE_ENEMY;
              AddEnemy(target);
            } else {
              printf("%s is dead.\n", Capitalize(GetNameDefinite(target)));
              FlushInput();
            }
            for (target = g_world[g_player.locationID]->inhabitants;
                 target != NULL;
                 target = target->next) {
              if (WillingToFight(target) && target->status[IN_COMBAT] == false) {
                target->relationship = HOSTILE_ENEMY;
                AddEnemy(target);
              }
            }
          }
          if (g_player.status[IN_COMBAT] == false && NumberOfEnemies() > 0) {
            printf("Prepare for battle!\n");
            FlushInput();
            Combat();
          }
          return SUCCESS;
        }
        g_character_type_described[target->ID] = true;
      }
    }
  }

#if DEBUG
  PRINT_ERROR_MESSAGE;
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
int Attack(game_character_t *attacker, game_character_t *defender) {
  int damage;

  if (attacker == NULL || defender == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  printf("%s attacks %s", attacker->name, defender->name);
  if (RandomInt(1, 10) > 2) {  // 80% chance of a successful hit.
    damage = RandomInt(1, attacker->physicalPower);
    damage -= RandomInt(0, defender->physicalDefense);
    if (damage <= 0) {
      damage = 1;
    }
    defender->currentHP -= damage;
    printf(" for %d damage.", damage);
  } else {
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

    Outputs: true or false.
******************************************************************************/
bool WillingToFight(game_character_t *pGC) {
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
      pGC->ID == ARCHNECROMANCER || pGC->ID == SKELETAL_KNIGHT) {
    return true;
  }

  return false;
}

/******************************************************************************
   Function: WillingToFlee

Description: Determines whether a given NPC will flee when losing a fight.

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: true or false.
******************************************************************************/
bool WillingToFlee(game_character_t *pGC) {
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

    Outputs: true or false.
******************************************************************************/
bool WillingToHelp(game_character_t *pGC) {
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
      pGC->ID == ILLARUM_KING) {
    return true;
  }

  return false;
}
