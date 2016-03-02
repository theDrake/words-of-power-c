/******************************************************************************
   Filename: magic.c

     Author: David C. Drake (http://davidcdrake.com)

Description: Functions governing magic for the text-based fantasy RPG "Words of
             Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: SpellMenu

Description: Takes the player through the process of selecting targets and
             creating a spell sequence. (The spell's effects are then processed
             via "CastSpell()".)

     Inputs: None.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int SpellMenu(void) {
  int i, iInput, temp, spellLength, numTargets = 0;
  bool repeatOptions;
  char spell[MAX_SPELL_LEN + 1];
  game_character_t *p_gc, *gcTargets[MAX_TARGETS];

    /* --STATUS CHECK-- */

  if (g_player.status[SILENCED]) {
    printf("You have been silenced and cannot cast spells at this time.\n");
    FlushInput();

    return FAILURE;
  }

    /* --SELECTION OF TARGET(S)-- */

  printf("Select a target:\n");
  UpdateVisibleGameCharCounter();
  for (i = 0; i < MAX_TARGETS; i++) {
    gcTargets[i] = NULL;
  }
  do {
    temp = 0;
    for (i = 0; i < NUM_GC_TYPES; i++) {
      g_character_type_described[i] = false;
    }
    if (CanCastBeneficialSpells(&g_player)) {
      if (Targeted(&g_player, gcTargets) == false) {
        temp++;
        printf("[%d] Myself\n", temp);
      }
      if (g_player.summonedCreature != NULL &&
          Targeted(g_player.summonedCreature, gcTargets) == false) {
        temp++;
        printf("[%d] My summoned %s\n", temp, p_gc->descriptor);
      }
      for (p_gc = g_player.next;
           p_gc != NULL && Targeted(p_gc, gcTargets) == false;
           p_gc = p_gc->next) {
        temp++;
        printf("[%d] My companion, %s\n", GetNameDefinite(p_gc));
      }
    }
    if (g_player.status[IN_COMBAT]) {  /* Combat mode: display enemies. */
      for (i = 0; i < NumberOfEnemies(); i++) {
        if (g_enemies[i]->status[INVISIBLE] == false &&
            Targeted(g_enemies[i], gcTargets) == false &&
            g_character_type_described[g_enemies[i]->type] == false) {
          temp++;
          if (g_num_visible_of_type[g_enemies[i]->type] > 1) {
            printf("[%d] %s (%d available)\n", temp,
                   g_enemies[i]->name,
                   g_num_visible_of_type[g_enemies[i]->type]);
          } else {
            printf("[%d] %s\n", temp, g_enemies[i]->name);
          }
          g_character_type_described[g_enemies[i]->type] = true;
        }
      }
    } else {  /* Not in combat mode: display local inhabitants. */
      for (p_gc = g_world[g_player.locationID]->inhabitants;
           p_gc != NULL;
           p_gc = p_gc->next) {
        if (p_gc->status[INVISIBLE] == false &&
            Targeted(p_gc, gcTargets) == false &&
            g_character_type_described[p_gc->type] == false) {
          temp++;
          if (g_num_visible_of_type[p_gc->type] > 1) {
            printf("[%d] %s (%d available)\n", temp,
                   p_gc->name,
                   g_num_visible_of_type[p_gc->type]);
          } else {
            printf("[%d] %s\n", temp, p_gc->name);
          }
          g_character_type_described[p_gc->type] = true;
        }
      }
    }
    if (temp == 0) {
      printf("There is nobody here to target for a spell.\n");
      FlushInput();
      return FAILURE;
    }

      /* Player chooses a target by number. */
    GetIntInput(&iInput, 1, temp);

      /* The target is now found by matching it with the input. */
    temp = 0;
    for (i = 0; i < NUM_GC_TYPES; i++) {
      g_character_type_described[i] = false;
    }
    if (CanCastBeneficialSpells(&g_player)) {
      if (Targeted(&g_player, gcTargets) == false) {
        temp++;
        if (temp == iInput) {
          gcTargets[numTargets] = &g_player;
          goto TargetFound;
        }
      }
      if (g_player.summonedCreature != NULL &&
          Targeted(g_player.summonedCreature, gcTargets) == false) {
        temp++;
        if (temp == iInput) {
          gcTargets[numTargets] = g_player.summonedCreature;
          goto TargetFound;
        }
      }
      for (p_gc = g_player.next;
           p_gc != NULL && Targeted(p_gc, gcTargets) == false;
           p_gc = p_gc->next) {
        temp++;
        if (temp == iInput) {
          gcTargets[numTargets] = p_gc;
          goto TargetFound;
        }
      }
    }
    if (g_player.status[IN_COMBAT]) {  /* Combat mode: search through enemies. */
      for (i = 0; i < NumberOfEnemies(); i++) {
        if (g_enemies[i]->status[INVISIBLE] == false &&
            Targeted(g_enemies[i], gcTargets) == false &&
            g_character_type_described[g_enemies[i]->type] == false) {
          temp++;
          if (temp == iInput) {
            gcTargets[numTargets] = g_enemies[i];
            g_num_visible_of_type[g_enemies[i]->type]--;  /* For counting. */
            goto TargetFound;
          }
          g_character_type_described[g_enemies[i]->type] = true;
        }
      }
    } else {  /* Not in combat mode: search through local inhabitants.*/
      for (p_gc = g_world[g_player.locationID]->inhabitants;
           p_gc != NULL;
           p_gc = p_gc->next) {
        if (p_gc->status[INVISIBLE] == false &&
            Targeted(p_gc, gcTargets) == false &&
            g_character_type_described[p_gc->type] == false) {
          gcTargets[numTargets] = g_enemies[i];
          temp++;
          if (temp == iInput) {
            gcTargets[numTargets] = p_gc;
            g_num_visible_of_type[p_gc->type]--;  /* For counting purposes. */
            goto TargetFound;
          }
          g_character_type_described[p_gc->type] = true;
        }
      }
    }
      /* If we reach this point, the target was not found. */
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
      /* If the target was found, we will have jumped to the following line. */
    TargetFound:
    numTargets++;
    repeatOptions = false;

      /* Check for remaining legal targets. */
    /*temp = 0;
    for (i = 0; i < NUM_GC_TYPES; i++) {
      temp += g_num_visible_of_type[i];
    }
    if (temp == 0) {
      repeatOptions = false;
    } else {
      do {
        repeatOptions = false;
        printf("Do you wish to select another target? (Y/N) ");
        GetCharInput(&cInput);
        if (cInput != 'Y' && cInput != 'N') {
          printf("Invalid response. ");
          repeatOptions = true;
        }
      }while (repeatOptions);
      if (input == 'Y') {
        repeatOptions = true;
      }
    }*/
  }while (repeatOptions);  /* Until the player's finished selecting targets. */
  UpdateVisibleGameCharCounter();

    /* --CREATION OF SPELL SEQUENCE-- */

  printf("Use the letters indicated to create a spell sequence of up to %d "
         "letters (letters may be used more than once):\n", MAX_SPELL_LEN);
  PrintKnownWords();
  do {
    repeatOptions = false;
    GetStrInput(spell, MAX_SPELL_LEN + 1);
    spellLength = strlen(spell);
    for (i = 0; i < spellLength; i++) {
      spell[i] = toupper(spell[i]);
      if (GetWordTypeFromChar(spell[i]) < 0 ||
          g_player.words[GetWordTypeFromChar(spell[i])] == UNKNOWN) {
        printf("Invalid spell sequence. Please try again: ");
        repeatOptions = true;
        i = spellLength;
      }
    }
  }while (repeatOptions);

    /* --CASTING OF SPELL-- */

  CastSpell(&g_player, spell, gcTargets);

  return SUCCESS;
}

/******************************************************************************
   Function: CastSpell

Description: Carries out a spell's effects (if any) and reports them to the
             player.

     Inputs: spellcaster - Pointer to the caster of the spell.
             spell       - String of letters, each representing a Word of
                           Power.
             gcTargets   - Array of pointers to targeted game characters.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int CastSpell(game_character_t *spellcaster, char *spell,
              game_character_t *gcTargets[]) {
  bool light = false, dark = false, holy = false, evil = false, giving = false,
       taking = false, increase = false, decrease = false, life = false,
       death = false, shield = false, counter = false, balance = false;
  int i, numTargets, spellLength, fireValue = 0, waterValue = 0, airValue = 0,
      earthValue = 0, damage = 0, backlashValue = 0;
  game_character_t *p_gc; /* To search through lists of game characters.      */

  for (numTargets = 0;
       numTargets < MAX_TARGETS && gcTargets[numTargets] != NULL;
       numTargets++)
    ;
  spellLength = strlen(spell);
  if (spellcaster == NULL || numTargets == 0 || spellLength == 0) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  printf("%s: \"", spellcaster->name);
  for (i = 0; i < spellLength; i++) {
    printf("%s", GetWordStartingWith(spell[i]));
    if (i < spellLength - 1) {
      printf("-");
    } else {
      printf("!\"\n\n");
    }
  }

  if (strcmp(spell, "B") == 0) {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  } else if (strcmp(spell, "BB") == 0) {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(spellcaster->mentalPower * 0.25,
                          spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "BBB") == 0) {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(spellcaster->mentalPower * 0.5,
                          spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  } else if (strcmp(spell, "BBBB") == 0) {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(1, spellcaster->mentalPower);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  } else if (strcmp(spell, "S") == 0) {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  } else if (strcmp(spell, "SS") == 0) {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(spellcaster->mentalPower * 0.25,
                           spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "SSS") == 0) {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(spellcaster->mentalPower * 0.5,
                           spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  } else if (strcmp(spell, "SSSS") == 0) {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  } else if (strcmp(spell, "P") == 0) {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  } else if (strcmp(spell, "PP") == 0) {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(spellcaster->mentalPower * 0.25,
                           spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "PPP") == 0) {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(spellcaster->mentalPower * 0.5,
                           spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  } else if (strcmp(spell, "PPPP") == 0) {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(8, 16) * spellcaster->mentalPower;
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  } else if (strcmp(spell, "E") == 0) {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  } else if (strcmp(spell, "EE") == 0) {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(spellcaster->mentalPower * 0.25,
                         spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "EEE") == 0) {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(spellcaster->mentalPower * 0.5,
                         spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  } else if (strcmp(spell, "EEEE") == 0) {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  } else if (spellLength == 4 &&
             StrContains(spell, 'E') &&
             StrContains(spell, 'S') &&
             StrContains(spell, 'P') &&
             StrContains(spell, 'B')) {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 3; i++) {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  } else if (spellLength == 3 &&
             StrContains(spell, 'S') &&
             StrContains(spell, 'P') &&
             StrContains(spell, 'B')) {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++) {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  } else if (spellLength == 3 &&
             StrContains(spell, 'E') &&
             StrContains(spell, 'S') &&
             StrContains(spell, 'B')) {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++) {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  } else if (spellLength == 3 &&
             StrContains(spell, 'E') &&
             StrContains(spell, 'S') &&
             StrContains(spell, 'P')) {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++)
    {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  } else if (spellLength == 3 &&
             StrContains(spell, 'E') &&
             StrContains(spell, 'P') &&
             StrContains(spell, 'B')) {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++) {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  } else if (strcmp(spell, "BS") == 0 || strcmp(spell, "SB") == 0) {
    printf("A blast of boiling water sprays forth from your outstretched "
           "hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "ES") == 0 || strcmp(spell, "SE") == 0) {
    printf("Shards of ice burst forth from your outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "BE") == 0 || strcmp(spell, "EB") == 0) {
    printf("A bolt of lightning shoots forth from your outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "BP") == 0 || strcmp(spell, "PB") == 0) {
    printf("A stream of lava sprays forth from your outstretched hand!\n");
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "SP") == 0 || strcmp(spell, "PS") == 0) {
    printf("A stream of acid sprays forth from your outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  } else if (strcmp(spell, "EP") == 0 || strcmp(spell, "PE") == 0) {
    printf("A debris-filled whirlwind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  } else {
    printf("Nothing happens.\n");
    FlushInput();
    return SUCCESS;
  }
  for (i = 0; i < numTargets && gcTargets[i] != NULL; i++) {
    damage = fireValue + waterValue + earthValue + airValue;
    damage -= RandomInt(0, gcTargets[i]->physicalDefense / 10);
    if (damage <= 0) {
      printf("%s resists all damage.\n", gcTargets[i]->name);
    } else {
      printf("%s takes %d points of damage.\n", gcTargets[i]->name, damage);
      gcTargets[i]->currentHP -= damage;
      if (spellcaster == &g_player && g_player.status[IN_COMBAT] == false) {
        if (gcTargets[i]->currentHP > 0) {
          gcTargets[i]->relationship = HOSTILE_ENEMY;
          AddEnemy(gcTargets[i]);
        } else {
          printf("%s is dead.\n", Capitalize(GetNameDefinite(gcTargets[i])));
          FlushInput();
        }
        for (p_gc = g_world[g_player.locationID]->inhabitants;
             p_gc != NULL;
             p_gc = p_gc->next) {
          if (WillingToFight(p_gc) && p_gc->status[IN_COMBAT] == false) {
            p_gc->relationship = HOSTILE_ENEMY;
            AddEnemy(p_gc);
          }
        }
      }
    }
  }
  backlashValue -= RandomInt(0, spellcaster->mentalDefense / 4);
  if (backlashValue > 0) {
    spellcaster->currentHP -= backlashValue;
    printf("%s takes %d points of backlash damage.\n", spellcaster->name,
           fireValue);
  }
  FlushInput();
  /*if (spellcaster == &g_player && spellLength == MAX_SPELL_LEN)
  {
    FlushInput(); /* Necessary for effective pausing in this special case.
  }*/

  if (g_player.status[IN_COMBAT] == false && NumberOfEnemies() > 0) {
    printf("Prepare for battle!\n");
    FlushInput();
    Combat();
  }

  return SUCCESS;
}

/******************************************************************************
   Function: Targeted

Description: Determines whether a given game character is contained within a
             given array of targeted game characters.

     Inputs: p_gc       - Pointer to the game character of interest.
             gcTargets - Array of pointers to targeted game characters (assumed
                         to be of length MAX_TARGETS).

    Outputs: true or false.
******************************************************************************/
int Targeted(game_character_t *p_gc, game_character_t *gcTargets[]) {
  int i;

  for (i = 0; i < MAX_TARGETS && gcTargets[i] != NULL; i++) {
    if (gcTargets[i] == p_gc) {
      return true;
    }
  }

  return false;
}

/******************************************************************************
   Function: CanCastBeneficialSpells

Description: Determines whether a given game character is capable of casting
             beneficial spells (i.e., spells that might reasonably target
             oneself).

     Inputs: p_gc - Pointer to the game character of interest.

    Outputs: true if "p_gc" is being targeted, otherwise false.
******************************************************************************/
bool CanCastBeneficialSpells(game_character_t *p_gc) {
  return p_gc->words[WORD_OF_BODY]      == KNOWN ||
         p_gc->words[WORD_OF_MIND]      == KNOWN ||
         p_gc->words[WORD_OF_FLORA]     == KNOWN ||
         p_gc->words[WORD_OF_FAUNA]     == KNOWN ||
         p_gc->words[WORD_OF_LIGHT]     == KNOWN ||
         p_gc->words[WORD_OF_DARKNESS]  == KNOWN ||
         p_gc->words[WORD_OF_HEALTH]    == KNOWN ||
         p_gc->words[WORD_OF_LIFE]      == KNOWN ||
         p_gc->words[WORD_OF_HOLINESS]  == KNOWN ||
         p_gc->words[WORD_OF_EVIL]      == KNOWN ||
         p_gc->words[WORD_OF_INCREASE]  == KNOWN ||
         p_gc->words[WORD_OF_DECREASE]  == KNOWN ||
         p_gc->words[WORD_OF_SHIELDING] == KNOWN ||
         p_gc->words[WORD_OF_TIME]      == KNOWN ||
         p_gc->words[WORD_OF_VOID]      == KNOWN;
}

/******************************************************************************
   Function: PrintKnownWords

Description: Displays each Word of Power the player knows in the following
             format: "[W]ord (Translation)".

     Inputs: None.

    Outputs: Returns the number of Words displayed.
******************************************************************************/
int PrintKnownWords(void) {
  int i, j, wordLength, wordsDisplayed = 0;
  char word[SHORT_STR_LEN + 1];  /* To store, format, and print each Word. */

  for (i = 0; i < NUM_WORD_TYPES; i++) {
    if (g_player.words[i] != UNKNOWN) {
      strcpy(word, GetWord(i));
      wordLength = strlen(word);

        /* The word must have room for 2 more characters: '(' and ')'. */
      if (wordLength >= (SHORT_STR_LEN - 2)) {
#if DEBUG
        PRINT_ERROR_MESSAGE;
#endif
        return wordsDisplayed;
      }
        /* Format the string, beginning at its end and working backwards. */
      for (j = wordLength; j >= 0; j--) {
        switch (j) {
          case 2:
            word[j + 2] = word[j];
            word[j] = ']';
            break;
          case 1:
            word[j + 2] = word[j];
            word[j] = word[j - 1];
            break;
          case 0:
            word[j] = '[';
            break;
          default:
            word[j + 2] = word[j];
            break;
        }
      }
      if (g_player.words[i] == KNOWN) {
        printf("%s (%s)\n", word, GetWordName(i));
      } else {  /* g_player.words[i] == PARTIALLY_KNOWN */
        printf("%s (\?\?\?)\n", word);
      }
      wordsDisplayed++;
    }
  }

  return SUCCESS;
}

/******************************************************************************
   Function: GetWord

Description: Given the ID number of a Word of Power, returns that Word as a
             string.

     Inputs: type - ID of the desired Word.

    Outputs: Pointer to the desired string.
******************************************************************************/
char *GetWord(int type) {
  switch (type) {
    case WORD_OF_AIR:
      return "Ethraem";
    case WORD_OF_WATER:
      return "Saelis";
    case WORD_OF_EARTH:
      return "Pallum";
    case WORD_OF_FIRE:
      return "Beor";
    case WORD_OF_BODY:
      return "Denthaeg";
    case WORD_OF_MIND:
      return "Jurithil";
    case WORD_OF_FLORA:
      return "Wynntal";
    case WORD_OF_FAUNA:
      return "Kerrovax";
    case WORD_OF_LIGHT:
      return "Illum";
    case WORD_OF_DARKNESS:
      return "Xenoth";
    case WORD_OF_HEALTH:
      return "Yaegmass";
    case WORD_OF_SICKNESS:
      return "Grashtmal";
    case WORD_OF_LIFE:
      return "Faerabenthos";
    case WORD_OF_DEATH:
      return "Morpenthaliss";
    case WORD_OF_HOLINESS:
      return "Zerahaelos";
    case WORD_OF_EVIL:
      return "Vashtkallar";
    case WORD_OF_GIVING:
      return "Ollosni";
    case WORD_OF_TAKING:
      return "Neth";
    case WORD_OF_INCREASE:
      return "Rausch";
    case WORD_OF_DECREASE:
      return "Lilth";
    case WORD_OF_BALANCE:
      return "Caerosqueltus";
    case WORD_OF_SHIELDING:
      return "Throm";
    case WORD_OF_WAVES:
      return "Quentas";
    case WORD_OF_FOCUS:
      return "Haem";
    case WORD_OF_TIME:
      return "Ullimaril";
    case WORD_OF_VOID:
      return "Aum";
    default:
      break;
  }

#if DEBUG
  PRINT_ERROR_MESSAGE;
#endif
  return NULL;
}

/******************************************************************************
   Function: GetWordStartingWith

Description: Given the first letter of a Word of Power, returns the entire Word
             as a string.

     Inputs: firstLetter - First letter of the desired Word.

    Outputs: Pointer to the desired string.
******************************************************************************/
char *GetWordStartingWith(char firstLetter) {
  return GetWord(GetWordTypeFromChar(firstLetter));
}

/******************************************************************************
   Function: GetWordName

Description: Returns the English name of a given Word of Power as a string
             (such as "Fire", "Water", etc.).

     Inputs: type - ID of the desired Word.

    Outputs: Pointer to the desired string.
******************************************************************************/
char *GetWordName(int type) {
  switch (type) {
    case WORD_OF_AIR:
      return "Air";
    case WORD_OF_WATER:
      return "Water";
    case WORD_OF_EARTH:
      return "Earth";
    case WORD_OF_FIRE:
      return "Fire";
    case WORD_OF_BODY:
      return "Body";
    case WORD_OF_MIND:
      return "Mind";
    case WORD_OF_FLORA:
      return "Flora";
    case WORD_OF_FAUNA:
      return "Fauna";
    case WORD_OF_LIGHT:
      return "Light";
    case WORD_OF_DARKNESS:
      return "Darkness";
    case WORD_OF_HEALTH:
      return "Health";
    case WORD_OF_SICKNESS:
      return "Sickness";
    case WORD_OF_LIFE:
      return "Life";
    case WORD_OF_DEATH:
      return "Death";
    case WORD_OF_HOLINESS:
      return "Holiness";
    case WORD_OF_EVIL:
      return "Evil";
    case WORD_OF_GIVING:
      return "Give";
    case WORD_OF_TAKING:
      return "Take";
    case WORD_OF_INCREASE:
      return "Increase";
    case WORD_OF_DECREASE:
      return "Decrease";
    case WORD_OF_BALANCE:
      return "Balance";
    case WORD_OF_SHIELDING:
      return "Shield";
    case WORD_OF_WAVES:
      return "Wave";
    case WORD_OF_FOCUS:
      return "Focus";
    case WORD_OF_TIME:
      return "Time";
    case WORD_OF_VOID:
      return "Void";
    default:
      break;
  }

#if DEBUG
  PRINT_ERROR_MESSAGE;
#endif
  return NULL;
}

/******************************************************************************
   Function: GetWordTypeFromChar

Description: Given the first letter of a Word of Power, returns the ID number
             corresponding to that Word. (Requires that no two Words share the
             same first letter.)

     Inputs: firstLetter - First letter of a Word of Power.

    Outputs: ID number for the Word associated with the given letter (or -1 if
             a corresponding ID is not found).
******************************************************************************/
int GetWordTypeFromChar(char firstLetter) {
  int i;
  char *temp; /* To check the first letter of each Word. */

  firstLetter = toupper(firstLetter);
  for (i = 0; i < NUM_WORD_TYPES; i++) {
    temp = GetWord(i);
    if (temp[0] == firstLetter) {
      return i;
    }
  }

#if DEBUG
  PRINT_ERROR_MESSAGE;
#endif
  return -1;
}

/******************************************************************************
   Function: IsSpellcaster

Description: Determines whether a given game character can cast spells.

     Inputs: p_gc - The game character of interest.

    Outputs: true if the GC knows at least one Word, otherwise false.
******************************************************************************/
bool IsSpellcaster(game_character_t *p_gc) {
  int i;

  for (i = 0; i < NUM_WORD_TYPES; i++) {
    if (p_gc->words[i] == KNOWN) {
      return true;
    }
  }

  return false;
}
