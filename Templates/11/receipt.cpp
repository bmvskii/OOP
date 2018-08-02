// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "receipt.hpp"

void Receipt::forEachService(std::function<void(std::string const&, double, double)> _function) const
{
	for (auto s : m_services)
	{
		_function(s.first, s.second.first, s.second.second);
	}
}

void Receipt::addService(std::string const & _sName)
{
	if (_sName.empty())
	{
		throw std::logic_error(Messages::EmptyServiceName);
	}
		
	if (m_services.find(_sName) != m_services.end())
	{
		throw std::logic_error(Messages::DuplicatedService);
	}
		
	m_services.insert(std::make_pair(_sName, std::make_pair(0.0,0.0)));
}

void Receipt::removeService(std::string const & _sName)
{
	if (_sName.empty())
	{
		throw std::logic_error(Messages::EmptyServiceName);
	}
		
	if (m_services.find(_sName) == m_services.end())
	{
		throw std::logic_error(Messages::ServiceDoesNotExist);
	}

	m_services.erase(_sName);
}

void Receipt::trackDebt(std::string const & _sName, double _debt)
{
	if (_sName.empty())
	{
		throw std::logic_error(Messages::EmptyServiceName);
	}
		
	if (m_services.find(_sName) == m_services.end())
	{
		throw std::logic_error(Messages::ServiceDoesNotExist);
	}
		
	m_services.find(_sName)->second.first += _debt;
}

void Receipt::renameService(std::string const & _oldName, std::string const & _newName)
{
	if (_oldName.empty() || _newName.empty())
	{
		throw std::logic_error(Messages::EmptyServiceName);
	}
		
	if (m_services.find(_oldName) == m_services.end())
	{
		throw std::logic_error(Messages::ServiceDoesNotExist);
	}
		
	if (m_services.find(_newName) != m_services.end())
	{
		throw std::logic_error(Messages::DuplicatedService);
	}
		
	m_services.insert(std::make_pair(_newName, std::make_pair(m_services.find(_oldName)->second.first, m_services.find(_oldName)->second.second)));
	m_services.erase(_oldName);
}

void Receipt::trackPay(std::string const & _sName, double _pay)
{
	if (_sName.empty())
	{
		throw std::logic_error(Messages::EmptyServiceName);
	}
		
	if (m_services.find(_sName) == m_services.end())
	{
		throw std::logic_error(Messages::ServiceDoesNotExist);
	}
		
	if (_pay < 0)
	{
		throw std::logic_error(Messages::InvalidAmountValue);
	}
		
	m_services.find(_sName)->second.second += _pay;
}

double Receipt::getTotalDebt() const
{
	double sum = 0;
	
	for (auto debt : m_services)
	{
		sum += debt.second.first;
	}

	return sum;
}

double Receipt::getTotalPaid() const
{
	double sum = 0;

	for (auto pay : m_services)
	{
		sum += pay.second.second;
	}

	return sum;
}

std::vector<std::string> Receipt::fetchOverpaid() const
{
	std::vector<std::string> result;
	
	for (auto debt : m_services)
	{
		if (debt.second.first < 0)
			result.push_back(debt.first);
	}

	std::sort(result.begin(), result.end());
	
	return result;
}

std::vector<std::string> Receipt::fetchUnderpaid() const
{
	std::vector<std::string> result;

	for (auto debt : m_services)
	{
		if (debt.second.first > 0)
			result.push_back(debt.first);
	}

	std::sort(result.begin(), result.end());

	return result;
}

Receipt::Receipt(std::string const & _ownerName,int _ownerID)
{
	m_name = _ownerName;
	m_ID = _ownerID;

	if (m_name.empty())
	{
		throw std::logic_error(Messages::EmptyPayerName);
	}

	if (m_ID < 1)
	{
		throw std::logic_error(Messages::InvalidAccountNumber);
	}
}