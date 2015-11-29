#pragma once
//////////////////////////////////////////////////////////////////////////
// Aeris Singly-Linked List
//////////////////////////////////////////////////////////////////////////

#include "CoreDefs.h"
#include "Assert.h"


namespace
{
	template<class T>
	struct Link
	{
		T data;
		Link<T>* next;

		Link()
		{
			next = nullptr;
		}

		Link(const T& item)
		{
			data = item;
		}

		~Link()
		{
			delete next;
		}

		Bool operator==(Link<T> other)
		{
			return data == other.data;
		}
	};

	template <class T>
	struct Link<T*>
	{
		T* data;
		Link<T*>* next;

		Link()
		{
			next = nullptr;
		}

		Link(const T& item)
		{
			data = item;
		}

		~Link()
		{
			delete next;
			delete data;
		}

		Bool operator==(UInt32 audioID)
		{
			return (*data) == audioID;
		}
	};
}


template <class T>
class AerList
{
public:
	AerList()
	{
		reserve = nullptr;
		head = nullptr;
		tail = nullptr;

		listSize = 0;

		allocReserve(defaultReserveNum);
	}

	AerList(UInt32 toReserve)
	{
		reserve = nullptr;
		head = nullptr;
		tail = nullptr;

		listSize = 0;

		allocReserve(toReserve);
	}

	~AerList()
	{
		delete head;
		head = nullptr;
		
		delete reserve;
		reserve = nullptr;
		
		tail = nullptr;
	}

	AerList(const AerList& otherList)
	{

	}

	AerList& operator=(const AerList& otherList)
	{
		return *this;
	}

	void AddToBack(const T& item)
	{
		Link<T>* link = pullOffReserve();
		AerAssert(link != nullptr);

		link->data = item;

		if (tail != nullptr) // There are items in the list
		{
			tail->next = link;
			tail = link;
		}
		else // There isn't anything in the list
		{
			tail = link;
			head = link;
		}

		++listSize;
	}

	void AddToFront(const T& item)
	{
		Link<T>* link = pullOffReserve();
		AerAssert(link != nullptr);

		link->data = item;

		if (head != nullptr) // There are items in the list
		{
			link->next = head;
			head = link;
		}
		else // There isn't anything in the list
		{
			head = link;
			tail = link;
		}

		++listSize;
	}

	T RemoveFront()
	{
		Link<T>* addReserve = head;
		head = head->next;
		--listSize;

		if (head == nullptr)
		{
			tail = nullptr;
		}

		T data = addReserve->data;
		addToReserve(addReserve);

		return data;
	}

	void Remove(T objToRemove)
	{
		Link<T>* current = head;

		while (current->next != nullptr)
		{
			if (current->next->data == objToRemove)
			{
				Link<T>* link = current->next;
				current->next = current->next->next;
				delete link;
				break;
			}

			current = current->next;
		}
	}

	T Find(UInt32 audioID)
	{
		Link<T>* current = head;
		Link<T>* found = nullptr;

		while (current != nullptr)
		{
			if (*current == audioID)
			{
				found = current;
				break;
			}

			current = current->next;
		}

		return current->data;
	}

	T Find(T objToFind)
	{
		Link<T>* current = head;
		Link<T>* found = nullptr;

		while (current != nullptr)
		{
			if (current->data == objToFind)
			{
				found = current;
				break;
			}

			current = current->next;
		}

		return current->data;
	}

	const T& operator[](UInt32 index) const
	{
		AerAssert(index < listSize, "Invalid index");

		Link<T>* link = head;
		for (UInt32 i = 0; i < index; ++i)
		{
			link = link->next;
		}

		return link->data;
	}

	T& operator[](UInt32 index)
	{
		AerAssert(index < listSize, "Invalid index");

		Link<T>* link = head;
		for (UInt32 i = 0; i < index; ++i)
		{
			link = link->next;
		}

		return link->data;
	}

	Int32 Size() const
	{
		return listSize;
	}

	Bool Empty() const
	{
		return listSize == 0;
	}

	T Front() const
	{
		return head->data;
	}

	T Back() const
	{
		return tail->data;
	}

private:
	void allocReserve(UInt32 toReserve)
	{
		for (UInt32 i = 0; i < toReserve; ++i)
		{
			addToReserve(new Link<T>());
		}
	}

	void addToReserve(Link<T>* oldLink)
	{
		if (reserve != nullptr)
		{
			oldLink->next = reserve;
			reserve = oldLink;
		}
		else
		{
			reserve = oldLink;
			oldLink->next = nullptr;
		}
	}

	Link<T>* pullOffReserve()
	{
		Link<T>* link = nullptr;

		if (reserve != nullptr)
		{
			// pull off a reserve node
			link = reserve;
			reserve = reserve->next;

			// Attach the link to the end of the list
			link->next = nullptr;
		}
		else
		{
			// Need to create a link because the reserve is empty
			link = new Link<T>();
			link->next = nullptr;
		}

		return link;
	}

	static const UInt32 defaultReserveNum = 5;
	UInt32 listSize;

	Link<T>* head;
	Link<T>* tail;

	// Reserve of preallocated nodes;
	Link<T>* reserve;
};