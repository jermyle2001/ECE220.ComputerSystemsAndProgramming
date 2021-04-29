//Partners: bgin2 jeremyl6, tmshu2

#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber() //Empty Constructor
{
    /* Your code here */
    real_component = 0.0; //Empty constructor by setting real_component to zero
}

RealNumber::RealNumber(double rval) //Complete Constructor - sets real_component to rval
{
    /* Your code here */
    real_component = rval;
}

RealNumber::RealNumber( const RealNumber& other ) //Copy constructor - RealNumber is an address of a pointer
{
    /* Your code here */
    real_component = other.get_real_component(); 
}

//Getter and Setter functions provide public access to read/write private vars

void RealNumber::set_real_component (double rval) //Update ALL class variables, including variables inherited from base class (only class variable is real_component)
{
    /* Your code here */
    real_component = rval;
}

double RealNumber::get_real_component() const //With getter functions, no variables can be modified - this function gets the value stored at real_component (rval)
{
    /* Your code here */
    return real_component;
}

double RealNumber::get_magnitude() const{ //Get magnitude of rval
    /* Your code here */
    return abs(real_component); //Magnitude always positive, use absolute value function and return real_component
}

double RealNumber::get_phase() const{ //Get phase of rval - phase is either 0 or pi (derived from equation)
    /* Your code here */
    return calculate_phase(real_component, 0); //Return pi if real_component is less than zero -------------------Come back to this?-------------------
}

RealNumber RealNumber::operator + (const RealNumber& arg) //RealNumber + RealNumber = RealNumber
{
    /* Your code here */
    return RealNumber(real_component + arg.get_real_component());
}

RealNumber RealNumber::operator - (const RealNumber& arg) //RealNumber -RealNumber = RealNumber
{
    /* Your code here */
    return RealNumber(real_component - arg.get_real_component());
}

RealNumber RealNumber::operator * (const RealNumber& arg) //RealNumber * RealNumber = RealNumber
{
    /* Your code here */
    return RealNumber(real_component * arg.get_real_component());
}

RealNumber RealNumber::operator / (const RealNumber& arg) //RealNumber / RealNumber = RealNumber
{
    /* Your code here */
    return RealNumber(real_component / arg.get_real_component());
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){ //Components are separate, so just throw into ComplexNumber
    /* Your code here */
	return ComplexNumber(real_component, arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){ //Components are separate, so just throw into ComplexNumber
    /* Your code here */
	return ComplexNumber(real_component, -1 * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(-1 * real_component / arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component + arg.get_real_component(), arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component - arg.get_real_component(), -1 * arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
	double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)(c + id) = (ac-bd) + i(ad+bc)
    //(ac-bd)
    real_temp = (real_component * arg.get_real_component()) - (0 * arg.get_imaginary_component());
    //(ad+bc)
    imag_temp = (real_component * arg.get_imaginary_component()) + (0 * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)/(c + id) = (ac+bd)/(c^2 + d^2), (bc-ad)/(c^2+d^2)
    //(ac+bd)/(c^2 + d^2) RealComponent
    real_temp = (real_component * arg.get_real_component() + 0 * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + arg.get_real_component() * arg.get_real_component());
    //(bc-ad)/(c^2+d^2)
    imag_temp = (0 * arg.get_real_component() - real_component * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + arg.get_real_component() * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}
