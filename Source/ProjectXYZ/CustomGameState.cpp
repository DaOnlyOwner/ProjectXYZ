// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"

// I might replace that with a better working solution. Right now its just too ugly
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
	   // shards
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
	       // wall
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
	   // rock
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

