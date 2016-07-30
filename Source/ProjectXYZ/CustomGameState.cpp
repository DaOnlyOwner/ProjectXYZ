// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"
#include "RockSpell.h"

ASpell* ACustomGameState::genSpell(ElementQueue &queue, bool selfcast, const APlayerCharacter& player)
{
   ASpell *spell = nullptr;

   if(selfcast) {
       if(queue.RemoveSingleSwap(SHIELD_ID, false))
       {
	   if(queue.Num() == 0) {
	       // dome shield
	   }
	   else {
	       // ward
	   }
       }
       else if(queue.RemoveSingleSwap(EARTH_ID, false))
       {
	   // earthquake
       }
       else if(queue.RemoveSingleSwap(LIGHTNING_ID, false))
       {
	  // lightning AoE
       }
       else if(queue.Find(WATER_ID) && queue.Find(COLD_ID))
       {
	   // shards AoE
       }
       else
       {
	   // AoE
       }
   }
   else
   {
       if(queue.RemoveSingleSwap(SHIELD_ID, false))
       {
	   if(queue.Num() == 0) {
	       // front shield
	   }
	   else if(queue.RemoveSingleSwap(EARTH_ID, false))
	   {
	       // Wall
	   }
	   else if(queue.RemoveSingleSwap(LIGHTNING_ID, false))
	   {
	       // lightning storm
	   }
	   else if(queue.Find(WATER_ID) && queue.Find(COLD_ID))
	   {
	       // ice push
	   }
	   else if(queue.Find(DEATH_ID) || queue.Find(LIFE_ID))
	   {
	       // mines
	   }
	   else
	   {
	       // elemental storm
	   }
       }
       else if(queue.RemoveSingleSwap(EARTH_ID, false))
       {
	   int size = 1;
	   ARockSpell *rockSpell;
	   
           size += queue.RemoveSwap(EARTH_ID);
	      
           rockSpell = static_cast<ARockSpell*>(GetWorld()->SpawnActor(ARockSpell::StaticClass()));
	   rockSpell->init(1, queue);
	   spell = static_cast<ASpell*>(rockSpell);
       }
       else if(queue.RemoveSingleSwap(LIGHTNING_ID, false))
       {
	  // lightning
       }
       else if(queue.Find(WATER_ID) && queue.Find(COLD_ID))
       {
	   // shards
       }
       else if(queue.Find(DEATH_ID) || queue.Find(LIFE_ID))
       {
	   // beam
       }
       else
       {
	   // spray
       }
   }

   return spell;
}

