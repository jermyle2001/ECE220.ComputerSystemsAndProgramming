#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    /* Your code here */
}

RealNumber::RealNumber(double rval)
{
    /* Your code here */
}

RealNumber::RealNumber( const RealNumber& other )
{
    /* Your code here */
}

void RealNumber::set_real_component (double rval)
{
    /* Your code here */
}

double RealNumber::get_real_component() const
{
    /* Your code here */
    return 0.0;
}

double RealNumber::get_magnitude() const{
    /* Your code here */
    return 0.0;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return 0.0;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber();
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber();
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber();
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber();
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber();
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber();
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber();
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
    return ComplexNumber();
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}