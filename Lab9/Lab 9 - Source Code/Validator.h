#pragma once
#include "string"
#include "PlantCluster.h"

class ValidationException {

private:
	std::string validationMessage;
public:
	ValidationException(std::string message);
	std::string getMessage() const { return this->validationMessage; };
};

class PlantClusterValidator {

public:
	static void validateEntity(const PlantCluster& p);
};

class Exceptions
{
public:
	virtual std::string getExceptionMessage() const = 0;
};


class RepoException : public Exceptions
{
private:
	std::string exception_message;
public:
	RepoException(std::string  message) { this->exception_message = message; }
	std::string getExceptionMessage() const;
};

class ServiceException : public Exceptions
{
private:
	std::string exception_message;
public:
	ServiceException(std::string message) { this->exception_message = message; }
	std::string getExceptionMessage() const;
};



