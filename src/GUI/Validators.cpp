#include "Validators.h"

QValidator::State ScaleValidator::validate ( QString& input, int& ) const
{
	if ( input.isEmpty () )
		return Intermediate;
	bool ok;
	float value = input.toFloat ( &ok );
	if ( ok && value>=0 ) {
		return Acceptable;
	} else {
		return Invalid;
	}
	return Invalid;
}

QValidator::State MedianValidator::validate ( QString& input, int& ) const
{
	if ( input.isEmpty () )
		return Intermediate;
	bool ok;
	uint value = input.toUInt ( &ok ) ;
	if ( ok && 0 < value && value <= 255 ) {
		return Acceptable;
	} else {
		return Invalid;
	}
	return Invalid;
}

QValidator::State GaussianValidator::validate ( QString& input, int& ) const
{
	if ( input.isEmpty () )
		return Intermediate;
	bool ok;
	uint value = input.toUInt ( &ok ) ;
	if ( ok && 0 < value && value <= 255 ) {
		return Acceptable;
	} else {
		return Invalid;
	}
	return Invalid;
}

QValidator::State GaussianSigmaValidator::validate ( QString& input, int& ) const
{
	if ( input.isEmpty () )
		return Intermediate;
	bool ok;
	float value= input.toFloat ( &ok );
	if ( ok && 0<=value && value <=42 ) {
		return Acceptable;
	} else {
		return Invalid;
	}
	return Invalid;
}

QValidator::State RotateValidator::validate ( QString& input, int& ) const
{
	if ( input.isEmpty () || input=="-" )
		return Intermediate;
	bool ok;
	int value = input.toInt ( &ok ) ;
	if ( ok && -360 <= value && value <= 360 ) {
		return Acceptable;
	} else {
		return Invalid;
	}
	return Invalid;
}

QValidator::State TableValidator::validate ( QString& input, int& ) const
{
	if ( input.isEmpty () || input=="-" )
		return Intermediate;
	bool ok;
	input.toFloat ( &ok );
	if ( ok ) {
		return Acceptable;
	} else {
		return Invalid;
	}
	return Invalid;
}

QValidator::State ManualValidator::validate ( QString& input, int& ) const
{
	if ( input.isEmpty () )
		return Intermediate;
	bool ok;
	int value = input.toUInt ( &ok ) ;
	if ( ok && value < 3 )
		return Intermediate;
	if ( ok && 3 <= value && value <= 30 ) {
		return Acceptable;
	} else {
		return Invalid;
	}
	return Invalid;
}