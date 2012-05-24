#include <exception>

#ifndef CPEXCEPTIONS_H
#define CPEXCEPTIONS_H

class NotImplementedError: public std::exception
{
private:
	std::string err;
public:
	NotImplementedError() throw(){};
	NotImplementedError(std::string errstring) throw(){err=errstring;};
  virtual const char* what() const throw()
  {
    return err.c_str();
  }
};

class SolutionError: public std::exception
{
private:
	std::string err;
public:
	SolutionError() throw(){};
	SolutionError(std::string errstring) throw(){err=errstring;};

  virtual const char* what() const throw()
  {
    return "Solution failed";
  }
};


class ValueError: public std::exception
{
private:
	std::string err;
public:
	ValueError() throw(){};
	ValueError(std::string errstring) throw(){err=errstring;};

  virtual const char* what() const throw()
  {
    return "Solution failed";
  }
};

class AttributeError: public std::exception
{
private:
	std::string err;
public:
	AttributeError() throw(){};
	AttributeError(std::string errstring) throw(){err=errstring;};

  virtual const char* what() const throw(){ return err.c_str(); }
};

#endif