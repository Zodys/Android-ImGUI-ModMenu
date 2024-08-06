#pragma once

namespace IL2CPP {
    namespace Array {
        Unity::il2cppObject* ValueBox(Unity::il2cppClass* m_pClass, void* m_value)
        {
            return reinterpret_cast<Unity::il2cppObject * (IL2CPP_CALLING_CONVENTION)(void*, void*)>(Functions.m_ValueBox)(m_pClass, m_value);
        }
        Unity::il2cppObject* ValueBox(const char* m_pClassName, void* m_value)
        {
            Unity::il2cppClass* m_pClass = IL2CPP::Class::Find(m_pClassName);
            return reinterpret_cast<Unity::il2cppObject * (IL2CPP_CALLING_CONVENTION)(void*, void*)>(Functions.m_ValueBox)(m_pClass, m_value);
        }
        template<typename T>
        Unity::il2cppArray<T*>* New(Unity::il2cppClass* m_pClass, int m_lenght)
        {
            return reinterpret_cast<Unity::il2cppArray<T*> * (IL2CPP_CALLING_CONVENTION)(void*, int)>(Functions.m_ArrayNew)(m_pClass, m_lenght);
        }
        template<typename T>
        Unity::il2cppArray<T*>* New(const char* m_pClassName, int m_lenght)
        {
            Unity::il2cppClass* m_pClass = IL2CPP::Class::Find(m_pClassName);
            return reinterpret_cast<Unity::il2cppArray<T*> * (IL2CPP_CALLING_CONVENTION)(void*, int)>(Functions.m_ArrayNew)(m_pClass, m_lenght);
        }
    }
}