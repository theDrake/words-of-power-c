/******************************************************************************
   Filename: locations.c

     Author: David C. Drake (http://davidcdrake.com)

Description: Functions governing locations, their inhabitants, and movement
             between locations for the text-based fantasy RPG "Words of Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: InitializeLocation

Description: Initializes a given location struct, along with all of its
             inhabitants (a linked list of game character structs), to their
             default starting values.

     Inputs: location - Pointer to the location struct to be initialized.
             idNum    - ID number of the desired location.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int InitializeLocation(location_t *location, int idNum) {
  int i;

  location->ID = idNum;
  location->hidden = false;
  location->visits = 0;
  location->searches = 0;
  location->inhabitants = NULL;

  switch (idNum) {
    case ILLARUM_ENTRANCE:
      strcpy(location->name, "Illarum, City Gate");
      AddInhabitants(location, HUMAN, RandomInt(15, 25));
      AddInhabitants(location, SOLDIER, RandomInt(8, 12));
      break;
    case ILLARUM_MARKET:
      strcpy(location->name, "Illarum, Marketplace");
      AddInhabitants(location, HUMAN, RandomInt(15, 25));
      AddInhabitants(location, MERCHANT, RandomInt(7, 12));
      AddInhabitants(location, SOLDIER, RandomInt(3, 6));
      break;
    case ILLARUM_INN:
      strcpy(location->name, "Illarum, Inn");
      AddInhabitant(location, INNKEEPER);
      AddInhabitants(location, HUMAN, RandomInt(15, 25));
      break;
    case ILLARUM_SCHOOL:
      strcpy(location->name, "Illarum, School of the Elements");
      AddInhabitants(location, WIZARD_OF_ELEMENTS, RandomInt(7, 12));
      AddInhabitant(location, ARCHWIZARD_OF_ELEMENTS);
      AddInhabitants(location, HUMAN, RandomInt(3, 6));
      break;
    case ILLARUM_TEMPLE:
      strcpy(location->name, "Illarum, Temple");
      AddInhabitants(location, ILLARUM_PRIEST, RandomInt(7, 12));
      AddInhabitant(location, ILLARUM_HIGH_PRIEST);
      AddInhabitants(location, HUMAN, RandomInt(3, 6));
      break;
    case ILLARUM_PALACE:
      strcpy(location->name, "Illarum, Palace of the King");
      AddInhabitant(location, ILLARUM_KING);
      AddInhabitants(location, COURT_WIZARD, RandomInt(1, 2));
      AddInhabitants(location, NOBLEMAN, RandomInt(3, 6));
      AddInhabitants(location, KNIGHT, RandomInt(1, 2));
      AddInhabitants(location, SOLDIER, RandomInt(7, 12));
      AddInhabitants(location, SERVANT, RandomInt(3, 6));
      break;
    case ILLARUM_PRISON:
      strcpy(location->name, "Illarum, Prison");
      AddInhabitants(location, PRISONER, RandomInt(7, 12));
      AddInhabitants(location, SOLDIER, RandomInt(3, 6));
      break;
    case VENTARRIS_ENTRANCE:
      strcpy(location->name, "Ventarris, Main Gate");
      AddInhabitants(location, SOLDIER, RandomInt(8, 12));
      AddInhabitants(location, HUMAN, RandomInt(15, 25));
      break;
    case VENTARRIS_MARKET:
      strcpy(location->name, "Ventarris, Marketplace");
      AddInhabitants(location, HUMAN, RandomInt(15, 25));
      AddInhabitants(location, MERCHANT, RandomInt(7, 12));
      AddInhabitants(location, SLAVE, RandomInt(3, 6));
      AddInhabitants(location, SOLDIER, RandomInt(3, 6));
      break;
    case VENTARRIS_INN:
      strcpy(location->name, "Ventarris, Inn");
      AddInhabitant(location, INNKEEPER);
      AddInhabitants(location, SAILOR, RandomInt(3, 6));
      AddInhabitants(location, HUMAN, RandomInt(7, 12));
      break;
    case VENTARRIS_SCHOOL:
      strcpy(location->name, "Ventarris, School of Mind");
      AddInhabitants(location, WIZARD_OF_MIND, RandomInt(7, 12));
      AddInhabitant(location, ARCHWIZARD_OF_MIND);
      AddInhabitants(location, SLAVE, RandomInt(3, 6));
      break;
    case VENTARRIS_TEMPLE:
      strcpy(location->name, "Ventarris, Temple");
      AddInhabitants(location, VENTARRIS_PRIEST, RandomInt(7, 12));
      AddInhabitant(location, VENTARRIS_HIGH_PRIEST);
      AddInhabitants(location, HUMAN, RandomInt(3, 6));
      break;
    case VENTARRIS_PALACE:
      strcpy(location->name, "Ventarris, Palace of the King");
      AddInhabitant(location, VENTARRIS_KING);
      AddInhabitants(location, COURT_WIZARD, RandomInt(1, 2));
      AddInhabitants(location, NOBLEMAN, RandomInt(7, 12));
      AddInhabitants(location, KNIGHT, RandomInt(1, 2));
      AddInhabitants(location, SOLDIER, RandomInt(7, 12));
      AddInhabitants(location, SERVANT, RandomInt(3, 6));
      AddInhabitants(location, SLAVE, RandomInt(7, 12));
      break;
    case VENTARRIS_PRISON:
      strcpy(location->name, "Ventarris, Prison");
      AddInhabitants(location, PRISONER, RandomInt(20, 29));
      AddInhabitants(location, SOLDIER, RandomInt(3, 6));
      AddInhabitant(location, KNIGHT);
      break;
    case VENTARRIS_DOCKS:
      strcpy(location->name, "Ventarris, Docks");
      AddInhabitants(location, FISHERMAN, RandomInt(3, 6));
      AddInhabitants(location, SAILOR, RandomInt(7, 12));
      AddInhabitants(location, SLAVE, RandomInt(3, 6));
      AddInhabitants(location, SOLDIER, RandomInt(7, 12));
      break;
    case PLAINS_NORTH:
      strcpy(location->name, "Northern Plains");
      break;
    case NORTHERN_FARMS:
      strcpy(location->name, "Northern Farmlands");
      AddInhabitants(location, FARMER, RandomInt(3, 6));
      break;
    case BRILL_OUTSKIRTS:
      strcpy(location->name, "Brill, Outskirts");
      AddInhabitants(location, HUMAN, RandomInt(3, 6));
      break;
    case BRILL_MARKET:
      strcpy(location->name, "Brill, Marketplace");
      AddInhabitants(location, MERCHANT, RandomInt(3, 5));
      AddInhabitants(location, HUMAN, RandomInt(7, 12));
      break;
    case BRILL_INN:
      strcpy(location->name, "Brill, Inn");
      AddInhabitant(location, INNKEEPER);
      AddInhabitants(location, SAILOR, RandomInt(3, 6));
      AddInhabitants(location, HUMAN, RandomInt(7, 12));
      break;
    case BRILL_DOCKS:
      strcpy(location->name, "Brill, Docks");
      AddInhabitants(location, SAILOR, RandomInt(13, 19));
      AddInhabitants(location, FISHERMAN, RandomInt(7, 12));
      AddInhabitant(location, THE_ANGLER);
      break;
    case PLAINS_SOUTH:
      strcpy(location->name, "Southern Plains");
      break;
    case SOUTHERN_FARMS:
      strcpy(location->name, "Southern Farmlands");
      AddInhabitants(location, FARMER, RandomInt(7, 12));
      AddInhabitants(location, SLAVE, RandomInt(3, 5));
      break;
    case SILENT_SAGE_HOME:
      strcpy(location->name, "Solitary House");
      AddInhabitant(location, THE_SILENT_SAGE);
      location->hidden = true;
      break;
    case FOREST:
      strcpy(location->name, "Western Woods, Fringe");
      break;
    case DRUIDS_GROVE:
      strcpy(location->name, "Druids' Grove");
      AddInhabitant(location, ARCHDRUID);
      AddInhabitants(location, DRUID, RandomInt(3, 6));
      location->hidden = true;
      break;
    case HERMIT_HUT:
      strcpy(location->name, "Solitary Hut");
      AddInhabitant(location, THE_HERMIT);
      location->hidden = true;
      break;
    case WYNNFAER_ENTRANCE:
      strcpy(location->name, "Wynnfaer, Main Gate");
      AddInhabitants(location, ELF, RandomInt(3, 6));
      location->hidden = true;
      break;
    case WYNNFAER_PLAZA:
      strcpy(location->name, "Wynnfaer, Central Plaza");
      AddInhabitants(location, ELF, RandomInt(15, 25));
      break;
    case WYNNFAER_PALACE:
      strcpy(location->name, "Wynnfaer, Palace");
      AddInhabitants(location, ELF_LOREMASTER, RandomInt(7, 12));
      break;
    case MOUNTAINS:
      strcpy(location->name, "Northern Mountains, Foothills");
      break;
    case GESHTAL:
      strcpy(location->name, "Gesh'tal");
      AddInhabitants(location, BARBARIAN, RandomInt(15, 25));
      AddInhabitants(location, BARBARIAN_WARRIOR, RandomInt(7, 12));
      AddInhabitants(location, BARBARIAN_SHAMAN, RandomInt(3, 6));
      AddInhabitant(location, BARBARIAN_CHIEFTAIN);
      location->hidden = true;
      break;
    case TORR_ENTRANCE:
      strcpy(location->name, "Torr, Entrance");
      AddInhabitants(location, DWARF_GUARDIAN, RandomInt(3, 6));
      location->hidden = true;
      break;
    case TORR_MARKET:
      strcpy(location->name, "Torr, Marketplace");
      AddInhabitants(location, DWARF, RandomInt(15, 25));
      AddInhabitants(location, DWARF_MERCHANT, RandomInt(3, 6));
      break;
    case TORR_SCHOOL:
      strcpy(location->name, "Torr, School");
      AddInhabitants(location, DWARF, RandomInt(7, 12));
      AddInhabitants(location, DWARF_LOREMASTER, RandomInt(1, 2));
      break;
    case TORR_TEMPLE:
      strcpy(location->name, "Torr, Temple");
      AddInhabitant(location, DWARF_HIGH_PRIEST);
      AddInhabitants(location, DWARF_PRIEST, RandomInt(3, 6));
      break;
    case TORR_THRONE_ROOM:
      strcpy(location->name, "Torr, Throne Room");
      AddInhabitant(location, DWARF_KING);
      AddInhabitants(location, DWARF_GUARDIAN, RandomInt(3, 6));
      break;
    case TORR_MINE:
      strcpy(location->name, "Torr, Mine");
      AddInhabitants(location, DWARF_MINER, RandomInt(7, 12));
      AddInhabitants(location, DWARF_GUARDIAN, RandomInt(1, 2));
      break;
    case TORR_VAULT:
      strcpy(location->name, "Torr, Secret Vault");
      AddInhabitants(location, DWARF_LOREMASTER, RandomInt(1, 2));
      location->hidden = true;
      break;
    case TORR_PRISON:
      strcpy(location->name, "Torr, Prison");
      AddInhabitants(location, PRISONER, RandomInt(3, 6));
      AddInhabitants(location, DWARF_GUARDIAN, 2);
      break;
    case GUGGENHOLM_ENTRANCE:
      strcpy(location->name, "Guggenholm, Entrance");
      AddInhabitant(location, DRAGON);
      location->hidden = true;
      break;
    case GUGGENHOLM_MAIN:
      strcpy(location->name, "Guggenholm, Main Hall");
      AddInhabitants(location, GNOME, RandomInt(15, 25));
      break;
    case GUGGENHOLM_MINE:
      strcpy(location->name, "Guggenholm, Mine");
      AddInhabitants(location, GNOME_MINER, RandomInt(7, 12));
      break;
    case SWAMP:
      strcpy(location->name, "Southwestern Swamplands, Fringe");
      break;
    case NECROMANCERS_CIRCLE:
      strcpy(location->name, "Southwestern Swamplands, Deep");
      AddInhabitants(location, NECROMANCER, RandomInt(7, 12));
      AddInhabitant(location, ARCHNECROMANCER);
      AddInhabitants(location, SLAVE, 2);
      AddInhabitants(location, ZOMBIE, RandomInt(3, 6));
      break;
    case ISHTARR_ENTRANCE:
      strcpy(location->name, "Ishtarr, Main Gate");
      AddInhabitants(location, ZOMBIE, RandomInt(3, 6));
      AddInhabitants(location, SKELETAL_KNIGHT, 2);
      break;
    case ISHTARR_EAST_WING:
      strcpy(location->name, "Ishtarr, East Wing");
      AddInhabitants(location, NECROMANCER, RandomInt(1, 2));
      AddInhabitants(location, ZOMBIE, RandomInt(3, 6));
      break;
    case ISHTARR_WEST_WING:
      strcpy(location->name, "Ishtarr, West Wing");
      AddInhabitants(location, NECROMANCER, RandomInt(1, 2));
      AddInhabitants(location, ZOMBIE, RandomInt(3, 6));
      break;
    case ISHTARR_CENTRAL_TOWER:
      strcpy(location->name, "Ishtarr, Central Tower");
      AddInhabitants(location, SKELETAL_KNIGHT, 2);
      AddInhabitant(location, LICH);
      break;
    case ISHTARR_DUNGEON:
      strcpy(location->name, "Ishtarr, Dungeon");
      AddInhabitants(location, PRISONER, RandomInt(3, 6));
      AddInhabitants(location, RAT, RandomInt(1, 2));
      break;
    case SHORE_NE:
      strcpy(location->name, "Northeastern Shoreline");
      AddInhabitants(location, FISHERMAN, RandomInt(0, 2));
      break;
    case SHORE_EAST:
      strcpy(location->name, "Eastern Shoreline");
      AddInhabitants(location, FISHERMAN, RandomInt(0, 2));
      break;
    case SHORE_SE:
      strcpy(location->name, "Southeastern Shoreline");
      AddInhabitants(location, FISHERMAN, RandomInt(0, 2));
      break;
    case OCEAN_SURFACE:
      strcpy(location->name, "Ocean Surface");
      break;
    case OCEAN_SHALLOW:
      strcpy(location->name, "Ocean, Shallow Waters");
      break;
    case OCEAN_DEEP:
      strcpy(location->name, "Ocean, Deep");
      break;
    case OCEAN_TRENCH:
      strcpy(location->name, "Ocean, Trench");
      location->hidden = true;
      break;
    case QUELACENTUS_ENTRANCE:
      strcpy(location->name, "Quelacentus, Entrance");
      AddInhabitants(location, MERFOLK_SOLDIER, RandomInt(3, 6));
      location->hidden = true;
      break;
    case QUELACENTUS_PLAZA:
      strcpy(location->name, "Quelacentus, Central Plaza");
      AddInhabitants(location, MERFOLK, RandomInt(7, 12));
      AddInhabitants(location, MERFOLK_SOLDIER, RandomInt(3, 6));
      break;
    case QUELACENTUS_TEMPLE:
      strcpy(location->name, "Quelacentus, Temple");
      AddInhabitants(location, MERFOLK_PRIESTESS, RandomInt(7, 12));
      AddInhabitant(location, MERFOLK_HIGH_PRIESTESS);
      break;
    case QUELACENTUS_PALACE:
      strcpy(location->name, "Quelacentus, Palace");
      AddInhabitant(location, MERFOLK_QUEEN);
      AddInhabitants(location, MERFOLK_PRIESTESS, RandomInt(1, 2));
      AddInhabitants(location, MERFOLK_SOLDIER, RandomInt(3, 6));
      break;
    default:
#if DEBUG
      PRINT_ERROR_MESSAGE;
#endif
      return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: InVentarrisTerritory

Description: Determines whether a given location is within the territory
             claimed by the king of Ventarris.

     Inputs: location - The location of interest.

    Outputs: true or false.
******************************************************************************/
bool InVentarrisTerritory(location_t *location) {
  return location->ID == VENTARRIS_ENTRANCE    ||
         location->ID == VENTARRIS_MARKET      ||
         location->ID == VENTARRIS_INN         ||
         location->ID == VENTARRIS_SCHOOL      ||
         location->ID == VENTARRIS_TEMPLE      ||
         location->ID == VENTARRIS_PALACE      ||
         location->ID == VENTARRIS_PRISON      ||
         location->ID == VENTARRIS_DOCKS       ||
         location->ID == PLAINS_SOUTH          ||
         location->ID == SOUTHERN_FARMS        ||
         location->ID == SWAMP                 ||
         location->ID == NECROMANCERS_CIRCLE   ||
         location->ID == ISHTARR_ENTRANCE      ||
         location->ID == ISHTARR_EAST_WING     ||
         location->ID == ISHTARR_WEST_WING     ||
         location->ID == ISHTARR_CENTRAL_TOWER ||
         location->ID == ISHTARR_DUNGEON       ||
         location->ID == SHORE_SE;
}

/******************************************************************************
   Function: AddInhabitant

Description: Creates a new game character and adds it to a given location's list
             of inhabitants.

     Inputs: location - Location into which the new character will be added.
             idNum    - ID of the desired game character.

    Outputs: Pointer to the new game character (or NULL if it failed).
******************************************************************************/
game_character_t *AddInhabitant(location_t *location, int idNum) {
  game_character_t *newGC = NULL, *temp;

  if (location == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
  } else {
    newGC = malloc(sizeof(game_character_t));
    if (newGC != NULL) {
      InitializeCharacter(newGC, idNum, location);
      newGC->locationID = location->ID;
      if (location->inhabitants == NULL) {
        location->inhabitants = newGC;  /* New inhabitant successfully added. */
      } else {
        for (temp = location->inhabitants;
             temp->next != NULL;
             temp = temp->next)
          ;
        temp->next = newGC;  /* New inhabitant successfully added. */
      }
    } else {
#if DEBUG
      PRINT_ERROR_MESSAGE;
#endif
      exit(1);
    }
  }

  return newGC;
}

/******************************************************************************
   Function: AddInhabitants

Description: Creates multiple game characters of a single type and adds them to
             a given location's list of inhabitants.

     Inputs: location - Location into which the new characters will be added.
             idNum    - Designates the desired game character type.
             amount   - Number of game characters to add.

    Outputs: Number of game characters successfully added.
******************************************************************************/
int AddInhabitants(location_t *location, int idNum, int amount) {
  int count;

  while (amount-- > 0) {
    if(AddInhabitant(location, idNum) != NULL) {
      count++;
    }
  }

  return count;
}

/******************************************************************************
   Function: FindInhabitant

Description: Returns a pointer to the first inhabitant found (if any) bearing a
             given ID value.

     Inputs: idNum - ID of the desired character or character type.

    Outputs: Pointer to an appropriate inhabitant, or NULL if none is found.
******************************************************************************/
game_character_t *FindInhabitant(int idNum) {
  game_character_t *pGC;

  for (pGC = world[player.locationID]->inhabitants;
       pGC != NULL;
       pGC = pGC->next) {
    if (pGC->ID == idNum) {
      return pGC;
    }
  }

  return NULL;
}

/******************************************************************************
   Function: MoveInhabitant

Description: Handles the movement of an NPC from one location to another.

     Inputs: inhabitant    - Pointer to the game character to be moved.
             destinationID - ID of the desired destination.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int MoveInhabitant(game_character_t *inhabitant, int destinationID) {
  game_character_t *pGC1, *pGC2;

  if (inhabitant == NULL ||
      destinationID < 0 ||
      destinationID >= NUM_LOCATION_IDS) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

    /* Add "inhabitant" to the new location's list of inhabitants. */
  if (world[destinationID]->inhabitants == NULL) {
    world[destinationID]->inhabitants = inhabitant;
  } else {
    for (pGC1 = world[destinationID]->inhabitants;
         pGC1->next != NULL;
         pGC1 = pGC1->next)
      ;
    pGC1->next = inhabitant;
  }

    /* Remove "inhabitant" from the old location's list of inhabitants. */
  for (pGC1 = world[inhabitant->locationID]->inhabitants;
       pGC1 != NULL;
       pGC2 = pGC1, pGC1 = pGC1->next) {
    if (pGC1 == inhabitant) {
      if (pGC1->next == NULL) {
        pGC2->next = NULL;
      } else {
        pGC2->next = pGC1->next;
      }
      break;
    }
  }

    /* Update other relevant variables. */
  inhabitant->locationID = destinationID;
  inhabitant->next = NULL;
  if (inhabitant->summonedCreature != NULL) {
    inhabitant->summonedCreature->locationID = destinationID;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: RemoveInhabitant

Description: Removes a game character from a location's list of inhabitants.

     Inputs: location   - Pointer to the relevant location.
             inhabitant - Pointer to the game character to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int RemoveInhabitant(location_t *location, game_character_t *inhabitant) {
  game_character_t *pGC1, *pGC2;

  if (location == NULL || inhabitant == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  for (pGC1 = location->inhabitants;
       pGC1 != NULL;
       pGC2 = pGC1, pGC1 = pGC1->next) {
    if (pGC1 == inhabitant) {
      if (pGC1->next == NULL) {
        pGC2->next = NULL;
      } else {
        pGC2->next = pGC1->next;
      }
      return SUCCESS;
    }
  }
  if (pGC1 == NULL) {  /* If true, "inhabitant" was not found. */
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: DeleteInhabitant

Description: Removes a game character from a location's list of inhabitants and
             deallocates its associated memory.

     Inputs: location   - Pointer to the relevant location.
             inhabitant - Pointer to the game character to be removed.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int DeleteInhabitant(location_t *location, game_character_t *inhabitant) {
  game_character_t *pGC1, *pGC2;

  if (location == NULL || inhabitant == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  pGC1 = location->inhabitants;
  pGC2 = NULL;
  do {    if (pGC1 == inhabitant) {
      if (pGC2 == NULL) {  /* Only one inhabitant in this location. */
        location->inhabitants = NULL;
      } else {  /* More than one inhabitant in this location. */
        if (inhabitant->next == NULL) {  /* End of the list. */
          pGC2->next = NULL;  /* Remove remaining pointer to "inhabitant". */
        } else {  /* "inhabitant" is not the end of the list. */
            /*
             * Set the game character previous to "inhabitant" to point at the
             * next game character after "inhabitant".
             */
          pGC1 = inhabitant->next;
          pGC2->next = pGC1;
        }
      }
      if (inhabitant->summonedCreature != NULL) {
        DeleteCreatureSummonedBy(inhabitant);
      }
      free(inhabitant);
      return SUCCESS;
    } else {
      pGC2 = pGC1;
      pGC1 = pGC1->next;
    }
  }while (pGC1 != NULL);

    /* If we reach this point, "inhabitant" was not found.                   */
#if DEBUG
  PRINT_ERROR_MESSAGE;
#endif
  return FAILURE;
}

/******************************************************************************
   Function: VisibleInhabitants

Description: Returns the number of visible inhabitants in a given location.

     Inputs: location - Pointer to the location of interest.

    Outputs: The number of visible inhabitants in the specified location.
******************************************************************************/
int VisibleInhabitants(location_t *location) {
  int count = 0;
  game_character_t *pGC;

  if (location == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
  } else {
    for (pGC = location->inhabitants;
         pGC != NULL;
         pGC = pGC->next) {
      if (pGC->status[INVISIBLE] == false) {
        count++;
      }
    }
  }

  return count;
}

/******************************************************************************
   Function: MovementMenu

Description: Displays movement options to the player.

     Inputs: None.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int MovementMenu(void) {
  int i, iInput, numDestinations = 0;
  location_t *destinations[MAX_DESTINATIONS] = {NULL};

    /* Determine available destinations and describe their orientation. */
  switch (player.locationID) {
    case ILLARUM_ENTRANCE:
      destinations[0] = world[ILLARUM_MARKET];
      destinations[1] = world[ILLARUM_INN];
      destinations[2] = world[ILLARUM_SCHOOL];
      destinations[3] = world[ILLARUM_TEMPLE];
      destinations[4] = world[ILLARUM_PALACE];
      destinations[5] = world[ILLARUM_PRISON];
      destinations[6] = world[PLAINS_NORTH];
      destinations[7] = world[PLAINS_SOUTH];
      destinations[8] = world[SHORE_EAST];
      destinations[9] = world[FOREST];
      break;
    case ILLARUM_MARKET:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[ILLARUM_INN];
      destinations[2] = world[ILLARUM_SCHOOL];
      destinations[3] = world[ILLARUM_TEMPLE];
      destinations[4] = world[ILLARUM_PALACE];
      destinations[5] = world[ILLARUM_PRISON];
      break;
    case ILLARUM_INN:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[ILLARUM_MARKET];
      destinations[2] = world[ILLARUM_SCHOOL];
      destinations[3] = world[ILLARUM_TEMPLE];
      destinations[4] = world[ILLARUM_PALACE];
      destinations[5] = world[ILLARUM_PRISON];
      break;
    case ILLARUM_SCHOOL:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[ILLARUM_MARKET];
      destinations[2] = world[ILLARUM_INN];
      destinations[3] = world[ILLARUM_TEMPLE];
      destinations[4] = world[ILLARUM_PALACE];
      destinations[5] = world[ILLARUM_PRISON];
      break;
    case ILLARUM_TEMPLE:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[ILLARUM_MARKET];
      destinations[2] = world[ILLARUM_INN];
      destinations[3] = world[ILLARUM_SCHOOL];
      destinations[4] = world[ILLARUM_PALACE];
      destinations[5] = world[ILLARUM_PRISON];
      break;
    case ILLARUM_PALACE:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[ILLARUM_MARKET];
      destinations[2] = world[ILLARUM_INN];
      destinations[3] = world[ILLARUM_SCHOOL];
      destinations[4] = world[ILLARUM_TEMPLE];
      destinations[5] = world[ILLARUM_PRISON];
      break;
    case ILLARUM_PRISON:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[ILLARUM_MARKET];
      destinations[2] = world[ILLARUM_INN];
      destinations[3] = world[ILLARUM_SCHOOL];
      destinations[4] = world[ILLARUM_TEMPLE];
      destinations[5] = world[ILLARUM_PALACE];
      break;
    case VENTARRIS_ENTRANCE:
      destinations[0] = world[VENTARRIS_MARKET];
      destinations[1] = world[VENTARRIS_INN];
      destinations[2] = world[VENTARRIS_SCHOOL];
      destinations[3] = world[VENTARRIS_TEMPLE];
      destinations[4] = world[VENTARRIS_PALACE];
      destinations[5] = world[VENTARRIS_PRISON];
      destinations[6] = world[VENTARRIS_DOCKS];
      destinations[7] = world[SHORE_EAST];
      destinations[8] = world[SHORE_SE];
      destinations[9] = world[PLAINS_SOUTH];
      break;
    case VENTARRIS_MARKET:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[VENTARRIS_INN];
      destinations[2] = world[VENTARRIS_SCHOOL];
      destinations[3] = world[VENTARRIS_TEMPLE];
      destinations[4] = world[VENTARRIS_PALACE];
      destinations[5] = world[VENTARRIS_PRISON];
      destinations[6] = world[VENTARRIS_DOCKS];
      break;
    case VENTARRIS_INN:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[VENTARRIS_MARKET];
      destinations[2] = world[VENTARRIS_SCHOOL];
      destinations[3] = world[VENTARRIS_TEMPLE];
      destinations[4] = world[VENTARRIS_PALACE];
      destinations[5] = world[VENTARRIS_PRISON];
      destinations[6] = world[VENTARRIS_DOCKS];
      break;
    case VENTARRIS_SCHOOL:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[VENTARRIS_MARKET];
      destinations[2] = world[VENTARRIS_INN];
      destinations[3] = world[VENTARRIS_TEMPLE];
      destinations[4] = world[VENTARRIS_PALACE];
      destinations[5] = world[VENTARRIS_PRISON];
      destinations[6] = world[VENTARRIS_DOCKS];
      break;
    case VENTARRIS_TEMPLE:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[VENTARRIS_MARKET];
      destinations[2] = world[VENTARRIS_INN];
      destinations[3] = world[VENTARRIS_SCHOOL];
      destinations[4] = world[VENTARRIS_PALACE];
      destinations[5] = world[VENTARRIS_PRISON];
      destinations[6] = world[VENTARRIS_DOCKS];
      break;
    case VENTARRIS_PALACE:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[VENTARRIS_MARKET];
      destinations[2] = world[VENTARRIS_INN];
      destinations[3] = world[VENTARRIS_SCHOOL];
      destinations[4] = world[VENTARRIS_TEMPLE];
      destinations[5] = world[VENTARRIS_PRISON];
      destinations[6] = world[VENTARRIS_DOCKS];
      break;
    case VENTARRIS_PRISON:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[VENTARRIS_MARKET];
      destinations[2] = world[VENTARRIS_INN];
      destinations[3] = world[VENTARRIS_SCHOOL];
      destinations[4] = world[VENTARRIS_TEMPLE];
      destinations[5] = world[VENTARRIS_PALACE];
      destinations[6] = world[VENTARRIS_DOCKS];
      break;
    case VENTARRIS_DOCKS:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[VENTARRIS_MARKET];
      destinations[2] = world[VENTARRIS_INN];
      destinations[3] = world[VENTARRIS_SCHOOL];
      destinations[4] = world[VENTARRIS_TEMPLE];
      destinations[5] = world[VENTARRIS_PALACE];
      destinations[6] = world[VENTARRIS_PRISON];
      destinations[7] = world[SHORE_EAST];
      destinations[8] = world[SHORE_SE];
      destinations[9] = world[OCEAN_SURFACE];
      break;
    case PLAINS_NORTH:
      destinations[0] = world[NORTHERN_FARMS];
      destinations[1] = world[MOUNTAINS];
      destinations[2] = world[ILLARUM_ENTRANCE];
      destinations[3] = world[BRILL_OUTSKIRTS];
      destinations[4] = world[FOREST];
      destinations[5] = world[VENTARRIS_ENTRANCE];
      break;
    case NORTHERN_FARMS:
      destinations[0] = world[PLAINS_NORTH];
      destinations[1] = world[MOUNTAINS];
      destinations[2] = world[ILLARUM_ENTRANCE];
      destinations[3] = world[BRILL_OUTSKIRTS];
      destinations[4] = world[FOREST];
      destinations[5] = world[VENTARRIS_ENTRANCE];
      break;
    case BRILL_OUTSKIRTS:
      destinations[0] = world[BRILL_MARKET];
      destinations[1] = world[BRILL_INN];
      destinations[2] = world[BRILL_DOCKS];
      destinations[3] = world[MOUNTAINS];
      destinations[4] = world[SHORE_NE];
      destinations[5] = world[SHORE_EAST];
      destinations[6] = world[PLAINS_NORTH];
      break;
    case BRILL_MARKET:
      destinations[0] = world[BRILL_OUTSKIRTS];
      destinations[1] = world[BRILL_INN];
      destinations[2] = world[BRILL_DOCKS];
      break;
    case BRILL_INN:
      destinations[0] = world[BRILL_OUTSKIRTS];
      destinations[1] = world[BRILL_MARKET];
      destinations[2] = world[BRILL_DOCKS];
      break;
    case BRILL_DOCKS:
      destinations[0] = world[BRILL_OUTSKIRTS];
      destinations[1] = world[BRILL_MARKET];
      destinations[2] = world[BRILL_INN];
      destinations[3] = world[SHORE_NE];
      destinations[4] = world[SHORE_EAST];
      destinations[5] = world[OCEAN_SURFACE];
      break;
    case PLAINS_SOUTH:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[SOUTHERN_FARMS];
      destinations[2] = world[SILENT_SAGE_HOME];
      destinations[3] = world[SHORE_EAST];
      destinations[4] = world[VENTARRIS_ENTRANCE];
      destinations[5] = world[SHORE_SE];
      destinations[6] = world[FOREST];
      destinations[7] = world[SWAMP];
      break;
    case SOUTHERN_FARMS:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[PLAINS_SOUTH];
      destinations[2] = world[SILENT_SAGE_HOME];
      destinations[3] = world[SHORE_EAST];
      destinations[4] = world[VENTARRIS_ENTRANCE];
      destinations[5] = world[SHORE_SE];
      destinations[6] = world[FOREST];
      destinations[7] = world[SWAMP];
      break;
    case SILENT_SAGE_HOME:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[PLAINS_SOUTH];
      destinations[2] = world[SOUTHERN_FARMS];
      destinations[3] = world[SHORE_EAST];
      destinations[4] = world[VENTARRIS_ENTRANCE];
      destinations[5] = world[SHORE_SE];
      destinations[6] = world[FOREST];
      destinations[7] = world[SWAMP];
      break;
    case FOREST:
      destinations[0] = world[MOUNTAINS];
      destinations[1] = world[PLAINS_NORTH];
      destinations[2] = world[SWAMP];
      destinations[3] = world[ILLARUM_ENTRANCE];
      destinations[4] = world[PLAINS_SOUTH];
      break;
    case DRUIDS_GROVE:
      destinations[0] = world[MOUNTAINS];
      destinations[1] = world[PLAINS_NORTH];
      destinations[2] = world[SWAMP];
      destinations[3] = world[ILLARUM_ENTRANCE];
      destinations[4] = world[PLAINS_SOUTH];
      destinations[5] = world[FOREST];
      break;
    case HERMIT_HUT:
      destinations[0] = world[FOREST];
      break;
    case WYNNFAER_ENTRANCE:
      destinations[0] = world[WYNNFAER_PLAZA];
      destinations[1] = world[WYNNFAER_PALACE];
      destinations[2] = world[FOREST];
      break;
    case WYNNFAER_PLAZA:
      destinations[0] = world[WYNNFAER_ENTRANCE];
      destinations[1] = world[WYNNFAER_PALACE];
      break;
    case WYNNFAER_PALACE:
      destinations[0] = world[WYNNFAER_ENTRANCE];
      destinations[1] = world[WYNNFAER_PLAZA];
      break;
    case MOUNTAINS:
      destinations[0] = world[GESHTAL];
      destinations[1] = world[TORR_ENTRANCE];
      destinations[2] = world[FOREST];
      destinations[3] = world[PLAINS_NORTH];
      destinations[4] = world[BRILL_OUTSKIRTS];
      destinations[5] = world[SHORE_NE];
      break;
    case GESHTAL:
      destinations[0] = world[MOUNTAINS];
      destinations[1] = world[TORR_ENTRANCE];
      destinations[3] = world[FOREST];
      destinations[4] = world[PLAINS_NORTH];
      destinations[5] = world[BRILL_OUTSKIRTS];
      destinations[6] = world[SHORE_NE];
      break;
    case TORR_ENTRANCE:
      destinations[0] = world[TORR_MARKET];
      destinations[1] = world[TORR_SCHOOL];
      destinations[2] = world[TORR_TEMPLE];
      destinations[3] = world[TORR_THRONE_ROOM];
      destinations[4] = world[TORR_MINE];
      destinations[5] = world[TORR_PRISON];
      destinations[6] = world[MOUNTAINS];
      destinations[7] = world[GESHTAL];
      destinations[9] = world[FOREST];
      destinations[10] = world[PLAINS_NORTH];
      destinations[11] = world[BRILL_OUTSKIRTS];
      break;
    case TORR_MARKET:
      destinations[0] = world[TORR_ENTRANCE];
      destinations[1] = world[TORR_SCHOOL];
      destinations[2] = world[TORR_TEMPLE];
      destinations[3] = world[TORR_THRONE_ROOM];
      destinations[4] = world[TORR_MINE];
      destinations[5] = world[TORR_PRISON];
      break;
    case TORR_SCHOOL:
      destinations[0] = world[TORR_ENTRANCE];
      destinations[1] = world[TORR_MARKET];
      destinations[2] = world[TORR_TEMPLE];
      destinations[3] = world[TORR_THRONE_ROOM];
      destinations[4] = world[TORR_MINE];
      destinations[5] = world[TORR_PRISON];
      break;
    case TORR_TEMPLE:
      destinations[0] = world[TORR_ENTRANCE];
      destinations[1] = world[TORR_MARKET];
      destinations[2] = world[TORR_SCHOOL];
      destinations[3] = world[TORR_THRONE_ROOM];
      destinations[4] = world[TORR_MINE];
      destinations[5] = world[TORR_PRISON];
      break;
    case TORR_THRONE_ROOM:
      destinations[0] = world[TORR_ENTRANCE];
      destinations[1] = world[TORR_MARKET];
      destinations[2] = world[TORR_SCHOOL];
      destinations[3] = world[TORR_TEMPLE];
      destinations[4] = world[TORR_MINE];
      destinations[5] = world[TORR_PRISON];
      break;
    case TORR_MINE:
      destinations[0] = world[TORR_ENTRANCE];
      destinations[1] = world[TORR_MARKET];
      destinations[2] = world[TORR_SCHOOL];
      destinations[3] = world[TORR_TEMPLE];
      destinations[4] = world[TORR_THRONE_ROOM];
      destinations[5] = world[TORR_PRISON];
      break;
    case TORR_VAULT:
      destinations[0] = world[TORR_SCHOOL];
      break;
    case TORR_PRISON:
      destinations[0] = world[TORR_ENTRANCE];
      destinations[1] = world[TORR_MARKET];
      destinations[2] = world[TORR_SCHOOL];
      destinations[3] = world[TORR_TEMPLE];
      destinations[4] = world[TORR_THRONE_ROOM];
      destinations[5] = world[TORR_MINE];
      break;
    case GUGGENHOLM_ENTRANCE:
      destinations[0] = world[GUGGENHOLM_MAIN];
      destinations[1] = world[MOUNTAINS];
      break;
    case GUGGENHOLM_MAIN:
      destinations[0] = world[GUGGENHOLM_ENTRANCE];
      destinations[1] = world[GUGGENHOLM_MINE];
      break;
    case GUGGENHOLM_MINE:
      destinations[0] = world[GUGGENHOLM_MAIN];
      break;
    case SWAMP:
      destinations[0] = world[FOREST];
      destinations[1] = world[PLAINS_SOUTH];
      destinations[2] = world[NECROMANCERS_CIRCLE];
      break;
    case NECROMANCERS_CIRCLE:
      destinations[0] = world[ISHTARR_ENTRANCE];
      destinations[1] = world[SWAMP];
      break;
    case ISHTARR_ENTRANCE:
      destinations[0] = world[ISHTARR_EAST_WING];
      destinations[1] = world[ISHTARR_WEST_WING];
      destinations[2] = world[ISHTARR_CENTRAL_TOWER];
      destinations[3] = world[ISHTARR_DUNGEON];
      destinations[4] = world[NECROMANCERS_CIRCLE];
      break;
    case ISHTARR_EAST_WING:
      destinations[0] = world[ISHTARR_ENTRANCE];
      destinations[1] = world[ISHTARR_WEST_WING];
      destinations[2] = world[ISHTARR_CENTRAL_TOWER];
      destinations[3] = world[ISHTARR_DUNGEON];
      break;
    case ISHTARR_WEST_WING:
      destinations[0] = world[ISHTARR_ENTRANCE];
      destinations[1] = world[ISHTARR_EAST_WING];
      destinations[2] = world[ISHTARR_CENTRAL_TOWER];
      destinations[3] = world[ISHTARR_DUNGEON];
      break;
    case ISHTARR_CENTRAL_TOWER:
      destinations[0] = world[ISHTARR_ENTRANCE];
      destinations[1] = world[ISHTARR_EAST_WING];
      destinations[2] = world[ISHTARR_WEST_WING];
      destinations[3] = world[ISHTARR_DUNGEON];
      break;
    case ISHTARR_DUNGEON:
      destinations[0] = world[ISHTARR_ENTRANCE];
      destinations[1] = world[ISHTARR_EAST_WING];
      destinations[2] = world[ISHTARR_WEST_WING];
      destinations[3] = world[ISHTARR_CENTRAL_TOWER];
      break;
    case SHORE_NE:
      destinations[0] = world[MOUNTAINS];
      destinations[1] = world[BRILL_OUTSKIRTS];
      destinations[2] = world[OCEAN_SURFACE];
      break;
    case SHORE_EAST:
      destinations[0] = world[ILLARUM_ENTRANCE];
      destinations[1] = world[PLAINS_NORTH];
      destinations[2] = world[BRILL_OUTSKIRTS];
      destinations[3] = world[PLAINS_SOUTH];
      destinations[4] = world[VENTARRIS_ENTRANCE];
      destinations[5] = world[OCEAN_SURFACE];
      break;
    case SHORE_SE:
      destinations[0] = world[VENTARRIS_ENTRANCE];
      destinations[1] = world[PLAINS_SOUTH];
      destinations[2] = world[OCEAN_SURFACE];
      break;
    case OCEAN_SURFACE:
      destinations[0] = world[SHORE_NE];
      destinations[1] = world[BRILL_DOCKS];
      destinations[2] = world[SHORE_EAST];
      destinations[3] = world[SHORE_SE];
      destinations[4] = world[VENTARRIS_DOCKS];
      destinations[5] = world[OCEAN_SHALLOW];
      break;
    case OCEAN_SHALLOW:
      destinations[0] = world[OCEAN_SURFACE];
      destinations[1] = world[OCEAN_DEEP];
      break;
    case OCEAN_DEEP:
      destinations[0] = world[OCEAN_SHALLOW];
      destinations[1] = world[OCEAN_TRENCH];
      destinations[2] = world[QUELACENTUS_ENTRANCE];
      break;
    case OCEAN_TRENCH:
      destinations[0] = world[OCEAN_DEEP];
      destinations[1] = world[QUELACENTUS_ENTRANCE];
      break;
    case QUELACENTUS_ENTRANCE:
      destinations[0] = world[QUELACENTUS_PLAZA];
      destinations[1] = world[QUELACENTUS_TEMPLE];
      destinations[2] = world[QUELACENTUS_PALACE];
      destinations[3] = world[OCEAN_DEEP];
      destinations[4] = world[OCEAN_TRENCH];
      break;
    case QUELACENTUS_PLAZA:
      destinations[0] = world[QUELACENTUS_ENTRANCE];
      destinations[1] = world[QUELACENTUS_TEMPLE];
      destinations[2] = world[QUELACENTUS_PALACE];
      break;
    case QUELACENTUS_TEMPLE:
      destinations[0] = world[QUELACENTUS_ENTRANCE];
      destinations[1] = world[QUELACENTUS_PLAZA];
      destinations[2] = world[QUELACENTUS_PALACE];
      break;
    case QUELACENTUS_PALACE:
      destinations[0] = world[QUELACENTUS_ENTRANCE];
      destinations[1] = world[QUELACENTUS_PLAZA];
      destinations[2] = world[QUELACENTUS_TEMPLE];
      break;
    default:
#if DEBUG
      PRINT_ERROR_MESSAGE;
#endif
      break;
  }

    /* List the available destinations; player chooses one by number. */
  printf("Where would you like to go?\n");
  for (i = 0; i < MAX_DESTINATIONS && destinations[i] != NULL; i++) {
    printf("[%d] %s\n", i + 1, destinations[i]->name);
  }
  GetIntInput(&iInput, 1, i);

  return MovePlayer(destinations[iInput - 1]->ID);
}

/******************************************************************************
   Function: MovePlayer

Description: Handles the movement of the player character from one location to
             another.

     Inputs: destinationID - ID of the desired destination.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int MovePlayer(int destinationID) {
  game_character_t *companion;

  if (destinationID < 0 || destinationID >= NUM_LOCATION_IDS) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  player.locationID = destinationID;
  if (player.summonedCreature != NULL) {
    player.summonedCreature->locationID = destinationID;
  }
  if (player.next != NULL) {
    for (companion = player.next;
         companion != NULL;
         companion = companion->next) {
      companion->locationID = destinationID;
    }
  }

  return SUCCESS;
}

/******************************************************************************
   Function: SearchLocation

Description: Determines the outcome of a given search.

     Inputs: location - The location being searched.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int SearchLocation(location_t *location) {
  int temp;
  char output[LONG_STR_LEN + 1] = "";

  if (location == NULL) {
#if DEBUG
    PRINT_ERROR_MESSAGE;
#endif
    return FAILURE;
  }

  location->searches++;
  switch (location->ID) {
    case FOREST:
      temp = RandomInt(1, 5);
      if (temp == 1) {
        sprintf(output, "You have discovered the Druids' Grove!");
        MovePlayer(DRUIDS_GROVE);
        break;
      } else if (temp == 2) {
        AddItem(&player, GLOWING_MUSHROOM);
        break;
      }
      /* Otherwise, fall through. */
    default:
      switch (RandomInt(1, 5)) {
        case 1:
          temp = RandomInt(1, 20);
          sprintf(output,
                  "You find a small bag holding %d gold coins.",
                  temp);
          player.gold += temp;
          break;
        case 2:
          sprintf(output,
                  "You find a healing potion.",
                  temp);
          player.inventory[HEALING_POTION]++;
          break;
        case 3:
          if (AddRandomEnemy(world[player.locationID]) == SUCCESS) {
            sprintf(output,
                    "While searching, you're attacked by %s!",
                    GetNameIndefinite(enemyNPCs[0]));
            break;
          }
          /* Fall through if no random enemy appeared. */
        default:
          sprintf(output, "You find nothing of consequence.");
          break;
      }
      break;
  }
  PrintString(output);
  FlushInput();
  if (enemyNPCs[0] != NULL) {
    Combat();
  }

  return SUCCESS;
}

/******************************************************************************
   Function: DescribeSituation

Description: Describes the current location and its inhabitants to the player.
             Also initiates combat if hostile enemies are present.

     Inputs: None.

    Outputs: None.
******************************************************************************/
void DescribeSituation(void) {
  int i, temp, gcTypesDescribed;
  char output[LONG_STR_LEN + 1] = "";
  game_character_t *pGC;

    /* Describue the current location. */
  switch (player.locationID)
  {
    case ILLARUM_SCHOOL:
      if (world[ILLARUM_SCHOOL]->visits == 0) {  /* Indicates a new game. */
        world[ILLARUM_SCHOOL]->visits++;
        sprintf(output,
                "%s, Archwizard of the School of the Elements, approaches to "
                "speak with you.",
                FindInhabitant(ARCHWIZARD_OF_ELEMENTS)->name);
        PrintString(output);
        FlushInput();
        Dialogue(FindInhabitant(ARCHWIZARD_OF_ELEMENTS));
        return;
      } else {
        sprintf(output,
                "You are in the School of the Elements in the city of Illarum."
                " ");
      }
      break;
    case ILLARUM_ENTRANCE:
      sprintf(output, "You are at the main gate of the city of Illarum. ");
      break;
    case ILLARUM_MARKET:
      sprintf(output, "You are in the marketplace of the city of Illarum. ");
      break;
    case ILLARUM_INN:
      sprintf(output, "You are at an inn in the city of Illarum. ");
      break;
    case ILLARUM_TEMPLE:
      sprintf(output, "You are in the Illarum Temple. ");
      break;
    case ILLARUM_PALACE:
      sprintf(output, "You are in the palace of the King of Illarum. ");
      break;
    case ILLARUM_PRISON:
      sprintf(output, "You are in the Illarum prison. ");
      break;
    case VENTARRIS_ENTRANCE:
      sprintf(output, "You are at the main gate of the city of Ventarris. ");
      break;
    case VENTARRIS_MARKET:
      sprintf(output, "You are in the marketplace of the city of Ventarris. ");
      break;
    case VENTARRIS_INN:
      sprintf(output, "You are at an inn in the city of Ventarris. ");
      break;
    case VENTARRIS_SCHOOL:
      sprintf(output,
              "You are in the School of Mind in the city of Ventarris. ");
      break;
    case VENTARRIS_TEMPLE:
      sprintf(output, "You are in the Ventarris Temple. ");
      break;
    case VENTARRIS_PALACE:
      sprintf(output, "You are in the palace of the King of Ventarris. ");
      break;
    case VENTARRIS_PRISON:
      sprintf(output, "You are in the Ventarris prison. ");
      break;
    case VENTARRIS_DOCKS:
      sprintf(output, "You are at the docks of the city of Ventarris. ");
      break;
    case PLAINS_NORTH:
      sprintf(output, "You are in the northern plains. ");
      break;
    case NORTHERN_FARMS:
      sprintf(output, "You are in the northern farmlands. ");
      break;
    case BRILL_OUTSKIRTS:
      sprintf(output, "You are in the outskirts of the village of Brill. ");
      break;
    case BRILL_MARKET:
      sprintf(output, "You are in the marketplace of the village of Brill. ");
      break;
    case BRILL_INN:
      sprintf(output, "You are at an inn in the village of Brill. ");
      break;
    case BRILL_DOCKS:
      sprintf(output, "You are at the docks of the village of Brill. ");
      break;
    case PLAINS_SOUTH:
      sprintf(output, "You are in the southern plains. ");
      break;
    case SOUTHERN_FARMS:
      sprintf(output, "You are in the southern farmlands. ");
      break;
    case SILENT_SAGE_HOME:
      sprintf(output,
              "You are at a simple, solitary home in the middle of the "
              "southern plains. ");
      break;
    case FOREST:
      sprintf(output, "You are in the western woods. ");
      break;
    case DRUIDS_GROVE:
      sprintf(output, "You are in the Druids' Grove of the western woods. ");
      break;
    case HERMIT_HUT:
      sprintf(output, "You are at a solitary hut deep in the western woods. ");
      break;
    case WYNNFAER_ENTRANCE:
      sprintf(output, "You are at the main gate of the city of Wynnfaer. ");
      break;
    case WYNNFAER_PLAZA:
      sprintf(output,
              "You are in the central plaza of the city of Wynnfaer. ");
      break;
    case WYNNFAER_PALACE:
      sprintf(output, "You are in the palace of the city of Wynnfaer. ");
      break;
    case MOUNTAINS:
      sprintf(output, "You are in the northern mountains. ");
      break;
    case GESHTAL:
      sprintf(output, "You are in the barbarian village of Gesh'tal. ");
      break;
    case TORR_ENTRANCE:
      sprintf(output,
              "You are at the entrance to the underground city of Torr. ");
      break;
    case TORR_MARKET:
      sprintf(output, "You are in the marketplace of the city of Torr. ");
      break;
    case TORR_SCHOOL:
      sprintf(output, "You are in the school of the city of Torr. ");
      break;
    case TORR_TEMPLE:
      sprintf(output, "You are in the temple of the city of Torr. ");
      break;
    case TORR_THRONE_ROOM:
      sprintf(output, "You are in the throne room of the King of Torr. ");
      break;
    case TORR_MINE:
      sprintf(output, "You are in the mines of Torr. ");
      break;
    case TORR_VAULT:
      sprintf(output, "You are in a secret vault in the city of Torr. ");
      break;
    case TORR_PRISON:
      sprintf(output, "You are in the prison of the city of Torr. ");
      break;
    case GUGGENHOLM_ENTRANCE:
      sprintf(output,
              "You are at the entrance to the underground city of Guggenholm."
              " ");
      break;
    case GUGGENHOLM_MAIN:
      sprintf(output, "You are in the main hall of Guggenholm. ");
      break;
    case GUGGENHOLM_MINE:
      sprintf(output, "You are in the mines of Guggenholm. ");
      break;
    case SWAMP:
      sprintf(output, "You are in the southwestern swamplands. ");
      break;
    case NECROMANCERS_CIRCLE:
      sprintf(output, "You are deep in the southwestern swamplands. ");
      break;
    case ISHTARR_ENTRANCE:
      sprintf(output,
              "You are at the main gate of the dark citadel of Ishtarr. ");
      break;
    case ISHTARR_EAST_WING:
      sprintf(output, "You are in the east wing of Ishtarr. ");
      break;
    case ISHTARR_WEST_WING:
      sprintf(output, "You are in the west wing of Ishtarr. ");
      break;
    case ISHTARR_CENTRAL_TOWER:
      sprintf(output, "You are in the central tower of Ishtarr. ");
      break;
    case ISHTARR_DUNGEON:
      sprintf(output, "You are in the dungeon of Ishtarr. ");
      break;
    case SHORE_NE:
      sprintf(output, "You are on the northeastern shore. ");
      break;
    case SHORE_EAST:
      sprintf(output, "You are on the eastern shore. ");
      break;
    case SHORE_SE:
      sprintf(output, "You are on the southeastern shore. ");
      break;
    case OCEAN_SURFACE:
      sprintf(output, "You are on the surface of the ocean. ");
      break;
    case OCEAN_SHALLOW:
      sprintf(output, "You are in the ocean at a relatively shallow depth. ");
      break;
    case OCEAN_DEEP:
      sprintf(output, "You are deep in the ocean. ");
      break;
    case OCEAN_TRENCH:
      sprintf(output, "You are in an oceanic trench. ");
      break;
    case QUELACENTUS_ENTRANCE:
      sprintf(output,
              "You are in the deep, dark waters just above the merfolk city of"
              " Quelacentus. ");
      break;
    case QUELACENTUS_PLAZA:
      sprintf(output, "You are in the central plaza of Quelacentus. ");
      break;
    case QUELACENTUS_TEMPLE:
      sprintf(output, "You are in the temple of Quelacentus. ");
      break;
    case QUELACENTUS_PALACE:
      sprintf(output, "You are in the palace of the Queen of Quelacentus. ");
      break;
    default:
#if DEBUG
      PRINT_ERROR_MESSAGE;
#endif
      break;
  }

    /* Describe local inhabitants (NPCs).                                    */
  UpdateVisibleGameCharCounter();
  gcTypesDescribed = 0;
  for (i = 0; i < NUM_GC_IDS; i++) {
    gcDescribed[i] = false;
  }
  temp = VisibleInhabitants(world[player.locationID]);
  if (temp > 0) {
    strcat(output, "You see ");
    for (pGC = world[player.locationID]->inhabitants;
         pGC != NULL;
         pGC = pGC->next) {
      if (pGC->status[INVISIBLE] == false && gcDescribed[pGC->ID] == false) {
        if (temp < VisibleInhabitants(world[player.locationID])) {
          if (temp <= visibleGameCharCounter[pGC->ID]) {
            if (gcTypesDescribed > 1) {
              strcat(output, ",");
            }
            strcat(output, " and ");
          } else {
            strcat(output, ", ");
          }
        }
        if (visibleGameCharCounter[pGC->ID] == 1) {
          strcat(output, GetNameIndefinite(pGC));
        } else {
          sprintf(output + strlen(output),
                  "%d %s",
                  visibleGameCharCounter[pGC->ID],
                  GetNamePlural(pGC));
        }
        gcTypesDescribed++;
        gcDescribed[pGC->ID] = true;
        temp -= visibleGameCharCounter[pGC->ID];
        if (temp <= 0) {
          strcat(output, ". ");
        }
      }
    }
  }
  PrintString(output);
  FlushInput();

    /* Check for hostile enemies. If any exist, they immediately attack.     */
  for (pGC = world[player.locationID]->inhabitants;
       pGC != NULL;
       pGC = pGC->next) {
    if (pGC->relationship <= HOSTILE_ENEMY) {
      AddEnemy(pGC);
    }
  }
  if (NumberOfEnemies() > 0) {
    printf("\nYou are being attacked!\n");
    FlushInput();
    Combat();
    if (worldExists) {
      DescribeSituation();
    }
  }
}
