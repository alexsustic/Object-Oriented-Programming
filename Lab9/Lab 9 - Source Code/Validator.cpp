#include "Validator.h"

ValidationException::ValidationException(std::string message) : validationMessage{ message }
{

}


void PlantClusterValidator::validateEntity(const PlantCluster& p) {
    
	string errors;
	if (p.getCodedName().size() < 1)
		errors += "Inexisting coded name!\n";
	if (p.getSpecies().size() < 1)
		errors += "Inexisting species !\n";
	if (p.getAgeInMonths() < 0)
		errors += "The age in months can't be represented using negative values!";
	if (p.getDigitizedScan().size() < 1)
		errors += "Inexisting digitized scan!";
	if (errors.size())
		throw ValidationException(errors);

}

std::string RepoException::getExceptionMessage() const {
	return this->exception_message;
}

std::string ServiceException::getExceptionMessage() const {
	return this->exception_message;
}