/******************************************************************************
   Filename: main.c

     Author: David C. Drake (http://davidcdrake.com)

Description: Main C file for "Words of Power": a text-based fantasy RPG
             emphasizing verbal spell-casting through the use of magic words.
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: main

Description: Main function for the "Words of Power" RPG.

     Inputs: None.

    Outputs: Number of errors encountered.
******************************************************************************/
int main(void) {
  srand((int) time(0));
  g_world_exists = false;
  g_player_has_quit = false;

  PrintString("\nWelcome to WORDS OF POWER: a text-based fantasy RPG!\n"
              "Designed and programmed by David C. Drake: "
              "http://davidcdrake.com\n\0");
  while (!g_player_has_quit) {
    if (!g_world_exists) {
      HandleMainMenuInput();
    } else {
      CheckStatus();
      DescribeSituation();
      HandleStandardOptionsInput();
    }
  }
  if (g_world_exists) {
    DestroyWorld();
  }
  printf("Farewell!\n");
#if DEBUG
  printf("End of main reached.\n");
#endif

  return 0;
}

/******************************************************************************
   Function: HandleMainMenuInput

Description: Displays main menu options and does some handling of input.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void HandleMainMenuInput(void) {
  char input;
  bool repeat_options;

  do {
    repeat_options = false;
    printf("Main Menu:\n"
           "[N]ew Game\n"
           "[L]oad Game\n"
           "[Q]uit\n");
    GetCharInput(&input);
    switch (input) {
      case 'N':  // New Game
        if (g_world_exists) {
          DestroyWorld();
        }
        CreateWorld();
        InitializeCharacter(&g_player, PLAYER, g_world[ILLARUM_SCHOOL]);
        break;
      case 'L':  // Load Game
        if (g_world_exists) {
          DestroyWorld();
        }
        //LoadGame();
        printf("Sorry, no save files found.\n\n");
        break;
      case 'Q':  // Quit
        if (g_world_exists) {
          DestroyWorld();
        }
        g_player_has_quit = true;
        break;
      default:
        printf("Invalid response.\n\n");
        repeat_options = true;
        break;
    }
  }while (repeat_options);
}

/******************************************************************************
   Function: HandleStandardOptionsInput

Description: Prints the standard (i.e., non-combat) player options and
             processes corresponding player input.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void HandleStandardOptionsInput(void) {
  char input;
  bool repeat_options;

  do {
    repeat_options = false;
    printf("What do you want to do?\n"
           "[T]alk\n"
           "[S]earch\n"
           "[U]se an Item\n"
           "[C]ast a Spell\n"
           "[A]ttack\n"
           "[V]iew Inventory and Status\n"
           "[M]ove to Another Location\n"
           "[Q]uit (Return to Main Menu)\n");
    GetCharInput(&input);
    switch (input) {
      case 'T':  // Talk
        if (HandleTalkMenuInput() == FAILURE) {
          repeat_options = true;
        }
        break;
      case 'S':  // Search
        if (SearchLocation(g_world[g_player.location]) == FAILURE) {
          repeat_options = true;
        }
        break;
      case 'U':  // Use an Item
        if (HandleItemMenuInput() == FAILURE) {
          repeat_options = true;
        }
        break;
      case 'C':  // Cast a Spell
        if (HandleSpellMenuInput() == FAILURE) {
          repeat_options = true;
        }
        break;
      case 'A':  // Attack
        if (HandleAttackMenuInput() == FAILURE) {
          repeat_options = true;
        }
        break;
      case 'M':  // Move to Another Location
        if (HandleMovementMenuInput() == FAILURE) {
          repeat_options = true;
        }
        break;
      case 'V':  // View Inventory and Status
        DisplayCharacterData(&g_player);
        repeat_options = true;
        break;
      case 'Q':  // Quit
        if (GetExitConfirmation() == false) {
          repeat_options = true;
        }
        break;
      default:
        printf("Invalid response.\n\n");
        repeat_options = true;
        break;
    }
  }while (repeat_options);
}

/******************************************************************************
   Function: CreateWorld

Description: Allocates memory for, and initializes, location structs for all
             game locations as well as game character structs for each
             location's default inhabitants. Also sets other global variables
             to their default starting values.

     Inputs: None.

    Outputs: The number of failed location initializations.
******************************************************************************/
int CreateWorld(void) {
  int i, errors = 0;

#if DEBUG
  printf("Creating world...\n\n");
#endif

  if (g_world_exists) {
    PRINT_ERROR_MESSAGE;
    errors++;
    DestroyWorld();
  }

  // Initialize each location (including its inhabitants):
  for (i = 0; i < NUM_LOCATION_IDS; i++) {
    g_world[i] = malloc(sizeof(location_t));
    if (g_world[i] != NULL) {
      errors += InitializeLocation(g_world[i], i);
    } else {
      PRINT_ERROR_MESSAGE;
      exit(1);
    }
  }

  // Set status of all missions to CLOSED:
  for (i = 0; i < NUM_MISSION_TYPES; i++) {
    g_missions[i] = CLOSED;
  }

  // Initialize player allegiances:
  for (i = 0; i < NUM_GROUP_TYPES; i++) {
    g_allegiances[i] = INDIFFERENT;
  }

  // Initialize player's "kill" history:
  for (i = 0; i < NUM_GC_TYPES; i++) {
    g_num_kills[i] = 0;
  }

  // Initialize remaining global variables:
  g_num_secrets_found = 0;
  g_world_exists = true;

  return errors;
}

/******************************************************************************
   Function: DestroyWorld

Description: Deallocates all memory set aside for location structs and their
             inhabitants.

     Inputs: None.

    Outputs: The number of errors detected.
******************************************************************************/
int DestroyWorld(void) {
  int i, errors = 0;

  if (g_world_exists == false) {
    PRINT_ERROR_MESSAGE;
    errors++;
  }

#if DEBUG
  printf("Destroying world...\n\n");
#endif

  for (i = 0; i < NUM_LOCATION_IDS; i++) {
    if (g_world[i] != NULL) {
      while (g_world[i]->inhabitants != NULL) {
        if (DeleteInhabitant(g_world[i], g_world[i]->inhabitants) == FAILURE) {
          errors++;
        }
      }
      free(g_world[i]);
    } else {
      errors++;
    }
  }
  for (i = 0; i < MAX_ENEMIES; i++) {
    g_enemies[i] = NULL;
  }
  while (g_player.next != NULL) {
    if (DeleteCompanion(g_player.next) == FAILURE) {
      errors++;
    }
  }
  if (g_player.summoned_creature != NULL) {
    if (DeleteCreatureSummonedBy(&g_player) == FAILURE) {
      errors++;
    }
  }
  g_world_exists = false;

  return errors;
}

/******************************************************************************
   Function: GetExitConfirmation

Description: Asks for confirmation of intent to exit to the main menu. If
             confirmed, memory is freed via DestroyWorld.

     Inputs: None.

    Outputs: true if the player confirms they want to exit to the main menu.
******************************************************************************/
bool GetExitConfirmation(void) {
  char input;

  do {
    printf("Are you sure you want to exit to the main menu (and lose unsaved "
           "data)? (Y/N) ");
    GetCharInput(&input);
    if (input == 'Y') {
      DestroyWorld();
      return true;
    } else if (input != 'N') {
      printf("Invalid response.\n\n");
    }
  }while (input != 'N');

  return false;
}

/******************************************************************************
   Function: RandomInt

Description: Returns a random integer between specified values (inclusive).

     Inputs: low  - Lowest possible return value.
             high - Highest possible return value.

    Outputs: A randomly generated integer between "low" and "high" (inclusive).
******************************************************************************/
int RandomInt(int low, int high) {
  int temp;

  if (low > high) {
    temp = low;
    low = high;
    high = temp;
    PRINT_ERROR_MESSAGE;
  }

  return rand() % (high - low + 1) + low;
}

/******************************************************************************
   Function: RandomBool

Description: Returns a random boolean value.

     Inputs: None.

    Outputs: true or false.
******************************************************************************/
int RandomBool(void) {
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
char GetCharInput(char *c) {
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
int GetIntInput(int *i, int low, int high) {
  int temp;
  bool repeat;

  if (low > high) {
    temp = low;
    low = high;
    high = temp;
    PRINT_ERROR_MESSAGE;
  }

  do {
    repeat = false;
    scanf("%d", i);
    FlushInput();
    if (*i < low || *i > high) {
      printf("Invalid response. Enter a number between %d and %d: ", low,
             high);
      repeat = true;
    }
  }while (repeat);
  printf("\n");

  return *i;
}

/******************************************************************************
   Function: GetStrInput

Description: Takes in a string of one or more characters entered by the user.

     Inputs: str - Pointer to the string that will store input.
             n   - Maximum number of characters to read in (if greater than
                   SHORT_STR_LEN or negative, it will be set to SHORT_STR_LEN).

    Outputs: Returns a pointer to the string where the input is stored.
******************************************************************************/
char *GetStrInput(char *str, int n)
{
  int length;

  if (n < 0 || n > (SHORT_STR_LEN + 1)) {
    PRINT_ERROR_MESSAGE;
    if (n > SHORT_STR_LEN) {
      n = SHORT_STR_LEN;
    }
  }
  fgets(str, n, stdin);
  length = strlen(str);
  if (length > 0 && str[length - 1] == '\n') {
    str[length - 1] = '\0';
  }
  printf("\n");

  return str;
}

/******************************************************************************
   Function: PrintString

Description: Prints a given string according to the maximum characters per
             line, followed by a new line character. (Assumes the string is
             NULL-terminated and contains no tabs. If no NULL-terminator is
             encountered, assumes the size of the string is equal to
             LONG_STR_LEN.)

     Inputs: str - The string to be printed, which must be NULL-terminated.

    Outputs: None.
******************************************************************************/
void PrintString(char *str) {
  int i, last_blank_space_index = 0, current_line_length = 0;
  static char output[LONG_STR_LEN + 1];

  strcpy(output, str);
  for (i = 0; i < LONG_STR_LEN && output[i] != '\0'; i++) {
    current_line_length++;
    if (output[i] == ' ') {
      last_blank_space_index = i;
    }
    if (output[i] == '\n') {
      last_blank_space_index = 0;
      current_line_length    = 0;
    } else if (current_line_length == MAX_LINE_LENGTH) {
      if (last_blank_space_index == 0) {
        output[i]           = '\n';
        current_line_length = 0;
      } else {
        i = last_blank_space_index;
        output[i] = '\n';
        last_blank_space_index = 0;
        current_line_length = 0;
      }
    }
  }
  if (i == LONG_STR_LEN) {
    output[i] = '\0';
  }
  printf("%s\n", output);
}

/******************************************************************************
   Function: Capitalize

Description: Capitalizes the first character of a given string.

     Inputs: str - The string to be capitalized.

    Outputs: Pointer to the capitalized string.
******************************************************************************/
char *Capitalize(char *str) {
  toupper(str[0]);

  return str;
}

/******************************************************************************
   Function: AllCaps

Description: Capitalizes every character in a given string (which is assumed to
             be NULL-terminated).

     Inputs: str - The string to be modified.

    Outputs: Pointer to the modified string.
******************************************************************************/
char *AllCaps(char *str) {
  int i;

  for (i = 0; str[i] != '\0'; i++) {
    toupper(str[i]);
  }

  return str;
}

/******************************************************************************
   Function: StrContains

Description: Determines whether a given string contains a given character.

     Inputs: str - Pointer to the string of interest.
             c   - Character to search for in the string.

    Outputs: true if the string contains "c", otherwise false.
******************************************************************************/
bool StrContains(char *str, char c) {
  int i;

  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      return true;
    }
  }

  return false;
}

/******************************************************************************
   Function: FlushInput

Description: Removes remaining input up to and including an end of line or end
             of file character. (Also generally an effective way of pausing the
             game until the player hits the Enter key.)

     Inputs: None.

    Outputs: None.
******************************************************************************/
void FlushInput(void) {
  int c;

  while((c = getchar()) != '\n' && c != EOF) {
    /* discard */ ;
  }
}
