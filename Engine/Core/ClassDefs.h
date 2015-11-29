#pragma once

#define AER_CLASS_INSTACE(Class) Class##Instance
#define AER_DEREF_INSTANCE(Class) *(AER_CLASS_INSTACE(Class))

#define AER_DEFINE_INSTANCE(Class) Class* Class::Class##Instance = nullptr

#define AER_DEF_SINGLE_INSTANCE(Class)	\
		Class##();									\
		~##Class##();								\
		static Class* AER_CLASS_INSTACE(Class)	\


#define AER_SINGLETON(Class)						\
	private:										\
	AER_DEF_SINGLE_INSTANCE(Class);					\
	static Class& instance()						\
	{												\
		if (AER_CLASS_INSTACE(Class) == nullptr)	\
		{											\
			AER_CLASS_INSTACE(Class) = new Class();	\
		}											\
		return AER_DEREF_INSTANCE(Class);			\
	}												\
	public: