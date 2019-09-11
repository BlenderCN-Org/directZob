#include "ZobObjectManagerWrapper.h"
#include "DirectZob.h"
#include "ZobObject.h"
namespace CLI
{
	ZobObjectManagerWrapper::ZobObjectManagerWrapper():ManagedObject(DirectZob::GetInstance()->GetZobObjectManager(), false)
	{

	}

	System::String^ ZobObjectManagerWrapper::GetZobObjectList()
	{
		return gcnew System::String(m_Instance->GetZobObjectList().c_str());
	}

	ZobObjectInterface^ ZobObjectManagerWrapper::GetZobObject(System::String^ name)
	{
		std::string n;
		MarshalString(name, n);
		ZobObject* z = m_Instance->GetZobObject(n);
		return gcnew ZobObjectInterface(z);
	}

	void ZobObjectManagerWrapper::RemoveZobObject(System::String^ name)
	{
		std::string n;
		MarshalString(name, n);
		ZobObject* z = m_Instance->GetZobObject(n);
		m_Instance->RemoveZobObject(z);
	}

	void ZobObjectManagerWrapper::AddZobObject(System::String^ parent)
	{
		std::string n;
		MarshalString(parent, n);
		ZobObject* z = m_Instance->GetZobObject(n);
		m_Instance->CreateZobObject(z);
	}
}