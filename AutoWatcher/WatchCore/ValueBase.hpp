#pragma once
#include "Define.h"
#include "Default.h"
#include "Checker.hpp"

/// <summary>
/// Class ValueBase.
/// </summary>
template <class ValueType>
class ValueBase
{
public:
	/// <summary>
	/// ��ȡValueֵ
	/// </summary>
	ValueType& Value(void)
	{
		return _value;
	}

	/// <summary>
	/// Values the specified value.
	/// </summary>
	/// <param name="val">The value.</param>
	void Value(const ValueType& val)
	{ 
		SetValue(val);
	}

	ValueType* Reference(void)
	{
		return &_value;
	}

	operator ValueType()
	{
		return _value;
	}

	ValueBase& operator=(const ValueType& val)
	{
		SetValue(val);
		return *this;
	}

	ValueBase& operator=(const ValueBase& val)
	{
		if (this == &val)
			return *this;

		SetValue(val());

		return *this;
	}

	ValueBase(void)
		:_value(Value<ValueType>::Default())
	{
	}

	ValueBase(const ValueType& val)
		:_value(val)
	{
	}

	ValueBase(ValueBase& orginal)
		:_value(orginal)
	{
	}

private:
	void SetValue(const ValueType& val)
	{
		if (Checker<ValueType>::Check(val))
		{
			_value = val;
		}
		else
		{
			Log::Warning("�޷�ͨ����ֵ��Ч����֤��������ֵ");
		}
	}

	ValueType _value;
};