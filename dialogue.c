/******************************************************************************
   Filename: dialogue.c

     Author: David C. Drake (www.davidcdrake.com)

Description: Functions governing dialogue for the text-based fantasy RPG "Words
             of Power."
******************************************************************************/

#include "wop.h"

/******************************************************************************
   Function: TalkMenu

Description: Takes the player through the process of selecting a game character
             with whom to speak.

     Inputs: None.

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int TalkMenu(void) {
  int i, iInput, temp = 0;
  BOOL repeatOptions;
  GameCharacter *target;

  UpdateVisibleGameCharCounter();
  for (i = 0; i < TOTAL_GC_IDS; i++) {
    gcDescribed[i] = FALSE;
  }

    /* Potential targets are displayed (unless only one is available).       */
  if (VisibleInhabitants(world[player.locationID]) == 0) {
    PrintString("There is no one to speak with here.");
    FlushInput();
    return FAILURE;
  } else if (VisibleInhabitants(world[player.locationID]) == 1) {
    for (target = world[player.locationID]->inhabitants;
         target != NULL;
         target = target->next) {
      if (target->status[INVISIBLE] == FALSE) {
        return Dialogue(target);
      }
    }
  } else {  /* Multiple visible inhabitants to choose from. */
    PrintString("With whom do you wish to speak?");
    for (target = world[player.locationID]->inhabitants;
         target != NULL;
         target = target->next) {
      if (target->status[INVISIBLE] == FALSE &&
          gcDescribed[target->ID] == FALSE) {
        temp++;
        printf("[%d] %s", temp, Capitalize(GetNameIndefinite(target)));
        if (visibleGameCharCounter[target->ID] > 1) {
          printf(" (%d available)", visibleGameCharCounter[target->ID]);
        }
        printf("\n");
        gcDescribed[target->ID] = TRUE;
      }
    }
  }

    /* Player chooses a target by number. */
  GetIntInput(&iInput, 1, temp);

    /* The target is now found by matching it with the input. */
  temp = 0;
  for (i = 0; i < TOTAL_GC_IDS; i++) {
    gcDescribed[i] = FALSE;
  }

  for (target = world[player.locationID]->inhabitants;
       target != NULL;
       target = target->next) {
    if (target->status[INVISIBLE] == FALSE &&
        gcDescribed[target->ID] == FALSE) {
      temp++;
      if (temp == iInput) {
        return Dialogue(target);
      }
      gcDescribed[target->ID] = TRUE;
    }
  }

#if DEBUG
  ERROR_MESSAGE
#endif
  return FAILURE;
}

/******************************************************************************
   Function: Dialogue

Description: Presents dialogue text and options when the player interacts with
             a particular NPC.

     Inputs: pGC - A pointer to the GameCharacter struct of the NPC the player
                   is speaking with (or, in group dialogue, the main NPC).

    Outputs: SUCCESS or FAILURE.
******************************************************************************/
int Dialogue(GameCharacter *pGC) {
  int i, iInput;
  BOOL repeatOptions, canCommunicate;
  char output[LONG_STR_LEN + 1] = "";

  if (pGC == NULL) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

    /* Check for language compatibility. */
  canCommunicate = FALSE;
  for (i = 0; i < TOTAL_LANGUAGE_IDS; i++) {
    if (player.languages[i] == KNOWN && pGC->languages[i] == KNOWN) {
      canCommunicate = TRUE;
      break;
    }
  }
  if (canCommunicate == FALSE) {
    sprintf(output,
            "All your attempts at communication have failed. It appears that "
            "you and %s do not share a common language.",
            GetNameDefinite(pGC));
    PrintString(output);
    FlushInput();
    return SUCCESS; /* Although they can't talk, no error has occurred. */
  }

  pGC->conversations++;
  if (pGC->ID == MERCHANT || pGC->ID == DWARF_MERCHANT) {
    MerchantDialogue(pGC);
  }
  switch (pGC->ID) {
    case ARCHWIZARD_OF_ELEMENTS:
      if (pGC->conversations == 1) {  /* Indicates new game: offer tutorial. */
        sprintf(output,
                "%s: \"Good morning, %s, and congratulations!\"",
                AllCaps(pGC->name),
                player.name);
        PrintString(output);
        FlushInput();
        sprintf(output,
                "%s: \"You have mastered the art of projecting your will "
                "through the four elemental Words of Power -- the Words of "
                "Air, Water, Earth, and Fire -- and demonstrated great "
                "potential as a mage.\"",
                AllCaps(pGC->name));
        PrintString(output);
        FlushInput();
        sprintf(output,
                "%s: \"As such, I have decided not only to declare you a "
                "graduate of the School of the Elements, but also to offer you"
                " employment as an agent of the Elemental Wizards' Guild. In "
                "fact, I already have a task in mind for you. Before "
                "discussing the details, however, would you like an "
                "opportunity to demonstrate your skills once again for the "
                "newer students?\"\n",
                AllCaps(pGC->name));
        allegiances[ELEMENTS_GUILD] = GOOD_FRIEND;
        PrintString(output);
        printf("[1] \"Of course!\"  (Enter tutorial.)\n"
               "[2] \"No, thanks.\" (Skip tutorial.)\n");
        GetIntInput(&iInput, 1, 2);
        switch (iInput) {
          case 1:
            sprintf(output,
                    "%s: \"Excellent! Destroy this stuffed dummy with a "
                    "simple, one-Word spell.\"",
                    AllCaps(pGC->name));
            PrintString(output);
            FlushInput();
            AddEnemy(AddInhabitant(world[player.locationID], DUMMY));
            Combat();
            sprintf(output,
                    "%s: \"Well done! We'll set up another dummy. This time, "
                    "speak two or more Words in succession. Remember, this can"
                    " be harmful to the spellcaster, so be cautious! We will "
                    "heal you if necessary while you are practicing in our "
                    "school, but elsewhere you'll have no such protection.\"",
                    AllCaps(pGC->name));
            PrintString(output);
            FlushInput();
            AddEnemy(AddInhabitant(world[player.locationID], DUMMY));
            Combat();
            sprintf(output,
                    "%s: \"Fantastic! It's gratifying to see the progress "
                    "you've made. But now, let us discuss the work I have in "
                    "mind for you...\"",
                    AllCaps(pGC->name));
            PrintString(output);
            FlushInput();
            /*while (FindInhabitant(DUMMY) != NULL) {
              DeleteInhabitant(world[player.locationID],
                               FindInhabitant(DUMMY));
            }*/
            player.currentHP = player.maxHP;
            /* Fall through. */
          default:
            sprintf(output,
                    "%s: \"Your first task is quite simple. Go to the western "
                    "woods and return with at least ten glowing mushrooms. I "
                    "need them for one of my research projects. You may "
                    "encounter wild beasts while snooping around, but you "
                    "should be more than a match for them!\"",
                    AllCaps(pGC->name));
            PrintString(output);
            FlushInput();
            missions[ELEMENTS1] = OPEN;
            break;
        }
      } else if (missions[ELEMENTS1] == OPEN) {
        sprintf(output,
                "%s: \"Do you have those mushroom samples I asked for?\"\n"
                "[1] \"Yes.\"\n"
                "[2] \"No.\"",
                AllCaps(pGC->name));
        PrintString(output);
        GetIntInput(&iInput, 1, 2);
        switch (iInput) {
          case 1:
            if (player.inventory[GLOWING_MUSHROOM] >= 10) {
              sprintf(output,
                      "%s: \"Excellent! I knew I could count on you. Here's 20"
                      " gold to compensate you for your time.\"",
                      AllCaps(pGC->name));
              PrintString(output);
              FlushInput();
              missions[ELEMENTS1] = COMPLETED;
              player.inventory[GLOWING_MUSHROOM] -= 10;
              GiveGold(pGC, &player, 20);
              pGC->relationship++;
              GainExperience(STD_MISSION_EXP);
            } else {
              sprintf(output,
                      "%s: \"No you don't. If this is a joke, it isn't funny. "
                      "Return when you have those ten samples!\"",
                      AllCaps(pGC->name));
              if (pGC->relationship > INDIFFERENT) {
                pGC->relationship--;
              }
            }
            break;
          default:
            sprintf(output,
                    "%s: \"Please collect them for me as soon as possible.\"",
                    AllCaps(pGC->name));
            PrintString(output);
            FlushInput();
            break;
        }
      } else if (missions[ELEMENTS2] == OPEN) {
        sprintf(output,
                "%s: \"Why haven't you delivered those goods to the druids "
                "yet, %s? Please hurry or I will not trust you with any more "
                "errands.\"",
                AllCaps(pGC->name),
                player.name);
        PrintString(output);
        FlushInput();
      } else if (missions[ELEMENTS2] == COMPLETED) {
        sprintf(output,
                "%s: \"Thank you for delivering those goods to the druids, %s!"
                "Our relationship with them is crucial to Illarum's future.\"",
                AllCaps(pGC->name),
                player.name);
        PrintString(output);
        FlushInput();
      } else {
        sprintf(output,
                "%s: \"Welcome back, %s! Tell me of your travels...\"\n",
                AllCaps(pGC->name),
                player.name);
        PrintString(output);
        FlushInput();
      }
      break;
    case DRUID:
      sprintf(output,
              "%s: \"Greetings, friend! Nature's blessings upon you.\"\n"
              "[1] \"Nature's blessings upon you as well.\"\n"
              "[2] \"Can you teach me a new language?\"\n"
              "[3] \"Can you teach me a new Word of Power?\"",
              AllCaps(pGC->name));
      PrintString(output);
      GetIntInput(&iInput, 1, 3);
      if (iInput == 2) {
        LanguageLearningDialogue(pGC);
      } else if (iInput == 3) {
        WordLearningDialogue(pGC);
      }
      break;
    case ARCHDRUID:
      if (missions[ELEMENTS1] == OPEN) {
        sprintf(output,
                "%s: \"Greetings, friend. You wear the garb of a Wizard of the"
                " Elements. Do you bear goods from the Archwizard?\"\n"
                "[1] \"Yes, he asked me to bring this food to you.\"\n"
                "[2] \"No, I'm afraid I don't.\"",
                AllCaps(pGC->name));
        PrintString(output);
        GetIntInput(&iInput, 1, 2);
        switch (iInput) {
          case 1:
            if (player.inventory[FOOD] > 0) {
              if (player.inventory[FOOD] < 5) {
                sprintf(output,
                        "%s: \"Hm. This is less than we were promised, but we "
                        "will get by. Be sure to thank the Archwizard for me, "
                        "will you?\"",
                        AllCaps(pGC->name));
                PrintString(output);
                FlushInput();
                pGC->inventory[FOOD] += player.inventory[FOOD];
                player.inventory[FOOD] = 0;
              } else {
                sprintf(output,
                        "%s: \"Wonderful! It is just as we were promised. Be "
                        "sure to thank the Archwizard for me, will you?\"",
                        AllCaps(pGC->name));
                PrintString(output);
                FlushInput();
                pGC->inventory[FOOD] += 5;
                player.inventory[FOOD] -= 5;
              }
              missions[ELEMENTS1] = COMPLETED;
            } else {
              printf(output,
                     "%s: \"Yet you bring us no food. Please return once you "
                     "have the promised supplies.\"",
                     AllCaps(pGC->name));
              PrintString(output);
              FlushInput();
            }
            break;
          default:
            sprintf(output,
                    "%s: \"I see. I hope the shipment will not be delayed much"
                    " longer. We are usually able to live off the land, but "
                    "this year has proven extraordinarily difficult. If you "
                    "get a chance, please remind the Archwizard of our "
                    "predicament.\"",
                    AllCaps(pGC->name));
            PrintString(output);
            FlushInput();
            break;
        }
      } else {
        sprintf(output,
                "%s: \"Greetings, friend.\"\n",
                AllCaps(pGC->name));
        PrintString(output);
        FlushInput();
      }
      break;
    default:
      switch (RandomInt(1, 14)) {
        case 1:
          sprintf(output,
                  "%s: \"Ever heard of the Lonely Fisherman, otherwise known "
                  "as the Angler? They say he frequents the docks at Brill, "
                  "just fishing and staring at the sea. You wouldn't know it "
                  "to look at him, but he's one of the most powerful wizards "
                  "in the world!\"",
                  AllCaps(pGC->name));
          break;
        case 2:
          sprintf(output,
                  "%s: \"You want my advice? Stay away from the southwestern "
                  "swamplands...unless you've got a death wish, that is. Not "
                  "only is it a known refuge for necromancers and other evil "
                  "wizards, but deep within the swamp lies the dark citadel of"
                  " a powerful lich and his undead minions.\"",
                  AllCaps(pGC->name));
          break;
        case 3:
          sprintf(output,
                  "%s: \"A powerful druid known as the Hermit lives alone deep"
                  " in the western woodlands. He doesn't usually take kindly "
                  "to strangers, but if you're a friend of the druids he may "
                  "be willing to teach you a thing or two.\"",
                  AllCaps(pGC->name));
          break;
        case 4:
          sprintf(output,
                  "%s: \"They say a wise and powerful monk has been wandering "
                  "the northern mountains in recent years. I wonder what he's "
                  "doing there...\"",
                  AllCaps(pGC->name));
          break;
        case 5:
          sprintf(output,
                  "%s: \"You heard of the Silent Sage? He lives in a solitary "
                  "house on the southern plains. Never speaks to anyone. Some "
                  "folks think he's deaf or mute. I don't know anything about "
                  "that, but I do know this: he's considered by some to be the"
                  " most powerful wizard in the world!\"",
                  AllCaps(pGC->name));
          break;
        case 6:
          sprintf(output,
                  "%s: \"The elves live in a place called Wynnfaer, deep "
                  "within the western woods. Don't bother trying to find it, "
                  "though: their magic will prevent you from ever getting "
                  "close!\"",
                  AllCaps(pGC->name));
          break;
        case 7:
          sprintf(output,
                  "%s: \"I hear the gnomes in the northern mountains are being"
                  " harassed by a dragon.\"",
                  AllCaps(pGC->name));
          break;
        case 8:
          sprintf(output,
                  "%s: \"Have you visited Gesh'tal? It's a barbarian village "
                  "in the northern mountains. Their chieftain is said to have "
                  "such a frightening battle cry that orcs and goblins fall "
                  "dead at his feet when they hear it!\"",
                  AllCaps(pGC->name));
          break;
        case 9:
          sprintf(output,
                  "%s: \"The dwarves have a stronghold up in the northern "
                  "mountains known as Torr. They say the dwarven loremasters "
                  "have hidden several rare tomes of arcane knowledge there "
                  "in a secret vault. I bet a wizard like you would love to "
                  "get your hands on some of those books!\"",
                  AllCaps(pGC->name));
          break;
        case 10:
          sprintf(output,
                  "%s: \"Some sailors and fisherman in these parts like to "
                  "tell tall tales about mermaids and such. They even claim "
                  "the merfolk live in a great city deep within the ocean to "
                  "the east of here. Ha!\"",
                  AllCaps(pGC->name));
          break;
        case 11:
          sprintf(output,
                  "%s: \"Make no mistake: both of the Archwizards in this "
                  "region have strong political ambitions, and neither of them"
                  " would make for a very benevelont ruler. My advice? Don't "
                  "get involved, or if you do, make sure you're on the winning"
                  " side.\"",
                  AllCaps(pGC->name));
          break;
        case 12:
          sprintf(output,
                  "%s: \"It's well known that the king of Ventarris wants to "
                  "conquer Illarum and expand his power throughout this "
                  "region. But did you know the lich of the southern swamp was"
                  " himself once a king of Ventarris? He also hopes to "
                  "dominate the region and reign once again as king.\"",
                  AllCaps(pGC->name));
          break;
        default:
          sprintf(output,
                  "%s: \"Sorry, I'm too busy to talk right now.\"",
                  AllCaps(pGC->name));
          break;
      }
      PrintString(output);
      FlushInput();
      break;
  }

  return SUCCESS;
}

/******************************************************************************
   Function: LanguageLearningDialogue

Description: Presents dialogue and options relevant to learning a language.

     Inputs: pGC - A pointer to the game character the player is speaking with.

    Outputs: SUCCESS if a language is learned, otherwise FAILURE.
******************************************************************************/
int LanguageLearningDialogue(GameCharacter *pGC) {
  int i, iInput, count = 0;  /* Number of languages available to be learned. */
  char output[LONG_STR_LEN + 1] = "";

  if (pGC == NULL) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  for (i = 0; i < TOTAL_LANGUAGE_IDS; i++) {
    if (pGC->languages[i] == KNOWN && player.languages[i] != KNOWN) {
      count++;
      if (count == 1) {
        sprintf(output,
                "%s: \"What language do you want to learn?\"",
                AllCaps(pGC->name));
      }
      sprintf(output + strlen(output),
              "\n[%d] %s",
              count,
              LanguageName(i));
    }
  }

  if (count > 0) {
    sprintf(output + strlen(output),
            "\n[%d] Cancel",
            ++count);
    PrintString(output);
    GetIntInput(&iInput, 1, count);
    count = 0;
    for (i = 0; i < TOTAL_LANGUAGE_IDS; i++) {
      if (pGC->languages[i] == KNOWN && player.languages[i] != KNOWN) {
        count++;
        if (iInput == count) {
          if (Transaction(pGC,
                          STD_LANG_FEE * GetPriceModifier(pGC)) == SUCCESS) {
            LearnLanguage(i);
            return SUCCESS;
          } else {
            break;
          }
        }
      }
    }
  } else {
    sprintf(output,
            "%s: \"You already know all the languages I can teach you.\"",
            AllCaps(pGC->name));
    PrintString(output);
    FlushInput();
  }

  return FAILURE;
}

/******************************************************************************
   Function: WordLearningDialogue

Description: Presents dialogue and options relevant to learning a Word of
             Power.

     Inputs: pGC - A pointer to the game character the player is speaking with.

    Outputs: SUCCESS if a Word is learned, otherwise FAILURE.
******************************************************************************/
int WordLearningDialogue(GameCharacter *pGC) {
  int i, iInput, count = 0;  /* Number of Words available to be learned. */
  char output[LONG_STR_LEN + 1] = "";

  if (pGC == NULL) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  for (i = 0; i < TOTAL_WORD_IDS; i++) {
    if (pGC->words[i] == KNOWN && player.words[i] != KNOWN) {
      count++;
      if (count == 1) {
        sprintf(output,
                "%s: \"I am willing to teach the following Words. Which one "
                "interests you?\"",
                AllCaps(pGC->name));
      }
      sprintf(output + strlen(output),
              "[%d] Word of %s\n",
              count,
              WordName(i));
    }
  }

  if (count > 0) {
    sprintf(output + strlen(output),
            "[%d] Cancel\n",
            ++count);
    PrintString(output);
    GetIntInput(&iInput, 1, count);
    count = 0;
    for (i = 0; i < TOTAL_WORD_IDS; i++) {
      if (pGC->words[i] == KNOWN && player.words[i] != KNOWN) {
        count++;
        if (iInput == count) {
          if (Transaction(pGC,
                          STD_WORD_FEE * GetPriceModifier(pGC)) == SUCCESS) {
            LearnWord(i);
            return SUCCESS;
          } else {
            break;
          }
        }
      }
    }
  } else {
    sprintf(output,
            "%s: \"You already know all the Words I'm willing to teach you.\"",
            AllCaps(pGC->name));
    PrintString(output);
    FlushInput();
  }

  return FAILURE;
}

/******************************************************************************
   Function: MerchantDialogue

Description: Presents dialogue and options relevant to buying and selling.

     Inputs: merchant - Pointer to the merchant NPC.

    Outputs: SUCCESS if a transaction is completed, otherwise FAILURE.
******************************************************************************/
int MerchantDialogue(GameCharacter *merchant)
{
  int i, iInput, count = 0;  /* No. of item types and/or options available. */
  char output[LONG_STR_LEN + 1] = "";

  if (merchant == NULL) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

    /* Present the merchant's inventory and other options to the player. */
  sprintf(output,
          "%s: \"What would you like to buy?\"\n",
          merchant->name);
  for (i = 0; i < TOTAL_ITEM_IDS; i++) {
    if (merchant->inventory[i] > 0) {
      count++;
      sprintf(output + strlen(output),
              "[%d] %s (%d gold)\n",
              count,
              GetItemName(i),
              ItemValue(i) * GetPriceModifier(merchant));
      if (merchant->inventory[i] >= 10) {
        count++;
        sprintf(output + strlen(output),
                "[%d] 10 %s (%d gold)",
                count,
                GetItemNamePlural(i),
                10 * (ItemValue(i) * GetPriceModifier(merchant)));
      }
    }
  }
  sprintf(output + strlen(output),
          "[%d] \"Actually, I'd like to sell something.\"\n"
          "[%d] \"Nothing for now, thank you.\"\n",
          ++count,
          ++count);

    /* Get input and determine what selection the player made. */
  GetIntInput(&iInput, 1, count);
  for (i = 0; i < TOTAL_ITEM_IDS; i++) {
    if (merchant->inventory[i] > 0) {
      count++;
      if (count == iInput) {
        if (Transaction(merchant,
                        ItemValue(i) * GetPriceModifier(merchant)) == SUCCESS) {
          GiveItem(merchant, &player, i);
          merchant->inventory[i]++;  /* Merchant's supply is infinite. */
          return SUCCESS;
        }
      }
      if (merchant->inventory[i] >= 10) {
        count++;
        if (count == iInput) {
          if (Transaction(merchant,
                          10 * (ItemValue(i) *
                                GetPriceModifier(merchant))) == SUCCESS) {
            GiveItems(merchant, &player, i, 10);
            merchant->inventory[i] += 10;  /* Merchant's supply is infinite. */
            return SUCCESS;
          }
        }
      }
    }
  }
  if (iInput == ++count) {
    /* Sell stuff. */
  }

  return FAILURE;
}

/******************************************************************************
   Function: GetPriceModifier

Description: Returns a floating point value for adjusting a price up or down
             based on the given merchant's relationship with the player.

     Inputs: merchant - Pointer to the seller of goods or services.

    Outputs: Floating point value that may be multiplied by a price to adjust
             the price up or down.
******************************************************************************/
double GetPriceModifier(GameCharacter *merchant) {
  if (merchant->relationship > INDIFFERENT) {
    return FRIEND_MODIFIER;
  } else if (merchant->relationship < INDIFFERENT) {
    return ENEMY_MODIFIER;
  }

  return 1.0;
}

/******************************************************************************
   Function: Transaction

Description: Presents dialogue and options relevant to completing a purchase.

     Inputs: merchant - Pointer to the seller of goods or services.
             price    - Amount of gold required to complete the transaction.

    Outputs: SUCCESS if a transaction is completed, otherwise FAILURE.
******************************************************************************/
int Transaction(GameCharacter *merchant, int price) {
  int iInput;

  if (merchant == NULL) {
#if DEBUG
    ERROR_MESSAGE
#endif
    return FAILURE;
  }

  printf("%s: \"That will cost %d gold. Do we have a deal?\"\n"
         "[1] \"Yes.\"\n"
         "[2] \"No.\"\n",
         merchant->name,
         price);
  GetIntInput(&iInput, 1, 2);
  if (iInput == 1) {
    if (player.gold < price) {
      printf("%s: \"It looks like you don't have enough gold.\"\n",
             merchant->name);
      FlushInput();
      return FAILURE;
    }
    GiveGold(&player, merchant, price);
    return SUCCESS;
  }
  printf("%s: \"Let me know if you change your mind!\"\n",
         merchant->name);
  FlushInput();

  return FAILURE;
}

/******************************************************************************
   Function: LanguageName

Description: Returns the name of a given language as a string (e.g., "Elvish").

     Inputs: idNum - ID of the desired language.

    Outputs: Pointer to the desired string.
******************************************************************************/
char *LanguageName(int idNum) {
  switch (idNum) {
    case IMPERIAL:
      return "Imperial";
    case ANCIENT_IMPERIAL:
      return "Ancient Imperial";
    case ELVISH:
      return "Elvish";
    case ANCIENT_ELVISH:
      return "Ancient Elvish";
    case DWARVISH:
      return "Dwarvish";
    case ANCIENT_DWARVISH:
      return "Ancient Dwarvish";
    case GNOMISH:
      return "Gnomish";
    case ANCIENT_GNOMISH:
      return "Ancient Gnomish";
    case MER:
      return "Mer";
    case ANCIENT_MER:
      return "Ancient Mer";
    case VENTARRI:
      return "Ventarri";
    case ANCIENT_VENTARRI:
      return "Ancient Ventarri";
    case GESH:
      return "Gesh";
    default:
      break;
  }

#if DEBUG
  ERROR_MESSAGE
#endif
  return NULL;
}
