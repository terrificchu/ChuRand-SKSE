#include "common/IDebugLog.h"  // IDebugLog
#include "skse64_common/skse_version.h"  // RUNTIME_VERSION
#include "skse64/PluginAPI.h"  // SKSEInterface, PluginInfo

#include <ShlObj.h>  // CSIDL_MYDOCUMENTS
#include <chrono>
#include <random>
#include <numeric>
#include <array>
#include <algorithm>
#include "skse64/PapyrusModEvent.h"
#include "version.h"  // VERSION_VERSTRING, VERSION_MAJOR

#include "skse64/PapyrusVM.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PapyrusLeveledActor.h"
#include "skse64/PapyrusLeveledItem.h"
#include "skse64/PapyrusWornObject.h"
#include "skse64/GameObjects.h"
#include "skse64/PapyrusCell.h"
#include "skse64/GameForms.h"
#include "skse64/GameReferences.h"
#include "skse64/PapyrusGameData.h"
#include "skse64/PapyrusDelayFunctors.h"
#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"
#include "skse64/GameForms.h"
#include "skse64/GameObjects.h"
#include "skse64/GameReferences.h"
#include "skse64/GameExtraData.h"

#include "skse64/PapyrusEvents.h"
#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusEventFunctor.h"
#include "skse64/PluginManager.h"
#include "common/IDirectoryIterator.h"
#include "skse64/GameAPI.h"
#include "skse64_common/Utilities.h"
#include "skse64/Serialization.h"
#include "skse64_common/skse_version.h"
#include "skse64/PapyrusEnchantment.h"
#include "skse64/GameEvents.h"
#include <set>
#include "chu-rand/lib/EventFunctors.h"
#include "chu-rand/lib/EventHelpers.h"
#include "chu-rand/lib/EventFunctors.h"
#include "skse64/GameFormComponents.h"
#include "skse64/PapyrusMagicEffect.h"


static SKSEPapyrusInterface         * g_papyrus = NULL;
extern EventDispatcher<SKSEModCallbackEvent>	g_modCallbackEventDispatcher;
namespace chutools
{
	
	UInt32 randintrange(int lwlim, int uplim)
	{
		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_int_distribution<int> distribution(lwlim, uplim);
		int rm = distribution(generator);
		return rm;
	}
	TESForm * randformofsametype(TESForm * tomatch)
	{
		DataHandler * dataHandler = DataHandler::GetSingleton();
		int reftype = tomatch->formType;

		if (reftype == 27)
		{
			int size = dataHandler->books.count - 1;
			
			int r1 = randintrange(0, size);
			TESObjectBOOK * refToPlace = NULL;
			dataHandler->books.GetNthItem(r1, refToPlace);
			if (refToPlace != NULL)
			{
				return DYNAMIC_CAST(refToPlace, TESObjectBOOK, TESForm);
				
			}

		}
		else if (reftype == 26)
		{
			int size = dataHandler->armors.count - 1;

			int r1 = randintrange(0, size);
			TESObjectARMO * refToPlace = NULL;
			dataHandler->armors.GetNthItem(r1, refToPlace);
			if (refToPlace != NULL)
			{

				return DYNAMIC_CAST(refToPlace, TESObjectARMO, TESForm);


			}
		}
		else if (reftype == 41)
		{
			int size = dataHandler->weapons.count - 1;
			int r1 = randintrange(0, size);
			TESObjectWEAP* refToPlace = NULL;
			dataHandler->weapons.GetNthItem(r1, refToPlace);
			if (refToPlace != NULL)
			{

				return DYNAMIC_CAST(refToPlace, TESObjectWEAP, TESForm);
				
			}
		}
		else if (reftype == 30)
		{
			
			int size = dataHandler->ingredients.count - 1;
			
			int r1 = randintrange(0, size);
			IngredientItem* refToPlace = NULL;
			while (dataHandler->ingredients.GetNthItem(r1, refToPlace) == NULL)
			{
				r1 = r1 = randintrange(0, size);
				dataHandler->ingredients.GetNthItem(r1, refToPlace);
			}
			if (refToPlace != NULL)
			{
				return DYNAMIC_CAST(refToPlace, IngredientItem, TESForm);
				
			}
		}
		else if (reftype == 32)
		{
			
			int size = dataHandler->miscObjects.count - 1;
			int r1sub = std::rand() % 10;
			
			int r1 = 1;
			int tsize = size - 966;
			if (r1sub < 5)
			{
				r1 = randintrange(1, 427);
			}
			else if (r1sub > 5)
			{
				r1 = randintrange(967, size);
			}
			TESObjectMISC* refToPlace = NULL;
			dataHandler->miscObjects.GetNthItem(r1, refToPlace);
			if (refToPlace != NULL)
			{

				return DYNAMIC_CAST(refToPlace, TESObjectMISC, TESForm);
				
			}
		}
		else if (reftype == 46)
		{
			
			int size = dataHandler->potions.count - 1;
			
			int r1 = randintrange(0, size);
			AlchemyItem* refToPlace = NULL;
			while (dataHandler->potions.GetNthItem(r1, refToPlace) == NULL)
			{
				int r1 = randintrange(0, size);
				dataHandler->potions.GetNthItem(r1, refToPlace);
			}
			if (refToPlace != NULL)
			{

				return DYNAMIC_CAST(refToPlace, AlchemyItem, TESForm);
				
			}
		}
		else if (reftype == 40)
		{
			
			int size = dataHandler->arrFURN.count - 1;
			
			int r1 = randintrange(0, size);
			TESFurniture* refToPlace = NULL;
			while (dataHandler->arrFURN.GetNthItem(r1, refToPlace) == NULL)
			{
				int r1 = randintrange(0, size);
				dataHandler->arrFURN.GetNthItem(r1, refToPlace);
			}
			if (refToPlace != NULL)
			{

				return DYNAMIC_CAST(refToPlace, TESFurniture, TESForm);
				
				
			}
		}
		else if (reftype == 43)
		{
			
			int size = dataHandler->npcs.count - 1;
			
			int r1 = randintrange(0, size);
			TESNPC * refToPlace = NULL;
			while (dataHandler->npcs.GetNthItem(r1, refToPlace) == NULL)
			{
				int r1 = randintrange(0, size);
				dataHandler->npcs.GetNthItem(r1, refToPlace);
			}
			if (refToPlace != NULL)
			{

				return DYNAMIC_CAST(refToPlace, TESNPC, TESForm);

				
			}
		}
		else if (reftype == 61)
		{
		  //TODO
		  return tomatch;
		}
		else if (reftype == 28)
		{

			
			int size = dataHandler->arrCONT.count - 1;
			
			int r1 = randintrange(0, size);
			TESObjectCONT* refToPlace = NULL;
			while (dataHandler->arrCONT.GetNthItem(r1, refToPlace) == NULL)
			{
				int r1 = randintrange(0, size);
				dataHandler->arrCONT.GetNthItem(r1, refToPlace);
			}
			if (refToPlace != NULL)
			{

				return DYNAMIC_CAST(refToPlace, TESObjectCONT, TESForm);

			}
		}
		else if (reftype == 53)
		{


			int size = dataHandler->arrLVLI.count - 1;

			int r1 = randintrange(0, size);
			TESForm* refToPlace = NULL;
			while (dataHandler->arrLVLI.GetNthItem(r1, refToPlace) == NULL)
			{
				int r1 = randintrange(0, size);
				dataHandler->arrLVLI.GetNthItem(r1, refToPlace);
			}
			if (refToPlace != NULL)
			{

				return refToPlace;
	
			}
		}
		else if (reftype == 44)
			{
			int size = dataHandler->arrLVLN.count - 1;

			int r1 = randintrange(0, size);
			TESForm* refToPlace = NULL;
			while (dataHandler->arrLVLN.GetNthItem(r1, refToPlace) == NULL)
			{
				int r1 = randintrange(0, size);
				dataHandler->arrLVLN.GetNthItem(r1, refToPlace);
			}
			if (refToPlace != NULL)
			{

				return refToPlace;

			}
			}
		else
		{
			_MESSAGE("REF TYPE NOT SUPPORTED YET");
			return tomatch;
		}
	}
	void distributeformlist(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, BGSListForm * list, VMArray<TESLevItem*> forms)
	{
		int progress = 0;
		TESLevItem * form3 = NULL;
		forms.Get(&form3, 39);
		
		
		if (list)
		{
			
			for (UInt32 i = 0; i < 38; i++)
			{
					TESLevItem * form2 = NULL;
					forms.Get(&form2, i);
					if (form2)
					{
						for (UInt32 k = 0; k < 250; k++)
						{
							if (progress > 9111)
							{
								i = 41;
								break;
							}
						
							
							int rm = randintrange(1, 3);
							int rmsub = 0;
							if (rm == 1)
							{
								
								rmsub = randintrange(0, 3228);
								
							}
							else if(rm == 2)
							{ 
								
								rmsub = randintrange(5230, 8668);
							
							}
							else if (rm == 3)
							{
								
								int rmsub2 = (1, 3);
								if (rmsub2 == 1)
								{
									
									rmsub = randintrange(8669, 9116);
								}
								else
								{
									
									rmsub = randintrange(3229, 5229);
								}
							}
							
							int r1 = randintrange(1, 25);
							
							int r2 = randintrange(1, 5);
							CALL_MEMBER_FN(&form2->leveledList, LAddForm)(&form2->leveledList, r1, r2, list->forms.entries[rmsub]);
							progress += 1;




						}
						CALL_MEMBER_FN(&form3->leveledList, LAddForm)(&form3->leveledList, 1, 1, form2);

					}
					
			}
		}
		
		DataHandler * dataHandler = DataHandler::GetSingleton();
		
		for (UInt32 i = 0; i < dataHandler->arrLVLI.count; i++)
		{
			bool matchform = false;
			TESForm * tempLVLIF = NULL;
			dataHandler->arrLVLI.GetNthItem(i, tempLVLIF);
			TESLeveledList * tempLVLI = DYNAMIC_CAST(tempLVLIF, TESForm, TESLeveledList);
			for (UInt32 p = 0; p < 39; p++)
			{
				TESLevItem * form2 = NULL;
				forms.Get(&form2, p);
				if (&form2->leveledList == tempLVLI)
				{
					matchform = true;
				}
			}
			if (matchform == false)
			{
				for (UInt32 k = 0; k < 1; k++)
				{
					if (tempLVLI->length > 250)
					{
						break;
					}
					else
					{
						CALL_MEMBER_FN(tempLVLI, LAddForm)(tempLVLI, 1, 1, DYNAMIC_CAST(form3, TESLevItem, TESForm));
					}
				}
			}
		}
	}
	void shufflelootlist(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, VMArray<TESLevItem*> forms, UInt32 logictype = 0)
	{
		DataHandler * dataHandler = DataHandler::GetSingleton();

		for (UInt32 i = 0; i < dataHandler->arrLVLI.count; i++)
		{
			bool matchform = false;
			TESForm * tempLVLIF = NULL;
			dataHandler->arrLVLI.GetNthItem(i, tempLVLIF);
			TESLevItem * tempLVLI = DYNAMIC_CAST(tempLVLIF, TESForm, TESLevItem);
			int lsize = tempLVLI->leveledList.length;
			for (UInt32 p = 0; p < 1; p++)
			{
				TESLevItem * form2 = NULL;
				forms.Get(&form2, p);
				if (form2 == tempLVLI)
				{
					matchform = true;
				}
			}
			if (matchform == false)
			{
				for (UInt32 k = 0; k < lsize; k++)
				{
					if (tempLVLI->leveledList.length > 250 || k > 250)
					{
						break;
					}
					else
					{
						if (tempLVLI->leveledList.entries[k].form)
						{

							TESForm * toadd = NULL;

							do {

								toadd = randformofsametype(tempLVLI->leveledList.entries[k].form);

							} while (!toadd  || toadd->formID == tempLVLIF->formID);
							switch (logictype) {
							case 0: {
									CALL_MEMBER_FN(&tempLVLI->leveledList, LAddForm)(&tempLVLI->leveledList, tempLVLI->leveledList.entries[k].level, tempLVLI->leveledList.entries[k].count, toadd);
									break;
							}
							case 1:
								if (toadd->formType == tempLVLIF->formType)
								{
									break;
								}
								else
								{
									CALL_MEMBER_FN(&tempLVLI->leveledList, LAddForm)(&tempLVLI->leveledList, tempLVLI->leveledList.entries[k].level, tempLVLI->leveledList.entries[k].count, toadd);
								}
								break;
							case 2: {
								int r1 = randintrange(1, 75);
								int r2 = randintrange(1, 5);
								CALL_MEMBER_FN(&tempLVLI->leveledList, LAddForm)(&tempLVLI->leveledList, r1, r2, toadd);
								break;
							}
							case 3:
								tempLVLI->leveledList.entries[k].form = toadd;
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
	void shuffleNPClist(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, BGSListForm * forms, BGSListForm * forms2, BGSListForm * forms3)
	{
		bool alogic = false;
		UInt32 fsize = (forms->forms.count - 1);
		UInt32 tsize = (forms2->forms.count - 1);
		for (UInt32 i = 0; i < fsize; i++)
		{
			
			bool matchform = false;
			TESForm * tempLVLNF = NULL;
			forms->forms.GetNthItem(i, tempLVLNF);
			if (tempLVLNF)
			{
				TESLevCharacter * tempLVLN = DYNAMIC_CAST(tempLVLNF, TESForm, TESLevCharacter);
				UInt8 * lsize = &tempLVLN->leveledList.length;
				
					for (UInt8 k = 0; k < *lsize; k++)
					{
						if (tempLVLN->leveledList.length > UInt8(250) || k > 250)
						{
						}
						else
						{
							if ((tempLVLN->leveledList.entries[k].form) && (tempLVLN->leveledList.entries[k].count))
							{
								if (alogic == true)
								{
									TESForm * toadd = NULL;

									do {
										int r3 = randintrange(0, tsize);
										forms2->forms.GetNthItem(0, toadd);

									} while (!toadd || toadd->formID == tempLVLN->formID);
									tempLVLN->leveledList.entries[k].form = toadd;
									
								}
								else
								{
									UInt32 tsize = (forms3->forms.count - 1);
									TESForm * toadd = NULL;

									do {
										int r3 = randintrange(0, tsize);
										forms3->forms.GetNthItem(r3, toadd);

									} while (!toadd || toadd->formID == tempLVLN->formID);
									tempLVLN->leveledList.entries[k].form = toadd;
								}
							}
							else
							{
							}
						}
					}
				
			}
		}
	}
	void shufflelootcont(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, UInt32 logictype = 0)
	{
		DataHandler * dataHandler = DataHandler::GetSingleton();

		for (UInt32 i = 0; i < dataHandler->arrCONT.count; i++)
		{
			bool matchform = false;
			TESObjectCONT * tempF = NULL;
			dataHandler->arrCONT.GetNthItem(i, tempF);
			int lsize = tempF->container.numEntries;
			
			for (UInt32 k = 0; k < lsize; k++)
				{
					if (tempF->container.numEntries > 250 || k > 250)
					{
						break;
					}
					else
					{
						if (tempF->container.entries[k]->form)
						{

							TESForm * toadd = NULL;

							do {

								toadd = randformofsametype(tempF->container.entries[k]->form);

							} while (!toadd);
							switch (logictype){
							case 0:
								tempF->container.entries[k]->form = toadd;
								break;
							case 1:
								//todo

								int r1 = randintrange(1, 75);
								int r2 = randintrange(1, 5);

							}

						}
						else
						{
							break;
						}
					}
				}
			
		}
		for (UInt32 i = 0; i < dataHandler->npcs.count; i++)
		{
			bool matchform = false;
			TESNPC * tempF = NULL;
			dataHandler->npcs.GetNthItem(i, tempF);
			int lsize = tempF->container.numEntries;

			for (UInt32 k = 0; k < lsize; k++)
			{
				if (tempF->container.numEntries > 250 || k > 250)
				{
					break;
				}
				else
				{
					if (tempF->container.entries[k]->form)
					{

						TESForm * toadd = NULL;

						do {

							toadd = randformofsametype(tempF->container.entries[k]->form);

						} while (!toadd);
						switch (logictype)
						{
						case 0:
							tempF->container.entries[k]->form = toadd;
							break;
						case 1:
							//todo
							int r1 = randintrange(1, 75);
							int r2 = randintrange(1, 5);

						}

					}
					else
					{
						break;
					}
				}
			}

		}
	}
	void shuffleench(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, UInt32 logictype = 0)
	{
		DataHandler * dataHandler = DataHandler::GetSingleton();
		if (logictype < 2)
		{ 
			for (UInt32 i = 0; i < dataHandler->enchantments.count; i++)
			{
				EnchantmentItem * toswap = NULL;
				EnchantmentItem * toreplace = NULL;
				dataHandler->enchantments.GetNthItem(i, toswap);
				int k = randintrange(0, (dataHandler->enchantments.count - 1));
				dataHandler->enchantments.GetNthItem(k, toreplace);
				if (toswap != nullptr && toreplace != nullptr)
				{
					int exit1 = papyrusEnchantment::GetNumEffects(toswap);
					int exit2 = papyrusEnchantment::GetNumEffects(toreplace);
					for (UInt32 j = 0; j < exit1; j++)
					{
						switch (logictype) {
						case 0:
						{
							int rindex = randintrange(0, (exit2 - 1));
							papyrusEnchantment::SetNthEffectArea(toswap, j, papyrusEnchantment::GetNthEffectArea(toreplace, rindex));
							papyrusEnchantment::SetNthEffectDuration(toswap, j, papyrusEnchantment::GetNthEffectDuration(toreplace, rindex));
							papyrusEnchantment::SetNthEffectMagnitude(toswap, j, papyrusEnchantment::GetNthEffectDuration(toreplace, rindex));
						}
						case 1:
						{
							int r1 = randintrange(0, 99);
							int r2 = randintrange(0, 99);
							int r3 = randintrange(0, 99);
							papyrusEnchantment::SetNthEffectArea(toswap, j, r1);
							papyrusEnchantment::SetNthEffectDuration(toswap, j, r2);
							papyrusEnchantment::SetNthEffectMagnitude(toswap, j, r3);
						}
						}



					}
				}
			}
		}
		else if(logictype == 2)
		{
			for (UInt32 i = 0; i < dataHandler->arrEffectSettings.count; i++) 
			{
				EffectSetting * toswap = NULL;
				EffectSetting * toreplace = NULL;
				dataHandler->arrEffectSettings.GetNthItem(i, toswap);
				int k = randintrange(0, (dataHandler->enchantments.count - 1));
				dataHandler->arrEffectSettings.GetNthItem(k, toreplace);
				if (toswap != nullptr && toreplace != nullptr)
				{
					
							int r1 = randintrange(0, 99);
							int r2 = randintrange(0, 99);
							int r3 = randintrange(0, 99);
							papyrusMagicEffect::SetArea(toswap, r1);
							papyrusMagicEffect::SetBaseCost(toswap, r2);
							papyrusMagicEffect::SetCastTime(toswap, r3);
				
						
						
				}



			
			}
		}
	}
	void shufflelootwrld(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, TESObjectCELL* thisCell, TESQuest * delquest, BGSListForm * todel, bool chaos=false)
	{


		if (!thisCell)
		{
			return;
		}
		bool refrplcd = false;
		registry = (*g_skyrimVM)->GetClassRegistry();
		
		DataHandler * dataHandler = DataHandler::GetSingleton();
		PersistentFormManager * pformmanager = PersistentFormManager::GetSingleton();
		//UInt32 a_refhandle = NULL;
		_MESSAGE("PREPcompleted");
		void * chcknull = NULL;
		UInt32	numRefs = thisCell->refData.maxSize - thisCell->refData.freeEntries;
		for (UInt32 i = 0; i < numRefs; i++)
			{
				TESObjectCELL::ReferenceData::Reference * arrayreftoreplace = &thisCell->refData.refArray[i];
				refrplcd = false;
				if (arrayreftoreplace && arrayreftoreplace->unk08 != nullptr)
				{

					if (referenceUtils::GetNumReferenceAliases(&thisCell->refData.refArray[i].ref->extraData) == 0)
					{
						UInt8 reftype = thisCell->refData.refArray[i].ref->baseForm->formType;
						TESObjectREFR * refToReplace = thisCell->refData.refArray[i].ref;
						NiPoint3 pos;
						pos.x = thisCell->refData.refArray[i].ref->pos.x;
						pos.y = thisCell->refData.refArray[i].ref->pos.y;
						pos.z = thisCell->refData.refArray[i].ref->pos.z;

						if (reftype == 27)
						{
							refrplcd = true;
							int size = dataHandler->books.count - 1;

							int r1 = randintrange(0, size);
							TESObjectBOOK * refToPlace = NULL;
							dataHandler->books.GetNthItem(r1, refToPlace);
							if (refToPlace != NULL)
							{

								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);

							}

						}
						else if (reftype == 26)
						{
							refrplcd = true;
							int size = dataHandler->armors.count - 1;

							int r1 = randintrange(0, size);
							TESObjectARMO * refToPlace = NULL;
							dataHandler->armors.GetNthItem(r1, refToPlace);
							if (refToPlace != NULL)
							{

								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);


							}
						}
						else if (reftype == 41)
						{
							refrplcd = true;
							int size = dataHandler->weapons.count - 1;

							int r1 = randintrange(0, size);
							TESObjectWEAP* refToPlace = NULL;
							dataHandler->weapons.GetNthItem(r1, refToPlace);
							if (refToPlace != NULL)
							{

								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);

							}
						}
						else if (reftype == 30)
						{
							refrplcd = true;
							int size = dataHandler->ingredients.count - 1;

							int r1 = randintrange(0, size);
							IngredientItem* refToPlace = NULL;
							while (dataHandler->ingredients.GetNthItem(r1, refToPlace) == NULL)
							{
								r1 = randintrange(0, size);
								dataHandler->ingredients.GetNthItem(r1, refToPlace);
							}
							if (refToPlace != NULL)
							{
								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);

							}
						}
						else if (reftype == 32)
						{
							refrplcd = true;
							int size = dataHandler->miscObjects.count - 1;
							int r1sub = randintrange(0, 10);
							int r1 = 1;
							int tsize = size - 966;
							if (r1sub < 5)
							{

								r1 = r1 = randintrange(0, 427);
							}
							else if (r1sub > 5)
							{

								r1 = randintrange(967, size);
							}
							TESObjectMISC* refToPlace = NULL;
							dataHandler->miscObjects.GetNthItem(r1, refToPlace);
							if (refToPlace != NULL)
							{

								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);

							}
						}
						else if (reftype == 46)
						{
							refrplcd = true;
							int size = dataHandler->potions.count - 1;

							int r1 = randintrange(0, size);
							AlchemyItem* refToPlace = NULL;
							while (dataHandler->potions.GetNthItem(r1, refToPlace) == NULL)
							{
								int r1 = randintrange(0, size);
								dataHandler->potions.GetNthItem(r1, refToPlace);
							}
							if (refToPlace != NULL)
							{

								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);

							}
						}
						else if (reftype == 40 && chaos == true)
						{
							refrplcd = true;
							int size = dataHandler->arrFURN.count - 1;

							int r1 = randintrange(0, size);
							TESFurniture* refToPlace = NULL;
							while (dataHandler->arrFURN.GetNthItem(r1, refToPlace) == NULL)
							{
								int r1 = randintrange(0, size);
								dataHandler->arrFURN.GetNthItem(r1, refToPlace);
							}
							if (refToPlace != NULL)
							{

								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);

							}
						}
						else if (reftype == 43 && chaos == true)
						{
							refrplcd = false;
							int size = dataHandler->npcs.count - 1;

							int r1 = randintrange(0, size);
							TESNPC * refToPlace = NULL;
							while (dataHandler->npcs.GetNthItem(r1, refToPlace) == NULL)
							{
								int r1 = randintrange(0, size);
								dataHandler->npcs.GetNthItem(r1, refToPlace);
							}
							if (refToPlace != NULL)
							{

								Actor * actor = DYNAMIC_CAST(refToReplace, TESObjectREFR, Actor);
								if (actor != NULL)
								{
									// CALL_MEMBER_FN(actor, SetRace)(refToPlace->race.race, false);
								}


							}
						}
						else if (reftype == 61)
						{

						}
						else if (reftype == 28 && chaos == true)
						{

							refrplcd = true;
							int size = dataHandler->arrCONT.count - 1;

							int r1 = randintrange(0, size);
							TESObjectCONT* refToPlace = NULL;
							while (dataHandler->arrCONT.GetNthItem(r1, refToPlace) == NULL)
							{
								int r1 = randintrange(0, size);
								dataHandler->arrCONT.GetNthItem(r1, refToPlace);
							}
							if (refToPlace != NULL)
							{

								PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);

							}
						}
						else
						{

						}
					}
					if (refrplcd == true)
					{
						BSFixedString eventName("CHUrefFilled");
						TESForm * form2send = DYNAMIC_CAST(arrayreftoreplace->ref, TESObjectREFR, TESForm);
						//EventQueueFunctor< TESObjectREFR *, TESForm *>(eventName, form2send).SendEvent(arrayreftoreplace->ref);

						const uint64_t handle = EventLib::GetVMHandleForQuest(delquest, false, 0);
						//CALL_MEMBER_FN(arrayreftoreplace->ref, objDelete)();
						Delete_Native(registry, stackId, arrayreftoreplace->ref);
						refrplcd = false;
						//if (handle)
						{

							//EventLib::EventFunctor1<TESForm *>(eventName, form2send)(handle);
						}

					}



				}

			
		}
		_MESSAGE("Random succeed");
		return;
	}
	void swaptextsets(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput)
	{
		DataHandler * dataHandler = DataHandler::GetSingleton();
			for (UInt32 i = 0; i < dataHandler->arrTXST.count; i++)
			{
				TESForm * toswapF = NULL;
				TESForm * toreplaceF = NULL;
				dataHandler->arrTXST.GetNthItem(i, toswapF);
				int k = randintrange(0, (dataHandler->arrTXST.count - 1));
				dataHandler->arrTXST.GetNthItem(k, toreplaceF);
				BGSTextureSet * toswap = DYNAMIC_CAST(toswapF, TESForm, BGSTextureSet);
				BGSTextureSet * toreplace = DYNAMIC_CAST(toreplaceF, TESForm, BGSTextureSet);
				if (toswap && toreplace) {
					for (UInt32 j = 0; j < toswap->kNumTextures; j++)
					{

						toswap->textureSet.SetTexturePath(j, toreplace->textureSet.GetTexturePath(j));

					}

				}
			}
			for (UInt32 i = 0; i < dataHandler->npcs.count; i++)
			{
				TESNPC * toswapF = NULL;
				BGSHeadPart * toreplaceF = NULL;
				dataHandler->npcs.GetNthItem(i, toswapF);
				int k = randintrange(0, (dataHandler->headParts.count - 1));
				dataHandler->headParts.GetNthItem(k, toreplaceF);
				if (toswapF != nullptr && toreplaceF != nullptr) {
					CALL_MEMBER_FN(toswapF, ChangeHeadPart)(toreplaceF);

				}


			}
	}
	bool RegisterFuncs(VMClassRegistry* a_registry) {
		a_registry->RegisterFunction(
			new NativeFunction4<StaticFunctionTag, void, TESObjectCELL*, TESQuest*, BGSListForm*, bool>("shufflelootwrld", "chutools", chutools::shufflelootwrld, a_registry));
		a_registry->RegisterFunction(
			new NativeFunction2<StaticFunctionTag, void, VMArray<TESLevItem*>, UInt32>("shufflelootlist", "chutools", chutools::shufflelootlist, a_registry));
		a_registry->RegisterFunction(
			new NativeFunction3<StaticFunctionTag, void, BGSListForm*, BGSListForm*, BGSListForm*>("shuffleNPClist", "chutools", chutools::shuffleNPClist, a_registry));
		a_registry->RegisterFunction(
			new NativeFunction1<StaticFunctionTag, void, UInt32>("shufflelootcont", "chutools", chutools::shufflelootcont, a_registry));
		a_registry->RegisterFunction(
			new NativeFunction1<StaticFunctionTag, void, UInt32>("shuffleench", "chutools", chutools::shuffleench, a_registry));
		a_registry->RegisterFunction(
			new NativeFunction0 <TESForm, TESForm *>("randformofsametype", "Form", chutools::randformofsametype, a_registry));
		a_registry->RegisterFunction(
			new NativeFunction0 <StaticFunctionTag, void>("swaptextsets", "chutools", chutools::swaptextsets, a_registry));
		a_registry->RegisterFunction(
			new NativeFunction2<StaticFunctionTag, void, BGSListForm*, VMArray<TESLevItem*>>("distributeformlist", "chutools", chutools::distributeformlist, a_registry));
		return true;
	}






}
extern "C" {
	bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\Chustools.log");

		//gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\skse64.log");

		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("Chu's Tools v%s", MYFP_VERSION_VERSTRING);

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "Chu's Tools ";
		a_info->version = MYFP_VERSION_MAJOR;

		if (a_skse->isEditor) {
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}
		else if (a_skse->runtimeVersion != RUNTIME_VERSION_1_5_97) {
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_skse->runtimeVersion);
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSEInterface* a_skse)
	{
		_MESSAGE("chutoolsloaded");
		g_papyrus = (SKSEPapyrusInterface *)a_skse->QueryInterface(kInterface_Papyrus);

		//Check if the function registration was a success...
		bool btest = g_papyrus->Register(chutools::RegisterFuncs);

		if (btest) {
			_MESSAGE("Register Succeeded");
		}
		return true;
	}
};
