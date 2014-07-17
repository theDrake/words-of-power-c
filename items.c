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
int ItemMenu(void)
{
  int i;  /* for loop variable */
  int iInput;
  int temp = 0;

  for (i = 0; i < TOTAL_ITEM_IDS; i++)
  {
    if (player.inventory[i] > 0)
    {
      temp++;
      printf("[%d] ", temp);
      PrintItemName(i);
      printf(" (%d)\n", player.inventory[i]);
    }
  }
  if (temp == 0)
  {
    printf("You have no items.\n");
    FlushInput();
    return FAILURE;
  }
  else
  {
    temp++;
    printf("[%d] Cancel (return to previous menu)\n", temp);
    GetIntInput(&iInput, 1, temp);
    temp = 0;
    for (i = 0; i < TOTAL_ITEM_IDS; i++)
    {
      if (player.inventory[i] > 0)
      {
        temp++;
        if (temp == iInput)
        {
          UseItem(&player, i);
          return SUCCESS;
        }
      }
    }
  }

  return FAILURE; /* No item was used: the player changed his/her mind.      */
}

/******************************************************************************
   Function: UseItem

Description: Executes the use of an item by a given game character (the player
             or an NPC).

     Inputs: pGC   - Pointer to the user of the item.
             idNum - ID number of the item to be used.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int UseItem(GameCharacter *pGC, int idNum)
{
  if (pGC->inventory[idNum] < 1)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  switch(idNum)
  {
    case HEALING_POTION:
      PrintNameDefinite(pGC, UPPERCASE);
      printf(" drinks a healing potion and regains %d hit points.\n",
             HealGameCharacter(pGC, RandomInt(DEFAULT_HP / 2, DEFAULT_HP)));
      break;
    case FOOD:
      PrintNameDefinite(pGC, TRUE);
      printf(" eats some food and regains %d hit points.\n",
             HealGameCharacter(pGC,
                               RandomInt(DEFAULT_HP / 4, DEFAULT_HP / 2)));
      break;
    default:
#ifdef DEBUG
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
int PrintInventory(GameCharacter *pGC)
{
  int i; /* for loop variable */
  int itemTypesDescribed = 0;

  if (pGC == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return -1;
  }

  printf("Inventory: ");
  for (i = 0; i < TOTAL_ITEM_IDS; i++)
  {
    if (pGC->inventory[i] > 0)
    {
      if (itemTypesDescribed > 0)
      {
        printf(", ");
        if (itemTypesDescribed % 3 == 0)
        {
          printf("\n\t");
        }
      }
      if (pGC->inventory[i] == 1)
      {
        PrintItemName(i);
      }
      else
      {
        printf("%d ", pGC->inventory[i]);
        PrintItemNamePlural(i);
      }
      if (pGC->equippedItems[i] > 0)
      {
        if (pGC->inventory[i] == 1)
        {
          printf("(equipped)");
        }
        else
        {
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
   Function: PrintItemName

Description: Given an item ID, prints the name of that item.

     Inputs: idNum - ID number of an item.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int PrintItemName(int idNum)
{
  switch (idNum)
  {
    case FOOD:
      printf("Food Packet");
      break;
    case HEALING_POTION:
      printf("Healing Potion");
      break;
    case GLOWING_MUSHROOM:
      printf("Glowing Mushroom");
      break;
    default:
#ifdef DEBUG
      ERROR_MESSAGE
#endif
      printf("???");
      return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: PrintItemNamePlural

Description: Given an item ID, prints the plural name of that item.

     Inputs: idNum - ID number of an item.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int PrintItemNamePlural(int idNum)
{
  BOOL errorFound = FALSE;

  switch (idNum)
  {
    default:
      if (PrintItemName(idNum) == FAILURE)
      {
        errorFound = TRUE;
      }
      printf("s");  /* The default is to simply add an 's' to the item name. */
      break;
  }
  if (errorFound)
  {
    return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: GiveGold

Description: Transfers gold from one game character to another.

     Inputs: giver    - Pointer to the GC giving gold.
             receiver - Pointer to the GC receiving gold.
             amount   - Amount of gold to be transferred.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int GiveGold(GameCharacter *giver, GameCharacter *receiver, int amount)
{
  if (giver == NULL || receiver == NULL || giver->gold < amount)
  {
#ifdef DEBUG
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
int AddItem(GameCharacter *receiver, int itemID)
{
  if (receiver == NULL)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  receiver->inventory[itemID]++;
  if (receiver->ID == PLAYER)
  {
    printf("You discover: ");
    PrintItemName(itemID);
    printf("\n");
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
int GiveItem(GameCharacter *giver, GameCharacter *receiver, int itemID)
{
  if (giver == NULL || receiver == NULL || giver->inventory[itemID] <= 0)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  giver->inventory[itemID]--;
  if (giver->equippedItems[itemID] > giver->inventory[itemID])
  {
    giver->equippedItems[itemID]--;
  }
  receiver->inventory[itemID]++;
  printf("%s gives ", giver->name);
  PrintItemName(itemID);
  printf(" to %s.\n", receiver->name);
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
              int amount)
{
  if (giver == NULL || receiver == NULL || giver->inventory[itemID] < amount)
  {
#ifdef DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  giver->inventory[itemID] -= amount;
  if (giver->equippedItems[itemID] > giver->inventory[itemID])
  {
    giver->equippedItems[itemID] = giver->inventory[itemID];
  }
  receiver->inventory[itemID] += amount;
  printf("%s gives %d ", giver->name, amount);
  PrintItemNamePlural(itemID);
  printf(" to %s.\n", receiver->name);
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
int ItemValue(int idNum)
{
  switch (idNum)
  {
    case FOOD:
      return 1;
    case HEALING_POTION:
      return 15;
    case GLOWING_MUSHROOM:
      return 20;
    default:
#ifdef DEBUG
      ERROR_MESSAGE
#endif
      break;
  }

  return -1;
}
