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
#include "skse64/PapyrusEventFunctor.h"
#include "skse64/GameEvents.h"
#include <set>
#include "chu-rand/lib/EventFunctors.h"
#include "chu-rand/lib/EventHelpers.h"
#include "chu-rand/lib/EventFunctors.h"
#include "skse64/GameFormComponents.h"

static SKSEPapyrusInterface         * g_papyrus = NULL;
extern EventDispatcher<SKSEModCallbackEvent>	g_modCallbackEventDispatcher;
namespace chutools
{


	void distributeformlist(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, BGSListForm * list, VMArray<TESLevItem*> forms)
	{
		std::array<int, 9117> aj;
		std::iota(aj.begin(), aj.end(), 1);
		int progress = 0;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(aj.begin(), aj.end(), std::default_random_engine(seed));
		std::random_device rd;
		std::mt19937 generator(rd());
		
		if (list)
		{
			
			for (UInt32 i = 0; i < forms.Length(); i++)
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
						
							int lindex = aj[progress];
							std::uniform_int_distribution<int> distribution(1, 25);
							int r1 = distribution(generator);
							CALL_MEMBER_FN(&form2->leveledList, LAddForm)(&form2->leveledList, r1, r1, list->forms.entries[lindex]);
							progress += 1;




							_MESSAGE(" formid");

						}
					}
				
				
			}
		}
		
		DataHandler * dataHandler = DataHandler::GetSingleton();
		
		for (UInt32 i = 0; i < dataHandler->arrLVLI.count; i++)
		{
			TESForm * tempLVLIF = NULL;
			dataHandler->arrLVLI.GetNthItem(i, tempLVLIF);
			TESLeveledList * tempLVLI = DYNAMIC_CAST(tempLVLIF, TESForm, TESLeveledList);
			for (UInt32 k = 0; k < 10; k++)
			{
				if (tempLVLI->length > 250)
				{
					break;
				}
				else
				{
					std::uniform_int_distribution<int> distribution(0, 39);
					int r1 = distribution(generator);
					TESLevItem * formL = NULL;
					forms.Get(&formL, r1);
					CALL_MEMBER_FN(tempLVLI, LAddForm)(tempLVLI, 1, 1, DYNAMIC_CAST(formL, TESLevItem, TESForm));
				}
			}
		}
	}

	void shufflelootwrld(VMClassRegistry* registry, UInt32 stackId, StaticFunctionTag* thisInput, TESObjectCELL* thisCell)
	{


		if (!thisCell)
		{
			return;
		}
		bool refrplcd = false;
		std::random_device rd;
		std::mt19937 generator(rd());
		TESQuest * quest = DYNAMIC_CAST(LookupFormByID(118045387), TESForm, TESQuest);
		TESForm *  tmptodel = LookupFormByID(118688224);
		BGSListForm * todel = DYNAMIC_CAST(tmptodel, TESForm, BGSListForm);
		CALL_MEMBER_FN(todel, RevertList)();
		registry = (*g_skyrimVM)->GetClassRegistry();
		UInt32	numRefs = thisCell->refData.maxSize - thisCell->refData.freeEntries;
		DataHandler * dataHandler = DataHandler::GetSingleton();
		//UInt32 a_refhandle = NULL;
		_MESSAGE("PREPcompleted");
		


		for (UInt32 i = 0; i < numRefs; i++)
		{
			if (thisCell->refData.refArray[i].unk08 && thisCell->refData.refArray[i].ref)
			{
				refrplcd = false;
				if (referenceUtils::GetNumReferenceAliases(&thisCell->refData.refArray[i].ref->extraData) == 0)
				{
					UInt8 reftype = thisCell->refData.refArray[i].ref->baseForm->formType;
					TESObjectREFR * refToReplace = thisCell->refData.refArray[i].ref;
					NiPoint3 pos;
					pos.x = thisCell->refData.refArray[i].ref->pos.x + 100000;
					pos.y = thisCell->refData.refArray[i].ref->pos.y + 100000;
					pos.z = thisCell->refData.refArray[i].ref->pos.z + 100000;

					if (reftype == 27)
					{
						refrplcd = true;
						int size = dataHandler->books.count - 1;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
						TESObjectBOOK * refToPlace = NULL;
						dataHandler->books.GetNthItem(r1, refToPlace);
						if (refToPlace != NULL)
						{

							PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							//CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}

					}
					else if (reftype == 26)
					{
						refrplcd = true;
						int size = dataHandler->armors.count - 1;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
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
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
						TESObjectWEAP* refToPlace = NULL;
						dataHandler->weapons.GetNthItem(r1, refToPlace);
						if (refToPlace != NULL)
						{

							PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							//CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}
					}
					else if (reftype == 30)
					{
						refrplcd = true;
						int size = dataHandler->ingredients.count - 1;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
						IngredientItem* refToPlace = NULL;
						while (dataHandler->ingredients.GetNthItem(r1, refToPlace) == NULL)
						{
							r1 = distribution(generator);
							dataHandler->ingredients.GetNthItem(r1, refToPlace);
						}
						if (refToPlace != NULL)
						{
							PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							//CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}
					}
					else if (reftype == 32)
					{
						refrplcd = true;
						int size = dataHandler->miscObjects.count - 1;
						int r1sub = std::rand() % 10;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = 1;
						int tsize = size - 966;
						if (r1sub < 5)
						{
							std::uniform_int_distribution<int> distribution(1, 427);
							r1 = distribution(generator);
						}
						else if (r1sub > 5)
						{
							std::uniform_int_distribution<int> distribution(967, size);
							r1 = distribution(generator);
						}
						TESObjectMISC* refToPlace = NULL;
						dataHandler->miscObjects.GetNthItem(r1, refToPlace);
						if (refToPlace != NULL)
						{

							PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							//CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}
					}
					else if (reftype == 46)
					{
						refrplcd = true;
						int size = dataHandler->potions.count - 1;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
						AlchemyItem* refToPlace = NULL;
						while (dataHandler->potions.GetNthItem(r1, refToPlace) == NULL)
						{
							int r1 = distribution(generator);
							dataHandler->potions.GetNthItem(r1, refToPlace);
						}
						if (refToPlace != NULL)
						{

							PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							//CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}
					}
					else if (reftype == 40)
					{
						refrplcd = true;
						int size = dataHandler->arrFURN.count - 1;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
						TESFurniture* refToPlace = NULL;
						while (dataHandler->arrFURN.GetNthItem(r1, refToPlace) == NULL)
						{
							int r1 = distribution(generator);
							dataHandler->arrFURN.GetNthItem(r1, refToPlace);
						}
						if (refToPlace != NULL)
						{

							PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							//CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}
					}
					else if (reftype == 43)
					{
						refrplcd = false;
						int size = dataHandler->npcs.count - 1;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
						TESNPC * refToPlace = NULL;
						while (dataHandler->npcs.GetNthItem(r1, refToPlace) == NULL)
						{
							int r1 = distribution(generator);
							dataHandler->npcs.GetNthItem(r1, refToPlace);
						}
						if (refToPlace != NULL)
						{
							
							Actor * actor = DYNAMIC_CAST(refToReplace, TESObjectREFR, Actor);
							if (actor != NULL)
							{
								CALL_MEMBER_FN(actor, SetRace)(refToPlace->race.race, false);
							}
							
							//PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							////CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}
					}
					else if (reftype == 61)
					{
						
					}
					else if (reftype == 28)
					{
					
						refrplcd = true;
						int size = dataHandler->arrCONT.count - 1;
						std::uniform_int_distribution<int> distribution(1, size);
						int r1 = distribution(generator);
						TESObjectCONT* refToPlace = NULL;
						while (dataHandler->arrCONT.GetNthItem(r1, refToPlace) == NULL)
						{
							int r1 = distribution(generator);
							dataHandler->arrCONT.GetNthItem(r1, refToPlace);
						}
						if (refToPlace != NULL)
						{

							PlaceAtMe_Native(registry, stackId, thisCell->refData.refArray[i].ref, refToPlace, 1, false, false);
							//UInt32 a_refhandle = GetOrCreateRefrHandle(thisCell->refData.refArray[i].ref);
							//TESWorldSpace* worldspace = CALL_MEMBER_FN(thisCell->refData.refArray[i].ref, GetWorldspace)();
							//MoveRefrToPosition(thisCell->refData.refArray[i].ref, &a_refhandle, thisCell, worldspace, &pos, &thisCell->refData.refArray[i].ref->rot);
							////CALL_MEMBER_FN(todel, AddFormToList)(DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm));
						}
					}
					else
					{
						/*
							const char * john = thisCell->refData.refArray[i].ref->baseForm->GetName();
							if (john)
							{

								_MESSAGE(john);
							}
							std::string p = std::to_string(thisCell->refData.refArray[i].ref->formID);

								_MESSAGE(p.c_str());


							p = std::to_string(thisCell->refData.refArray[i].ref->baseForm->formType);

								_MESSAGE(p.c_str());

							*/
					}
				}
				if (refrplcd == true)
				{
					BSFixedString eventName("CHUrefFilled");


					TESForm * form2send = DYNAMIC_CAST(thisCell->refData.refArray[i].ref, TESObjectREFR, TESForm);
					EventQueueFunctor< TESObjectREFR *, TESForm *>(eventName, form2send).SendEvent(thisCell->refData.refArray[i].ref);

					const uint64_t handle = EventLib::GetVMHandleForQuest(quest, false, 0);
					if (handle)
					{

							EventLib::EventFunctor1<TESForm *>(eventName, form2send)(handle);
					}
				}
					
					
				
			}

		}
		_MESSAGE("Random succeed");
		return;
	}
	bool RegisterFuncs(VMClassRegistry* a_registry) {
		a_registry->RegisterFunction(
			new NativeFunction1<StaticFunctionTag, void, TESObjectCELL*>("shufflelootwrld", "chutools", chutools::shufflelootwrld, a_registry));
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
		else if (a_skse->runtimeVersion != RUNTIME_VERSION_1_5_80) {
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
