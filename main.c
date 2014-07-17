/******************************************************************************
   Filename: main.c

     Author: David C. Drake (www.davidcdrake.com)

Description: Main C file for "Words of Power": a text-based fantasy RPG
             emphasizing verbal spell-casting through the use of magic words.

  Functions: main, Print, MainMenu, PrintStandardOptions, CreateWorld,
             DestroyWorld, QuitMenu, HelpMenu, RandomInt, RandomBool,
             GetCharInput, GetIntInput, GetStrInput, StrContains, FlushInput
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: main

Description: Main function for the "Words of Power" RPG.

     Inputs: None.

    Outputs: Number of errors encountered.
******************************************************************************/
int main(void)
{
  srand(time(0));
  worldExists = FALSE;

  printf(
"\nWelcome to \"Words of Power\": a fantasy RPG developed by David C. Drake "
"(www.davidcdrake.com)\n"
        );
  FlushInput();

  MainMenu();
  while (worldExists && !quit)
  {
    StatusCheck();
    DescribeSituation();
    PrintStandardOptions();
  }

#ifdef DEBUG
  printf("End of main reached.\n\n");
#endif
  if (worldExists)
  {
    DestroyWorld();
  }
  printf("Farewell!\n");

  return 0;
}

/******************************************************************************
   Function: PrintParagraph

Description: Prints a given string according to the maximum characters per
             line, then prints two new line characters to provide spacing.

     Inputs: paragraph - The string to be printed.

    Outputs: None.
******************************************************************************/
void PrintParagraph(char *paragraph)
{

}

/******************************************************************************
   Function: MainMenu

Description: Displays main menu options and does some handling of input.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void MainMenu(void)
{
  char cInput;
  BOOL repeatOptions;

  do
  {
    repeatOptions = FALSE;
    printf("Main Menu:\n"
           "[N]ew Game\n"
           "[A]bout Words of Power...\n"
           "[Q]uit\n");
    GetCharInput(&cInput);
    switch (cInput)
    {
      case 'N': /* New Game */
        if (worldExists)
        {
          DestroyWorld();
        }
        CreateWorld();
        InitializeCharacter(&player, PLAYER, world[ILLARUM_SCHOOL]);
        break;
      case 'A':
        /*AboutWordsOfPower();*/
        repeatOptions = TRUE;
        break;
      case 'Q': /* Quit */
        if (worldExists)
        {
          DestroyWorld();
        }
        printf("Farewell!\n");
        exit(0);
        break;
      default:
        printf("Invalid response.\n\n");
        repeatOptions = TRUE;
        break;
    }
  }while(repeatOptions);
}

/******************************************************************************
   Function: PrintStandardOptions

Description: Prints the standard (i.e., non-combat) player options and
             processes corresponding player input.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void PrintStandardOptions(void)
{
  int i;              /* for loop variable                        */
  int iInput;
  char cInput;
  int temp;
  BOOL repeatOptions;
  GameCharacter *pGC; /* To scan linked lists of game characters. */

  do
  {
    repeatOptions = FALSE;
    printf("What do you want to do?\n"
           "[T]alk\n"
           "[S]earch\n"
           "[C]ast a Spell\n"
           "[U]se an Item\n"
           "[A]ttack\n"
           "[V]iew My Status\n"
           "[M]ove to Another Location\n"
           "[Q]uit\n");
    GetCharInput(&cInput);
    switch (cInput)
    {
      case 'T': /* Talk */
        if (TalkMenu() == FAILURE)
        {
          repeatOptions = TRUE;
        }
        break;
      case 'S': /* Search */
        if (SearchLocation(world[player.locationID]) == FAILURE)
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
      case 'A': /* Attack */
        if (AttackMenu() == FAILURE)
        {
          repeatOptions = TRUE;
        }
        break;
      case 'M': /* Move to Another Location */
        if (MovementMenu() == FAILURE)
        {
          repeatOptions = TRUE;
        }
        break;
      case 'V': /* View Character Data */
        DisplayCharacterData(&player);
        repeatOptions = TRUE;
        break;
      /*case 'H': /* Help *//*
        HelpMenu();
        repeatOptions = TRUE;
        break;*/
      case 'Q': /* Quit */
        QuitMenu();
        repeatOptions = TRUE;
        break;
      default:
        printf("Invalid response.\n\n");
        repeatOptions = TRUE;
        break;
    }
  }while (repeatOptions);
}

/******************************************************************************
   Function: CreateWorld

Description: Allocates memory for, and initializes, Location structs for all
             game locations as well as GameCharacter structs for each
             location's default inhabitants. Also sets other global variables
             to their default starting values.

     Inputs: None.

    Outputs: The number of failed location initializations.
******************************************************************************/
int CreateWorld(void)
{
  int i;          /* for loop variable                                       */
  int errors = 0; /* The number of failed location initializations.          */

#ifdef DEBUG
  printf("Creating world...\n\n");
#endif

    /* If a game world already exists in memory, destroy it.                 */
  if (worldExists)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    errors++;
    DestroyWorld();
  }

    /* Initialize each location (including its inhabitants).                 */
  for (i = 0; i < TOTAL_LOCATION_IDS; i++)
  {
    world[i] = malloc(sizeof(Location));
    if (world[i] != NULL)
    {
      errors += InitializeLocation(world[i], i);
    }
    else
    {
#ifdef DEBUG
      ERROR_MESSAGE
#endif
      exit(1);
    }
  }

    /* Set the status of all missions to CLOSED.                             */
  for (i = 0; i < TOTAL_MISSION_IDS; i++)
  {
    missions[i] = CLOSED;
  }

    /* Initialize the player's allegiances.                                  */
  for (i = 0; i < TOTAL_GROUP_IDS; i++)
  {
    allegiances[i] = INDIFFERENT;
  }

    /* Initialize the player's "kill" history.                               */
  for (i = 0; i < TOTAL_GC_IDS; i++)
  {
    kills[i] = 0;
  }

    /* Initialize remaining global variables.                                */
  secretsFound = 0;
  quit = FALSE;
  worldExists = TRUE;

  return errors;
}

/******************************************************************************
   Function: DestroyWorld

Description: Deallocates all memory set aside for Location structs and their
             inhabitants.

     Inputs: None.

    Outputs: The number of errors detected.
******************************************************************************/
int DestroyWorld(void)
{
  int i;               /* for loop variable                                  */
  int errors = 0;      /* The number of errors detected.                     */
  GameCharacter *temp; /* To search for and deallocate game characters.      */

  if (worldExists == FALSE)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    errors++;
  }

#ifdef DEBUG
  printf("Destroying world...\n\n");
#endif

  for (i = 0; i < TOTAL_LOCATION_IDS; i++)
  {
    if (world[i] != NULL)
    {
      while (world[i]->inhabitants != NULL)
      {
        if (DeleteInhabitant(world[i], world[i]->inhabitants) == FAILURE)
        {
          errors++;
        }
      }
      free(world[i]);
    }
    else
    {
      errors++;
    }
  }
  for (i = 0; i < MAX_ENEMIES; i++)
  {
    enemyNPCs[i] = NULL;
  }
  while (player.next != NULL)
  {
    if (DeleteCompanion(player.next) == FAILURE)
    {
      errors++;
    }
  }
  if (player.summonedCreature != NULL)
  {
    if (DeleteCreatureSummonedBy(&player) == FAILURE)
    {
      errors++;
    }
  }
  worldExists = FALSE;

  return errors;
}

/******************************************************************************
   Function: QuitMenu

Description: Asks for confirmation of intent to quit. If confirmed, memory is
             deallocated as needed via "DestroyWorld()", then the program is
             terminated.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void QuitMenu(void)
{
  char cInput;

  do
  {
    printf("Are you sure you want to quit? (Y/N) ");
    GetCharInput(&cInput);
    if (cInput == 'Y')
    {
      DestroyWorld();
      printf("\nThanks for playing!\n");
      exit(0);
    }
    else if (cInput != 'N')
    {
      printf("Invalid response.\n\n");
    }
  }while (cInput != 'N');
}

/******************************************************************************
   Function: HelpMenu

Description: Provides information about how to play the game.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void HelpMenu(void)
{
  printf("Sorry, I can't help you right now! :)\n");
  FlushInput();
}

/******************************************************************************
   Function: RandomInt

Description: Returns a pseudo-random integer between specified values
             (inclusive).

     Inputs: low  – Lowest possible return value.
             high - Highest possible return value.

    Outputs: A randomly generated integer between "low" and "high" (inclusive).
******************************************************************************/
int RandomInt(int low, int high)
{
  int temp;

    /* If the arguments were passed in the wrong order, switch them.         */
  if (low > high)
  {
    temp = low;
    low = high;
    high = temp;
#ifdef DEBUG
    ERROR_MESSAGE
#endif
  }

  return rand() % (high - low + 1) + low;
}

/******************************************************************************
   Function: RandomBool

Description: Randomly returns a boolean value.

     Inputs: None.

    Outputs: TRUE or FALSE.
******************************************************************************/
int RandomBool(void)
{
  return rand() % 2;
}

/******************************************************************************
   Function: GetCharInput

Description: Takes in one character entered by the user, converts it to
             uppercase, and flushes the input stream.

     Inputs: c - Pointer to the variable that will store the input.

    Outputs: Returns the character read in from the user, converted to
             uppercase.
******************************************************************************/
char GetCharInput(char *c)
{
  scanf(" %c", c);
  FlushInput();
  printf("\n");
  *c = toupper(*c);

  return *c;
}

/******************************************************************************
   Function: GetIntInput

Description: Reads in one integer, then repeats until an integer within given
             parameters is read.

     Inputs: i    - Pointer to the variable that will store the input.
             low  - Lowest acceptable value.
             high - Highest acceptable value.


    Outputs: Returns the input value stored in "*i".
******************************************************************************/
int GetIntInput(int *i, int low, int high)
{
  int temp;
  BOOL repeat;

    /* If "low" and "high" were passed in the wrong order, switch them.      */
  if (low > high)
  {
    temp = low;
    low = high;
    high = temp;
#ifdef DEBUG
    ERROR_MESSAGE
#endif
  }

  do
  {
    repeat = FALSE;
    scanf("%d", i);
    FlushInput();
    if (*i < low || *i > high)
    {
      printf("Invalid response. Enter a number between %d and %d: ",
             low,
             high);
      repeat = TRUE;
    }
  }while (repeat);
  printf("\n");

  return *i;
}

/******************************************************************************
   Function: GetStrInput

Description: Takes in a string of one or more characters entered by the user.

     Inputs: string - Pointer to the array of characters that will store input.
             n      - Maximum number of characters to read in (if greater than
                      STR_LEN or negative, it will be set to STR_LEN).

    Outputs: Returns a pointer to string where the input is stored.
******************************************************************************/
char *GetStrInput(char *string, int n)
{
  int length;  /* To store the input string's length.                        */

  if (n < 0 || n > (STR_LEN + 1))
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    if (n > STR_LEN)
    {
      n = STR_LEN;
    }
  }
  fgets(string, n, stdin);
  length = strlen(string);
  if (length > 0 && string[length - 1] == '\n')
  {
    string[length - 1] = '\0';
  }
  printf("\n");

  return string;
}

/******************************************************************************
   Function: StrContains

Description: Determines whether a given string contains a given character.

     Inputs: string - Pointer to the string of interest.
             c      - Character to search for in the string.

    Outputs: TRUE if the string contains "c", otherwise FALSE.
******************************************************************************/
BOOL StrContains(char string[], char c)
{
  int i;  /* for loop variable */
  int stringLength = strlen(string);

  for (i = 0; i < stringLength; i++)
  {
    if (string[i] == c)
    {
      return TRUE;
    }
  }

  return FALSE;
}

/******************************************************************************
   Function: FlushInput

Description: Removes remaining input up to and including an end of line or end
             of file character. (Also generally an effective way of pausing the
             game until the player hits the Enter key.)

     Inputs: None.

    Outputs: None.
******************************************************************************/
void FlushInput(void)
{
  int c;

  while((c = getchar()) != '\n' && c != EOF)
  {
    /* discard */ ;
  }
}
