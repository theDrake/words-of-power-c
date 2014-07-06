/******************************************************************************
   Filename: magic.c

     Author: David C. Drake (www.davidcdrake.com)

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
int SpellMenu(void)
{
  int i;                         /* for loop variable                        */
  int iInput;
  BOOL repeatOptions;
  int temp;
  int spellLength;               /* Number of Words of Power in the spell.   */
  int numTargets = 0;            /* Number of targets selected.              */
  char spell[MAX_SPELL_LEN + 1]; /* Spell sequence (first letters of Words). */
  GameCharacter *pGC;            /* To search through linked lists of GCs.   */
  GameCharacter *gcTargets[MAX_TARGETS]; /* GC targets (if any).             */

    /* --STATUS CHECK -- */

  if (player.status[SILENCED])
  {
    printf("You have been silenced and thus cannot cast spells at this time."
           "\n");
    FlushInput();
    return FAILURE;
  }

    /* --SELECTION OF TARGET(S)-- */

  printf("Select a target:\n");
  UpdateVisibleGameCharCounter();
  for (i = 0; i < MAX_TARGETS; i++)
  {
    gcTargets[i] = NULL;
  }
  do
  {
    temp = 0;
    for (i = 0; i < TOTAL_GC_IDS; i++)
    {
      gcDescribed[i] = FALSE;
    }
    if (CanCastBeneficialSpells(&player))
    {
      if (Targeted(&player, gcTargets) == FALSE)
      {
        temp++;
        printf("[%d] Myself\n", temp);
      }
      if (player.summonedCreature != NULL &&
          Targeted(player.summonedCreature, gcTargets) == FALSE)
      {
        temp++;
        printf("[%d] My summoned %s\n", temp, pGC->descriptor);
      }
      for (pGC = player.next;
           pGC != NULL && Targeted(pGC, gcTargets) == FALSE;
           pGC = pGC->next)
      {
        temp++;
        printf("[%d] My companion, ");
        PrintNameDefinite(pGC, FALSE);
        printf("\n");
      }
    }
    if (player.status[IN_COMBAT]) /* Combat mode: display enemies.           */
    {
      for (i = 0; i < NumberOfEnemies(); i++)
      {
        if (enemyNPCs[i]->status[INVISIBLE] == FALSE &&
            Targeted(enemyNPCs[i], gcTargets) == FALSE &&
            gcDescribed[enemyNPCs[i]->ID] == FALSE)
        {
          temp++;
          if (visibleGameCharCounter[enemyNPCs[i]->ID] > 1)
          {
            printf("[%d] %s (%d available)\n", temp,
                   enemyNPCs[i]->name,
                   visibleGameCharCounter[enemyNPCs[i]->ID]);
          }
          else
          {
            printf("[%d] %s\n", temp, enemyNPCs[i]->name);
          }
          gcDescribed[enemyNPCs[i]->ID] = TRUE;
        }
      }
    }
    else /* Not in combat mode: display local inhabitants.                   */
    {
      for (pGC = world[player.locationID]->inhabitants;
           pGC != NULL;
           pGC = pGC->next)
      {
        if (pGC->status[INVISIBLE] == FALSE &&
            Targeted(pGC, gcTargets) == FALSE &&
            gcDescribed[pGC->ID] == FALSE)
        {
          temp++;
          if (visibleGameCharCounter[pGC->ID] > 1)
          {
            printf("[%d] %s (%d available)\n", temp,
                   pGC->name,
                   visibleGameCharCounter[pGC->ID]);
          }
          else
          {
            printf("[%d] %s\n", temp, pGC->name);
          }
          gcDescribed[pGC->ID] = TRUE;
        }
      }
    }
    if (temp == 0)
    {
      printf("There is nobody here to target for a spell.\n");
      FlushInput();
      return FAILURE;
    }

      /* Player chooses a target by number.                                  */
    GetIntInput(&iInput, 1, temp);

      /* The target is now found by matching it with the input.              */
    temp = 0;
    for (i = 0; i < TOTAL_GC_IDS; i++)
    {
      gcDescribed[i] = FALSE;
    }
    if (CanCastBeneficialSpells(&player))
    {
      if (Targeted(&player, gcTargets) == FALSE)
      {
        temp++;
        if (temp == iInput)
        {
          gcTargets[numTargets] = &player;
          goto TargetFound;
        }
      }
      if (player.summonedCreature != NULL &&
          Targeted(player.summonedCreature, gcTargets) == FALSE)
      {
        temp++;
        if (temp == iInput)
        {
          gcTargets[numTargets] = player.summonedCreature;
          goto TargetFound;
        }
      }
      for (pGC = player.next;
           pGC != NULL && Targeted(pGC, gcTargets) == FALSE;
           pGC = pGC->next)
      {
        temp++;
        if (temp == iInput)
        {
          gcTargets[numTargets] = pGC;
          goto TargetFound;
        }
      }
    }
    if (player.status[IN_COMBAT]) /* Combat mode: search through enemies.    */
    {
      for (i = 0; i < NumberOfEnemies(); i++)
      {
        if (enemyNPCs[i]->status[INVISIBLE] == FALSE &&
            Targeted(enemyNPCs[i], gcTargets) == FALSE &&
            gcDescribed[enemyNPCs[i]->ID] == FALSE)
        {
          temp++;
          if (temp == iInput)
          {
            gcTargets[numTargets] = enemyNPCs[i];
            visibleGameCharCounter[enemyNPCs[i]->ID]--; /* For counting.     */
            goto TargetFound;
          }
          gcDescribed[enemyNPCs[i]->ID] = TRUE;
        }
      }
    }
    else /* Not in combat mode: search through local inhabitants.            */
    {
      for (pGC = world[player.locationID]->inhabitants;
           pGC != NULL;
           pGC = pGC->next)
      {
        if (pGC->status[INVISIBLE] == FALSE &&
            Targeted(pGC, gcTargets) == FALSE &&
            gcDescribed[pGC->ID] == FALSE)
        {
          gcTargets[numTargets] = enemyNPCs[i];
          temp++;
          if (temp == iInput)
          {
            gcTargets[numTargets] = pGC;
            visibleGameCharCounter[pGC->ID]--; /* For counting purposes.     */
            goto TargetFound;
          }
          gcDescribed[pGC->ID] = TRUE;
        }
      }
    }
      /* If we reach this point, the target was not found.                   */
    #ifdef DEBUG
    ERROR_MESSAGE
    #endif
    return FAILURE;
      /* If the target was found, we will have jumped to the following line. */
    TargetFound:
    numTargets++;

      /* Check for remaining legal targets.                                  */
    /*temp = 0;
    for (i = 0; i < TOTAL_GC_IDS; i++)
    {
      temp += visibleGameCharCounter[i];
    }
    if (temp == 0)
    {
      repeatOptions = FALSE;
    }
    else
    {
      do
      {
        repeatOptions = FALSE;
        printf("Do you wish to select another target? (Y/N) ");
        GetCharInput(&cInput);
        if (cInput != 'Y' && cInput != 'N')
        {
          printf("Invalid response. ");
          repeatOptions = TRUE;
        }
      }while (repeatOptions);
      if (input == 'Y')
      {
        repeatOptions = TRUE;
      }
    }*/
  }while (repeatOptions); /* Until the player is finished selecting targets. */
  UpdateVisibleGameCharCounter();

    /* --CREATION OF SPELL SEQUENCE-- */

  printf("Use the letters indicated to create a spell sequence of up to %d "
         "letters (letters may be used more than once):\n", MAX_SPELL_LEN);
  PrintKnownWords();
  do
  {
    repeatOptions = FALSE;
    GetStrInput(spell, MAX_SPELL_LEN + 1);
    spellLength = strlen(spell);
    for (i = 0; i < spellLength; i++)
    {
      spell[i] = toupper(spell[i]);
      if (WordID(spell[i]) < 0 || player.words[WordID(spell[i])] == UNKNOWN)
      {
        printf("Invalid spell sequence. Please try again: ");
        repeatOptions = TRUE;
        i = spellLength;
      }
    }
  }while (repeatOptions);

    /* --CASTING OF SPELL-- */

  CastSpell(&player, spell, gcTargets);

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
             location    - Pointer to targeted location.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int CastSpell(GameCharacter *spellcaster,
              char *spell,
              GameCharacter *gcTargets[])
{
  BOOL light = FALSE, dark = FALSE, holy = FALSE, evil = FALSE, giving = FALSE,
       taking = FALSE, increase = FALSE, decrease = FALSE, life = FALSE,
       death = FALSE, shield = FALSE, counter = FALSE, balance = FALSE;
  int i, numTargets, spellLength, fireValue = 0, waterValue = 0, airValue = 0,
      earthValue = 0, damage = 0, backlashValue = 0;
  GameCharacter *pGC; /* To search through linked lists of game characters.  */

  for (numTargets = 0;
       numTargets < MAX_TARGETS && gcTargets[numTargets] != NULL;
       numTargets++)
    ;
  spellLength = strlen(spell);
  if (spellcaster == NULL || numTargets == 0 || spellLength == 0)
  {
    #ifdef DEBUG
    ERROR_MESSAGE
    #endif
    return FAILURE;
  }

  printf("%s: \"", spellcaster->name);
  for (i = 0; i < spellLength; i++)
  {
    printf("%s", WordStartingWith(spell[i]));
    if (i < spellLength - 1)
    {
      printf("-");
    }
    else
    {
      printf("!\"\n\n");
    }
  }

  if (strcmp(spell, "B") == 0)
  {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  }
  else if (strcmp(spell, "BB") == 0)
  {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(spellcaster->mentalPower * 0.25,
                          spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "BBB") == 0)
  {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(spellcaster->mentalPower * 0.5,
                          spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  }
  else if (strcmp(spell, "BBBB") == 0)
  {
    printf("Fire bursts forth from your outstretched hand!\n");
    fireValue = RandomInt(1, spellcaster->mentalPower);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  }
  else if (strcmp(spell, "S") == 0)
  {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  }
  else if (strcmp(spell, "SS") == 0)
  {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(spellcaster->mentalPower * 0.25,
                           spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "SSS") == 0)
  {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(spellcaster->mentalPower * 0.5,
                           spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  }
  else if (strcmp(spell, "SSSS") == 0)
  {
    printf("An overpowering stream of water bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  }
  else if (strcmp(spell, "P") == 0)
  {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  }
  else if (strcmp(spell, "PP") == 0)
  {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(spellcaster->mentalPower * 0.25,
                           spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "PPP") == 0)
  {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(spellcaster->mentalPower * 0.5,
                           spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  }
  else if (strcmp(spell, "PPPP") == 0)
  {
    printf("A rain of stones bursts forth from your outstretched hand!\n");
    earthValue = RandomInt(8, 16) * spellcaster->mentalPower;
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  }
  else if (strcmp(spell, "E") == 0)
  {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
  }
  else if (strcmp(spell, "EE") == 0)
  {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(spellcaster->mentalPower * 0.25,
                         spellcaster->mentalPower * 0.5);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "EEE") == 0)
  {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(spellcaster->mentalPower * 0.5,
                         spellcaster->mentalPower * 0.75);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.2);
  }
  else if (strcmp(spell, "EEEE") == 0)
  {
    printf("An overpowering gust of wind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower);
    backlashValue = RandomInt(0, spellcaster->mentalPower * 0.3);
  }
  else if (spellLength == 4 &&
           StrContains(spell, 'E') &&
           StrContains(spell, 'S') &&
           StrContains(spell, 'P') &&
           StrContains(spell, 'B'))
  {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 3; i++)
    {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  }
  else if (spellLength == 3 &&
           StrContains(spell, 'S') &&
           StrContains(spell, 'P') &&
           StrContains(spell, 'B'))
  {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++)
    {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  }
  else if (spellLength == 3 &&
           StrContains(spell, 'E') &&
           StrContains(spell, 'S') &&
           StrContains(spell, 'B'))
  {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++)
    {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  }
  else if (spellLength == 3 &&
           StrContains(spell, 'E') &&
           StrContains(spell, 'S') &&
           StrContains(spell, 'P'))
  {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++)
    {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  }
  else if (spellLength == 3 &&
           StrContains(spell, 'E') &&
           StrContains(spell, 'P') &&
           StrContains(spell, 'B'))
  {
    printf("A colorful spray of elemental energies bursts forth from your "
           "outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    for (i = 0; i < 2; i++)
    {
      backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
    }
  }
  else if (strcmp(spell, "BS") == 0 || strcmp(spell, "SB") == 0)
  {
    printf("A blast of boiling water sprays forth from your outstretched "
           "hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "ES") == 0 || strcmp(spell, "SE") == 0)
  {
    printf("Shards of ice burst forth from your outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "BE") == 0 || strcmp(spell, "EB") == 0)
  {
    printf("A bolt of lightning shoots forth from your outstretched hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "BP") == 0 || strcmp(spell, "PB") == 0)
  {
    printf("A stream of lava sprays forth from your outstretched hand!\n");
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    fireValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "SP") == 0 || strcmp(spell, "PS") == 0)
  {
    printf("A stream of acid sprays forth from your outstretched hand!\n");
    waterValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else if (strcmp(spell, "EP") == 0 || strcmp(spell, "PE") == 0)
  {
    printf("A debris-filled whirlwind bursts forth from your outstretched "
           "hand!\n");
    airValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    earthValue = RandomInt(1, spellcaster->mentalPower * 0.25);
    backlashValue += RandomInt(0, spellcaster->mentalPower * 0.1);
  }
  else
  {
    printf("Nothing happens.\n");
    FlushInput();
    return SUCCESS;
  }
  for (i = 0; i < numTargets && gcTargets[i] != NULL; i++)
  {
    damage = fireValue + waterValue + earthValue + airValue;
    damage -= RandomInt(0, gcTargets[i]->physicalDefense / 10);
    if (damage <= 0)
    {
      printf("%s resists all damage.\n", gcTargets[i]->name);
    }
    else
    {
      printf("%s takes %d points of damage.\n", gcTargets[i]->name, damage);
      gcTargets[i]->currentHP -= damage;
      if (spellcaster == &player && player.status[IN_COMBAT] == FALSE)
      {
        if (gcTargets[i]->currentHP > 0)
        {
          gcTargets[i]->relationship = HOSTILE_ENEMY;
          AddEnemy(gcTargets[i]);
        }
        else
        {
          PrintNameDefinite(gcTargets[i], TRUE);
          printf(" is dead.\n");
          FlushInput();
        }
        for (pGC = world[player.locationID]->inhabitants;
             pGC != NULL;
             pGC = pGC->next)
        {
          if (WillingToFight(pGC) && pGC->status[IN_COMBAT] == FALSE)
          {
            pGC->relationship = HOSTILE_ENEMY;
            AddEnemy(pGC);
          }
        }
      }
    }
  }
  backlashValue -= RandomInt(0, spellcaster->mentalDefense / 4);
  if (backlashValue > 0)
  {
    spellcaster->currentHP -= backlashValue;
    printf("%s takes %d points of backlash damage.\n", spellcaster->name,
           fireValue);
  }
  FlushInput();
  /*if (spellcaster == &player && spellLength == MAX_SPELL_LEN)
  {
    FlushInput(); /* Necessary for effective pausing in this special case.
  }*/

  if (player.status[IN_COMBAT] == FALSE && NumberOfEnemies() > 0)
  {
    printf("Prepare for battle!\n");
    FlushInput();
    Combat();
  }

  return SUCCESS;
}

/******************************************************************************
   Function: CanCastBeneficialSpells

Description: Determines whether a given game character is capable of casting
             beneficial spells (i.e., spells that might reasonably target
             oneself).

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: TRUE if "pGC" is being targeted, otherwise FALSE.
******************************************************************************/
BOOL CanCastBeneficialSpells(GameCharacter *pGC)
{
  if (pGC->words[WORD_OF_BODY] == KNOWN ||
      pGC->words[WORD_OF_MIND] == KNOWN ||
      pGC->words[WORD_OF_FLORA] == KNOWN ||
      pGC->words[WORD_OF_FAUNA] == KNOWN ||
      pGC->words[WORD_OF_LIGHT] == KNOWN ||
      pGC->words[WORD_OF_DARKNESS] == KNOWN ||
      pGC->words[WORD_OF_HEALTH] == KNOWN ||
      pGC->words[WORD_OF_LIFE] == KNOWN ||
      pGC->words[WORD_OF_HOLINESS] == KNOWN ||
      pGC->words[WORD_OF_EVIL] == KNOWN ||
      pGC->words[WORD_OF_INCREASE] == KNOWN ||
      pGC->words[WORD_OF_DECREASE] == KNOWN ||
      pGC->words[WORD_OF_SHIELDING] == KNOWN ||
      pGC->words[WORD_OF_TIME] == KNOWN ||
      pGC->words[WORD_OF_VOID] == KNOWN)
  {
    return TRUE;
  }

  return FALSE;
}

/******************************************************************************
   Function: PrintKnownWords

Description: Displays each Word of Power the player knows in the following
             format: "[W]ord (Translation)".

     Inputs: None.

    Outputs: Returns the number of Words displayed.
******************************************************************************/
int PrintKnownWords(void)
{
  int i, j;               /* for loop variables                              */
  int wordsDisplayed = 0; /* Number of Words displayed.                      */
  int wordLength;         /* To store the length of each unformatted Word.   */
  char word[STR_LEN + 1]; /* To store, format, and print each Word.          */

  for (i = 0; i < TOTAL_WORD_IDS; i++)
  {
    if (player.words[i] != UNKNOWN)
    {
      strcpy(word, Word(i));
      wordLength = strlen(word);

        /* The word must have room for 2 more characters: '(' and ')'.       */
      if (wordLength >= (STR_LEN - 2))
      {
        #ifdef DEBUG
        ERROR_MESSAGE
        #endif
        return wordsDisplayed;
      }
        /* Format the string, beginning at its end and working backwards.    */
      for (j = wordLength; j >= 0; j--)
      {
        switch (j)
        {
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
      if (player.words[i] == KNOWN)
      {
        printf("%s (%s)\n", word, WordName(i));
      }
      else /* player.words[i] == PARTIALLY_KNOWN */
      {
        printf("%s (\?\?\?)\n", word);
      }
      wordsDisplayed++;
    }
  }

  return SUCCESS;
}

/******************************************************************************
   Function: Word

Description: Given the ID number of a Word of Power, returns that Word as a
             string.

     Inputs: idNum - ID of the desired Word.

    Outputs: Pointer to the desired string.
******************************************************************************/
char *Word(int idNum)
{
  switch (idNum)
  {
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

  #ifdef DEBUG
  ERROR_MESSAGE
  #endif
  return NULL;
}

/******************************************************************************
   Function: WordStartingWith

Description: Given the first letter of a Word of Power, returns the entire Word
             as a string.

     Inputs: firstLetter - First letter of the desired Word.

    Outputs: Pointer to the desired string.
******************************************************************************/
char *WordStartingWith(char firstLetter)
{
  return Word(WordID(firstLetter));
}

/******************************************************************************
   Function: WordName

Description: Returns the English name of a given Word of Power as a string
             (such as "Fire", "Water", etc.).

     Inputs: idNum - ID of the desired Word.

    Outputs: Pointer to the desired string.
******************************************************************************/
char *WordName(int idNum)
{
  switch (idNum)
  {
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

  #ifdef DEBUG
  ERROR_MESSAGE
  #endif
  return NULL;
}

/******************************************************************************
   Function: WordID

Description: Given the first letter of a Word of Power, returns the ID number
             corresponding to that Word. (Requires that no two Words share the
             same first letter.)

     Inputs: firstLetter - First letter of a Word of Power.

    Outputs: ID number for the Word associated with the given letter (or -1 if
             a corresponding ID is not found).
******************************************************************************/
int WordID(char firstLetter)
{
  int i;      /* for loop variable                       */
  char *temp; /* To check the first letter of each Word. */

  firstLetter = toupper(firstLetter);
  for (i = 0; i < TOTAL_WORD_IDS; i++)
  {
    temp = Word(i);
    if (temp[0] == firstLetter)
    {
      return i;
    }
  }

  #ifdef DEBUG
  ERROR_MESSAGE
  #endif
  return -1;
}

/******************************************************************************
   Function: IsSpellcaster

Description: Determines whether a given game character can cast spells.

     Inputs: pGC - The game character of interest.

    Outputs: TRUE if the GC knows at least one Word, otherwise FALSE.
******************************************************************************/
BOOL IsSpellcaster(GameCharacter *pGC)
{
  int i;  /* for loop variable */

  for (i = 0; i < TOTAL_WORD_IDS; i++)
  {
    if (pGC->words[i] == KNOWN)
    {
      return TRUE;
    }
  }

  return FALSE;
}
