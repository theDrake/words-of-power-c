/*******************************************************************************
   Filename: items.c

     Author: David C. Drake (https://davidcdrake.com)

Description: Functions governing items for the text-based RPG "Words of Power."
*******************************************************************************/

#include "wop.h"

/*******************************************************************************
   Function: HandleItemMenuInput

Description: Displays the player's inventory and prompts the player to choose
             which item to use.

     Inputs: None.

    Outputs: SUCCESS if an item is used, FAILURE otherwise.
*******************************************************************************/
int HandleItemMenuInput(void) {
  int i, input, temp = 0;

  for (i = 0; i < NUM_ITEM_TYPES; i++) {
    if (g_player.inventory[i] > 0) {
      temp++;
      printf("[%d] %s (%d)\n", temp, GetItemName(i), g_player.inventory[i]);
    }
  }
  if (temp == 0) {
    printf("You have no items.\n");
    FlushInput();
    return FAILURE;
  } else {
    temp++;
    printf("[%d] Cancel (return to previous menu)\n", temp);
    GetIntInput(&input, 1, temp);
    temp = 0;
    for (i = 0; i < NUM_ITEM_TYPES; i++) {
      if (g_player.inventory[i] > 0) {
        temp++;
        if (temp == input) {
          UseItem(&g_player, i);
          return SUCCESS;
        }
      }
    }
  }

  return FAILURE;  // No item was used: player changed their mind.
}

/*******************************************************************************
   Function: UseItem

Description: Handles the use of an item by a given character (player or NPC).

     Inputs: p_gc - Pointer to the user of the item.
             item - Integer representing the type of item to be used.

    Outputs: SUCCESS or FAILURE.
*******************************************************************************/
int UseItem(game_character_t *p_gc, int item) {
  if (p_gc->inventory[item] < 1) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  switch(item) {
    case HEALING_POTION:
      printf("%s drinks a healing potion and regains %d hit points.\n",
             Capitalize(GetNameDefinite(p_gc)),
             HealGameCharacter(p_gc, RandomInt(DEFAULT_HP / 2, DEFAULT_HP)));
      break;
    case FOOD:
      printf("%s eats food and regains %d hit points.\n",
             Capitalize(GetNameDefinite(p_gc)),
             HealGameCharacter(p_gc,
                               RandomInt(DEFAULT_HP / 4, DEFAULT_HP / 2)));
      break;
    default:
      PRINT_ERROR_MESSAGE;
      return FAILURE;
  }
  p_gc->inventory[item]--;
  FlushInput();

  return SUCCESS;
}

/*******************************************************************************
   Function: PrintInventory

Description: Prints the name and quantity of each item owned by a given game
             character. Indicates which, if any, are equipped.

     Inputs: p_gc - Pointer to the game character of interest.

    Outputs: Number of item types described (or -1 if an error is encountered).
*******************************************************************************/
int PrintInventory(game_character_t *p_gc) {
  int i, num_item_types_described = 0;

  if (p_gc == NULL) {
    PRINT_ERROR_MESSAGE;
    return -1;
  }

  printf("Inventory: ");
  for (i = 0; i < NUM_ITEM_TYPES; i++) {
    if (p_gc->inventory[i] > 0) {
      if (num_item_types_described > 0) {
        printf(", ");
        if (num_item_types_described % 3 == 0) {
          printf("\n\t");
        }
      }
      if (p_gc->inventory[i] == 1) {
        printf("%s", GetItemName(i));
      } else {
        printf("%d %s", p_gc->inventory[i], GetItemNamePlural(i));
      }
      if (p_gc->equipped_items[i] > 0) {
        if (p_gc->inventory[i] == 1) {
          printf("(equipped)");
        } else {
          printf("(%d equipped)", p_gc->equipped_items[i]);
        }
      }
      num_item_types_described++;
    }
  }
  printf(".\n");

  return num_item_types_described;
}

/*******************************************************************************
   Function: GetItemName

Description: Given an item type, returns the name of that item.

     Inputs: item - Integer representing the item of interest.

    Outputs: The item's name as a pointer to an array of characters.
*******************************************************************************/
char *GetItemName(int item) {
  static char itemName[SHORT_STR_LEN + 1];

  switch (item) {
    case FOOD:
      strcpy(itemName, "Food");
      break;
    case HEALING_POTION:
      strcpy(itemName, "Healing Potion");
      break;
    case GLOWING_MUSHROOM:
      strcpy(itemName, "Glowing Mushroom");
      break;
    default:
      PRINT_ERROR_MESSAGE;
      strcpy(itemName, "???");
  }

  return itemName;
}

/*******************************************************************************
   Function: GetItemNamePlural

Description: Given an item type, returns the plural name of that item.

     Inputs: item - Integer representing the item of interest.

    Outputs: The item's plural name as a pointer to an array of characters.
*******************************************************************************/
char *GetItemNamePlural(int item) {
  static char itemName[SHORT_STR_LEN + 1];

  strcpy(itemName, GetItemName(item));
  if (item != FOOD) {
    strcat(itemName, "s");
  }

  return itemName;
}

/*******************************************************************************
   Function: GiveGold

Description: Transfers gold from one game character to another.

     Inputs: giver    - Pointer to the GC giving gold.
             receiver - Pointer to the GC receiving gold.
             amount   - Amount of gold to be transferred.

    Outputs: SUCCESS or FAILURE.
*******************************************************************************/
int GiveGold(game_character_t *giver, game_character_t *receiver, int amount) {
  if (giver == NULL || receiver == NULL || giver->gold < amount) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  giver->gold -= amount;
  receiver->gold += amount;
  printf("%s gives %d gold to %s.\n", giver->name, amount, receiver->name);
  FlushInput();

  return SUCCESS;
}

/*******************************************************************************
   Function: AddItem

Description: Adds a given item to a given game character's inventory.

     Inputs: receiver - Pointer to the GC receiving the item.
             item     - Integer representing the type of item to be added.

    Outputs: SUCCESS or FAILURE.
*******************************************************************************/
int AddItem(game_character_t *receiver, int item) {
  if (receiver == NULL) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  receiver->inventory[item]++;
  if (receiver->type == PLAYER) {
    printf("You discover: %s\n", GetItemName(item));
  }

  return SUCCESS;
}

/*******************************************************************************
   Function: GiveItem

Description: Transfers an item from one game character to another.

     Inputs: giver    - Pointer to the GC giving the item.
             receiver - Pointer to the GC receiving the item.
             item     - Integer representing the type of item to be given.

    Outputs: SUCCESS or FAILURE.
*******************************************************************************/
int GiveItem(game_character_t *giver, game_character_t *receiver, int item) {
  if (giver == NULL || receiver == NULL || giver->inventory[item] <= 0) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  giver->inventory[item]--;
  if (giver->equipped_items[item] > giver->inventory[item]) {
    giver->equipped_items[item]--;
  }
  receiver->inventory[item]++;
  printf("%s gives %s to %s\n",
         giver->name,
         GetItemName(item),
         receiver->name);
  FlushInput();

  return SUCCESS;
}

/*******************************************************************************
   Function: GiveItems

Description: Transfers a specified amount of a given item from one game
             character to another.

     Inputs: giver    - Pointer to the GC giving the item.
             receiver - Pointer to the GC receiving the item.
             item     - Integer representing the type of item to be given.
             amount   - Quantity of the item to be transferred.

    Outputs: SUCCESS or FAILURE.
*******************************************************************************/
int GiveItems(game_character_t *giver, game_character_t *receiver, int item,
              int amount) {
  if (giver == NULL || receiver == NULL || giver->inventory[item] < amount) {
    PRINT_ERROR_MESSAGE;
    return FAILURE;
  }

  giver->inventory[item] -= amount;
  if (giver->equipped_items[item] > giver->inventory[item]) {
    giver->equipped_items[item] = giver->inventory[item];
  }
  receiver->inventory[item] += amount;
  printf("%s gives %d %s to %s.\n", giver->name, amount,
         GetItemNamePlural(item), receiver->name);
  FlushInput();

  return SUCCESS;
}

/*******************************************************************************
   Function: GetItemValue

Description: Returns the standard market value of a given item.

     Inputs: item - Integer representing the item of interest.

    Outputs: The standard market value of the item of interest (or -1 if an
             error is encountered).
*******************************************************************************/
int GetItemValue(int item) {
  switch (item) {
    case FOOD:
      return 1;
    case HEALING_POTION:
      return 15;
    case GLOWING_MUSHROOM:
      return 20;
    default:
      PRINT_ERROR_MESSAGE;
      break;
  }

  return -1;
}
