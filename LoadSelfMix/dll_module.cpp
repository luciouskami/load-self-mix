#include "dll_module.h"
#include "fp_call.h"
#include "xorstr.hpp"
#include <vector>


namespace model_pack
{
	dll_module* dll_module::instance_ = nullptr;
	dll_module::dll_module()
	= default;

	dll_module::~dll_module()
	= default;

	dll_module* dll_module::GetInstance()
	{

		if (nullptr == instance_)
		{
			instance_ = new dll_module;
		}
		return instance_;
	}

	void dll_module::Init()
	{
		if (is_init_)
		{
			return;
		}
		wchar_t v_war3_path[MAX_PATH + 1] = { '\0' };
		GetModuleFileNameW(nullptr, v_war3_path, MAX_PATH);
		war3_root_dir = fs::path(v_war3_path).remove_filename();
		mpq_root_dir_ = war3_root_dir / xorstr_(L"次元风暴模型包");
		if (!fs::exists(mpq_root_dir_))
		{
			fs::create_directories(mpq_root_dir_);
			return;
		}
		storm_dll_instance_ = GetModuleHandleW(xorstr_(L"storm.dll"));
		storm_266_address_ = reinterpret_cast<uintptr_t>(GetProcAddress(storm_dll_instance_, reinterpret_cast<const char*>(266)));
		storm_252_address_ = reinterpret_cast<uintptr_t>(GetProcAddress(storm_dll_instance_, reinterpret_cast<const char*>(252)));
		is_init_ = true;
	}

	void dll_module::LoadModelPacks()
	{
		std::vector<fs::path> v_model_pack_path_vector;
		v_model_pack_path_vector.clear();
		for (auto& v : fs::directory_iterator(mpq_root_dir_))
		{
			if (!fs::is_regular_file(v.path()))
			{
				continue;
			}
			if (v.path().extension().string() == ".mpq")
			{
				v_model_pack_path_vector.emplace_back(v.path());
			}
		}
		if (v_model_pack_path_vector.empty())
		{
			return;
		}
		const auto v_mpq_count = v_model_pack_path_vector.size();

		for (size_t i = 0; i < v_mpq_count + 1; ++i)
		{
			mpq_handles_.emplace_back(new HANDLE);
		}

		for (size_t i = 0; i < v_mpq_count + 1; ++i)
		{
			if (!v_model_pack_path_vector[i].string().empty())
			{
				base::std_call<BOOL>(storm_266_address_,v_model_pack_path_vector[i].string().c_str(), 0x30, 0, &mpq_handles_[i]);
			}
		}

	}

	void dll_module::UnLoadModelPacks()
	{
		//for (size_t i = 0; i < mpq_handles_.size(); ++i)
		//{
		//	if (nullptr != mpq_handles_[i])
		//	{
		//		delete mpq_handles_[i];
		//		base::std_call<BOOL>(storm_266_address_, v_model_pack_path_vector[i].string().c_str(), 0x30, 0, &mpq_handles_[i]);
		//	}
		//}
	}

	bool dll_module::IsInit() const
	{
		return is_init_;
	}

	void dll_module::Attach()
	{
		if (is_init_)
		{
			return;
		}

		Init();

		if (!is_init_)
		{
			return;
		}

		LoadModelPacks();
	}

	void dll_module::Detach()
	{
		if (!is_init_)
		{
			return;
		}

		UnLoadModelPacks();
	}
}
