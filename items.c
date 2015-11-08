/******************************************************************************
   Filename: items.c

     Author: David C. Drake (www.davidcdrake.com)

Description: Functions governing items for the text-based fantasy RPG "Words of
             Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: ItemMenu

Description: Displays the player's inventory and prompts the player to choose
             which item to use.

     Inputs: None.

    Outputs: SUCCESS if an item is used, FAILURE otherwise.
******************************************************************************/
int ItemMenu(void) {
  int i, iInput, temp = 0;

  for (i = 0; i < TOTAL_ITEM_IDS; i++) {
    if (player.inventory[i] > 0) {
      temp++;
      printf("[%d] %s (%d)\n", temp, GetItemName(i), player.inventory[i]);
    }
  }
  if (temp == 0) {
    printf("You have no items.\n");
    FlushInput();
    return FAILURE;
  } else {
    temp++;
    printf("[%d] Cancel (return to previous menu)\n", temp);
    GetIntInput(&iInput, 1, temp);
    temp = 0;
    for (i = 0; i < TOTAL_ITEM_IDS; i++) {
      if (player.inventory[i] > 0) {
        temp++;
        if (temp == iInput) {
          UseItem(&player, i);
          return SUCCESS;
        }
      }
    }
  }

  return FAILURE;  /* No item was used: the player changed his/her mind. */
}

/******************************************************************************
   Function: UseItem

Description: Executes the use of an item by a given game character (the player
             or an NPC).

     Inputs: pGC   - Pointer to the user of the item.
             idNum - ID number of the item to be used.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int UseItem(GameCharacter *pGC, int idNum) {
  if (pGC->inventory[idNum] < 1) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  switch(idNum) {
    case HEALING_POTION:
      printf("%s drinks a healing potion and regains %d hit points.\n",
             Capitalize(GetNameDefinite(pGC)),
             HealGameCharacter(pGC, RandomInt(DEFAULT_HP / 2, DEFAULT_HP)));
      break;
    case FOOD:
      printf("%s eats food and regains %d hit points.\n",
             Capitalize(GetNameDefinite(pGC)),
             HealGameCharacter(pGC,
                               RandomInt(DEFAULT_HP / 4, DEFAULT_HP / 2)));
      break;
    default:
#if DEBUG
      ERROR_MESSAGE
#endif
      return FAILURE;
  }
  pGC->inventory[idNum]--;
  FlushInput();

  return SUCCESS;
}

/******************************************************************************
   Function: PrintInventory

Description: Prints the name and quantity of each item owned by a given game
             character. Indicates which, if any, are equipped.

     Inputs: pGC - Pointer to the game character of interest.

    Outputs: Number of item types described (or -1 if an error is encountered).
******************************************************************************/
int PrintInventory(GameCharacter *pGC) {
  int i, itemTypesDescribed = 0;

  if (pGC == NULL) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return -1;
  }

  printf("Inventory: ");
  for (i = 0; i < TOTAL_ITEM_IDS; i++) {
    if (pGC->inventory[i] > 0) {
      if (itemTypesDescribed > 0) {
        printf(", ");
        if (itemTypesDescribed % 3 == 0) {
          printf("\n\t");
        }
      }
      if (pGC->inventory[i] == 1) {
        printf("%s", GetItemName(i));
      } else {
        printf("%d %s", pGC->inventory[i], GetItemNamePlural(i));
      }
      if (pGC->equippedItems[i] > 0) {
        if (pGC->inventory[i] == 1) {
          printf("(equipped)");
        } else {
          printf("(%d equipped)", pGC->equippedItems[i]);
        }
      }
      itemTypesDescribed++;
    }
  }
  printf(".\n");

  return itemTypesDescribed;
}

/******************************************************************************
   Function: GetItemName

Description: Given an item ID, returns the name of that item.

     Inputs: idNum - ID number of the item of interest.

    Outputs: The item's name as a pointer to an array of characters.
******************************************************************************/
char *GetItemName(int idNum) {
  static char itemName[SHORT_STR_LEN + 1];

  switch (idNum) {
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
#if DEBUG
      ERROR_MESSAGE
#endif
      strcpy(itemName, "???");
  }

  return itemName;
}

/******************************************************************************
   Function: GetItemNamePlural

Description: Given an item ID, returns the plural name of that item.

     Inputs: idNum - ID number of the item of interest.

    Outputs: The item's plural name as a pointer to an array of characters.
******************************************************************************/
char *GetItemNamePlural(int idNum) {
  static char itemName[SHORT_STR_LEN + 1];

  strcpy(itemName, GetItemName(idNum));
  if (idNum != FOOD) {
    strcat(itemName, "s");
  }

  return itemName;
}

/******************************************************************************
   Function: GiveGold

Description: Transfers gold from one game character to another.

     Inputs: giver    - Pointer to the GC giving gold.
             receiver - Pointer to the GC receiving gold.
             amount   - Amount of gold to be transferred.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int GiveGold(GameCharacter *giver, GameCharacter *receiver, int amount) {
  if (giver == NULL || receiver == NULL || giver->gold < amount) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  giver->gold -= amount;
  receiver->gold += amount;
  printf("%s gives %d gold to %s.\n",
         giver->name,
         amount,
         receiver->name);
  FlushInput();

  return SUCCESS;
}

/******************************************************************************
   Function: AddItem

Description: Adds a given item to a given game character's inventory.

     Inputs: receiver - Pointer to the GC receiving the item.
             itemID   - ID of the item to be added.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int AddItem(GameCharacter *receiver, int itemID) {
  if (receiver == NULL) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  receiver->inventory[itemID]++;
  if (receiver->ID == PLAYER) {
    printf("You discover: %s\n", GetItemName(itemID));
    FlushInput();
  }

  return SUCCESS;
}

/******************************************************************************
   Function: GiveItem

Description: Transfers an item from one game character to another.

     Inputs: giver    - Pointer to the GC giving the item.
             receiver - Pointer to the GC receiving the item.
             itemID   - ID of the item to be transferred.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int GiveItem(GameCharacter *giver, GameCharacter *receiver, int itemID) {
  if (giver == NULL || receiver == NULL || giver->inventory[itemID] <= 0) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  giver->inventory[itemID]--;
  if (giver->equippedItems[itemID] > giver->inventory[itemID]) {
    giver->equippedItems[itemID]--;
  }
  receiver->inventory[itemID]++;
  printf("%s gives %s to %s\n",
         giver->name,
         GetItemName(itemID),
         receiver->name);
  FlushInput();

  return SUCCESS;
}

/******************************************************************************
   Function: GiveItems

Description: Transfers a specified amount of a given item from one game
             character to another.

     Inputs: giver    - Pointer to the GC giving the item.
             receiver - Pointer to the GC receiving the item.
             itemID   - ID of the item to be transferred.
             amount   - Quantity of the item to be transferred.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int GiveItems(GameCharacter *giver,
              GameCharacter *receiver,
              int itemID,
              int amount) {
  if (giver == NULL || receiver == NULL || giver->inventory[itemID] < amount) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  giver->inventory[itemID] -= amount;
  if (giver->equippedItems[itemID] > giver->inventory[itemID]) {
    giver->equippedItems[itemID] = giver->inventory[itemID];
  }
  receiver->inventory[itemID] += amount;
  printf("%s gives %d %s to %s.\n",
         giver->name,
         amount,
         GetItemNamePlural(itemID),
         receiver->name);
  FlushInput();

  return SUCCESS;
}

/******************************************************************************
   Function: ItemValue

Description: Returns the standard market value of a given item.

     Inputs: idNum - ID number of the item of interest.

    Outputs: The standard market value of the item of interest (or -1 if an
             error is encountered).
******************************************************************************/
int ItemValue(int idNum) {
  switch (idNum) {
    case FOOD:
      return 1;
    case HEALING_POTION:
      return 15;
    case GLOWING_MUSHROOM:
      return 20;
    default:
#if DEBUG
      ERROR_MESSAGE
#endif
      break;
  }

  return -1;
}
