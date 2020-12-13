#include "Core.hpp"

namespace Green
{
	class AppModule;
	class Player;

	class TableCliData
	{
	public:
		char pad_0000[196]; //0x0000
		char* Name; //0x00C4
		char pad_00C8[36]; //0x00C8
		int32_t SmallBlind; //0x00EC
		int32_t BigBlind; //0x00F0
		char pad_00F4[320]; //0x00F4
		int32_t PotSize; //0x0234
		char pad_0238[96]; //0x0238
		int32_t Ante; //0x0298
		char pad_029C[2228]; //0x029C
		int32_t CardsOnDisplay; //0x0B50
		char pad_0B54[8]; //0x0B54
		int32_t CardOneNumber; //0x0B5C
		int32_t CardOneType; //0x0B60
		int32_t CardTwoNumber; //0x0B64
		int32_t CardTwoType; //0x0B68
		int32_t CardThreeNumber; //0x0B6C
		int32_t CardThreeType; //0x0B70
		int32_t CardFourNumber; //0x0B74
		int32_t CardFourType; //0x0B78
		int32_t CardFiveNumber; //0x0B7C
		int32_t CardFiveType; //0x0B80
	};

	class Table
	{
	public:
		int32_t class_id; //0x0000
		char pad_0004[352]; //0x0004
		class TableCliData* data; //0x0164
		char pad_0168[28]; //0x0168
		int32_t RoundNumber; //0x0184
		char pad_0188[80]; //0x0188
		int32_t RoundJoined; //0x01D8
		char pad_01DC[3396]; //0x01DC
		int32_t ButtonId; //0x0F20
		int32_t TurnId; //0x0F24
	};

	class AppModule
	{
	public:
		char pad_0000[20]; //0x0000
		uint32_t cash_table_list; //0x0014
		char pad_0018[8]; //0x0018
		uint32_t tournament_table_list; //0x0020

		std::vector<Table*> GetTables()
		{
			std::vector<Table*> tables;
			
			if (cash_table_list)
			{
				for (int i = 0; i < 6; i++) {
					auto table = RPM<Table*>(cash_table_list + (0x4 * i));

					if (!table)
						break;

					auto class_id = RPM<uint32_t>((uint32_t)table);

					if (!class_id)
						break;

					//g_Logger->Info("table index %i %X %X", i, table, t);

					if (class_id != 0x15D3654 || !table->data || !table->data->Name)
						break;

					//g_Logger->Info("Name: %s", table->data->Name);

					std::string table_name = table->data->Name;

					auto it = std::find_if(tables.begin(), tables.end(), [&table_name](const Table* obj) {return obj->data->Name == table_name; });

					if (it != tables.end())
					{
						break;
					}
					else {
						tables.push_back(table);
					}
				}
			}
			return tables;
		}
	};

	class Player
	{
	public:
		char pad_0000[8]; //0x0000
		char Name[4]; //0x0008
		char pad_000C[12]; //0x000C
		uint32_t NameLength; //0x0018
		char pad_001C[8]; //0x001C
		char* Location; //0x0024
		char pad_0028[128]; //0x0028
		int32_t Bank; //0x00A8
		char pad_00AC[4]; //0x00AC
		int32_t Bet; //0x00B0
		char pad_00B4[20]; //0x00B4
		int32_t State; //0x00C8
		char pad_00CC[12]; //0x00CC
		int32_t CardOneNumber; //0x00D8
		int32_t CardOneType; //0x00DC
		int32_t CardTwoNumber; //0x00E0
		int32_t CardtwoType; //0x00E4
	};

	Core::Core()
	{
		auto AppModuleStr = skCrypt("55 8B EC 51 A1 ? ? ? ? 85 C0 74 ? 8B E5 5D C3 68 ? ? ? ?");
		auto AppModuleFuncAddress = Signature(AppModuleStr).Scan().As<uint64_t*>();
		AppModuleStr.clear();

		g_Logger->Info("AppModule function %X", AppModuleFuncAddress);

		typedef int(__stdcall* AppModuleUnkFunc_)(void*);
		AppModuleUnkFunc_ AppModuleFunc = (AppModuleUnkFunc_)AppModuleFuncAddress;

		uint32_t AppModuleAddress = AppModuleFunc(NULL); // Call the function which returns AppModule pointer
		
		g_Logger->Info("BaseAddress %X", GetModuleHandleA(NULL));
		g_Logger->Info("AppModule %X", AppModuleAddress);

		AppModule* module = reinterpret_cast<AppModule*>(AppModuleAddress);

		while (true)
		{
			auto tables = module->GetTables();

			for (auto& table : tables) {
				g_Logger->Info("Table Name: %s", table->data->Name);
			}

			std::this_thread::sleep_for(1500ms);
		}

		/*
		uint32_t table_list = RPM<uint32_t>(AppModule + 0x14);
		g_Logger->Info("table_list %X", table_list);

		Table* first_table = RPM<Table*>(table_list + 0x0);
		g_Logger->Info("first_table %X", first_table);
		g_Logger->Info("first_table data %X", first_table->data);
		g_Logger->Info("Name %s", first_table->data->Name);
		g_Logger->Info("ButtonId %i", first_table->ButtonId);
		g_Logger->Info("TurnId %i", first_table->TurnId);
		*/
	}
}