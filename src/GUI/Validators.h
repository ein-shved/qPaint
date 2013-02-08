#ifndef _VALIDATORS_H
#define _VALIDATORS_H

#include <QValidator>

class ScaleValidator : public QValidator {
public:
	State validate ( QString & input, int & pos ) const;
};

class MedianValidator : public QValidator {
public:
	State validate ( QString & input, int & pos ) const;
};

class GaussianValidator : public QValidator {
public:
	State validate ( QString & input, int & pos ) const;
};

class GaussianSigmaValidator : public QValidator {
public:
	State validate ( QString & input, int & pos ) const;
};
class RotateValidator : public QValidator {
public:
	State validate ( QString & input, int & pos ) const;
};
class TableValidator : public QValidator {
public:
	State validate ( QString & input, int & pos ) const;
};
class ManualValidator : public QValidator {
public:
	State validate ( QString & input, int & pos ) const;
};

#endif //_VALIDATORS_H